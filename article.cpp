#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "article.h"

article::article(const string& naam, const string& fabrikant, int vooraad, const int dia, float prijs, const char typ) {
	setName(naam);
	setManufacturer(fabrikant);
	setStock(vooraad);
	setDiameter(dia);
	setPrice(prijs);
	setType(typ);
}

void article::setName(const string& naam) {
	size_t length{naam.size()};
	length = (length < CHAR ? length : (CHAR - 1));
	naam.copy(name, length);
	name[length] = '\0';
}
string article::getName() const {
	return name;
}

void article::setManufacturer(const string& fabrikant) {
	size_t length{ fabrikant.size() };
	length = (length < CHAR ? length : (CHAR - 1));
	fabrikant.copy(manufacturer, length);
	manufacturer[length] = '\0';
}
string article::getManufacturer() const {
	return manufacturer;
}

void article::setStock(int vooraad) {
	stock = vooraad;
}
int article::getStock() const{
	return stock;
}

void article::setDiameter(const int dia) {
	diameter = dia;
}
int article::getDiameter() const {
	return diameter;
}

void article::setPrice(float prijs) {
	price = prijs;
}
float article::getPrice() const {
	return price;
}

void article::setType(const char typ) {
	type = typ;
}
char article::getType() const {
	return type;
}

string article::toString() const {
	string type;
	if (getType() == 'r' || getType() == 'R')
		type = "Rim";
	else
		type = "Tyre";
	ostringstream stream;
	stream << "Name: " << setw(20) << getName() << "\nManufacturer: " << setw(20) << getManufacturer()
		<< "\nStock: " << setw(20) << getStock() << "\nDiameter: " << setw(20) << getDiameter()
		<< "\nPrice: " << setw(20) << setprecision(2) << fixed << showpoint << getPrice() << "\nType: " << setw(20) << type;
	return stream.str();
}

string article::toTable() const {
	string type;
	if (getType() == 'r' || getType() == 'R')
		type = "Rim";
	else
		type = "Tyre";
	ostringstream stream;
	stream << getName() << setw(CHAR) << getManufacturer() << setw(CHAR) << getStock()
		<< setw(10) << getDiameter() << setw(10) << setprecision(2) << fixed << showpoint << getPrice() << setw(10) << type;
	return stream.str();
}

void article::toFile(const static string& file, int* pos) {
	ofstream outFile{file, ios::out | ios::binary};

	if (!outFile) {
		cerr << "File could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	outFile.seekp(*pos);
	outFile.write(reinterpret_cast<char*>(this), sizeof(article));
	*pos = outFile.tellp();
}

void article::fromFile(const static string& file, int* pos) {
	ifstream inFile{file, ios::in | ios::binary};
	
	if (!inFile) {
		cerr << "File could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	inFile.seekg(*pos);
	inFile.read(reinterpret_cast<char*>(this), sizeof(article));
	*pos = inFile.tellg();
}