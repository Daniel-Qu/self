#include <string>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Twist.h>
#include <visualization_msgs/Marker.h>
#include <angles/angles.h>

double command_length = 100;
using namespace std;

struct Point {
  double x;
  double y;
  double z;
  Point(double _x = 0, double _y = 0, double _z = 0) : x(_x), y(_y), z(_z) {}
};

struct Speed {
  double v;
  double w;
  Speed(double _v = 0, double _w = 0) : v(_v), w(_w) {}
};

struct Pose : public Point {
  double theta;
  Pose(double _x = 0, double _y = 0, double _z = 0, double _theta = 0) : Point(_x, _y, _z), theta(_theta) {}
};

vector<Speed> trajectoryPlan(const vector<Point>& waypoints, const Pose& cur_pose, const Speed& cur_speed, double period, double command_length);
vector<Speed> mytrajectoryPlan(const vector<Point>& waypoints, const Pose& cur_pose, const Speed& cur_speed, double period, double command_length);
vector<geometry_msgs::PoseStamped> genPathDisplay(const vector<Speed>& plan_result, const Pose& pose, double period);

visualization_msgs::Marker genMarkerDisplay(const vector<Point>& waypoints);

int main(int argc, char** argv) {
  ros::init(argc, argv, "state_publisher");
  ros::NodeHandle n;
  ros::Publisher path_pub = n.advertise<nav_msgs::Path>("path_display", 1);
  ros::Publisher marker_pub  = n.advertise<visualization_msgs::Marker>("waypoint_markers", 1);
  tf::TransformBroadcaster broadcaster;
  ros::Rate loop_rate(30);

  vector<Point> given_waypoints;
  given_waypoints.push_back(Point(0.0, 0.0));
  given_waypoints.push_back(Point(-2.0, -1.0));
  given_waypoints.push_back(Point(2.0, -1.0));
  given_waypoints.push_back(Point(0.0, 3.0));
  given_waypoints.push_back(Point(2.0, 5.0));

  visualization_msgs::Marker waypoints = genMarkerDisplay(given_waypoints);

  Pose current_pose(Pose(-1, 1, 0));
  Speed curret_speed(Speed(0, 0));

  //Control period represented in second
  double dt = 0.01;
  //Number of commands generated at one time

  //vector<Speed> plan_result = trajectoryPlan(given_waypoints, current_pose, curret_speed, dt, command_length);
  vector<Speed> plan_result = mytrajectoryPlan(given_waypoints, current_pose, curret_speed, dt, command_length);

  vector<geometry_msgs::PoseStamped> poses_display = genPathDisplay(plan_result, current_pose, dt);

  // message declarations
  geometry_msgs::TransformStamped odom_trans;
  odom_trans.header.frame_id = "map";
  odom_trans.child_frame_id = "base_link";

  nav_msgs::Path path_display;
  path_display.header.stamp = ros::Time::now();
  path_display.header.frame_id = "map";
  path_display.poses = poses_display;

  // wait for input
  while(std::getchar() != 's') {
    sleep(1);
  }

  int i = 0;
  while (ros::ok())
  {
    marker_pub.publish(waypoints);
    // update transform
    odom_trans.header.stamp = ros::Time::now();
    odom_trans.transform.translation.x = poses_display[i].pose.position.x;
    odom_trans.transform.translation.y = poses_display[i].pose.position.y;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = poses_display[i].pose.orientation;
    // publish transform
    path_pub.publish(path_display);
    broadcaster.sendTransform(odom_trans);
    if (i < poses_display.size() - 1) {
      i += 1;
    } else {
      i += 0;
    }
    // This will adjust as needed per iteration
    loop_rate.sleep();
  }
  return 0;
}

  visualization_msgs::Marker genMarkerDisplay(const vector<Point>& waypoints) {
  visualization_msgs::Marker result;
  result.ns = "wayPoints";
  result.id = 0;
  result.type = 6;
  result.action = 0;
  result.lifetime = ros::Duration(0);
  result.scale.x = 0.2;
  result.scale.y = 0.2;
  result.color.r = 1.0;
  result.color.g = 0.7;
  result.color.b = 1.0;
  result.color.a = 1.0;

  vector<geometry_msgs::Point> pose_list;
  for (int i = 0; i < waypoints.size(); i++) {
    geometry_msgs::Point temp;
    temp.x = waypoints[i].x;
    temp.y = waypoints[i].y;
    temp.z = waypoints[i].z;
    pose_list.push_back(temp);
  }

  result.header.frame_id = "map";
  result.header.stamp = ros::Time::now();
  result.points = pose_list;
  return result;
}

