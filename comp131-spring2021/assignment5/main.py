### COMP131 Assignment 5: Naive Bayesian Classification   ###
####################### main.py #############################
#### Eli Dow
####
#### driver for Bayesian Networks problem


# imports
import time
import re
import math

# class for Bayesian Classifier
class Bayesian_Classifier:

    # reads data.txt and converts it into a 10-element list where each 
    # element represents an object (list of numbers representing speed)
    def readData(self):
        data = open("/Users/edow1720/Desktop/tufts_cs/comp131-ai/assignment-5/data.txt", "r")
        object_velocities = []

        for line in data:
            object_velocities.append(re.split(",|\n", line))
            object_velocities[len(object_velocities) - 1].pop()
        
        return object_velocities

    # reads PDF.txt and converts it into a 2-element list of lists.
    # the first sub-list represents birds velocity/likelhood of velocity
    # the second sub-list represents aircrafts velocity/likelhood of velocity
    # each element of the sub-list is a number (likelihood (0-1))
    def readPDF(self):
        data = open("/Users/edow1720/Desktop/tufts_cs/comp131-ai/assignment-5/pdf.txt", "r")
        graph_data = []

        for line in data:
            graph_data.append(re.split(",|\n", line))
            graph_data[len(graph_data) - 1].pop()
        
        return graph_data

    # given a number representing velocity, returns a tuple representing the
    # likelihood for that velocity for each posssible object
    def generateLikelihood(self, graph, velocity):

        half = 0
        for i in range(1, len(velocity)):
            if(velocity[i-1] == '.'):
                if(int(velocity[i]) >= 5 and int(velocity[i]) <= 9):
                    half = 0.5
        index = int(2 * (math.floor(float(velocity)) + half))
        
        return (float(graph[0][index]), float(graph[1][index]))
    
    # given a list of velocities for an object, returns a tuple representing the
    # probability of that object for each possible object
    def calcObjProb(self, graph, object_velocity):

        # initializing probability variables
        totalBirdProb = 0
        totalAircraftProb = 0
        num_probs = 0
        avgBirdProb = 0
        avgAircraftProb = 0
        curr_likelihoods = (0,0)
        past_velocity = 0

        # calculating total probability of object in each class
        for i in range(len(object_velocity)):

            # checking to see if value is not NaN
            if(object_velocity[i] != "NaN"):
                curr_likelihoods = self.generateLikelihood(graph, object_velocity[i])
                totalBirdProb += curr_likelihoods[0]
                totalAircraftProb += curr_likelihoods[1]
                num_probs += 1

                # improving classification by increasing probability of aircraft 
                # if speed is over 140 (birds likelihood is 0)
                if(float(object_velocity[i]) > 140):
                    totalAircraftProb += 0.02

                # improving classification by increasing probability of bird 
                # and decreasing probability of aircraft if speed varies by more 
                # than 10 (birds change direciton more often)
                if (i > 0):
                    if(abs(float(past_velocity) - float(object_velocity[i])) > 10):
                        totalBirdProb += 0.01
                        totalAircraftProb -= 0.01

                if(i < (len(object_velocity) - 1)):
                    past_velocity = object_velocity[i]
                
        # calculating average probability of object in each class      
        avgBirdProb = totalBirdProb / num_probs
        avgAircraftProb = totalAircraftProb / num_probs

        return (avgBirdProb,avgAircraftProb)

    # given a tuple of probabilites, reports the results
    def reportProbability(self, probability):
        if probability[0] > probability[1]:
            return "bird"
        return "aircraft"

    # main function of class: classifies each object and returns a list of 
    # strings reporting it
    def classify(self):
 
        # reading data.txt
        print("Reading data.txt...")
        object_velocities = self.readData()
        time.sleep(1)

        # reading PDF.txt
        print("Reading PDF.txt...")
        graph_data = self.readPDF()
        time.sleep(1)

        # finding average probability of object in each class 
        object_probabilities = []
        for i in range(len(object_velocities)):
            object_probabilities.append(self.calcObjProb(graph_data, object_velocities[i]))

        # reporting results
        results = []
        for i in range(len(object_probabilities)):
            results.append("O" + str(i+1) + " = " + str(self.reportProbability(object_probabilities[i])))

        return results
        

# main function
def main():
    simulate = -1

    # main loop for simulation
    while simulate != 2:

        # intro and menu
        print("\nWelcome to the Naive Bayesian Classifier!\n" + 
              "The goal of this program is to calculate and report the " +
              "probability that objects belong to one of two categories: " +
              "birds and aircrafts. The given data for this problem includes" +
              " a PDF of a specified speed for the two categories of objects" +
              ", and a textfile of data representing the the velocity of 10" +
              " unidentified flying objects on 10 different tracks.\n")

        simulate = int(input("Would you like to calculate and report the" +
                            " probability that the 10 unidentified objects " +
                            "are one of the two categories?\n" + 
                            "Enter 1 if yes\n" +
                            "Enter 2 to quit\n\n"))
        # run simulation
        if simulate == 1:
            classifier = Bayesian_Classifier()
            results = classifier.classify()

            # print results
            print("\nResults: ")
            for i in range(10):
                print(results[i])
            time.sleep(3)

        # other entries
        elif simulate != 2:
            print("Please enter 1 or 2 from the menu options")
    
    print("Goodbye")


# call main function
if __name__ == '__main__':
	main()