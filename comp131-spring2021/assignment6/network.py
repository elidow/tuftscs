##### COMP131 Assignment 6: Artificial Neural Networks  #####
####################### neural.py #############################
#### Eli Dow
####
#### neural network file for Artificial Neural Networks Problem


# imports
import time
import re
import math
import random
from itertools import chain

# important values
BENCHES = 3
FLOWER_TYPES = 3
FT_DATA = 50

# class for Neural Network
class Neural_Network:

    # constructor:
    # 
    # Nueral Network has 3 layers: input layer of 4 neurons (one for each 
    # measurement), hidden layer of 4 neurons, and 3 neurons in output layer.
    #
    # weights are in 2D lists for weights between neurons, weights are in 1D 
    # lists for weights in between biases and neurons
    def __init__(self):

        # number of neurons in each layer
        self.num_inputs = 4
        self.num_hidden = 4
        self.num_outputs = 3

        # current output activations
        self.hidden_neurons = [0, 0, 0, 0]
        self.output_neurons = [0, 0, 0]
        self.bias = 1


        # all weights, randomly generated
        # Note: all of these are formated so list[i][j] means from i to j

        # for weights between inputs and hidden layer
        iHWeights = []
        for i in range(self.num_inputs):
            iHWeights.append([])
            for j in range(self.num_hidden):
                iHWeights[i].append(round(random.uniform(-1.0,1.0), 1))

        self.iHWeights = iHWeights

        # for weights between hidden layer and outputs
        hOWeights = []
        for i in range(self.num_hidden):
            hOWeights.append([])
            for j in range(self.num_outputs):
                hOWeights[i].append(round(random.uniform(-1.0,1.0), 1))
        self.hOWeights = hOWeights

        # for weights between bias and hidden layer
        bHWeights = []
        for i in range(self.num_hidden):
            bHWeights.append(round(random.uniform(-1.0,1.0), 1))
        self.bHWeights = bHWeights

        # for weights between bias and output layer
        bOWeights = []
        for i in range(self.num_outputs):
            bOWeights.append(round(random.uniform(-1.0,1.0), 1))
        self.bOWeights = bOWeights

        # learning rate
        self.learning_rate = 0.1



    # reads data.txt and converts it into a 150-element list where each 
    # element represents an instance (4 element list of 4 float measurements)
    def readData(self):

        # initializing data
        data = open("/Users/edow1720/Desktop/tufts_cs/comp131-ai/assignment-6/data.txt", "r")
        iris_data = []

        # reading through file
        for line in data:
            iris_data.append(re.split(",|\n", line))
            iris_data[len(iris_data) - 1].pop()

        # creating list of instances, each with 4 measurements
        for i in range(len(iris_data)):
            for j in range(0, (len(iris_data[i]) - 1)):
                iris_data[i][j] = float(iris_data[i][j])
            iris_data[i].pop()

        return iris_data


    # normalizes input so that it is a value between 0 and 1
    def normalize(self, item):
        num = round((item / 8.0), 2)
        return num


    # calculate the potential of all hidden neurons
    def calculateHiddenPotential(self, iris):
        total_p = [0, 0, 0, 0]
        for t in range(len(total_p)):
            for i in range(len(iris)):
                total_p[t] += self.normalize(iris[i]) * self.iHWeights[i][t]
            total_p[t] += self.bHWeights[t]
            total_p[t] = round(total_p[t], 3)

        return total_p


    # calculate the potential of all output neurons
    def calculateOutputPotential(self):
        total_p = [0, 0, 0]
        for t in range(len(total_p)):
            for i in range(self.num_hidden):
                total_p[t] += self.hidden_neurons[i] * self.hOWeights[i][t]
            total_p[t] += self.bOWeights[t]
            total_p[t] = round(total_p[t], 3)

        return total_p
        

    # activation function for the potential of the neural network
    # used sigmoid: O(Pi) = 1 / (1 + e^(Pi))
    def activationFunction(self, potential):
        exponent = -1 * potential
        activation = round((1 / (1 + math.exp(exponent))), 3)
        return activation


    # calculating error for each output neuron, returns list of those errors
    # According to slides: Delta(Pi) = O(Pi) * (1 - O(Pi)) * (1 - O(Pi))
    def calculateOutputDelta(self):
        deltas = []
        for i in range(self.num_outputs):
            deltas.append(round((self.output_neurons[i] * 
                (1 - self.output_neurons[i]) * 
                    (1 - self.output_neurons[i])), 3))
        return deltas


    # calculating error for each hidden neuron, returns list of those errors
    # According to slides: Delta(Pi) = O(Pi) * (1 - O(Pi)) * 
    #           (summation of ((weight btwn hidden and output) * Output O(Pi)))
    def calculateHiddenDelta(self, output_deltas):
        deltas = []

        for i in range(self.num_hidden):
            temp = 0
            for j in range(self.num_outputs):
                temp += self.hOWeights[i][j] * output_deltas[j]

            deltas.append(round((self.hidden_neurons[i] * (1 - self.hidden_neurons[i]) * temp), 3))
        
        return deltas


    # updating weights between inputs and hidden layer
    # Change in weight_ij = N * O(Pi) * Delta(Pj)
    def updateiHWeights(self, iris, hidden_deltas):
        for i in range(len(self.iHWeights)):
            for j in range(len(self.iHWeights[i])):
                weight_change = self.learning_rate * iris[i] * hidden_deltas[j]
                if(weight_change > 0.0009):
                    self.iHWeights[i][j] = round((self.iHWeights[i][j] + weight_change), 3)
        return


    # updating weights between hidden layer and outputs  
    # Change in weight_ij = N * O(Pi) * Delta(Pj) 
    def updatehOWeights(self, output_deltas):
        for i in range(len(self.hOWeights)):
            for j in range(len(self.hOWeights[i])):
                weight_change = self.learning_rate * output_deltas[j] * self.hidden_neurons[i]
                if(weight_change > 0.0009):
                    self.hOWeights[i][j] = round((self.hOWeights[i][j] + weight_change), 3)
        return


    # updating weights between bias and hidden layer
    # Change in weight_ij = N * O(Pi) * Delta(Pj)
    def updatebHWeights(self, hidden_deltas):
        for i in range(len(self.bHWeights)):
            weight_change = self.learning_rate * self.bHWeights[i] * hidden_deltas[i]
            if(weight_change > 0.0009):
                self.bHWeights[i] = round((self.bHWeights[i] + weight_change), 3)
        return
    

    # updating weights between bias and output layer
    # Change in weight_ij = N * O(Pi) * Delta(Pj)
    def updatebOWeights(self, output_deltas):
        for i in range(len(self.bOWeights)):
            weight_change = self.learning_rate * self.bOWeights[i] * output_deltas[i]
            if(weight_change > 0.0009):
                self.bOWeights[i] = round((self.bOWeights[i] + weight_change), 3)
        return


    # forward and backward propagation for the neural network
    def Propagation(self, iris_data):

        # reading in data one at a time
        for i in range(len(iris_data)):

            ### forward propagation ###

            # calculating potentials, then activation for each hidden neuron
            total_p = self.calculateHiddenPotential(iris_data[i])
            for j in range(len(total_p)):
                self.hidden_neurons[j] = self.activationFunction(total_p[j])

            # calculating potentials, then activation for each output neuron
            total_p = self.calculateOutputPotential()
            for j in range(len(total_p)):
                self.output_neurons[j] = self.activationFunction(total_p[j])

            # backward propagation
            
            # calculating error for each neuron (delta)
            output_deltas = self.calculateOutputDelta()
            hidden_deltas = self.calculateHiddenDelta(output_deltas)

            # calculating rate of change, and updating weights
            self.updateiHWeights(iris_data[i], hidden_deltas)
            self.updatehOWeights(output_deltas)
            self.updatebHWeights(hidden_deltas)
            self.updatebOWeights(output_deltas)

        return

