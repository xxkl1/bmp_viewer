#include <iostream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <bmp_utils.hpp>
#include <bmp_parser.hpp>
#include <test_to_number.hpp>
#include <test_bmp_parser.hpp>

int main() {
    std::vector<u_char> buffer = readFile("./image_test/16bit_color_small.bmp");

    BMP bmp = bmpParser(buffer);

    // TODO: 迁移到test目录
    testToNumber();
    testBmpParser();

    sf::RenderWindow window(sf::VideoMode(800, 600), "bmp viewer");
    sf::VertexArray points(sf::Points);

    for (size_t i = 0; i < bmp.pixels.size(); ++i) {
        std::vector<u_char> pixel = bmp.pixels[i];
        u_char r = pixel[2];
        u_char g = pixel[1];
        u_char b = pixel[0];
        // 渲染顺序：从下到上，从右到左
        size_t x = bmp.width - i % bmp.width;
        size_t y = bmp.height - i / bmp.width;
        points.append(sf::Vertex(sf::Vector2f(x, y), sf::Color(r, g, b)));
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        window.draw(points);

        window.display();
    }
    return 0;
}
