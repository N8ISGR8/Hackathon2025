#pragma once


#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void inStream();

class Image
{
public:
	Image();

	void loadFromCsv(const string& infile);
	void printBytes();
	
	void saveToFile();
private:
	char byteArr[10000] = { '\0' };
};