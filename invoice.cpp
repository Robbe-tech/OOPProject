#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "invoice.h"

invoice::invoice(customer& customers, array<article, ARTIKELEN>& artiekels, float prijs, int korting) : custom(customers), articles(artiekels) {
	setCustomer(customers);
	setArticles(artiekels);
	setPrice(prijs);
	setDiscount(korting);
}

void invoice::setCustomer(customer& customers) {
	if (customers.getType() == 'u' || customers.getType() == 'U') {
		custom(customers);
	}
	else {
		custom = company(customers)
	}
}

customer invoice::getCustomer(){
	return invoice::custom;
}

void invoice::setArticles(array<article, ARTIKELEN>& artiekels) {
	int i = 0;
	while (artiekels[i].getType() != '\0')
	{
		invoice::articles[i](artiekels[i]);
		i++;
	}
}
std::array<article, ARTIKELEN> invoice::getArticles() const {
	return articles;
}

void invoice::setPrice(float prijs) {
	price = prijs;
}
float invoice::getPrice() const {
	return price;
}

void invoice::setDiscount(int korting) {
	discount = korting;
}
int invoice::getDiscount() const {
	return discount;
}

float invoice::calculateDiscount() {
	float totdis = (100 - invoice::discount) * price / 100;
	return totdis;
}
float invoice::calculatePrice() {
	float totprice = price - (100 - discount) * price / 100;
	return totprice;
}

string invoice::toString() const {
	ostringstream stream;
	int id, i = 0;
	stream << custom.toString() << "\nTotal Price: " << setw(20) << getPrice() << "\nDiscount: " << setw(20) << getDiscount() << "\nArticles: \n"
		<< "ID" << setw(3) << "Name" << setw(CHAR) << "Manufacturer" << setw(CHAR) << "Stock" << setw(10) << "Diameter" << setw(10) << "Price" << setw(10) << "Type" << setw(5) << "Width" << setw(10) << "Height/Aluminum" << setw(20) << "Color/Season" << setw(20) << "SpeedIndex";
	while (articles[i].getType() != '\0' && i < ARTIKELEN) {
		id = i + 1;
		stream << id << setw(3) << articles[i].toTable();
		i++;
	}
	return stream.str();
}

string invoice::toTable() const {
	ostringstream stream;
	stream << custom.getName() << setw(NAME) << articles[0].getName() << setw(CHAR) << getPrice() << getDiscount;
	return stream.str();
}

void invoice::toFile(const static string& file, static int pos) {
	ofstream outFile{ file, ios::out | ios::binary };

	if (!outFile) {
		cerr << "File could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	outFile.seekp(pos);
	outFile.write(reinterpret_cast<char*>(this), sizeof(invoice));
	pos = outFile.tellp();
}

void invoice::fromFile(const static string& file, static int pos) {
	ifstream inFile{ file, ios::in | ios::binary };

	if (!inFile) {
		cerr << "File could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	inFile.seekg(pos);
	inFile.read(reinterpret_cast<char*>(this), sizeof(invoice));
	pos = inFile.tellg();
}