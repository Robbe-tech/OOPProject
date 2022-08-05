#include "tireCenter.h"

tireCenter::tireCenter(string& naam, string& adres, array<article, ARTIKELEN>& artiekels, array<customer, KLANTEN>& klant) {
	setName(naam);
	setAddress(adres);
	setArticles(artiekels);
	setCustomers(klant);
}

void tireCenter::setName(string & naam) {
	size_t length{ naam.size() };
	length = (length < NAME ? length : (NAME - 1));
	naam.copy(name, length);
	name[length] = '\0';
}
string tireCenter::getName() const {
	return name;
}

void tireCenter::setAddress(string & adres) {
	size_t length{ adres.size() };
	length = (length < ADDRESS ? length : (ADDRESS - 1));
	adres.copy(address, length);
	adres[length] = '\0';
}
string tireCenter::getAddress() const {
	return address;
}

void tireCenter::setArticles(array<article, ARTIKELEN>&artiekels) {
	int i = 0;

	while (artiekels[i].getName() != "")
	{
		articles[i].setName(artiekels[i].getName());
		articles[i].setManufacturer(artiekels[i].getManufacturer());
		articles[i].setStock(artiekels[i].getStock());
		articles[i].setDiameter(artiekels[i].getDiameter());
		articles[i].setPrice(artiekels[i].getPrice());
		articles[i].setType(artiekels[i].getType());
		i++;
	}
}
array<article, ARTIKELEN> tireCenter::getArticles() const {
	return articles;
}

void tireCenter::setCustomers(array<customer, KLANTEN>&klant) {
	int j = 0;
	while (klant[j].getName() != "")
	{
		customers[j].setName(klant[j].getName());
		customers[j].setAddress(klant[j].getAddress());
		customers[j].setType(klant[j].getType());
		j++;
	}
}
array<customer, KLANTEN> tireCenter::getCustomers() const {
	return customers;
}