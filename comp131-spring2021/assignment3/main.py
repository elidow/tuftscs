### COMP131 Assignment 3: Informed Search ###
############### main.py #####################
#### Eli Dow
####
#### driver for genetic algorithm implementation


# imports
import random
import time

# important figures

# set
SET_SIZE = 15

# boxes
MIN_WEIGHT = 5
MAX_WEIGHT = 25
MIN_VALUE = 1
MAX_VALUE = 10

# backpack
MAX_TOTAL_WEIGHT = 250
NUM_BOXES= 10

# population
POP_NUM = 12


def maxGoal():
    return MAX_VALUE * NUM_BOXES

# Class for Box
class Box:

    # constructor
    def __init__(self, weight, value):
        self.weight = weight
        self.value = value
    
    # get weight of box
    def getWeight(self):
        return self.weight
    
    # get value of box
    def getValue(self):
        return self.value

    # set weight of box
    def setWeight(self, weight):
        self.weight = weight
    
    # set value of box
    def setValue(self, value):
        self.value = value

    # print box in easy to read format
    def printBox(self):
        print("Box: weight of " + str(self.weight) + ", value of " + str(self.value))


# Class for Backpack
class Backpack:

    # constructor
    def __init__(self, boxes, phenotype, max_weight):
        self.boxes = boxes
        self.phenotype = phenotype
        self.max_weight = max_weight
    
    # get boxes
    def getBoxes(self):
        return self.boxes

    # get phenotype (genetic representation)
    def getPhenotype(self):
        return self.phenotype
    
    # get max weight
    def getMaxWeight(self):
        return self.max_weight

    # set boxes
    def setBoxes(self, boxes):
        self.boxes = boxes
    
    # set phenotype (genetic representation)
    def setPhenotype(self, phenotype):
        self.phenotype = phenotype

    # returns number of unique boxes in representation (perfect = NUM_BOXES)
    def onesInPhenotype(self):
        ones = 0
        for i in range(len(self.phenotype)):
            if self.phenotype[i] == 1:
                ones += 1
        return ones
    
    # print backpack in easy to read format
    def printBackpack(self):
        print("Backpack:")
        for i in range(len(self.boxes)):
            self.boxes[i].printBox()
        print("Phenotype: ", end = "")
        print(self.phenotype)
        print("")

    # returns total weight of box
    def getTotalWeight(self):
        total = 0
        for i in range (len(self.boxes)):
            total += self.boxes[i].getWeight()
        return total

    def getTotalValue(self):
        total = 0
        for i in range (len(self.boxes)):
            total += self.boxes[i].getValue()
        return total
    
    # for an individual box: 
    #     min score is 5 * MIN_VALUE - MAX_WEIGHT
    #     max score is 5 * MAX_VALUE - MIN_WEIGHT
    # for an backpack: 
    #     min score is NUM_BOXES * (5 * MIN_VALUE - MAX_WEIGHT) roughly
    #     max score is NUM_BOXES * (5 * MAX_VALUE - MIN_WEIGHT) roughly
    # Ex:
    #     NUM_BOXES = 10, MIN_VALUE = 1, MAX_VALUE = 10, MIN_WEIGHT = 5, MAX_WEIGHT = 25
    #     min score for box is -200 roughly
    #     max score for box is 45, 450 overall roughly
    def fitnessFunction(self):
        total = 0
        for i in range (len(self.boxes)):
            total += (5 * self.boxes[i].getValue() - self.boxes[i].getWeight())
        if self.getTotalWeight() > self.max_weight:
            total -= 500
        return total


