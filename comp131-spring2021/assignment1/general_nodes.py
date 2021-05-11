############# COMP131 Assignment 1 #############
############## general nodes file ##############
#### Eli Dow
####
#### contains all classes for general nodes such as conditions, composites, 
#### decorators, and the timer

# imports
import time # Note: time module only used for natural flow of print statements
            #       time for clean_spot is 0.25 sec in real time, but 1 sec for
            #       the blackboard
import random

# global variables
global SUCCEEDED
SUCCEEDED = 'SUCCEEDED'
global RUNNING 
RUNNING = 'RUNNING'
global FAILED 
FAILED = 'FAILED'

# initializes blackboard in this class
def set_rob_for_general_nodes(blackboard):
    global rob 
    rob = blackboard

# Behavior_Tree_Super superclass
class Behavior_Tree_Super:
    #   def __init__(self):
    #        self.children = children
    def execute(self):
        if False:
            print("In a tree node")



### Composite Classes ###

# Selection Class
class Selection(Behavior_Tree_Super):
    # constructor
    def __init__(self, children):
        self.children = children

    # run function
    def run(self):
        for child in self.children:
            if child.run() == SUCCEEDED:
                return SUCCEEDED
        return FAILED

# Priority Class
# Note: nodes are already in priority order
class Priority(Selection):
    # constructor
    def __init__(self, children):
        self.children = children

    # run function
    def run(self):
        for priority_child in self.children:
            if priority_child.run() == SUCCEEDED:
                return SUCCEEDED
        return FAILED

# Sequence Class
class Sequence(Behavior_Tree_Super):
    # constructor
    def __init__(self, children):
        self.children = children

    # run function
    def run(self):
        for child in self.children:
            if child.run() == FAILED:
                return FAILED
        return SUCCEEDED


### Condition Classes ###

# Condition Class
class Conditions(Behavior_Tree_Super):
    # constructor
    def __init__(self, attribute):
        self.attribute = attribute

    # run function
    def run(self):
        
        # battery level attribute
        if self.attribute == 'BATTERY_LEVEL':
            print("Checking battery...")
            time.sleep(1)
            if rob.BATTERY_LEVEL < 30:
                print("Battery below 30%!\n")
                time.sleep(1)
                return SUCCEEDED
            else:
                print("Battery at least 30%!\n")
                time.sleep(1)
                return FAILED

        # spot cleaning attribute
        elif self.attribute == 'SPOT_CLEANING':
            print("Checking command for spot cleaning...")
            time.sleep(1)
            if rob.SPOT_CLEANING:
                print("Spot detected!\n")
                time.sleep(1)
                return SUCCEEDED
            else:
                print("No spot detected!\n")
                time.sleep(1)
                return FAILED

        # general cleaning attribute
        elif self.attribute == 'GENERAL_CLEANING':
            print("Checking command for general cleaning...")
            time.sleep(1)
            if rob.GENERAL_CLEANING:
                print("General cleaning detected!\n")
                time.sleep(1)
                return SUCCEEDED
            else:
                print("No general cleaning detected!\n")
                time.sleep(1)
                return FAILED

        # dusty spot attribute
        elif self.attribute == 'DUSTY_SPOT':
            print("Checking command for dusty spot...")
            time.sleep(1)
            if rob.DUSTY_SPOT:
                print("Dusty spot detected!\n")
                time.sleep(1)
                return SUCCEEDED
            else:
                print("No dusty spot detected!\n")
                time.sleep(1)
                return FAILED



### Decorator Classes ###

# UntilSuccess class
class UntilSuccess(Behavior_Tree_Super):
    # constructor
    def __init__(self, child):
        self.child = child

    # run function
    def run(self):

        while self.child.run() != SUCCEEDED:
            rob.decrease_battery(1)

        return SUCCEEDED

# UntilFailure class
class UntilFailure(Behavior_Tree_Super):
    # constructor
    def __init__(self, child):
        self.child = child

    # run function
    def run(self):

        if self.child.run() != FAILED:
            rob.decrease_battery(1)

        return FAILED

# Negation class
class Negation(Behavior_Tree_Super):
    # constructor
    def __init__(self, child):
        self.child = child

    # run function
    def run(self):
        if self.child.run() == SUCCEEDED:
            return FAILED
        else:
            return SUCCEEDED

### Timer Classes ###

class Timer(Behavior_Tree_Super):
    # constructor
    def __init__(self, child, time_left):
        self.child = child
        self.time_left = time_left
        self.timer_on = True

    # run function
    def run(self):

        # turn timer on for rob
        if not rob.timer_on and self.timer_on:
            rob.timer_on = True
            rob.time_left = self.time_left
            if(rob.time_left == 20):
                print("Starting timer to spot clean for 20 seconds!\n")
            else:
                print("Starting timer to spot clean for 35 seconds!\n")
            time.sleep(1)

        # no time left
        if rob.time_left == 0:
            rob.timer_on = False
            return self.child.run(cleaning=False)

        # some time left
        elif rob.time_left > 0:
            result = self.child.run(cleaning=True)

            if result == FAILED:
                rob.timer_on = False
                print("Failure: Timer ran into some issues...\n")
                return FAILED

            else:
                print("Clean Spot is running. " + str(rob.time_left) + 
                    " seconds left\n")
                time.sleep(0.25)
                rob.time_left -= 1
                rob.decrease_battery(1)
                self.run()

# Task class
class Task(Behavior_Tree_Super):
    #def __init__(self, task): # TASKs: blue pentagon nodes
    #    self.task = task

    def execute(self):
        return 'SUCCEEDED'