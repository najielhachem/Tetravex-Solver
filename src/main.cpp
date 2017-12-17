#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "tetravex.hpp"
#include "solver.hpp"

void usage(char* file)
{
	std::cout << "Usage: " << file << std::endl;
	std::cout << "options: " << std::endl;
	std::cout << "-w width: set width" << std::endl;
	std::cout << "-h height: set height" << std::endl;
	std::cout << "-l lambda: set lambda" << std::endl;
	std::cout << "-m nb_interations: set max number of iterations" << std::endl;
	std::cout << "-v : set verbose" << std::endl;

}

void parse(int argc, char** argv, int& w, int& h, int& v, float& l, int& m)
{
	w = 3;
	h = 3;
	v = 0;
	l = 0.99;
	m = -1;

	for (int i = 1; i < argc; ++i)
	{
		if (strcmp(argv[i], "-w") == 0)
			w = atoi(argv[i + 1]);
		if (strcmp(argv[i], "-h") == 0)
			h = atoi(argv[i + 1]);
		if (strcmp(argv[i], "-v") == 0)
			v = 1;
		if (strcmp(argv[i], "-l") == 0)
			l = atof(argv[i + 1]);
		if (strcmp(argv[i], "-m") == 0)
			m = atoi(argv[i + 1]);
	}
}

int main(int argc, char** argv)
{
	int w, h, v, m;
	float l;
	parse(argc, argv, w, h, v, l, m);
	// Start Test
	Tetravex t = Tetravex(w, h);	
	t.random_init();
	std::cout << "random unsolved puzzle\n";	
	std::cout << t;
	Solver s = Solver();
	int it = s.solve(t, l, m, v);
	std::cout << "random puzzle solved in " << it << " iterations\n";	
	std::cout << t;
	// End Test

	return 0;
}
