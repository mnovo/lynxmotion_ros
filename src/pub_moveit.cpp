// This program will publish joint states

#include <ros/ros.h>
#include <trajectory_msgs/JointTrajectory.h>
#include <sensor_msgs/JointState.h>
#include <stdlib.h>

trajectory_msgs::JointTrajectory msg2;


void pubCallback(const sensor_msgs::JointState msg)
{
  ROS_INFO("joint1: [%f]", msg.position[0]);
  ROS_INFO("joint2: [%f]", msg.position[1]);
  ROS_INFO("joint3: [%f]", msg.position[2]);
  ROS_INFO("joint4: [%f]", msg.position[3]);
  ROS_INFO("joint5: [%f]", msg.position[4]);  
  
  msg2.joint_names.resize(5);     
  msg2.joint_names[0] = "joint_1";
  msg2.joint_names[1] = "joint_2";
  msg2.joint_names[2] = "joint_3";
  msg2.joint_names[3] = "joint_4";
  msg2.joint_names[4] = "joint_5";     

  msg2.points.resize(1);
  msg2.points[0].positions.resize(5);

  msg2.points[0].positions[0] = msg.position[0];
  msg2.points[0].positions[1] = msg.position[1];
  msg2.points[0].positions[2] = msg.position[2];
  msg2.points[0].positions[3] = msg.position[3];
  msg2.points[0].positions[4] = msg.position[4];
  ROS_INFO("After setting msg2");
     
  msg2.points[0].velocities.resize(5);
  msg2.points[0].velocities[0] = 0.5;
  msg2.points[0].velocities[1] = 0.5;
  msg2.points[0].velocities[2] = 0.5;
  msg2.points[0].velocities[3] = 0.5;
  msg2.points[0].velocities[4] = 0.5; 
  ROS_INFO_STREAM("MSG2 in calback "<<  msg2.joint_names[0] << " " << msg2.points[0].positions[0]);   
}


int main(int argc, char **argv) {

  ros::init(argc, argv, "publish_joint_states");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe("/move_group/fake_controller_joint_states", 1000, pubCallback);
  ROS_INFO("After subscribe");
  ros::spinOnce();
  ROS_INFO("After spin"); 
  
  ros::Publisher pub = nh.advertise<trajectory_msgs::JointTrajectory>("/joint_controller_1/command", 1000);  

  ros::Rate rate(2);  
  ros::spinOnce();
  int count =0;
  while(ros::ok())
  {

  if( count>=1)
  {
    pub.publish(msg2); 
  }
  
  ros::spinOnce();
  rate.sleep();
  count++;
  }

return 0;
}