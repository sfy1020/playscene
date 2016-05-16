#ifndef __SOUNDCLASS_H__
#define __SOUNDCLASS_H__
#include "constant.h"
#include "cocos2d.h"
#include "audio\include\SimpleAudioEngine.h"
#include <fstream>
#include <queue>
#include <utility>
class SoundClass{
private:
	enum{SOUND_EFFECT = 1, SOUND_BGM = 2};
	std::map<int,SoundDBdata> DBdata;

public:			//constructor & destructor
	SoundClass();
	~SoundClass();

public:
	void run(int id);
	void init();
};
#endif
