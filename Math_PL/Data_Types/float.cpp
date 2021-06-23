#include <iostream>
#include <string>

using namespace std;

class Float
{
public:
	void set_name(string name)
	{
		this->name = name;
	}

	void set_value(double value)
	{
		this->value = value;
	}

	string get_name()
	{
		return this->name;
	}

	double get_value()
	{
		return this->value;
	}

private:
	double value;
	string name;
};