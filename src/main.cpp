#include <iostream>
#include <stdlib.h>

#include "tetravex.hpp"
#include "solver.hpp"

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << "width [height]\n";
		return -1;
	}
	int width = atoi(argv[1]);
	// Start Test
	Tetravex t = Tetravex(width);	
	t.random_init();
	std::cout << "random unsolved puzzle\n";	
	std::cout << "---------------------\n";
	std::cout << t;
	std::cout << "---------------------\n";
	std::cout << "---------------------\n";
	Solver s = Solver();
	int it = s.solve(t, 0.99);
	std::cout << "random puzzle solved in " << it << " iterations\n";	
	std::cout << "---------------------\n";
	std::cout << t;
	// End Test

	return 0;
}
