#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class BigInteger {
private:

    bool sign = true;//符号, 默认为正, 且规定0均为正
    vector<int> num;

     //移除前导零
    string removeLeadingZero(string in){
        string res = "";
        int pos = 0;
        while(in[pos] == '0'){
            pos++;
        }
        res = in.substr(pos, in.length());
        return res;
    }

    BigInteger removeLeadingZero(){
        string in = this->toString();
        BigInteger ans = BigInteger(removeLeadingZero(in));
        ans.sign = this->sign;
        return ans;
    }

public:

    BigInteger(const string &n) {
        string inNum = "";
        num.clear();

        if(n == "0"){
            num.push_back(0);
            sign = true;
            return;
        }
        if(n[0] == '-'){
            sign = false;
            inNum = n.substr(1, n.size());
        }
        else if(n[0] == '+'){
            sign = true;
            inNum = n.substr(1, n.size());
        }
        else
            inNum = n;
        inNum = removeLeadingZero(inNum);
        for (int i = 0; i < inNum.length();i++){
            num.push_back(inNum[i] - '0');//注意存入的应该是int
        }
    }

    string toString() {
        string res = "";
        if(sign == false){
            res += "-";
        }
        for (int i = 0; i < num.size();i++){
            res += (num[i] + '0');
        }
        return res;
    }

    //检查一个字符串是否是一个合法的整数
    static bool isVaild(string in){
        int pos = 0;
        if(in[0] == '+' || in[0] == '-')
            pos++;
        if(pos == 1 && in.length() == 1)
            return false;

        for (int i = pos; i < in.length();i++){
            if(isdigit(in[i]) == false)
                return false;
            return true;
        }
        return false;
    }

    bool isZero() {
        int sum = 0;
        for (int i = 0; i < num.size();i++){
            sum += num[i];
        }
        if(sum == 0)
            return true;
        else
            return false;
    }

    BigInteger abs(){
        BigInteger res = BigInteger(this->toString());
        return res;
    }

    //比较, a<b == -1 a==b == 0 a>b == 1
    int compareTo(BigInteger &in){
        //以下根据符号直接判定
        if(this->sign == false && in.sign == true)
            return -1;
        if(this->sign == true && in.sign == false)
            return 1;
        if(this->sign == false){
            BigInteger inNumAbs = in.abs();
            if(this->abs().compareTo(inNumAbs) == 1)
                return -1;
            if(this->abs().compareTo(inNumAbs) == 0)
                return 0;
            if(this->abs().compareTo(inNumAbs) == -1)
                return 1;
        } else {
            if(this->num.size() < in.num.size())
                return -1;
            if(this->num.size() > in.num.size())
                return 1;

            //按位比较
            for (int i = 0; i < this->num.size();i++){
                if(this->num[i] < in.num[i])
                    return -1;
                if(this->num[i] > in.num[i])
                    return 1;
            }
            return 0;
        }
        return -2;
    }

    static BigInteger add(BigInteger a, BigInteger b){
        string zero = "";
        BigInteger ans = BigInteger(zero);
        int sum = 0, x = 0;//某位之和, 进位标识

        if(a.isZero()){
            ans = a;
        }
        if(b.isZero()){
            ans = b;
        }

        // 下面假设a>0 b>0来说明
        if(a.sign == false && b.sign == true){// -a+b -> b-a
            a.sign = true;
            ans = minus(b, a);
            return ans;
        }

        if(a.sign == true && b.sign == false){// a+(-b) -> a-b
            b.sign = true;
            ans = minus(a, b);
            return ans;
        }

        //将a, b翻转来从尾端开始相加
        reverse(a.num.begin(), a.num.end());
        reverse(b.num.begin(), b.num.end());

        //保证左长右短(就是竖式里的上长下短)
        if(a.num.size() < b.num.size()){
            swap(a, b);
        }
        while(b.num.size() < a.num.size()){
            b.num.push_back(0);
        }

        for (int pos = 0; pos < a.num.size();pos++){
            sum = a.num[pos] + b.num[pos] + x;
            ans.num.push_back(sum % 10);
            x = sum / 10;//计算是否进位
            sum = 0;
        }
        if(x!=0)
            ans.num.push_back(x);
        ans.sign = a.sign;
        reverse(ans.num.begin(), ans.num.end());
        ans = ans.removeLeadingZero();
        if(ans.num.size() == 0)//如果为空补个零
            ans.num.push_back(0);
        return ans;
    }

    static BigInteger minus(BigInteger a, BigInteger b){
        string zero = "";
        BigInteger ans = BigInteger(zero);
        int x = 0;

        //减数为零, 返回原值
        if(b.isZero()){
            ans = a;
            return a;
        }
        if(a.compareTo(b) == 0){
            ans.num.push_back(0);
            return ans;
        }
        //下面假设a>0 b>0来说明
        if(a.sign == true && b.sign == false){// a - (-b) -> a + b
            b.sign = true;
            ans = add(a, b);
            return ans;
        }
        if(a.sign == false && b.sign == true){// (-a) - b -> -(a + b)
            a.sign == true;
            ans = add(a, b);
            ans.sign = false;
            return ans;
        }
        if(a.sign == false && b.sign == false){// (-a) - (-b) -> b - a
            b.sign = true;
            ans = add(a, b);
            return ans;
        }

        BigInteger aAbs = BigInteger(a.abs());
        if(b.abs().compareTo(aAbs) == 1){
            swap(a, b);
            ans.sign = false;
        }

        reverse(a.num.begin(), a.num.end());
        reverse(b.num.begin(), b.num.end());

        while(b.num.size() < a.num.size()){
            b.num.push_back(0);
        }

        for (int pos = 0; pos < b.num.size();pos++){
            if(a.num[pos] < b.num[pos] || a.num[pos] < 0){//需要借位
                int temp = a.num[pos + 1] - 1;
                a.num[pos + 1] = temp;
                x = 10;
            }
            ans.num.push_back(a.num[pos] - b.num[pos] + x);
            x = 0;
        }

        reverse(ans.num.begin(), ans.num.end());
        ans = ans.removeLeadingZero();
        if(ans.num.size() == 0)//为空补零
            ans.num.push_back(0);
        return ans;
    }

};

int main(int argc, char* argv[]){
    string a, b, sign;
    cin >> a >> sign >> b;

    if(BigInteger::isVaild(a) == false){
        cout << "Invalid First Value: " << a << endl;
        return 0;
    }
    if(BigInteger::isVaild(b) == false){
        cout << "Invalid Second Value: " << b << endl;
        return 0;
    }
    if(sign != "+" && sign != "-"){
        cout << "Invalid Sign Given: " << sign << endl;
        return 0;
    }

    BigInteger left = BigInteger(a), right = BigInteger(b);

    if(sign == "+"){
        cout << BigInteger::add(a, b).toString() << endl;
    }else{
        cout << BigInteger::minus(a, b).toString() << endl;
    }
    return 0;
}