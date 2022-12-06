#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "rudolph_msgs/rasp_arduino.h"
#include "rudolph_msgs/web_rasp.h"

class SendGoal
{
  public:
    SendGoal();
    //~SendGoal();
    bool init();
    //bool GotoGoal();
    bool GoMidDestination();
    bool GoFinalDestination();
    bool Check();
    int start = 0;
    //int chk_point = 0;
  private:
    ros::NodeHandle nh_;
    ros::NodeHandle nh_priv_;
    // 로봇의 포지션 및 방향 
    ros::Subscriber dest_sub_;
    // 경유지 좌표
    double middle_x,middle_y,middle_theta;
    double dest_x,dest_y,dest_theta;
    double x;
    double y;
    double theta;
    int chk_point;
    void poseMsgCallBack(const rudolph_msgs::web_rasp::ConstPtr &msg);
    void SetMidDestination(double x_pos,double y_pos,double theta);
    void SetFinalDestination(double x_pos,double y_pos,double theta);
};