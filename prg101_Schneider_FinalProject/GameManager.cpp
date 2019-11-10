#include "GameManager.h"




GameManager::GameManager(string levelName)
{
}

void GameManager::Init()
{	
	int menuOption = 0;

	do
	{		//main menu
		cout << "Main Menu: \n1. Play\n2.Exit" << endl;
		cin >> menuOption;
		//initializing the level, player and enemies
		Level lev = Level();
		Player p = Player(100, 1, 15, 6);
		Enemy e1 = Enemy("Rob", 'E', 15, 4, 5, 45);
		Enemy e2 = Enemy("White", 'E', 18, 6, 7, 60);
		lev.enemies[0] = e1;
		lev.enemies[1] = e2;
		switch (menuOption)
		{
		case 1: {
			//play the game		
			stringstream temp;
			temp << lev.currentLevel;
			string str = temp.str();
			string levelName = "Level" + str;
			GameManager::Play(lev, p, levelName);
			system("Color 07");
			return;
			break;
		}
		case 2: {
			//exit
			return;
			break;
		}
		default:
			break;
		}
	} while (menuOption != 2);
}



void GameManager::PlayerMove(Level& level, Player&  P)
{
	char input = 'n';
	int frameCounter = 0;

	
	while (input != 'x')
	{		
		if (input == 'c')
		{
			//loading next level and setting counters to zero
			system("Color 07");
			level.GameOver = false;
			frameCounter = 0;
			stringstream temp;
			level.currentLevel++;
			temp << level.currentLevel;
			string str = temp.str();
			string levelName = "Level" + str;
			level.Load(levelName);
			//initializing enemies and player
			for (int i = 0; i < 2; i++) {
				level.enemies[i].SetHealth();
				level.enemies[i].isDead = false;
			}
			P.SetHealth();			
		}
		//printing the level, moving the player, updating the grid every movement, moving enemies and toggling traps
			level.Print(P);
			cin >> input;
			Location nextPos = level.MovePlayer(P);
			if (frameCounter == 0) {
				level.InitEnemies(level.enemies);
			}
			level.MoveEnemies(level.enemies, P);
			level.UpdateLevel(nextPos, P, input);
			level.ToggleTraps(P);
			frameCounter++;			
	}
	
	
		
	
}

void GameManager::Play(Level & l, Player & p, string s)
{
	//loading the first level
	system("Color 07");
	l.GameOver = false;
	l.Load(s);
	GameManager::PlayerMove(l, p);
	
	
}





GameManager::~GameManager()
{
}
