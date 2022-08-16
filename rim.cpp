#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "Rim.h"

Rim::Rim(const string& naam, const string& fabrikant, int vooraad, const int dia, float prijs, const char typ, const bool aluminium, const string& kleur, const int breedte) :Article(naam, fabrikant, vooraad, dia, prijs, typ) {
	setAluminum(aluminium);
	setColor(kleur);
	setWidth(breedte);
}

void Rim::setAluminum(const bool aluminium) {
	aluminum = aluminium;
}
int Rim::getAluminum() const {
	return aluminum;
}

void Rim::setColor(const string & kleur) {
	size_t length{ kleur.size() };
	length = (length < COLOR ? length : (COLOR - 1));
	kleur.copy(color, length);
	color[length] = '\0';
}
std::string Rim::getColor() const {
	return color;
}

void Rim::setWidth(const int breedte) {
	width = breedte;
}
int Rim::getWidth() const {
	return width;
}

string Rim::toString() const {
	string alu;
	if (getAluminum())
		alu = "True";
	else
		alu = "False";
	ostringstream stream;
	stream << Article::toString() << endl << setw(20) << "Aluminum: " << alu << endl << setw(20) << "Color" << getColor() << endl << setw(20) << "Width" << getWidth() << " Inch";
	return stream.str();
}

string Rim::toTable() const {
	string alu;
	if (getAluminum())
		alu = "True";
	else
		alu = "False";
	ostringstream stream;
	stream << Article::toTable() << setw(10) << getWidth() << setw(20) << alu << getColor();
	return stream.str();
}

void Rim::toFile(ofstream& outFile, streamoff* pos) {
	Article::toFile(outFile, pos);
	outFile.write((char*)&aluminum, sizeof(bool));
	outFile.write((char*)color, sizeof(char[COLOR]));
	outFile.write((char*)&width, sizeof(int));
	*pos = outFile.tellp();
}

void Rim::fromFile(ifstream& inFile, streamoff* pos) {
	inFile.seekg(*pos);
	if (inFile.peek() != EOF)
	{
		Article::fromFile(inFile, pos);
		inFile.read((char*)&aluminum, sizeof(bool));
		inFile.read((char*)color, sizeof(char[COLOR]));
		inFile.read((char*)&width, sizeof(int));
		*pos = inFile.tellg();
	}
}