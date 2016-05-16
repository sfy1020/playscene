#include "SoundClass.h"

SoundClass::SoundClass(){
}

void SoundClass::init(){
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

	std::ifstream soundDB;
	int id=0;
	std::string filename="";
	std::string msg="";
	soundDB.open("soundData\\soundDB.txt");
	std::getline(soundDB, filename);	//¸Ç À­ÁÙ Á¦°Å
	while(1){
		soundDB>>msg;
		if(soundDB.eof())break;
		if(msg == "SOUND_EFFECT"){
			soundDB>>id>>filename;
			filename = "soundData\\"+filename+".wav";
			DBdata.emplace(id, SoundDBdata(id,filename,SOUND_EFFECT));
			audio->preloadBackgroundMusic(filename.c_str());

		}else if(msg == "SOUND_BGM"){
			soundDB>>id>>filename;
			filename = "soundData\\"+filename+".wav";
			DBdata.emplace(id, SoundDBdata(id, filename, SOUND_BGM));
			//audio->preloadEffect(filename.c_str());	//????????????????????????????????????????????????????
		}
	}
	soundDB.close();

}

SoundClass::~SoundClass(){
}

void SoundClass::run(int id){
	auto Find = DBdata.find(id);
	if(Find == DBdata.end()){
		EXCEPTION2("SoundDBdata is not in hash",id);
		return;
	}

	std::string filename = Find->second.filename;
	int msg = Find->second.msg;

	if(msg == SOUND_EFFECT){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(filename.c_str());
	}else if(msg == SOUND_BGM){
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(filename.c_str(), true);
	}
}


