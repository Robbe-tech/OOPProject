#ifndef INVOICE_H
#define INVOICE_H
#define ARTIKELEN 50

#include <string>
#include <array>
#include "company.h"
#include "rim.h"
#include "tire.h"

class invoice{
public:
	invoice(customer&, array<article, ARTIKELEN>&, float, int);
	virtual ~invoice() = default;

	void setCustomer(customer&);
	customer getCustomer();
	
	void setArticles(array<article, ARTIKELEN>&);
	array<article, ARTIKELEN> getArticles() const;

	void setPrice(float);
	float getPrice() const;

	void setDiscount(int);
	int getDiscount() const;

	float calculateDiscount();
	float calculatePrice();
private:
	customer& custom;
	array<article, ARTIKELEN>& articles;
	float price;
	int discount;
};

#endif