//question c)
#include <iostream>
#include <iomanip>

using namespace std;

double ctok(double c);
class IllegalInput {};
int main() {
    double c = 0;
    double k;

    cout << "Celcius: ";
    cin >> c;

    try{
        if((k = ctok(c)) < 0) throw IllegalInput{};
        cout << "Kelvin: " << k << '\n';
    }
    catch(IllegalInput){
        cerr << "Error reporting!" << endl;
    }

    return 0;
}

double ctok(double c) {
    double k = c + 273.15;
    return k;
}