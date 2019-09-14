//question a)
#include <iostream>
#include <iomanip>

using namespace std;

double ctok(double c);

int main() {
    double c = 0;

    cout << "Celcius: ";
    cin >> c;

    double k = ctok(c);

    cout << "Kelvin: " << k << '\n';

    return 0;
}

double ctok(double c) {
    double k = c + 273.15;
    return k;
}