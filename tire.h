#ifndef TIRE_H
#define TIRE_H
#define INDEX 10

#include <string>
#include "article.h"

class Tire : public Article {
public:
	Tire(const string&, const string&, int, const int, float, const char, const int, const int, const string&, const char);
	virtual ~Tire() = default;

	void setWidth(const int);
	int getWidth() const;

	void setHeight(const int);
	int getHeight() const;

	void setSpeedIndex(const string&);
	string getSpeedIndex() const;

	void setSeason(const char);
	char getSeason() const;

	virtual string toString() const override;
	virtual string toTable() const override;

	virtual void toFile(ofstream&, streamoff*) override;
	virtual void fromFile(ifstream&, streamoff*) override;
private:
	int width;
	int height;
	char speedIndex[INDEX];
	char season;
};

#endif