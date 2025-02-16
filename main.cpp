#include "byteInStream.hpp"

int main()
{
    Image img;
    img.loadFromCsv("imgBytes.csv");
    img.printBytes();
    img.saveToFile();
    return 0;
}