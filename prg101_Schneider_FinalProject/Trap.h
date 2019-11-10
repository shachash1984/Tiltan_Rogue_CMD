#pragma once
#include<iostream>
#include<string>
#include"Location.h"

using namespace std;

class Trap
{
public:

	bool isOpen;
	Location location;

	///constructor
	Trap();
	
	///getters
	Location GetLocation();
	char GetSymbol();
	bool GetState();

	///setters
	void SetSymbol(char symbol);

	///methods
	

	///destructor
	~Trap();

private:
	
	int Damage;
	char Symbol;
	
};

