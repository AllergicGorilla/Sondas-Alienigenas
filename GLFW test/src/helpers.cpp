#include "helpers.h"

typedef std::__cxx11::string string;
using namespace std;
string getShaderFromFile(string filepath)
{
    ifstream file(filepath);
    string result;
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            result += line + "\n";
        }
    }
    return result;

}
