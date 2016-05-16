#ifndef __MOVE_H__
#define __MOVE_H__
//Move
#include "State.h"
#include "Object_.h"

void make_around_position(int &around_x, int &around_y, int target_x, int target_y, int board[BOARD_Y][BOARD_X]);

class Move : public State{
public:
	Move(){ state = STATE::MOVE; }
	virtual void run(cocos2d::Ref* ref) = 0;
};

class MoveCharacterNoneSpace : public Move{
public:
	virtual void run(cocos2d::Ref* ref);
};

class MoveSkill : public Move{
public:
	virtual void run(cocos2d::Ref* ref);
};

class MoveDamagedEffect : public Move{
public:
	virtual void run(cocos2d::Ref* ref);
};

class MoveSkillDirect : public Move{
public:
	virtual void run(cocos2d::Ref* ref);
};

class MoveMesmerize : public Move{
public:
	virtual void run(cocos2d::Ref* ref);
};

class MoveFlyingCharacter : public Move {
public:
	virtual void run(cocos2d::Ref* ref);
};

#endif