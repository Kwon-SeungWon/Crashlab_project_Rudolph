#include "std_srvs/Empty.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <ros/ros.h>

int main(int argc, char** argv){
    
    ros::Duration(15).sleep();

    while(ros::ok()){
        ros::Rate loop_rate(1);

        std_srvs::Empty emptymsg;
        ros::service::call("/move_base/clear_costmaps",emptymsg);

        loop_rate.sleep();
        ros::spin();
    }
   

    return 0;
}