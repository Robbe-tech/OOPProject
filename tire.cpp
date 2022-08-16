#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "Tire.h"

Tire::Tire(const string& naam, const string& fabrikant, int vooraad, const int dia, float prijs, const char typ, const int breedte, const int hoogte, const string& index, const char seizoen) :Article(naam, fabrikant, vooraad, dia, prijs, typ) {
	setWidth(breedte);
	setHeight(hoogte);
	setSpeedIndex(index);
	setSeason(seizoen);
}

void Tire::setWidth(const int breedte) {
	width = breedte;
}
int Tire::getWidth() const {
	return width;
}

void Tire::setHeight(const int hoogte) {
	height = hoogte;
}
int Tire::getHeight() const {
	return height;
}

void Tire::setSpeedIndex(const std::string & index) {
	size_t length{ index.size() };
	length = (length < INDEX ? length : (INDEX - 1));
	index.copy(speedIndex, length);
	speedIndex[length] = '\0';
}
std::string Tire::getSpeedIndex() const {
	return speedIndex;
}

void Tire::setSeason(const char seizoen) {
	season = seizoen;
}
char Tire::getSeason() const {
	return season;
}

string Tire::toString() const {
	string season;
	if (getSeason() == 's' || getSeason() == 'S')
		season = "Summer";
	else
		season = "Winter";
	ostringstream stream;
	stream << Article::toString() << endl << setw(20) << "Width: " << width << " mm" << endl << setw(20) << "Height: " << getHeight() << " mm" << endl << setw(20) << "SpeedIndex: " << getSpeedIndex() << endl << setw(20) << "Season: " << season;
	return stream.str();
}

string Tire::toTable() const {
	string season;
	if (getSeason() == 's' || getSeason() == 'S')
		season = "Summer";
	else
		season = "Winter";
	ostringstream stream;
	stream << Article::toTable() << setw(10) << getWidth() << setw(20) << getHeight() << setw(15) << season << getSpeedIndex();
	return stream.str();
}

void Tire::toFile(ofstream& outFile, streamoff* pos) {
	Article::toFile(outFile, pos);
	outFile.write((char*)&width, sizeof(int));
	outFile.write((char*)&height, sizeof(int));
	outFile.write((char*)speedIndex, sizeof(char[INDEX]));
	outFile.write((char*)&season, sizeof(char));
	*pos = outFile.tellp();
}

void Tire::fromFile(ifstream& inFile, streamoff* pos) {
	inFile.seekg(*pos);
	if (inFile.peek() != EOF)
	{
		Article::fromFile(inFile, pos);
		inFile.read((char*)&width, sizeof(int));
		inFile.read((char*)&height, sizeof(int));
		inFile.read((char*)speedIndex, sizeof(char[INDEX]));
		inFile.read((char*)&season, sizeof(char));
		*pos = inFile.tellg();
	}
}