/*
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
+	i = 0;                                  +
+	aux_text = "";                          +
+	endline = true;                         +
+                                           +
+	the block above starts a new line       +
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+	                       
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <windows.h>

// don't need to include Integer or Float because Print already include they

#include "Functions/Print/print.cpp"
#include "Functions/Read/read.cpp"

// #include "Math/math_solver.cpp"

#include "Operators/Attribution/receive.cpp"

using namespace std;

// this class do not anything
class AuxObject
{
public:
private:
protected:
};

int main(int argc, char *argv[])
{
	// Objects

	// ineteger data_type
	Integer int_vars[1001];

	// double data_type
	Float dbl_vars[1001];

	// this obj is so helpful to use with var declaration
	Receive_Operator receive;

	// PRINT
	Print prt;

	// READ
	Read read;

	// MATH
	// Math_Solver math;

	// file to "compile"
	ifstream file;

	// why i created these ???
	int current_int_var_index = 0;
	int current_dbl_var_index = 0;

	file.open("m.txt");

	// i was too lazy to work with char and char array or char pointer
	// so i decided to use string library :)
	string text_file;
	string aux_text;

	int i = 0;

	// this is useful with exceptions
	int line = 0;
	
	bool endfile = false;
	bool endline = false;

	bool end_program = false;

	while (!endfile)
	{
		endline = false;
		line++;

		// gets a line in source file
		getline(file, text_file);

		while (!endline)
		{
			aux_text += text_file[i];

			// end of a file
			if (aux_text == "end")
			{
				endline = true;
				endfile = true;
				aux_text = "";
				i = 0;
			}

			// a empty line
			if (text_file == "")
			{
				endline = true;
				aux_text = "";
				i = 0;
				continue;
			}

			if (text_file[0] == '$')
			{
				i = 1;

				aux_text = "";

				while (text_file[i] != ' ')
				{
					aux_text += text_file[i];

					i++;
				}

				bool is_var_name = true;

				int aux = 0;

				while (is_var_name)
				{
					if (aux_text == int_vars[aux].get_name())
					{
						string name = receive.get_name(text_file, 1);
						int value = receive.get_expr<int>(text_file, receive.aux_i, "integer");

						int_vars[aux].set_value(value);

						i = 0;
						aux_text = "";
						endline = true;

						break;
					}

					else if (aux_text == dbl_vars[aux].get_name())
					{
						string name = receive.get_name(text_file, 1);
						double value = receive.get_expr<double>(text_file, receive.aux_i, "double");

						dbl_vars[aux].set_value(value);

						i = 0;
						aux_text = "";
						endline = true;

						break;
					}

					else
						aux++;
				}
			}

			if (aux_text == "print")
			{
				int i_exp;
				double d_exp;
				string s_exp;

				string print_type;

				i++;

				bool is_var_print = false;
				bool is_number_print = false;
				bool is_expr_value_print = false;

				int tmp_i = i + 1;

				// the operator '$' get a var value (try)
				if (text_file[tmp_i] == '$')
					is_var_print = true;
				
				else if (text_file[tmp_i] == '*')
					is_expr_value_print = true;

				else
					// single number print
					is_number_print = true;

				// execute the block bellow if print is a single number: print 10; or print 9.2;
				if (is_number_print)
				{
					s_exp = prt.get_expr<string, Integer>(text_file, i, line, &end_program, int_vars);
					print_type = "string";
				}
				
				// the block bellow try to find a var name
				else if (is_var_print)
				{
					string type;

					bool name_founded = false;

					int o = tmp_i + 1;

					string var_name = "";

					while (!name_founded)
					{
						var_name += text_file[o];

						if (text_file[o + 1] == ';')
							name_founded = true;
						
						o++;
					}

					// get a type of a var in print: print $var_name;
					type = prt.get_var_type(var_name, int_vars, dbl_vars);
					
					// i_exp is a integer var output
					if (type == "integer")
					{
						i_exp = prt.get_expr<int, Integer>(text_file, i, line, &end_program, int_vars);
						print_type = "integer";
					}
					
					// d_exp is a double var output
					else if (type == "double")
					{
						d_exp = prt.get_expr<double, Float>(text_file, i, line, &end_program, dbl_vars);
						print_type = "double";
					}
				}

				/*else if (is_expr_value_print)
				{
					i++;

					string expr = "";

					int result;

					bool expr_ended = false;

					while (!expr_ended)
					{
						expr += text_file[i];

						if (text_file[i + 1] == ';')
						{
							expr += text_file[i + 1];
							break;
						}
						
						i++;
					}

					result = math.expr_solver<int>(expr);
				}*/
				
				// only execute the block bellow is the interpreter have not found any exception in code
				if (!end_program)
					// string ????????!!
					if (print_type == "string")
						cout << s_exp << endl;
					
					// integer data_type output
					else if (print_type == "integer")
						cout << i_exp << endl;

					// double data_type output
					else if (print_type == "double")
						cout << d_exp << endl;

				// new line
				aux_text = "";
				i = 0;
				endline = true;
			}

			// vars data_types
			else if (aux_text == "int" || aux_text == "double")
			{
				if (aux_text == "int")
				{
					int_vars[current_int_var_index].set_name(receive.get_name(text_file, 4));

					// if var have a defined value
					if (!receive.value_not_defined)
						int_vars[current_int_var_index].set_value(receive.get_expr<int>(text_file, receive.aux_i, "integer"));
					
					// else
					else
						// set var_value as 0
						int_vars[current_int_var_index].set_value(0);

					// new line
					endline = true;
					i = 0;
					aux_text = "";

					// the max is 1000
					current_int_var_index++;
				}

				else if (aux_text == "double")
				{
					dbl_vars[current_dbl_var_index].set_name(receive.get_name(text_file, 7));

					// set a var name
					if (!receive.value_not_defined)
						dbl_vars[current_dbl_var_index].set_value(receive.get_expr<double>(text_file, receive.aux_i, "double"));
					
					// else
					else
						// set var_value as 0.0
						dbl_vars[current_dbl_var_index].set_value(0.0);

					// new line
					endline = true;
					i = 0;
					aux_text = "";

					// the max is: 1000
					current_dbl_var_index++;
				}
			}

			else if (aux_text == "read")
			{
				i++;

				string name = read.get_name(text_file, i);
				string type = prt.get_var_type(name, int_vars, dbl_vars);

				int int_value;
				double dbl_value;

				int int_index;
				int dbl_index;

				if (type == "integer")
				{
					int_value = read.read_input<int>();
					int_index = read.get_var_index<Integer>(name, int_vars);

					int_vars[int_index].set_value(int_value);
				}

				else if (type == "double")
				{
					dbl_value = read.read_input<double>();
					dbl_index = read.get_var_index<Float>(name, dbl_vars);

					dbl_vars[dbl_index].set_value(dbl_value);
				}

				// new line
				i = 0;
				endline = true;
				aux_text = "";
			}

			else if (aux_text == "newline")
			{
				cout << endl;

				// new line
				i = 0;
				endline = true;
				aux_text = "";
			}

			else if (aux_text == "clear")
			{
				system("cls");

				// new line
				i = 0;
				endline = true;
				aux_text = "";
			}

			else if (aux_text == "wait")
			{
				i++;

				string s_num = "";

				bool duration_founded = false;

				while (!duration_founded)
				{
					while (text_file[i] == ' ')
						i++;

					s_num += text_file[i];

					if (text_file[i + 1] == ';')
						duration_founded = true;

					i++;
				}

				Sleep(stoi(s_num));

				// new line
				i = 0;
				endline = true;
				aux_text = "";
			}

			else
				i++;

			// this block is to finish the interpreter after a exception
			if (end_program)
			{
				return 1;
			}
		}
	}

	// why have a comment here ??
	return 0;
}

// end of CODE
