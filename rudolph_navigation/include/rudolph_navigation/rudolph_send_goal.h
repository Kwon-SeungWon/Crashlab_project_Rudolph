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
    bool GoBackHome();

    bool SendMidArrive();
    bool SendFinArrive();
    
    bool Check();
    
    int start = 0;
    
    //int chk_point = 0;

  private:
    ros::NodeHandle nh_;
    ros::NodeHandle nh_priv_;
    // 로봇의 포지션 및 방향 
    ros::Subscriber dest_sub_;
    // 신호 sub 
    ros::Subscriber signal_sub_;
    // 신호 pub
    ros::Publisher signal_pub_;
    
    // 경유지 좌표
    double middle_x,middle_y,middle_z,middle_w;
    double dest_x,dest_y,dest_z,dest_w;
    double x;
    double y;
    double theta;
    bool Mid_Fin = 0;
    bool Fin_Return = 0;
    int chk_point;
    

    void signalCallBack(const rudolph_msgs::rasp_arduino::ConstPtr &sig);

    void poseMsgCallBack(const rudolph_msgs::web_rasp::ConstPtr &msg);
    void SetMidDestination(double x_pos,double y_pos,double z_pos,double w_pos);
    void SetFinalDestination(double x_pos,double y_pos,double z_pos,double w_pos);
};