#include <iostream>

using namespace std;

class Print_Exceptions
{
public:
	void invalid_DataType(char ch_data, int line, bool *end_program) // ---PRINT_E001---
	{
		cout << "Erro: PRINT_E001" << endl;
		cout << "Line: " << line << endl;
		cout << "\"" << ch_data << "\"" << " is a invalid data type" << endl;

		*end_program = true;
	}
};