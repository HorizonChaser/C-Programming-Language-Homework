#include <windows.h>  //计时用

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class BigInteger {
   private:
    bool sign = true;  //符号, 默认为正, 且规定0均为正
    vector<int> num;

    //移除前导零
    string removeLeadingZero(string in) {
        string res = "";
        int pos = 0;
        while (in[pos] == '0') {
            pos++;
        }
        res = in.substr(pos, in.length());
        return res;
    }

    BigInteger removeLeadingZero() {
        string in = this->toString();
        BigInteger ans = BigInteger(removeLeadingZero(in));
        ans.sign = this->sign;
        return ans;
    }

   public:
    BigInteger(const string &n) {
        string inNum = "";
        num.clear();

        if (n == "0") {
            num.push_back(0);
            sign = true;
            return;
        }
        if (n[0] == '-') {
            sign = false;
            inNum = n.substr(1, n.size());
        } else if (n[0] == '+') {
            sign = true;
            inNum = n.substr(1, n.size());
        } else
            inNum = n;
        inNum = removeLeadingZero(inNum);
        for (unsigned int i = 0; i < inNum.length(); i++) {
            num.push_back(inNum[i] - '0');  //注意存入的应该是int
        }
    }

    string toString() {
        string res = "";
        if (sign == false) {
            res += "-";
        }
        for (unsigned int i = 0; i < num.size(); i++) {
            res += (num[i] + '0');
        }
        return res;
    }

    //检查一个字符串是否是一个合法的整数
    static bool isVaild(string in) {
        int pos = 0;
        if (in[0] == '+' || in[0] == '-')
            pos++;
        if (pos == 1 && in.length() == 1)
            return false;

        for (unsigned int i = pos; i < in.length(); i++) {
            if (isdigit(in[i]) == false)
                return false;
            return true;
        }
        return false;
    }

    bool isZero() {
        int sum = 0;
        for (unsigned int i = 0; i < num.size(); i++) {
            sum += num[i];
        }
        if (sum == 0)
            return true;
        else
            return false;
    }

    BigInteger abs() {
        BigInteger res = BigInteger(this->toString());
        return res;
    }

    //比较, a<b == -1 a==b == 0 a>b == 1
    int compareTo(BigInteger &in) {
        //以下根据符号直接判定
        if (this->sign == false && in.sign == true)
            return -1;
        if (this->sign == true && in.sign == false)
            return 1;
        if (this->sign == false) {
            BigInteger inNumAbs = in.abs();
            if (this->abs().compareTo(inNumAbs) == 1)
                return -1;
            if (this->abs().compareTo(inNumAbs) == 0)
                return 0;
            if (this->abs().compareTo(inNumAbs) == -1)
                return 1;
        } else {
            if (this->num.size() < in.num.size())
                return -1;
            if (this->num.size() > in.num.size())
                return 1;

            //按位比较
            for (unsigned int i = 0; i < this->num.size(); i++) {
                if (this->num[i] < in.num[i])
                    return -1;
                if (this->num[i] > in.num[i])
                    return 1;
            }
            return 0;
        }
        return -2;
    }

    //a+b
    static BigInteger add(BigInteger &ina, BigInteger &inb) {
        BigInteger a = BigInteger(ina.toString());
        BigInteger b = BigInteger(inb.toString());
        string zero = "";
        BigInteger ans = BigInteger(zero);
        int sum = 0, x = 0;  //某位之和, 进位标识

        if (a.isZero()) {
            ans = b;
            return ans;
        }
        if (b.isZero()) {
            ans = a;
            return ans;
        }

        // 下面假设a>0 b>0来说明
        if (a.sign == false && b.sign == true) {  // -a+b -> b-a
            a.sign = true;
            ans = minus(b, a);
            return ans;
        }

        if (a.sign == true && b.sign == false) {  // a+(-b) -> a-b
            b.sign = true;
            ans = minus(a, b);
            return ans;
        }

        //将a, b翻转来从尾端开始相加
        reverse(a.num.begin(), a.num.end());
        reverse(b.num.begin(), b.num.end());

        //保证左长右短(就是竖式里的上长下短)
        if (a.num.size() < b.num.size()) {
            swap(a, b);
        }
        while (b.num.size() < a.num.size()) {
            b.num.push_back(0);
        }

        for (unsigned int pos = 0; pos < a.num.size(); pos++) {
            sum = a.num[pos] + b.num[pos] + x;
            ans.num.push_back(sum % 10);
            x = sum / 10;  //计算是否进位
            sum = 0;
        }
        if (x != 0)
            ans.num.push_back(x);
        ans.sign = a.sign;
        reverse(ans.num.begin(), ans.num.end());
        ans = ans.removeLeadingZero();
        if (ans.num.size() == 0)  //如果为空补个零
            ans.num.push_back(0);
        return ans;
    }

    //a-b
    static BigInteger minus(BigInteger a, BigInteger b) {
        string zero = "";
        BigInteger ans = BigInteger(zero);
        int x = 0;

        //减数为零, 返回原值
        if (b.isZero()) {
            ans = a;
            return a;
        }
        if (a.compareTo(b) == 0) {
            ans.num.push_back(0);
            return ans;
        }
        //下面假设a>0 b>0来说明
        if (a.sign == true && b.sign == false) {  // a - (-b) -> a + b
            b.sign = true;
            ans = add(a, b);
            return ans;
        }
        if (a.sign == false && b.sign == true) {  // (-a) - b -> -(a + b)
            a.sign = true;
            ans = add(a, b);
            ans.sign = false;
            return ans;
        }
        if (a.sign == false && b.sign == false) {  // (-a) - (-b) -> b - a
            b.sign = true;
            ans = add(a, b);
            return ans;
        }

        BigInteger aAbs = BigInteger(a.abs());
        if (b.abs().compareTo(aAbs) == 1) {
            swap(a, b);
            ans.sign = false;
        }

        reverse(a.num.begin(), a.num.end());
        reverse(b.num.begin(), b.num.end());

        while (b.num.size() < a.num.size()) {
            b.num.push_back(0);
        }

        for (unsigned int pos = 0; pos < b.num.size(); pos++) {
            if (a.num[pos] < b.num[pos] || a.num[pos] < 0) {  //需要借位
                int temp = a.num[pos + 1] - 1;
                a.num[pos + 1] = temp;
                x = 10;
            }
            ans.num.push_back(a.num[pos] - b.num[pos] + x);
            x = 0;
        }

        reverse(ans.num.begin(), ans.num.end());
        ans = ans.removeLeadingZero();
        if (ans.num.size() == 0)  //为空补零
            ans.num.push_back(0);
        return ans;
    }

    //对两个vector的乘法进行计算
    //本来计划还有除法, 但是时间不够了 :(
    static vector<int> multi(vector<int> x, vector<int> y) {
        unsigned long long r;
        size_t lenx = x.size(), leny = y.size();
        vector<int> result(lenx + leny, 0);  //预分配空间
        for (size_t i = 0; i < leny; ++i) {
            r = 0;
            size_t j, k;  // k为移位的个数
            for (j = 0, k = i; j < lenx; ++j, ++k) {
                r += (y[i]) * x[j] + result[k];
                result[k] = unsigned(r);
                r >>= 32;
            }
            result[k] = unsigned(r);
        }
        return move(result);  //移交所有权
    }

    static BigInteger multiply(BigInteger &a, BigInteger &b) {
        BigInteger left = BigInteger(a.toString()),
                   right = BigInteger(b.toString()),
                   ans = BigInteger(string(""));

        if (left.sign != right.sign)
            ans.sign = false;
        if (left.isZero() || right.isZero()) {
            ans.num.push_back(0);
            ans.sign = true;
            return ans;
        }

        ans.num = multi(left.num, right.num);
        ans.num.pop_back();
        return ans;
    }
};

