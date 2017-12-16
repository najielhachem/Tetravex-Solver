#include <vector>
#include <iostream>

#define N 0
#define E 1
#define S 2
#define W 3

struct Square
{
	// Edge values order: N-E-S-W
	float values [4];
};

class Tetravex
{
	public:
		Tetravex(int width, int height = 0, int nb_values = 10);

		void set_squares(std::vector<Square> squares);
		std::vector<Square> get_squares() const;
		int get_width() const;
		int get_height() const;
		
		void random_solved_init();
	
	private:
		int width;
		int height;
		int nb_values;
		std::vector<Square> squares;
};

std::ostream& operator<<(std::ostream& o, const Tetravex& tetravex);
