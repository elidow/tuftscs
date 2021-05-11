############# COMP131 Assignment 1 #############
################# vaccum file ##################
#### Eli Dow
####
#### contains class for blackboard and initializes bb in other classes

# imports
import time # Note: time module only used for natural flow of print statements
            #       time for clean_spot is 0.25 sec in real time, but 1 sec for
            #       the blackboard
import random

from general_nodes import set_rob_for_general_nodes
from tasks import set_rob_for_tasks

# global variables
global SUCCEEDED
SUCCEEDED = 'SUCCEEDED'
global RUNNING 
RUNNING = 'RUNNING'
global FAILED 
FAILED = 'FAILED'

# Vaccum Class: blackboard
class Vaccum:

    # constructor
    def __init__(self, dictionary):
        self.BATTERY_LEVEL = dictionary["BATTERY_LEVEL"]
        self.SPOT_CLEANING = dictionary["SPOT_CLEANING"]
        self.GENERAL_CLEANING = dictionary["GENERAL_CLEANING"]
        self.DUSTY_SPOT = dictionary["DUSTY_SPOT"]
        self.HOME_PATH = dictionary["HOME_PATH"]

        self.timer_on = False
        self.time_left = 0

    # decreases blackboard battery
    def decrease_battery(self, decrease):
        self.BATTERY_LEVEL -= decrease

# initializes the blackboard in all necessary classes
def initialize(robot_data):
    global rob
    rob = Vaccum(robot_data)
    set_rob_for_general_nodes(rob)
    set_rob_for_tasks(rob)


