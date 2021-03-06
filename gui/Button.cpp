/*
 * Button.cpp
 *
 *  Created on: 21.06.2014
 *      Author: Jonas
 */

#include "Button.h"
#include "io/InputManager.h"
#include <iostream>
#include <sstream>

using namespace std;

Button::Button(unsigned int id, Sprite* sprite, Vec2 position, Vec2 dimension):
	Entity(sprite, position, dimension),
	id_(id),
	is_hovered_(false),
	handler_(nullptr),
	font_(nullptr),
	text_("Button"),
	visible_(false){
	InputManager::getInstance().addMouseListener(this);
	stringstream but_text;
	but_text << "Button" << id;
	text_ = but_text.str();
}

Button::~Button(){

}
void Button::onMouseMove(Vec2 screen_pos, Vec2 delta){
	bool x = screen_pos.getX() > position_.getX() && screen_pos.getX() < position_.getX() + dimension_.getX();
	bool y = screen_pos.getY() > position_.getY() && screen_pos.getY() < position_.getY() + dimension_.getY();
	is_hovered_ = x && y;


}
void Button::onButtonUp(int button, Vec2 screen_pos){

}
bool Button::onButtonDown(int button , Vec2 screen_pos){

	if(visible_){
		bool x = screen_pos.getX() > position_.getX() && screen_pos.getX() < position_.getX() + dimension_.getX();
		bool y = screen_pos.getY() > position_.getY() && screen_pos.getY() < position_.getY() + dimension_.getY();
		if(x && y && handler_ != nullptr){
			handler_->onButtonClick(id_);
			return true;
		}
	}
	return false;
}


void Button::onScroll(Vec2 offset){

}

void Button::setVisible(bool b){
	visible_ = b;
}

void Button::draw(){
	if(visible_){
		sprite_->draw(position_,dimension_,is_hovered_ ? Vec2(0.5,0) : Vec2(0,0), is_hovered_ ? Vec2(1,1) : Vec2(0.5,1));
		if(font_ != nullptr){
			Vec2 text_dim = font_->computeDimension(text_);
			float x = position_.getX() + (dimension_.getX() - text_dim.getX())/2.0;
			float y = position_.getY() + (dimension_.getY() - text_dim.getY())/2.0;
			font_->draw_text(Vec2(x,y),text_);
		}
	}
}

void Button::setHandler(ButtonHandler* handler){
	handler_ = handler;
}

void Button::setFont(Font* font){
	font_ = font;
}
void Button::setText(std::string text){
	text_ = text;
}