vector<Speed> trajectoryPlan(const vector<Point>& waypoints, const Pose& cur_pose, const Speed& cur_speed, double dt, double command_length)
{
  vector<Speed> plan_result;
  plan_result.clear();
  int num_segment = waypoints.size();
  int command_per_segment = command_length / num_segment;
  int command_remain = command_length - (command_per_segment * num_segment);
  vector<Point> path_points;
  path_points.push_back(cur_pose);
  for (int i = 0; i < waypoints.size(); i++)
  {
    path_points.push_back(waypoints[i]);
  }

  double robot_orientation = cur_pose.theta;
  Speed temp_command;
  for (int i = 0; i < path_points.size() - 1; i++)
  {
    double cur_point_x = path_points[i].x;
    double cur_point_y = path_points[i].y;
    double next_point_x = path_points[i + 1].x;
    double next_point_y = path_points[i + 1].y;
    ROS_INFO_STREAM("current plan: (" << cur_point_x << "," << cur_point_y << ") => (" << next_point_x << "," << next_point_y << ")");
    double delta_x = next_point_x - cur_point_x;
    double delta_y = next_point_y - cur_point_y;

    double segment_length = sqrt(delta_x * delta_x + delta_y * delta_y);
    double segment_angle = atan2(delta_y, delta_x);
    double delta_angle = segment_angle - robot_orientation;
    ROS_INFO_STREAM("delta_angle: " << delta_angle << " segment_angle: " << segment_angle << " robot_orientation: " << robot_orientation);
    temp_command.v = 0;
    temp_command.w = delta_angle / dt;
    plan_result.push_back(temp_command);
    ROS_INFO_STREAM("segment_length:"<<segment_length);
    ROS_INFO_STREAM("command_per_segment:" << command_per_segment);
    double delta_length = segment_length / (command_per_segment - 1);
    ROS_INFO_STREAM("delta_length:"<<delta_length);
    for (int j = 0; j < command_per_segment - 1; j++) {
      temp_command.v = delta_length / dt;
      temp_command.w = 0;
      plan_result.push_back(temp_command);
    }
    robot_orientation = segment_angle;
  }

  for (int i = 0; i < command_remain; i++) {
    temp_command.v = 0;
    temp_command.w = 0;
    plan_result.push_back(temp_command);
  }
  return plan_result;
}

