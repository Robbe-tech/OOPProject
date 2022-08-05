#ifndef CUSTOMER_H
#define CUSTOMER_H
#define NAME 15
#define ADDRESS 30

#include <string>

using namespace std;

class customer {
public:
	customer(const string&, const  string&, const char);
	virtual ~customer() = default;

	void setName(const string&);
	string getName() const;

	void setAddress(const string&);
	string getAddress() const;

	void setType(const char);
	char getType() const;
private:
	char name[NAME];
	char address[ADDRESS];
	char type;
};

#endif