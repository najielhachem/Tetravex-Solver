#include "solver.hpp"

#include <iostream>
#include <math.h>

double proba_transition(double delta_U, double T)
{
	return exp(delta_U / T);
}

double energie(Tetravex& t)
{
	double U = 0;
	std::vector<Piece> pieces = t.get_pieces();
	for (int i = 0; i < t.get_height(); ++i)
	{
		for (int j = 0; j < t.get_width(); ++j)
		{
			int k = i * t.get_width() + j;

			if (i != 0) 
				if (pieces[k].values[N] != pieces[(i - 1) * t.get_width() + j].values[S])
					U += 1;
			if (j != 0)
				if (pieces[k].values[W] != pieces[i * t.get_width() + (j - 1)].values[E])
					U += 1;
		}
	}
	return U;
}

void solve(Tetravex& t)
{

}
