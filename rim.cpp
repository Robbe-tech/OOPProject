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
	stream << Article::toString() << endl << "Aluminum: " << setw(20) << alu << endl << "Color" << setw(20) << getColor() << endl << "Width" << setw(20) << getWidth() << " Inch";
	return stream.str();
}

string Rim::toTable() const {
	string alu;
	if (getAluminum())
		alu = "True";
	else
		alu = "False";
	ostringstream stream;
	stream << Article::toTable() << setw(5) << getWidth() << setw(10) << alu << setw(20) << getColor();
	return stream.str();
}

void Rim::toFile(ofstream& outFile, int* pos) {
	outFile.seekp(*pos);
	outFile.write(reinterpret_cast<char*>(this), sizeof(Rim));
	*pos = outFile.tellp();
}

void Rim::fromFile(ifstream& inFile, int* pos) {
	inFile.seekg(*pos);
	if (inFile.peek() != EOF)
	{
		inFile.read(reinterpret_cast<char*>(this), sizeof(Rim));
		*pos = inFile.tellg();
	}
}