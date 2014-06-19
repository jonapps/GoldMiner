/*
 * World.cpp
 *
 *  Created on: 02.06.2014
 *      Author: Chris
 */

#include "World.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

World::World(SpriteManager* spriteManager) :
		sprite_manager_(spriteManager), player_(
				new Player(
						sprite_manager_->getSprite("assets/graphics/mario.ppm"),
						Vec2(0, 0), Vec2(1280.0 / 18, 720.0 / 11))), map_(
				new vector<Block*>()) {
	cout << "readmap" << endl;
	this->readMap("map.txt");
}

World::~World() {
//	size_t i = 0;
//	for(auto block : this->map){
//		delete block;
//		cout << i++ << endl;
//	}
	delete player_;
}

void World::onKeyDown(int key) {

}

void World::onKeyUp(int key) {

}

void World::testCollision() {

	Block* left, *right, *top, *bottom;
	left = right = top = bottom = nullptr;

	for (Block* block : *map_) {

		double bx, by, bw, bh, px, py, pw, ph;
		bx = block->getPosition().getX();
		by = block->getPosition().getY();
		bw = block->getDimension().getX();
		bh = block->getDimension().getY();
		px = this->player_->getDestination().getX();
		py = this->player_->getDestination().getY();
		pw = this->player_->getDimension().getX();
		ph = this->player_->getDimension().getY();
		//-----UNTEN-----

		py -= 5;
		if (by + bh >= py && py > by) {

			if ((bx <= px && px <= bx + bw) || (bx >= px && px + pw >= bx)) {

				bottom = block;
			}
		}
		//-----LINKS-----
		py += 5;
		px -= 5;

		if (bx + bw >= px && bx <= px) {
			if ((by <= py && py <= by + bh) || (by >= py && py + ph >= by)) {

				left = block;
			}
		}
		//-----RECHTS-----
		px += 10;
		if (bx <= px + pw && bx > px) {
			if ((by <= py && py <= by + bh) || (by >= py && py + ph >= by)) {

				right = block;
			}
		}
		if (bottom) {
			top = block;
		}
	}

	this->player_->setNearestBlocks(top, left, right, bottom);
}

void World::readMap(string fileName) {
	ifstream quelle(fileName);
	int rowCount = 0;

	if (!quelle) {
		cerr << "map.txt kann nicht ge�ffnet werden!\n";
	}
	char ch[17];
	for (int i = 0; i < 16; i++) {
		ch[i] = ' ';
	}
	while (quelle.getline(ch, sizeof(ch))) {
		for (int i = 0; i < 16; i++) {
			if (ch[i] == 'x') {
				//TODO block h�he und breite benutzen
				Block* block = new Block(Block::dirt,
						Vec2((1280.0 / 16) * i, 640 - (720.0 / 9) * rowCount),
						sprite_manager_->getSprite("assets/graphics/dirt.ppm"));
				map_->push_back(block);
				cout << "new Ground " << (1280.0 / 16) * i << " ,"
						<< (720.0 / 9) * rowCount << endl;
			}
			if (ch[i] == 'g') {
				//TODO block h�he und breite benutzen
				Block* block = new Block(Block::dirt,
						Vec2((1280.0 / 16) * i, 640 - (720.0 / 9) * rowCount),
						sprite_manager_->getSprite("assets/graphics/gold.ppm"));
				map_->push_back(block);
				cout << "new Ground " << (1280.0 / 16) * i << " ,"
						<< (720.0 / 9) * rowCount << endl;
			}
			if (ch[i] == 's') {
				player_->setPosition(
						Vec2((1280.0 / 16) * i, 640 - (720.0 / 9) * rowCount));
				cout << "Player Pos " << 20 * i << " " << 20 * rowCount << endl;
			}
			ch[i] = ' ';
		}
		rowCount++;
	}
	cout << "rowcount:" << rowCount << endl;
}

void World::testBlockLife() {
//	for(unsigned int i=0; i<map.size(); i++)    {
//		if(map.at(i).getHp()<=0) {
//			map.erase(map.begin() + i);
//		}
//	}
}

void World::tick() {
	this->testCollision();
	vector<Block*>::iterator iter = map_->begin();
	while(iter != map_->end()){
		if((*iter)->isDestroyed()){
			map_->erase(iter++);
		}
	}

	player_->tick();
}

void World::draw() {

//cout << "draw blocks("<< map->size()<< ")" << endl;
	for (auto block : *map_) {
		block->draw();
	}

//cout << "draw player" << endl;
	player_->draw();
}
