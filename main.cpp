#include<iostream>
#include<string>
#include<vector>
using namespace std;

string multiplyInt (string num1,string num2)
{
    if(num1 == "0" || num2 == "0") return "0";

    int m = num1.size(),n = num2.size();
    vector<int>pos(m + n,0);
    //按位数进行竖式乘法
    for(int i = m - 1;i >= 0;i--)
    {
        for(int j = n - 1;j >= 0;j--)
        {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int sum = mul + pos[i + j + 1];

            pos[i + j] += sum / 10;
            pos[i + j + 1] = sum % 10;
        }
    }
    
    string result = "";
    for(int p : pos)
    {
        if(!(result.empty() && p == 0))
        {
            result += to_string(p);
        }
    }
    return result.empty() ? "0" : result;
}

string multiply(string num1,string num2)
{
    //计算小数点总位数，最后累加化归到整数的情况
    int decimalPlaces = 0;

    int dotPos1 = num1.find('.');
    if(dotPos1 != string::npos)
    {
        decimalPlaces += num1.size() - dotPos1 - 1;
        num1.erase(dotPos1,1);
    }

    int dotPos2 = num2.find('.');
    if(dotPos2 != string::npos)
    {
        decimalPlaces += num2.size() - dotPos2 - 1;
        num2.erase(dotPos2,1);
    }

    string intResult = multiplyInt(num1,num2);

    if (decimalPlaces == 0) return intResult;

    //在整数中加入小数点
    //如果整数结果位数不够，前面补零
    while ((int)intResult.size() <= decimalPlaces)
    {
        intResult = "0" + intResult;
    }

    int insertPos = intResult.size() - decimalPlaces;
    string result = intResult.substr(0,insertPos) + "." + intResult.substr(insertPos);

    //去掉末尾多余的零
    while(result.back() == '0')result.pop_back();
    if (result.back() == '.') result.pop_back();

    return result;
}

int main()
{
    string a;
    int n;
    while (cin>>a>>n)
    {
        string answer = "1";
        for(int i = 0;i < n;i++)
        {
            answer = multiply(answer,a);
        }
        cout<<answer<<endl;
    }
}