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

void readarticles(const static string&, vector<Article*>, vector<int>);
void searcharticle(vector<Article*>);
void addarticle(const static string&,vector<Article*>, vector<int>);
void deletearticle(const static string&, vector<Article*>, vector<int>,const static string&, vector<Article*>, vector<int>);
void changearticle(const static string&, vector<Article*>, vector<int>);

void readcustomers(const static string&, vector<Customer*>, vector<int>);
void searchcustomer(vector<Customer*>);
void addcustomer(const static string&, vector<Customer*>, vector<int>);
void deletecustomer(const static string&, vector<Customer*>, vector<int>, const static string&, vector<Customer*>, vector<int>);
void changecustomer(const static string&, vector<Customer*>, vector<int>);

void readinvoices(const static string&, vector<Invoice*>);
void searchinvoice(vector<Invoice*>);
void makeorder(const static string&, vector<Invoice*>, const static string&, vector<Article*>, vector<int>, const static string&, vector<Customer*>, vector<int>, const static string&, vector<TireCenter*>, int);

void readtirecenters(const static string&, vector<TireCenter*>);
void searchtirecenter(vector<TireCenter*>);
void addtirecenter(const static string&, vector<TireCenter*>, vector<Article*>, vector<Customer*>);

void updatestock(const static string&, vector<Article*>, vector<int>, int, int);
bool isSubstring(string, string);
inline bool fileTest(const static string&);

int main(void) {
	const static string articleFile = "Articles.dat", customerFile = "Customers.dat", invoiceFile = "Invoices.dat", tireCenterFile = "TireCenters.dat", deletedArticleFile = "DeletedArticles.dat", deletedCustomerFile = "DeletedCustomers.dat";
	int i, id;

	vector<Article*> articles{};
	vector<Article*> deletedArticles{};
	vector<Customer*> customers{};
	vector<Customer*> deletedCustomers{};
	vector<Invoice*> invoices{};
	vector<TireCenter*> tireCenters{};

	vector<int> articlesPos{};				//binaire positie van volgende product
	vector<int> deletedArticlesPos{};
	vector<int> customersPos{};
	vector<int> deletedCustomersPos{};		//posities zijn niet nodig voor invoices en tirecenters omdat ze altijd dezelfde grootte hebben

	char employee, option = 'b', checkcenter;

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
			addarticle(articleFile, articles, articlesPos);
			while (articles.empty()) {
				cout << "Please add at least one article." << endl;
				addarticle(articleFile, articles, articlesPos);
			}

			cout << "Please add some customers." << endl;
			addcustomer(customerFile, customers, customersPos);
			while (customers.empty()) {
				cout << "Please add at least one customer." << endl;
				addcustomer(customerFile, customers, customersPos);
			}

			cout << "Please add some tire centers." << endl;
			addtirecenter(tireCenterFile, tireCenters, articles, customers);
			while (tireCenters.empty()) {
				cout << "Please add at least one tire center." << endl;
				addtirecenter(tireCenterFile, tireCenters, articles, customers);
			}

			cout << "Enter the ID of the tire center you are from (0 to exit, you cant make invoices without it): ";
			cin >> id;
			while (id < 0 || id > tireCenters.size()) {
				cout << "Enter a valid ID (0 to exit): ";
				cin >> id;
			}

			if (id != 0) {
				cout << "If you want you could add some invoices." << endl;
				makeorder(invoiceFile, invoices, articleFile, articles, articlesPos, customerFile, customers, customersPos, tireCenterFile, tireCenters, id);
			}

			if (invoices.empty()) {
				ofstream createInvoice(invoiceFile, ios::out | ios::binary);
				if (!createInvoice) {
					cerr << "Something went wrong creating the invoice file." << endl;
					exit(EXIT_FAILURE);
				}
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
				addcustomer(customerFile, customers, customersPos);
			}

			ofstream createArticle(articleFile, ios::in | ios::binary);				//create files
			ofstream createInvoice(invoiceFile, ios::in | ios::binary);
			ofstream createTireCenter(tireCenterFile, ios::in | ios::binary);

			if (!createArticle) {
				cerr << "Something went wrong creating the article file." << endl;
				exit(EXIT_FAILURE);
			}

			if (!createInvoice) {
				cerr << "Something went wrong creating the invoice file." << endl;
				exit(EXIT_FAILURE);
			}

			if (!createTireCenter) {
				cerr << "Something went wrong creating the tire center file." << endl;
				exit(EXIT_FAILURE);
			}
		}
	}

	else {
		readarticles(articleFile, articles, articlesPos);
		readarticles(deletedArticleFile, deletedArticles, deletedArticlesPos);
		readcustomers(customerFile, customers, customersPos);
		readcustomers(deletedCustomerFile, deletedCustomers, deletedCustomersPos);
		readinvoices(invoiceFile, invoices);
		readtirecenters(tireCenterFile, tireCenters);

		if (articles.empty() || customers.empty() || tireCenters.empty()) {
			if (articles.empty()) {
				if (employee == 'e' || employee == 'E') {
					cout << "Please contact the owner to add articles to the program." << endl;
				}
				else {
					cout << "Please add some articles." << endl;
					addarticle(articleFile, articles, articlesPos);
					while (articles.empty()) {
						cout << "Please add at least one article." << endl;
						addarticle(articleFile, articles, articlesPos);
					}
				}
			}

			if (customers.empty()) {
				cout << "Please add some customers." << endl;
				addcustomer(customerFile, customers, customersPos);
				while (customers.empty()) {
					cout << "Please add at least one customer." << endl;
					addcustomer(customerFile, customers, customersPos);
				}
			}

			if (tireCenters.empty()) {
				if (employee == 'e' || employee == 'E') {
					cout << "Please contact the owner to add tire centers to the program." << endl;
				}
				else {
					cout << "Please add some tire centers." << endl;
					addtirecenter(tireCenterFile, tireCenters, articles, customers);
					while (tireCenters.empty()) {
						cout << "Please add at least one tire center." << endl;
						addtirecenter(tireCenterFile, tireCenters, articles, customers);
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
					addtirecenter(tireCenterFile, tireCenters, articles, customers);
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
						cout << "Choose between adding an article (a), searching articles (s), deleting an article (d), changing an article (c), checking invoices (i), placing an order (p), deleting customers (b), searching customers (m), changing customers (h), adding customers(n) and updating stock (u) and exiting (e): ";
						cin >> option;
					}
					else
					{
						cout << "Choose between searching articles (s), changing an article (c), checking invoices (i), placing an order (p), searching customers (m), changing customers (h), adding customers(n) and updating stock (u) and exiting (e): ";
						cin >> option;
					}

					if (option == 's' || option == 'S')
					{
						searcharticle(articles);
					}
					if ((option == 'a' || option == 'A') && (employee == 'o' || employee == 'O'))
					{
						addarticle(articleFile, articles, articlesPos);
					}
					if ((option == 'd' || option == 'D') && (employee == 'o' || employee == 'O'))
					{
						deletearticle(articleFile, articles, articlesPos, deletedArticleFile, deletedArticles, deletedArticlesPos);
					}
					if (option == 'c' || option == 'C')
					{
						changearticle(articleFile, articles, articlesPos);
					}
					if ((option == 'b' || option == 'B') && (employee == 'o' || employee == 'O'))
					{
						deletecustomer(customerFile, customers, customersPos, deletedCustomerFile, deletedCustomers, deletedCustomersPos);
					}
					if (option == 'm' || option == 'M')
					{
						searchcustomer(customers);
					}
					if (option == 'h' || option == 'H')
					{
						changecustomer(customerFile, customers, customersPos);
					}
					if (option == 'n' || option == 'N')
					{
						addcustomer(customerFile, customers, customersPos);
					}
					if (option == 'i' || option == 'I')
					{
						searchinvoice(invoices);
					}
					if (option == 'p' || option == 'P')
					{
						makeorder(invoiceFile, invoices, articleFile, articles, articlesPos, customerFile, customers, customersPos, tireCenterFile, tireCenters, id);
					}
					if (option == 'u' || option == 'U')
					{
						updatestock(articleFile, articles, articlesPos, 0, 0);
					}
				}
			}
		}
	}

	return 0;
}

