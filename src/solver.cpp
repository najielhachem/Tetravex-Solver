#include "solver.hpp"

#include <algorithm>

#include <math.h>
#include <stdlib.h>

Solver::Solver()
{
	std::random_device rd;  
	this->gen = std::mt19937(rd()); 
	this->dist = std::uniform_real_distribution<double>(0.0, 1.0);
}

int Solver::sample(double delta_U, double T)
{
	double p = exp(- delta_U / T);
	if (this->dist(this->gen) < p)
		return 1;
	return 0;
}

double Solver::get_U(const std::vector<Piece>& pieces, const int width, const int height)
{
	double U = 0;
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			int k = i * width + j;
			if (i != 0) 
				if (pieces[k].values[N] != pieces[(i - 1) * width + j].values[S])
					U += 1;
			if (j != 0)
				if (pieces[k].values[W] != pieces[i * width + (j - 1)].values[E])
					U += 1;
		}
	}
	return U;
}

double Solver::init_T(Tetravex& t)
{
	double T1 = 0;
	double T2 = 1000000;
	double T = T2;

	std::vector<Piece> pieces = t.get_pieces();
	int width = t.get_width();
	int height = t.get_height();
	int n = height * width;

	double eps_T = 1;

	while ((T2 - T1) > eps_T)
	{
		T = T1 + (T2 - T1) / 2;

		int uniform = 0;
		int nb_samples = 100;
	
		// check if uniform distribution
		// sample m times and check if transition proba is near 1
		for (int i = 0; i < nb_samples; ++i)
		{
			double eps_prob = 0.01;
			
			int i1 = rand() % n;
			int i2 = i1;
			while (i2 == i1)
				i2 = rand() % n;

			double U1 = get_U(pieces, width, height);
			std::iter_swap(pieces.begin() + i1, pieces.begin() + i2);
			double U2 = get_U(pieces, width, height);
			
			if (exp(- abs(U2 - U1) / T) > 1 - eps_prob)
				uniform += 1;
		}

		if (uniform >= 0.98 * nb_samples)
			T2 = T;
		else
			T1 = T;
	}

	std::cout << "Initial T: " << T << std::endl;
	return T;

}

int Solver::solve(Tetravex& t, double lambda, int max_iterations, int verbose)
{
	t.random_shuffle();
  double T = this->init_T(t);

	std::vector<Piece> pieces = t.get_pieces();
	int width = t.get_width();
	int height = t.get_height();
	int n = height * width;

	int iterations = 0;
	double U1 = get_U(pieces, width, height);
	while (U1 != 0)
	{
		// 1- Choose two different random axes
		int i1 = rand() % n;
		int i2 = i1;
		while (i2 == i1)
			i2 = rand() % n;

		// 2- swap axis
		std::iter_swap(pieces.begin() + i1, pieces.begin() + i2);

		// 3- delta_u
		double U2 = get_U(pieces, width, height);
		double delta_U = U2 - U1;

		if (delta_U <= 0) // 4- choose candidate
			t.set_pieces(pieces);
		else if (sample(delta_U, T)) // choose candidate based on transition proba
				t.set_pieces(pieces);

		T *= lambda;
		U1 = get_U(pieces, width, height);
		iterations++;

		if (verbose)
			std::cout << iterations << ": " << U1 << std::endl;
		if (max_iterations == iterations)
			break;
	}
	return iterations;
}