# Class for Box
class Genetic_Algorithm:

    def generateInitialPop(self, boxes):
        backpacks = []

        # populate population
        for i in range(POP_NUM):
            print("Generating Backpack #" + str(i+1))

            # initialize variables
            temp = []
            not_used = []
            phenotype = []

            for j in range(SET_SIZE):
                not_used.append(j)
                phenotype.append(0)

            # populate boxes array for backpack
            while len(temp) != NUM_BOXES:
                num = random.randint(0,SET_SIZE - 1)
                if num in not_used: 
                    temp.append(boxes[num])
                    not_used.remove(num)
                    phenotype[num] = 1

            # initialize backpack object and print backpacks
            backpacks.append(Backpack(temp, phenotype, MAX_TOTAL_WEIGHT))
            backpacks[i].printBackpack()

            time.sleep(0.8)
        
        print("Simulating population now")
        time.sleep(0.5)
        print(3)
        time.sleep(1)
        print(2)
        time.sleep(1)
        print(1)
        time.sleep(1)
        print("GO!")
        return backpacks

    # returns the population index of the backpack with the lowest fitness function
    def indexOfWeakest(self, population):
        min_num_score = 450
        min_index = -1
        for i in range(len(population)):
            curr_score = population[i].fitnessFunction()
            if curr_score < min_num_score:
                min_num_score = curr_score
                min_index = i
        return min_index

    # culls the population by 50%: returns population half with highest fitness
    def cullPopulation(self, population):

        # initializing variables
        fittest_half = []
        min_num_score = 50
        min_index = -1

        # iterating through population
        for i in range(POP_NUM):
            num_score = population[i].fitnessFunction()

            if len(fittest_half) < 6:
                fittest_half.append(population[i])

            # booting backpack with least fitness score
            else:
                min_index = self.indexOfWeakest(fittest_half)
                min_num_score = fittest_half[min_index].fitnessFunction()
                if num_score > min_num_score:
                    fittest_half[min_index] = population[i]
                
        return fittest_half

    # conducting crossover with two backpacks
    def crossover(self, backpack1, backpack2, boxes, point):
        # initializing variables
        child_backpack = []
        boxes1 = backpack1.getBoxes()
        boxes2 = backpack2.getBoxes()
        phenotype = []

        # crossover: updating boxes
        for i in range(NUM_BOXES):
            if i < point:
                child_backpack.append(boxes1[i])
            else:
                child_backpack.append(boxes2[i])
        
        for i in range(SET_SIZE):
            phenotype.append(0)
        
        # updating phenotype from crossover
        for i in range(len(child_backpack)):
            for j in range(len(boxes)):
                if child_backpack[i].getWeight() == boxes[j].getWeight() and child_backpack[i].getValue() == boxes[j].getValue():
                    phenotype[j] = 1

        return Backpack(child_backpack, phenotype, MAX_TOTAL_WEIGHT)

    # execute mutation
    def mutate(self, backpack, original_set):
        # initialize variables
        boxes = backpack.getBoxes()
        phenotype = backpack.getPhenotype()
    
        pairs = []
        repeat_pairs = []
        repeats = 0

        # find unique pairs and repeats
        for i in range(NUM_BOXES):
            if (boxes[i].getWeight(), boxes[i].getValue()) not in pairs:
                pairs.append((boxes[i].getWeight(), boxes[i].getValue()))
            else:
                repeats += 1
                repeat_pairs.append((boxes[i].getWeight(), boxes[i].getValue()))

        # remove repeats
        index = 0
        while repeats != 0:
            if (boxes[index].getWeight(), boxes[index].getValue()) in repeat_pairs:
                boxes.remove(boxes[index])
                repeats -= 1
            else:
                index += 1

        # add new boxes so that there are 10 in backpack
        while len(boxes) != 10:
            index = random.randint(0, SET_SIZE - 1)
            if (original_set[index].getWeight(), original_set[index].getValue()) not in pairs:
                boxes.append(original_set[index])
                pairs.append((original_set[index].getWeight(), original_set[index].getValue()))
                phenotype[index] = 1
        
        backpack.setBoxes(boxes)
        backpack.setPhenotype(phenotype)
        

    # main function simulating genetic algorithm
    def simulateGeneticAlgorithm(self, original_set):

        print("\nGenerating backpacks for initial population")
        initial_pop = self.generateInitialPop(original_set)

        soln_val = 0
        start_time = time.time()
        solution = []
        point1 = int(NUM_BOXES / 3)
        point2 = 2 * int(NUM_BOXES / 3)

        # simulating for 0.1 seconds
        while (time.time() - start_time) < 0.1:

            # find fittest indiviuals and initialize new population
            fittest_half = self.cullPopulation(initial_pop)
            new_population = []

            # crossover
            for i in range(len(fittest_half)):
                if i % 2 == 0:
                    new_population.append(self.crossover(fittest_half[i], fittest_half[i+1], original_set, point1))
                    new_population.append(self.crossover(fittest_half[i], fittest_half[i+1], original_set, point2))
                else:
                    new_population.append(self.crossover(fittest_half[i], fittest_half[i-1], original_set, point1))
                    new_population.append(self.crossover(fittest_half[i], fittest_half[i-1], original_set, point2))

            # mutation
            for i in range(len(new_population)):
                if new_population[i].onesInPhenotype() != 10:
                    self.mutate(new_population[i], original_set)

            # updating solution
            for i in range(len(new_population)):
                curr_val = new_population[i].getTotalValue()
                if curr_val > soln_val:
                    print(str(curr_val) + ">" + str(soln_val))
                    solution = new_population[i]
                    soln_val = curr_val
            
            if(soln_val > maxGoal()):
                break

            # setting new initial population for next round
            initial_pop = new_population
        
        print("\nFOUND A SOLUTION:")
        return solution


# main function
def main():
    simulate = -1

    # main loop for simulation
    while simulate != 2:

        # intro and menu
        print("\nWelcome to the Knapsack Problem!\n")

        simulate = int(input("Would you like to simulate the problem?\n" + 
                            "Enter 1 if yes\n" +
                            "Enter 2 to quit\n\n"))
        # run simulation
        if simulate == 1:

            # initializing variables
            original_set = []
            pairs = []
            weight = 0
            value = 0
            index = 0

            print("Generating original set...")
            while len(original_set) != SET_SIZE:
                print("Generating Box #" + str(index+1))
                weight = random.randint(MIN_WEIGHT, MAX_WEIGHT)
                value = random.randint(MIN_VALUE, MAX_VALUE)
                if (weight, value) not in pairs:
                    original_set.append(Box(weight, value))
                    pairs.append((weight, value))
                    original_set[index].printBox()
                    index += 1
                else:
                    print("REPEAT: " + str(weight) + " " + str(value))
                time.sleep(0.4)

            print("Printing out initial population and running simulation")
            time.sleep(1.5)
            agent = Genetic_Algorithm()
            results = agent.simulateGeneticAlgorithm(original_set)

            results.printBackpack()
            print("Total weight: " + str(results.getTotalWeight()))
            print("Total value: " + str(results.getTotalValue()))

        # other entries
        elif simulate != 2:
            print("Please enter 1 or 2 from the menu options")
    
    print("Goodbye")


# call main function
if __name__ == '__main__':
	main()