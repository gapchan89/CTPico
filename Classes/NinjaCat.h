#ifndef __NINJACAT_H__
#define __NINJACAT_H__

#include "cocos2d.h"

using namespace cocos2d;

class NinjaCat : public CCSprite
{
private:
	bool					isClicked;
	bool					isDead;

public:
	NinjaCat(void);
	~NinjaCat(void);

	CC_SYNTHESIZE(CCPoint, _nextPosition, NextPosition);
	CC_SYNTHESIZE(CCPoint, _vector, Vector);
	CC_SYNTHESIZE(CCTouch *, _touch, Touch);

	void					setIsClicked(bool click);
	bool					returnIsClicked();
	void					setIsDead(bool click);
	bool					returnIsDead();

	static NinjaCat*		gameSpriteWithFile(const char* filename);
	virtual void 			setPosition(const CCPoint& pos);

};

#endif // __NINJACAT_H__
