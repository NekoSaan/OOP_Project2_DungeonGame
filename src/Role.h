#pragma once
#include "Entity.h"
#include "Object.h"
#include <vector>

class Object;
class Entity;

class Role : public Entity, public Object {
public:
	Role() : Entity() {
		srand(time(0));  // 初始化隨機種子
		setVitality(rand() % 15 + 30);  // [30, 45) 的隨機數
		setFocus(3);  // 專注力固定為 3
		setSpeed(rand() % 25 + 30);  // [30, 55) 的隨機數
		setHitRate(rand() % 20 + 40);  // [40, 60) 的隨機數
		setPAttack(rand() % 11 + 5);  // [5, 15] 的隨機數
		setMAttack(rand() % 11 + 5);  // [5, 15] 的隨機數
		setPDefense(rand() % 21);  // [0, 20] 的隨機數
		setMDefense(rand() % 21);  // [0, 20] 的隨機數
	}

	void move(int y, int x);

	//Object's virtual funtion
	void active(Role* role);
	void chooseActiveUP();
	void chooseActiveDown();
	vector<string> getAllChoose();
	int getChosenIndex();
};

