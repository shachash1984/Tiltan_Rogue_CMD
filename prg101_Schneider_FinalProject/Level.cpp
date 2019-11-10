#include "Level.h"



Level::Level()
{
	currentLevel = 1;
}

char Level::GetTileSymbol(Location pos)
{
	char symbol = mapData[pos.GetX()][pos.GetY()];
	return symbol;
}

int Level::GetWidth()
{
	return Width;
}

int Level::GetHeight()
{
	return Height;
}

void Level::SetTileSymbol(Location pos, char symbol)
{
	mapData[pos.GetX()][pos.GetY()] = symbol;

}




void Level::Load(string fileName)
{
	ifstream levelFile;

	levelFile.open(fileName + ".txt");
	if (levelFile.fail()) {
		perror("Level not Found");
		return;
	}
	
	string levelDrawer;
	int rows = 0;
	while (getline(levelFile, levelDrawer))
	{
		for (int columns = 0; columns < Height; columns++) {
				mapData[rows][columns] = levelDrawer[columns];
		}
		rows++;
	}
	levelFile.close();
}

void Level::Print(Player& p)
{
	//printing the level
	system("CLS");
	for (int i = 0; i < Width; i++) {
		cout << endl;
		for (int j = 0; j < Height; j++) {
			cout << mapData[i][j];
		}
		
	}
	//Assistance key
	cout << "\n\nKey: \n\nH = Hero\nX = Exit\n+ = Wall\nO = Open trap\no = Closed trap\nE = Enemy\nSize: " << Height << " * " << Width << endl << endl;
	//printing stats for player and enemies
	p.PrintUI();
	enemies[0].PrintUI();
	enemies[1].PrintUI();
	cout << "" << endl;
	//directions
	if (!p.isDead) {
		cout << "Use the WASD keys to move the player." << endl << endl;
	}
	//printing the current notification
	cout << notification << endl << endl;

	
}

Location Level::MovePlayer(Player& p)
{	
	for (int i = 0; i < Width; i++) {
		cout << endl;
		for (int j = 0; j < Height; j++) {

			if (mapData[i][j] == p.GetSymbol())
			{
				//finding the player and setting its initial position
				Location currentPlayerLocation;
				currentPlayerLocation.SetLocation(i, j);
				p.SetPosition(currentPlayerLocation);				
			}
		}
	}
	//initializing the next position for the player
	Location nextPos = p.GetPosition();
	return nextPos;
}

void Level::UpdateLevel(Location nextPos, Player& p, char input)	{

	int x = nextPos.GetX();
	int y = nextPos.GetY();
	if (p.isDead) {
		GameOver = true;
		notification = "The Player has died...\nPress 'x' to return to Main Menu";
	}
	//setting the next position according to user input
	if (!GameOver) {
		switch (input)
		{
			case 'w': {
				x--;
				nextPos.SetLocation(x, y);
				break;
			}

			case 's': {
				x++;
				nextPos.SetLocation(x, y);
				break;
			}

			case 'd': {
				y++;
				nextPos.SetLocation(x, y);
				break;
			}

			case 'a': {
				y--;
				nextPos.SetLocation(x, y);
				break;
			}
		}

		//checking the status of the next position
		switch (GetTileSymbol(nextPos))
		{
		case ' ':
		{
			//next position is empty - player is free to go
			SetTileSymbol(p.GetPosition(), ' ');
			p.SetPosition(nextPos);
			p.SetSymbol();
			SetTileSymbol(p.GetPosition(), p.GetSymbol());
			notification = "";
			break;
		}
		case 'X':
		{
			//player has reached the exit and finished the level
			system("Color 57");
			GameOver = true;
			notification = "Hooray! you have reached the Exit! ...\nPress 'c' to continue to the next level\nPress 'x' to return to Quit";			
			break;
		}
		case 'O':
		{
			//player has gone into an open trap - taking damage
			if (!p.isDead) {
				notification = "Oh no! You fell into a trap!";
				srand(time(0));
				int damage = rand() % 20 + 1;
				p.TakeDamage(damage);
				SetTileSymbol(p.GetPosition(), p.GetSymbol());
			}			
			break;
		}
		case 'o':
		{
			//player has gone into a closed trap and disabled it
			SetTileSymbol(p.GetPosition(), ' ');
			p.SetPosition(nextPos);
			p.SetSymbol();
			SetTileSymbol(p.GetPosition(), p.GetSymbol());
			notification = "Way to go! yo passed the trap!";
			break;
		}
		case '+':
		{
			//wall
			notification = "You are blocked by the wall";
			break;
		}
		case 'E':
		{
			//player is encountering an enemy
			//taking and giving damage
			//last one still standing wins the battle
			for (int i = 0; i < 2; i++) {
				if (enemies[i].GetPosition().GetX() == nextPos.GetX() && enemies[i].GetPosition().GetY() == nextPos.GetY())
				{
					notification = "Attacking Enemy!";
					system("Color 2B");
					enemies[i].BattleMode = true;
					p.BattleMode = true;
					p.TakeDamage(enemies[i].Attack());
					enemies[i].TakeDamage(p.Attack(enemies[i]));

					if (enemies[i].isDead) {
						//player has won and is getting XP
						SetTileSymbol(enemies[i].GetPosition(), enemies[i].GetSymbol());
						enemies[i].BattleMode = false;
						p.BattleMode = false;
						system("Color 07");
						p.SetXP(enemies[i].Die());
						notification = "You Won!";
					}
					if (p.isDead) {
						//player has died - game over
						SetTileSymbol(p.location, p.GetSymbol());
						enemies[i].BattleMode = false;
						p.BattleMode = false;
						notification = "The Player has died...\nPress 'x' to Exit";
						return;
					}
				}
			}
			break;
		}
		default:
			break;
		}
	}
}

