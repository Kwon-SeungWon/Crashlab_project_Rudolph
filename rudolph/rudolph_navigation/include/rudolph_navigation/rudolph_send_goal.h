#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>


class SendGoal
{
  public:
    SendGoal();
    //~SendGoal();
    //bool init();
    //bool GotoGoal();
    bool InputDestination();
  private:
    ros::NodeHandle nh_;
    ros::NodeHandle nh_priv_;
    // 로봇의 포지션 및 방향 
    double x;
    double y;
    double theta;

    void SetDestination(double x_pos,double y_pos,double theta);
};