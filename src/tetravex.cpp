#include "tetravex.hpp"

#include <stdlib.h>

Tetravex::Tetravex(int width, int height, int nb_values)
{
	if (width <= 0 || height < 0)
	{
		// TODO Throw Error
	}
	this->width = width;
	if (height == 0)
		height = width;
	this->height = height;
	this->nb_values = nb_values;
	this->squares = std::vector<Square>(this->width * this->height);
}

void Tetravex::set_squares(std::vector<Square> squares)
{
	if (squares.size() != this->width * this->height)
	{
		// TODO Throw Error
		return; 
	}
	this->squares = squares;
}

std::vector<Square> Tetravex::get_squares() const
{
	return this->squares;
}

int Tetravex::get_width() const
{
	return this->width;
}

int Tetravex::get_height() const
{
	return this->height;
}


void Tetravex::random_solved_init()
{
	// build solved tetravex then permute members
	// random on East and South
	// random on North only in first row
	// random on West only in first column
	// copy North and West from neighbour elsewhere
	srand(time(NULL));
	for (int i = 0; i < this->height; ++i)
	{
		for (int j = 0; j < this->width; ++j)
		{
			int k = i * this->width + j;
			this->squares[k].values[E] = rand() % this->nb_values;
			this->squares[k].values[S] = rand() % this->nb_values;
			
			if (i == 0) 
				this->squares[k].values[N] = rand() % this->nb_values;
			else 
				this->squares[k].values[N] = this->squares[(i - 1) * this->width + j].values[S];
			if (j == 0)
				this->squares[k].values[W] = rand() % this->nb_values;
			else 
				this->squares[k].values[W] = this->squares[i * this->width + (j - 1)].values[E];
		}
	}
}

std::ostream& operator<<(std::ostream& o, const Tetravex& tetravex)
{
	for (int i = 0; i < tetravex.get_height(); ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < tetravex.get_width(); ++k)
			{
				Square sq = tetravex.get_squares()[i * tetravex.get_width() + k];
				if (j == 1)
					o << sq.values[3] << " " << sq.values[1];
				else
					o << " " << sq.values[j] << " ";
				o << " ";
			}
			o << "\n";
		}
		o << "\n";
	}
	return o;
}
