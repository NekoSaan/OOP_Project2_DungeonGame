#ifndef _ARMOR_H_
#define _ARMOR_H_
#include "Items.h"

// Armor Class, inherti Item Class
class Armor : public Item{
private:
	int vitality;		// hp
	int speed;			// speed
	int pDefense;		// physical defense
	int mDefense;		// magical defense
	char type;			// type of equipment
	std::string passiveSkill = "NULL";	

public:
	// Default Constructor
	Armor(std::string, ITEMID);

	// Getter
	int getVitality(void); 
	int getSpeed(void);
	int getPDefense(void);
	int getMDefense(void);
	char getType(void);
	std::string getPassiveSkill(void);

	// equip the armor
	void use(Role*) override;
};

#endif // _ARMOR_H_
