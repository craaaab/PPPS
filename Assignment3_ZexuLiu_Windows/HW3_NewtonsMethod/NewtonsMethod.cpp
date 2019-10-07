#include <iostream>
#include <cmath>

using namespace std;

double f(double x) {
    return 10 * x * x * x - 8.3 * x * x + 2.295 * x - 0.21141;
}

double fdiffer1(double x) {
    return 30 * x * x - 16.6 * x + 2.295;
}

const double x0 = 0.343036;

int main() {
    int cnt = 0;
    double x = x0;

    while(fabs(x - 0.29) > 0.00001) {
        cout << 'x' << cnt++ << ": " << x << '\n';
        x = x - f(x) / fdiffer1(x);
    }
    cout << 'x' << cnt << ": " << x << '\n';
    system("pause");

    return 0;
}