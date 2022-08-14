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
	float totdis = (100 - discount) * price / 100;
	return totdis;
}
float Invoice::calculatePrice() {
	float totprice = price - calculateDiscount();
	return totprice;
}

string Invoice::toString() const {
	ostringstream stream;
	int i = 0;
	stream << "Customer:" << endl << customers.toString() << endl << endl << "Total Price: " << setw(20) << setprecision(2) << fixed << showpoint << getPrice() << endl << "Discount: " << setw(20) << setprecision(2) << fixed << showpoint << getDiscount() << endl << endl << "Articles:" << endl
		<< "ID" << setw(3) << "Name" << setw(CHAR) << "Manufacturer" << setw(CHAR) << "Stock" << setw(10) << "Diameter" << setw(10) << "Price" << setw(10) << "Type" << endl;
	while (articles[i].getType() != '\0' && i < ARTIEKELEN) {
		stream << (i + 1) << setw(3) << articles[i].toTable() << endl;
		i++;
	}
	return stream.str();
}

string Invoice::toTable() const {
	ostringstream stream;
	stream << customers.getName() << setw(NAME) << articles[0].getName() << setw(CHAR) << setprecision(2) << fixed << showpoint << getPrice() << setw(10) << setprecision(2) << fixed << showpoint << getDiscount();
	return stream.str();
}

void Invoice::toFile(ofstream& outFile, int loc) {
	outFile.seekp(loc);
	outFile.write(reinterpret_cast<char*>(this), sizeof(Invoice));
}

void Invoice::fromFile(ifstream& inFile) {
	if (inFile.peek() != EOF)
	{
		inFile.read(reinterpret_cast<char*>(this), sizeof(Invoice));
	}
}