from _typeshed import Self
from enum import Enum, auto

#Value
class LightColor (Enum) :
    Green = 0
    Orange = 2
    Red = 0

class GatesState (Enum) :
    Open = 0
    GoDown = 5
    Closed = 0
    GoUp = 5    


class Railroad_Crossing_System :
    
    # Input 
    __train_approach = False
    __train_in = False
    __train_leave = False

    # Output
    __blinker_light = False
    __tri_color_light = LightColor.Green
    __gates = GatesState.Open

    #Internal value
    __light_timer_approach = 0
    __gates_timer = 0

    #Function
    def __init__(self):
        print ("Construction of the light")
    
    def train_approach(self,coming):
        self.__train_approach = coming
        if (self.__train_approach == True) :
            self.__tri_color_light = LightColor.Orange
            self.__light_timer_approach = LightColor.Orange.Value


    
    def train_leave(self,coming):
        self.train_leave = coming
    
    def train_in(self,coming):
        self.train_in = coming
        
    




