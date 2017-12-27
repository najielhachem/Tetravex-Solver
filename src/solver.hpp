#pragma once

#include "tetravex.hpp"

#include <iostream>
#include <vector>
#include <random>

class Solver{

	public:
		Solver();

		int solve(Tetravex& t, double lambda, double T_min,
				double T_max, int max_iterations, int verbose);

		double get_U(const std::vector<Piece>& pieces, const int width, const int height);
		double init_T(Tetravex& t);

	private:
		std::mt19937 gen;
		std::uniform_real_distribution<double> dist;

		bool sample(double delta_U, double T);
};

