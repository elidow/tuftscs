############# COMP131 Assignment 1 #############
################# tasks file ###################
#### Eli Dow
####
#### contains all classes for tasks

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
def set_rob_for_tasks(blackboard):
    global rob 
    rob = blackboard

# Task_Super superclass
class Task_Super():

    # run function
    def run(self):
        return SUCCEEDED

# Find_Home Class
class Find_Home(Task_Super):

    # run function
    def run(self):

        # Target: store home path
        print("Finding Home...")        
        rob.HOME_PATH = input("Enter Rob's path to the " +
                                "docking station (string describing path).\n")
        time.sleep(1)

        # only false if empty
        if not rob.HOME_PATH:
            print("Failure! Couldn't find home: No path specified")
            time.sleep(1)
            return FAILED
        else:
            print("Success! Storing path to home: " + rob.HOME_PATH)
            time.sleep(1)
            return SUCCEEDED

# Go_Home Class
class Go_Home(Task_Super):

    # run function
    def run(self):
  
        # Target: recall home path (rob.HOME_PATH)
        print("Going Home...")
        time.sleep(1)

        # only false if empty
        if not rob.HOME_PATH:
            print("Failure! Couldn't go home: Directions not clear")
            time.sleep(1)
            return FAILED
        else:
            print("Success! Arrived home from path: " + rob.HOME_PATH)
            time.sleep(1)
            return SUCCEEDED

# Dock Class
class Dock(Task_Super):

    # run function
    def run(self):

        print("Docking...")
        time.sleep(1)

        # docking is always a success
        rob.BATTERY_LEVEL = 100
        print("Success! Battery charged to 100")
        time.sleep(3)

        return SUCCEEDED

# Clean_Spot Class
class Clean_Spot(Task_Super):

    # run function
    def run(self, cleaning):

        print("Cleaning Spot...")

        if cleaning:
            print("Still more to clean...")
            return RUNNING

        # always true
        clean_spot = True
        if not clean_spot:
            print("Failure! Spot could not be cleaned")
            return FAILED
        else:
            print("Success! Spot was cleaned")
            return SUCCEEDED

# Done_Spot Class
class Done_Spot(Task_Super):

    # run function
    def run(self):

        # Target: clear spot
        rob.SPOT_CLEANING = False

        print("Done Spot: Success")
        time.sleep(3)

        return SUCCEEDED

# Clean_Floor Class
class Clean_Floor(Task_Super):

    # run function
    def run(self):

        # clean_floor suceeds when >= 8
        print("Cleaning Floor...")
        clean_floor = random.randint(0, 10)
        time.sleep(1)

        if clean_floor < 8:
            print("Unsuccessful! Floor must still be cleaned...\n")
            return FAILED
        else:
            print("Success! Floor was cleaned")
            return SUCCEEDED

# Done_General Class
class Done_General(Task_Super):

    # run function
    def run(self):

        # Target: clear general
        rob.spot = False

        print("Success! Done with general cleaning")
        time.sleep(3)

        return SUCCEEDED

# Do_Nothing Class
class Do_Nothing(Task_Super):

    # run function
    def run(self):

        print("Successfully did nothing!\n")
        time.sleep(3)

        return SUCCEEDED