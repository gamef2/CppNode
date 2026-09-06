#include<iostream>
using namespace std;

class Furniture
{
public:
	int weight_;
	Furniture(int weight):weight_(weight)
	{
		cout<<"Furniture(int weight):weight_(weight)"<<endl;
	}
	~Furniture()
	{
		cout<<"~Furniture()"<<endl;
	}
};
class Bed:virtual public Furniture
{
public:
	Bed(int weight):Furniture(weight)
	{
		cout<<"Bed(int weight):Furniture(weight)"<<endl;
	}
	void Sleep()
	{
		cout<<"Sleep()..."<<endl;
	}
	~Bed()
	{
		cout<<"~Bed()"<<endl;
	}
//private:
	//int weight_;
};

class Sofa:virtual public Furniture
{
public:
	Sofa(int weight):Furniture(weight)
	{
		cout<<"Sofa(int weight):Furniture(weight)"<<endl;
	}
	~Sofa()
	{
		cout<<"~Sofa()"<<endl;
	}
	void WatchTv()
	{
		cout<<"WatchTv()..."<<endl;
	}
	//int weight_;
};
class SofaBed:public Bed,public Sofa
{
public:
	SofaBed(int weight):Sofa(weight),Bed(weight),Furniture(weight)
	{
		cout<<"SofaBed(int weight):Sofa(weight),Bed(weight),Furniture(weight)"<<endl;
	}
	~SofaBed()
	{
		cout<<"~SofaBed()"<<endl;
	}
	void FoldOut()
	{
		cout<<"FoldOut()..."<<endl;
	}
	void FoldInt()
	{
		cout<<"FoldInt()..."<<endl;
	}
};

int main()
{
	SofaBed sofabed(10);
	sofabed.weight_=20;
	/*sofabed.Bed::weight_=10;
	sofabed.Sofa::weight_=20;*/
	
	sofabed.WatchTv();
	sofabed.FoldOut();
	sofabed.Sleep();
}