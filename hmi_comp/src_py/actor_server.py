#!/usr/bin/env python

import roslib; roslib.load_manifest('hmi_comp')
from hmi_comp.srv import *
import rospy
import re
import sys

import pygtk
pygtk.require('2.0')
import gtk
import string 
import os
import commands
from std_msgs.msg import String

agent="robot"
def call_actor(req):
    global agent
    if req.goal != "get":
        agent = req.goal
        if agent == "ROBOTS" or agent == "robots":
            agent = "robot"
        return tldl_parserResponse(agent)
    else:
        tmp = agent
        agent = "robot"       
        return tldl_parserResponse(tmp)

def get_agent_server():
    rospy.init_node("actor_server")
    s = rospy.Service("add_actor", tldl_parser, call_actor)
    print "Ready to set the robot name."
    rospy.spin()


if __name__ == "__main__":
    get_agent_server()
