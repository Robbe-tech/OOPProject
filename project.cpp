#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <array>
#include <vector>

#include "Invoice.h"
#include "TireCenter.h"

#define TOTTIRE 50
#define TOTRIMS 50
#define CUSTOMERS 50
#define COMPANIES 10
#define INVOICES 50
#define TIRECENTERS 5
#define LEN 50

using namespace std;

void readarticles(const static string&, int*, vector<Article*>, vector<int>);
void searcharticle(vector<Article*>);
void addarticle(vector<Article*>);
void deletearticle(vector<Article*>);
void changearticle(vector<Article*>);

void readcustomers(const static string&, int*, vector<Customer*>, vector<int>);
void searchcustomer(vector<Customer*>);
void addcustomer(vector<Customer*>);
void deletecustomer(vector<Customer*>);
void changecustomer(vector<Customer*>);

void readinvoices(const static string&, vector<Invoice*>);
void searchinvoice(vector<Invoice*>);
void makeorder(vector<Invoice*>);

void readtirecenters(const static string&, vector<TireCenter*>);
void searchtirecenter(vector<TireCenter*>);
void addtirecenter(vector<TireCenter*>);

void updatearticle(vector<Article*>);				//update single article
void updatecustomer(vector<Customer*>);
void updateinvoice(vector<Invoice*>);
void updatetirecenter(vector<TireCenter*>);

void updatearticles(vector<Article*>);				//update all articles
void updatecustomers(vector<Customer*>);
void updateinvoices(vector<Invoice*>);
void updatetirecenters(vector<TireCenter*>);

void updatestock(vector<Article*>);
void update(vector<Article*>);
bool isSubstring(string, string);
inline bool fileTest(const static string&);

