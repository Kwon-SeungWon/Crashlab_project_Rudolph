#include "rudolph_navigation/rudolph_send_goal.h"
#include "std_srvs/Empty.h"

SendGoal::SendGoal()
  : nh_priv_("~")
{
  ROS_INFO("Waiting for the action server to start");
  auto ret = init();
}

bool SendGoal::init()
{
  // 경유지, 목적지 좌표 받는 Subscriber 노드 실행
  dest_sub_ = nh_.subscribe("dest_val", 10, &SendGoal::poseMsgCallBack, this);
  // 신호 받는 Subscriber 노드 실행
  signal_sub_=nh_.subscribe("slave_val", 10, &SendGoal::signalCallBack, this);

  // 신호 주는 Publisher 노드 실행
  signal_pub_=nh_.advertise<rudolph_msgs::rasp_arduino>("master_val",10); 

  int chk_point = 0;
  return true;
}

void SendGoal::poseMsgCallBack(const rudolph_msgs::web_rasp::ConstPtr &msg)
{
  middle_x = msg->mid_x, middle_y = msg->mid_y;
  middle_z = msg->mid_z, middle_w = msg->mid_w;

  dest_x = msg->fin_x, dest_y = msg->fin_y;
  dest_z = msg->fin_z, dest_w = msg->fin_w;

  start = msg->state;
  std::cout << "dest_val 작동완료!!\n";
}

void SendGoal::signalCallBack(const rudolph_msgs::rasp_arduino::ConstPtr &sig)
{
  Mid_Fin = sig->mid_fin;
  Fin_Return = sig->fin_return;
}

void SendGoal::SetFinalDestination1(double x_pos,double y_pos,double z_pos,double w_pos)
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
  goal.target_pose.pose.orientation.z = z_pos;
  goal.target_pose.pose.orientation.w = w_pos;

  client.sendGoal(goal);

  ROS_INFO("Waiting for the result");
  bool finished_before_timeout = client.waitForResult(ros::Duration(1.0));

  if (finished_before_timeout)
  {
    actionlib::SimpleClientGoalState state = client.getState();
    ROS_INFO("Action finished: %s",state.toString().c_str());
    start = 4;
  }
  else
    ROS_INFO("Action did not finish before the time out.");
}

void SendGoal::SetFinalDestination2(double x_pos,double y_pos,double z_pos,double w_pos)
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
  goal.target_pose.pose.orientation.z = z_pos;
  goal.target_pose.pose.orientation.w = w_pos;

  client.sendGoal(goal);

  ROS_INFO("Waiting for the result");
  bool finished_before_timeout = client.waitForResult(ros::Duration(1.0));

  if (finished_before_timeout)
  {
    actionlib::SimpleClientGoalState state = client.getState();
    ROS_INFO("Action finished: %s",state.toString().c_str());
    //start = 5;
    start = 6;
  }
  else
    ROS_INFO("Action did not finish before the time out.");
}

void SendGoal::SetFinalDestination3(double x_pos,double y_pos,double z_pos,double w_pos)
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
  goal.target_pose.pose.orientation.z = z_pos;
  goal.target_pose.pose.orientation.w = w_pos;

  client.sendGoal(goal);

  ROS_INFO("Waiting for the result");
  bool finished_before_timeout = client.waitForResult(ros::Duration(1.0));

  if (finished_before_timeout)
  {
    actionlib::SimpleClientGoalState state = client.getState();
    ROS_INFO("Action finished: %s",state.toString().c_str());
    start = 6;
  }
  else
    ROS_INFO("Action did not finish before the time out.");
}

void SendGoal::SetFinalDestination4(double x_pos,double y_pos,double z_pos,double w_pos)
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
  goal.target_pose.pose.orientation.z = z_pos;
  goal.target_pose.pose.orientation.w = w_pos;

  client.sendGoal(goal);

  ROS_INFO("Waiting for the result");
  bool finished_before_timeout = client.waitForResult(ros::Duration(1.0));

  if (finished_before_timeout)
  {
    actionlib::SimpleClientGoalState state = client.getState();
    ROS_INFO("Action finished: %s",state.toString().c_str());
    start = 7;
  }
  else
    ROS_INFO("Action did not finish before the time out.");
}

void SendGoal::SetMidDestination(double x_pos,double y_pos,double z_pos,double w_pos)
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
  goal.target_pose.pose.orientation.z = z_pos;
  goal.target_pose.pose.orientation.w = w_pos;

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
  if (start == 1)
  {
    SetMidDestination(middle_x, middle_y, middle_z, middle_w);
  }
  return true;
}

