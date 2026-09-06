#include<iostream>
using namespace std;
const unsigned N=0x80;
/*c++仿汇编除算*/
bool And(char a)
{
	return a&0x80?true:false;
}
int main()
{
	unsigned char chars[6];

	unsigned short *num=(unsigned short*)chars,*divisor=(unsigned short*)(chars+2),
		*other=(unsigned short*)(chars+4);
	while (cin>>*num&&cin>>*divisor)
	{
		chars[4]=chars[5]='\0';//初始等于0
		char t1,t2;

		for (int i=16;i!=0;i--)
		{
			size_t flag=0;

			t1=chars[0];
			chars[0]<<=1;

			t2=t1,t1=chars[1];
			chars[1]<<=1;
			chars[1]+=And(t2);//进位操作

			
			t2=t1,t1=chars[4];
			chars[4]<<=1;
			chars[4]+=And(t2);//进位操作

			t2=t1;
			chars[5]<<=1;
			chars[5]+=And(t2);//进位操作
			
			chars[0]++;

			if (chars[4]<chars[2])
			{
				if (chars[5]<=chars[3])
					flag=1;
				chars[5]--;
			}

			chars[4]-=chars[2];
			if (chars[5]<chars[3])
				flag=1;
			chars[5]-=chars[3];
			if (flag==1)//不够减的情况
			{
				chars[4]>=chars[2]?(t1=chars[4],t2=chars[2]):(t1=chars[2],t2=chars[4]);//取最大值
				
				
				chars[4]+=chars[2];
				chars[5]+=chars[3];
				if (t1>=N)//如果最大值超过0x80则减去这个值
				{
					t1-=N;
					if (t1+t2>=N)//判断相加的值是否超过无符号类型的0x80
						chars[5]++;
				}

				//方法2
				/*short adi=chars[4];//用来判断是否有进位
				adi+=chars[2];

				chars[4]+=chars[2];
				chars[5]+=chars[3];
				if (adi>255)
					chars[5]++;*/
				chars[0]--;
			}

		}
		cout<<"结果:"<<*num<<"\t 余数"<<*other<<endl;
	}
	system("pause");
	return 0;
}