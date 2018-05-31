#pragma once

#include "C:\Users\szkatu\Desktop\lodepng-master\lodepng.h"
#include <iostream>
using namespace std;
class Util
{
public:
	Util();
	~Util();
	 void displayPNGInfo(const LodePNGInfo & info);
	 void displayChunkNames(const std::vector<unsigned char>& buffer);
	void decode(const std::vector<unsigned char>& image, unsigned w, unsigned h, array<array<int, 28>, 28>& tab);
	void displayFilterTypes(const std::vector<unsigned char>& buffer, bool ignore_checksums);
};