const pi = 3.141592653589;
vector<Speed> mytrajectoryPlan(const vector<Point>& waypoints, const Pose& cur_pose, const Speed& cur_speed, double dt, double command_length)
{
  vector<Speed> plan_result;
  plan_result.clear();
  int num_segment = waypoints.size();

  ROS_INFO_STREAM("num_segment: "<<num_segment);
  int command_per_segment = command_length / num_segment;
  ROS_INFO_STREAM("command_length: "<<command_length);
  ROS_INFO_STREAM("command_per_segment: "<<command_per_segment);
  int command_remain = command_length ;
  vector<Point> path_points;
  path_points.push_back(cur_pose);
  for (int i = 0; i < waypoints.size(); i++)
  {
    path_points.push_back(waypoints[i]);
  }

  double robot_orientation = cur_pose.theta;
  Speed temp_command;
  double cur_point_x,cur_point_y,next_point_x,next_point_y;
  double delta_x,delta_y,segment_length,segment_angle,delta_angle;
  cur_point_x = path_points[0].x;
  cur_point_y = path_points[0].y;
  for (int i = 0; i < path_points.size() - 1; i++)
  {

     cur_point_x = path_points[i].x;
     cur_point_y = path_points[i].y;

     ROS_INFO_STREAM("robot_orientation: " << robot_orientation);
     ROS_INFO_STREAM("start x: " << cur_point_x);
     ROS_INFO_STREAM("start y: " << cur_point_y);



     next_point_x = path_points[i + 1].x;
     next_point_y = path_points[i + 1].y;
     ROS_INFO_STREAM("current plan: (" << cur_point_x << "," << cur_point_y << ") => (" << next_point_x << "," << next_point_y << ")");
     delta_x = next_point_x - cur_point_x;
     delta_y = next_point_y - cur_point_y;

     segment_length = sqrt(delta_x * delta_x + delta_y * delta_y);
     segment_angle = atan2(delta_y, delta_x);
     delta_angle = segment_angle - robot_orientation;

     ROS_INFO_STREAM("segment_length : " << segment_length);
     ROS_INFO_STREAM("segment_angle : " << segment_angle);
     ROS_INFO_STREAM("delta_angle : " << delta_angle);
     while(delta_angle > pi)
     {
       delta_angle = delta_angle - 2 * pi;
     }
     while(delta_angle < -pi)
     {
       delta_angle=delta_angle + 2 * pi;
     }

/**************added by yyf**************/



    double Kp = 3;
    double Ka = 8;
    double Kb = 1.5;



    while(segment_length > 0.08)
    {

	    temp_command.v  = Kp * segment_length;
	    if(temp_command.v > 0.8)      //Max velocity 0.5
	    {
        temp_command.v = 0.8;
	    }

	    if((delta_angle>(-pi/2.0))&&(delta_angle<=(pi/2.0)))
	    {
        temp_command.v=temp_command.v;
      }
      else
      {
     // temp_command.v=-temp_command.v;
       temp_command.v=temp_command.v;
      }
	    temp_command.w  =Ka * delta_angle + Kb * segment_angle;

	     if(temp_command.w  > 60.0 * pi/180.0)        //Max vomega = 0.5
	    {
        temp_command.w  = 60.0 * pi/180.0;
	    }
	    else if(temp_command.w  < -60.0 * pi/180.0)
	    {
        temp_command.w  = -60.0 * pi/180.0;
	    }

      command_remain = command_remain-1;
	    plan_result.push_back(temp_command);

	    robot_orientation = robot_orientation + temp_command.w*dt;
      while(robot_orientation > pi)
      {
        robot_orientation = robot_orientation - 2 * pi;
      }
      while(robot_orientation < -pi)
      {
        robot_orientation = robot_orientation + 2 * pi;
      }
      cur_point_x = cur_point_x + temp_command.v * dt * cos(robot_orientation);
      cur_point_y = cur_point_y + temp_command.v * dt * sin(robot_orientation);
      delta_x = next_point_x - cur_point_x;
      delta_y = next_point_y - cur_point_y;
      segment_length = sqrt(delta_x * delta_x + delta_y * delta_y);
      segment_angle = atan2(delta_y, delta_x);
      delta_angle = segment_angle - robot_orientation;
      while(delta_angle > pi)
      {
        delta_angle=delta_angle - 2 * pi;
      }
      while(delta_angle < -pi)
      {
        delta_angle=delta_angle + 2 * pi;
      }
	 }
       temp_command.v = segment_length/dt;

       plan_result.push_back(temp_command);
 }


    // for (int i = 0; i < command_remain; i++)
    // {
    //   temp_command.v = 0;
    //   temp_command.w = 0;
    //   plan_result.push_back(temp_command);
    // }
    for (int i = 0; i < command_remain; i++)
    {
      temp_command.v = 0;
      temp_command.w = 0;
      plan_result.push_back(temp_command);
    }


  return plan_result;
}

vector<geometry_msgs::PoseStamped> genPathDisplay(const vector<Speed>& plan_result, const Pose& cur_pose, double dt)
{
  vector<geometry_msgs::PoseStamped> poses_display;
  int num_points = plan_result.size();
  double robot_pose_x = cur_pose.x;
  double robot_pose_y = cur_pose.y;
  double robot_pose_theta = cur_pose.theta;
  for (int i = 0; i < num_points; i++)
  {
    geometry_msgs::PoseStamped temp;
    temp.header.stamp = ros::Time::now();
    temp.header.frame_id = "map";
    temp.pose.position.x = robot_pose_x;
    temp.pose.position.y = robot_pose_y;
    temp.pose.position.z = 0;
    temp.pose.orientation = tf::createQuaternionMsgFromYaw(robot_pose_theta - 1.57);
    poses_display.push_back(temp);
    double w = plan_result[i].w;
    robot_pose_theta += w * dt;
    robot_pose_theta = angles::normalize_angle(robot_pose_theta);
    double v = plan_result[i].v;
    robot_pose_x += v * dt * cos(robot_pose_theta);
    robot_pose_y += v * dt * sin(robot_pose_theta);
  }
  return poses_display;
}