############## main functions for training and classifying ###############

    # main function for training ANN
    def train(self):
 
        # reading data.txt
        print("Training ANN by reading data.txt...")
        iris_data = self.readData()
        time.sleep(3)

        # forward and backward propagation
        self.Propagation(iris_data)

        print("Done training ANN\n")
        time.sleep(1)

        return


    # main function for ANN classifying new inputs
    def classify(self):
        
        # these are the farmer's inputs
        # Note: one type of flower on each bench
        # *** Solution in main.py comments where results are printed ***

        benches = [[[5.0, 3.4, 1.4, 0.2], [5.9, 2.7, 4.2, 1.3], [6.6, 3.0, 5.5, 2.0]],
                   [[6.0, 2.8, 4.3, 1.4], [6.5, 2.9, 5.6, 2.1], [5.1, 3.5, 1.5, 0.3]],
                   [[6.6, 2.9, 5.5, 2.1], [5.0, 3.5, 1.4, 0.3], [5.9, 2.8, 4.2, 1.4]]]

        # outputing farmer's inputs
        print("Farmer wants to classify the following plants:")
        for i in range(BENCHES):
            print("Bench " + str(i+1))
            for j in range(len(benches[i])):
                print(benches[i][j])

        print("Wait 5 seconds for the ANN to classify each plant...")
        time.sleep(5)

        # initializing results
        results = []
        
        # using ANN to classify
        for i in range(BENCHES):
            max_output = []
            for j in range(len(benches[i])):
                temp = []
                temp.append(benches[i][j])
                self.Propagation(temp)
                max_output.append(max(self.output_neurons))
            
            results.append([])

          
            for j in range(len(max_output)):
                if max_output[j] == min(max_output):
                    results[i].append("Iris-setosa belongs to " + str(benches[i][j]))
                elif max_output[j] == max(max_output):
                    results[i].append("Iris-virginica belongs to " + str(benches[i][j]))
                else:
                    results[i].append("Iris-versicolor belongs to " + str(benches[i][j]))

        return results



