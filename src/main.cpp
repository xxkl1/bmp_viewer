#include <iostream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <bmp_utils.hpp>
#include <bmp_parser.hpp>
#include <test_to_number.hpp>
#include <test_bmp_parser.hpp>

void test () {
    testToNumber();
    testBmpParser();
}

void render (const std::string& filePath) {
    // bmp解析
    std::vector<u_char> buffer = readFile(filePath);
    BMP bmp = bmpParser(buffer);

    // bmp像素转sfml像素
    sf::VertexArray points(sf::Points);
    for (size_t i = 0; i < bmp.pixels.size(); ++i) {
        std::vector<u_char> pixel = bmp.pixels[i];
        u_char r = pixel[2];
        u_char g = pixel[1];
        u_char b = pixel[0];
        // 渲染顺序：从下到上，从左到右
        size_t x = i % bmp.width + 1;
        size_t y = bmp.height - i / bmp.width;
        points.append(sf::Vertex(sf::Vector2f(x, y), sf::Color(r, g, b)));
    }

    // 渲染
    sf::RenderWindow window(sf::VideoMode(800, 600), "bmp viewer");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(231, 222, 205));

        window.draw(points);

        window.display();
    }
}

int main() {
    test();
    render("./image/24bit_color.bmp");
    return 0;
}
