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

agent="none"
def call_openease(req):
    global agent
    if req.goal != "get":
        agent = req.goal
        return tldl_parserResponse(agent)
    else:
        tmp = agent
        agent = "none"       
        return tldl_parserResponse(tmp)

def get_openease_server():
    rospy.init_node("openease_server")
    s = rospy.Service("add_openease", tldl_parser, call_openease)
    print "Ready to click on object."
    rospy.spin()


if __name__ == "__main__":
    get_openease_server()
