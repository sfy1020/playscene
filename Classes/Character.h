#ifndef __CHARARCTER_H__
#define __CHARARCTER_H__

#include "constant.h"
#include "Unit.h"
#include <vector>
#include <utility>

class Character : public Unit{
public:
	std::vector<std::pair<int, int>> path;
	int after_x;
	int after_y;
protected:				//value
	int gold;			//DB
	int move_frame;
	int move_imgID;
	int move_soundID;

public:					//constructor & destructor
	Character();
	virtual ~Character();
	Character(const CharacterDBdata& data, int id, int x, int y, DIRECTION direction, int targetID);

public:					//virtual method
	virtual void base()					=	0;
	virtual void levelUp();

public:					//own method
	
public:					//getter & setter
	const int& get_gold() const;
	const int& get_move_frame() const;
	const int& get_move_imgID() const;
	const int& get_move_soundID() const;

	void set_gold(const int& gold);
	void set_move_frame(const int& move_frame);
	void set_move_imgID(const int& move_imgID);
	void set_move_soundID(const int& move_soundID);
};

#endif