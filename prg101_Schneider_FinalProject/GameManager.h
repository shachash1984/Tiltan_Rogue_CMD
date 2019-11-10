#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<stdlib.h>
#include"Level.h"
#include"Player.h"
#include"Trap.h"

using namespace std;


class GameManager
{
public:
	static bool gameOver;
	//static int frameCounter = 0;
	

	///constructor
	GameManager(string levelName);
	
	///getters

	
	///setters


	///methods
	static void Init();
	static void PlayerMove(Level& level, Player& P);
	static void Play(Level& l, Player& p, string s);

	///destructor

	~GameManager();

private:
	string levelData;
	
	
};

