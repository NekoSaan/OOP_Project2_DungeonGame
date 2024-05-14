#include "Items.h"
#include "Role.h"

std::vector<std::string> ItemList = {
	// Consumables
	"Godsbeard",
	"GoldenRoot",
	"TeleportScroll",
	"Tent",

	// Equipments, non-stackable
	"WoodenSword",
	"Hammer",
	"MagicWand",
	"Shoes",
	"PlateArmor",
	"Bracelet"
};

Item::Item(std::string tag, ITEMID id) : tag(tag), id(id), itemName(ItemList[(int)id]), amount(1) {};

Item::~Item(void) {

	itemName = "";
	des = "";
	id = ITEMID::Invalid;
	amount = NULL;
}

int Item::getId(void) {
	return (int)id;
}

int Item::getAmount(void) {
	return amount;
}

void Item::incAmount(void) {
	amount++;
}

void Item::decAmount(void) {
	amount--;
}

std::string Item::getTag(void) {
	return tag;
}

std::string Item::getName(void) {
	return itemName;
}

void Item::use(Role* role) {
	switch (id) {
	case ITEMID::Godsbeard:
		// role->gainHealth(25);
		break;
	case ITEMID::GoldenRoot:
		// role->gainFocus(3);
		break;
	case ITEMID::TeleportScroll:
		// teleportScene();
		break;
	case ITEMID::Tent:
		// placeTentScene();
		break;
	default:
		// nothing happend, invalid id
		break;
	}

	// others using overwrite method to action
}