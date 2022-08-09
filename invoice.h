#ifndef INVOICE_H
#define INVOICE_H
#define ARTIEKELEN 50

#include <string>
#include <array>
#include "Company.h"
#include "Rim.h"
#include "Tire.h"

class Invoice{
public:
	Invoice(Customer&, array<Article&, ARTIEKELEN>&, float, int);
	virtual ~Invoice() = default;

	void setCustomer(Customer&);
	Customer getCustomer();
	
	void setArticles(array<Article&, ARTIEKELEN>&);
	array<Article&, ARTIEKELEN> getArticles() const;

	void setPrice(float);
	float getPrice() const;

	void setDiscount(int);
	int getDiscount() const;

	float calculateDiscount();
	float calculatePrice();

	string toString() const;
	string toTable() const;

	void toFile(ofstream&);
	void fromFile(ifstream&);
private:
	Customer& customers;
	array<Article&, ARTIEKELEN>& articles;
	float price;
	int discount;
};

#endif