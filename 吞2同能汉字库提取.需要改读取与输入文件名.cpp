#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<windows.h>
using namespace std;

#define byte unsigned char
const int Size = 16;
int flag_c = 0;
//如果函数返回不赋值的话将不会改变
//ROL的移位功能是将字节内容连同进位C一起依次向左移1位
byte ROL(byte val)//循环左移
{
    byte ret = val >> 7;//右移最高位
    val <<= 1;//左移位
    val |= flag_c;//是1则相或
    flag_c = false;//清除标志位
    flag_c |= ret;//读取最高位是否是1
    return val;
}

//ASL移位功能是将字节内各位依次向左移1位,最高位移进标志位C中,最底位补0
byte ASL(byte val)//算术左移
{
    flag_c = false;//清除标志位
    byte ret = val >> 7;//右移最高位
    val <<= 1;//左移位
    flag_c |= ret;//读取最高位是否是1
    return val;
}

//该指令功能是将字节内各位依次向右移1位,最低位移进标志位C,最高位补0.
byte LSR(byte val)//逻辑右移
{
    flag_c = false;//清除标志位
    flag_c |= val & 1;//得到进位标志
    val >>= 1;//右移位
    return val;
}

bool Empty(byte arr[], int sz)
{
    int cnt = 0, i;
    for (i = 0; i < sz; i++) //判定获取的是否都是0,是的话结束
    {

        if (arr[i] == '\0')
        {
            ++cnt;
        }
    }
    return cnt == i;
}

byte DataResult(byte arr[],byte &elem,byte &re, int &cnt_0, int &cnt_1, int &SetAddr, int cnt_x)
{
    do
    {
        if (!(--SetAddr))
        {
            elem = arr[cnt_1++];
            SetAddr = 8;
        }
        elem = LSR(elem);//逻辑右移
        re = ROL(re);//循环左移
    }
    while (--cnt_x);
    return  re;
}
void ElemProcess(byte data[],byte tmp[])
{
    //cnt_0=51f8,cnt_1=51f9,SetAddr=51fa,elem=51fb, re=result


    byte elem = '\0', re = '\0';


    int cnt_0 = 5, cnt_1 = 0, SetAddr = 1;
    do
    {
        re = '\0';
        byte c = DataResult(data, elem,re,cnt_0, cnt_1, SetAddr, 8);
        tmp[cnt_0] = c;//第一行
        c = DataResult(data, elem, re, cnt_0, cnt_1, SetAddr, 3);

        c <<= 5;

        tmp[cnt_0 + 0x10] = c;//第二行的
        ++cnt_0;
    }
    while (cnt_0 != 16);

}
int main()
{
    byte data[16] ={
        0x88, 0x40, 0x04, 0x22, 0x15, 0xA5, 0x1B, 0x45, 0x28, 0x42, 0x11, 0xBA, 0x74, 0xE4, 0xE0, 0xF9
    };


    ifstream fpr("1.dat",ios::binary|ios::in);
    if (!fpr)
    {
        cout<<"未发现文件退出"<<endl;
        exit(1);
    }
    else//90410是前部分字库
        fpr.seekg(0x91010,ios::beg);
    ofstream fpw("2.dat",ios::binary|ios::out);
    if (!fpw)
    {
        cout<<"未发现文件并创建"<<endl;
    }
    fpw.close();
    fpw.open("2.dat",ios::binary|ios::out|ios::in);
    cout<<"创建成功"<<endl;
    byte tmp[Size * 2] { 0 }, out[Size * 4] { 0 };


    while(1)
    {
        //memset((char*)data,0,Size);

        fpr.read((char*)data,Size);
        if (Empty(data, Size))//读取连续为空则退出
            break;
        ElemProcess(data,tmp);
        int i=0,j=0,k=0;
        while(k<Size*2/8)
        {
            memcpy((char*)out+i,(char*)tmp+j,8);
            k++;
            i+=0x10,j+=0x8;
        }
        fpw.write((char*)out,Size*4);
    }
    fpw.close();
    fpr.close();

    cout<<"写入2.dat完毕"<<endl;
    return 0;
}