int main(int argc, char *argv[]) {
    string a, b, sign;
    cout << "-----------------------------------------" << endl;
    cout << "Simple Calc by HorizonChaser based on C++" << endl;
    cout << "Supported Operators: plus + " << endl;
    cout << "                     minus - " << endl;
    cout << "                     multiply * or x " << endl;
    cout << "To Exit, Input . for 3 Times " << endl;
    cout << "Have fun ~" << endl;
    cout << "-----------------------------------------" << endl;

    while (true) {
        cin >> a >> sign >> b;
        if (a == "." && b == "." && sign == ".") {
            cout << "Thanks for Using. " << endl << "Powered by Teacher Yao, Determination, VS Code and C++" << endl;
            cout << "Exiting Now... " << endl;
            return 0;
        }
        if (BigInteger::isVaild(a) == false) {
            cout << "Invalid First Value: " << a << endl;
            system("pause");
            continue;
        }
        if (BigInteger::isVaild(b) == false) {
            cout << "Invalid Second Value: " << b << endl;
            system("pause");
            continue;
        }
        if (sign != "+" && sign != "-" && sign != "*" && sign != "x") {
            cout << "Invalid Sign Given: " << sign << endl;
            system("pause");
            continue;
        }

        BigInteger left = BigInteger(a), right = BigInteger(b);

        LARGE_INTEGER large_interger;
        double dff;
        __int64 c1, c2;
        QueryPerformanceFrequency(&large_interger);
        dff = large_interger.QuadPart;
        QueryPerformanceCounter(&large_interger);
        c1 = large_interger.QuadPart;

        if (sign == "+") {
            cout << BigInteger::add(left, right).toString() << endl;
        } else if (sign == "-") {
            cout << BigInteger::minus(left, right).toString() << endl;
        } else if (sign == "*" || sign == "x") {
            cout << BigInteger::multiply(left, right).toString() << endl;
        }

        QueryPerformanceCounter(&large_interger);
        c2 = large_interger.QuadPart;
        cout << "Time Consumed in ms: " << (c2 - c1) * 1000 / dff << endl;
        system("pause");
    }
    return 0;
}