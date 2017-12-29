#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>
#include <stdlib.h>

#define N 0
#define E 1
#define S 2
#define W 3

struct Piece
{
	// Edge values order: N-E-S-W
	int values [4];
};

class Tetravex
{
	public:
		Tetravex(int width, int height = 0, int nb_values = 10);

		void set_pieces(std::vector<Piece> pieces);
		std::vector<Piece> get_pieces() const;
		int get_width() const;
		int get_height() const;

		void random_shuffle();	
		void random_solved_init();
		void random_init();

	private:
		int width;
		int height;
		int nb_values;
		std::vector<Piece> pieces;
};

std::ostream& operator<<(std::ostream& o, const Tetravex& tetravex);
std::istream& operator>>(std::istream& i, Tetravex& tetravex);
