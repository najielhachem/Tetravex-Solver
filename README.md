# Tetravex Solver

### Project

Generate a random solvable tetravex and try to solve it.

* __Method__  : Simulated annealing
  * Initial Temp: end of uniform distribution
* __Sampler__ : Metropolis-Hastings
  * Improvement: Swap 2 random axis since each axe has one value

### Usage  

* Compiling: `make`
* Execution: `./solver.out [-w width -h height -l lambda -Tmin temperature -Tmax temperature -m max_iter -f input_file -v]`
* Help: `./solver.out --help`

### File Format:
* Piece: `####`
* Order: `North East South West`
* Piece Seperator: `' '`
* Example: `5948 1599 4617 6049 4820 9185 9666 1901 8346`

> File content must match width and height arguments, an error will be generated otherwise.
