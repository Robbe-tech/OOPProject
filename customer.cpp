#include "customer.h"

customer::customer(const string& naam,const string& adres, const char typ) {
	setName(naam);
	setAddress(adres);
	setType(typ);
}

void customer::setName(const string & naam) {
	size_t length{ naam.size() };
	length = (length < NAME ? length : (NAME - 1));
	naam.copy(name, length);
	name[length] = '\0';
}
std::string customer::getName() const {
	return name;
}

void customer::setAddress(const string & adres) {
	size_t length{ adres.size() };
	length = (length < ADDRESS ? length : (ADDRESS - 1));
	adres.copy(address, length);
	address[length] = '\0';
}
string customer::getAddress() const {
	return address;
}

void customer::setType(const char typ) {
	type = typ;
}
char customer::getType() const {
	return type;
}