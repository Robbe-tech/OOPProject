#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <vector>

#include "article.h"
#include "company.h"
#include "customer.h"
#include "invoice.h"
#include "rim.h"
#include "tire.h"
#include "tireCenter.h"

#define TOTTIRE 50
#define TOTRIMS 50
#define CUSTOMERS 50
#define COMPANIES 10
#define INVOICES 50
#define TIRECENTERS 5
#define LEN 50

using namespace std;

void addarticle(tire tires[TOTTIRE], rim rims[TOTRIMS]);
void searcharticle(tire tires[TOTTIRE], rim rims[TOTRIMS]);
void deletearticle(tire tires[TOTTIRE], rim rims[TOTRIMS]);
void changearticle(tire tires[TOTTIRE], rim rims[TOTRIMS]);
void checkinvoice(invoice invoices[INVOICES]);
void makeorder(tire tires[TOTTIRE], rim rims[TOTRIMS], customer customers[CUSTOMERS], company companies[COMPANIES], invoice invoices[INVOICES]);
void deletecustomer(customer customers[CUSTOMERS], company companies[COMPANIES]);
void searchcustomer(customer customers[CUSTOMERS], company companies[COMPANIES]);
void changecustomer(customer customers[CUSTOMERS], company companies[COMPANIES]);
void addcustomer(customer customers[CUSTOMERS], company companies[COMPANIES]);
void updatestock(tire tires[TOTTIRE], rim rims[TOTRIMS]);
void update(tire tires[TOTTIRE], rim rims[TOTRIMS], article artikel, int change);
int isSubstring(string s1, string s2);


int main(void) {
	const static string articleFile = "Articles.dat", customerFile = "Customers.dat", invoiceFile = "Invoices.dat", tireCenterFile = "TireCenters.dat";
	static int articlePos = 0, customerPos = 0, invoicePos = 0, tireCenterPos = 0;
	tire tires[TOTTIRE];
	rim rims[TOTRIMS];
	customer customers[CUSTOMERS];
	company companies[COMPANIES];
	invoice invoices[INVOICES];
	tireCenter tirecenters[TIRECENTERS];

	char employee, option = 'l';

	cout << "Are you the owner (o) or employee (e)?" << std::endl;
	cin >> employee;
	while (!(employee == 'e' || employee == 'o'))
	{
		cout << "Please give a valid option o or e: ";
		cin >> employee;
	}

	while (option != 'e')
	{
		if (employee == 'o')
		{
			cout << "Choose between adding an article (a), searching articles (s), deleting an article (d), changing an article (c), checking invoices (i), placing an order (p), deleting customers (b), searching customers (m), changing customers (h), adding customers(n) and updating stock (u) and exiting (e)";
			cin >> option;
		}
		else
		{
			cout << "Choose between searching articles (s), changing an article (c), checking invoices (i), placing an order (p), searching customers (m), changing customers (h), adding customers(n) and updating stock (u) and exiting (e)";
			cin >> option;
		}

		if (option == 'a' && employee == 'o')
		{
			addarticle(tires, rims);
		}
		if (option == 's')
		{
			searcharticle(tires, rims);
		}
		if (option == 'd' && employee == 'o')
		{
			deletearticle(tires, rims);
		}
		if (option == 'c')
		{
			changearticle(tires, rims);
		}
		if (option == 'i')
		{
			checkinvoice(invoices);
		}
		if (option == 'p')
		{
			makeorder(tires, rims, customers, companies, invoices);
		}
		if (option == 'b' && employee == 'o')
		{
			deletecustomer(customers, companies);
		}
		if (option == 'm')
		{
			searchcustomer(customers, companies);
		}
		if (option == 'h')
		{
			changecustomer(customers, companies);
		}
		if (option == 'n')
		{
			addcustomer(customers, companies);
		}
		if (option == 'u')
		{
			updatestock(tires, rims);
		}
	}

	return 0;
}