############################ functions for testing ############################

    # reads in iris_data and returns the averges of the data in 3 by 4 list
    def calcAverage(self, iris_data):
        iris_avg = []
        sepal_l, sepal_w, petal_l, petal_w = [], [], [], []

        for i in range(FLOWER_TYPES):
            sepal_l.append(0)
            sepal_w.append(0)
            petal_l.append(0)
            petal_w.append(0)

        for i in range(len(iris_data)):
            sepal_l[i // FT_DATA] += float(iris_data[i][0])
            sepal_w[i // FT_DATA] += float(iris_data[i][1])
            petal_l[i // FT_DATA] += float(iris_data[i][2])
            petal_w[i // FT_DATA] += float(iris_data[i][3])

        for i in range(len(sepal_l)):
            sepal_l[i] /= FT_DATA
            sepal_w[i] /= FT_DATA
            petal_l[i] /= FT_DATA
            petal_w[i] /= FT_DATA
            iris_avg.append([round(sepal_l[i], 2), round(sepal_w[i], 2),
                              round(petal_l[i], 2), round(petal_w[i], 2)])
       
        return iris_avg

    # prints all instance variables
    def printAllInstances(self):
        print("Nums for inputs, hidden, outputs")
        print(self.num_inputs)
        print(self.num_hidden)
        print(self.num_outputs)

        print("Vals: hidden, output, bias")
        print(self.hidden_neurons)
        print(self.output_neurons)
        print(self.bias)

        print("Weights: IH, HO, BH, BO")
        print(self.iHWeights)
        print(self.hOWeights)
        print(self.bHWeights)
        print(self.bOWeights)

        print("Learning rate")
        print(self.learning_rate)

        