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