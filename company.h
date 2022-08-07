#ifndef COMPANY_H
#define COMPANY_H
#define VATNUM 15

#include <string>
#include "customer.h"

class company : public customer{
public:
	company(const string&, string&, char, string&, int);
	virtual ~company() = default;

	void setVAT(string&);
	string getVAT() const;

	void setVolumeDiscount(int);
	int getVolumeDiscount() const;

	virtual string toString() const override;
	virtual string toTable() const override;

	virtual void toFile(const static string&, int*) override;
	virtual void fromFile(const static string&, int*) override;
private:
	char VAT[VATNUM];
	int volumeDiscount;
};

#endif