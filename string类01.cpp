#include <string>
#include <iostream>
using namespace std;
#define Num 52
char ch[Num];
void InitializingABC()
{
	int i,j;
	for (i=0,j=Num+13;i<Num;i++)
	{
		if (i>=1)
		{
			if (ch[i-1]==Num*2-14)
			{
				j=Num-20;//32
			}
			else if (ch[i-1]==Num-20)//32
			{
				j+=(Num+12);//32
			}
		}
		ch[i]=(char)j++;
	}
}
int main()
{
	InitializingABC();
	string s(ch);
	cout<<"s=\t"<<s<<endl;
	char *ch1=const_cast<char*>(s.c_str());
	cout<<"ch1=\t"<<ch1<<endl;
	
	string s1;
	cout<<"s.size()＝\t"<<s.size()<<endl;//大小
	cout<<"s1.length()=\t"<<s1.length()<<endl;//同上
	cout<<"s.empty()=\t"<<s.empty()<<endl;//!NULL==0返回0
	cout<<"s1.empty()=\t"<<s1.empty()<<endl;//NULL==0返回1

	cout<<"s.substr(2,3)=\t"<<s.substr(2,3)<<endl;//截取字符串
	string::size_type pos=s.find('x',5);
	if (pos==string::npos)
	{
		cout<<"没找到"<<endl;
	}
	else
		cout<<"pos=\t"<<pos<<endl;
	pos=s.rfind('a',51);
	
	if (pos==string::npos)
	{

		cout<<"没找到"<<endl;
	}
	else
		cout<<"pos=\t"<<pos<<endl;
	string::iterator first=s.begin()+6;
	string::iterator last=s.end()-5;
	basic_string<char> s2(first,last);
	cout<<"string::iterator first=s.begin()+6;\nstring::iterator last=s.end()-5;\nbasic_string<char> s2(first,last);"<<endl;
	cout<<"s2=\t"<<s2<<endl;
	s1=s.substr(3,9);
	cout<<"s1.replace(2,4,“123456”)=\t"<<s1.replace(2,4,"123456")<<endl;
	cout<<"s1.compare(s2)=\t"<<s1.compare(s2)<<endl;
	cout<<"s2.insert(3,“987”)="<<s2.insert(3,"987")<<endl;
	cout<<"s1.swap(s2)"<<endl;
	s1.swap(s2);
	cout<<"s1=\t"<<s1<<endl;
	cout<<"s2=\t"<<s2<<endl;
	
	return 0;
}
