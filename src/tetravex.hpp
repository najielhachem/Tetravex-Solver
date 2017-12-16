#include <vector>
#include <iostream>

struct Square
{
	// Edge values order: N-E-S-W
	float values [4];
}

class Tetravex
{
	public:
		Tetravex(int width, int height = 0);

		void set_squares(std::vector<Square> squares);

	private:
		int width;
		int height;
		std::vector<Square> squares;
}

std::ostream& operator<<(std::ostream& o, const Tetravex& tetravex);
