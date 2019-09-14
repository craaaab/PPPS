//question d)
#include <iostream>
#include <iomanip>

using namespace std;

double ctok(double c);
class IllegalInput{};

int main() {
    double c = 0;

    cout << "Celcius: ";
    cin >> c;

    double k = ctok(c);

    cout << "Kelvin: " << k << '\n';


    return 0;
}

double ctok(double c) {
    double k;

    try {
        k = c + 273.15;
        if(k < 0) throw IllegalInput{};
    }
    catch(IllegalInput) {
        cerr << "Error reporting!" << endl;
        exit(-1);
    }

    return k;
}