#include<iostream>
using namespace std;
#include<string.h>
int main()
{
	double s(double key, double num, double low, double higt);
	double key, num, result;	// low,high;
	char c;
	do
	{
		cout<<"==========二分法求一个数的n次方根============\n";
		cout << "输入一个数:";
		cin >> key;
		cout << "求这个数的几次方: ";
		cin >> num;
		result = s(key, num, 0, key);
		cout << key << "的" << num << "次方根=" << result << endl;
		cout << "是否继续(Y/N)?" ;
		cin >> c;
		if (c != 'y' && c != 'Y')
			break;
		cout<<endl;
	}
	while (true);
	return 0;
}
double s(double key, double num, double low, double higt)
{
	double mid = (low + higt) / 2, square, sq = mid;
	for (int i = 0; i < num - 1; i++)
		sq *= mid;
	square = sq;
	if (key == square || (key - square) > 0 && (key - square) < 0.0001 || (key - square) < 0
		&& (key - square) > -0.0001)
		return mid;
	
	else
	{
		if (key > square)
			low = mid;
		else
			higt = mid;
	}
	return s(key, num, low, higt);
}
