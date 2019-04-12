# simulator
An Indian Road Traffic Simulator
Given a configuration file (conf.txt is a sample), simulator simulates how vehicles on an usual Indian road behaves.
We have four options in our configuration file.
1) GenerateAtBestLane:
   It generates the vehicle at the best possible lane considering the distance as the parameter.
2) Ignore
   It ignores the vehicles if there is no space for them to enter
3) NoOvertaking
   There wont be any overtaking if we mention this in our config file.
4) Infinite Acceleration
   You can instantly move to the maxSped of the vehicle.
We have four sections in our configuration file.
1)RoadParameters Definition Section
2)Default Vehicle Parameters
3)Specific Vehicle Parameters
4)Simulation Specifications:
  Signal RED : Turns the signal to RED
  Signal GREEN : Turns the signal to GREEN
  VEHICLE COLOR : Generates the vechile of type VEHICLE with color COLOR
  Pass n : Doesnot generate any more vehicles till n sec
  END : End of simulation
We can add comments in the first three sections but in the last section we are not supposed to add any comments in our last section.
Different Configuration files are provided by us in the folder.
POSSIBLE COLORS:
 1) BLUE
 2) VIOLLET
 3) RED 
 4) GREEN
 5) BLUE
 6) ORANGE
 7) VIOLET
 8) WHILTE
 9) BLACK
 10) GREEN (For any other non valid color)
