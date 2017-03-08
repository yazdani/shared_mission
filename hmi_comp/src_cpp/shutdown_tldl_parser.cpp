#include "ros/ros.h"
#include <stdlib.h>

int main(int argc, char **argv)
{

  ros::init(argc, argv, "shutdown_parser");
  ros::NodeHandle n;

  while(ros::ok())
    {
      
    }
  
  system("killall gnome-terminal");

  return 0;
}
