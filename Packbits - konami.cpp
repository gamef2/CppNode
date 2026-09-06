//本程序由废废77鱼编写
#include<iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

class Packbits
{
public:
	Packbits() = default;
	/* 传入数据 1:数据。2:方式:code或decode，表示编码或解码。3:开始的位置，默认0*/
	void move_data(const string&, const string&, int);
	/* 编码 */
	void packbits();
	/* 解码 */
	void unpackbits();
	string getdata() { return data; }
	string getout_d() { return out_d; }
	string getunpack_src() { return unpack_src; }
	size_t cur() { return start_cur; }
	const char* data_c_str()
	{
		return data.c_str();
	}
	void free() {
		data.clear();
		out_d.clear();
		unpack_src.clear();

	}
	/* 返回一个解码的str */
	const char* out_d_c_str()
	{
		return out_d.c_str();
	}
//private:
	int start_cur = 0;
	string data;
	string out_d;
	string unpack_src;
};
void Packbits::move_data(const string& str, 
	const string& control_str = "", int p = 0)
{
	
	if (control_str == "" || control_str == "code")
	{
		unpack_src = str;
		packbits();
	}
	else
	{
		start_cur = p;
		data = str;
		unpackbits();
	}
}
void Packbits::packbits()
{
	int count;
	int Length = unpack_src.size(), i = 0, t;
	
	while (i< Length)
	{
		if (i <= (Length - 2) &&
			unpack_src[i] == unpack_src[i + 1])
		{
			for (t = i + 2; t < Length&&unpack_src[t] == unpack_src[i]
				&&t-i<0x7E;)//这里7F改7E否则魂斗罗会变成写屏幕地址
				++t;
			count = t - i;
			out_d += count;
			out_d += unpack_src[i];
		}
		else
		{
			for (t = i; t < Length && t - i < 0x7E;)//这里7F改7E否则跳出循环后会变成FF结束
				if (t <= (Length - 3) && unpack_src[t] == unpack_src[t + 1]
					&& unpack_src[t] == unpack_src[t + 2])
					break;
				else
					++t;
			count = t - i;
			out_d += (count | 0x80);
			out_d += unpack_src.substr(i, count);
		}
		i += count;
	}
	/* 结束符 */
	out_d += (char)0xFF;
}
void Packbits::unpackbits()
{ 
	int len;
	int val, i = start_cur;
	int Length = data.size();
	while (i<Length)
	{
		len = data[i++]&0xFF;
		/* 遇到0xff结束 */
		if (len ==0xFF)
			break;
		if (len < 0x80)
		{
			/* 取byte*/
			val = data[i++] & 0xFF;
			/* （string分配len个val）相加 */
			out_d += string(len, val);
		}
		else
		{
			/* 清除最高位 */
			len &= 0x7F;
			/* 从inp的i开始地方截取长度为len的数据 */
			out_d += data.substr(i, len);
			/* 地址偏移 */
			i += len;
		}
	}
	cout << "读取了并解包了" <<hex<< i << "字节" << endl;
}
fstream& input(fstream &in, Packbits &rhs, 
	const string& str, int pos)
{
	ostringstream os_n;
	os_n << in.rdbuf();
	rhs.move_data(os_n.str(),str,pos);
	return in;
}
fstream& output(fstream &os, Packbits &rhs)
{
	os.write(rhs.out_d_c_str(), rhs.getout_d().size());
	return os;
}
fstream& outputScoure(fstream &os, Packbits &rhs)
{
	string s = rhs.getdata();
	auto first = s.begin() + rhs.cur(),
		last = s.begin() + (rhs.cur() + rhs.getout_d().size());
	s.replace(first, last, rhs.getout_d());
	os.write(s.c_str(), s.size());
	return os;
}
void Test(Packbits &p,const string &control_str,int cur)
{
	string fileName,outName;
	if (control_str == "decode")
		fileName = "1.bin", outName = "2.bin";
	else
		fileName = "2.bin", outName = "3.bin";
	fstream in(fileName, ios::in | ios::binary);
	if (!in)
	{
		cerr << "没有" << fileName << "按键退出!" << endl;
		cin.get();
		exit(1);
	}
	/* 表示文件是fileName，传到np,调用编码，初始位置是0 */
	input(in, p, control_str, cur);
	in.close();

	if (remove(outName.c_str()) == 0)
		cout << "ok" << endl;
	fstream out(outName, ios::out | ios::binary);
	if (!out)
		cerr << "创建文件" << endl;
	output(out, p);
	out.close();
	cout << outName<<" 输出完毕" << endl;
	if (fileName == "2.bin"&&p.getdata().size()!=0)
	{
		char c;
		cerr << "是否写入原文件1.bin? Y/N\n";
		cin >> c;
		while (c != 'N'&&c != 'n')
		{
			if (c == 'N' || c == 'n' || c == 'Y' || c == 'y')
			{
				string tst = "1.bin";
				fstream outfile;
				outfile.open(tst, iostream::out | iostream::binary);
				outputScoure(outfile, p);
				outfile.close();
				cout << "输出" << tst <<"完毕!"<< endl;
				break;
			}
			else
			{
				cerr << "输入错误,请重新输入!" << endl;
				cin >> c;
			}
		}
	}
}
int main()
{
	string control_str;

	Packbits p;
	while ([&control_str]()->bool {
		cout << "===============\n"
			"(选择一个文件名:1.bin的源文件.放在cpp目录下\n输入方式：\n"
			"decode:解码(对1.bin进行解码,输出到2.bin)\n"
			"code:编码(对2.bin进行编码,输出到3.bin,需要先对1.bin解码出2.bin)\n"
			"end:结束!\n"
			"请输入内容:" << endl; 
		std::cin >> control_str; return control_str != "end"; }())
	{
		if (control_str != "code" && control_str != "decode")
		{
			cerr << "输入错误!请重新输入" << endl;
			continue;
		}
		int cur;

		if (control_str == "decode")
		{
			cout << "输入开始处理的位置:" << endl;
			while ([&cur]() {cin >> cur; return cur <= -1; }())
			{
				cerr << "输入错误!请重新输入" << endl;
			}
		}
		else
		{
			cout << "编码模式位置默认从2.bin的0开始" << endl;
			cur = 0;
		}
		p.free();
		Test(p, control_str, cur);
	}
	return 0;
}