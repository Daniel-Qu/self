#include<iostream>
#include<list>
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>

/* Dijkstra */

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
  double px;
  double py;
  double f,g,h;

  Node()
  {
    px = 0.0;
    py = 0.0;
    f = g = h = 0.0;
  }

  Node(double px_, double py_, double g_):
    px(px_), py(py_), g(g_)
  {
    ;
  }
  const bool operator <(const Node &node_) const
  {
    return this->f < node_.f;
  }

  void F()
  {
    f = g + h;
  }
  void hManhattanDistance(int &tp_x, int &tp_y)
  {
    h = abs(tp_x - px) + abs(tp_y - py);
  }
};

// const std::vector<std::vector<int> > delta = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
const int delta[2][4] = {{0, 1 , 0 , -1}, {1, 0, -1, 0}};
const double dg = 1.0;

std::string int2str(int i);
std::vector<std::string> pathPlan_Dijkstra(const std::vector< std::vector<GridCell> >& grid_map, std::string start_point, std::string target_point);
bool findIndexWithName(const std::vector< std::vector<GridCell> >& grid_map, const std::string& name, int& cx, int& cy) ;

int main(int argc, char *argv[])
{
  std::string start_name = "A0_0";
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
  std::vector<std::string> plan_result = pathPlan_Dijkstra(grid_map, start_name, end_name);
  std::cout << "plan_result.size: " << plan_result.size() << std::endl;
  for(int i = 0; i < plan_result.size(); i++)
  {
    std::cout << plan_result[i] << std::endl;
  }
  return 0;
}

// bool sort_down(Node &node1, Node &node2){return node1.f > node2.f;}
std::vector<std::string> pathPlan_Dijkstra(const std::vector< std::vector<GridCell> >& grid_map, std::string start_point, std::string target_point) { // use dijkstra algorithm to plan path
  std::vector<std::string> plan_result;
  int map_size_x = grid_map.size();
  int map_size_y = 0;
  if(map_size_x > 0) {
    map_size_y = grid_map[0].size();
  }
  const int max_value = 10000;
  std::vector<bool> close_list(map_size_x * map_size_y, false);
  std::vector<int> traceback(map_size_x * map_size_y, -1);
  std::vector<int> dist(map_size_x * map_size_y, max_value);
  // init the start point
  int cx, cy;
  findIndexWithName(grid_map, start_point, cx, cy);
  int u = cx * map_size_y + cy;
  dist[u] = 0;
  if(cx - 1 >= 0) {
    dist[(cx - 1) * map_size_y + cy] = 1;
    traceback[(cx - 1) * map_size_y + cy] = u;
  }
  if(cx + 1 < map_size_x) {
    dist[(cx + 1) * map_size_y + cy] = 1;
    traceback[(cx + 1) * map_size_y + cy] = u;
  }
  if(cy - 1 >= 0) {
    dist[cx * map_size_y + (cy - 1)] = 1;
    traceback[cx * map_size_y + (cy - 1)] = u;
  }
  if(cy + 1 < map_size_y) {
    dist[cx * map_size_y + (cy + 1)] = 1;
    traceback[cx * map_size_y + (cy + 1)] = u;
  }
  close_list[u] = true;

  // the main loop of dijkstra
  for(int i = 1; i < map_size_x * map_size_y; ++i) {
    int min_dist = max_value;
    for(int j = 0; j < map_size_x * map_size_y; ++j) {
      if(grid_map[j / map_size_y][j % map_size_y].value == 0 && !close_list[j] && dist[j] < min_dist) {
        min_dist = dist[j];
        u = j;
      }
    }
    cx = u / map_size_y;
    cy = u % map_size_y;
    close_list[u] = true;

    if(cx - 1 >= 0 && !close_list[(cx - 1) * map_size_y + cy]) {
      if(dist[(cx - 1) * map_size_y + cy] > min_dist + 1) {
        dist[(cx - 1) * map_size_y + cy] = min_dist + 1;
        traceback[(cx - 1) * map_size_y + cy] = u;
      }
    }
    if(cx + 1 < map_size_x && !close_list[(cx + 1) * map_size_y + cy]) {
      if(dist[(cx + 1) * map_size_y + cy] > min_dist + 1) {
        dist[(cx + 1) * map_size_y + cy] = min_dist + 1;
        traceback[(cx + 1) * map_size_y + cy] = u;
      }
    }
    if(cy - 1 >= 0 && !close_list[cx * map_size_y + (cy - 1)]) {
      if(dist[cx * map_size_y + (cy - 1)] > min_dist + 1) {
        dist[cx * map_size_y + (cy - 1)] = min_dist + 1;
        traceback[cx * map_size_y + (cy - 1)] = u;
      }
    }
    if(cy + 1 < map_size_y && !close_list[cx * map_size_y + (cy + 1)]) {
      if(dist[cx * map_size_y + (cy + 1)] > min_dist + 1) {
        dist[cx * map_size_y + (cy + 1)] = min_dist + 1;
        traceback[cx * map_size_y + (cy + 1)] = u;
      }
    }
  }

  //traceback the plan path
  findIndexWithName(grid_map, target_point, cx, cy);
  u = cx * map_size_y + cy;
  plan_result.push_back(grid_map[cx][cy].name);
  while(dist[u] != 0) {
    u = traceback[u];
    cx = u / map_size_y;
    cy = u % map_size_y;
    plan_result.push_back(grid_map[cx][cy].name);
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
