#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>
#include<cstdlib>
#include<ctime>
#include<Windows.h>
#include"Player.h"
#include"Trap.h"
#include"Location.h"
#include"Enemy.h"





using namespace std;

class Level
{
public:
	char mapData[18][54];
	Trap traps[2];
	Enemy enemies[2];
	string notification;
	bool GameOver;
	int currentLevel;


	///Constructors
	Level();

	///getters
	char GetTileSymbol(Location pos);
	int GetWidth();
	int GetHeight();

	///setters
	void SetTileSymbol(Location pos, char symbol);
	

	///Methods
	void Load(string fileName);
	void Print(Player& p);
	Location MovePlayer(Player& p);
	void UpdateLevel(Location nextPos, Player& p, char input);
	void MoveEnemies(Enemy eArr[], Player& p);
	void InitEnemies(Enemy eArr[]);
	void ToggleTraps(Player& p);

	

	///Destructor
	~Level();

	
	

private:
	
	const int Width = 18;
	const int Height = 54;
	


};

