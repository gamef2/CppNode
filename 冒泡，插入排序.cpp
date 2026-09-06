#include <iostream>
#include <ctime>
#include <string>
//冒泡排序
int* Bubble_sort(int data[], int len)
{
	std::cout << "顺序从小到大:";
	for (int i = 0; i < len - 1; i++)//i初始化0，循环到长度减1
		for (int j = i + 1; j < len; ++j)//j初始化等于下一个位置，到长度相等结束
			if (data[i] > data[j])//如果当前比下一个位置大则进入对调//经过不断对调，i位置的值最小
			{
				int t = data[i];
				data[i] = data[j];
				data[j] = t;
			}
	return data;
}
//插入排序
int *Insert_Sort(int data[], int len)
{
	std::cout << "顺序从大到小:";
	for (int i = 1; i < len; ++i)
	{
		int temp = data[i];//初始化等于i当前位置
		int j = i - 1;//j等于前一个位置
		while (data[j]<temp&&j>=0)//当上一个小于当前位置的值,并且j>=0则进入循环
								  //直到找到当前最大值或者j<0
		{
			data[j + 1] = data[j];//当前等于上一个位置的值
			j--;
		}
		data[j + 1] = temp;//j--后跳出的j+1是等于这个小于temp的位置
		//如果进入while循环,则最前面小于temp的值替换成这个值
		//如果未进入,则i位置自己赋值
	}
	return data;
}

int main()
{
	void Display(int data[], int len);
	int data[] = { 11,44,2,35,68,94,14,20 };
	int len = sizeof(data) / sizeof(int);
	int data1[8];
	memcpy(data1, data, 4*8);
	clock_t start_, end_;//定义一个time对象
	start_ = clock();//初始时间
	Display(Bubble_sort(data, len), len);//调用冒泡排序
	end_ = clock();//结束时间
	std::cout << "调用冒泡排序用了" << (double)(end_ - start_) / CLOCKS_PER_SEC << "秒" << std::endl;
	memcpy(data, data1, 4 * 8);
	start_ = clock();//初始时间
	Display(Insert_Sort(data, len), len);//调用插入排序
	end_ = clock();//结束时间
	std::cout << "调用插入排序用了" << (double)(end_ - start_) / CLOCKS_PER_SEC << "秒" << std::endl;
	system("pause");
	return 0;
}
void Display(int data[], int len)
{
	for (int i = 0; i < len; i++)
	{
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
}