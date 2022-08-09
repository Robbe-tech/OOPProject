#ifndef RIM_H
#define RIM_H
#define COLOR 10

#include <string>
#include "Article.h"

class Rim : public Article {
public:
	Rim(const string&, const string&, int, const int, float, const char, const bool, const string&, const int);
	virtual ~Rim() = default;

	void setAluminum(const bool);
	int getAluminum() const;

	void setColor(const string&);
	string getColor() const;

	void setWidth(const int);
	int getWidth() const;
	
	virtual string toString() const override;
	virtual string toTable() const override;

	virtual void toFile(ofstream&, int*) override;
	virtual void fromFile(ifstream&, int*) override;
private:
	bool aluminum;
	char color[COLOR];
	int width;
};

#endif