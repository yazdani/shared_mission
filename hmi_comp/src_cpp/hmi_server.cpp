#include "ros/ros.h"
#include <hmi_comp/tldl_parser.h>
#include <hmi_comp/HMIDesig.h>
#include <hmi_comp/Desig.h>
#include <hmi_comp/Propkey.h>
#include <sstream>
#include <string>
#include <std_msgs/String.h>
#include <iostream>
#include <tf/LinearMath/Quaternion.h>
#include <stdio.h> 
#include <math.h>
#include <geometry_msgs/Pose.h>
#include <cstdlib>
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <cstddef>    
#include "std_msgs/String.h"

using namespace std;
//std::string find_agent;

std::vector<string> splitString(string input, string delimiter)
{
  std::vector<string> output;
  
  split(output, input, boost::is_any_of(delimiter), boost::token_compress_on);
  return output;
}

std::vector<hmi_comp::Desig> stringToDesigMsg(string words, string actor, string viewpoint, string clicked)
{
  //ROS_INFO_STREAM("words: "+words);
  std::vector<string> without_zeros = splitString(words,"0");
  std::vector <hmi_comp::Desig> desigs;

  hmi_comp::HMIDesig hmidesig;
  hmi_comp::Propkey prop;
  geometry_msgs::Point point;
  

  for(unsigned i = 0; i < without_zeros.size(); i++)
    {
      if(without_zeros[i].empty())
	break;
      hmi_comp::Desig desig;
      hmi_comp::Propkey prop;
      std::vector<hmi_comp::Propkey> props;
      std::vector<string> without_commas = splitString(without_zeros[i],",");
 
      // bool x = std::find(without_commas.begin(), without_commas.end(),"repeat") != without_commas.end();
      // ROS_INFO_STREAM(x);
      if(std::find(without_commas.begin(), without_commas.end(),"repeat") != without_commas.end()) //ein repeat
       {
	 // ROS_INFO_STREAM("test without_commas[0] "+without_commas[0]);
	 if(without_commas[0].compare("take") == 0 && without_commas[1].compare("off") == 0)
	    {
	      desig.type.data = without_commas[0]+"-off";
	      desig.actor.data = actor;
	      desig.viewpoint.data = viewpoint;
	      desig.instructor.data = "busy_genius";//viewpoint;
	      prop.object_relation.data = "null";
	    }else if (without_commas[0].compare("take") == 0 || without_commas[0].compare("show") == 0 )
	   {
	     desig.type.data = without_commas[0]+"-picture";
	      desig.actor.data = actor;
	      desig.viewpoint.data = viewpoint;//instructor;
	      desig.instructor.data = "busy_genius";//viewpoint;
	      prop.object_relation.data = "null";
	   }else
	    {
	      desig.type.data = without_commas[0];
	      desig.actor.data = actor;
	      desig.viewpoint.data = viewpoint;//instructor;
	      desig.instructor.data = "busy_genius";//viewpoint;
	      prop.object_relation.data = without_commas[1];
	    }
	 //Go to your LEFT  => move(to,robot(left))
	 if(without_commas[2].compare("left") == 0 || without_commas[2].compare("right") == 0)
	   {
	     prop.object_relation.data = without_commas[2];
	     prop.object.data = "null";
	   }else
	   {
	     prop.object.data = without_commas[2];
	   }
	 prop.object_color.data =  without_commas[3];
	 prop.object_size.data = without_commas[4];
	 prop.object_num.data = without_commas[5];
	 prop.object_clicked.data = clicked;
	 prop.flag.data = without_commas[6];
	 prop.pointing_gesture.position.x = 0;
	 prop.pointing_gesture.position.y = 0;
	 prop.pointing_gesture.position.z = 0;
	 props.push_back(prop);
	 prop.object_relation.data = without_commas[9];
	 if(without_commas[10].compare("left") == 0 || without_commas[10].compare("right") == 0)
	   {
	     prop.object_relation.data = without_commas[10];
	     prop.object.data = "null";
	   }else
	   {
	     prop.object.data = without_commas[10];
	   }
	 // prop.object_entity.data = without_commas[10];
	 prop.object_color.data =  without_commas[11];
	 prop.object_size.data = without_commas[12];
	 prop.object_num.data = without_commas[13];
	 prop.object_clicked.data = clicked;
	 prop.flag.data = without_commas[14];
	 prop.pointing_gesture.position.x = 0;
	 prop.pointing_gesture.position.y = 0;
	 prop.pointing_gesture.position.z = 0;
	 props.push_back(prop);
	 desig.propkeys = props;
       

       }else
	{	 //take,pic,tree,null,null,null,false0
	  // ROS_INFO_STREAM("without_commas[0] "+without_commas[0]);

	  if(without_commas[0].compare("take") == 0 && without_commas[1].compare("off") == 0)
	    {
	      desig.type.data = without_commas[0]+"-off";
	      desig.actor.data = actor;//instructor;
	      desig.viewpoint.data = viewpoint;//instructor;
	      desig.instructor.data = "busy_genius";//viewpoint;
	      prop.object_relation.data = "null";	 
	    }else if (without_commas[0].compare("take") == 0 || without_commas[0].compare("show") == 0 )
	   {
	     desig.type.data = without_commas[0]+"-picture";
	      desig.actor.data = actor;//instructor;
	      desig.viewpoint.data = viewpoint;//instructor;
	      desig.instructor.data = "busy_genius";//viewpoint;
	      prop.object_relation.data = "null";	 
	   }else
	    {
	      desig.type.data = without_commas[0];
	      desig.actor.data = actor;//instructor;
	      desig.viewpoint.data = viewpoint;//instructor;
	      desig.instructor.data = "busy_genius";//viewpoint;
	      prop.object_relation.data = without_commas[1];
	    }
	  if(without_commas[2].compare("left") == 0 || without_commas[2].compare("right") == 0)
	   {
	     prop.object_relation.data = without_commas[2];
	     prop.object.data = "null";
	   }else
	   {
	     prop.object.data = without_commas[2];
	   }
	  // prop.object_entity.data = without_commas[2];
	  prop.object_color.data =  without_commas[3];
	  prop.object_size.data = without_commas[4];
	  prop.object_num.data = without_commas[5];
	  prop.object_clicked.data = clicked;
	  prop.flag.data = without_commas[6];
	  prop.pointing_gesture.position.x = 0;
	  prop.pointing_gesture.position.y = 0;
	  prop.pointing_gesture.position.z = 0;
	  props.push_back(prop);
	  desig.propkeys = props;
	}
	 desigs.push_back(desig);
	 
    }
  if(desigs.size() > 1)
    {
        ROS_INFO_STREAM(desigs[0]);
        ROS_INFO_STREAM(desigs[1]); 
    }else
    {
          ROS_INFO_STREAM(desigs[0]);
    }
 return desigs;
}



