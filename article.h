#ifndef ARTICLE_H
#define ARTICLE_H
#define CHAR 20

#include <string>

using namespace std;

class article {
public:
	article(const string&, const string&, int, const int, float, const char);
	virtual ~article() = default;

	void setName(const string&);
	string getName() const;

	void setManufacturer(const string&);
	string getManufacturer() const;

	void setStock(int);
	int getStock() const;

	void setDiameter(const int);
	int getDiameter() const;

	void setPrice(float);
	float getPrice() const;

	void setType(const char);
	char getType() const;

	virtual string toString() const;
	virtual string toTable() const;

	virtual void toFile(const string& file, static int pos);
	virtual void fromFile(const string& file, static int pos);
private:
	char name[CHAR];
	char manufacturer[CHAR];
	int stock;
	int diameter;
	float price;
	char type;
};

#endif