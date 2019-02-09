#include <iostream>
#include <time.h>
#include <vector> 
#include <string>

class fieldInfo
{
	public:
		static int fieldLenght;
		static int fieldWidth;
		static int fieldExitAmount;
		static std::vector<int> xPositionFieldExit;
		static std::vector<int> yPositionFieldExit;
};

class playerInfo
{
	public:
		static int xPosition;
		static int yPosition;
};

class monsterInfo
{
	public:
		static std::vector<int> xPosition;
		static std::vector<int> yPosition;
		static int monsterAmountDesired;
		static int monsterAmountCurrent;
};

int fieldInfo::fieldLength = 10;
int fieldInfo::fieldWidth = 10;
std::vector<int> fieldInfo::xPositionFieldExit;
std::vector<int> fieldInfo::yPositionFieldExit;

int monsterInfo::monsterAmountDesired = 0;
int monsterInfo::monsterAmountCurrent = 0;
std::vector<int> monsterInfo::xPosition;
std::vector<int> monsterInfo::yPosition;

void GameRules();
void SetFieldSize();
void SetFieldExits();
void SetPlayerPosition();
void SetMonsterAmount();
void RandomizeMonsterPositions();
bool CheckForSpawnNearPlayer();
bool CheckForFieldExit( int xPos, int yPos );
bool CheckForFieldWall( int xPos, int yPos);
bool CheckForPlayerPosition( int xPos, int yPos);
bool CheckForMonsterPosition( int xPos, int yPos);
void CheckForWinCodnition();
void CheckForLoseCondition();
void DrawField();
void TurnOptions();
void TurnChoice();
void RandomMonsterMovement();
void PreventAutoExit();
bool CheckUnvaildIntegerInput( std::string input);

int main()
{
	srand( time( 0 ) );

	GameRules( );
	SetFieldSize( );
	SetFieldExits( );
	SetPlayerPosition( );
	SetMonsterAmount( );
	RandomizeMonsterPosition( );

	while( true )
	{
		DrawField( );
		CheckForWinCondition( );
		CheckForLoseCondition( );
		TurnOptions( );
		TurnChoice( );
		RandomMonsterMovement( );
	}

	return 0;
}

void GameRules( )
{
	std::cout << "Win condition: Enter the exit.\n";
	std::cout << "Lose condition: Enter the same space as a monster.\n\n";

}

void SetFieldSize( )
{
	char userChoice = 'n';
	std::cout << "Would you like to determine the playing field, [y/n]: ";
	std::cin >> userChoice;

	if( userChoice == "y" )
	{
		while(true) //def programming lol
		{
			std::string inputLength;
			std::string inputWidth;

			std::cout << std::endl;
			std::cout << "Enter the playing field length: ";
			std::cin >> inputLength;
			std::cout << "Enter the playing field width: ";
			std::cin >> inputWidth;

			if( CheckUnvaildIntegerInput( inputLength ) == true || CheckUnvaildIntegerInput( inputWidth ) == true)
			{
				fieldInfo::fieldLength = atoi( inputLength.c_str( ) );
				fieldInfo::fieldWidth = atoi( inputWidth.c_str( ) );
				break;
			}
			else
			{
				std::cout << "\nInvalid input, try again.\n";
			}
		}
	}
}

void SetFieldExits( )
{
	fieldInfo::fieldExitAmount = 1;
	fieldInfo::xPositionFieldExit.push_back( 1 );
	fieldInfo::yPositionFieldExit.push_back( 0 );
}

void SetPlayerPosition( )
{
	playerInfo::xPosition = fieldInfo::fieldWidth - 2;
	playerInfo::yPosition = fieldInfo::fieldLength - 2;
	
}

void SetMonsterAmount( )
{
	while(true)
	{
		std::string input;

		std::cout << "\nEnter amount of monsters: ";
		std::cin >> input;

		if( CheckUnvaildIntegerInput( input ) == true)
		{
			monsterInfo::monsterAmountDesired = atoi( input.c_str( ) );
			if( monsterInfo::monsterAmountDesired > ( fieldInfo::fieldLength - 2 ) * ( fieldInfo::fieldWidth - 2) - 9)
			{
				std::cout << "\nToo many monsters, try again.\n";
				continue;
			}
			
			break;

		}
		else
		{
			std::cout << "\nInvaild input, try again.\n";
		}
	}
}

void RandomizeMonsterPositions( )
{
	int xPosTemp, yPosTemp;
	for( int i = 0; i < monsterInfo::monsterAmountDesired; i++)
	{
		while(true)
		{
			xPosTemp = 1 + (rand() % (fieldInfo::fieldWidth - 2) );
			yPosTemp = 1 + (rand() % (fieldInfo::fieldLength -2) );

			if( CheckForMonsterPosition( xPosTemp, yPosTemp ) == false && CheckForSpawnNearPlayer( xPosTemp, yPosTemp ) == false ** CheckForPlayerPosition( xPosTemp, yPosTemp ) == false && CheckForFieldWall( xPosTemp, yPosTemp ) == false)
			{
				break;
			}
		}
		if( monsterInfo::monsterAmountCurrent < monsterInfo::monsterAmountDesired )
		{
			monsterInfo::monsterAmountCurrent++;
		}
		monsterInfo::xPosition.push_back( xPosTemp );
		monsterInfo::yPosition.push_back( yPosTemp );
	}
}

