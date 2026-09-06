#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;
unsigned char key[8] = {
		0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01
};
void inputOut(fstream& in)
{
	ostringstream os;
	os << in.rdbuf();
	string text = os.str(), s,tmp;

	while ([&]()mutable->bool {cout << "ÇëÊäÈëºº×Ö:" << endl;
	cin >> s; return s != "end"; }())
	{
		size_t offset, i = 0;
		while (i<s.size())
		{
			offset = (94 * (unsigned int)((s[i] - 0xa0 - 1)&0xff )
				+ ((s[i+1] - 0xa0 - 1)&0xff)) * 32;
			cout<<offset<<endl;
			tmp = text.substr(offset, 32);
			for(int vi=0;vi<tmp.size();++vi)
			cout<<(int)(tmp[vi]&0xff)<<" ";
			cout<<endl;
			fstream out(s.substr(i, 2), ios::binary | ios::out);
			if (out.fail())
				exit(1);
			out.write(tmp.c_str(), tmp.size());
			out.close();
			for (int len = 0; len < 16; ++len)
			{
				for (int set = 0; set < 2; ++set)
				{
					for (int j = 0; j < 8; ++j)
					{
						cout <<setw(2)<< (tmp[len * 2 + set] & key[j] ? 
							s.substr(i, s.size()) : " ");
					}
				}
				cout << endl;
			}

			i += 2;
			cout << endl;
		}
	}
}
int main()
{
	string fileName = "HZK16";
	fstream infile(fileName, ios::binary|ios::in );
	if (!infile)
		exit(1);
	inputOut(infile);
	infile.close();
	system("pause");
	return 0;
}