#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <string>
#include <iostream>

class Window
{
public:
	Window();
	~Window();
	bool OnCreate(std::string name_, int width_, int height_);
	void OnDestroy();

	//Gets the window and the hight and width of the window
	int GetWidth() const;
	int GetHeight() const;
	SDL_Window* GetWindow() const;

private:
	//Sets attributes needed before the window is opened
	void SetPreAttributes();

	//Sets attributes needed after the window is opened
	void SetPostAttributes();

	//stores the width and height
	int width;
	int height;

	//Actual Pointer to the sdl window
	SDL_Window* window;

	//Allows you to communicate with the graphics card via opengl and sdl
	SDL_GLContext context;

};

#endif // !WINDOW_H

