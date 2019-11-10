#include "Location.h"



Location::Location()
{
}

int Location::GetX()
{
	return X;
}

int Location::GetY()
{
	return Y;
}

void Location::SetLocation(int x, int y)
{
	X = x;
	Y = y;
}

void Location::SetX(int x)
{
	X = x;
}

void Location::SetY(int y)
{
	Y = y;
}


Location::~Location()
{

}
