#pragma once
class Location
{
public:
	///constructor
	Location();

	///getters
	int GetX();
	int GetY();

	///setters
	void SetLocation(int x, int y);
	void SetX(int x);
	void SetY(int y);

	///methods


	///destructor
	~Location();

private:
	int X;
	int Y;
};

