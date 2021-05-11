############# COMP131 Assignment 1 #############
############## btree file ##############
#### Eli Dow
####
#### simulates the entire behabior tree

#imports

# from general_nodes
from general_nodes import Behavior_Tree_Super
from general_nodes import Selection
from general_nodes import Priority
from general_nodes import Sequence
from general_nodes import Conditions
from general_nodes import UntilSuccess
from general_nodes import UntilFailure
from general_nodes import Negation
from general_nodes import Timer
from general_nodes import Task

# from tasks
from tasks import Task_Super
from tasks import Find_Home
from tasks import Go_Home
from tasks import Dock
from tasks import Clean_Spot
from tasks import Done_Spot
from tasks import Clean_Floor
from tasks import Done_General
from tasks import Do_Nothing



# run_simulation function runs the whole behavior tree
class Behavior_Tree:

    # run function: executes function for task, condition, decorator, ect.
    def run(self):

        # running tree
        tree = Priority(children=[
            Sequence(children=[
                Conditions(attribute='BATTERY_LEVEL'),Find_Home(), Go_Home(), 
                    Dock()]),
            Selection(children=[
                Sequence(children=[
                    Conditions(attribute='SPOT_CLEANING'), Timer(
                    child=Clean_Spot(), time_left=20), Done_Spot()]),
                Sequence(children=[
                    Conditions(attribute='GENERAL_CLEANING'),
                    Sequence(children=[
                        Priority(children=[
                            Sequence(children=[
                                Conditions(attribute='DUSTY_SPOT'),
                                Timer(child=Clean_Spot(), time_left=35)]),
                            UntilSuccess(child=Clean_Floor())]),
                        Done_General()])])]),
            Do_Nothing()]).run()

        return tree

