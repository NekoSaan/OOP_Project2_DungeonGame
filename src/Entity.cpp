﻿#include "Entity.h"
#include "Dice.h"
#include "Weapon.h"
#include "Armor.h"
#include "Accessory.h"
#include <conio.h>
#include <algorithm>

// Intent: Construct an Entity object
// Pre: None
// Post: Constructs an Entity object with random attribute values within
//		 specified ranges, initializes focus, and creates a default weapon
Entity::Entity(void)
{
	setVitality(rand() % 15 + 30);  // random value between [30, 45)
	setMaxFocus(3);					// initialize to 3, fixed
	setFocus(3);					// initialize to 3, fixed
	setSpeed(rand() % 25 + 30);		// random value between [30, 55)
	setHitRate(rand() % 20 + 40);	// random value between [40, 60)
	setPAttack(rand() % 11 + 5);	// random value between [5, 15]
	setMAttack(rand() % 11 + 5);	// random value between [5, 15]
	setPDefense(rand() % 21);		// random value between [0, 20]
	setMDefense(rand() % 21);		// random value between [0, 20]
	setHp(getVitality());
	actions = 0;
	name = "";
	sort = " ";
}

// Intent: Set the vitality of the entity
// Pre: newVitality must be a non-negative integer
// Post: Sets the vitality of the entity to the specified value
void Entity::setVitality(int newVitality) 
{
	vitality = newVitality; 
}

// Intent: Set the maximum focus of the entity
// Pre: newFocus must be a non-negative integer
// Post: Sets the maximum focus of the entity to the specified value
void Entity::setMaxFocus(int newFocus) 
{
	maxFocus = newFocus;
}

// Intent: Set the speed of the entity
// Pre: newSpeed must be a non-negative integer
// Post: Sets the speed of the entity to the specified value
void Entity::setSpeed(int newSpeed) 
{
	speed = newSpeed; 
}

// Intent: Set the hit rate of the entity
// Pre: newHitRate must be a non-negative integer
// Post: Sets the hit rate of the entity to the specified value
void Entity::setHitRate(int newHitRate)
{
	hitRate = newHitRate; 
}

// Intent: Set the physical attack of the entity
// Pre: newPAttack must be a non-negative integer
// Post: Sets the physical attack of the entity to the specified value
void Entity::setPAttack(int newPAttack) 
{
	pAttack = newPAttack; 
}

// Intent: Set the magical attack of the entity
// Pre: newMAttack must be a non-negative integer
// Post: Sets the magical attack of the entity to the specified value
void Entity::setMAttack(int newMAttack)
{
	mAttack = newMAttack; 
}

// Intent: Set the physical defense of the entity
// Pre: newPDefense must be a non-negative integer
// Post: Sets the physical defense of the entity to the specified value
void Entity::setPDefense(int newPDefense) 
{
	pDefense = newPDefense; 
}

// Intent: Set the magical defense of the entity
// Pre: newMDefense must be a non-negative integer
// Post: Sets the magical defense of the entity to the specified value
void Entity::setMDefense(int newMDefense) 
{
	mDefense = newMDefense; 
}

// Intent: Set the current focus of the entity
// Pre: newFocus must be a non-negative integer
// Post: Sets the current focus of the entity to the specified value
void Entity::setFocus(int newFocus) 
{
	focus = newFocus; 
}

// Intent: Set the current hit points of the entity
// Pre: newHp must be a non-negative integer
// Post: Sets the current hit points of the entity to the specified value
void Entity::setHp(int newHp) 
{ 
	hp = min(newHp,getVitality()); 
}

// Intent: Search for a specific buff in the entity's buffs
// Pre: None
// Post: Returns true if the entity has the specified buff; otherwise, returns false
bool Entity::searchBuff(std::string Buff)
{
	std::vector<std::string>::iterator it = std::find(buff.begin(), buff.end(), Buff);

	return it != buff.end();
}

// Intent: Give a buff to the entity
// Pre: None
// Post: Adds the specified buff to the entity's buffs with the specified duration
void Entity::giveBuff(std::string Buff, int BuffTime)
{
	std::vector<std::string>::iterator it = std::find(buff.begin(), buff.end(), Buff);

	if (it != buff.end()) 
	{
		buffTime[it - buff.begin()] = BuffTime;
		
	}
	else 
	{
		buff.push_back(Buff);
		buffTime.push_back(BuffTime);
	}
}

// Intent: Decrease the duration of active buffs and remove expired buffs
// Pre: None
// Post: Decreases the duration of active buffs and removes buffs with expired durations
void  Entity::minusBuff()
{
	for (int i = 0; i < buffTime.size(); i++) 
	{
		buffTime[i]--;

		if (buffTime[i] < 0) 
		{
			removeBuff(buff[i]);
		}
	}
}

