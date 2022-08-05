#ifndef TIRE_H
#define TIRE_H
#define INDEX 10

#include <string>
#include "article.h"

class tire : public article {
public:
	tire(const string&, const string&, int, const int, float, const char, const int, const int, const string&, const char);
	virtual ~tire() = default;

	void setWidth(const int);
	int getWidth() const;

	void setHeight(const int);
	int getHeight() const;

	void setSpeedIndex(const string&);
	string getSpeedIndex() const;

	void setSeason(const char);
	char getSeason() const;

	virtual string toString() const = 0;
	virtual string toTable() const = 0;

	virtual void toFile() const = 0;
	virtual void fromFile() const = 0;
private:
	int width;
	int height;
	char speedIndex[INDEX];
	char season;
};

#endif