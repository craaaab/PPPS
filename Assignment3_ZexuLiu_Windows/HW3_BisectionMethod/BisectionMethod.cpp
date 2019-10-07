#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double f(double x) {
    return 10 * x  * x * x - 8.3 * x * x + 2.295 * x - 0.21141;
}

const double a = 0.28516, b=  0.400912;

int main() {
    double lval = a, rval = b;
    double mid  = (lval + rval) / 2;
    int cnt = 0;

    while(fabs(mid - 0.29) > 0.00001) {
        cout << 'x' << cnt++ << ": " << mid << '\n';
        if(f(mid) > 0) rval = mid;
        else lval = mid;
        mid = (lval + rval) / 2;
    }
    cout << 'x' << cnt << ": " << mid << '\n';
    system("pause");

    return 0;
}