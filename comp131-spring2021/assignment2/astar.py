### COMP131 Assignment 2: Informed Search ###
############### astar.py ####################
#### Eli Dow
####
#### driver for astar implementation


# imports
import random
import copy
import time
from queue import PriorityQueue

# size of stack
SIZE = 10


# returns the goal stack
def goalStack():
    stack = []
    for i in range(SIZE, 0, -1):
        stack.append(i)
    return stack


# returns a user generated stack for option 1 in the menu
def generateUserStack():
    stack = []
    pancakes_left = goalStack()
    print("\nEnter stack in reverse order (bottom to top)")

    # keep adding pancakes until we have none left from possible pancakes
    while len(stack) != SIZE:
        print("Current stack: " + str(stack))
        print("Numbers left: " + str(pancakes_left))
        choice = int(input(
                  "Enter a number value between 1 and " + str(SIZE) +
                  " that you haven't used\n"))
        if choice in pancakes_left:
            stack.append(choice)
            pancakes_left.remove(choice)
        else:
            print("Not a valid choice.")
    
    return stack
    

# returns a randomly generated stack for option 2 in the menu
def generateRandomStack():
    stack = goalStack()
    random.shuffle(stack) # shuffles elements in random order
    return stack


# Class for Pancake Stack
class Stack:

    # constructor
    def __init__(self, pancake_stack):
        self.pancake_stack = pancake_stack
    
    def __lt__(self, other):
        if(self.pancake_stack[0] > other.pancake_stack[0]):
            return True
        else:
            return False
    
    # accessor function for pancake_stack
    def getStack(self):
        return self.pancake_stack

    # returns true if pancake_stack = goal state, returns false otherwise
    def compareToGoal(self):
        if self.pancake_stack == goalStack():
            return True
        return False

    # successor function: 
    #                   Given an index of a stack (index), flip 
    #                   reverses the elements from that index to the top of the 
    #                   stack, then returns the resulting list
    def flip(self, flip_index):
        stack = copy.copy(self.pancake_stack)
        if flip_index == 0:
            stack.reverse()
            return stack
        else:
            flipped = stack[flip_index:]
            flipped.reverse()
            new_stack = stack[0:flip_index]
            new_stack.extend(flipped)
            return new_stack

    # heuristic funciton/forward cost:
    #         num_of_gaps() returns the number of pancakes whose neighbor on top
    #         of it (to the right of it) is not the next smallest 
    #         pancake (values differ more than 1). It also adds 1 
    #         to a stack that doesn't have it's largest pancake on 
    #         the bottom of the stack.
    def num_of_gaps(self):
        gaps = 0
        for i in range(SIZE - 1):
            if self.pancake_stack[i] != self.pancake_stack[i + 1] + 1:
                gaps += 1
        if(self.pancake_stack[0] != SIZE):
            gaps += 1
        return gaps


# Class for AStar Algorithm
class AStarAlgorithm:

    # simulates astar algorithm
    def Astar(self, pancake_stack):

        # initialize stack and priority queue
        stack = Stack(pancake_stack)
        priority_q = PriorityQueue()
        priority_q.put((stack.num_of_gaps(), stack, []))

        # while no success or failure
        while True:
             
            # if queue is empty, return FAILURE 
            if priority_q.empty():
                return "FAILURE"
            
            # access front of queue and its components
            current_node = priority_q.get()
            current_total_cost = current_node[0]
            current_stack = current_node[1]
            past_flips = current_node[2]

            # if list == goal, return SUCCESS 
            if current_stack.compareToGoal():
                print("We have reached the goal stack: " + 
                    str(current_stack.getStack()))
                print("Minumum Total Cost: " + str(current_total_cost))
                print("Flips to get solution: " + str(past_flips))
                return "SUCCESS"
            
            # try all possible flips
            for i in range(SIZE - 1):
                # if stack wasn't the previous flip, put it in
                # did not necessarily check for duplicates and replace because
                # you can only access the front in a priority queue
                if len(past_flips) == 0 or i != past_flips[len(past_flips) - 1]:
                    new_stack = Stack(current_stack.flip(i))
                    new_total_cost = 1 + len(past_flips) + new_stack.num_of_gaps()
                    priority_q.put((new_total_cost, 
                        new_stack, past_flips + [i]))
                

# main function
def main():
    pancake_option = -1

    # main loop for simulation
    while pancake_option != 3:
        initial_stack = []
        #pancake_stack = []

        # intro and menu
        print("\nWelcome to the Pancake Problem (with Astar)!\n")

        pancake_option = int(input("Select an option for simulating the " +
                            "Pancake Problem:\n" + 
                            "Enter 1 if you would like to run the pancake " + 
                            "problem with user entered data\n" +
                            "Enter 2 if you would like to run the pancake " +
                            "problem with randomly generated data\n" +
                            "Enter 3 to quit\n\n"))

        #user inputted data or randomly generated data
        if pancake_option == 1 or pancake_option == 2:
            if pancake_option == 1:
                initial_stack = generateUserStack()
            else:
                initial_stack = generateRandomStack()
            
            # print initial stack and record time
            print("\nInitial Stack: " + str(initial_stack) + "\n")
            start = time.time()

            # run astar algorithm
            agent = AStarAlgorithm()
            results = agent.Astar(initial_stack)

            # record time
            end = time.time()
            print("This simulation ran in " +
                str(round((end - start), 2)) + " seconds")
            print("The result: " + results)

        # other entries
        elif pancake_option != 3:
            print("Please enter 1, 2, or 3 from the menu options")
    
    print("Goodbye")


# call main function
if __name__ == '__main__':
	main()