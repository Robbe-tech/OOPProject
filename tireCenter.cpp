#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "TireCenter.h"

TireCenter::TireCenter(const string& naam, const string& adres, array<Article, ARTIEKELEN>& artiekels, array<Customer, KLANTEN>& klanten) : articles(artiekels), customers(klanten) {
	setName(naam);
	setAddress(adres);
	setArticles(artiekels);
	setCustomers(klanten);
}

void TireCenter::setName(const string& naam) {
	size_t length{ naam.size() };
	length = (length < NAME ? length : (NAME - 1));
	naam.copy(name, length);
	name[length] = '\0';
}
string TireCenter::getName() const {
	return name;
}

void TireCenter::setAddress(const string& adres) {
	size_t length{ adres.size() };
	length = (length < ADDRESS ? length : (ADDRESS - 1));
	adres.copy(address, length);
	address[length] = '\0';
}
string TireCenter::getAddress() const {
	return address;
}

void TireCenter::setArticles(array<Article, ARTIEKELEN>& artiekels) {
	articles = artiekels;
}
array<Article, ARTIEKELEN> TireCenter::getArticles() const {
	return articles;
}

void TireCenter::setCustomers(array<Customer, KLANTEN>& klant) {
	customers = klant;
}
array<Customer, KLANTEN> TireCenter::getCustomers() const {
	return customers;
}

string TireCenter::toString() const {
	ostringstream stream;
	int i = 0;
	stream << setw(20) << "Name: " << getName() << endl << setw(20) << "Address: " << getAddress() << endl << endl << "Articles:" << endl
		<< setw(3) << "ID" << setw(CHAR) << "Name" << setw(CHAR) << "Manufacturer" << setw(10) << "Stock" << setw(10) << "Diameter" << setw(10) << "Price" << "Type" << endl;
	while (articles[i].getType() != '\0' && i < ARTIEKELEN) {
		stream << setw(3) << (i + 1) << articles[i].toTable() << endl;
		i++;
	}
	i = 0;
	stream << endl << "Customers:" << endl << setw(3) << "ID" << setw(NAME) << "Name" << setw(ADDRESS) << "Address" << "Type" << endl;
	while (customers[i].getType() != '\0' && i < KLANTEN) {
		stream << setw(3) << (i + 1) << customers[i].toTable() << endl;
		i++;
	}
	return stream.str();
}

string TireCenter::toTable() const {
	ostringstream stream;
	stream << getName() << setw(NAME) << getAddress() << setw(ADDRESS) << articles[0].getName() << setw(CHAR) << customers[0].getName();
	return stream.str();
}

void TireCenter::toFile(ofstream& outFile) {
	int i;
	streamoff loc;

	outFile.write((char*)name, sizeof(char[NAME]));
	outFile.write((char*)address, sizeof(char[ADDRESS]));
	loc = outFile.tellp();

	for (i = 0; i < KLANTEN; i++) {
		customers[i].toFile(outFile, &loc);
	}

	for (i = 0; i < ARTIEKELEN; i++) {
		articles[i].toFile(outFile, &loc);
	}
}

void TireCenter::fromFile(ifstream& inFile) {
	if (inFile.peek() != EOF)
	{
		int i;
		streamoff loc;

		inFile.read((char*)name, sizeof(char[NAME]));
		inFile.read((char*)address, sizeof(char[ADDRESS]));
		loc = inFile.tellg();

		for (i = 0; i < KLANTEN; i++) {
			customers[i].fromFile(inFile, &loc);
		}

		for (i = 0; i < ARTIEKELEN; i++) {
			articles[i].fromFile(inFile, &loc);
		}
	}
}