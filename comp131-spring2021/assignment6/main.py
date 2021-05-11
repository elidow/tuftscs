##### COMP131 Assignment 6: Artificial Neural Networks  #####
####################### main.py #############################
#### Eli Dow
####
#### driver for Artificial Neural Networks Problem


# imports
from network import Neural_Network

import time  

# main function
def main():
    simulate = -1

    # main loop for simulation
    while simulate != 2:

        # intro and menu
        print("\nArtificial Neural Networks:\n" + 
              "A gardener of the Garden of Heavens is given the task to " + 
              "straighten up a mess because a prankster has mixed up all the " +
              "Iris plants and removed their tags. There were three benches " + 
              "in the greenhouse, with one type of Iris on each: Iris Setosa," +
              " Iris Versicolour, Iris Virginica.\n\n This Neural Network " + 
              "program will train an ANN by reading Fisher’s Iris Database " +
              "that contains three classes of 50 instances of Iris Plants." +
              " Then, the gardener will be asked to provide all necessary " +
              "information and the ANN will classify the plants based on " +
              "user input.")

        simulate = int(input("Would you like to classify the plants?\n" + 
                            "Enter 1 if yes\n" +
                            "Enter 2 to quit\n\n"))
        # run simulation
        if simulate == 1:
            ANN = Neural_Network()
            ANN.train()
            results = ANN.classify()

            # print results
            print("\nResults: ")
            for i in range(len(results)):
                print("Bench " + str(i+1))
                for j in range(len(results[i])):
                    print(results[i][j])
            time.sleep(5)


            # *** Solution (is accurate at least 95%)
            # Bench 1
            # Iris-setosa belongs to [5.0, 3.4, 1.4, 0.2]
            # Iris-versicolor belongs to [5.9, 2.7, 4.2, 1.3]
            # Iris-virginica belongs to [6.6, 3.0, 5.5, 2.0]
            # Bench 2
            # Iris-versicolor belongs to [6.0, 2.8, 4.3, 1.4]
            # Iris-virginica belongs to [6.5, 2.9, 5.6, 2.1]
            # Iris-setosa belongs to [5.1, 3.5, 1.5, 0.3]
            # Bench 3
            # Iris-virginica belongs to [6.6, 2.9, 5.5, 2.1]
            # Iris-setosa belongs to [5.0, 3.5, 1.4, 0.3]
            # Iris-versicolor belongs to [5.9, 2.8, 4.2, 1.4]


        # other entries
        elif simulate != 2:
            print("Please enter 1 or 2 from the menu options")
    
    print("Goodbye")


# call main function
if __name__ == '__main__':
	main()