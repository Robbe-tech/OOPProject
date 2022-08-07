#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "tireCenter.h"

tireCenter::tireCenter(string& naam, string& adres, array<article, ARTIEKELEN>& artiekels, array<customer, KLANTEN>& klanten) : articles(artiekels), customers(klanten) {
	setName(naam);
	setAddress(adres);
	setArticles(artiekels);
	setCustomers(klanten);
}

void tireCenter::setName(string& naam) {
	size_t length{ naam.size() };
	length = (length < NAME ? length : (NAME - 1));
	naam.copy(name, length);
	name[length] = '\0';
}
string tireCenter::getName() const {
	return name;
}

void tireCenter::setAddress(string& adres) {
	size_t length{ adres.size() };
	length = (length < ADDRESS ? length : (ADDRESS - 1));
	adres.copy(address, length);
	adres[length] = '\0';
}
string tireCenter::getAddress() const {
	return address;
}

void tireCenter::setArticles(array<article, ARTIEKELEN>& artiekels) {
	int i = 0;
	while (artiekels[i].getType() != '\0' && i < ARTIEKELEN)
	{
		articles[i] = article(artiekels[i]);
		i++;
	}
}
array<article, ARTIEKELEN> tireCenter::getArticles() const {
	return articles;
}

void tireCenter::setCustomers(array<customer, KLANTEN>& klant) {
	int i = 0;
	while (klant[i].getType() != '\0' && i < KLANTEN)
	{
		tireCenter::customers[i] = customer(klant[i]);
		i++;
	}
}
array<customer, KLANTEN> tireCenter::getCustomers() const {
	return customers;
}

string tireCenter::toString() const {
	ostringstream stream;
	int id, i = 0;
	stream << "Name: " << setw(20) << getName() << "\nAddress: " << setw(20) << getAddress() << "\nArticles:\n"
		<< "ID" << setw(3) << "Name" << setw(CHAR) << "Manufacturer" << setw(CHAR) << "Stock" << setw(10) << "Diameter" << setw(10) << "Price" << setw(10) << "Type" << setw(5) << "Width" << setw(10) << "Height/Aluminum" << setw(20) << "Color/Season" << setw(20) << "SpeedIndex\n";
	while (articles[i].getType() != '\0' && i < ARTIEKELEN) {
		id = i + 1;
		stream << id << setw(3) << articles[i].toTable() << "\n";
		i++;
	}
	i = 0;
	stream << "\nCustomers\n" << "ID" << setw(3) << "Name" << setw(NAME) << "Address" << setw(ADDRESS) << "Type" << setw(10) << "VAT" << setw(VATNUM) << "VolumeDiscount\n";
	while (customers[i].getType() != '\0' && i < KLANTEN) {
		id = i + 1;
		stream << id << setw(3) << customers[i].toTable() << "\n";
		i++;
	}
	return stream.str();
}

string tireCenter::toTable() const {
	ostringstream stream;
	stream << getName() << setw(NAME) << getAddress() << setw(ADDRESS) << articles[0].getName() << setw(CHAR) << customers[0].getName();
	return stream.str();
}

void tireCenter::toFile(const static string& file, int* pos) {
	ofstream outFile{ file, ios::out | ios::binary };

	if (!outFile) {
		cerr << "File could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	outFile.seekp(*pos);
	outFile.write(reinterpret_cast<char*>(this), sizeof(tireCenter));
	*pos = outFile.tellp();
}

void tireCenter::fromFile(const static string& file, int* pos) {
	ifstream inFile{ file, ios::in | ios::binary };

	if (!inFile) {
		cerr << "File could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	inFile.seekg(*pos);
	inFile.read(reinterpret_cast<char*>(this), sizeof(tireCenter));
	*pos = inFile.tellg();
}