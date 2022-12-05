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
  dest_sub_ = nh_.subscribe("/dest_val", 10, &SendGoal::poseMsgCallBack, this);
  // std::cout << "222222222" ;
  return true;
}

void SendGoal::poseMsgCallBack(const rudolph_msgs::web_rasp::ConstPtr &msg)
{
  // std::cout << "HIIIIIIIIIIIIIIIIIIIIIII" ;
  dest_x = msg->mid_x, dest_y = msg->mid_y;
  dest_theta = msg->mid_theta;
  count += 1;
}

void SendGoal::SetDestination(double x_pos,double y_pos,double theta)
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

bool SendGoal::InputDestination()
{
  // std::cout << "Please input your goal x,y,theta\n";
  // std::cin >> x >> y >> theta;
  if (count > 0)
  {
    SetDestination(dest_x, dest_y, dest_theta);
  }
  return true;
}

int main(int argc, char** argv){
  ros::init(argc, argv, "send_goal_cpp");
  SendGoal sendgoal;

  while(ros::ok()){
    sendgoal.InputDestination();
    ros::spinOnce();
  }

  return 0;
}
