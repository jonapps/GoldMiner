/*
 * InputManager.h
 *
 *  Created on: 08.06.2014
 *      Author: Jonas
 */

#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include <tr1/unordered_map>
#include <vector>
#include "Game.h"

class MouseListener{
public:
	virtual ~MouseListener(){};
	virtual void onMouseMove(float x, float y, float dx, float dy);
	virtual void onButtonUp(int button);
	virtual void onButtonDown(int button);
	virtual void onScroll(double x_offset, double y_offset);
};

class KeyListener{
public:
	virtual ~KeyListener(){};
	virtual void onKeyUp(int key);
	virtual void onKeyDown(int key);
};

class InputManager {
public:

    static InputManager& getInstance();
	static void onMouseMove(GLFWwindow *window, double x, double y);
	static void onKey(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void onButton(GLFWwindow *window, int button, int action, int mods);
	static void onScroll(GLFWwindow *window, double x_offset, double y_offset);

    void onMouseMoveImpl(GLFWwindow *window, double x, double y);
	void onKeyImpl(GLFWwindow *window, int key, int scancode, int action, int mods);
	void onButtonImpl(GLFWwindow *window, int button, int action, int mods);
	void onScrollImpl(GLFWwindow *window, double x_offset, double y_offset);

	void addMouseMoveListener(KeyListener listener);
	void addKeyListener(KeyListener listener);
	bool isKeyDown(int key);
	bool isButtonDown(int button);

private:
    std::tr1::unordered_map<int, bool> keys_;
    std::tr1::unordered_map<int, bool> mouse_buttons_;

    std::vector<MouseListener*> mouse_listeners_;
    std::vector<KeyListener*> key_listeners_;


    InputManager(){}

    InputManager(InputManager const&);
    void operator=(InputManager const&);
};

#endif /* INPUTMANAGER_H_ */