void addarticle(tire tires[TOTTIRE], rim rims[TOTRIMS])
{
	int i, stock, diameter, width, height, alu;
	float price;
	char search = 'd', choice, season, type;
	std::string name, manufacturer, colorspeed;
	bool occured, aluminum;
	cout << "Do you wish to search for an article (s) or just start (any other letter)?" <<endl;
	cin >> search;

	if (search == 's')
	{
		searcharticle(tires, rims);
	}

	while (search != 'e')
	{
		cout << "Do you wish to add a tire (t), rim (r) or exit (e): ";
		cin >> choice;

		if (choice == 't')
		{
			do {
				occured = false;
				i = 0;
				cout << "Enter the name: ";
				cin >> name;
				while (tires[i].getPrice() > 0)
				{
					if (name.compare(tires[i].getName()) == 0)
					{
						cout << "The name you entered is already used" << std::endl;
						occured = false;
					}
					i++;
				}
			} while (occured);
			cout << "Enter the manufacturer: ";
			cin >> manufacturer;
			cout << "Enter the stock: ";
			cin >> stock;
			while (stock < 0)
			{
				cout << "The stock can't be negative: ";
				cin >> stock;
			}
			cout << "Enter the diameter: ";
			cin >> diameter;
			while (diameter <= 0)
			{
				cout << "The diameter must be greater than 0: ";
				cin >> diameter;
			}
			cout << "Enter the price: ";
			cin >> price;
			while (price <= 0)
			{
				cout << "The price must be greater than 0: ";
				cin >> price;
			}
			cout << "Enter the width: ";
			cin >> width;
			while (width <= 0)
			{
				cout << "The width must be greater than 0: ";
				cin >> width;
			}
			cout << "Enter the height: ";
			cin >> height;
			while (height <= 0)
			{
				cout << "The height must be greater than 0: ";
				cin >> height;
			}
			cout << "Enter the speed index: ";
			cin >> colorspeed;
			cout << "Enter the season, summer (s) or winter (w): ";
			cin >> season;
			while (!(season == 's' || season == 'w'))
			{
				cout << "The season must be either summer(s) or winter (w): ";
				cin >> season;
			}
			tires[i].setName(name);
			tires[i].setManufacturer(manufacturer);
			tires[i].setStock(stock);
			tires[i].setDiameter(diameter);
			tires[i].setPrice(price);
			tires[i].setType(type);
			tires[i].setWidth(width);
			tires[i].setHeight(height);
			tires[i].setSpeedIndex(colorspeed);
			tires[i].setSeason(season);
		}
		if (choice == 'r')
		{
			do {
				occured = false;
				i = 0;
				cout << "Enter the name: ";
				cin >> name;
				while (rims[i].getPrice() > 0)
				{
					if (name.compare(rims[i].getName()) == 0)
					{
						cout << "The name you entered is already used" << std::endl;
						occured = false;
					}
					i++;
				}
			} while (occured);
			cout << "Enter the manufacturer: ";
			cin >> manufacturer;
			cout << "Enter the stock: ";
			cin >> stock;
			while (stock < 0)
			{
				cout << "The stock can't be negative: ";
				cin >> stock;
			}
			cout << "Enter the diameter: ";
			cin >> diameter;
			while (diameter <= 0)
			{
				cout << "The diameter must be greater than 0: ";
				cin >> diameter;
			}
			cout << "Enter the price: ";
			cin >> price;
			while (price <= 0)
			{
				cout << "The price must be greater than 0: ";
				cin >> price;
			}
			cout << "Enter the width: ";
			cin >> width;
			while (width <= 0)
			{
				cout << "The width must be greater than 0: ";
				cin >> width;
			}
			cout << "Enter the color: ";
			cin >> colorspeed;
			cout << "Is the rim made of aluminum (1) or not (0): ";
			cin >> alu;
			while (!(alu == 0 || alu == 1))
			{
				cout << "Enter either a 0 (not aluminum) or 1 aluminum: ";
				cin >> alu;
			}
			if (alu == 0)
			{
				aluminum = false;
			}
			else
			{
				aluminum = true;
			}
			rims[i].setName(name);
			rims[i].setManufacturer(manufacturer);
			rims[i].setStock(stock);
			rims[i].setDiameter(diameter);
			rims[i].setPrice(price);
			rims[i].setType(type);
			rims[i].setWidth(width);
			rims[i].setColor(colorspeed);
			rims[i].setAluminum(aluminum);
		}
	}
}