// Intent: Remove a specific buff from the entity
// Pre: None
// Post: Removes the specified buff from the entity's buffs
void Entity::removeBuff(std::string Buff)
{
	std::vector<std::string>::iterator it = std::find(buff.begin(), buff.end(), Buff);
	int index = std::distance(buff.begin(), it);
	buff.erase(it);
	buffTime.erase(buffTime.begin() + index);
}

// Intent: Get the current vitality of the entity
// Pre: None
// Post: Returns the current vitality of the entity
int Entity::getVitality()
{
	return vitality;
}

// Intent: Get the maximum focus of the entity
// Pre: None
// Post: Returns the maximum focus of the entity
int Entity::getMaxFocus()
{
	return maxFocus + acc->getMaxFocus();
}


// Intent: Get the effective speed of the entity, considering buffs and equipped weapon
// Pre: None
// Post: Returns the effective speed of the entity
int Entity::getSpeed() 
{
	int Speed = speed + armor->getSpeed() + acc->getSpeed();

	if (searchBuff("SpeedUp")) 
	{
		Speed *= 1.5;
	}

	return std::min(100, Speed);
}

// Intent: Get the effective hit rate of the entity, considering buffs
// Pre: None
// Post: Returns the effective hit rate of the entity
int Entity::getHitRate() 
{ 
	int HitRate = hitRate + weapon->getHitRate() - (searchBuff("Angry") ? 30 : 0);

	return std::min(100, HitRate);
}

// Intent: Get the effective physical attack of the entity, considering equipped weapon
// Pre: None
// Post: Returns the effective physical attack of the entity
int Entity::getPAttack() 
{
	return std::min(100, pAttack + weapon->getPAttack());
}

// Intent: Get the effective magical attack of the entity, considering equipped weapon
// Pre: None
// Post: Returns the effective magical attack of the entity
int Entity::getMAttack() 
{
	return std::min(100, mAttack + weapon->getMAttack());
}

// Intent: Get the effective physical defense of the entity, considering equipped weapon
// Pre: None
// Post: Returns the effective physical defense of the entity
int Entity::getPDefense() 
{
	return std::min(100, pDefense + armor->getPDefense());
}

// Intent: Get the effective magical defense of the entity, considering equipped weapon
// Pre: None
// Post: Returns the effective magical defense of the entity
int Entity::getMDefense() 
{
	int MDefense = mDefense + armor->getMDefense() + acc->getMDefense();

	return std::min(100, mDefense);
}

// Intent: Get the current focus of the entity
// Pre: None
// Post: Returns the current focus of the entity
int Entity::getFocus() 
{
	return focus; // current focus
}

// Intent: Get the current hit points of the entity
// Pre: None
// Post: Returns the current hit points of the entity
int Entity::getHp() 
{
	return hp; // current health
}

// Intent: Select an action for the entity based on user input
// Pre: role and enemy must be non-empty vectors of Entity pointers
// Post: Selects an action for the entity based on user input
int Entity::selectAction(std::vector<Entity*> role, std::vector<Entity*> enemy) 
{
	char c = _getch();

	if (c == '0') 
	{
		normalAttack(role, enemy);
	}
	else if (c == '1') 
	{
		skillAttack(role, enemy);
	}
	else if (c == '3') 
	{
		return 1;
	}

	return 0;
}

// Intent: Perform a normal attack against an enemy entity
// Pre: role and enemy must be non-empty vectors of Entity pointers
// Post: Performs a normal attack against an enemy entity
void Entity::normalAttack(std::vector<Entity* > role, std::vector<Entity* > enemy) {};

// Intent: Perform a skill attack against an enemy entity
// Pre: role and enemy must be non-empty vectors of Entity pointers
// Post: Performs a skill attack against an enemy entity
void Entity::skillAttack(std::vector<Entity* > role, std::vector<Entity* > enemy) {};

// Intent: Check if the entity has a specific passive skill
// Pre: passiveSkill must be a valid string
// Post: Returns true if the passive skill matches any equipped item, false otherwise
bool Entity::getPassiveSkill(std::string passiveSkill) {
	return (passiveSkill == weapon->getPassiveSkill() ||
			passiveSkill == armor->getPassiveSkill()  ||
			passiveSkill == acc->getPassiveSkill());
}

// Intent: Get the name of the entity
// Pre: None
// Post: Returns the name of the entity
string Entity::getName() {
	return name;
}

// Intent: Set the name of the entity
// Pre: Name must be a valid string
// Post: Updates the name of the entity
void Entity::setName(string Name) {
	name = Name;
}