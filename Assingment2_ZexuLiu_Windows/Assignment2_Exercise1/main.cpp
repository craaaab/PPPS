#include <iostream>
#include <cmath>

using namespace std;

class Rational{
    friend void divide();
    friend void coeRead();
    friend void coePrint();
    friend ostream &operator<<(ostream & os, const Rational r);
private:
    int num, den;
    void ReductFraction(){
        if (!num) return;
        int numP = (num > 0) ? num : -1 * num;
        int denP = (den > 0) ? den : -1 * den;

        int tmp = (numP > denP) ? denP : numP;

        while(tmp > 1) {
            if(numP % tmp == 0 && denP % tmp == 0){
                num /= tmp;
                den /= tmp;
                break;
            }
            --tmp;
        }
    }

public:
    Rational():num(0), den(1){}
    ~Rational(){}

    void write(int nT, int dT) {
        num = nT;
        den = dT;
        ReductFraction();
    }

    Rational operator+(const Rational &r1) const {
        Rational tmp;

        tmp.num = num * r1.den + den * r1.num;
        tmp.den = den * r1.den;
        tmp.ReductFraction();

        return tmp;
    }

    Rational operator-(const Rational &r1) const {
        Rational tmp;

        tmp.num = num * r1.den - den * r1.num;
        tmp.den = den * r1.den;
        tmp.ReductFraction();

        return tmp;
    }

    Rational operator*(const Rational &r1) const {
        Rational tmp;

        tmp.num = num * r1.num;
        tmp.den = den * r1.den;
        tmp.ReductFraction();

        return tmp;
    }

    Rational operator/(const Rational &r1) const {
        Rational tmp;

        tmp.num = num * r1.den;
        tmp.den = den * r1.num;
        tmp.ReductFraction();

        return tmp;
    }



};
class IllegalInput{};

ostream &operator<<(ostream & os, const Rational r) {
    if(r.num == 0) os << 0;
    else if(r.num * r.den < 0){
        if(abs(r.den) == 1) os << '-' << abs(r.num);
        else os << '-' << abs(r.num) << '/' << abs(r.den);
    }
    else {
        if(abs(r.den) == 1) os << abs(r.num);
        else os << abs(r.num) << '/' << abs(r.den);
    }

    return os;
}
void coeRead();
void divide();
void coePrint();

Rational dividend[4], divisor[4];
Rational quotient[4], rem[3];
int degree;

int main() {
    try{
        coeRead();
    }
    catch(IllegalInput){
        cerr << "error" << endl;
        return -1;
    }

    divide();

    coePrint();

    return 0;
}

void coeRead() {
    int dividendI[4], divisorI[4];

    for (int i = 0; i < 4; ++i) cin >> dividendI[i];
    for (int i = 0; i < 4; ++i) cin >> divisorI[i];

    if(!dividendI[0] || cin.fail()) throw IllegalInput();

    bool flag = true;
    for(int i = 0; i < 4; ++i) {
        if(divisorI[i]) flag = false;
    }
    if(flag) throw IllegalInput();

    for (int i = 0; i < 4; ++i) {
        dividend[i].write(dividendI[i], 1);
    }

    for (int i = 0; i < 4; ++i) {
        divisor[i].write(divisorI[i], 1);
    }
}

void divide() {
    degree = 3;
    int k = 0;
    while(!divisor[k++].num) --degree;

    if(!degree) {
        for (int i = 0; i < 4; ++i)
            quotient[i] = dividend[i] / divisor[3];
        rem[0].write(0, 1);
        rem[1].write(0, 1);
        rem[2].write(0, 1);
    }
    else if(degree == 1) {
        quotient[0].write(0, 1);
        quotient[1] = dividend[0] / divisor[2];
        Rational remainder1 = dividend[1] - (dividend[0] * divisor[3] / divisor[2]);
        quotient[2] = remainder1 / divisor[2];
        Rational remainder2 = dividend[2] - (remainder1 * divisor[3] / divisor[2]);
        quotient[3] = remainder2 / divisor[2];
        rem[2] = dividend[3] - (remainder2 * divisor[3] / divisor[2]);
        rem[1].write(0, 1);
        rem[0] = rem[1];
    }
    else if(degree == 2) {
        Rational remainder1, remainder2;
        quotient[0].write(0, 1);
        quotient[1] = quotient[0];
        quotient[2] = dividend[0] / divisor[1];
        remainder1 = dividend[1] - (dividend[0] * divisor[2] / divisor[1]);
        remainder2 = dividend[2] - (dividend[0] * divisor[3] / divisor[1]);
        quotient[3] = remainder1 / divisor[1];
        rem[0].write(0, 1);
        rem[1] = remainder2 - (remainder1 * divisor[2] / divisor[1]);
        rem[2] = dividend[3] - (remainder1 * divisor[3] / divisor[1]);
    }
    else {
        quotient[0].write(0, 1);
        quotient[1] = quotient[2] = quotient[0];
        quotient[3] = dividend[0] / divisor[0];

        for (int i = 0; i < 3; ++i) {
            rem[i] = dividend[i + 1] - quotient[3] * divisor[i + 1];
        }
    }
}

void coePrint() {
    int k = 0;
    while(quotient[k].num == 0) ++k;
    for(int i = k; i < 4; ++i) {
        cout << quotient[i];
        if(i == 3) cout << '\n';
        else cout << ' ';
    }

    k = 0;
    while(rem[k].num == 0) ++k;
    for(int i = k; i < 3; ++i) {
        cout << rem[i];
        if(i < 3) cout << ' ';
    }
    cout << '\n';
}