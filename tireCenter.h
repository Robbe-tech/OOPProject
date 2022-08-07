#ifndef TIRECENTER_H
#define TIRECENTER_H
#define ARTIEKELEN 50
#define KLANTEN 50

#include <string>
#include <array>

#include "company.h"
#include "rim.h"
#include "tire.h"

class tireCenter {
public:
	tireCenter(string&, string&, array<article, ARTIEKELEN>&, array<customer, KLANTEN>&);
	virtual ~tireCenter() = default;

	void setName(string&);
	string getName() const;

	void setAddress(string&);
	string getAddress() const;

	void setArticles(array<article, ARTIEKELEN>&);
	array<article, ARTIEKELEN> getArticles() const;

	void setCustomers(array<customer, KLANTEN>&);
	array<customer, KLANTEN> getCustomers() const;

	string toString() const;
	string toTable() const;

	void toFile(const static string&, int*);
	void fromFile(const static string&, int*);
private:
	char name[NAME];
	char address[ADDRESS];
	array<article, ARTIEKELEN>& articles;
	array<customer, KLANTEN>& customers;
};

#endif