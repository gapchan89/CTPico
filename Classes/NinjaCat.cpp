#include "NinjaCat.h"
//#include "SimpleAudioEngine.h"

using namespace cocos2d;
//using namespace CocosDenshion;


NinjaCat::NinjaCat(void)
{
	isClicked = false;
	isDead = false;
	_vector = ccp(0,0);
}

NinjaCat::~NinjaCat(void)
{

}

void NinjaCat::setIsClicked(bool click) {
	isClicked = click;
}
bool NinjaCat::returnIsClicked() {
	return isClicked;
}

void NinjaCat::setIsDead(bool dead) {
	isDead = dead;
}
bool NinjaCat::returnIsDead() {
	return isDead;
}

NinjaCat* NinjaCat::gameSpriteWithFile(const char* filename)
{
	NinjaCat *cat = new NinjaCat();

	if( cat && cat->initWithFile(filename))
	{
		cat->autorelease();
		return cat;
	}

	CC_SAFE_DELETE(cat);
	return NULL;
}

void NinjaCat::setPosition(const CCPoint& pos) {
	CCSprite::setPosition(pos);
	if (!_nextPosition.equals(pos)) {
		_nextPosition = pos;
	}
}
