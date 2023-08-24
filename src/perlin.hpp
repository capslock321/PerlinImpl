#pragma once

#ifndef PERLIN_IMPL_HPP
#define PERLIN_IMPL_HPP

#include <vector>
#include <ctime>

namespace PerlinImpl {
	struct Vector2 {
		double x;
		double y;
	};


	class Perlin2D {
		std::vector<int> permutations;
	public:
		int width;
		int height;

		double generate_noise(int x, int y, int octaves = 8);

		double lerp(double a, double b, double x);
		double calculate_noise(double x, double y);

		Perlin2D(int x_size, int y_size, int seed = std::time(nullptr)) :
			width(x_size), height(y_size), permutations(create_permutations(seed)) {}

	private:
		std::vector<int> create_permutations(int seed);

		double fade(double value);
		double sample(std::vector<int> vec, int x, int y);
		double gradient(int permutation, double x, double y);
	};
}

#endif