﻿#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <windows.h>
#include <vector>
#include <string>
#include <conio.h>	
#include "Role.h"

// Declare Classes to let this file know they're exists
class Object;
class Rect;
class Tent;

// THe game status enum class
enum class GAME_STATUS 
{
	MAP, 
	COMBAT,
	BACKPACK,
	INTERACTIVE
};

// Game manager Class
class GameManager
{
private:
	//instance, Singleton pattern
	static GameManager* instance;

	// Helper functions to manage console output
	void setCameraToCurrentRole();
	void setColor(int color = 7);
	void setCursor(int y, int x);

	// Print information on the screen
	void outputInformation(std::vector<std::string>& information);

	// Functions to generate different types of information
	std::vector<std::string> normalInformation();
	std::vector<std::string> backpackInformation();
	std::vector<std::string> interactiveInformation();
	std::vector<std::string> playerInformation[3]; 

	// Array to track which players are active
	bool playerList[3] = { false };

	// Static member variables
	static std::vector<Role*> roles;
	static Role* currentRole;
	static Object* interactiveObject;

	int round; // current round

	std::vector<Tent*> observerList;
	
	// Private constructor to initialize roles
	GameManager();

public:
	// Singleton pattern
	static GameManager* getInstance();

	// Constants for camera height and width rates
	static const float CAMERA_HEIGHT_RATE;
	static const float CAMERA_WIDTH_RATE;

	// Static member variables to define map and window dimensions
	static int mapHeight;
	static int mapWidth;
	static int windowHeight;
	static int windowWidth;
	static int cameraHeight;
	static int cameraWidth;
	static int cameraX;
	static int cameraY;

	// Current game status
	static GAME_STATUS gameStatus;

	// 2D vector to represent the game board
	static std::vector<std::vector<Rect>> gameBoard;

	// Function to check if a position is valid on the game board
	static bool isPositionValid(int y, int x);

	// Getters for role and interactive object
	Role* getRole(int i);
	Role* getCurrentRole();
	Object* getInteractiveObject();

	void nextRole();

	int getRound();

	void notifyObservers();
	void addObserver(Tent* o);
	void removeObserver(Tent* o);

	// Setter for interactive object
	void setInteractiveObject(Object* o);

	// Initialize the map
	void setMap();

	// Display the battle screen
	void battleScreen(std::vector<Entity*> player, std::vector<Entity*> enemy, std::vector<std::string> list, std::vector<std::string> data);

	// Output the game board
	void outputGameBoard();
	void outputShowBoard(std::vector<std::vector<std::pair<char, int>>>& showBoard, char icon);

	// Set information based on game status
	void setInformation();

	// Set player information
	void setPlayerInformation(int playerSize , vector<Entity*>player);
	void outputPlayerBoard(std::vector<std::string>&, int);

	// Set enemy information
	void setEnemyInformation(int playerSize,vector<Entity*>enemys);
	void outputEnemyBoard(std::vector<std::string>&, int);

	// Function to check if a position is visible to the player
	bool canSee(std::pair<int, int> current, std::pair<int, int> answer, std::vector<std::vector<std::pair<char, int>>>& showBoard);
};

#endif // _GAMEMANAGER_H_
