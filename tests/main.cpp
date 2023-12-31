#include <iostream>
#include <fstream>
#include <algorithm>

#include "../external/png++/png.hpp"

#include "../src/perlin.hpp"

/*
 *  Sources used:
 *       - https://adrianb.io/2014/08/09/perlinnoise.html
 *       - https://mrl.cs.nyu.edu/~perlin/noise/
 *       - https://rtouti.github.io/graphics/perlin-noise-algorithm
 */


void write_png(std::vector<double> noise, std::string fp, int w, int h) {
    png::image<png::rgb_pixel> image(w, h);
    for (size_t y = 0; y < image.get_height(); ++y) {
        for (size_t x = 0; x < image.get_width(); ++x) {
            double color_value = (noise.at(x + y * w) + 1) / 2;

            int color = color_value * 255;
            image.set_pixel(x, y, png::rgb_pixel(color, color, color));
        }
    }
    return image.write(fp);
}


int main(int argc, char* argv[]) {
    PerlinImpl::Perlin2D perlin(256, 256, 1992);
    // perlin.width = 256, perlin.height = 256
    std::vector<double> noise(perlin.width * perlin.height);
    std::cout << "Generating...\n";

    for (int y = 0; y < perlin.width; y++) {
        for (int x = 0; x < perlin.height; x++) {
            noise[x + y * perlin.width] = perlin.generate_noise(x, y, 8);
        }
    }

    write_png(noise, "noise.png", perlin.width, perlin.height);

    std::cout << "Done!" << "\n";
    return 0;
}
