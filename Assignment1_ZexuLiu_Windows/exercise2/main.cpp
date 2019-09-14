#include "solve.h"

int main() {
    try{
        solve();
    }
    catch(InvalidDelta) {
        cerr << "b^2-4ac is less than zero!" << endl;
    }
    catch(IllegalInput) {
        cerr << "Illegal inputs!" << endl;
    }
    //system("pause");
    return 0;
}