#ifndef COMPANY_H
#define COMPANY_H
#define VATNUM 15

#include <string>
#include "Customer.h"

class Company : public Customer{
public:
	Company(const string& = "", const string& = "", char = '\0', const string& = "", int = NULL);
	virtual ~Company() = default;

	void setVAT(const string&);
	string getVAT() const;

	void setVolumeDiscount(int);
	int getVolumeDiscount() const;

	virtual string toString() const override;
	virtual string toTable() const override;

	virtual void toFile(ofstream&, streamoff*) override;
	virtual void fromFile(ifstream&, streamoff*) override;
private:
	char VAT[VATNUM];
	int volumeDiscount;
};

#endif