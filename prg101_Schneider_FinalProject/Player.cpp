#include "Player.h"



Player::Player()
{
}

Player::Player(int health, int xp, int attackPower, int defensePower)
{
	Health = health;
	SetSymbol();
	XP = xp;
	AttackPower = attackPower;
	DefensePower = defensePower;
}






Location Player::GetPosition()
{
	return location;
}

char Player::GetSymbol()
{
	return Symbol;
}

void Player::SetPosition(Location playerPos)
{
	location.SetLocation(playerPos.GetX(), playerPos.GetY());	
}

void Player::SetXP(int xp)
{
	XP += xp;	
}

void Player::SetSymbol()
{
	if (isDead) {
		Symbol = '$';
	}
	else {
		Symbol = 'H';
	}
	
}

void Player::SetHealth()
{
	Health = 100;
}

void Player::PrintUI()
{
	SetSymbol();
	cout << "Player Stats: " << endl << endl;
	cout << "Health: " << Health << endl;
	cout << "XP: " << XP << endl;
	cout << "Attack Power: " << AttackPower << endl;
	cout << "Defense Power: " << DefensePower << endl;
}

int Player::Attack(Enemy& e)
{
	if (BattleMode) {
		if (e.isDead)
		{
			SetXP(e.GetXP());
			DefensePower *= 0.5*XP;
			AttackPower *= 0.5*XP;
		}
		else
		{
			srand(time(0));
			int attack;
			attack = rand() % (3 * AttackPower) + 1;
			return attack;
		}
	}
	
	return 0;
	
}

void Player::TakeDamage(int damage)
{
	int defense;
	defense = rand() % (2 * DefensePower) + 1;
	damage -= defense;
	if (damage <= 0)
		damage = 1;
	
	Health -= damage;
	if (Health <= 0) {
		Health = 0;
		isDead = true;
		system("Color 04");
	}
	else if (Health > 0) {
		isDead = false;
	}		
	SetSymbol();
		

}

Player::~Player()
{
}
