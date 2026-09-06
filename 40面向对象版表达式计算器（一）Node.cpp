#include "Node.h"
#include <cmath>
#include<iostream>

double NumberNode::Calc()const
{
	return number_;
}

double AddNode::Calc()const
{
	return left_->Calc()+right_->Calc();
}

BinaryNode::~BinaryNode()
{
	delete left_;
	delete right_;

}



double SubNode::Calc()const
{
	return left_->Calc()-right_->Calc();
}

double MultiplyNode::Calc()const
{
	return left_->Calc()*right_->Calc();
}

double DivideNode::Calc()const
{
	double divisor=right_->Calc();
	if (divisor != 0)
	{
		return left_->Calc()/divisor;
	}
	else
	{
		std::cout<<"Error : Divisor by zero"<<std::endl;
		return HUGE_VAL;//的返回一个最大值

	}

}

double UminusNode::Calc()const
{
	return - child_->Calc();
}