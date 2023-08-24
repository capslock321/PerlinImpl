#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <cmath>

#include "perlin.hpp"


std::vector<int> PerlinImpl::Perlin2D::create_permutations(int seed) {
    // permutations MUST be in the 0-256 range
    std::vector<int> permutations(512);
    
    auto shuffler = std::default_random_engine(seed);

    std::iota(permutations.begin(), permutations.end(), 1);
    std::shuffle(permutations.begin(), permutations.end(), shuffler);
    
    // extend the permutation array to prevent overflows
    permutations.insert(permutations.end(), permutations.begin(), permutations.end());
    return permutations;
}

double PerlinImpl::Perlin2D::lerp(double a, double b, double x) {
    // return (1 - x) * a + x * b; // both work
    return a * (1 - x) + x * b;
}


double PerlinImpl::Perlin2D::gradient(int permutation, double x, double y) {
    double x_result = ((permutation & 1) ? x : -x) * x; // u
    double y_result = ((permutation & 2) ? y : -y) * y; // v
    return x_result + y_result;
}

double PerlinImpl::Perlin2D::sample(std::vector<int> vec, int x, int y) {
    int _x = x & 255;
    int _y = y & 255;
    return vec[_y + vec[_x]];
}


double PerlinImpl::Perlin2D::calculate_noise(double x, double y) {
    int fx = (int) floor(x) & 255; // floored x
    int fy = (int) floor(y) & 255; // floored y
    
    // why not use fx and fy? i have no clue.
    double x_distance = x - floor(x);
    double y_distance = y - floor(y);

    double bottom_left = gradient(sample(permutations, fx + 0, fy + 0), x_distance - 0.0, y_distance - 0.0);
    double bottom_right = gradient(sample(permutations, fx + 1, fy + 0), x_distance - 1.0, y_distance - 0.0);
    double top_left = gradient(sample(permutations, fx + 0, fy + 1), x_distance - 0.0, y_distance - 1.0);
    double top_right = gradient(sample(permutations, fx + 1, fy + 1), x_distance - 1.0, y_distance - 1.0);
        
    double top_lerp = lerp(top_left, top_right, fade(x_distance));
    double bottom_lerp = lerp(bottom_left, bottom_right, fade(x_distance));

    return lerp(bottom_lerp, top_lerp, fade(y_distance));
}

double PerlinImpl::Perlin2D::fade(double value) {
    return 6 * pow(value, 5) - 15 * pow(value, 4) + 10 * pow(value, 3);
}

double PerlinImpl::Perlin2D::generate_noise(int x, int y, int octaves) {
    double calculated_noise = 0.0;
    double amplitude = 1.0;
    double frequency = 0.05;

    for (int octave = 0; octave < octaves; octave++) {
        calculated_noise += calculate_noise(x * frequency, y * frequency) * amplitude;

        amplitude = amplitude * 0.5;
        frequency = frequency * 2.0;
    }
    return calculated_noise;

}
