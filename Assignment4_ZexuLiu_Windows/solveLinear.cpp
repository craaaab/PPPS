#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

class Matrix {
    friend void getAugMat(int n, Matrix &A, Matrix &b);
    friend bool isUnique(Matrix &A, Matrix &b);
    friend void swap(int r1, int r2, Matrix &A, Matrix &b);
    friend void Jacobi(Matrix &A, Matrix &b);
    friend void Gauss(Matrix &A, Matrix &b);
private:
    double **mat;
    int row;
    int col;

public:
    Matrix() : row(1), col(1) {
        mat = new double*[1];
        mat[0] = new double[1];
        mat[0][0] = 1;
    }

    Matrix(int r, int c) : row(r), col(c) {
        mat = new double*[row];
        for(int i = 0; i < row; ++i) {
            mat[i] = new double[col];
            for(int j = 0; j < col; ++j) {
                mat[i][j] = 0;
            }
        }
    }

    Matrix(const Matrix &m) : row(m.row), col(m.col) {
        mat = new double*[m.row];
        for(int i = 0; i < m.row; ++i) {
            mat[i] = new double[m.col];
            for(int j = 0; j < m.col; ++j) {
                mat[i][j] = m.mat[i][j];
            }
        }
    }

    ~Matrix() {
        for(int i = 0; i < row; ++i) delete mat[i];
        delete mat;
    }

    Matrix operator+(const Matrix &m){
        Matrix tmp(row, col);

        for(int i = 0; i < row; ++i) {
            for(int j = 0; j < col; ++j) {
                tmp.mat[i][j] = mat[i][j] + m.mat[i][j];
            }
        }
        return tmp;
    }

    Matrix operator-(const Matrix &m){
        Matrix tmp(row, col);

        for(int i = 0; i < row; ++i) {
            for(int j = 0; j < col; ++j) {
                tmp.mat[i][j] = mat[i][j] - m.mat[i][j];
            }
        }

        return tmp;
    }

    Matrix operator*(const Matrix &m){
        Matrix tmp(row, m.col);

        for(int i = 0; i < row; ++i) {
            for(int j = 0; j < m.col; ++j) {
                for(int k = 0; k < col; ++k) {
                    tmp.mat[i][j] += mat[i][k] * m.mat[k][j];
                }
            }
        }

        return tmp;
    }

    void printMat() {
        for(int i = 0; i < row; ++i) {
            for(int j = 0; j < col; ++j) {
                cout << mat[i][j] << ' ';
            }
            cout << '\n';
        }
    }

    Matrix &operator=(const Matrix &m) {
        row = m.row;
        col = m.col;
        mat = new double*[m.row];
        for(int i = 0; i < m.row; ++i) {
            mat[i] = new double[m.col];
            for(int j = 0; j < m.col; ++j) {
                mat[i][j] = m.mat[i][j];
            }
        }

        return *this;
    }
};

void getAugMat(int n, Matrix &A, Matrix &b);
void swap(int r1, int r2, Matrix &A, Matrix &b);
bool isUnique(Matrix &A, Matrix &b);
void Jacobi(Matrix &A, Matrix &b);
void Gauss(Matrix &A, Matrix &b);

int main() {
    int n;

    cout << "Input the number of equations and unknowns n: ";
    cin >> n;
    if(cin.fail()) {
        cerr << "Invalid input!";
        exit(-1);
    }

    Matrix A(n, n), b(n, 1);
    cout << "Input the augmented matrix of Ax=b as [A b]:\n";
    getAugMat(n, A, b);

    Matrix upperTriangularMat(A),upperAug(b);

    if(!isUnique(upperTriangularMat, upperAug)) {
        cerr << "No unique solution exists!";
        exit(-1);
    }


    int flag;
    cout << "[0] Jacobi Iteration [1] Gaussian Elimination\n"
         << "Choose a method: ";
    cin >> flag;
    if(cin.fail()) {
        cerr << "Invalid input!";
        exit(-1);
    }

    if(flag) Gauss(upperTriangularMat, upperAug);
    else Jacobi(A, b);

    return 0;
}

void getAugMat(int n, Matrix &A, Matrix &b) {
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cin >> A.mat[i][j];
        }
        cin >> b.mat[i][0];
    }
    if(cin.fail()) {
        cerr << "Invalid input!";
        exit(-1);
    }
}

void swap(int r1, int r2, Matrix &A, Matrix &b){
    double tmp[A.col];
    for(int i = 0; i < A.col; ++i) {
        tmp[i] = A.mat[r1][i];
        A.mat[r1][i] = A.mat[r2][i];
        A.mat[r2][i] = tmp[i];
    }
    double tmpb;
    tmpb = b.mat[r1][0];
    b.mat[r1][0] = b.mat[r2][0];
    b.mat[r2][0] = tmpb;
}

bool isUnique(Matrix &A, Matrix &b) {
    for(int i = 0; i < A.row - 1; ++i) {
        for(int j = i; j < A.row; ++j) {
            if(A.mat[j][i] != 0) {
                if(j != i)
                    swap(i, j, A, b);
                break;
            }
            if(j == A.row - 1 && A.mat[j][i] == 0)
                return false;
        }

        for(int j = i + 1; j < A.row; ++j) {
            double m = A.mat[j][i] / A.mat[i][i];
            for(int k = i; k < A.col; ++k) {
                A.mat[j][k] = A.mat[j][k] - m * A.mat[i][k];
            }
            b.mat[j][0] = b.mat[j][0] - m * b.mat[i][0];
        }
    }

    if(fabs(A.mat[A.row - 1][A.col - 1]) < 0.00001) return false;

    return true;
}

void Gauss(Matrix &A, Matrix &b) {
    int n = A.row;
    double x[n];
    x[n - 1] = b.mat[n - 1][0] / A.mat[n - 1][n - 1];
    for(int i = n - 2; i >= 0; --i) {
        x[i] = b.mat[i][0];
        for(int j = i + 1; j < n; ++j) {
            x[i] -= A.mat[i][j] * x[j];
        }
        x[i] /= A.mat[i][i];
    }

    cout << "Result is:\n";
    for(int i = 0; i < n; ++i) cout << x[i] <<' ';
}

void Jacobi(Matrix &A, Matrix &b) {
    int n = A.row;
    cout << "Input the initial approximation x(0):\n";
    Matrix x(n, 1);
    for(int i = 0; i < n; ++i) cin >> x.mat[i][0];

    Matrix D(n, n), I(n, n);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if(j == i) {
                D.mat[i][j] = 1 / A.mat[i][j];
                I.mat[i][j] = 1;
            }
            else {
                D.mat[i][j] = 0;
                I.mat[i][j] = 0;
            }
        }
    }

    Matrix B1(I - (D * A));
    Matrix f1(D * b);

    int cnt = 0;
    while(++cnt <= 10) {
        Matrix xt(n, 1);
        xt = B1 * x + f1;

        bool flag = true;
        for(int i = 0; i < n; ++i) {
            if(fabs(x.mat[i][0] - xt.mat[i][0]) > 0.001){
                flag = false;
                break;
            }
        }

        if(flag) {
            cout << "Result is:\n";
            for(int i = 0; i < n; ++i)
                cout << fixed << x.mat[i][0] << ' ';
            return;
        }
        x = xt;
    }

    cerr << "Maximum number of iterations exceeded!";
    exit(-1);
}


