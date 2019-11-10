#pragma once
#include<iostream>
#include<string>
#include<stdio.h>      
#include<cstdlib>
#include<ctime>
#include"Location.h"

using namespace std;

class Enemy
{
public:
	bool isDead = GetSymbol() == '~';
	bool BattleMode;
	Location location;
	
	
	///constructors
	Enemy();
	Enemy(string name, char symbol, int attackPower, int defensePower, int xpValue, int health);

	///getters
	Location GetPosition();
	char GetSymbol();
	string GetName();
	int GetXP();
	

	///setters
	void SetPosition(Location Pos);
	void SetSymbol();
	void SetHealth();

	///methods
	int Attack();
	void TakeDamage(int damage);
	int Die();
	void PrintUI();


	///destructor
	~Enemy();

private:
	char Symbol;
	string Name;
	int Health;
	int AttackPower;
	int DefensePower;
	int XPValue;
	
	
};

