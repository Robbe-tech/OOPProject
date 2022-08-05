#ifndef TIRECENTER_H
#define TIRECENTER_H
#define ARTIKELEN 50
#define KLANTEN 50

#include <string>
#include <array>

#include "company.h"
#include "rim.h"
#include "tire.h"

class tireCenter {
public:
	tireCenter(string&, string&, array<article, ARTIKELEN>&, array<customer, KLANTEN>&);
	virtual ~tireCenter() = default;

	void setName(string&);
	string getName() const;

	void setAddress(string&);
	string getAddress() const;

	void setArticles(array<article, ARTIKELEN>&);
	array<article, ARTIKELEN> getArticles() const;

	void setCustomers(array<customer, KLANTEN>&);
	array<customer, KLANTEN> getCustomers() const;
private:
	char name[NAME];
	char address[ADDRESS];
	array<article, ARTIKELEN> articles;
	array<customer, KLANTEN> customers;
};

#endif