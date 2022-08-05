#include <sstream>
#include <iomanip>
#include "rim.h"

rim::rim(const string& naam, const string& fabrikant, int vooraad, const int dia, float prijs, const char typ, const bool aluminium, const string& kleur, const int breedte) :article(naam, fabrikant, vooraad, dia, prijs, typ) {
	setAluminum(aluminium);
	setColor(kleur);
	setWidth(breedte);
}

void rim::setAluminum(const bool aluminium) {
	aluminum = aluminium;
}
int rim::getAluminum() const {
	return aluminum;
}

void rim::setColor(const string & kleur) {
	size_t length{ kleur.size() };
	length = (length < COLOR ? length : (COLOR - 1));
	kleur.copy(color, length);
	color[length] = '\0';
}
std::string rim::getColor() const {
	return color;
}

void rim::setWidth(const int breedte) {
	width = breedte;
}
int rim::getWidth() const {
	return width;
}

string rim::toString() const {
	string alu;
	if (getAluminum())
		alu = "True";
	else
		alu = "False";
	ostringstream stream;
	stream << article::toString() << "\nAluminum: " << setw(20) << alu << "\nColor" << setw(20) << getColor() << "\nWidth" << setw(20) << getWidth();
	return stream.str();
}

string rim::toTable() const {
	string alu;
	if (getAluminum())
		alu = "True";
	else
		alu = "False";
	ostringstream stream;
	stream << article::toTable() << setw(5) << getWidth() << setw(10) << alu << setw(20) << getColor();
	return stream.str();
}