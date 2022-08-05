#include "invoice.h"

invoice::invoice(customer& customers, array<article, ARTIKELEN>& artiekels, float prijs, int korting) : custom(customers), articles(artiekels) {
	/*setCustomer(customers);
	setArticles(artiekels);*/
	setPrice(prijs);
	setDiscount(korting);
}

/*void invoice::setCustomer(customer& customers) {
	custom(customers);
}*/
customer invoice::getCustomer(){
	return invoice::custom;
}

/*void invoice::setArticles(array<article, ARTIKELEN>& artiekels) {
	int i = 0;
	while (artiekels[i].getName() != "")
	{
		articles[i](artiekels[i]);
		i++;
	}
}*/
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