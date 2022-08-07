#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "rim.h"

rim::rim(const string& naam, const string& fabrikant, int vooraad, const int dia, float prijs, const char typ, const bool aluminium, const string& kleur, const int breedte) :article(naam, fabrikant, vooraad, dia, prijs, typ) {
	setAluminum(aluminium);
	setColor(kleur);
	setWidth(breedte);
}

void rim::setAluminum(const bool aluminium) {
	aluminum = aluminium;
}
int rim::getAluminum() const {
	return aluminum;
}

void rim::setColor(const string & kleur) {
	size_t length{ kleur.size() };
	length = (length < COLOR ? length : (COLOR - 1));
	kleur.copy(color, length);
	color[length] = '\0';
}
std::string rim::getColor() const {
	return color;
}

void rim::setWidth(const int breedte) {
	width = breedte;
}
int rim::getWidth() const {
	return width;
}

string rim::toString() const {
	string alu;
	if (getAluminum())
		alu = "True";
	else
		alu = "False";
	ostringstream stream;
	stream << article::toString() << "\nAluminum: " << setw(20) << alu << "\nColor" << setw(20) << getColor() << "\nWidth" << setw(20) << getWidth();
	return stream.str();
}

string rim::toTable() const {
	string alu;
	if (getAluminum())
		alu = "True";
	else
		alu = "False";
	ostringstream stream;
	stream << article::toTable() << setw(5) << getWidth() << setw(10) << alu << setw(20) << getColor();
	return stream.str();
}

void rim::toFile(const static string& file, static int pos) {
	ofstream outFile{file, ios::out | ios::binary};

	if (!outFile) {
		cerr << "File could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	outFile.seekp(pos);
	outFile.write(reinterpret_cast<char*>(this), sizeof(rim));
	pos = outFile.tellp();
}

void rim::fromFile(const static string& file, static int pos) {
	ifstream inFile{file, ios::in | ios::binary};

	if (!inFile) {
		cerr << "File could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	inFile.seekg(pos);
	inFile.read(reinterpret_cast<char*>(this), sizeof(rim));
	pos = inFile.tellg();
}