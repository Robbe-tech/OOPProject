#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "Company.h"

Company::Company(const string& naam, string& adres, char typ, string& vat, int korting) : Customer(naam, adres, typ) {
	setVAT(vat);
	setVolumeDiscount(korting);
}

void Company::setVAT(string& vat) {
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
	stream << Customer::toString << "\nVAT: " << setw(20) << getVAT() << "\nVolume Discount: " << setw(20) << getVolumeDiscount();
	return stream.str();
}

string Company::toTable() const {
	ostringstream stream;
	stream << Customer::toTable << setw(10) << getVAT() << setw(VATNUM) << getAddress();
	return stream.str();
}

void Company::toFile(ofstream outFile, int* pos) {
	outFile.seekp(*pos);
	outFile.write(reinterpret_cast<char*>(this), sizeof(Company));
	*pos = outFile.tellp();
}

void Company::fromFile(ifstream inFile, int* pos) {
	inFile.seekg(*pos);
	inFile.read(reinterpret_cast<char*>(this), sizeof(Company));
	*pos = inFile.tellg();
}