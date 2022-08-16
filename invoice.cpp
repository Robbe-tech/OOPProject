#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "Invoice.h"

Invoice::Invoice(Customer klant, array<Article, ARTIEKELEN>& artiekels, float prijs, int korting) : customers(klant), articles(artiekels) {
	setCustomer(klant);
	setArticles(artiekels);
	setPrice(prijs);
	setDiscount(korting);
}

void Invoice::setCustomer(Customer klant) {
	customers = klant;
}

Customer Invoice::getCustomer(){
	return Invoice::customers;
}

void Invoice::setArticles(array<Article, ARTIEKELEN>& artiekels) {
	articles = artiekels;
}
std::array<Article, ARTIEKELEN> Invoice::getArticles() const {
	return articles;
}

void Invoice::setPrice(float prijs) {
	price = prijs;
}
float Invoice::getPrice() const {
	return price;
}

void Invoice::setDiscount(int korting) {
	discount = korting;
}
int Invoice::getDiscount() const {
	return discount;
}

float Invoice::calculateDiscount() {
	float totdis = ((100 - discount) * price) / 100;
	return totdis;
}
float Invoice::calculatePrice() {
	float totprice = price - calculateDiscount();
	return totprice;
}

string Invoice::toString() const {
	ostringstream stream;
	int i = 0;
	stream << "Customer:" << endl << customers.toString() << endl << endl << left << setw(20) << "Total Price: " << setprecision(2) << fixed << showpoint << getPrice() << endl << setw(20) << "Discount: " << getDiscount() << "%" << endl
		<< endl << "Articles:" << endl << setw(3) << "ID" << setw(CHAR) << "Name" << setw(CHAR) << "Manufacturer" << setw(10) << "Stock" << setw(10) << "Diameter" << setw(10) << "Price" << "Type" << endl;
	while (articles[i].getType() != '\0' && i < ARTIEKELEN) {
		stream << (i + 1) << setw(3) << articles[i].toTable() << endl;
		i++;
	}
	return stream.str();
}

string Invoice::toTable() const {
	ostringstream stream;
	stream << left << setw(NAME) << customers.getName() << setw(CHAR) << articles[0].getName() << setw(10) << setprecision(2) << fixed << showpoint << getPrice() << getDiscount();
	return stream.str();
}

void Invoice::toFile(ofstream& outFile) {
	int i;
	streamoff loc = outFile.tellp();
	customers.toFile(outFile, &loc);
	for (i = 0; i < ARTIEKELEN; i++) {
		articles[i].toFile(outFile, &loc);
	}
	outFile.write((char*)&price, sizeof(float));
	outFile.write((char*)&discount, sizeof(int));
}

void Invoice::fromFile(ifstream& inFile) {
	if (inFile.peek() != EOF)
	{
		int i;
		streamoff loc = inFile.tellg();
		customers.fromFile(inFile, &loc);
		for (i = 0; i < ARTIEKELEN; i++) {
			articles[i].fromFile(inFile, &loc);
		}
		inFile.read((char*)&price, sizeof(float));
		inFile.read((char*)&discount, sizeof(int));
	}
}