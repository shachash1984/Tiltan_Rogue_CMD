#include "Enemy.h"





Enemy::Enemy()
{
}

Enemy::Enemy(string name, char symbol, int attackPower, int defensePower, int xpValue, int health)
{
	Name = name;
	Symbol = symbol;
	AttackPower = attackPower;
	DefensePower = defensePower;
	XPValue = xpValue;
	srand(time(0));
	Health = health;
	isDead = false;
	BattleMode = false;
	
}

Location Enemy::GetPosition()
{
	return location;
}

char Enemy::GetSymbol()
{
	return Symbol;
}

string Enemy::GetName()
{
	return Name;
}

int Enemy::GetXP()
{
	return XPValue;
}



void Enemy::PrintUI()
{
	cout << "\n";
	cout << "\t\t\tEnemy stats: " << endl << endl;
	cout << "\t\t\tName: " << Name << endl;
	cout << "\t\t\tHealth: " << Health << endl;
	cout << "\t\t\tXP value : " << XPValue << endl;
	cout << "\t\t\tAttack Power: " << AttackPower << endl;
	cout << "\t\t\tDefense Power: " << DefensePower << endl;	
}



void Enemy::SetPosition(Location Pos)
{
	location.SetLocation(Pos.GetX(), Pos.GetY());
}

void Enemy::SetSymbol()
{
	if (isDead) {
		Symbol = '~';
	}
	else {
		Symbol = 'E';
	}
}

void Enemy::SetHealth()
{
	srand(time(0));
	Health = rand() % 50 + 1;
}

int Enemy::Attack()
{
	srand(time(0));
	int attack = rand() % 6 + 1;
	attack += AttackPower;
	return attack;
}

void Enemy::TakeDamage(int damage)
{	//reducing damage by defense power
	damage -= DefensePower;
	if (damage <= 0)
		damage = 1;

	//reducing health by reduced damage
	Health -= damage;
	if (Health <= 0) {
		Health = 0;
		isDead = true;
	}
	else if (Health > 0) {
		isDead = false;
	}

	SetSymbol();	
}

int Enemy::Die()
{
	return XPValue;
}




Enemy::~Enemy()
{
}


