############# COMP131 Assignment 1 #############
################# main file ####################
#### Eli Dow
####
#### driver for program

# imports
import random
from vaccum import initialize
from btree import Behavior_Tree

# requests user data and returns populated blackboard
def request_user_data(robot_data):
    
    robot_data['BATTERY_LEVEL'] = int(input("Enter Rob's battery life.\n"))
                
    robot_data['SPOT_CLEANING'] = bool(int(input("Do you want Rob to spot " + 
            "clean? Enter 1 for yes, 0 for no.\n")))

    robot_data['GENERAL_CLEANING'] = bool(int(input("Do you want Rob to do a " + 
                        "general clean? Enter 1 for yes, 0 for no.\n")))

    robot_data['DUSTY_SPOT'] = bool(int(input("Is there a dusty spot?\n")))

    robot_data['HOME_PATH'] = ""

    print("")
    return robot_data

# generates random data and returns populated blackboard
def generate_data(robot_data):
    
    robot_data['BATTERY_LEVEL'] = random.randint(0, 100)
                
    robot_data['SPOT_CLEANING'] = bool(random.randint(0, 1))

    robot_data['GENERAL_CLEANING'] = bool(random.randint(0, 1))

    dusty_decider = random.randint(0, 10)
    robot_data['DUSTY_SPOT'] = bool(dusty_decider >= 8)

    '''paths = ["Over the river and through the woods!", "To infinity and beyond!",
            "Off to Hogwarts!", "Off to where the wild things are!", 
            "Travelling behind the couch"]

    robot_data['HOME_PATH'] = "paths[random.randint(0, 4)]"'''
    robot_data['HOME_PATH'] = ""

    return robot_data

# main function
def main():
    data_option = -1

    # main loop for simulation
    while data_option != 3:
        robot_data = {}
        completed_tree = False

        # intro and menu
        print("\nWelcome to our Vacuum Cleaning Simulation!\n")
        print("I am Rob the robot! I'll be doing all the dirty work today.\n")

        data_option = int(input("Would you like to run the tree?:\n" + 
                            "Press 1 if you would like to run the tree with " + 
                            "user entered data\n" +
                            "Press 2 if you would like to run the tree with " +
                            "randomly generated data\n" +
                            "Press 3 to quit\n\n"))

        #user inputted data or randomly generated data
        if data_option == 1 or data_option == 2:
            if data_option == 1:
                robot_data = request_user_data(robot_data)
            else:
                robot_data = generate_data(robot_data)

            # initialize object
            initialize(robot_data)
            # initialize tree
            bt = Behavior_Tree()
            # run simulation
            while not completed_tree:
                completed_tree = bt.run()

        # other entries
        elif data_option != 3:
            print("Please enter 1, 2, or 3 from the menu options")
    
    print("Goodbye")


# call main function
if __name__ == '__main__':
	main()