int main(void) {
	const static string articleFile = "Articles.dat", customerFile = "Customers.dat", invoiceFile = "Invoices.dat", tireCenterFile = "TireCenters.dat", deletedArticles = "DeletedArticles.dat", deletedCustomers = "DeletedCustomers.dat";
	int articlePos = 0, customerPos = 0, invoicePos = 0, tireCenterPos = 0, i, id;

	vector<Article*> articles{};
	vector<Customer*> customers{};
	vector<Invoice*> invoices{};
	vector<TireCenter*> tireCenters{};

	vector<int> articlesPos{};				//binaire positie van volgende product
	vector<int> customersPos{};				//posities zijn niet nodig voor invoices en tirecenters omdat ze altijd dezelfde grootte hebben

	char employee, option, checkcenter;

	cout << "Are you the owner (o) or employee (e): " << std::endl;
	cin >> employee;
	while (!(employee == 'e' || employee == 'E' || employee == 'o' || employee == 'O'))
	{
		cout << "Please give a valid option o or e: ";
		cin >> employee;
	}

	if (!fileTest(articleFile)) {
		if (employee == 'o' || employee == 'O') {
			cout << "We see that you are new here, we will create the files in wich you can add articles, customers, invoices and tire centers." << endl << "Lets start with adding some articles.";
			addarticle(articles);
			while (articles.empty()) {
				cout << "Please add at least one article." << endl;
				addarticle(articles);
			}

			cout << "Please add some customers." << endl;
			addcustomer(customers);
			while (customers.empty()) {
				cout << "Please add at least one customer." << endl;
				addcustomer(customers);
			}

			cout << "If you want you could add some invoices." << endl;
			makeorder(invoices);
			
			cout << "Please add some tire centers." << endl;
			addtirecenter(tireCenters);
			while (tireCenters.empty()) {
				cout << "Please add at least one tire center." << endl;
				addtirecenter(tireCenters);
			}
		}
		else {
			cout << "Since you're the employee the only thing you can do at the moment is add customers. Ask the owner to add articles if you want to start adding invoices." << endl << "Do you want to add some customers (y/n): ";
			cin >> option;
			while (!(option == 'y' || option == 'Y' || option == 'n' || option == 'N')) {
				cout << "Please enter a valid awnser (y or n): ";
				cin >> option;
			}

			if (option == 'y' || option == 'Y') {
				addcustomer(customers);
			}

			updatearticles(articles);				//create files
			updateinvoices(invoices);
			updatetirecenters(tireCenters);
		}
	}

	else {
		readarticles(articleFile, &articlePos, articles, articlesPos);
		readcustomers(customerFile, &customerPos, customers, customersPos);
		readinvoices(invoiceFile, invoices);
		readtirecenters(tireCenterFile, tireCenters);

		if (articles.empty() || customers.empty() || tireCenters.empty()) {
			if (articles.empty()) {
				if (employee == 'e' || employee == 'E') {
					cout << "Please contact the owner to add articles to the program." << endl;
				}
				else {
					cout << "Please add some articles." << endl;
					addarticle(articles);
					while (articles.empty()) {
						cout << "Please add at least one article." << endl;
						addarticle(articles);
					}
				}
			}

			if (customers.empty()) {
				cout << "Please add some customers." << endl;
				addcustomer(customers);
				while (customers.empty()) {
					cout << "Please add at least one customer." << endl;
					addcustomer(customers);
				}
			}

			if (tireCenters.empty()) {
				if (employee == 'e' || employee == 'E') {
					cout << "Please contact the owner to add tire centers to the program." << endl;
				}
				else {
					cout << "Please add some tire centers." << endl;
					addtirecenter(tireCenters);
					while (tireCenters.empty()) {
						cout << "Please add at least one tire center." << endl;
						addtirecenter(tireCenters);
					}
				}
			}
		}

		else {
			searchtirecenter(tireCenters);
			cout << "Did you see your tire center in the list (y/n): ";
			cin >> checkcenter;
			while (!(checkcenter == 'y' || checkcenter == 'Y' || checkcenter == 'n' || checkcenter == 'N')) {
				cout << "Please enter a valid awnser (y or n): ";
				cin >> checkcenter;
			}

			if (checkcenter == 'n' || checkcenter == 'N') {
				if (employee == 'o' || employee == 'O') {
					cout << "Please add your tire center." << endl;
					addtirecenter(tireCenters);
				}
				else {
					cout << "Please contact the owner." << endl;
				}
			}

			else {
				cout << "Please choose the id of the tire center you are from (if you see multiple of your tire center choose the id of the last one): ";
				cin >> id;

				while (id > tireCenters.size() || id <= 0) {
					cout << "Please choose a valid id: ";
					cin >> id;
				}

				while (!(option == 'e' || option == 'E'))
				{
					if (employee == 'o' || employee == 'O')
					{
						cout << "Choose between adding an article (a), searching articles (s), deleting an article (d), changing an article (c), checking invoices (i), placing an order (p), deleting customers (b), searching customers (m), changing customers (h), adding customers(n) and updating stock (u) and exiting (e)";
						cin >> option;
					}
					else
					{
						cout << "Choose between searching articles (s), changing an article (c), checking invoices (i), placing an order (p), searching customers (m), changing customers (h), adding customers(n) and updating stock (u) and exiting (e)";
						cin >> option;
					}

					if (option == 's' || option == 'S')
					{
						searcharticle(articles);
					}
					if ((option == 'a' || option == 'A') && (employee == 'o' || employee == 'O'))
					{
						addarticle(articles);
					}
					if ((option == 'd' || option == 'D') && (employee == 'o' || employee == 'O'))
					{
						deletearticle(articles);
					}
					if (option == 'c' || option == 'C')
					{
						changearticle(articles);
					}
					if (option == 'i' || option == 'I')
					{
						searchinvoice(invoices);
					}
					if (option == 'p' || option == 'P')
					{
						makeorder(invoices);
					}
					if ((option == 'b' || option == 'B') && (employee == 'o' || employee == 'O'))
					{
						deletecustomer(customers);
					}
					if (option == 'm' || option == 'M')
					{
						searchcustomer(customers);
					}
					if (option == 'h' || option == 'H')
					{
						changecustomer(customers);
					}
					if (option == 'n' || option == 'N')
					{
						addcustomer(customers);
					}
					if (option == 'u' || option == 'U')
					{
						updatestock(articles);
					}
				}
			}
		}
	}

	return 0;
}

