### COMP131 Assignment 4: Constraint Satisfaction Problem ###
####################### main.py #############################
#### Eli Dow
####
#### driver for CSP problem


# imports
import random
import time
import queue
import copy


# returns easy board defined for assignment
def initialize_easy_board():
    return [[6, -1, 8, 7, -1, 2, 1, -1, -1],
            [4, -1, -1, -1, 1, -1, -1, -1, 2],
            [-1, 2, 5, 4, -1,  -1, -1, -1, -1],
            [7, -1, 1, -1, 8, -1, 4, -1, 5],
            [-1, 8, -1, -1, -1, -1, -1, 7, -1],
            [5, -1, 9, -1, 6, -1, 3, -1, 1],
            [-1, -1, -1, -1, -1, 6, 7, 5, -1],
            [2, -1, -1, -1, 9,  -1, -1, -1, 8],
            [-1, -1, 6, 8, -1, 5, 2, -1, 3]]


# returns evil board defined for assignment
def initialize_hard_board():
    return [[-1, 7, -1, -1, 4, 2, -1, -1, -1],
            [-1, -1, -1, -1, -1, 8, 6, 1, -1],
            [3, 9, -1, -1, -1, -1, -1, -1, 7],
            [-1, -1, -1, -1, -1, 4, -1, -1, 9],
            [-1, -1, 3, -1, -1, -1, 7, -1, -1],
            [5, -1, -1, 1, -1, -1, -1, -1, -1],
            [8, -1, -1, -1, -1, -1, -1, 7, 6],
            [-1, 5, 4, 8, -1, -1, -1, -1, -1],
            [-1, -1, -1, 6, 1, -1, -1, 5, -1]]


# prompts user to enter initial board and returns result
def initialize_user_board():

    # initialize variables
    board = []
    row = []
    
    # beginning prompt
    print("Enter by row.")
    print("Enter #1-9 for each square. If empty square, enter -1\n")

    # get each square
    for i in range(9):
        print("Entering row #" + str(i+1))
        for j in range(9):
            row.append(int(input("Enter col # " + str(j+1) + " ")))
        board.append(row)
        row = []
        print("")

    return board



# Class for Sudoku Board
class Board:

    # constructor
    def __init__(self, board):
        self.board = board
    
    # isEmpty takes in a row number and col number, and returns true if that
    #         square is empty; false otherwise
    def isEmpty(self, row, col):
        if self.board[row][col] == -1:
            return True
        return False

    # getBoard returns the board
    def getBoard(self):
        return self.board

    # setBoard sets the board
    def setBoard(self, board):
        self.board = board
    
    # getSquare takes in a row number and col number, and returns the value in
    #           the square
    def getSquare(self, row, col):
        return self.board[row][col]

    # getRowNums takes in a row number, and returns a list of the numbers in 
    #               that row
    def getRowNums(self, row):
        nums = []
        for i in range(1, 10):
            if i in self.board[row]:
                nums.append(i)
        return nums

    # getColNums takes in a col number, and returns a list of the numbers in 
    #            that col
    def getColNums(self, col):
        nums = []
        for i in range(1, 10):
            for j in range(9):
                if i == self.board[j][col]:
                    nums.append(i)
        return nums


    # get3by3Nums takes in a row number and col number. It returns a list of the
    #             numbers in it's 3 by 3 square
    def get3by3Nums(self, row, col):

        # find top left square in 3 by 3 square 
        start_row_sq = int(row / 3) * 3
        start_col_sq = int(col / 3) * 3
        
        # initialize variables
        nums = []
        exists = False

        # iterate through square
        for i in range(1, 10):
            for j in range(start_row_sq, (start_row_sq + 3)):
                for k in range(start_col_sq, (start_col_sq + 3)):
                    if i == self.board[j][k]:
                        nums.append(i)
                
        return nums

    # printBoard prints the board in a user-friendly format
    def printBoard(self):
        for i in range(9):
            for j in range(9):
                if self.board[i][j] != -1:
                    print(" ", end = "")
                print(str(self.board[i][j]) + " ", end = "")
            print("")
            
            

