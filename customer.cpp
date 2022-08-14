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
	stream << "Name: " << setw(20) << getName() << endl << "Address: " << setw(20) << getAddress() << endl << "Type: " << setw(20) << type;
	return stream.str();
}

string Customer::toTable() const {
	string type;
	if (getType() == 'u' || getType() == 'U')
		type = "Customer";
	else
		type = "Company";
	ostringstream stream;
	stream << getName() << setw(NAME) << getAddress() << setw(ADDRESS) << type;
	return stream.str();
}

void Customer::toFile(ofstream& outFile, int* pos) {
	outFile.seekp(*pos);
	outFile.write(reinterpret_cast<char*>(this), sizeof(Customer));
	*pos = outFile.tellp();
}

void Customer::fromFile(ifstream& inFile, int* pos) {
	inFile.seekg(*pos);
	if (inFile.peek() != EOF)
	{
		inFile.read(reinterpret_cast<char*>(this), sizeof(Customer));
		*pos = inFile.tellg();
	}
}