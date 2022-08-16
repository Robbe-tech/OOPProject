#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "Customer.h"

Customer::Customer(const string& naam,const string& adres, const char typ) {
	setName(naam);
	setAddress(adres);
	setType(typ);
}

void Customer::setName(const string & naam) {
	size_t length{ naam.size() };
	length = (length < NAME ? length : (NAME - 1));
	naam.copy(name, length);
	name[length] = '\0';
}
std::string Customer::getName() const {
	return name;
}

void Customer::setAddress(const string & adres) {
	size_t length{ adres.size() };
	length = (length < ADDRESS ? length : (ADDRESS - 1));
	adres.copy(address, length);
	address[length] = '\0';
}
string Customer::getAddress() const {
	return address;
}

void Customer::setType(const char typ) {
	type = typ;
}
char Customer::getType() const {
	return type;
}

string Customer::toString() const {
	string type;
	if (getType() == 'u' || getType() == 'U')
		type = "Customer";
	else
		type = "Company";
	ostringstream stream;
	stream << setw(20) << "Name: " << getName() << endl << setw(20) << "Address: " << getAddress() << endl << setw(20) << "Type: " << type;
	return stream.str();
}

string Customer::toTable() const {
	string type;
	if (getType() == 'u' || getType() == 'U')
		type = "Customer";
	else
		type = "Company";
	ostringstream stream;
	stream << setw(NAME) << getName() << setw(ADDRESS) << getAddress() << setw(10) << type;
	return stream.str();
}

void Customer::toFile(ofstream& outFile, streamoff* pos) {
	outFile.seekp(*pos);
	outFile.write((char*)name, sizeof(char[NAME]));
	outFile.write((char*)address, sizeof(char[ADDRESS]));
	outFile.write((char*)&type, sizeof(char));
	*pos = outFile.tellp();
}

void Customer::fromFile(ifstream& inFile, streamoff* pos) {
	inFile.seekg(*pos);
	if (inFile.peek() != EOF)
	{
		inFile.read((char*)name, sizeof(char[NAME]));
		inFile.read((char*)address, sizeof(char[ADDRESS]));
		inFile.read((char*)&type, sizeof(char));
		*pos = inFile.tellg();
	}
}