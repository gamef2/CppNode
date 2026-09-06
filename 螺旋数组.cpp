#include <iostream>
#include <iomanip>
using namespace std;

template<typename T, unsigned l>
void print(const T(&arr)[l][l],unsigned n)
{
	//cout << "----"<<typeid(T).name()<<"----" << endl;
	int width = n / 2 + 1;
	for (unsigned i = 0; i < n; ++i)
	{
		for (unsigned j = 0; j < n; ++j)
			cout << setw(width) << arr[i][j];
		cout << endl;
	}
	cout << "--------" << endl;
}

template<typename T,unsigned l >
void processArr(T(&arr)[l][l], unsigned n, T v)
{
	if (n > l)
	{
		cout << "数组范围错误" << endl;
		return;
	}
	unsigned i, j, t;
	for (i=0;i<=n/2;++i)
	{
		t = n - i - 1;
		/* 方向→:1,2,3,4,5 */
		for (j = i; j <= t; ++j)
			arr[i][j] = v++;
		/* 方向↓:6,7,8 */
		for (j = i+1; j < t; ++j)
			arr[j][t] = v++;
		/* 方向←:9,10,11,12 */
		for (j = t; j >i; --j)
			arr[t][j] = v++;
		/* 方向↑:13,14,15,16 */
		for (j = t; j > i; --j)
			arr[j][i] = v++;
	}
	print(arr,n);
}
int main()
{
	int intArr[10][10] = { 0 };
	//输入:数组，处理长度，初始值
	processArr(intArr, 5, 1);

	char charArr[10][10] = { 0 };
	processArr(charArr,5,'A');

	cin.get();
	return 0;
}