void readarticles(const static string& articleFile, vector<Article*> articles, vector<int> articlesPos) {
	ifstream inArticle(articleFile, ios::in | ios::binary);
	int articlePos = 0;
	Article checkArticleType{ "", "", NULL, NULL, NULL, '\0' };
	Rim tempRim{"", "", NULL, NULL, NULL, '\0', false, "", NULL};
	Tire tempTire{ "", "", NULL, NULL, NULL, '\0', NULL, NULL, "", '\0' };
	articles.clear();

	if (!inArticle) {
		cerr << "The article file could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	checkArticleType.fromFile(inArticle, &articlePos);

	while (checkArticleType.getType() != '\0') {
		if (checkArticleType.getType() == 'r' || checkArticleType.getType() == 'R') {
			tempRim.fromFile(inArticle, &articlePos);
			articles.push_back(new Rim(tempRim));
		}
		else {
			tempTire.fromFile(inArticle, &articlePos);
			articles.push_back(new Tire(tempTire));
		}

		articlesPos.push_back(articlePos);
		checkArticleType.setType('\0');
		checkArticleType.fromFile(inArticle, &articlePos);
	}
}

void searcharticle(vector<Article*> articles)
{
	char filter, choice = 'l';
	string search;
	int size, i;
	ostringstream stream;

	while (!(choice == 'e' || choice == 'E'))
	{
		cout << "Do you wish to do a normal search (n), do a filtered search (f) or exit (e)?" << std::endl;
		cin >> choice;
		if (choice == 'n' || choice == 'N')
		{
			cout << "Do you wish to look at all of the items (all), or look for a specific object (just type what you are looking for)?" << std::endl;
			getline(cin, search);
			if (search.compare("all") == 0 || search.compare("All") == 0)
			{
				stream << "ID" << setw(3) << "Name" << setw(CHAR) << "Manufacturer" << setw(CHAR) << "Stock" << setw(10) << "Diameter" << setw(10) << "Price" << setw(10) << "Type" << setw(5) << "Width" << setw(10) << "Height/Aluminum" << setw(20) << "Color/Season" << setw(20) << "SpeedIndex" << endl;
				for (i = 0; i < articles.size(); i++) {
					stream << (i + 1) << setw(3) << articles[i]->toTable() << endl;
				}
				cout << stream.str();
			}
			else
			{
				stream << "ID" << setw(3) << "Name" << setw(CHAR) << "Manufacturer" << setw(CHAR) << "Stock" << setw(10) << "Diameter" << setw(10) << "Price" << setw(10) << "Type" << setw(5) << "Width" << setw(10) << "Height/Aluminum" << setw(20) << "Color/Season" << setw(20) << "SpeedIndex" << endl;
				for (i = 0; i < articles.size(); i++) {
					if (isSubstring(search, articles[i]->getName())) {
						stream << (i + 1) << setw(3) << articles[i]->toTable() << endl;
					}
				}
				cout << stream.str();
			}
		}

		if (choice == 'f' || choice == 'F')
		{
			cout << "Do you wish to look at only tires (t), only rims (r), or search by size(s): ";
			cin >> filter;
			while (!(filter == 't' || filter == 'T' || filter == 'r' || filter == 'R' || filter == 's' || filter == 'S')) {
				cout << "Enter a valid choice (t/r/s): ";
				cin >> filter;
			}
			if (filter == 't' || filter == 'T')
			{
				cout << "Do you wish to look at all of the items (all), or look for a specific object (just type what you are looking for)?" << std::endl;
				getline(cin, search);
				if (search.compare("all") == 0 || search.compare("All") == 0)
				{
					stream << "ID" << setw(3) << "Name" << setw(CHAR) << "Manufacturer" << setw(CHAR) << "Stock" << setw(10) << "Diameter" << setw(10) << "Price" << setw(10) << "Type" << setw(5) << "Width" << setw(10) << "Height" << setw(20) << "Season" << setw(20) << "SpeedIndex" << endl;
					for (i = 0; i < articles.size(); i++) {
						if (articles[i]->getType() == 't' || articles[i]->getType() == 'T') {
							stream << (i + 1) << setw(3) << articles[i]->toTable() << endl;
						}
					}
					cout << stream.str();
				}
				else
				{
					stream << "ID" << setw(3) << "Name" << setw(CHAR) << "Manufacturer" << setw(CHAR) << "Stock" << setw(10) << "Diameter" << setw(10) << "Price" << setw(10) << "Type" << setw(5) << "Width" << setw(10) << "Height" << setw(20) << "Season" << setw(20) << "SpeedIndex" << endl;
					for (i = 0; i < articles.size(); i++) {
						if ((articles[i]->getType() == 't' || articles[i]->getType() == 'T') && isSubstring(search, articles[i]->getName())) {
							stream << (i + 1) << setw(3) << articles[i]->toTable() << endl;
						}
					}
					cout << stream.str();
				}
			}

			if (filter == 'r' || filter == 'R')
			{
				cout << "Do you wish to look at all of the items (all), or look for a specific object (just type what you are looking for)?" << std::endl;
				getline(cin, search);
				if (search.compare("all") == 0 || search.compare("All") == 0)
				{
					stream << "ID" << setw(3) << "Name" << setw(CHAR) << "Manufacturer" << setw(CHAR) << "Stock" << setw(10) << "Diameter" << setw(10) << "Price" << setw(10) << "Type" << setw(5) << "Width" << setw(10) << "Aluminum" << setw(20) << "Color" << endl;
					for (i = 0; i < articles.size(); i++) {
						if (articles[i]->getType() == 'r' || articles[i]->getType() == 'R') {
							stream << (i + 1) << setw(3) << articles[i]->toTable() << endl;
						}
					}
					cout << stream.str();
				}
				else
				{
					stream << "ID" << setw(3) << "Name" << setw(CHAR) << "Manufacturer" << setw(CHAR) << "Stock" << setw(10) << "Diameter" << setw(10) << "Price" << setw(10) << "Type" << setw(5) << "Width" << setw(10) << "Aluminum" << setw(20) << "Color" << endl;
					for (i = 0; i < articles.size(); i++) {
						if ((articles[i]->getType() == 'r' || articles[i]->getType() == 'R') && isSubstring(search, articles[i]->getName())) {
							stream << (i + 1) << setw(3) << articles[i]->toTable() << endl;
						}
					}
					cout << stream.str();
				}
			}
			if (filter == 's' || filter == 'S')
			{
				cout << "What size do you want: ";
				cin >> size;
				cout << "Do you wish to look at all of the items (all), or look for a specific object (just type what you are looking for)?" << std::endl;
				getline(cin, search);
				if (search.compare("all") == 0 || search.compare("All") == 0)
				{
					stream << "ID" << setw(3) << "Name" << setw(CHAR) << "Manufacturer" << setw(CHAR) << "Stock" << setw(10) << "Diameter" << setw(10) << "Price" << setw(10) << "Type" << setw(5) << "Width" << setw(10) << "Height/Aluminum" << setw(20) << "Color/Season" << setw(20) << "SpeedIndex" << endl;
					for (i = 0; i < articles.size(); i++) {
						if (articles[i]->getDiameter() == size) {
							stream << (i + 1) << setw(3) << articles[i]->toTable() << endl;
						}
					}
					cout << stream.str();
				}
				else
				{
					stream << "ID" << setw(3) << "Name" << setw(CHAR) << "Manufacturer" << setw(CHAR) << "Stock" << setw(10) << "Diameter" << setw(10) << "Price" << setw(10) << "Type" << setw(5) << "Width" << setw(10) << "Height/Aluminum" << setw(20) << "Color/Season" << setw(20) << "SpeedIndex" << endl;
					for (i = 0; i < articles.size(); i++) {
						if (articles[i]->getDiameter() == size && isSubstring(search, articles[i]->getName())) {
							stream << (i + 1) << setw(3) << articles[i]->toTable() << endl;
						}
					}
					cout << stream.str();
				}
			}
		}
	}
}

void addarticle(const static string& articleFile, vector<Article*> articles, vector<int> articlesPos)
{
	int i, stock, diameter, width, height, alu, loc;
	float price;
	char choice = 's', season, type;
	string name, manufacturer, colorspeed;
	bool occured, aluminum, articleAdd;
	Article* article;
	ofstream outArticle(articleFile, ios::out | ios::binary);

	while (!(choice == 'e' || choice == 'E')) {
		articleAdd = false;
		cout << "Do you wish to add a tire (t), rim (r) or exit (e): ";
		cin >> choice;

		if (choice == 't' || choice == 'T') {
			do {
				occured = false;
				cout << "Enter the name: ";
				cin >> name;
				for (i = 0; i < articles.size(); i++) {
					if (name.compare(articles[i]->getName()) == 0 && (articles[i]->getType() == 't' || articles[i]->getType() == 'T')) {
						cout << "The name you entered is already used" << std::endl;
						occured = true;
					}
				}
			} while (occured);

			cout << "Enter the manufacturer: ";
			cin >> manufacturer;

			cout << "Enter the stock: ";
			cin >> stock;

			while (stock < 0) {
				cout << "The stock can't be negative: ";
				cin >> stock;
			}

			cout << "Enter the diameter: ";
			cin >> diameter;
			while (diameter <= 0) {
				cout << "The diameter must be greater than 0: ";
				cin >> diameter;
			}

			cout << "Enter the price: ";
			cin >> price;
			while (price <= 0) {
				cout << "The price must be greater than 0: ";
				cin >> price;
			}

			cout << "Enter the width: ";
			cin >> width;
			while (width <= 0) {
				cout << "The width must be greater than 0: ";
				cin >> width;
			}

			cout << "Enter the height: ";
			cin >> height;
			while (height <= 0) {
				cout << "The height must be greater than 0: ";
				cin >> height;
			}

			cout << "Enter the speed index: ";
			cin >> colorspeed;

			cout << "Enter the season, summer (s) or winter (w): ";
			cin >> season;
			while (!(season == 's' || season == 'S' || season == 'w' || season == 'W')) {
				cout << "The season must be either summer(s) or winter (w): ";
				cin >> season;
			}
			if (season == 's' || season == 'S') {
				article = new Tire(name, manufacturer, stock, diameter, price, 't', width, height, colorspeed, 's');
			}
			else {
				article = new Tire(name, manufacturer, stock, diameter, price, 't', width, height, colorspeed, 'r');;
			}

			articleAdd = true;
		}
		if (choice == 'r' || choice == 'R')
		{
			do {
				occured = false;
				cout << "Enter the name: ";
				cin >> name;
				for (i = 0; i < articles.size(); i++) {
					if (name.compare(articles[i]->getName()) == 0 && (articles[i]->getType() == 't' || articles[i]->getType() == 'T')) {
						cout << "The name you entered is already used" << std::endl;
						occured = true;
					}
				}
			} while (occured);

			cout << "Enter the manufacturer: ";
			cin >> manufacturer;

			cout << "Enter the stock: ";
			cin >> stock;

			while (stock < 0) {
				cout << "The stock can't be negative: ";
				cin >> stock;
			}

			cout << "Enter the diameter: ";
			cin >> diameter;
			while (diameter <= 0) {
				cout << "The diameter must be greater than 0: ";
				cin >> diameter;
			}

			cout << "Enter the price: ";
			cin >> price;
			while (price <= 0) {
				cout << "The price must be greater than 0: ";
				cin >> price;
			}

			cout << "Enter the width: ";
			cin >> width;
			while (width <= 0) {
				cout << "The width must be greater than 0: ";
				cin >> width;
			}

			cout << "Enter the color: ";
			cin >> colorspeed;

			cout << "Is the rim made of aluminum (1) or not (0): ";
			cin >> alu;
			while (!(alu == 0 || alu == 1)) {
				cout << "Enter either a 0 (not aluminum) or 1 (aluminum): ";
				cin >> alu;
			}
			if (alu == 0) {
				aluminum = false;
			}
			else {
				aluminum = true;
			}
			
			article = new Rim(name, manufacturer, stock, diameter, price, 'r', aluminum, colorspeed, width);
			articleAdd = true;
		}

		if (articleAdd) {
			if (!outArticle) {
				cerr << "Something went wrong opening the article file." << endl;
				exit(EXIT_FAILURE);
			}

			loc = outArticle.eof();
			article->toFile(outArticle, &loc);

			readarticles(articleFile, articles, articlesPos);
		}
	}
}

void deletearticle(const static string& articleFile, vector<Article*> articles, vector<int> articlesPos, const static string& deletedArticleFile, vector<Article*> deletedArticles, vector<int> deletedArticlesPos)
{
	vector<int> articleInvoiceLoc, articleTireCenterLoc;
	char del, choice = 'l';
	int i, id, loc;

	ofstream outArticles(articleFile, ios::out | ios::binary);
	ofstream outDeletedArticles(deletedArticleFile, ios::out | ios::binary);

	while (!(choice == 'e' || choice == 'E')) {
		cout << "Do you wish to search for the article (s), delete an article (d), or exit (e) (note the id's do change after deleting an article, every article after the deleted id is one lower): ";
		cin >> choice;

		if (choice == 's' || choice == 'S') {
			readarticles(articleFile, articles, articlesPos);
		}

		if (choice == 'd' || choice == 'D') {
			cout << "Enter the id of the article you want to delete (0 is to exit): ";
			cin >> id;

			while (id < 0 || id > articles.size()) {
				cout << "Enter a valid ID (0 to exit): ";
				cin >> id;
			}

			if (id != 0) {
				cout << articles[id - 1]->toString() << endl
					<< "Do you really wish to delete the following article (y/n): ";
				cin >> del;
				while (!(del == 'y' || del == 'Y' || del == 'n' || del == 'N')) {
					cout << "Please enter a valid choice, y or n: ";
					cin >> del;
				}

				if (del == 'y' || del == 'Y') {
					if (!outDeletedArticles) {
						cerr << "The deleted articles file could not be opened." << endl;
						exit(EXIT_FAILURE);
					}

					loc = outDeletedArticles.eof();
					articles[id - 1]->toFile(outDeletedArticles, &loc);
					readarticles(deletedArticleFile, deletedArticles, deletedArticlesPos);

					outArticles.close();
					remove(articleFile.c_str());

					loc = 0;
					for (i = 0; i < articles.size(); i++) {
						if (i == (id - 1)) {
							articles[i]->toFile(outArticles, &loc);
						}
					}

					readarticles(articleFile, articles, articlesPos);
				}
			}
		}
	}
}

void changearticle(const static string& articleFile, vector<Article*> articles, vector<int> articlesPos)
{
	char choice = 'l', change = 'b', yes, season;
	int id, dia, alu, pos, oristock, width, height;
	float price;
	bool aluminum;
	string manufacturer, colorIndex;
	Rim tempRim{ "", "", NULL, NULL, NULL, '\0', false, "", NULL };
	Tire tempTire{ "", "", NULL, NULL, NULL, '\0', NULL, NULL, "", '\0' };
	ifstream readArticle(articleFile, ios::in | ios::binary);
	ofstream writeArticle(articleFile, ios::out | ios::binary);

	while (!(choice == 'e' || choice == 'E')) {
		cout << "Do you wish to search for an article (s), change an article (c) or exit (e): ";
		cin >> choice;
		
		if (choice == 's' || choice == 'S') {
			searcharticle(articles);
		}

		if (choice == 'c' || choice == 'C') {
			cout << "Enter the id of the article you wish to change (0 to exit): ";
			cin >> id;

			while (id < 0 || id > articles.size()) {
				cout << "Enter a valid ID (0 to exit): ";
				cin >> id;
			}

			if (id != 0) {
				if (!readArticle) {
					cerr << "A problem occured opening the file." << endl;
					exit(EXIT_FAILURE);
				}

				pos = articlesPos[id - 2];

				if (articles[id - 1]->getType() == 'r' || articles[id - 1]->getType() == 'R') {
					tempRim.fromFile(readArticle, &pos);
				}
				if (articles[id - 1]->getType() == 't' || articles[id - 1]->getType() == 'T') {
					tempTire.fromFile(readArticle, &pos);
				}
				pos = articlesPos[id - 2];

				while (!(change == 'e' || change == 'E')) {
					

					cout << articles[id - 1]->toString() << endl
						<< "What do you wish to change about the article, the manufacturer (m), stock ammount (s), the diameter (d), the price (p), ";
					if (articles[id - 1]->getType() == 'r' || articles[id - 1]->getType() == 'R') {
						cout << "the aluminum (a), the color (c), the width (w), ";
					}
					if (articles[id - 1]->getType() == 't' || articles[id - 1]->getType() == 'T') {
						cout << "the width (w), the height (h), the speed index (i), the season (a), ";
					}

					cout << "or to exit the loop (e): ";
					cin >> change;

					if (change == 'm' || change == 'M') {
						cout << "Please enter the new name of the manufacturer: ";
						cin >> manufacturer;
						if (articles[id - 1]->getType() == 'r' || articles[id - 1]->getType() == 'R') {
							tempRim.setManufacturer(manufacturer);
						}
						else {
							tempTire.setManufacturer(manufacturer);
						}
					}

					if (change == 's' || change == 'S') {
						oristock = articles[id - 1]->getStock();
						updatestock(articleFile, articles, articlesPos, id, 0);
						if (articles[id - 1]->getType() == 'r' || articles[id - 1]->getType() == 'R') {
							tempRim.setStock(articles[id - 1]->getStock());
						}
						else {
							tempTire.setStock(articles[id - 1]->getStock());
						}
						articles[id - 1]->setStock(oristock);
					}

					if (change == 'd' || change == 'D') {
						cout << "Please enter the new diameter: ";
						cin >> dia;
						while (dia <= 0) {
							cout << "The diameter must be larger than 0";
							cin >> dia;
						}
						if (articles[id - 1]->getType() == 'r' || articles[id - 1]->getType() == 'R') {
							tempRim.setDiameter(dia);
						}
						else {
							tempTire.setDiameter(dia);
						}
					}

					if (change == 'p' || change == 'P') {
						cout << "Please enter the new price: ";
						cin >> price;
						while (price <= 0) {
							cout << "The price must be larger than 0";
							cin >> price;
						}
						if (articles[id - 1]->getType() == 'r' || articles[id - 1]->getType() == 'R') {
							tempRim.setPrice(price);
						}
						else {
							tempTire.setPrice(price);
						}
					}

					if ((change == 'a' || change == 'A') && (articles[id - 1]->getType() == 'r' || articles[id - 1]->getType() == 'R')) {
						cout << "Is the rim made of aluminum (1) or not (0): ";
						cin >> alu;
						while (!(alu == 0 || alu == 1)) {
							cout << "Enter either a 0 (not aluminum) or 1 (aluminum): ";
							cin >> alu;
						}
						if (alu == 0) {
							aluminum = false;
						}
						else {
							aluminum = true;
						}
						tempRim.setAluminum(aluminum);
					}

					if ((change == 'c' || change == 'C') && (articles[id - 1]->getType() == 'r' || articles[id - 1]->getType() == 'R')) {
						cout << "Enter the new color: ";
						cin >> colorIndex;
						tempRim.setColor(colorIndex);
					}

					if ((change == 'w' || change == 'W') && (articles[id - 1]->getType() == 'r' || articles[id - 1]->getType() == 'R')) {
						cout << "Enter the new width: ";
						cin >> width;
						while (width <= 0) {
							cout << "The width must be larger than 0: ";
							cin >> width;
						}
						tempRim.setWidth(width);
					}

					if ((change == 'w' || change == 'W') && (articles[id - 1]->getType() == 't' || articles[id - 1]->getType() == 'T')) {
						cout << "Enter the new width: ";
						cin >> width;
						while (width <= 0) {
							cout << "The width must be larger than 0: ";
							cin >> width;
						}
						tempTire.setWidth(width);
					}

					if ((change == 'h' || change == 'H') && (articles[id - 1]->getType() == 't' || articles[id - 1]->getType() == 'T')) {
						cout << "Enter the new height: ";
						cin >> height;
						while (height <= 0) {
							cout << "The height must be larger than 0: ";
							cin >> height;
						}
						tempTire.setHeight(height);
					}

					if ((change == 'i' || change == 'I') && (articles[id - 1]->getType() == 't' || articles[id - 1]->getType() == 'T')) {
						cout << "Enter the new speed index: ";
						cin >> colorIndex;
						tempTire.setSpeedIndex(colorIndex);
					}

					if ((change == 'a' || change == 'A') && (articles[id - 1]->getType() == 't' || articles[id - 1]->getType() == 'T')) {
						cout << "Enter the new season: ";
						cin >> season;
						while (!(season == 's' || season == 'S' || season == 'w' || season == 'W')) {
							cout << "The season must be either summer(s) or winter (w): ";
							cin >> season;
						}
						tempTire.setSeason(season);
					}
				}

				if (articles[id - 1]->getType() == 'r' || articles[id - 1]->getType() == 'R') {
					cout << "The article would be changed from:" << endl
						<< articles[id - 1]->toString() << endl << "to" << endl << tempRim.toString();
				}
				if (articles[id - 1]->getType() == 't' || articles[id - 1]->getType() == 'T') {
					cout << "The article would be changed from:" << endl
						<< articles[id - 1]->toString() << endl << "to" << endl << tempTire.toString() << endl;
				}

				cout << "Do you wish to save your changes (y/n): ";
				cin >> yes;
				while (!(yes == 'y' || yes == 'Y' || yes == 'n' || yes == 'N')) {
					cout << "Enter a valid choice, y or n: ";
					cin >> yes;
				}

				if (yes == 'y' || yes == 'Y') {
					if (articles[id - 1]->getType() == 'r' || articles[id - 1]->getType() == 'R') {
						tempRim.toFile(writeArticle, &pos);
					}
					if (articles[id - 1]->getType() == 't' || articles[id - 1]->getType() == 'T') {
						tempTire.toFile(writeArticle, &pos);
					}
					readarticles(articleFile, articles, articlesPos);
				}
			}
		}
	}
}

void readcustomers(const static string& customerFile, vector<Customer*> customers, vector<int> customersPos) {
	ifstream inCustomer(customerFile, ios::in | ios::binary);
	Customer checkCustomer{ "", "", '\0' };
	Company tempCompany{ "", "", '\0', "", NULL };
	int tempPos, customerPos = 0;
	customers.clear();

	if (!inCustomer) {
		cerr << "The customer file could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	tempPos = customerPos;
	checkCustomer.fromFile(inCustomer, &customerPos);

	while (checkCustomer.getType() != '\0') {
		if (checkCustomer.getType() == 'o' || checkCustomer.getType() == 'O') {
			customerPos = tempPos;
			tempCompany.fromFile(inCustomer, &customerPos);
			customers.push_back(new Company(tempCompany));
		}
		else {
			customers.push_back(new Customer(checkCustomer));
		}
		customersPos.push_back(customerPos);

		tempPos = customerPos;
		checkCustomer.setType('\0');
		checkCustomer.fromFile(inCustomer, &customerPos);
	}
}

void searchcustomer(vector<Customer*> customers)
{
	char filter, choice = 'l';
	string search;
	int i;
	ostringstream stream;

	while (!(choice == 'e' || choice == 'E'))
	{
		cout << "Do you wish to do a normal search (n), do a filtered search (f) or exit (e)?" << std::endl;
		cin >> choice;
		if (choice == 'n' || choice == 'N')
		{
			cout << "Do you wish to look at all of the items (all), or look for a specific object (just type what you are looking for)?" << std::endl;
			getline(cin, search);
			if (search.compare("all") == 0 || search.compare("All") == 0)
			{
				stream << "ID" << setw(3) << "Name" << setw(NAME) << "Address" << setw(ADDRESS) << "Type" << setw(10) << "VAT" << setw(VATNUM) << "Volume Discount" << endl;
				for (i = 0; i < customers.size(); i++) {
					stream << (i + 1) << setw(3) << customers[i]->toTable() << endl;
				}
				cout << stream.str();
			}
			else
			{
				stream << "ID" << setw(3) << "Name" << setw(NAME) << "Address" << setw(ADDRESS) << "Type" << setw(10) << "VAT" << setw(VATNUM) << "Volume Discount" << endl;
				for (i = 0; i < customers.size(); i++) {
					if (isSubstring(search, customers[i]->getName())) {
						stream << (i + 1) << setw(3) << customers[i]->toTable() << endl;
					}
				}
				cout << stream.str();
			}
		}

		if (choice == 'f' || choice == 'F')
		{
			cout << "Do you wish to look at only customers (u), or only companies (o): ";
			cin >> filter;
			while (!(filter == 'u' || filter == 'U' || filter == 'o' || filter == 'O')) {
				cout << "Enter a valid choice (o/u): ";
				cin >> filter;
			}
			if (filter == 'u' || filter == 'U')
			{
				cout << "Do you wish to look at all of the customers (all), or look for a specific object (just type what you are looking for)?" << std::endl;
				getline(cin, search);
				if (search.compare("all") == 0 || search.compare("All") == 0)
				{
					stream << "ID" << setw(3) << "Name" << setw(NAME) << "Address" << setw(ADDRESS) << "Type" << setw(10) << "VAT" << setw(VATNUM) << "Volume Discount" << endl;
					for (i = 0; i < customers.size(); i++) {
						if (customers[i]->getType() == 'u' || customers[i]->getType() == 'U') {
							stream << (i + 1) << setw(3) << customers[i]->toTable() << endl;
						}
					}
					cout << stream.str();
				}
				else
				{
					stream << "ID" << setw(3) << "Name" << setw(NAME) << "Address" << setw(ADDRESS) << "Type" << setw(10) << "VAT" << setw(VATNUM) << "Volume Discount" << endl;
					for (i = 0; i < customers.size(); i++) {
						if ((customers[i]->getType() == 'u' || customers[i]->getType() == 'U') && isSubstring(search, customers[i]->getName())) {
							stream << (i + 1) << setw(3) << customers[i]->toTable() << endl;
						}
					}
					cout << stream.str();
				}
			}

			if (filter == 'o' || filter == 'O')
			{
				cout << "Do you wish to look at all of the items (all), or look for a specific object (just type what you are looking for)?" << std::endl;
				getline(cin, search);
				if (search.compare("all") == 0 || search.compare("All") == 0)
				{
					stream << "ID" << setw(3) << "Name" << setw(NAME) << "Address" << setw(ADDRESS) << "Type" << setw(10) << "VAT" << setw(VATNUM) << "Volume Discount" << endl;
					for (i = 0; i < customers.size(); i++) {
						if (customers[i]->getType() == 'o' || customers[i]->getType() == 'O') {
							stream << (i + 1) << setw(3) << customers[i]->toTable() << endl;
						}
					}
					cout << stream.str();
				}
				else
				{
					stream << "ID" << setw(3) << "Name" << setw(NAME) << "Address" << setw(ADDRESS) << "Type" << setw(10) << "VAT" << setw(VATNUM) << "Volume Discount" << endl;
					for (i = 0; i < customers.size(); i++) {
						if ((customers[i]->getType() == 'o' || customers[i]->getType() == 'O') && isSubstring(search, customers[i]->getName())) {
							stream << (i + 1) << setw(3) << customers[i]->toTable() << endl;
						}
					}
					cout << stream.str();
				}
			}
		}
	}
}

void addcustomer(const static string& customerFile, vector<Customer*> customers, vector<int> customersPos)
{
	int i, discount, loc;
	char type, choice = 'x';
	string name, address, VAT;
	ofstream outCustomer;
	Customer* customer;
	bool customerAdd;

	while (!(choice == 'e' || choice == 'E')) {
		customerAdd = false;
		cout << "Do you wish to add a customer (u), company (o) or exit (e): ";
		cin >> choice;

		if (choice == 'u' || choice == 'U') {
			cout << "Enter the name: ";
			cin >> name;

			cout << "Enter the address: ";
			cin >> address;

			customer = new Customer(name, address, 'u');
			customerAdd = true;
		}

		if (choice == 'r' || choice == 'R')
		{
			cout << "Enter the name: ";
			cin >> name;

			cout << "Enter the address: ";
			cin >> address;

			cout << "Enter the VAT: ";
			cin >> VAT;

			cout << "Enter the volume discount: ";
			cin >> discount;
			while (discount < 0) {
				cout << "The discount can't be negative. Enter a valid discount: ";
				cin >> discount;
			}

			customer = new Company(name, address, 'o', VAT, discount);
			customerAdd = true;
		}

		if (customerAdd) {
			if (!outCustomer) {
				cerr << "Something went wrong opening the customer file." << endl;
				exit(EXIT_FAILURE);
			}

			loc = outCustomer.eof();
			customer->toFile(outCustomer, &loc);

			readcustomers(customerFile, customers, customersPos);
		}
	}
}

void deletecustomer(const static string& customerFile, vector<Customer*> customers, vector<int> customersPos, const static string& deletedCustomerFile, vector<Customer*> deletedCustomers, vector<int> deletedCustomersPos)
{
	;
}

void changecustomer(vector<Customer*> customers)
{
	;
}

void readinvoices(const static string& invoiceFile, vector<Invoice*> invoices) {
	ifstream inInvoice(invoiceFile, ios::in | ios::binary);
	Customer customer{ "", "", '\0' };
	Article article{ "", "", NULL, NULL, NULL, '\0' };
	array<Article, ARTIEKELEN> articles = { article, article, article, article, article, article, article, article , article, article, article, article , article, article, article, article ,article, article, article, article , article, article, article, article , article, article, article, article, article, article, article, article, article , article, article, article, article , article, article, article, article ,article, article, article, article , article, article, article, article , article };
	Invoice invoice{ customer, articles, NULL, NULL };
	invoices.clear();

	if (!inInvoice) {
		cerr << "The invoice file could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	invoice.fromFile(inInvoice);

	while (invoice.getPrice() != NULL) {
		invoices.push_back(new Invoice(invoice));
		invoice.setPrice(NULL);
		invoice.fromFile(inInvoice);
	}
}

void searchinvoice(vector<Invoice*> invoices)
{
	;
}

void makeorder(const static string& invoiceFile, vector<Invoice*> invoices, const static string& articleFile, vector<Article*> articles, vector<int> articlesPos, const static string& customerFile, vector<Customer*> customers, vector<int> customersPos, const static string& tireCenterFile, vector<TireCenter*> tireCenters, int id)
{
	;
}

void changeinvoice(vector<Invoice*>);

void readtirecenters(const static string& tireCenterFile, vector<TireCenter*> tireCenters) {
	ifstream inTireCenter(tireCenterFile, ios::in | ios::binary);
	Article article{ "", "", NULL, NULL, NULL, '\0' };
	array<Article, ARTIEKELEN> articles = { article, article, article, article, article, article, article, article , article, article, article, article , article, article, article, article ,article, article, article, article , article, article, article, article , article, article, article, article, article, article, article, article, article , article, article, article, article , article, article, article, article ,article, article, article, article , article, article, article, article , article };
	Customer customer{ "", "", '\0' };
	array<Customer, CUSTOMERS> customers = { customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer, customer };
	TireCenter tireCenter{ "", "", articles, customers};
	tireCenters.clear();

	if (!inTireCenter) {
		cerr << "The tire center file could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	tireCenter.fromFile(inTireCenter);

	while (!(tireCenter.getName().compare(""))) {
		tireCenters.push_back(new TireCenter(tireCenter));
		tireCenter.setName("");
		tireCenter.fromFile(inTireCenter);
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

void addtirecenter(const static string& tireCenterFile, vector<TireCenter*> tireCenters, vector<Article*> articles, vector<Customer*> customers) {
	;
}

void updatestock(const static string& articleFile, vector<Article*> articles, vector<int> articlesPos, int id, int ammount)
{
	int newID, newAmmount = 0;											//zodat automatisch update als ammount word mee gegeven
	char achoice, choice = 'c';										//zodat het automatisch update als een id word mee gegeven
	ofstream changeArticle(articleFile, ios::out | ios::binary);

	while (!(choice == 'e' || choice == 'E')) {
		if (id == 0) {
			cout << "Do you wish to search for an article (s), change the stock (c), or exit (e): ";
			cin >> choice;
			if (choice == 'c' || choice == 'C') {
				cout << "Give the id of the product you wish to change (enter 0 to exit): ";
				cin >> newID;

				while (newID < 0 || newID > articles.size()) {
					cout << "Enter a valid ID (0 to exit): ";
					cin >> newID;
				}
			}
		}
		else {
			newID = id;
		}

		if (choice == 's' || choice == 'S') {
			searcharticle(articles);
		}

		if (choice == 'c' || choice == 'C') {
			if (ammount == 0) {
				cout << "Do you wish to add an ammount (a), subtract an ammount (s) or just choose the ammount (c): ";
				cin >> achoice;
				while (!(achoice == 'a' || achoice == 'A' || achoice == 's' || achoice == 'S' || achoice == 'c' || achoice == 'C')) {
					cout << "Please enter a valid choice, a, s, or c: ";
					cin >> achoice;
				}

				if (achoice == 'a' || achoice == 'A') {
					cout << "Enter the ammount you would like to add: ";
					cin >> newAmmount;
					while (-(newAmmount) > articles[id - 1]->getStock()) {
						cout << "Stock can't become negative. Enter a valid number";
						cin >> newAmmount;
					}

					newAmmount += articles[id - 1]->getStock();
				}

				if (achoice == 's' || achoice == 'S') {
					cout << "Enter the ammount you would like to subtract: ";
					cin >> newAmmount;
					while (newAmmount > articles[id - 1]->getStock()) {
						cout << "Stock can't become negative. Enter a valid number";
						cin >> newAmmount;
					}

					newAmmount = articles[id - 1]->getStock() - newAmmount;
				}

				if (achoice == 'a' || achoice == 'A') {
					cout << "Enter the ammount you would like to add: ";
					cin >> newAmmount;
					while (newAmmount < 0) {
						cout << "Stock can't become negative. Enter a valid number";
						cin >> newAmmount;
					}
				}
			}
			else {
				newAmmount = ammount;
			}

			articles[id - 1]->setStock(newAmmount);
			if (id == 0) {
				if (!changeArticle) {
					cerr << "An error occurred opening the article file." << endl;
					exit(EXIT_FAILURE);
				}

				articles[id - 1]->toFile(changeArticle, &articlesPos[id - 2]);
				readarticles(articleFile, articles, articlesPos);
			}
		}

		if (id != 0) {
			choice = 'e';
		}
	}
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