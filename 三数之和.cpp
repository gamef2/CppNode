//三数之和等于0
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//普通三层循环,算法的时间复杂度是O(n^3)
template<typename T, int n>
vector<vector<int> > threeSum(T(&arr)[n]) {
	// write your code here
	vector<vector<int> > ans;
	std::sort(begin(arr), end(arr));

	vector<int> temp;

	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			for (int k = j + 1; k < n; ++k) {
				if (arr[i] + arr[j] + arr[k] == 0) {
					temp.clear();
					temp.push_back(arr[i]);
					temp.push_back(arr[j]);
					temp.push_back(arr[k]);
					sort(temp.begin(), temp.end());
					if (ans.end() != find(ans.begin(), ans.end(), temp)) {//查找是否重复
						continue;
					}
					else
						ans.push_back(temp);

				}
			}
		}
	}
	return ans;
}

//双指针算法,算法的时间复杂度是O(n^2)
template<typename T,int n>
vector<vector<T>> Three_Num_Sum(T(&arr)[n]) {

	//排序的作用在于去掉重复的数字
	std::sort(begin(arr), end(arr));

	vector<vector<T>> v2;

	//异常处理
	if (n <= 2)
	{
		return v2;
	}
	for (int i = 0; i < n; i++)
	{
		//大于0就不用往下走
		if (arr[i] > 0)
		{
			break;
		}
		//跳过重复的
		if (i > 0 && arr[i - 1] == arr[i])
		{
			continue;
		}
		int start = i + 1;
		int end = n - 1;
		while (start < end)
		{
			if (arr[i] + arr[start] + arr[end] == 0)
			{
				v2.push_back({ arr[i],arr[start],arr[end] });
				//寻找接下来满足条件的
				//首先跳过重复的
				while (start < end &&arr[start] == arr[start + 1])
					start++;
				while (start < end &&arr[end] == arr[end - 1])
					end--;
				start++;
				end--;
			}
			//因为右边值大,所以大于0时,end--
			else if (arr[i] + arr[start] + arr[end] > 0)
			{
				end--;
			}
			else
				start++;
		}
	}
	return v2;
}

int main()
{
	int arr[] = { -1, 0, 1, 2, -1, -4 };
#define Methor 2	//通过修改该数查看两种遍历
#if Methor == 1
	for (auto i : threeSum(arr))
#elif Methor == 2
	for (auto i : Three_Num_Sum(arr))
#endif //Methor
	{
		cout << "[";
		for (auto j : i)
			cout << j << ",";
		cout << "]\n";
	}
}