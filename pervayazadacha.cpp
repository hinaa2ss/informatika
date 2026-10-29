#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
int main() {
    float x, y, r, s, c;
    cin >> x >> y;
    r = sqrt(pow(x, 2) + pow(y, 2)) * sin(x);
    s = exp(x / y);
    cout << r << endl;
    cout << s << endl;
    c = max(r, s);
    cout << c << endl;
    return 0;
}