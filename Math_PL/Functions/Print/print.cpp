#include <iostream>
#include <string>

#include "print_exceptions.cpp"

#include "..\..\Data_Types\integer.cpp"
#include "..\..\Data_Types\float.cpp"

using namespace std;

class Print
{
public:
	template <typename T, typename T2>
	T get_expr(string line, int i, int int_line, bool *end_program, T2 vars[])
	{
		Print_Exceptions prt_except;
		
		T exp;
		
		string var_name = "";
		T var_value;

		int int_var_value;
		
		bool init = true;

		bool endline = false;

		bool var_founded = false;

		int o = i;

		char ch;

		while (!endline)
		{
			while (line[i] == ' ')
				i++;

			if (line[i] == '$' && init == true)
			{
				i++;

				bool var_name_found = false;
				bool var_value_found = false;

				int current_var = 0;

				while (!var_name_found)
				{
					var_name += line[i];
					
					if (line[i + 1] == ';')
					{
						var_name_found = true;
					}

					else
						i++;
				}

				while (!var_value_found) 
				{	
					if (vars[current_var].get_name() == var_name)
					{
						var_value = vars[current_var].get_value();

						var_value_found = true;
					}

					else
					{
						if (current_var < 1000)
							current_var++;

						else
						{
							cout << var_name << " could not be found" << endl;

							*end_program = true;
							break;
						}
					}
				}

				if (var_name_found == true && var_value_found == true)
				{
					var_founded = true;
				}
			}

			if (var_founded == true)
			{
				endline = true;
				break;
			}

			if (*end_program == true)
			{
				break;
			}

			exp += line[i];
			ch = line[i];

			if (ch == '\"' || ch == '\'')
			{
				// new exception: PRINT_E001
				prt_except.invalid_DataType(ch, int_line, end_program);
			}

			switch (ch)
			{
				case 'a':
				case 'b':
				case 'c':
				case 'd':
				case 'e':
				case 'f':
				case 'g':
				case 'h':
				case 'i':
				case 'j':
				case 'k':
				case 'l':
				case 'm':
				case 'n':
				case 'o':
				case 'p':
				case 'q':
				case 'r':
				case 's':
				case 't':
				case 'u':
				case 'v':
				case 'w':
				case 'x':
				case 'y':
				case 'z':
				case '!':
				case '@':
				case '#':
				case '$':
				case '%':
				case '&':
				case '*':
					prt_except.invalid_DataType(ch, int_line, end_program);
					break;
			}

			if (line[i + 1] == ';')
			{
				endline = true;
				continue;
			}

			i++;
			o++;
		}

		if (var_founded)
			return var_value;

		else
			return exp;
	}

	string get_var_type(string var_name, Integer int_vars[], Float dbl_vars[])
	{
		int current_index = 0;

		string type;

		bool founded = false;

		bool int_found = true;
		bool dbl_found = false;

		while (int_found) // first Integer
		{
			if (int_vars[current_index].get_name() == var_name)
			{
				type = "integer";
				founded = true;
				int_found = false;
			}

			else
			{
				current_index++;

				if (current_index >= 1000)
				{
					int_found = false;
					dbl_found = true;

					current_index = 0;
				}
			}
		}

		while (dbl_found)
		{
			if (dbl_vars[current_index].get_name() == var_name)
			{
				type = "double";
				founded = true;
				dbl_found = false;
			}

			else
			{
				current_index++;

				if (current_index >= 1000)
				{
					int_found = false;
					dbl_found = false;
				}
			}
		}

		if (!founded)
			return "could'not found var: " + var_name;
		
		else
			return type;
	}
};