#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    string file = "agaricus-lepiota.data";
    ifstream infile(file);

    if (!infile.is_open())
    {
        cout << "Error opening file";
        return 0;
    }
    else
    {
        cout << "File opened";
    }
    infile.close();
    return 0;
}
