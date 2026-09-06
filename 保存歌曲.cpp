#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;
void read_(fstream& f, string& name, vector<string>& v)
{
	v.clear();
	string s;
	f.open(name,ios::in);
	if (!f)
	{
		cerr << "错误" << endl;
	}
	while (!f.eof())
	{
		getline(f, s);
		if (f.eof())
			break;
		s.push_back('\n');
		v.push_back(s);
	}
	f.close();
}
void write_(fstream& f,string& name,vector<string>& v)
{
	if (remove(name.c_str()) == 0)
		cout << "写入成功" << endl;
	f.open(name,ios::out);
	for (vector<string>::iterator it = v.begin(); it != v.end(); ++it)
		f.write((char*)it->c_str(), it->size());
	f.close();
}
void ShowVec(vector<string>&v)
{
	system("cls");
	int i = 1;
	cout << "------------------" << endl;
	for_each(v.begin(), v.end(), [&](string& s)
	{cout <<i++<< s; });
}
int main()
{
	string s = "------------------\n1保存文件\n2读取文件\n3添加新的歌曲并保存、读取\n4删除歌曲并保存、读取\n------------------\n";
	vector<string> svec;
	char c;
	while (true)
	{
		string filename = "1.txt",data;
		fstream file; 
		ShowVec(svec);
		cout << s;
		cin >> c;
		size_t t;
		switch (c)
		{
		case '1':
			write_(file, filename, svec);
			break;
		case '2':
			read_(file, filename, svec);
			break;
		case '3':
			cout << "输入歌曲信息" << endl;

			cin.get();
			getline(cin, data);
			data.push_back('\n');
			svec.push_back(data);
			write_(file, filename, svec);
			read_(file, filename, svec);
			break;
		case '4':
			if (svec.size() > 0)
			{
				cout << "删除第几首歌（数字)" << endl;
				
				while (cin >> t && t > svec.size())
				{
					cout << "大于歌的数,重新输入" << endl;
				}
				if (t > 0)
				{
					svec.erase(svec.begin() + (t - 1));
					write_(file, filename, svec);
					read_(file, filename, svec);
				}
				else
				{
					cout << "非法输入" << endl;
				}
			}
			else
				cout << "没有歌曲" << endl;
			break;
		default:
			cout << "输入错误" << endl;
		}
	}
	system("pause");
	return 0;
}
