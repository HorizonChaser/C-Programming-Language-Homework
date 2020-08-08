#include <bits/stdc++.h>
using namespace std;

int main(void) {
    int indate, rolls = 0;
    char ch;
    cin >> rolls;
    //cin >> ch;

    for (int i = 0; i < rolls; i++) {
        string indata;
        stringstream stream;

        do {
            getline(cin, indata);
        } while (indata.length() == 0);

        cout << "!!!" << indata.length() << endl;
        for (int i = 0; i < indata.length(); i++) {
            if (indata[i] < '0' || indata[i] > '9') {
                cout << "error3" << endl;
                continue;
            }
        }
        stream << indata;
        stream >> indate;
        if (indata.length() < 6) {
            cout << "error1" << endl;
            continue;
        } else if (indate > 999999) {
            cout << "error2" << endl;
            continue;
        }

        int year = indate / 100;
        int month = indate - 100 * year;

        if (year < 1990) {
            cout << "error4" << endl;
            continue;
        } else if (year > 2049) {
            cout << "error5" << endl;
            continue;
        }
        if (month < 1) {
            cout << "error6" << endl;
            continue;
        } else if (month > 12) {
            cout << "error7" << endl;
            continue;
        }
        cout << "(" << year << "," << month << ")" << endl;
    }

    return 0;
}