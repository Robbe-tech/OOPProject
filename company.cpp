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
	stream << Customer::toString() << endl << setw(20) << "VAT: " << getVAT() << endl << setw(20) << "Volume Discount: " << getVolumeDiscount();
	return stream.str();
}

string Company::toTable() const {
	ostringstream stream;
	stream << Customer::toTable() << setw(VATNUM) << getVAT() << getAddress();
	return stream.str();
}

void Company::toFile(ofstream& outFile, streamoff* pos) {
	Customer::toFile(outFile, pos);
	outFile.write((char*)VAT, sizeof(char[VATNUM]));
	outFile.write((char*)&volumeDiscount, sizeof(int));
	*pos = outFile.tellp();
}

void Company::fromFile(ifstream& inFile, streamoff* pos) {
	inFile.seekg(*pos);
	if (inFile.peek() != EOF)
	{
		Customer::fromFile(inFile, pos);
		inFile.read((char*)VAT, sizeof(char[VATNUM]));
		inFile.read((char*)&volumeDiscount, sizeof(int));
		*pos = inFile.tellg();
	}
}