bool SendGoal::SendMidArrive()
{
  if(start == 2)
  {
    std::cout << "경유지 도착!!!!!!\n";

    ros::Rate loop_rate(1);

    rudolph_msgs::rasp_arduino sig;
    sig.mid_arrive = true;
    sig.fin_arrive = false;
    signal_pub_.publish(sig);
    
    ros::spinOnce();
    loop_rate.sleep();

    if(Mid_Fin)
    {
      std::cout << "경유지에서 목적지로!!!!!!\n";
      start = 3;
    }

  }
  return true;
}

bool SendGoal::GoFinalDestination1()
{
    if (start == 3) // 112 위방향
    {
      SetFinalDestination1(34.000 ,12.12 ,0.097,0.99);
    }
  return true;
}

bool SendGoal::GoFinalDestination2()
{
    if(start == 4)  // 112 중간1
    {
      SetFinalDestination2(38.037 ,12.000 ,-0.5148, 0.976);
      // ros::param::set("/max_vel_theta",0.5);
      // ros::param::set("/min_vel_theta",-6.0);
    }
  return true;
}

// bool SendGoal::GoFinalDestination3()
// {
//     if(start == 5)  // 112 중간2
//     {
//       SetFinalDestination3(38.037 ,11.150 ,-0.6548, 0.876);
//     }
//   return true;
// }

bool SendGoal::GoFinalDestination4()
{
    if(start == 6)  // 112
    {
      SetFinalDestination4(dest_x, dest_y, dest_z, dest_w); //[37.021 , 10.771, 0.997, 0.121]
      // ros::param::set("/max_vel_theta",4.0);
      // ros::param::set("/min_vel_theta",4.0);
    }
  return true;
}

bool SendGoal::SendFinArrive()
{
  if(start == 7)
  {
    std::cout << "목적지 도착!!!!!\n";

    ros::Rate loop_rate(1);

    rudolph_msgs::rasp_arduino sig;
    sig.mid_arrive = false;
    sig.fin_arrive = true;
    signal_pub_.publish(sig);
    
    ros::spinOnce();
    loop_rate.sleep();
    
    if(Fin_Return)
    {
      std::cout << "목적지에서 출발지로!!!!!!\n";
      start = 8;
    }

  }
  return true;
}

bool SendGoal::GoBackHome()
{
  if(start == 8)
  {
    SetInitialDestination(initial_x,initial_y,initial_z,initial_w);
  }
  return true;
}

void SendGoal::SetInitialDestination(double x_pos,double y_pos,double z_pos,double w_pos)
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
  goal.target_pose.pose.orientation.z = z_pos;
  goal.target_pose.pose.orientation.w = w_pos;

  client.sendGoal(goal);

  ROS_INFO("Waiting for the result");
  bool finished_before_timeout = client.waitForResult(ros::Duration(1.0));

  if (finished_before_timeout)
  {
    actionlib::SimpleClientGoalState state = client.getState();
    ROS_INFO("Action finished: %s",state.toString().c_str());
    //start = 2;
  }
  else
    ROS_INFO("Action did not finish before the time out.");
}

bool SendGoal::ClearCostmap()
{
  std_srvs::Empty emptymsg;
  ros::service::call("/move_base/clear_costmaps",emptymsg);

  return true;
}

int main(int argc, char** argv){
  ros::init(argc, argv, "send_goal_cpp");
  SendGoal sendgoal;
  ros::Time prev_time = ros::Time::now();
  
  //int check = 0;

  while(ros::ok()){  
    ros::Time now_time = ros::Time::now();
    if (now_time - prev_time > ros::Duration(5.0))
    {
      sendgoal.ClearCostmap();
      prev_time = now_time;
    }
    
    //sendgoal.ClearCostmap();
    sendgoal.GoMidDestination();   //경유지 출발
    sendgoal.SendMidArrive();
    sendgoal.GoFinalDestination1(); // 112 전 직진
    sendgoal.GoFinalDestination2(); // 112 우회전
    //sendgoal.GoFinalDestination3(); // 112 우회전2
    sendgoal.GoFinalDestination4(); // 112 실제 위치
    sendgoal.SendFinArrive();
    sendgoal.GoBackHome(); 
    ros::spinOnce();
  }

  return 0;
}