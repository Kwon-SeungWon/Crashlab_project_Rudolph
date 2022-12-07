#include "rudolph_navigation/rudolph_send_goal.h"

SendGoal::SendGoal()
  : nh_priv_("~")
{
  ROS_INFO("Waiting for the action server to start");
  auto ret = init();
}

bool SendGoal::init()
{
  // Subscriber 노드 실행
  dest_sub_ = nh_.subscribe("dest_val", 20, &SendGoal::poseMsgCallBack, this);
  // std::cout << "222222222" ;
  int chk_point = 0;
  return true;
}

void SendGoal::poseMsgCallBack(const rudolph_msgs::web_rasp::ConstPtr &msg)
{
  start = msg->state;

  middle_x = msg->mid_x, middle_y = msg->mid_y;
  middle_theta = msg->mid_theta;

  dest_x = msg->fin_x, dest_y = msg->fin_y;
  dest_theta = msg->fin_theta;
  chk_point += 1;
  std::cout << "dest_val 작동완료!!\n";
}

void SendGoal::SetFinalDestination(double x_pos,double y_pos,double theta)
{
  typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
  
  MoveBaseClient client("move_base", true);
  client.waitForServer();

  ROS_INFO("Action server started, sending the goal");

  move_base_msgs::MoveBaseGoal goal;
  goal.target_pose.header.stamp = ros::Time::now();

  // set frame
  goal.target_pose.header.frame_id = "map";
  // set position
  goal.target_pose.pose.position.x = x_pos;
  goal.target_pose.pose.position.y = y_pos;
  goal.target_pose.pose.position.z = 0.0;

  // set orientation
  goal.target_pose.pose.orientation.x = 0.0;
  goal.target_pose.pose.orientation.y = 0.0;
  goal.target_pose.pose.orientation.z = sin(theta*0.5);
  goal.target_pose.pose.orientation.w = cos(theta*0.5);

  client.sendGoal(goal);

  ROS_INFO("Waiting for the result");
  bool finished_before_timeout = client.waitForResult(ros::Duration(1.0));

  if (finished_before_timeout)
  {
    actionlib::SimpleClientGoalState state = client.getState();
    ROS_INFO("Action finished: %s",state.toString().c_str());
  }
  else
    ROS_INFO("Action did not finish before the time out.");
}

bool SendGoal::GoFinalDestination()
{
  if (start == 2)
  {
    SetFinalDestination(dest_x, dest_y, dest_theta);
  }
  return true;
}

void SendGoal::SetMidDestination(double x_pos,double y_pos,double theta)
{
  typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
  
  MoveBaseClient client("move_base", true);
  client.waitForServer();

  ROS_INFO("Action server started, sending the goal");

  move_base_msgs::MoveBaseGoal goal;
  goal.target_pose.header.stamp = ros::Time::now();

  // set frame
  goal.target_pose.header.frame_id = "map";
  // set position
  goal.target_pose.pose.position.x = x_pos;
  goal.target_pose.pose.position.y = y_pos;
  goal.target_pose.pose.position.z = 0.0;

  // set orientation
  goal.target_pose.pose.orientation.x = 0.0;
  goal.target_pose.pose.orientation.y = 0.0;
  goal.target_pose.pose.orientation.z = sin(theta*0.5);
  goal.target_pose.pose.orientation.w = cos(theta*0.5);

  client.sendGoal(goal);

  ROS_INFO("Waiting for the result");
  bool finished_before_timeout = client.waitForResult(ros::Duration(1.0));

  if (finished_before_timeout)
  {
    actionlib::SimpleClientGoalState state = client.getState();
    ROS_INFO("Action finished: %s",state.toString().c_str());
    start = 2;
  }
  else
    ROS_INFO("Action did not finish before the time out.");
}

bool SendGoal::GoMidDestination()
{
  // std::cout << "Please input your goal x,y,theta\n";
  // std::cin >> x >> y >> theta;
  // SetMidDestination(x, y, theta);
  if (start == 1)
  {
    SetMidDestination(middle_x, middle_y, middle_theta);
  }
  return true;
}

// bool SendGoal::Check(){
//   return true;
// }


int main(int argc, char** argv){
  ros::init(argc, argv, "send_goal_cpp");
  SendGoal sendgoal;
  
  //int check = 0;

  while(ros::ok()){  
    sendgoal.GoMidDestination();   //경유지 출발
    sendgoal.GoFinalDestination(); 
    ros::spinOnce();
  }

  return 0;
}
