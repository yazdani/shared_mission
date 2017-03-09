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

agent="busy_genius"
def call_viewpoint(req):
    global agent
    if req.goal != "get":
        agent = req.goal
        return tldl_parserResponse(agent)
    else:
        tmp = agent
        agent = "busy_genius"       
        return tldl_parserResponse(tmp)

def get_viewpoint_server():
    rospy.init_node("viewpoint_server")
    s = rospy.Service("add_viewpoint", tldl_parser, call_viewpoint)
    print "Ready to set the viewpoint."
    rospy.spin()


if __name__ == "__main__":
    get_viewpoint_server()
