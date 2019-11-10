#include "Trap.h"



Trap::Trap()
{
}

Location Trap::GetLocation()
{
	return location;
}

char Trap::GetSymbol()
{
	return Symbol;
}

bool Trap::GetState()
{
	
	if (GetSymbol() == 'O') {
		isOpen = true;
	}
	else {
		isOpen = false;
	}
	return isOpen;
}



void Trap::SetSymbol(char symbol)
{
	Symbol = symbol;	
}

Trap::~Trap()
{
}