//bool getCmd(instructor_mission::call_cmd::Request &req,
//            instructor_mission::call_cmd::Response &res)
void getCmd(std_msgs::String request)
{
  string req = request.data;
  ros::NodeHandle n_client;
  ros::NodeHandle n_client_viewpoint;
  ros::NodeHandle n_client_actor;
  ros::NodeHandle n_client_clicked;
  hmi_comp::tldl_parser srv;
  hmi_comp::tldl_parser srv_actor;
  hmi_comp::tldl_parser srv_viewpoint;
  hmi_comp::tldl_parser srv_clicked;
  ros::ServiceClient client = n_client.serviceClient<hmi_comp::tldl_parser>("/ros_parser");
  ros::ServiceClient client_viewpoint = n_client_viewpoint.serviceClient<hmi_comp::tldl_parser>("/add_viewpoint");
  ros::ServiceClient client_actor = n_client_actor.serviceClient<hmi_comp::tldl_parser>("/add_agent_name");
  ros::ServiceClient client_clicked = n_client_clicked.serviceClient<hmi_comp::tldl_parser>("/add_openease_name");
  std::string inp;
  std::string received_highlevel_cmd = req;//.goal;
 
  std::vector<string> actions = splitString(req, " ");

  srv.request.goal = req;
  if (client.call(srv))
     {
     	ROS_INFO_STREAM("Waiting for the TLDL parser");
      }
     else
      {
     	ROS_ERROR("Failed to call the service in TLDL");
     	return;
      }

  // srv_actor.request.goal = "get";
  // if (client_actor.call(srv_actor))
  //    {
  //      ROS_INFO_STREAM("Waiting Agent Server");
  //    }
  // else
  //   {
  //     ROS_ERROR("Failed to call Agent Server");
  //     return;
  //   }

  // srv_viewpoint.request.goal = "get";
  // if (client_viewpoint.call(srv_viewpoint))
  //    {
  //      ROS_INFO_STREAM("Waiting Viewpoint Server");
  //    }
  // else
  //   {
  //     ROS_ERROR("Failed to call Viewpoint Server");
  //     return;
  //   }

  // srv_clicked.request.goal = "get";
  // if (client_clicked.call(srv_clicked))
  //    {
  //      ROS_INFO_STREAM("Waiting Clicked Server");
  //    }
  // else
  //   {
  //     ROS_ERROR("Failed to call Clicked Server");
  //     return;
  //   }


  std::vector<hmi_comp::Desig> desigs;
  hmi_comp::Desig desig;
  string actor;
  string viewpoint;
  string clicked;
  desigs = stringToDesigMsg(srv.response.result, actor, viewpoint, clicked);
  
  ros::NodeHandle ncram_client;
  hmi_comp::HMIDesig cram_srv;
  ROS_INFO_STREAM("Desigs");
  ROS_INFO_STREAM(desigs[0]);
  ros::ServiceClient cram_client = ncram_client.serviceClient<hmi_comp::HMIDesig>("/service_cram_reasoning");
  
  // cram_srv.request.goal = desigs;//srv.response.result;
  // if (cram_client.call(cram_srv))
  //    {
  //    	ROS_INFO_STREAM("Waiting for CRAM");
  //     }
  //    else
  //     {
  //    	ROS_ERROR("Failed to call the service in CRAM");
  //    	return;
  //     }

}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "hmi_server");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("callInstruction",1000,getCmd);
  ROS_INFO("Ready to receive new commands");
  ros::spin();
  
  return 0;
}
