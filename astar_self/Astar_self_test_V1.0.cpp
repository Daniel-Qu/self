#include<iostream>
#include<list>
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>

/* Astar QSL */

struct Point {
  double x;
  double y;
  double z;
  Point() {
    x = 0;
    y = 0;
    z = 0;
  }
};

struct GridCell {
  std::string name;
  int value;
  Point point;
  GridCell() {
    name = "";
    value = 0;
  }
};
struct Node
{
  int px;
  int py;
  double f,g,h;

  Node()
  {
    px = 0;
    py = 0;
    f = g = h = 0.0;
  }

  Node(double px_, double py_, double g_):
    px(px_), py(py_), g(g_)
  {
    ;
  }
  const bool operator <(const Node &node_) const
  {
    return this->f > node_.f;
  }

  void F()
  {
    f = g + h;
  }

  void hManhattanDistance(int &tp_x, int &tp_y)
  {
    h = abs(tp_x - px) + abs(tp_y - py);
  }

  int father[1][2];

};

// const std::vector<std::vector<int> > delta = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
// const int delta[2][4] = {{0, 1 , 0 , -1}, {-1, 0, 1, 0}}; //! done
const int delta[2][4] = {{0, 1 , 0 , -1}, {1, 0, -1, 0}}; //!bad
const double dg = 1.0;

std::string int2str(int i);
std::vector<std::string> pathPlan_Astar(const std::vector< std::vector<GridCell> >& grid_map, std::string start_point, std::string target_point);
bool findIndexWithName(const std::vector< std::vector<GridCell> >& grid_map, const std::string& name, int& cx, int& cy) ;

int main(int argc, char *argv[])
{
  std::string start_name = "A0_0";
  // std::string start_name = "A9_2";
  std::string end_name = "A2_8";
  std::string file_path_name = "/home/daniel/daniel_ws/src/exercise_ws/src/exercise_1/scripts/obsData.txt";
  int x_length = 10;
  int y_length = 10;
  std::vector< std::vector<GridCell> > grid_map(x_length);
  double mapResolution = 0.5;
  for(int i = 0; i < x_length; ++i) {
    for(int j = 0; j < y_length; ++j) {
      GridCell grid_cell;
      grid_cell.name = "A" + int2str(i) + "_" + int2str(j);
      grid_cell.value = 0;
      grid_cell.point.x = i * mapResolution;
      grid_cell.point.y = j * mapResolution;
      grid_map[i].push_back(grid_cell);
    }
  }
  // read obstacle information file
  std::ifstream in;
  in.open(file_path_name.c_str());
  std::string line;
  std::vector<std::string> obsData;
  if (in.is_open()) {
    while (getline (in, line)) {
      obsData.push_back(line);
    }
  } else {
    std::cout << "No such obstacle information file" << std::endl;
  }
  for (int i = 0; i < obsData.size(); i++)
  {
    int num = atoi(obsData[i].c_str());
    int x_index =  num / x_length;
    int y_index = num % x_length;
    grid_map[x_index][y_index].value = 1;
  }
  std::vector<std::string> plan_result = pathPlan_Astar(grid_map, start_name, end_name);
  std::cout << "plan_result.size: " << plan_result.size() << std::endl;
  for(int i = 0; i < plan_result.size(); i++)
  {
    std::cout << plan_result[i] << std::endl;
  }
  return 0;
}

// bool sort_down(Node &node1, Node &node2){return node1.f > node2.f;}
std::vector<std::string> pathPlan_Astar(const std::vector< std::vector<GridCell> >& grid_map, std::string start_point, std::string target_point)
{
  std::vector<std::string> plan_result;
  int map_size_x = grid_map.size();
  int map_size_y = 0;
  if(map_size_x > 0) {
    map_size_y = grid_map[0].size();
  }

  int sp_x , sp_y;
  int tp_x, tp_y;

  findIndexWithName(grid_map, start_point, sp_x, sp_y);
  findIndexWithName(grid_map, target_point, tp_x, tp_y);

  std::list<Node> openList;
  std::list<Node> closeList;

  bool visited[map_size_x][map_size_y] = {false};
  visited[sp_x][sp_y] = true;

  Node start(sp_x, sp_y, 0.0);
  start.hManhattanDistance(tp_x, tp_y);
  start.F();
  openList.push_back(start);

  while(true)
  {
    Node best;
    openList.sort();
    best = openList.back();
    std::cout << "best point: " << best.px << "_" << best.py << std::endl;
    openList.pop_back();

    closeList.push_back(best);
    if(best.px == tp_x && best.py == tp_y)
    {
      break;
    }

    for(int i = 0; i < 4; i++)
    {
      int np_x = best.px;
      int np_y = best.py;

      np_x += delta[0][i];
      np_y += delta[1][i];

      if(np_x < map_size_x && np_y < map_size_y &&
         np_x >= 0 && np_y >= 0 &&
         !visited[np_x][np_y] &&
         !grid_map[np_x][np_y].value)
      {
        Node next(np_x, np_y, best.g + dg);
        next.hManhattanDistance(tp_x, tp_y);
        next.F();
        next.father[0][0] = best.px;
        next.father[0][1] = best.py;
        openList.push_back(next);
        visited[np_x][np_y] = true;
        std::cout << "have new point: " << np_x << "_" <<np_y << std::endl;
      }
    }
  }

  // traceback
  closeList.reverse();
  std::list<Node>::iterator iter = closeList.begin();
  plan_result.push_back(grid_map[iter->px][iter->py].name);
  int father_x = iter->father[0][0];
  int father_y = iter->father[0][1];
  iter++;
  while(iter != closeList.end())
  {
    Node *np;
    np = &(*iter);
    if(np->px == father_x && np->py == father_y)
    {
      plan_result.push_back(grid_map[iter->px][iter->py].name);
      father_x = iter->father[0][0];
      father_y = iter->father[0][1];
      iter++;
    }
    else
    {
      iter = closeList.erase(iter);
    }
  }

  std::reverse(plan_result.begin(), plan_result.end());

  return plan_result;
}

bool findIndexWithName(const std::vector< std::vector<GridCell> >& grid_map, const std::string& name, int& cx, int& cy) {
  for(int i = 0; i < grid_map.size(); ++i) {
    for(int j = 0; j < grid_map[0].size(); ++j) {
      if(name == grid_map[i][j].name) {
        cx = i;
        cy = j;
        return true;
      }
    }
  }
  return false;
}

std::string int2str(int i)
{
  std::string s;
  std::stringstream ss(s);
  ss << i;
  return ss.str();
}
