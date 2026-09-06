#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>

using namespace std;
typedef unsigned char byte;

int unpack(string&, int, byte**);//函数声明
int main()
{
	//std::locale loc = std::locale::global(std::locale(""));
	string FileName = "1.bin";

	fstream infile;
	infile.open(FileName.c_str(), ios::in | ios::binary|ios::_Nocreate);
	if (infile.eof())
	{
		cerr << "没有文件" << endl;
		exit(1);
	}
	ostringstream os;
	os << infile.rdbuf();//读取全部
	infile.close();
	string rom = os.str();

	int index = 2;
	byte* output=nullptr;
	int size = unpack(rom, index, &output);
	rom = reinterpret_cast<char*>(output);
	istringstream is(rom);
	
	infile.open("out.bin", ios_base::out | ios_base::binary);
	if (infile.fail())
		cerr << "open Error" << endl;
	infile.write((char*)output, size);
	infile.close();
	//std::locale::global(loc);
	return 0;
}
int unpack(string& rom, int index, byte** output)
{
	const int table = 0x70000;
	index <<= 2;
	int offset = (rom[table + index + 0] << 24) +
		(rom[table + index + 1] << 16) +
		(rom[table + index + 2] << 8) +(rom[table + index + 3]&0xff); 

	int rpos = table + offset;

	int size = (rom[rpos] << 24) | 
		(rom[rpos + 1] << 16) |
		(rom[rpos + 2] << 8) | (rom[rpos + 3]&0xff);

	rpos += 4;
	
	*output = new byte[size];
	char *str = (char *)*output;
	memset(str, 0, size);
	int wpos = 0;
	size >>= 2;
	byte nibbles = 8;
	byte mask = 0xF;
	int b, nibble, count;
	while (size > 0)
	{
		b = rom[rpos++]&0xff;
		nibble = b;
		nibble >>= 4;
		count = 0;
		b &= mask;
		if (b < 0xD)
			count = b;
		else
		{
			if (b == 0xD)
			{
				count = rom[rpos++]&0xff;
			}
			else
			{
				if (b == 0xE)
				{
					count = (rom[rpos + 0] << 8) | (rom[rpos + 1]&0xff);
					rpos += 2;
				}
				else
				{
					count = (rom[rpos + 0] << 8) | (rom[rpos + 1]&0xff);
					count += 0x10000;
					rpos += 2;
				}
			}
		}
		int token = 0;
		for (int i = 1; i <= count + 1; ++i)
		{
			token <<= 4;
			token |= nibble;
			if (nibbles == 1)
			{
				output[0][wpos + 0] = (byte)((token >> 24) & 0xFF);
				output[0][wpos + 1] = (byte)((token >> 16) & 0xFF);
				output[0][wpos + 2] = (byte)((token >> 8) & 0xFF);
				output[0][wpos + 3] = (byte)((token >> 0) & 0xFF);
				wpos += 4;

				nibbles = 8;
				if (size == 1)
				{
					size = 0;
					break;
				}
				size--;
			}
			else
				nibbles--;
		}
	}
	return wpos;
}