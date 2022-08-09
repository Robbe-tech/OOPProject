#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "Invoice.h"

Invoice::Invoice(Customer& klant, array<Article&, ARTIEKELEN>& artiekels, float prijs, int korting) : customers(klant), articles(artiekels) {
	setCustomer(klant);
	setArticles(artiekels);
	setPrice(prijs);
	setDiscount(korting);
}

void Invoice::setCustomer(Customer& klant) {
	customers = klant;
}

Customer Invoice::getCustomer(){
	return Invoice::customers;
}

void Invoice::setArticles(array<Article&, ARTIEKELEN>& artiekels) {
	articles = artiekels;
}
std::array<Article&, ARTIEKELEN> Invoice::getArticles() const {
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
	float totprice = price - (100 - discount) * price / 100;
	return totprice;
}

string Invoice::toString() const {
	ostringstream stream;
	int id, i = 0;
	stream << customers.toString() << "\nTotal Price: " << setw(20) << getPrice() << "\nDiscount: " << setw(20) << getDiscount() << "\nArticles:\n"
		<< "ID" << setw(3) << "Name" << setw(CHAR) << "Manufacturer" << setw(CHAR) << "Stock" << setw(10) << "Diameter" << setw(10) << "Price" << setw(10) << "Type" << setw(5) << "Width" << setw(10) << "Height/Aluminum" << setw(20) << "Color/Season" << setw(20) << "SpeedIndex\n";
	while (articles[i].getType() != '\0' && i < ARTIEKELEN) {
		id = i + 1;
		stream << id << setw(3) << articles[i].toTable() << "\n";
		i++;
	}
	return stream.str();
}

string Invoice::toTable() const {
	ostringstream stream;
	stream << customers.getName() << setw(NAME) << articles[0].getName() << setw(CHAR) << getPrice() << getDiscount;
	return stream.str();
}

void Invoice::toFile(ofstream& outFile) {
	outFile.write(reinterpret_cast<char*>(this), sizeof(Invoice));
}

void Invoice::fromFile(ifstream& inFile) {
	if (inFile.peek() != EOF)
	{
		inFile.read(reinterpret_cast<char*>(this), sizeof(Invoice));
	}
}