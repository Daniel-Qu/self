#include<iostream>
#include<list>
#include<vector>
#include<algorithm>
#include<fstream>
#include<sstream>
#include <queue>
// #include<math>
// #include<math.h>

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

// const std::vector<std::vector<int> > delta = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
static const double gs[] = { 1.000, 1.000, 1.000,1.000};
// static const int    dx[] = {   0,         1,         0,         -1   };
static const int    dx[] = {   0,         -1,         0,         1   };
static const int    dy[] = {  -1,         0,        1,          0    };
// static const int    dy[] = {  1,         0,        -1,          0    };

std::string int2str(int i);
bool findIndexWithName(const std::vector< std::vector<GridCell> >& grid_map, const std::string& name, int& cx, int& cy) ;
std::vector<std::string> AStarPathPlanner(const std::vector< std::vector<GridCell> >& grid_map, std::string start_point, std::string target_point);

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
  std::vector<std::string> plan_result = AStarPathPlanner(grid_map, start_name, end_name);
  std::cout << "plan_result.size: " << plan_result.size() << std::endl;
  for(int i = 0; i < plan_result.size(); i++)
  {
    std::cout << plan_result[i] << std::endl;
  }
  std::cout << "done" << std::endl;
  return 0;
}

/*******Astar****************/
struct  QPoint
{
    QPoint()
    {
    xp=0; yp=0;
    }
    QPoint(int xpos, int ypos)
    {
    xp = xpos; yp = ypos;
    }
    int xp;
    int yp;


};

struct CostNode
{
public:
    CostNode(int _x, int _y, float _g, float _h) :
        x(_x), y(_y), g(_g), h(_h)
    {
        f = g + h;
    }

    bool operator <(const CostNode &node) const
    {
        return f > node.f;
    }
public:

    int x, y;

    float f, g, h;

    std::vector<QPoint> path;
};
double distance(float x1,float y1, float x2, float y2)
{
    double dx =x1 - x2;
    double dy = y1 - y2;
    // return std::sqrt(dx * dx + dy * dy);
    return abs(dx) + abs(dy);
}
std::vector<std::string> AStarPathPlanner(const std::vector< std::vector<GridCell> >& grid_map, std::string start_point, std::string target_point)
{


    int xs, ys;
    int xt, yt;
    findIndexWithName(grid_map, start_point, xs, ys);
    findIndexWithName(grid_map, target_point, xt, yt);

    int map_size_x = grid_map.size();
    int map_size_y = 0;
    if(map_size_x > 0)
    {
      map_size_y = grid_map[0].size();
    }
    std::priority_queue<CostNode> cost_nodes;
    std::vector<std::vector<bool> > visited(map_size_x, std::vector<bool>(map_size_y, false));
    std::vector<std::string> plan_result;
    std::vector<QPoint> path;

    CostNode ns(xs, ys, 0, distance(xs,ys,xt, yt));
    ns.path.push_back(QPoint(xs, ys));
    cost_nodes.push(ns);
    visited[ys][xs] = true;



    while (true)
    {
        const CostNode n_best = cost_nodes.top();
        std::cout << "best point: " << n_best.x << "_" << n_best.y << std::endl;
        cost_nodes.pop();

        int x = n_best.x;
        int y = n_best.y;


        if (x == xt && y == yt)
        {
            path = n_best.path;
            break;
        }

        // 1 2 3
        // 8   4
        // 7 6 5

        for (int i = 0; i < 4; ++i)
        {
            int x_new = x + dx[i];
            int y_new = y + dy[i];

            if (
                    (x_new >= 0) && (y_new >= 0) &&
                    (x_new < map_size_x) && (y_new < map_size_y) &&
                    (!visited[x_new][y_new]) &&
                    (!grid_map[x_new][y_new].value))
            {

                CostNode n_new(x_new, y_new, n_best.g + gs[i], distance((float)x_new, (float)y_new, (float)xt,(float)yt));

                n_new.path = n_best.path;
                n_new.path.push_back(QPoint(x_new, y_new));
                cost_nodes.push(n_new);
                visited[x_new][y_new] = true;
                std::cout << "have new point" << x_new << "_" << y_new << std::endl;
            }
        }
    }
    for(int i=0;i<path.size();i++)
     plan_result.push_back(grid_map[path[i].xp][path[i].yp].name);
    /*u = cx * map_size_y + cy;


    plan_result.push_back(grid_map[y_new][x_new].name);*/


  //  std::reverse(plan_result.begin(), plan_result.end());

  return plan_result;
}
/*******Astar****************/
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
