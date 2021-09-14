#include <iostream>
#include <fstream>
#include <random>
#include <string>
using namespace std;

int main()
{
    random_device rd;
    mt19937 gen(rd());

    ofstream inputFile;
    inputFile.open("../input.txt");

    int n, range;
    cout << "Numbers of input data : ";
    cin >> n;

    cout << "Maximum of random data : ";
    cin >> range;

    uniform_int_distribution<int> dis(1, range);

    string tmp = to_string(n);
    tmp += '\n';
    inputFile.write(tmp.c_str(), tmp.size());
    for (int i = 1; i < n; i++)
    {
        tmp = to_string(dis(gen));
        tmp += ", ";
        inputFile.write(tmp.c_str(), tmp.size());
    }
    tmp = to_string(dis(gen));
    tmp += '\n';
    inputFile.write(tmp.c_str(), tmp.size());

    inputFile.close();
}