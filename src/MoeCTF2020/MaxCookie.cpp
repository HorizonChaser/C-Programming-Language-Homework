#include <bits/stdc++.h>

using namespace std;

int getMax(int a, int b) {
    int max = a;
    if (b > max) {
        return b;
    } else {
        return a;
    }
}

int getMaxSubStrLeng(string inStr) {
    //滑动窗口, 应该很直观
    int max = 0, currBegin = 0, currEnd = 0;
    int len = inStr.size();
    string currContent = "";
    while (currBegin < len && currEnd < len) {
        if (currContent.find(inStr[currEnd]) == currContent.npos) {
            currContent.insert(currContent.end(), inStr[currEnd]);
            currEnd++;
            max = getMax(max, currEnd - currBegin);  //更新最大值
        } else {
            //cout << currContent.find(inStr[currBegin]) << endl;
            currContent.erase(currContent.find(inStr[currBegin]), 1);
            currBegin++;
            //遇到重复则逐渐从左端删除currContent中的字符,
            //直到不再有字符和inStr[currEnd]重复
        }
    }
    //cout << currContent << endl;
    return max;
}

int main(void) {
    string inStr;
    getline(cin, inStr);
    cout << getMaxSubStrLeng(inStr) << endl;
}