#include <iostream>
#include <string>
#include <cmath>
using namespace std;
int StrToNum(string &s)
{
	int ctr = s.size() - 1, sum = 0;
	for (auto i : s)
	{
		if (i == '1')
			sum += (int)pow(2, ctr);
		ctr--;
	}
	return sum;
}
int BinToNum(int num)
{
	if (num / 10 == 0)
		return 1;
	return BinToNum(num / 10) * 2 + num % 10;
}
string NumToStrBin(int num)
{
	string s;
	int l = 7;
	s.resize(8,0x0);
	while (num > 0)
	{
		s[l--] = num % 2 + '0';
		num /= 2;
	}
	while (l >= 0)
		s[l--] = '0';
	return s;
}
int main()
{
	string s = "10001";
	
	cout << StrToNum(s) << endl;
	cout << BinToNum(strtol(s.c_str(), NULL, 10)) << endl;
	int num = 17;
	s = NumToStrBin(num);
	cout << s<< endl;
}

