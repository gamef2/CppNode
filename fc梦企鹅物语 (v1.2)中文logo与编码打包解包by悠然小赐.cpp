#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
void use();
/*图形部分与$2000到0x2400的ppu编码部分的解压缩以0xff结束*/
const int MapOffset = 0x1c970;
const int MapNumOffset = 0x1c891;
//编码
void packbits(string &src,int locat)
{
	string dst;

	int count;
	int srcSize = src.size();
	int i=0, curPos = locat;
	int t;
	while (i < srcSize)
	{
		if (i <= (srcSize - 2) &&
			src[i] == src[i + 1] )
		{
			for (t = i+ 2; t<srcSize&&src[t] == src[i]&&(t-i)<0x7f; )
				++t;
			count = t - i;

			dst+= count; 
			dst+= src[i]; 
		}
		else 
		{
			
			for (t = i; t < srcSize&&t - i < 0x7f; )
				if (t <= (srcSize - 3) && src[t] == src[t + 1] && src[t] == src[t + 2])
					break; 
				else
					++t;
			count = t - i;
			dst+= (count |0x80);  
			dst+= src.substr(i, count); 
		}
		i += count;
	}
	/* 结束符 */
	dst += (char)0xff;
	src = dst;
}
//2、解码
void unpackbits(string &inp, string& outp,int i)
{
	/* 获取位置 */
	int len;
	int val;
	/* 获取文件 */
	int inLength = inp.size();
	while (i < inLength)
	{
		/* 遇到0xff结束 */
		len = inp[i++]&0xff;
		if (len == 0xff)
			break;

		if (len < 0x80)
		{
			/* 取byte*/
			val = inp[i++] & 0xff;
			/* （string分配len个val）相加 */
			outp += string(len, val);
		}
		else
		{
			/* 清除最高位 */
			len = len & 0x7f;
			/* 从inp的i开始地方截取长度为len的数据 */
			outp += inp.substr(i,len);
			/* 地址偏移 */
			i += len;
		}
	}
}
string ReadFileProcess(fstream &is,string& test,int locat)
{
	ostringstream os;
	os << is.rdbuf();
	test.assign(os.str());
	string s;
	unpackbits(test,s,locat);
	return s;
}

string WriteFilePorcess(fstream &is,string& test,int locat)
{
	ostringstream os;
	os << is.rdbuf();
	string s(os.str());
	packbits(s,locat);
/*
	fstream out("2.bin", ios::out | ios::binary);//测试单独压缩并写入一个文件
	out.write(s.c_str(), s.size());
	out.close();*/
	test.replace(test.begin() + locat, 
		test.begin() + locat + s.size(),
		s);
	return s;
}
void WriteFile(const string& test, fstream &infile)
{
	infile.write(test.c_str(), test.size());
}
void otherWrite(string& test)
{
	fstream infile("1.nes", ios::binary | ios::out);
	if (infile.eof())
	{
		cerr << "error" << endl;
		exit(1);
	}
	int i = 0;
	while (i<3)
	{
		test[0x3fc37 + i] = (char)0xea;
		i++;
	}
	test[0x3fc4b] = (char)0x80;
	WriteFile(test, infile);
	infile.close();
}
void Map()
{
	string inName("1.nes"), outName("1.bin");
	fstream infile(inName, ios::in | ios::binary | ios::_Nocreate);
	if (infile.eof())
	{
		cerr << "error" << endl;
		exit(1);
	}
	string test, s = ReadFileProcess(infile, test, MapOffset);
	infile.close();
	fstream outfile(outName, ios::out | ios::binary);
	if (infile.fail())
		cerr << "创建文件" << endl;
	WriteFile(s, outfile);
	outfile.close();

	cout << "已生成文件1.bin编辑好chr，按键打包继续处理" << endl;
	cin.get();
	infile.open(outName, ios::in | ios::binary | ios::_Nocreate);
	if (infile.eof())
	{
		cerr << "error" << endl;
		exit(1);
	}
	s = WriteFilePorcess(infile, test, MapOffset);
	infile.close();

	outfile.open(inName, ios::out | ios::binary);
	if (infile.fail())
	{
		cerr << "没有找到文件!" << endl;
		exit(1);
	}
	WriteFile(test, outfile);
	outfile.close();
	otherWrite(test);
	cout << "写入成功！" << endl;
	cin.get();
}
void MapNumBer()
{
	string inName("1.nes"), outName("2.bin");
	fstream infile(inName, ios::in | ios::binary | ios::_Nocreate);
	if (infile.eof())
	{
		cerr << "error" << endl;
		exit(1);
	}
	string test, s = ReadFileProcess(infile, test, MapNumOffset);
	infile.close();
	fstream outfile(outName, ios::out | ios::binary);
	if (infile.fail())
		cerr << "创建文件" << endl;
	WriteFile(s, outfile);
	outfile.close();

	cout << "已生成文件2.bin,请编辑好chr的编码，按键打包继续处理" << endl;
	cin.get();
	infile.open(outName, ios::in | ios::binary | ios::_Nocreate);
	if (infile.eof())
	{
		cerr << "error" << endl;
		exit(1);
	}
	s = WriteFilePorcess(infile, test, MapNumOffset);
	infile.close();

	outfile.open(inName, ios::out | ios::binary);
	if (infile.fail())
	{
		cerr << "没有找到文件!" << endl;
		exit(1);
	}
	WriteFile(test, outfile);
	outfile.close();
	cout << "写入成功！" << endl;
	cin.get();
}
int main()
{
	Map();
	MapNumBer();

	return 0;
}
void use()
{
	cout << "梦企鹅物语 (v1.2)[汉化你妹\n图形与编码打包解包\n"
		"西游记logo画面解包与打包程序by悠然小赐\n"
		"-----------------------------------\n"
		"文件名为1.nes，放cpp相同路径下。\n"
		"图形处理后生成文件 1.bin用chr工具编辑"
		"图形编码处理后生成文件 2.bin用chr工具编辑"
		"使用前先备份原rom\n按键继续!" << endl;
	cin.get();
}
