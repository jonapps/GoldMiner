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
#include <GLFW/glfw3.h>
#include "MouseListener.h"
#include "KeyListener.h"

class InputManager {
public:

    static InputManager& getInstance();
	static void onMouseMove(GLFWwindow *window, double x, double y);
	static void onKey(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void onButton(GLFWwindow *window, int button, int action, int mods);
	static void onScroll(GLFWwindow *window, double x_offset, double y_offset);
	static void onResize(GLFWwindow * window, int width, int height);


    void onMouseMoveImpl(GLFWwindow *window, double x, double y);
	void onKeyImpl(GLFWwindow *window, int key, int scancode, int action, int mods);
	void onButtonImpl(GLFWwindow *window, int button, int action, int mods);
	void onScrollImpl(GLFWwindow *window, double x_offset, double y_offset);
	void onResizeImpl(GLFWwindow * window, int width, int height);

	void addMouseListener(MouseListener* listener);
	void addKeyListener(KeyListener* listener);
	bool isKeyDown(int key);
	bool isButtonDown(int button);

	InputManager(InputManager const&);
	void operator=(InputManager const&);

private:
	InputManager();
    std::tr1::unordered_map<int, bool> keys_;
    std::tr1::unordered_map<int, bool> mouse_buttons_;

    std::vector<MouseListener*> mouse_listeners_;
    std::vector<KeyListener*> key_listeners_;

    double last_x = 0;
	double last_y = 0;


};

#endif /* INPUTMANAGER_H_ */
