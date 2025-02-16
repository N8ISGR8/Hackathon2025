#include "byteInStream.hpp"

Image::Image() {}

void Image::loadFromCsv(const string& infile)
{

	std::ifstream inputFile(infile);

	if (!inputFile.is_open())
	{
		std::cerr << "Error opening file" << std::endl;
		return;
	}
	else
	{
		std::string line;
		int index = 0;
		while (getline(inputFile, line, ',') && index < 10000)
		{
			int j = 0;
			while (line[j] != '\0')
			{
				byteArr[index] = line[j];
				index++;
				j++;
			}
		}
	}
	
	
}

void Image::printBytes() 
{
	for (int i = 0; i < 10000 && byteArr[i] != '\0'; ++i)
	{
		cout << byteArr[i] <<  "";
	}
	cout << endl;
}

void Image::saveToFile()
{
	std::ofstream outFile("savedImgBytes.csv");

	if (outFile.is_open())
	{
		int i = 0;
		while (byteArr[i] != '\0')
		{
			outFile << byteArr[i];
			i++;
		}
	}

	outFile.close();
}