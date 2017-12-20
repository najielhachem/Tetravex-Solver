# Tetravex Solver

Generate a random solvable tetravex and try to solve it.

* __Method__  : Simulated annealing
  * Initial Temp: end of uniform distribution
* __Sampler__ : Metropolis-Hastings
  * Improvement: Swap 2 random axis since each axe has one value

### Usage  
  * Compiling: `make`
  * Execution: `./solver.out [-w width -h height -l lambda -m max_iter -v]`
  * Help: `./solver.out --help`
