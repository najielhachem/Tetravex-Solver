#include "tetravex.hpp"

#include <stdlib.h>
#include <algorithm>
#include <random>

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
	this->pieces = std::vector<Piece>(this->width * this->height);
}

void Tetravex::set_pieces(std::vector<Piece> pieces)
{
	if (pieces.size() != this->width * this->height)
		throw std::length_error("invalid pieces size\n");
	this->pieces = pieces;
}

std::vector<Piece> Tetravex::get_pieces() const
{
	return this->pieces;
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
			this->pieces[k].values[E] = rand() % this->nb_values;
			this->pieces[k].values[S] = rand() % this->nb_values;
			
			if (i == 0) 
				this->pieces[k].values[N] = rand() % this->nb_values;
			else 
				this->pieces[k].values[N] = this->pieces[(i - 1) * this->width + j].values[S];
			if (j == 0)
				this->pieces[k].values[W] = rand() % this->nb_values;
			else 
				this->pieces[k].values[W] = this->pieces[i * this->width + (j - 1)].values[E];
		}
	}
}

void Tetravex::random_shuffle()
{
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(this->pieces.begin(), this->pieces.end(), g);
}

void Tetravex::random_init()
{
	this->random_solved_init();
	this->random_shuffle();
}

std::ostream& operator<<(std::ostream& o, const Tetravex& tetravex)
{
	o << " ";
	for (int i = 0; i < tetravex.get_width(); ++i)
			o << "----------";
		o << "-\n";

	for (int i = 0; i < tetravex.get_height(); ++i)
	{
		o << "| ";
		for (int j = 0; j < tetravex.get_width(); ++j)
			o << " -------  ";
		o << "|\n";

		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < tetravex.get_width(); ++k)
			{
				if (k == 0)
					o << "| ";

				Piece p = tetravex.get_pieces()[i * tetravex.get_width() + k];
				if (j == 1)
					o << "| " << p.values[3] << "   " << p.values[1] << " |";
				else
					o << "|   " << p.values[j] << "   |";
				o << " ";
				if (k == tetravex.get_width() - 1)
					o << "|";
			}
			o << "\n";
		}

		o << "| ";
		for (int j = 0; j < tetravex.get_width(); ++j)
			o << " -------  ";
		o << "|\n";
	}

	o << " ";
	for (int i = 0; i < tetravex.get_width(); ++i)
			o << "----------";
		o << "-\n";
	
	return o;
}

std::istream& operator>>(std::istream& i, Tetravex& tetravex)
{
	std::vector<Piece> tmp; 
	std::cout << "";
	Piece p;
	char c;
	int k = 0;
	while (i.get(c))
	{
		if (c == ' ')
		{
			if (k != 4)
				throw std::invalid_argument("Error in reading tetravex from file\n");
			tmp.push_back(p);
			k = 0;
		} else
			p.values[k++] = atoi(&c);
	}
	tmp.push_back(p);
	tetravex.set_pieces(tmp);
	return i;
}
