#include <sstream>
#include <iomanip>
#include <cstdlib>
#include "Article.h"

Article::Article(const string& naam, const string& fabrikant, int vooraad, const int dia, float prijs, const char typ) {
	setName(naam);
	setManufacturer(fabrikant);
	setStock(vooraad);
	setDiameter(dia);
	setPrice(prijs);
	setType(typ);
}

void Article::setName(const string& naam) {
	size_t length{naam.size()};
	length = (length < CHAR ? length : (CHAR - 1));
	naam.copy(name, length);
	name[length] = '\0';
}
string Article::getName() const {
	return name;
}

void Article::setManufacturer(const string& fabrikant) {
	size_t length{ fabrikant.size() };
	length = (length < CHAR ? length : (CHAR - 1));
	fabrikant.copy(manufacturer, length);
	manufacturer[length] = '\0';
}
string Article::getManufacturer() const {
	return manufacturer;
}

void Article::setStock(int vooraad) {
	stock = vooraad;
}
int Article::getStock() const{
	return stock;
}

void Article::setDiameter(const int dia) {
	diameter = dia;
}
int Article::getDiameter() const {
	return diameter;
}

void Article::setPrice(float prijs) {
	price = prijs;
}
float Article::getPrice() const {
	return price;
}

void Article::setType(const char typ) {
	type = typ;
}
char Article::getType() const {
	return type;
}

string Article::toString() const {
	string type;
	if (getType() == 'r' || getType() == 'R')
		type = "Rim";
	else
		type = "Tyre";
	ostringstream stream;
	stream << setw(20) << "Name: " << getName() << endl << setw(20) << "Manufacturer: " << getManufacturer() << endl
		<< setw(20) << "Stock: " << getStock() << endl << setw(20) << "Diameter: " << getDiameter() << endl
		<< setw(20) << "Price: " << setprecision(2) << fixed << showpoint << getPrice() << endl << setw(20) << "Type: " << type;
	return stream.str();
}

string Article::toTable() const {
	string type;
	if (getType() == 'r' || getType() == 'R')
		type = "Rim";
	else
		type = "Tyre";
	ostringstream stream;
	stream << setw(CHAR) << getName() << setw(CHAR) << getManufacturer() << setw(10) << getStock() << setw(10)
		<< getDiameter() << setw(10) << setprecision(2) << fixed << showpoint << getPrice() << setw(5) << type;
	return stream.str();
}

void Article::toFile(ofstream& outFile, streamoff* pos) {
	outFile.seekp(*pos);
	outFile.write((char*)name, sizeof(char[CHAR]));
	outFile.write((char*)manufacturer, sizeof(char[CHAR]));
	outFile.write((char*)&stock, sizeof(int));
	outFile.write((char*)&diameter, sizeof(int));
	outFile.write((char*)&price, sizeof(float));
	outFile.write((char*)&type, sizeof(char));
	*pos = outFile.tellp();
}

void Article::fromFile(ifstream& inFile, streamoff* pos) {
	inFile.seekg(*pos);
	if (inFile.peek() != EOF)
	{
		inFile.read((char*)name, sizeof(char[CHAR]));
		inFile.read((char*)manufacturer, sizeof(char[CHAR]));
		inFile.read((char*)&stock, sizeof(int));
		inFile.read((char*)&diameter, sizeof(int));
		inFile.read((char*)&price, sizeof(float));
		inFile.read((char*)&type, sizeof(char));
		*pos = inFile.tellg();
	}
}