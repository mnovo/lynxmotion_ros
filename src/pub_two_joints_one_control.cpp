// This program will publish joint states

#include <ros/ros.h>
#include <trajectory_msgs/JointTrajectory.h>
#include <stdlib.h>


int main(int argc, char **argv) {
  double max_angle = 0.7, min_angle= -1.1;

  double max_angle2 = 0.95, min_angle2 = -0.95;
  ros::init(argc, argv, "publish_joint_states");
  ros::NodeHandle nh;

  ros::Publisher pub = nh.advertise<trajectory_msgs::JointTrajectory>("/joint_controller_1/command", 1000);

  ros::Rate rate(0.2);
  while(ros::ok())
  {
  	 trajectory_msgs::JointTrajectory msg;

  	 // We will have 2 joints
     msg.joint_names.resize(5);  	 
     msg.joint_names[0] = "joint_1";
     msg.joint_names[1] = "joint_2";
     msg.joint_names[2] = "joint_3";
  	 msg.joint_names[3] = "joint_4";
     msg.joint_names[4] = "joint_5";

     // Create a random point for joints 4 and 5
  	 double a_random_double = (double)rand() / RAND_MAX;
  	 a_random_double = min_angle + a_random_double * (max_angle - min_angle);

     // for joints 1-3
     double a_random_double2 = (double)rand() / RAND_MAX;
     a_random_double2 = min_angle2 + a_random_double2 * (max_angle2 - min_angle2);

	   msg.points.resize(1);
  	 msg.points[0].positions.resize(5);

  	 msg.points[0].positions[0] = a_random_double2;
     msg.points[0].positions[1] = a_random_double2;
     msg.points[0].positions[2] = a_random_double2;
     msg.points[0].positions[3] = a_random_double;
     msg.points[0].positions[4] = a_random_double;
     
  	 msg.points[0].velocities.resize(5);
     msg.points[0].velocities[0] = 0.5;
     msg.points[0].velocities[1] = 0.5;
     msg.points[0].velocities[2] = 0.5;
     msg.points[0].velocities[3] = 0.5;
     msg.points[0].velocities[4] = 0.5;

     ROS_INFO_STREAM("Sending... position to "<<  msg.joint_names[0] << " " << msg.points[0].positions[0]);
     ROS_INFO_STREAM("Sending... position to "<<  msg.joint_names[1] << " " << msg.points[0].positions[1]);
     ROS_INFO_STREAM("Sending... position to "<<  msg.joint_names[2] << " " << msg.points[0].positions[2]);
     ROS_INFO_STREAM("Sending... position to "<<  msg.joint_names[3] << " " << msg.points[0].positions[3]);
     ROS_INFO_STREAM("Sending... position to "<<  msg.joint_names[4] << " " << msg.points[0].positions[4]);
  	 
  	 pub.publish(msg);

  	 rate.sleep();
  	}


return 0;

}