bool CheckForSpawnNearPlayer( int xPos, int yPos )
{
	int protectRange = 3;
	for( int yProtect = 0; yProtect < protectRange; yProtect++)
	{
		for( int xProtect = 0; xProtect < protectRange; xProtect++)
		{
			if( playerInfo::yPosition - yProtect == yPos && playerInfo::xPosition - xProtect == xPos)
			{
				return true;
			}
		}
	}
	return false;
}

bool CheckForFieldExit( int xPos, int yPos )
{
	for( int i = 0; i < fieldInfo::fieldExitAmount; i++ )
	{
		if( xPos == fieldInfo::xPositionFieldEXit[i] && yPos == fieldInfo::yPositionFieldExit[i] )
		{
			return true;
		}
	}
	return false;
}

bool CheckForFieldWall( int xPos, int yPos )
{
	if( xPos == 0 || xPos == fieldInfo::fieldWidth - 1 || yPos == 0 || yPos == fieldInfo::fieldWidth - 1 )
	{
		return true;
	}

	return false;
}

bool CheckForPlayerPosition( int xPos, int yPos )
{
	if( xPos == playerInfo::xPosition && yPos == playerInfo::yPosition )
	{
		return true;
	}

	return false;
}

bool CheckForMonsterPosition( int xPos, int yPos )
{
	for( int i = 0; i < monsterInfo::monsterAmiuntCurrent; i++)
	{
		if( xPos == monsterInfo::xPosition[i] && yPos == monsterInfo::yPosition[i] )
		{
			return true;
		}
	}

	return false;
}

void CheckForWinCondition( ) 
{
	if( CheckForFieldExit( playerInfo::xPosition, playerInfo::yPosition) == true )
	{
		std::cout << "\nYou win!";
		PreventAutoExit();
		exit( 0 );
	}
}

void CheckForLoseCondition( )
{
	if( CheckForMonsterPosition( playerInfo::xPosition, playerInfo::yPosition ) == true )
	{
		std::cout << "\nYou lose!";
		PreventAutoExit( );
		exit( 0 );
	}
}

void DrawField( )
{
	std::cout << std::endl;
	for( int yDraw = 0; yDraw < fieldInfo::fieldLength; yDraw++)
	{
		for( int xDraw = 0; xDraw < fieldInfo::fieldWidth; xDraw++)
		{
			if( CheckForFieldExit( xDraw, yDraw ) == true )
			{
				std::cout << "=";
			}
			else if( CheckForFieldWall( xDraw, yDraw ) == true )
			{
				std::cout << "#";
			}
			else if( CheckForPlayerPosition( xDraw, yDraw ) == true)
			{
				std::cout << "P";
			}
			else 
			{
				std::cout << "-";
			}
		}
		std::cout << std::endl;
	}
}

void TurnOptions( )
{
	std::cout << "\n";
	std::cout << "[1] Go up.\n";
	std::cout << "[2] Go down.\n";
	std::cout << "[3] Go left.\n";
	std::cout << "[4] Go right.\n";
	std::cout << "[5] Exit game.\n";
	std::cout << "[N/A] Do nothing.\n";
}

void TurnChoice( )
{
	char userChoice;
	int yPosTemp, xPosTemp;

	std::cout << "\nYour choice: ";
	std::cin >> userChoice;
	switch( userChoice )
	{
		case '1':
			{
				yPosTemp = playerInfo::yPosition - 1;

				if( CheckForFieldExit( playerInfo::xPosition, yTemp ) == true )
				{
					playerInfo::yPosition = yPosTemp;
				}
				else if( CheckForFieldWall( playerInfo::xPosition, yPosTemp ) == false )
				{
					playerInfo::yPosition = yPosTemp;
				}

				break;
			}

		case '2':
			{
				yPosTemp = playerInfo::yPosition + 1;

				if(CheckForFieldExit( playerInfo::xPosition, yPosTemp ) == true )
				{
					playerInfo::yPosition = yPosTemp;
				}
				else if(CheckForFieldWall( playerInfo::xPosition,yPosTemp ) == false ) 
				{
					playerInfo::yPosition = yPosTemp;
				}

				break;
			}

		case '3':
			{
				xPosTemp = playerInfo::xPosition - 1;
				if( CheckForFieldExit( xPosTemp, playerInfo::yPosition ) == true )
				{
					playerInfo::yPosition = xPosTemp;
				}
				else if( CheckForFieldWall( xPosTemp, playerInfo::yPosition ) == false )
				{
					playerInfo::xPosition = xPosTemp;
				}
				break;
			}
		case '4':
			{
				xPosTemp = playerInfo::xPosition + 1;
				if( CheckForFieldExit( xPosTemp, playerInfo::yPosition ) == true )
				{
					playerInfo::yPosition = xPosTemp;
				}
				else if( CheckForFieldWall( xPosTemp, playerInfo::yPosition ) == false )
				{
					playerInfo::xPosition = xPosTemp;
				}
				break;
			}

		case '5':
			{
				exit( 0 );
			}
		default:
			{
				break;
			}
	}
}


