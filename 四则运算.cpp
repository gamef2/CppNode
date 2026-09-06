#include<iostream>
using namespace std;
int main()
{
	cout<<"四则运算：如输入7.2+1.586*2/3回车:"<<endl;
	char a[100]={0},b[100]={0};
	float c[100]={0},l,h;
	int i,m=0,n=0,k;
	cout<<"请输入算术:"<<endl;
	cin.getline(a,100);
	for(i=0;a[i]!='\0';i++)
	{
		l=h=0,k=10;
		while(a[i]>='0'&&a[i]<='9')
		{
			l=l*10+(a[i]-'0');
			i++;
		}
		if(a[i]=='.')
		{
			i++;
			while(a[i]>='0'&&a[i]<='9')
			{
				h=h+(float)(a[i]-'0')/k;
				k*=10;
				i++;
			}
		}
		if(a[i]=='*'||a[i]=='/'||a[i]=='+'||a[i]=='-')
			b[m++]=a[i];
		c[n++]=l+h;
	}
	for(i=0;b[i]!='\0';i++)
	{
		if(b[i]=='*'||b[i]=='/')
		{
			switch(b[i])
			{
			case '*':
				c[i+1]*=c[i];
				c[i]=0;
				if(i==0)
					b[i]='+';
				else
					b[i]=b[i-1];
				break;
			case '/':
				c[i+1]=c[i]/c[i+1];
				c[i]=0;
				if(i==0)
					b[i]='+';
				else
					b[i]=b[i-1];
				break;
			}
		}
	}
	for(i=0;b[i]!='\0';i++)
	{
		if(b[i]=='+'||b[i]=='-')
		{
			switch(b[i])
			{
			case '+':
				c[i+1]+=c[i];
				break;
			case '-':
				c[i+1]=c[i]-c[i+1];
				break;
			}
		}
	}
	cout<<"="<<c[i]<<endl;
	return 0;
}
