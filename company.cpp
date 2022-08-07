#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "company.h"

company::company(const string& naam, string& adres, char typ, string& vat, int korting) : customer(naam, adres, typ) {
	setVAT(vat);
	setVolumeDiscount(korting);
}

void company::setVAT(string& vat) {
	size_t length{ vat.size() };
	length = (length < VATNUM ? length : (VATNUM - 1));
	vat.copy(VAT, length);
	VAT[length] = '\0';
}
string company::getVAT() const {
	return VAT;
}

void company::setVolumeDiscount(int korting) {
	volumeDiscount = korting;
}
int company::getVolumeDiscount() const {
	return volumeDiscount;
}

string company::toString() const {
	ostringstream stream;
	stream << customer::toString << "\nVAT: " << setw(20) << getVAT() << "\nVolume Discount: " << setw(20) << getVolumeDiscount();
	return stream.str();
}

string company::toTable() const {
	ostringstream stream;
	stream << customer::toTable << setw(10) << getVAT() << setw(VATNUM) << getAddress();
	return stream.str();
}

void company::toFile(const static string& file, static int pos) {
	ofstream outFile{ file, ios::out | ios::binary };

	if (!outFile) {
		cerr << "File could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	outFile.seekp(pos);
	outFile.write(reinterpret_cast<char*>(this), sizeof(company));
	pos = outFile.tellp();
}

void company::fromFile(const static string& file, static int pos) {
	ifstream inFile{ file, ios::in | ios::binary };

	if (!inFile) {
		cerr << "File could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	inFile.seekg(pos);
	inFile.read(reinterpret_cast<char*>(this), sizeof(company));
	pos = inFile.tellg();
}