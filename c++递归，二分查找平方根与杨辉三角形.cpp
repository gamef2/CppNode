#include <iostream>
#include<iomanip>
void d(int);
double s(double, double, double);
using namespace std;
int main()
{
	char c;
	do
	{
		double num, result;
		cout << "递归，二分查找平方根\n请输入" << endl;
		cin >> num;
		result = s(0, num, num);
		cout << "输出结果" << setprecision(2) << result << endl;
		int key;
		cout << "杨辉三角\n请输入行数" << endl;
		cin>>key;
		d(key);
		cout<<"是否重新来Y/N"<<endl;
		cin>>c;
		if(c!='y'&&c!='Y')
			break;
	}
	while(true);
	return 0;
}
void d(int len)
{
	int i,j;
	int **a=new int*[len];
	for (i=0;i<len;i++)
		a[i]=new int[len];
	for (i = 0; i < len; i++)
	{
		for (j = 0; j <= i; j++)
		{
			a[i][0] = 1;
			if (j > 0 && j < i)
				a[i][j] = a[i - 1][j - 1] + a[i - 1][j];
			else if (i == j)
				a[i][j] = 1;
		}
	}
	for (i = 0; i < len; i++)
	{
		for (j = 0; j <= i; j++)
		{
			cout << setw(4) << a[i][j];
			if (i == j)
				cout << endl;
		}
	}
	for (i=0;i<len;i++)
		delete[len] a[i];
	delete[len] a;
}
double s(double l, double h, double key)
{
	double m, n;
	m = (l + h) / 2;
	n = m * m;
	cout<<"l="<<l<<"  h="<<h<<"  m="<<m<<"  n="<<n<<endl;
	if (key == n || (key - n) > 0 && (key - n) < 0.0001 || (key - n) < 0 && (key - n) > -0.0001)
		return m;
	else
	{
		if (key > n)
		{
			cout << "key=" << key << "比" << "n=" << n << "大"<<endl;
			l = m + 1;
		}
		else
		{
			cout << "key=" << key << "比" << "n=" << n << "小"<<endl;
			h = m - 1;
		}
	}
	return s(l, h, key);
}