void readarticles(const static string& articleFile, int* articlePos, vector<Article*> articles, vector<int> articlesPos) {
	ifstream inArticle(articleFile, ios::in | ios::binary);
	Article checkArticleType{ "", "", NULL, NULL, NULL, '\0' };
	Rim tempRim{ "", "", NULL, NULL, NULL, '\0', false, "", NULL };
	Tire tempTire{ "", "", NULL, NULL, NULL, '\0', NULL, NULL, "", '\0' };

	if (!inArticle) {
		cerr << "The article file could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	checkArticleType.fromFile(inArticle,articlePos);

	while (checkArticleType.getType() != '\0') {
		if (checkArticleType.getType() == 'r' || checkArticleType.getType() == 'R') {
			tempRim.fromFile(inArticle, articlePos);
			articles.push_back(new Rim(tempRim));
		}
		else {
			tempTire.fromFile(inArticle, articlePos);
			articles.push_back(new Tire(tempTire));
		}
		articlesPos.push_back(*articlePos);
		checkArticleType.setType('\0');
		checkArticleType.fromFile(inArticle, articlePos);
	}
}

void searcharticle(vector<Article*> articles)
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
			if (search.compare("all") == 0 || search.compare("all") == 0)
			{
				cout << "Do you wish to see details yes (y), no (any other letter)?" << std::endl;
				cin >> detail;
				if (detail == 'y' || detail == 'Y')
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

void addarticle(vector<Article*> articles)
{
	int i, stock, diameter, width, height, alu;
	float price;
	char choice, season, type;
	std::string name, manufacturer, colorspeed;
	bool occured, aluminum;

	while (!(choice == 'e' || choice == 'E'))
	{
		cout << "Do you wish to add a tire (t), rim (r) or exit (e): ";
		cin >> choice;

		if (choice == 't' )
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

void deletearticle(vector<Article*> articles)
{
	;
}

void changearticle(vector<Article*> articles)
{
	;
}

void deletecustomer(vector<Customer*> customers)
{
	;
}

void readcustomers(const static string& customerFile, int* customerPos, vector<Customer*> customers, vector<int> customersPos) {
	ifstream inCustomer(customerFile, ios::in | ios::binary);
	Customer checkCustomer{ "", "", '\0' };
	Company tempCompany{ "", "", '\0', "", NULL };
	int tempPos = *customerPos;

	if (!inCustomer) {
		cerr << "The cusomer file could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	checkCustomer.fromFile(inCustomer, customerPos);

	while (checkCustomer.getType() != '\0') {
		if (checkCustomer.getType() == 'o' || checkCustomer.getType() == 'O') {
			*customerPos = tempPos;
			tempCompany.fromFile(inCustomer, customerPos);
			customers.push_back(new Company(tempCompany));
		}
		else {
			customers.push_back(new Customer(checkCustomer));
		}
		customersPos.push_back(*customerPos);
		tempPos = *customerPos;
		checkCustomer.setType('\0');
		checkCustomer.fromFile(inCustomer, customerPos);
	}
}

void searchcustomer(vector<Customer*> customers)
{
	;
}

void changecustomer(vector<Customer*> customers)
{
	;
}

void addcustomer(vector<Customer*> customers)
{
	;
}

void readinvoices(const static string& invoiceFile, vector<Invoice*> invoices) {
	ifstream inInvoice(invoiceFile, ios::in | ios::binary);
	Customer customer{ "", "", '\0' };
	array<Article&, ARTIEKELEN> articles{};
	Invoice tempInvoice{ customer, articles, NULL, NULL };

	if (!inInvoice) {
		cerr << "The cusomer file could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	tempInvoice.fromFile(inInvoice);

	while (tempInvoice.getPrice() != NULL) {
		invoices.push_back(new Invoice(tempInvoice));
		tempInvoice.setPrice(NULL);
		tempInvoice.fromFile(inInvoice);
	}
}

void searchinvoice(vector<Invoice*> invoices)
{
	;
}

void makeorder(vector<Invoice*> invoices)
{
	;
}

void changeinvoice(vector<Invoice*>);

void readtirecenters(const static string& tireCenterFile, vector<TireCenter*> tireCenters) {
	ifstream inTireCenter(tireCenterFile, ios::in | ios::binary);
	array<Customer&, KLANTEN> customers{};
	array<Article&, ARTIEKELEN> articles{};
	TireCenter tempTireCenter{ "", "", articles, customers };

	if (!inTireCenter) {
		cerr << "The cusomer file could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	tempTireCenter.fromFile(inTireCenter);

	while (tempTireCenter.getName() != "") {
		tireCenters.push_back(new TireCenter(tempTireCenter));
		tempTireCenter.setName("");
		tempTireCenter.fromFile(inTireCenter);
	}
}

void searchtirecenter(vector<TireCenter*> tireCenters) {
	int i, id;
	char choice, redo = 'r';
	ostringstream stream;
	
	while (redo == 'r' || redo == 'R')
	cout << "These are all current tire centers (Some may show up more than once due to too many customers)." << endl;
	stream << "ID" << setw(3) << "Name" << setw(NAME) << "Address" << setw(ADDRESS) << "Article Name" << setw(CHAR) << "Customer Name" << endl;
	for (i = 0; i < tireCenters.size(); i++) {
		stream << (i + 1) << setw(3) << tireCenters[i]->toTable() << endl;
	}

	cout << stream.str() << endl
		<< "Do you wish to view any tire centers in detail (y for yes, anything else for no): ";
	cin >> choice;
	if (choice == 'y' || choice == 'Y') {
		cout << "Please choose the id of the tire center you wish to view: ";
		cin >> id;
		while (id > tireCenters.size() || id <= 0) {
			cout << "Please choose a valid id: ";
			cin >> id;
		}
		cout << tireCenters[id - 1]->toString() << endl
			<< "If you wish to view the table again enter r else enter anything else: ";
		cin >> redo;
	}
}

void addtirecenter(vector<TireCenter*>);

void updatestock(vector<Article*> articles)
{
	;
}

void update(vector<Article*> articles)
{
	;
}

bool isSubstring(string s1, string s2)
{
	int M = s1.length();
	int N = s2.length();
	bool substring = false;

	for (int i = 0; i <= N - M; i++) {
		int j;
		substring = true;

		for (j = 0; j < M; j++) {
			if (s2[i + j] != s1[j]) {
				substring = false;
			}
		}
		if (substring)
			return substring;
	}

	return substring;
}

inline bool fileTest(const static string& name) {
	if (FILE* file = fopen(name.c_str(), "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}