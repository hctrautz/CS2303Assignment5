README for PA5 -- Hunter Trautz and Gabriel Aponte, Polymorphisim
------------------------------------------------------------------
Instructions for compiling:
Type 'make' from the command line in the project directory.
------------------------------------------------------------------
To Run:
Type “./PA5 gridSize #doodlebugs #ants #time_steps seed pause”
------------------------------------------------------------------	
Description: 
This program involves a simulation of a grid of n-by-n squares, some of which may be occupied by organisms. There are two kinds of organisms — doodlebugs (the predators) and ants (the prey). Only one organism may occupy a cell at a time. Time is simulated in steps. Each organism attempts to perform some action every step. No action may cause an organism to move off the edges of the grid.
------------------------------------------------------------------
Ants:
Move: For every step, each ant enumerates its adjacent cells — up, down, left, or right — and randomly selects an unoccupied one that is on the grid (Note: For this assignment, a cell has a maximum of four neighbors; no diagonal moves are allowed). If all adjacent cells are occupied or off the edges of the grid, the ant does not move but rather remains in its current location.

Breed: If an ant survives for at least three time steps, at the end of the third time step (i.e., after moving) the ant gives birth to a new ant in an adjacent cell (i.e., up, down, left, or right). If more than one empty cell is available, it chooses one at random. If no empty cell is available, no birth occurs.1F Once an offspring is produced, an ant cannot produce another offspring until it has survived three additional steps.2F
------------------------------------------------------------------
Doodlebugs: 
Move: For every time step, each doodlebug moves to an adjacent cell containing an ant and eats that ant. If more than one adjacent cell contains an ant, one is chosen at random. The ant that was eaten is removed from the grid. If no adjacent cell (i.e., up, down, left, or right) contains an ant, the doodlebug moves according to the same rules as ants. Note that a doodlebug cannot eat another doodlebug.

Starvation: If a doodlebug has not eaten an ant within three time steps, at the end of the third time step, it dies of starvation and is removed from the grid.

Breed: If a doodlebug survives for at least eight time steps, at the end of the eighth time step it spawns off a new doodlebug in the same manner as an ant. If no adjacent cell is empty, no breeding occurs. Once an offspring is produced, a doodlebug cannot produce another offspring until it has survived eight additional steps. Starvation takes precedence over breeding; that is, a starving doodlebug cannot breed.
------------------------------------------------------------------
Sample Output Code: 

Example #1:
******************************************
STATISTICS FOR SIMULATION:

The original command line was: gridSize – 20 #doodlebugs – 10 ants – 50 time_steps – 10 seed – 1 pause - 1
Steps Run: 10
Ant Total: 321
Ants Remaining: 306
Doodlebug Total: 12
Doodlebugs Remaining: 4
*******************************************
FINAL BOARD LAYOUT:

            ooooo o 
 ooo o   o  ooooo oo
ooooo     oo  oooooo
ooooo oooooo ooooo  
o oo  oo o ooooo  oo
 oo o o ooxoo o  ooo
oooooooo  oooo oooo 
oooooo  o  oooo    o
oooooo    xoo ooooo 
ooooo oo ooooxxo   o
ooooooooo  ooooo oo 
oooooooooooooooooooo
 ooooooooooooooooo o
ooooooooooooooooooo 
oooooooooooooooooo  
ooooooo oooooooooooo
ooooo ooooooooooooo 
ooooooooo ooo ooooo 
ooooooooooooooooooo 
ooooo oo oooooooo o 

Example #2:
******************************************
STATISTICS FOR SIMULATION:

The original command line was: gridSize – 5 #doodlebugs – 1 ants – 10 time_steps – 10 seed – 1 pause - 1
Steps Run: 10
Ant Total: 30
Ants Remaining: 21
Doodlebug Total: 1
Doodlebugs Remaining: 1
*******************************************
FINAL BOARD LAYOUT:

ooooo
ooooo
ooooo
oxoo 
 ooo 


------------------------------------------------------------------
Sources: 
We used the sample code from PA2 to create a 2DArray of ints for the game board
