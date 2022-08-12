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
			addarticle(articleFile, articles, articlesPos);
			while (articles.empty()) {
				cout << "Please add at least one article." << endl;
				addarticle(articleFile, articles, articlesPos);
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

void readarticles(const static string& articleFile, vector<Article*> articles, vector<int> articlesPos) {
	ifstream inArticle(articleFile, ios::in | ios::binary);
	Article* checkarticle;
	int* articlePos = 0;
	articles.clear();
	/*Rim tempRim{"", "", NULL, NULL, NULL, '\0', false, "", NULL};
	Tire tempTire{ "", "", NULL, NULL, NULL, '\0', NULL, NULL, "", '\0' };*/

	if (!inArticle) {
		cerr << "The article file could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	/*checkArticleType.fromFile(inArticle, articlePos);*/

	while (inArticle.peek() != EOF) {
		/*if (checkArticleType.getType() == 'r' || checkArticleType.getType() == 'R') {
			tempRim.fromFile(inArticle, articlePos);
			articles.push_back(new Rim(tempRim));
		}
		else {
			tempTire.fromFile(inArticle, articlePos);
			articles.push_back(new Tire(tempTire));
		}*/
		checkarticle->fromFile(inArticle, articlePos);
		articlesPos.push_back(*articlePos);
		articles.push_back(checkarticle);
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
	char choice = 'l';
	int id;

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
				cout << articles[id - 1]->toString() << endl
					<< "What do you wish to change about the article, the name (n), the manufacturer (m), stock ammount (s),  ";
				cin >> del;
			}
		}
	}
}

void readcustomers(const static string& customerFile, vector<Customer*> customers, vector<int> customersPos) {
	ifstream inCustomer(customerFile, ios::in | ios::binary);
	Customer* customer;
	int* customerPos = 0;
	customers.clear();

	if (!inCustomer) {
		cerr << "The cusomer file could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	//checkCustomer->fromFile(inCustomer, customerPos);

	while (inCustomer.peek() != EOF) {
		/*if (checkCustomer.getType() == 'o' || checkCustomer.getType() == 'O') {
			*customerPos = tempPos;
			tempCompany.fromFile(inCustomer, customerPos);
			customers.push_back(new Company(tempCompany));
		}
		else {
			customers.push_back(new Customer(checkCustomer));
		}*/
		customer->fromFile(inCustomer, customerPos);
		customersPos.push_back(*customerPos);
		customers.push_back(customer);
	}
}

void searchcustomer(vector<Customer*> customers)
{
	;
}

void addcustomer(vector<Customer*> customers)
{
	;
}

void deletecustomer(vector<Customer*> customers)
{
	;
}

void changecustomer(vector<Customer*> customers)
{
	;
}

void readinvoices(const static string& invoiceFile, vector<Invoice*> invoices) {
	ifstream inInvoice(invoiceFile, ios::in | ios::binary);
	Invoice* invoice;
	invoices.clear();

	if (!inInvoice) {
		cerr << "The cusomer file could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	while (inInvoice.peek() != EOF) {
		invoice->fromFile(inInvoice);
		invoices.push_back(invoice);
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
	TireCenter* tireCenter;
	tireCenters.clear();

	if (!inTireCenter) {
		cerr << "The cusomer file could not be opened." << endl;
		exit(EXIT_FAILURE);
	}

	while (inTireCenter.peek() != EOF) {
		tireCenter->fromFile(inTireCenter);
		tireCenters.push_back(tireCenter);
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