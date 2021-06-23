#include <iostream>
#include <string>

using namespace std;

class Receive_Operator
{
public:
	int aux_i;
	bool value_not_defined = false;

	string get_name(string line, int i)
	{
		string name = "";

		bool name_founded = false;

		while (!name_founded)
		{
			if (line[i + 1] == '=')
			{
			    name_founded = true;
				this->value_not_defined = false;
				break;
			}

			else if (line[i] == ';')
			{
				name_founded = true;
				this->value_not_defined = true;
				break;
			}

			while (line[i] == ' ')
				i++;

			name += line[i];

			i++;
		}

		if (!value_not_defined)
			this->aux_i = ((line[i] == ' ') ? i + 2 : i);

		return name;
	}

	string get_type(string line)
	{
		string type = "";

		int i = 0;

		bool type_founded;

		while (!type_founded)
		{
			while (line[i] == ' ')
				i++;

			type += line[i];

			if (line[i + 1] == ' ')
				type_founded = true;

			i++;
		}

		this->aux_i = i;
			
		return type;
	}

	template <typename T> 
	T get_expr(string line, int i, string type)
	{
		int i_aux_expr;
		double d_aux_expr;

		string aux_expr = "";

		bool endline = false;

		while (!endline)
		{
			while (line[i] == ' ')
				i++;

			aux_expr += line[i];

			if (line[i + 1] == ';')
			{
				endline = true;
			}

			i++;
		}

		i_aux_expr = stoi(aux_expr);
		d_aux_expr = atof(aux_expr.c_str());
		
		if (type == "integer")
			return i_aux_expr;
		
		else if (type == "double")
			return d_aux_expr;

		else
			return (T)-1;
	}
};