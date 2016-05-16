#include "AppDelegate.h"
#include "PlayScene.h"
#include "LoginScene.h"
#include "LoadingScene.h"
#include "RecordScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLViewImpl::createWithRect("Pokemon Defence", Rect(0, 0, SIZE_OF_GLWIN_WIDTH, SIZE_OF_GLWIN_HEIGHT));
        director->setOpenGLView(glview);
    }

	director->getOpenGLView()->setDesignResolutionSize(SIZE_OF_GLWIN_WIDTH, SIZE_OF_GLWIN_HEIGHT, ResolutionPolicy::SHOW_ALL);
	Object_::graphic.init();	//graphicDB 持失
	Object_::sound.init();		//soundDB 持失

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    FileUtils::getInstance()->addSearchPath("res");

    // create a scene. it's an autorelease object
    auto playscene = PlayScene::createScene();		//Scene 持失
	auto loginscene = LoginScene::createScene();
	auto loadingscene = LoadingScene::createScene();
	//auto recordscene = RecordScene::createScene();
	
	TransitionScene* play = TransitionFade::create(2.0f, playscene, Color3B::WHITE);
	//TransitionScene* record = TransitionFade::create(1.0f, recordscene, Color3B::WHITE);
	TransitionScene* login = TransitionJumpZoom::create(2.0f, loginscene);
	//director->pushScene(record);
	director->pushScene(play);
	director->pushScene(loadingscene);
	director->pushScene(login);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

