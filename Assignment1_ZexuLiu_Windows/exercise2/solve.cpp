#include "solve.h"

void solve() {
    double a, b, c;
    double x1, x2;

    cin >> a >> b >> c;
    if(cin.fail() | a == 0) throw IllegalInput{};

    double delta = b * b - 4 * a * c;
    if(delta < 0) throw InvalidDelta{};

    x1 = (-b + sqrt(delta)) / (2 * a);
    x2 = (-b - sqrt(delta)) / (2 * a);

    cout << setprecision(6) << x1 << ' ' <<  x2 << endl;

    return;
}