void searcharticle(tire tires[TOTTIRE], rim rims[TOTRIMS])
{
	char detail, type, season, filter, choice = 'l';
	std::string search, name, manufacturer, colorspeed;
	int stock, diameter, size, width, height, i = 0;
	bool aluminum;
	float price;
	ostringstream stream;

	while (choice != 'e')
	{
		cout << "Do you wish to do a normal search (n), do a filtered search (f) or exit (e)?" << std::endl;
		cin >> choice;
		if (choice == 'n')
		{
			cout << "Do you wish to look at all of the items (all), or look for a specific object (just type what you are looking for)?" << std::endl;
			getline(cin, search);
			if (search.compare("all") == 0)
			{
				cout << "Do you wish to see details yes (y), no (any other letter)?" << std::endl;
				cin >> detail;
				if (detail == 'y')
				{
					stream << "Name" << setw(CHAR) << "Manufacturer" << setw(CHAR) << "Stock" << setw(10) << "Diameter" << setw(10) << "Price" << setw(10) << "Type" << setw(5) << "Width" << setw(10) << "Height/Aluminum" << setw(20) << "Color/Season" << setw(20) << "SpeedIndex";
					while (tires[i].getPrice() > 0)
					{
						name = tires[i].getName();
						manufacturer = tires[i].getManufacturer();
						stock = tires[i].getStock();
						diameter = tires[i].getDiameter();
						price = tires[i].getPrice();
						type = tires[i].getType();
						width = tires[i].getWidth();
						height = tires[i].getHeight();
						colorspeed = tires[i].getSpeedIndex();
						season = tires[i].getSeason();
						cout << name << "\t" << manufacturer << "\t" << stock << "\t" << diameter << "\t" << price << "\t" << type << "\t" << width << "\t" << height << "\t" << colorspeed << "\t" << season << std::endl;
						i++;
					}
					i = 0;
					while (rims[i].getPrice() > 0)
					{
						name = rims[i].getName();
						manufacturer = rims[i].getManufacturer();
						stock = rims[i].getStock();
						diameter = rims[i].getDiameter();
						price = rims[i].getPrice();
						type = rims[i].getType();
						width = rims[i].getWidth();
						aluminum = rims[i].getAluminum();
						colorspeed = rims[i].getColor();
						cout << name << "\t" << manufacturer << "\t" << stock << "\t" << diameter << "\t" << price << "\t" << type << "\t" << width << "\t" << aluminum << "\t" << colorspeed << std::endl;
						i++;
					}
					i = 0;
				}
				else
				{
					cout << "Name\tManufacturer\tStock\tDiameter\tPrice\tType" << endl;
					while (tires[i].getPrice() > 0)
					{
						name = tires[i].getName();
						manufacturer = tires[i].getManufacturer();
						stock = tires[i].getStock();
						diameter = tires[i].getDiameter();
						price = tires[i].getPrice();
						type = tires[i].getType();
						cout << name << "\t" << manufacturer << "\t" << stock << "\t" << diameter << "\t" << price << "\t" << type << std::endl;
						i++;
					}
					i = 0;
					while (rims[i].getPrice() > 0)
					{
						name = rims[i].getName();
						manufacturer = rims[i].getManufacturer();
						stock = rims[i].getStock();
						diameter = rims[i].getDiameter();
						price = rims[i].getPrice();
						type = rims[i].getType();
						cout << name << "\t" << manufacturer << "\t" << stock << "\t" << diameter << "\t" << price << "\t" << type << std::endl;
						i++;
					}
					i = 0;
				}
			}
			else
			{
				cout << "Do you wish to see details yes (y), no (any other letter)?" << std::endl;
				cin >> detail;
				if (detail == 'y')
				{
					cout << "Name\tManufacturer\tStock\tDiameter\tPrice\tType\twidth\theight/aluminum\tspeedindex/color\tseason" << endl;
					while (tires[i].getPrice() > 0)
					{
						name = tires[i].getName();
						manufacturer = tires[i].getManufacturer();
						stock = tires[i].getStock();
						diameter = tires[i].getDiameter();
						price = tires[i].getPrice();
						type = tires[i].getType();
						width = tires[i].getWidth();
						height = tires[i].getHeight();
						colorspeed = tires[i].getSpeedIndex();
						season = tires[i].getSeason();
						if (isSubstring(search, name) > -1)
						{
							cout << name << "\t" << manufacturer << "\t" << stock << "\t" << diameter << "\t" << price << "\t" << type << "\t" << width << "\t" << height << "\t" << colorspeed << "\t" << season << std::endl;
						}
						i++;
					}
					i = 0;
					while (rims[i].getPrice() > 0)
					{
						name = rims[i].getName();
						manufacturer = rims[i].getManufacturer();
						stock = rims[i].getStock();
						diameter = rims[i].getDiameter();
						price = rims[i].getPrice();
						type = rims[i].getType();
						width = rims[i].getWidth();
						aluminum = rims[i].getAluminum();
						colorspeed = rims[i].getColor();
						if (isSubstring(search, name) > -1)
						{
							cout << name << "\t" << manufacturer << "\t" << stock << "\t" << diameter << "\t" << price << "\t" << type << "\t" << width << "\t" << aluminum << "\t" << colorspeed << std::endl;
						}
						i++;
					}
					i = 0;
				}
				else
				{
					cout << "Name\tManufacturer\tStock\tDiameter\tPrice\tType" << endl;
					while (tires[i].getPrice() > 0)
					{
						name = tires[i].getName();
						manufacturer = tires[i].getManufacturer();
						stock = tires[i].getStock();
						diameter = tires[i].getDiameter();
						price = tires[i].getPrice();
						type = tires[i].getType();
						if (isSubstring(search, name) > -1)
						{
							cout << name << "\t" << manufacturer << "\t" << stock << "\t" << diameter << "\t" << price << "\t" << type << std::endl;
						}
						i++;
					}
					i = 0;
					while (rims[i].getPrice() > 0)
					{
						name = rims[i].getName();
						manufacturer = rims[i].getManufacturer();
						stock = rims[i].getStock();
						diameter = rims[i].getDiameter();
						price = rims[i].getPrice();
						type = rims[i].getType();
						if (isSubstring(search, name) > -1)
						{
							cout << name << "\t" << manufacturer << "\t" << stock << "\t" << diameter << "\t" << price << "\t" << type << std::endl;
						}
						i++;
					}
					i = 0;
				}
			}
		}

		if (choice == 'f')
		{
			cout << "Do you wish to look at only tires (t), only rims (r), or search by size(s)?" << std::endl;
			cin >> filter;
			if (filter == 't')
			{
				cout << "Do you wish to look at all of the items (all), or look for a specific object (just type what you are looking for)?" << std::endl;
				getline(cin, search);
				if (search.compare("all") == 0)
				{
					cout << "Name\tManufacturer\tStock\tDiameter\tPrice\tType\twidth\theight/aluminum\tspeedindex/color\tseason" << endl;
					while (tires[i].getPrice() > 0)
					{
						name = tires[i].getName();
						manufacturer = tires[i].getManufacturer();
						stock = tires[i].getStock();
						diameter = tires[i].getDiameter();
						price = tires[i].getPrice();
						type = tires[i].getType();
						width = tires[i].getWidth();
						height = tires[i].getHeight();
						colorspeed = tires[i].getSpeedIndex();
						season = tires[i].getSeason();
						cout << name << "\t" << manufacturer << "\t" << stock << "\t" << diameter << "\t" << price << "\t" << type << "\t" << width << "\t" << height << "\t" << colorspeed << "\t" << season << std::endl;
						i++;
					}
					i = 0;
				}
				else
				{
					cout << "Name\tManufacturer\tStock\tDiameter\tPrice\tType\twidth\theight/aluminum\tspeedindex/color\tseason" << endl;
					while (tires[i].getPrice() > 0)
					{
						name = tires[i].getName();
						manufacturer = tires[i].getManufacturer();
						stock = tires[i].getStock();
						diameter = tires[i].getDiameter();
						price = tires[i].getPrice();
						type = tires[i].getType();
						width = tires[i].getWidth();
						height = tires[i].getHeight();
						colorspeed = tires[i].getSpeedIndex();
						season = tires[i].getSeason();
						if (isSubstring(search, name) > -1)
						{
							cout << name << "\t" << manufacturer << "\t" << stock << "\t" << diameter << "\t" << price << "\t" << type << "\t" << width << "\t" << height << "\t" << colorspeed << "\t" << season << std::endl;
						}
						i++;
					}
					i = 0;
				}
			}

			if (filter == 'r')
			{
				cout << "Do you wish to look at all of the items (all), or look for a specific object (just type what you are looking for)?" << std::endl;
				getline(cin, search);
				if (search.compare("all") == 0)
				{
					while (rims[i].getPrice() > 0)
					{
						name = rims[i].getName();
						manufacturer = rims[i].getManufacturer();
						stock = rims[i].getStock();
						diameter = rims[i].getDiameter();
						price = rims[i].getPrice();
						type = rims[i].getType();
						width = rims[i].getWidth();
						aluminum = rims[i].getAluminum();
						colorspeed = rims[i].getColor();
						cout << name << "\t" << manufacturer << "\t" << stock << "\t" << diameter << "\t" << price << "\t" << type << "\t" << width << "\t" << aluminum << "\t" << colorspeed << std::endl;
						i++;
					}
					i = 0;
				}
				else
				{
					while (rims[i].getPrice() > 0)
					{
						name = rims[i].getName();
						manufacturer = rims[i].getManufacturer();
						stock = rims[i].getStock();
						diameter = rims[i].getDiameter();
						price = rims[i].getPrice();
						type = rims[i].getType();
						width = rims[i].getWidth();
						aluminum = rims[i].getAluminum();
						colorspeed = rims[i].getColor();
						if (isSubstring(search, name) > -1)
						{
							cout << name << "\t" << manufacturer << "\t" << stock << "\t" << diameter << "\t" << price << "\t" << type << "\t" << width << "\t" << aluminum << "\t" << colorspeed << std::endl;
						}
						i++;
					}
					i = 0;
				}
			}
			if (filter == 's')
			{
				cout << "What size do you want: ";
				cin >> size;
				cout << "Do you wish to look at all of the items (all), or look for a specific object (just type what you are looking for)?" << std::endl;
				getline(cin, search);
				if (search.compare("all") == 0)
				{
					cout << "Do you wish to see details yes (y), no (any other letter)?" << std::endl;
					cin >> detail;
					if (detail == 'y')
					{
						cout << "Name\tManufacturer\tStock\tDiameter\tPrice\tType\twidth\theight/aluminum\tspeedindex/color\tseason" << endl;
						while (tires[i].getPrice() > 0)
						{
							name = tires[i].getName();
							manufacturer = tires[i].getManufacturer();
							stock = tires[i].getStock();
							diameter = tires[i].getDiameter();
							price = tires[i].getPrice();
							type = tires[i].getType();
							width = tires[i].getWidth();
							height = tires[i].getHeight();
							colorspeed = tires[i].getSpeedIndex();
							season = tires[i].getSeason();
							if (size == diameter)
							{
								cout << name << "\t" << manufacturer << "\t" << stock << "\t" << diameter << "\t" << price << "\t" << type << "\t" << width << "\t" << height << "\t" << colorspeed << "\t" << season << std::endl;
							}
							i++;
						}
						i = 0;
						while (rims[i].getPrice() > 0)
						{
							name = rims[i].getName();
							manufacturer = rims[i].getManufacturer();
							stock = rims[i].getStock();
							diameter = rims[i].getDiameter();
							price = rims[i].getPrice();
							type = rims[i].getType();
							width = rims[i].getWidth();
							aluminum = rims[i].getAluminum();
							colorspeed = rims[i].getColor();
							if (size == diameter)
							{
								cout << name << "\t" << manufacturer << "\t" << stock << "\t" << diameter << "\t" << price << "\t" << type << "\t" << width << "\t" << aluminum << "\t" << colorspeed << std::endl;
							}
							i++;
						}
						i = 0;
					}
					else
					{
						cout << "Name\tManufacturer\tStock\tDiameter\tPrice\tType" << endl;
						while (tires[i].getPrice() > 0)
						{
							name = tires[i].getName();
							manufacturer = tires[i].getManufacturer();
							stock = tires[i].getStock();
							diameter = tires[i].getDiameter();
							price = tires[i].getPrice();
							type = tires[i].getType();
							if (size == diameter)
							{
								cout << name << "\t" << manufacturer << "\t" << stock << "\t" << diameter << "\t" << price << "\t" << type << std::endl;
							}
							i++;
						}
						i = 0;
						while (rims[i].getPrice() > 0)
						{
							name = rims[i].getName();
							manufacturer = rims[i].getManufacturer();
							stock = rims[i].getStock();
							diameter = rims[i].getDiameter();
							price = rims[i].getPrice();
							type = rims[i].getType();
							if (size == diameter)
							{
								cout << name << "\t" << manufacturer << "\t" << stock << "\t" << diameter << "\t" << price << "\t" << type << std::endl;
							}
							i++;
						}
						i = 0;
					}
				}
				else
				{
					cout << "Do you wish to see details yes (y), no (any other letter)?" << std::endl;
					cin >> detail;
					if (detail == 'y')
					{
						cout << "Name\tManufacturer\tStock\tDiameter\tPrice\tType\twidth\theight/aluminum\tspeedindex/color\tseason" << endl;
						while (tires[i].getPrice() > 0)
						{
							name = tires[i].getName();
							manufacturer = tires[i].getManufacturer();
							stock = tires[i].getStock();
							diameter = tires[i].getDiameter();
							price = tires[i].getPrice();
							type = tires[i].getType();
							width = tires[i].getWidth();
							height = tires[i].getHeight();
							colorspeed = tires[i].getSpeedIndex();
							season = tires[i].getSeason();
							if (isSubstring(search, name) > -1 && size == diameter)
							{
								cout << name << "\t" << manufacturer << "\t" << stock << "\t" << diameter << "\t" << price << "\t" << type << "\t" << width << "\t" << height << "\t" << colorspeed << "\t" << season << std::endl;
							}
							i++;
						}
						i = 0;
						while (rims[i].getPrice() > 0)
						{
							name = rims[i].getName();
							manufacturer = rims[i].getManufacturer();
							stock = rims[i].getStock();
							diameter = rims[i].getDiameter();
							price = rims[i].getPrice();
							type = rims[i].getType();
							width = rims[i].getWidth();
							aluminum = rims[i].getAluminum();
							colorspeed = rims[i].getColor();
							if (isSubstring(search, name) > -1 && size == diameter)
							{
								cout << name << "\t" << manufacturer << "\t" << stock << "\t" << diameter << "\t" << price << "\t" << type << "\t" << width << "\t" << aluminum << "\t" << colorspeed << std::endl;
							}
							i++;
						}
						i = 0;
					}
					else
					{
						cout << "Name\tManufacturer\tStock\tDiameter\tPrice\tType" << endl;
						while (tires[i].getPrice() > 0)
						{
							name = tires[i].getName();
							manufacturer = tires[i].getManufacturer();
							stock = tires[i].getStock();
							diameter = tires[i].getDiameter();
							price = tires[i].getPrice();
							type = tires[i].getType();
							if (isSubstring(search, name) > -1 && size == diameter)
							{
								cout << name << "\t" << manufacturer << "\t" << stock << "\t" << diameter << "\t" << price << "\t" << type << std::endl;
							}
							i++;
						}
						i = 0;
						while (rims[i].getPrice() > 0)
						{
							name = rims[i].getName();
							manufacturer = rims[i].getManufacturer();
							stock = rims[i].getStock();
							diameter = rims[i].getDiameter();
							price = rims[i].getPrice();
							type = rims[i].getType();
							if (isSubstring(search, name) > -1 && size == diameter)
							{
								cout << name << "\t" << manufacturer << "\t" << stock << "\t" << diameter << "\t" << price << "\t" << type << std::endl;
							}
							i++;
						}
						i = 0;
					}
				}
			}
		}
	}
}

