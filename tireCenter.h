#ifndef TIRECENTER_H
#define TIRECENTER_H
#define ARTIEKELEN 50
#define KLANTEN 50

#include <string>
#include <array>

#include "Company.h"
#include "Rim.h"
#include "Tire.h"

class TireCenter {
public:
	TireCenter(const string&, const string&, array<Article&, ARTIEKELEN>&, array<Customer&, KLANTEN>&);
	virtual ~TireCenter() = default;

	void setName(const string&);
	string getName() const;

	void setAddress(const string&);
	string getAddress() const;

	void setArticles(array<Article&, ARTIEKELEN>&);
	array<Article&, ARTIEKELEN> getArticles() const;

	void setCustomers(array<Customer&, KLANTEN>&);
	array<Customer&, KLANTEN> getCustomers() const;

	string toString() const;
	string toTable() const;

	void toFile(ofstream&);
	void fromFile(ifstream&);
private:
	char name[NAME];
	char address[ADDRESS];
	array<Article&, ARTIEKELEN>& articles;
	array<Customer&, KLANTEN>& customers;
};

#endif