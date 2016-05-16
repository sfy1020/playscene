#ifndef __OBJECT_H__
#define __OBJECT_H__
#include "constant.h"
#include "GraphicClass.h"
#include "SoundClass.h"
#include "DBClass.h"
#include "cocos2d.h"
#include "State.h"
#include <queue>
#include <vector>
#include <map>
#include <unordered_map>

class Object_ : public cocos2d::Ref{				//autorelease를 위한 Ref상속
public:		//static value
	static std::map<int, Object_*> all;		//공유 데이터
	static int board[BOARD_Y][BOARD_X];
	static std::queue<Message> mainQ;
	static GraphicClass graphic;
	static SoundClass sound;
	static cocos2d::Layer *objectLayer;
	static DBClass DBmanager;

protected:	//value
	std::queue<STATE> message;
	std::vector<std::shared_ptr<State> > stateMachine;	//모든 행위를 갖는다.
	int id;								//변수
	STATE state;						//내부 변수
	int time_slice_cnt;
	int sleep_time;
	bool started;
	int DB_ID;							//DB
	std::string name;
	int imgID;
	cocos2d::Sprite* sprite;

public:		//constructor
	Object_();
	virtual ~Object_();
	Object_(const ObjectDBdata& data, int id);

public:		//virtual method
	virtual void run();
	virtual void base()				=	0;
	virtual bool skipTimeSlice();

public:		//own method
	void initMessage(STATE msg);
	STATE popMessage();
	bool isMessageEmpty();

public:		//getter & setter
	const int& get_id() const;
	const std::string& get_name() const;
	const int& get_DB_ID() const;
	const STATE& get_state() const;
	const int& get_time_slice_cnt() const;
	const int& get_sleep_time() const;
	const bool& get_started() const;
	const int& get_imgID() const;
	cocos2d::Sprite*& get_sprite();

	void set_id(const int& id);
	void set_name(const std::string& name);
	void set_DB_ID(const int& DB_ID);
	void set_state(const STATE& state);
	void set_time_slice_cnt(const int& time_slice_cnt);
	void set_sleep_time(const int& sleep_time);
	void set_started(const bool& started);
	void set_imgID(const int& imgID);
};


#endif