void Level::MoveEnemies(Enemy eArr[], Player& p)
{
	
	for (int k = 0; k < 2; k++) {
		int xDirection = 0;
		int yDirection = 0;
		//checking the location of the player relative to the enemy and checking that the enemy isn't dead
		if (abs(eArr[k].GetPosition().GetX() - p.GetPosition().GetX()) <= 12 && abs(eArr[k].GetPosition().GetY() - p.GetPosition().GetY()) <= 12 && eArr[k].isDead == false)
		{
			//telling the enemies in which direction to go
			xDirection = p.GetPosition().GetX() - eArr[k].GetPosition().GetX();
			if (xDirection > 0) {
				xDirection = 1;
			}
			else if (xDirection < 0) {
				xDirection = -1;
			}
			
			yDirection= p.GetPosition().GetY() - eArr[k].GetPosition().GetY();
			if (yDirection > 0) {
				yDirection = 1;
			}
			else if (yDirection < 0) {
				yDirection = -1;
			}
			
			//moving the enemies
			Location enemyNextPos;
			enemyNextPos.SetX(eArr[k].GetPosition().GetX() + xDirection);
			enemyNextPos.SetY(eArr[k].GetPosition().GetY() + yDirection);
			eArr[k].SetSymbol();
			if (GetTileSymbol(enemyNextPos) == ' ' ) {
				SetTileSymbol(eArr[k].GetPosition(), ' ');
				eArr[k].SetPosition(enemyNextPos);
				SetTileSymbol(eArr[k].GetPosition(), eArr[k].GetSymbol());
			}
		}		
	}	
}

void Level::InitEnemies(Enemy eArr[]) {
	int enemyNum = 0;
	for (int i = 0; i < Width; i++) {
		cout << endl;
		for (int j = 0; j < Height; j++) {

			if (mapData[i][j] == 'E' || mapData[i][j] == '~')
			{
				//finding the enemies on the grid and setting their position
				Location enemyLocation;
				enemyLocation.SetLocation(i, j);
				eArr[enemyNum].SetPosition(enemyLocation);
				enemyNum++;
			}

		}
	}
}

void Level::ToggleTraps(Player& p)
{
	int trapNum = 0;
	for (int i = 0; i < Width; i++) {
		cout << endl;
		for (int j = 0; j < Height; j++) {

			if (mapData[i][j] == 'O' || mapData[i][j] == 'o')
			{
				//finding the traps on the grid
					Trap trap;
					trap.SetSymbol(mapData[i][j]);
					trap.location.SetLocation(i, j);
					trap.GetState();
					traps[trapNum] = trap;
					trapNum++;
			}			
		}
	}
	for (int t = 0; t < trapNum; t++) {		

		//changing the status of the traps
			if (traps[t].GetState() == false)
			{
				traps[t].SetSymbol('O');
				SetTileSymbol(traps[t].GetLocation(), traps[t].GetSymbol());
			}
			else
			{
				traps[t].SetSymbol('o');
				SetTileSymbol(traps[t].GetLocation(), traps[t].GetSymbol());
			}		
	}
	
}

Level::~Level()
{
}
