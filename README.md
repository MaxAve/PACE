# P.A.C.E (Pretty Awful Chess Engine)
### Description
PACE is a simple chess engine using minimax with alpha-beta pruning and basic move ordering.\
This is going to be my second attempt at making a chess engine. My first attempt (MaxAve/NerdChess) has been mostly a failure as it performs very poorly, reaching a depth of about 2 moves with decent computation time. Now I'm trying to make a better and faster chess engine. I'm quite sure PACE will be awful, but hopefully better than my first attempt as I have learned much about optimization when developing NerdChess.
### Getting started ###
**Step 1**: Clone the repo
```
git clone https://github.com/MaxAve/PACE.git
```
**Step 2**: ```cd``` into the project and use the Makefile to compile the source code
```
cd PACE
```
```
make
```
If you're on Windows and ```make``` doesn't work for you, you can also try
```
mingw32-make
```
**Step 3**: Run the project
```
./PACE
```
### Tasks ###
What needs to be done
- Implement board representation (**DONE**)
- Implement basic attack bitboards for piece legal moves (**DONE**)
- Implement special moves like castling & en pessant
- Implement an evaluation function
- Implement a minimax function (**DONE**)
- Implement opening book (*CURRENTLY WORKING ON*)
- Optimize minimax function