# Class for CSP algorithm
class Solver:

    # getOptions takes in a board object, a row number, and a col number. It 
    #            returns all the possible numbers that could be at the empty 
    #            square at the given row and given column in the given board
    def getOptions(self, puzzle_board, row, col):

        # possible overall options
        options = [1, 2, 3, 4, 5, 6, 7, 8, 9]

        # getting numbers in rows/cols/3by3
        row_nums = puzzle_board.getRowNums(row)
        col_nums = puzzle_board.getColNums(col)
        sq_nums = puzzle_board.get3by3Nums(row, col)

        # finding options
        for i in range(len(row_nums)):
            if row_nums[i] in options:
                options.remove(row_nums[i])
        for i in range(len(col_nums)):
            if col_nums[i] in options:
                options.remove(col_nums[i])
        for i in range(len(sq_nums)):
            if sq_nums[i] in options:
                options.remove(sq_nums[i])

        return options

    # pickNumber takes in a list of numbers called options. It 
    #            returns one of the numbers (randomly) from that list.
    def pickNumber(self, options):
        
        if len(options) == 1:
            return options[0]
        
        num = options[random.randint(0, len(options) -1)]
        return num

    # hasSolution takes in a board object and returns true if the board 
    #             contains a solution; returns false otherwise
    def hasSolution(self, board):
        for i in range(9):
            for j in range(9):
                if board.isEmpty(i, j):
                    return False
        return True 
            


    # main function simulating algorithm
    def simulateAlgorithm(self, puzzle_board):

        # introduction
        print("\nRunning algorithm...\n")
        queue = []
        solution = "RUNNING"

        while solution == "RUNNING":

            # setting default min_options
            min_options = [1, 2, 3, 4, 5, 6, 7, 8, 9]
            min_square = (-1, -1)
            curr_options = []

            # finding square with minimum options
            for i in range(9):
                for j in range(9):
                    if puzzle_board.isEmpty(i, j):
                        curr_options = self.getOptions(puzzle_board, i, j)

                        # updating square with minimum options
                        if len(curr_options) < len(min_options):
                            min_options = curr_options
                            min_square = (i, j)
                            if len(min_options) == 1: # saves runtime
                                break
                else:
                    continue  # if inner loop didn't break
                break         # if inner loop breaks

            # if board is empty
            if min_options == [1, 2, 3, 4, 5, 6, 7, 8, 9]:
                min_square = (0, 0)
            
            # this is true when we put an incorrect square earlier
            if len(min_options) == 0:

                # board is wrong
                if len(queue) == 0:
                    solution = "FAILURE"
                # get first board on the queue and try from there
                else:
                    puzzle_board.setBoard(queue[0])
                    queue.pop(0)

            else:
                # if square with minimum options has at least two options
                if len(min_options) > 1:
                    queue.append(copy.deepcopy(puzzle_board.getBoard()))

                # update board with that possible option at min_square
                temp_board = puzzle_board.getBoard()
                temp_board[min_square[0]][min_square[1]] = self.pickNumber(min_options)
                puzzle_board = Board(temp_board)

                # checking for solution
                if self.hasSolution(puzzle_board):
                    solution = "SUCCESS"


        if(solution == "FAILURE"):
            return []
        
        return puzzle_board
           


# main function
def main():
    simulate = -1

    # main loop for simulation
    while simulate != 2:

        # intro and menu
        print("\nWelcome to the Sudoku Problem Solver!\n")

        simulate = int(input("Would you like to solve a Sudoku Puzzle?\n" + 
                            "Enter 1 if yes\n" +
                            "Enter 2 to quit\n\n"))
        # run simulation
        if simulate == 1:

            initial_board = []
            board_type = -1

            # main loop for simulation
            while board_type != 1 and board_type !=2 and board_type != 3:

                # board type menu
                board_type = int(input(
                                "Which board would you like to solve?\n" + 
                                "Enter 1 for Easy Board\n" +
                                "Enter 2 for Hard Board\n" + 
                                "Enter 3 for User-Defined Board\n\n"))

                # get board based on type

                if board_type == 1:
                    initial_board = initialize_easy_board()

                elif board_type == 2:
                    initial_board = initialize_hard_board()
                
                elif board_type == 3: 
                    initial_board = initialize_user_board()

                # run simulation
                if len(initial_board) > 0:

                    puzzle_board = Board(initial_board)
                    puzzle_board.printBoard()
                    agent = Solver()
                    results = []

                    start_time = time.time()
                    results = agent.simulateAlgorithm(puzzle_board)
                    end_time = time.time()

                    if results == []:
                        print("The board you gave does not have a solution\n")
                    else:
                        print("The results are ")
                        results.printBoard()
                        print("\nThis took " + str(end_time - start_time) + " seconds!")


                else:
                    print("Please enter 1, 2, or 3 for which board to solve")

        # other entries
        elif simulate != 2:
            print("Please enter 1 or 2 from the menu options")
    
    print("Goodbye")


# call main function
if __name__ == '__main__':
	main()