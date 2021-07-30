#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

// PROTOTYPES
void EnsureEqual(const string& left, const string& right);

int main (int argc, char** argv)
{
    try {
        EnsureEqual("C++ White", "C++ White");
        EnsureEqual("C++ White", "C++ Yellow");
    }
    catch (runtime_error& e) {
        cout << e.what() << endl;
    }
    return 0;
}

// IMPLEMENTATION
void EnsureEqual(const string& left, const string& right)
{
	if (left != right) throw runtime_error(left + " != " + right);
}