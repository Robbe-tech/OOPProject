#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "customer.h"

customer::customer(const string& naam,const string& adres, const char typ) {
	setName(naam);
	setAddress(adres);
	setType(typ);
}

void customer::setName(const string & naam) {
	size_t length{ naam.size() };
	length = (length < NAME ? length : (NAME - 1));
	naam.copy(name, length);
	name[length] = '\0';
}
std::string customer::getName() const {
	return name;
}

void customer::setAddress(const string & adres) {
	size_t length{ adres.size() };
	length = (length < ADDRESS ? length : (ADDRESS - 1));
	adres.copy(address, length);
	address[length] = '\0';
}
string customer::getAddress() const {
	return address;
}

void customer::setType(const char typ) {
	type = typ;
}
char customer::getType() const {
	return type;
}

string customer::toString() const {
	string type;
	if (getType() == 'u' || getType() == 'U')
		type = "Customer";
	else
		type = "Company";
	ostringstream stream;
	stream << "Name: " << setw(20) << getName() << "\nAddress: " << setw(20) << getAddress() << "\nType: " << setw(20) << type;
	return stream.str();
}

string customer::toTable() const {
	string type;
	if (getType() == 'u' || getType() == 'U')
		type = "Customer";
	else
		type = "Company";
	ostringstream stream;
	stream << getName() << setw(NAME) << getAddress() << setw(ADDRESS) << type;
	return stream.str();
}

void customer::toFile(const string& file, static int pos) {
	ofstream outFile{ file, ios::out | ios::binary };

	if (!outFile) {
		cerr << "File could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	outFile.seekp(pos);
	outFile.write(reinterpret_cast<char*>(this), sizeof(customer));
	pos = outFile.tellp();
}

void customer::fromFile(const string& file, static int pos) {
	ifstream inFile{ file, ios::in | ios::binary };

	if (!inFile) {
		cerr << "File could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	inFile.seekg(pos);
	inFile.read(reinterpret_cast<char*>(this), sizeof(customer));
	pos = inFile.tellg();
}