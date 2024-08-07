#include <test_bmp_parser.hpp>

Bmp getBmpMsg () {
    std::vector<char> buffer = readFile("./image_test/16bit_color_small.bmp");
    return bmpParser(buffer);
}

void testBmpParserContentStart (const Bmp msg) {
    size_t expect = 0xca;
    size_t result = msg.contentStart;
    ensure<size_t>(result, expect, "testBmpParser content start");
}

void testBmpParserContentLen (const Bmp msg) {
    size_t expect = 8;
    size_t result = msg.content.size();
    ensure<size_t>(result, expect, "testBmpParser content len");
}

void testBmpParserCompression (const Bmp msg) {
    size_t expect = 0;
    size_t result = msg.compression;
    ensure<size_t>(result, expect, "testBmpParser compression");
}

void testBmpParserWidth (const Bmp msg) {
    size_t expect = 2;
    size_t result = msg.width;
    ensure<size_t>(result, expect, "testBmpParser width");
}

void testBmpParserHeight (const Bmp msg) {
    size_t expect = 2;
    size_t result = msg.height;
    ensure<size_t>(result, expect, "testBmpParser height");
}

void testBmpParserDeep (const Bmp msg) {
    size_t expect = 4;
    size_t result = msg.deep;
    ensure<size_t>(result, expect, "testBmpParser deep");
}

void testBmpSizeDIB (const Bmp msg) {
    size_t expect = 124;
    size_t result = msg.sizeDIB;
    ensure<size_t>(result, expect, "testBmpParser size DIB");
}

void testPalette (const Bmp msg) {
    std::vector<std::string> expect = {
        "#000000",
        "#ff0000",
        "#00ff00",
        "#0000ff",
        "#000000",
        "#000000",
        "#000000",
        "#000000",
        "#000000",
        "#000000",
        "#000000",
        "#000000",
        "#000000",
        "#000000",
        "#000000",
        "#000000",
    };
    std::vector<std::string> result = msg.palette;
    ensure<std::vector<std::string>>(result, expect, "testBmpParser palette");
}

void testBmpParser () {
    Bmp msg = getBmpMsg();
    testBmpParserContentStart(msg);
    testBmpParserContentLen(msg);
    testBmpParserCompression(msg);
    testBmpParserWidth(msg);
    testBmpParserHeight(msg);
    testBmpParserDeep(msg);
    testBmpSizeDIB(msg);
    testPalette(msg);
}