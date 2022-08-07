#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "tire.h"

tire::tire(const string& naam, const string& fabrikant, int vooraad, const int dia, float prijs, const char typ, const int breedte, const int hoogte, const string& index, const char seizoen) :article(naam, fabrikant, vooraad, dia, prijs, typ) {
	setWidth(breedte);
	setHeight(hoogte);
	setSpeedIndex(index);
	setSeason(seizoen);
}

void tire::setWidth(const int breedte) {
	width = breedte;
}
int tire::getWidth() const {
	return width;
}

void tire::setHeight(const int hoogte) {
	height = hoogte;
}
int tire::getHeight() const {
	return height;
}

void tire::setSpeedIndex(const std::string & index) {
	size_t length{ index.size() };
	length = (length < INDEX ? length : (INDEX - 1));
	index.copy(speedIndex, length);
	speedIndex[length] = '\0';
}
std::string tire::getSpeedIndex() const {
	return speedIndex;
}

void tire::setSeason(const char seizoen) {
	season = seizoen;
}
char tire::getSeason() const {
	return season;
}

string tire::toString() const {
	string season;
	if (getSeason() == 's' || getSeason() == 'S')
		season = "Summer";
	else
		season = "Winter";
	ostringstream stream;
	stream << article::toString() << "\nWidth: " << setw(20) << getWidth() << "\nHeight: " << setw(20) << getHeight() << "\nSpeedIndex: " << setw(20) << getSpeedIndex() << "\nSeason: " << setw(20) << season;
	return stream.str();
}

string tire::toTable() const {
	string season;
	if (getSeason() == 's' || getSeason() == 'S')
		season = "Summer";
	else
		season = "Winter";
	ostringstream stream;
	stream << article::toTable() << setw(5) << getWidth() << setw(10) << getHeight() << setw(20) << season << setw(15) << getSpeedIndex();
	return stream.str();
}

void tire::toFile(const static string& file, static int pos) {
	ofstream outFile{ file, ios::out | ios::binary };

	if (!outFile) {
		cerr << "File could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	outFile.seekp(pos);
	outFile.write(reinterpret_cast<char*>(this), sizeof(tire));
	pos = outFile.tellp();
}

void tire::fromFile(const static string& file, static int pos) {
	ifstream inFile{ file, ios::in | ios::binary };

	if (!inFile) {
		cerr << "File could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	inFile.seekg(pos);
	inFile.read(reinterpret_cast<char*>(this), sizeof(tire));
	pos = inFile.tellg();
}