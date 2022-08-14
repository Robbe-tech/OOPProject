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
	stream << "Name: " << setw(20) << getName() << endl << "Address: " << setw(20) << getAddress() << endl << endl << "Articles:" << endl
		<< "ID" << setw(3) << "Name" << setw(CHAR) << "Manufacturer" << setw(CHAR) << "Stock" << setw(10) << "Diameter" << setw(10) << "Price" << setw(10) << "Type" << endl;
	while (articles[i].getType() != '\0' && i < ARTIEKELEN) {
		stream << (i + 1) << setw(3) << articles[i].toTable() << endl;
		i++;
	}
	i = 0;
	stream << endl << "Customers:" << endl << "ID" << setw(3) << "Name" << setw(NAME) << "Address" << setw(ADDRESS) << "Type" << endl;
	while (customers[i].getType() != '\0' && i < KLANTEN) {
		stream << (i + 1) << setw(3) << customers[i].toTable() << endl;
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
	outFile.write(reinterpret_cast<char*>(this), sizeof(TireCenter));
}

void TireCenter::fromFile(ifstream& inFile) {
	if (inFile.peek() != EOF)
	{
		inFile.read(reinterpret_cast<char*>(this), sizeof(TireCenter));
	}
}