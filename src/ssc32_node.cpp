// This header defines the standard ROS classes.
#include <ros/ros.h>
#include "lynxmotion_ssc32/ssc32_driver.h"

int main( int argc, char** argv )
{
	// Initiliazes the ROS system
	ros::init( argc, argv, "ssc32_node" );

	// Establish this program as a ROS node 
	ros::NodeHandle nh;

	// Pass this program's node to the SSC32 driver
	lynxmotion_ssc32::SSC32Driver ssc32( nh );

	ssc32.spin( );

	return 0;
}
