#include <iostream>
#include <sstream>

using namespace std;

string rev(string src)
{
    string ret;
    for(int i = src.length()-1;i>-1;i--)
        ret+=src[i];
    return ret;
}

struct BigInt
{
    string reved;

    int operator%(const int& a)const
    {
        int d = 0;
        for(int i = 0;i<this->reved.length();i++)
            d=(d*10+(this->reved[i]-'0'))%a;
        return d;
    }
};

string toString(int n)
{
    stringstream ss;
    ss<<n;
    return ss.str();
}

string getNum(int a, int b)
{
    string ret;
    for(int i = a;i<=b;i++)
        ret+=toString(i);
    return ret;
}

int main()
{
    int round_;
    cin>>round_;
    for(int i = 0;i<round_;i++)
    {
        int a,b;    cin>>a>>b;
        BigInt current_stf;
        current_stf.reved = rev(getNum(a,b));
        cout<<(current_stf%9)<<endl;
    }
    return 0;
}