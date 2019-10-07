#include <iostream>
#include <cmath>

using namespace std;

class NewtonInterpolation {
private:
    double x[7];
    double f[7][7];

public:
    NewtonInterpolation() {
        x[0] = 0.1;
        x[1] = 0.4;
        x[2] = 1;
        x[3] = 1.8;
        x[4] = 2.9;
        x[5] = 3.2;
        x[6] = 3.8;

        f[0][0] = 4.2;
        f[1][0] = 3.8;
        f[2][0] = 2.5;
        f[3][0] = 2;
        f[4][0] = -2;
        f[5][0] = 0;
        f[6][0] = -0.3;
    }

    void DividedDifferenceTable() {
        for(int i = 1; i < 7; ++i) {
            for(int j = 0; j < i; ++j) {
                f[j][i] = 0;
            }
            for(int j = i; j < 7; ++j) {
                f[j][i] = (f[j][i - 1] - f[j - 1][i - 1]) / (x[j] - x[j - i]);
            }
        }

        for(int i = 0; i < 7; ++i){
            for(int j = 0 ; j <=i ; ++j)
                cout << f[i][j] << ' ';
            cout << '\n';
        }
    }

    double ApproximateValue(double xnew) {
        double ans = f[0][0];
        double xmxn = 1;
        for(int i = 1; i < 7; ++i) {
            xmxn *= xnew - x[i - 1];
            ans += f[i][i] * xmxn;
        }

        return ans;
    }
};

int main() {
    NewtonInterpolation N;
    N.DividedDifferenceTable();

    double xnew;
    cin >> xnew;
    if(cin.fail()) exit(-1);

    cout << N.ApproximateValue(xnew);

    return 0;
}