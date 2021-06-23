/*#include <iostream>
#include <string>

using namespace std;

class Math_Solver
{
public:
    template <typename T>
    T expr_solver(string expr_s)
    {
        string expr = expr_s.erase(remove(expr_s.begin(), expr_s.end(), ' '), expr_s.end());

        T result;

        T numbers[1000];

        string equations[1000];

        int i = 0;
        int n_i = 0;
        int e_i = 0;

        bool end = false;

        while (!end)
        {
            if (expr[i + 1] == ';')
                end = true;

            else if (expr[i] != '+' && expr[i] != '-' && expr[i] != '*' && expr[i] != '/')
            {
                double tmp_res = atof(expr[i]);

                numbers[n_i] = (T)tmp_res;

                n_i++;
                i++;
            }

            else if (expr[i] == '+' && expr[i] == '-' && expr[i] == '*' && expr[i] == '/')
            {
                equations[e_i] = expr[i];

                e_i++;
                i++;
            }
        }

        

        return T;
    }
};*/
