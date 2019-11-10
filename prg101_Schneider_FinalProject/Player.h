#pragma once
#include<iostream>
#include<string>
#include<stdlib.h>
#include<cstdlib>
#include<ctime>
#include"Location.h"
#include"Enemy.h"


using namespace std;

class Player
{
public:
	bool isDead = false;
	bool BattleMode;
	char Symbol;
	Location location;

	///constructor
	Player();
	Player(int health, int xp, int attackPower, int defensePower);

	///getters
	
	Location GetPosition();
	char GetSymbol();

	///setters
	
	void SetPosition(Location playerPos);
	void SetXP(int xp);
	void SetSymbol();
	void SetHealth();
	


	///methods
	
	
	int Attack(Enemy& e);
	void TakeDamage(int damage);
	void PrintUI();

	

	///destructor
	~Player();

private:
	
	int Health;
	int XP;
	int DefensePower;
	int AttackPower;
	
	
	

};