void deletearticle(tire tires[TOTTIRE], rim rims[TOTRIMS])
{
	;
}

void changearticle(tire tires[TOTTIRE], rim rims[TOTRIMS])
{
	;
}

void checkinvoice(invoice invoices[INVOICES])
{
	;
}

void makeorder(tire tires[TOTTIRE], rim rims[TOTRIMS], customer customers[CUSTOMERS], company companies[COMPANIES], invoice invoices[INVOICES])
{
	;
}

void deletecustomer(customer customers[CUSTOMERS], company companies[COMPANIES])
{
	;
}

void searchcustomer(customer customers[CUSTOMERS], company companies[COMPANIES])
{
	;
}

void changecustomer(customer customers[CUSTOMERS], company companies[COMPANIES])
{
	;
}

void addcustomer(customer customers[CUSTOMERS], company companies[COMPANIES])
{
	;
}

void updatestock(tire tires[TOTTIRE], rim rims[TOTRIMS])
{
	;
}

void update(tire tires[TOTTIRE], rim rims[TOTRIMS], article artikel, int change)
{
	;
}

int isSubstring(string s1, string s2)
{
	int M = s1.length();
	int N = s2.length();

	for (int i = 0; i <= N - M; i++) {
		int j;

		for (j = 0; j < M; j++)
			if (s2[i + j] != s1[j])
				break;

		if (j == M)
			return i;
	}

	return -1;
}