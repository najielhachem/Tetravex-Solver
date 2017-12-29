#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

#include "tetravex.hpp"
#include "solver.hpp"

void usage(char* file)
{
	std::cout << "Usage:\n" 																							 
					  << "\t" << file << " [-w width -h height -l lambda -Tmin temperature -Tmax temperature -m max_iter -f input_file -v]\n"
						<< "Help:\n"
						<< "\t" << file << " --help\n";
}

void help(char* file)
{
	std::cout << "Usage:\n" 																							 
					  << "\t" << file << " [-w width -h height -l lambda -Tmin temperature -Tmax temperature -m max_iter -f input_file -v]\n"
						<< "\nDesctiption:\n" 																				 
						<< "\t-w width          : set board width to width\n" 												 
						<< "\t-h height         : set board height to height\n" 											 
						<< "\t-l lambda         : set lambda to lambda\n" 											 
						<< "\t-Tmin temperature : set temperature's lower bound\n" 											 
						<< "\t-Tmax temperature : set starting temperature\n" 											 
						<< "\t-m max_iter       : set max number of iterations to max_iter (-1 <=> inf)\n" 	
						<< "\t-f input_file     : read tetravex from input_file\n" 	
						<< "\t-v                : set verbose to true\n"
						<< "\nDefault Values:\n"
						<< "\twidth             : 3\n" 												 
						<< "\theight            : 3\n" 											 
						<< "\tlambda            : 0.99\n" 											 
						<< "\tmin_temperature   : 0.5\n"
						<< "\tmax_temperature   : end point of uniform distribution\n"
						<< "\tmax_iter          : inf\n" 		
						<< "\tinput_file        : if not defined, random tetravex is generated\n" 		
						<< "\tverbose           : false\n";
}

int parse(int argc, char** argv, int& w, int& h, int& v,
		float& l, float& T_min, float& T_max, int& m,
		char* input_file)
{
	w = 3;
	h = 3;
	v = 0;
	l = 0.99;
	T_max = -1;
	T_min = 0.5;
	m = -1;

	for (int i = 1; i < argc; ++i)
	{
		if (strcmp(argv[i], "-w") == 0)
			w = atoi(argv[++i]);
		else if (strcmp(argv[i], "-h") == 0)
			h = atoi(argv[++i]);
		else if (strcmp(argv[i], "-v") == 0)
			v = 1;
		else if (strcmp(argv[i], "-l") == 0)
			l = atof(argv[++i]);
		else if (strcmp(argv[i], "-Tmin") == 0)
			T_min = atof(argv[++i]);
		else if (strcmp(argv[i], "-Tmax") == 0)
			T_max = atof(argv[++i]);
		else if (strcmp(argv[i], "-f") == 0)
			strcpy(input_file, argv[++i]);
		else if (strcmp(argv[i], "-m") == 0)
			m = atoi(argv[++i]);
		else if (strcmp(argv[i], "--help") == 0)
		{
			help(argv[0]);
			return 0;
		} 
		else
		{
			usage(argv[0]);
			return 0;
		}
	}
	if (w <= 0 || h <= 0 || l <= 0.0 || l >= 1.0 || m < -1) // error in atoi or atof
	{
		std::cout << "Error:\n"
							<< "\twidth, height must be a positive integers\n"
							<< "\tmax_iter must be a positive integer or -1\n"
							<< "\tlambda must be a float contained in ]0, 1[\n";
		usage(argv[0]);
		return 0;
	}
	return 1;
}

int main(int argc, char** argv)
{
	int w, h, v, m;
	float l, T_min, T_max;
	char input[256];
	if (parse(argc, argv, w, h, v, l, T_min, T_max, m, input))
	{
		// Start Test
		Tetravex t = Tetravex(w, h);	
		if (input[0] == '\0')
		{
			t.random_init();
			std::cout << "random unsolved puzzle\n";	
		} else
		{
			try {
				std::ifstream is(input);
				std::cout << "reading puzzle from file\n";	
				is >> t;
			} catch (const std::exception& e) {
				std::cout << e.what();
				return 1;
			}
		}
		std::cout << t;
		Solver s = Solver();
		int it = s.solve(t, l, T_min, T_max, m, v);
		std::cout << "random puzzle solved in " << it << " iterations\n";	
		std::cout << t;
		// End Test
	}
	return 0;
}
