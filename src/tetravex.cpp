#include "tetravex.hpp"


Tetravex::Tetravex(int width, int height)
{
	if (width <= 0 || height < 0)
	{
		// TODO Throw Error
	}
	this->width = width;
	if (height == 0)
		height = width;
	this->height = height;
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

std::ostream& operator<<(std::ostream& o, const Tetravex& tetravex);
{
	for (int i = 0; i < this->height; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < this->width; ++k)
			{
				Square sq = this->squares[i * this->width + k];
				if (j == 1)
					o << sq.values[3] << " " << sq.values[1];
				else
					o << " " << sq.values[j] << " ";
				o << " ";
			}
		}
		o << "\n";
	}
	return o;
}
