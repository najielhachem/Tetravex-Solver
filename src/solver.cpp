#include "solver.hpp"

#include <iostream>

int energie(Tetravex& t)
{
	int e = 0;
	std::vector<Piece> pieces = t.get_pieces();
	for (int i = 0; i < t.get_height(); ++i)
	{
		for (int j = 0; j < t.get_width(); ++j)
		{
			int k = i * t.get_width() + j;

			if (i != 0) 
				if (pieces[k].values[N] != pieces[(i - 1) * t.get_width() + j].values[S])
					e += 1;
			if (j != 0)
				if (pieces[k].values[W] != pieces[i * t.get_width() + (j - 1)].values[E])
					e += 1;
		}
	}
	return e;
}

void solve(Tetravex& t)
{
	std::cout << energie(t) << "\n";
}
