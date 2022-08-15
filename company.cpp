#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "Company.h"

Company::Company(const string& naam, const string& adres, char typ, const string& vat, int korting) : Customer(naam, adres, typ) {
	setVAT(vat);
	setVolumeDiscount(korting);
}

void Company::setVAT(const string& vat) {
	size_t length{ vat.size() };
	length = (length < VATNUM ? length : (VATNUM - 1));
	vat.copy(VAT, length);
	VAT[length] = '\0';
}
string Company::getVAT() const {
	return VAT;
}

void Company::setVolumeDiscount(int korting) {
	volumeDiscount = korting;
}
int Company::getVolumeDiscount() const {
	return volumeDiscount;
}

string Company::toString() const {
	ostringstream stream;
	stream << Customer::toString() << endl << "VAT: " << setw(20) << getVAT() << endl << "Volume Discount: " << setw(20) << getVolumeDiscount();
	return stream.str();
}

string Company::toTable() const {
	ostringstream stream;
	stream << Customer::toTable() << setw(10) << getVAT() << setw(VATNUM) << getAddress();
	return stream.str();
}

void Company::toFile(ofstream& outFile, streamoff* pos) {
	outFile.seekp(*pos);
	outFile.write(reinterpret_cast<char*>(this), sizeof(Company));
	*pos = outFile.tellp();
}

void Company::fromFile(ifstream& inFile, streamoff* pos) {
	inFile.seekg(*pos);
	if (inFile.peek() != EOF)
	{
		inFile.read(reinterpret_cast<char*>(this), sizeof(Company));
		*pos = inFile.tellg();
	}
}