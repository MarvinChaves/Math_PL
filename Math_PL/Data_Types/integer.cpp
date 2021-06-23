#include <iostream>
#include <string>

using namespace std;

class Integer
{
public:
	void set_name(string name)
	{
		this->name = name;
	}

	void set_value(int value)
	{
		this->value = value;
	}

	string get_name()
	{
		return this->name;
	}
	
	int get_value()
	{
		return this->value;
	}

private:
	int value;
	string name;
};