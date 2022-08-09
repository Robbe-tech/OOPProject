#ifndef COMPANY_H
#define COMPANY_H
#define VATNUM 15

#include <string>
#include "Customer.h"

class Company : public Customer{
public:
	Company(const string&, const string&, char, const string&, int);
	virtual ~Company() = default;

	void setVAT(const string&);
	string getVAT() const;

	void setVolumeDiscount(int);
	int getVolumeDiscount() const;

	virtual string toString() const override;
	virtual string toTable() const override;

	virtual void toFile(ofstream&, int*) override;
	virtual void fromFile(ifstream&, int*) override;
private:
	char VAT[VATNUM];
	int volumeDiscount;
};

#endif