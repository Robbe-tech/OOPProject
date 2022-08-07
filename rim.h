#ifndef RIM_H
#define RIM_H
#define COLOR 10

#include <string>
#include "article.h"

class rim : public article {
public:
	rim(const string&, const string&, int, const int, float, const char, const bool, const string&, const int);
	virtual ~rim() = default;

	void setAluminum(const bool);
	int getAluminum() const;

	void setColor(const string&);
	string getColor() const;

	void setWidth(const int);
	int getWidth() const;
	
	virtual string toString() const override;
	virtual string toTable() const override;

	virtual void toFile(const static string&, static int) override;
	virtual void fromFile(const static string&, static int) override;
private:
	bool aluminum;
	char color[COLOR];
	int width;
};

#endif