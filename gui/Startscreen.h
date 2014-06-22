/*
 * Startscreen.h
 *
 *  Created on: 20.06.2014
 *      Author: Chris
 */

#ifndef STARTSCREEN_H_
#define STARTSCREEN_H_

#include "../gui/io/InputManager.h"
#include "../objects/Entity.h"
#include "Button.h"
#include "SpriteManager.h"
#include "Font.h"
#include "Screen.h"
#include <vector>

class Startscreen : public Screen{
public:
	enum button{
		levelOneButton = 0,
		levelTwoButton = 1,
		highScoreButton = 2,
		exitButton = 3,
	};

	Startscreen(SpriteManager* spriteManager, bool enable);
	~Startscreen();

	Button* getButton(int id);

	virtual void tick();
	virtual void draw() const;

private:
	Sprite* bg_;
	std::vector<Button*> buttons_;
	Font* font_;

};


#endif /* STARTSCREEN_H_ */
