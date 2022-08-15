#ifndef CUSTOMER_H
#define CUSTOMER_H
#define NAME 15
#define ADDRESS 30

#ifndef IOSTREAM
#include <iostream>
#include <fstream>
#endif

#include <string>

using namespace std;

class Customer {
public:
	Customer(const string&, const  string&, const char);
	virtual ~Customer() = default;

	void setName(const string&);
	string getName() const;

	void setAddress(const string&);
	string getAddress() const;

	void setType(const char);
	char getType() const;

	virtual string toString() const;
	virtual string toTable() const;

	virtual void toFile(ofstream&, streamoff*);
	virtual void fromFile(ifstream&, streamoff*);
private:
	char name[NAME];
	char address[ADDRESS];
	char type;
};

#endif