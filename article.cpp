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
	stream << "Name: " << setw(20) << getName() << endl << "Manufacturer: " << setw(20) << getManufacturer() << endl
		<< "Stock: " << setw(20) << getStock() << endl << "Diameter: " << setw(20) << getDiameter() << endl
		<< "Price: " << setw(20) << setprecision(2) << fixed << showpoint << getPrice() << endl << "Type: " << setw(20) << type;
	return stream.str();
}

string Article::toTable() const {
	string type;
	if (getType() == 'r' || getType() == 'R')
		type = "Rim";
	else
		type = "Tyre";
	ostringstream stream;
	stream << getName() << setw(CHAR) << getManufacturer() << setw(CHAR) << getStock() << setw(10)
		<< getDiameter() << setw(10) << setprecision(2) << fixed << showpoint << getPrice() << setw(10) << type;
	return stream.str();
}

void Article::toFile(ofstream& outFile, streamoff* pos) {
	outFile.seekp(*pos);
	outFile.write(reinterpret_cast<char*>(this), sizeof(Article));
	*pos = outFile.tellp();
}

void Article::fromFile(ifstream& inFile, streamoff* pos) {
	inFile.seekg(*pos);
	if (inFile.peek() != EOF)
	{
		inFile.read(reinterpret_cast<char*>(this), sizeof(Article));
	}
}