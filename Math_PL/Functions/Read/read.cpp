#include <iostream>
#include <string>

using namespace std;

class Read
{
public:
    template <typename T>
    T read_input()
    {
        T input;

        cin >> input;

        return input;
    }

    string get_name(string line, int i)
    {
        string name = "";

        bool name_founded = false;

        while (!name_founded)
        {
            while (line[i] == ' ')
                i++;

            name += line[i];

            if (line[i + 1] == ';')
            {
                name_founded = true;
                break;
            }

            else
                i++;
        }

        return name;
    }

    template <typename T>
    int get_var_index(string name, T vars[])
    {
        int index = 0;

        bool founded = false;

        while (!founded)
        {
            if (vars[index].get_name() == name)
            {
                founded = true;
                break;
            }

            else
                index++;
        }

        return index;
    }
};