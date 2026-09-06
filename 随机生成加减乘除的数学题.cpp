#include <iostream>
#include<vector>
#include<algorithm>
#include<ctime>
#include<string>
using namespace std;


typedef int(*Func)(int, int);
#define random(N) rand()%N
const int Num = 100;
#define rand random(Num)
const string s = "加减乘除";


void inputHandle()
{
	auto add = [](int a, int b) {return a + b; };
	auto sub = [](int a, int b) {return a - b; };
	auto mul = [](int a, int b) {return a * b; };
	auto div = [](int a, int b) {return a / b; };

	vector<Func> calc{ add,sub,mul,div };

	string sizestr = "测";
	int a = rand, b = rand, flag = rand & 3, result;
	cout << a << s.substr(flag*sizestr.size(), sizestr.size()) << b << "输入结果:";
	cin >> result;
	cout << "输入" << ((*(calc.begin() + flag))(a, b) == result ? "正确" : "错误") << endl;
}
int main()
{
	srand((int)time(nullptr));

	while (1)
	{
		inputHandle();
		char c;
		cout << "是否继续y/n" << endl;
		cin >> c;
		if (c != 'y'&&c != 'Y')
			break;

	}
	cout << "退出程序" << endl;
	return 0;
}
