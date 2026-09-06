#include <iostream>
#include<fstream>
#include<string.h>
#include<iomanip>
using namespace std;

typedef struct Member
{
	float age;
	char *Name;
	struct Member *next;
} MEM, *pMEM;

char *process(const string & s)
{
	char *newstr = new char[s.size() + 1]{ 0 };
	strcpy(newstr, (char *)(s.c_str()));
	return newstr;
}

float StrConvert(const string & s, int *t)
{
	float result = 0;
	int k = 10;
	size_t i = 0;
	int flag = 0;

	for (i = 0; i != s.size(); ++i)
	{
	    if(!isdigit(s[i])&&s[i]!='.')
            break;

		if (s[i] >= '0' && s[i] <= '9' && flag != 1)
			result = result * k + (s[i] - '0');
		else if(s[i] == '.' || flag == 1)
		{
			flag = 1;
			if(s[i]=='.')
            {
                continue;
            }
			int num=(s[i]-'0')&255;

			float n=(float)num / k;
			result += n;
			k *= 10;
		}
	}
	*t = ++i;
	return result;
}

void Destory(pMEM head)
{
	pMEM t;
	while (head)
	{
		t = head;
		head = head->next;
		delete t;
	}
}

int main()
{
	fstream in("1.txt", ios::binary | ios::in);
	if (!in)
		exit(1);

	string text;
	pMEM head = nullptr, p = nullptr;

	while (getline(in, text))
	{
		pMEM t = new MEM;
		int cur;
		t->age = StrConvert(text, &cur);
		t->Name = process(text.substr(cur));
		if (p)
			p->next = t;
		p = t;
		t->next = nullptr;
		if (!head)
			head = p;
	}
	in.close();

	for (pMEM elem = head; elem != nullptr; elem = elem->next)
	{
	    cout<<setiosflags(ios::fixed);
	    cout<<setprecision(2);
		cout << elem->age << " " << (elem->Name) << endl;
	}
	cout << endl;
	Destory(head);
	return 0;
}
