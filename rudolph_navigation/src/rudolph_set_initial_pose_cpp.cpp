#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

int main(int argc, char** argv){
    
    ros::init(argc, argv, "set_initial_pose_cpp");
    ros::NodeHandle nh_;
    ros::Rate loop_rate(10);

    std::string fixed_frame = "map";
    
    geometry_msgs::PoseWithCovarianceStamped pose;
    ros::Publisher pub_ = nh_.advertise<geometry_msgs::PoseWithCovarianceStamped> ("/initialpose", 1);
    pose.header.frame_id = "map";
    pose.header.stamp = ros::Time::now();

    double x,y;

    double theta = 0.08;

    double X, Y, Z;

    // Input Robot's real Initial pose
    std::cout << "Please input your robot's x,y,theta\n";
    std::cin >> x >> y;

    // set x,y position
    pose.pose.pose.position.x = x;
    pose.pose.pose.position.y = y;
    pose.pose.pose.position.z = 0.0;

    pose.pose.pose.orientation.z = sin(theta*0.5);

    // set theta
    tf::Quaternion quat;
    quat.setRPY(0.0, 0.0, theta);
    tf::quaternionTFToMsg(quat, pose.pose.pose.orientation);
    pose.pose.covariance[6*0+0] = 0.5 * 0.5;
    pose.pose.covariance[6*1+1] = 0.5 * 0.5;
    pose.pose.covariance[6*5+5] = M_PI/12.0 * M_PI/12.0;
    
    ros::param::set("/initial_pose_x",x);
    ros::param::set("/initial_pose_y",y);
    ros::param::set("/initial_pose_a",theta);

    // publish 
    pub_.publish(pose);
    ROS_INFO("x: %f, y: %f, z: 0.0, theta: %f", x, y, theta);
    ros::spinOnce();
    loop_rate.sleep();

    return 0;
}