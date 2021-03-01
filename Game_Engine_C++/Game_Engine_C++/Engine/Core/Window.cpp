#include "Window.h"

Window::Window() // Another way - : window(nullptr), context(nullptr)
{
	// Sets default value for width, height, window and context

	width = 0;
	height = 0;
	window = nullptr;
	context = nullptr;
}

Window::~Window()
{
	OnDestroy();
}

bool Window::OnCreate(std::string name_, int width_, int height_)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) // initialize SDL
	{
		std::cout << "Failed to initialize SDL" << std::endl;
		return false; // if it doesn't work don't attempt to create the window
	}

	//this->width = width_;
	//this->height = height_;

	// saves width and height of window if the window is created
	width = width_;
	height = height_;

	SetPreAttributes();

	//call to create the sdl window
	window = SDL_CreateWindow(name_.c_str(), // 1st paramater - name of window
		SDL_WINDOWPOS_CENTERED, // sets window to center of screen on x 
		SDL_WINDOWPOS_CENTERED, // sets window to center of screen on y
		width, // 2nd param sets width of window
		height, // 3rd param sets height of window
		SDL_WINDOW_OPENGL); // flags to set - tells sdl that it will be creating a window but will be expecting any form of opengl rendering to happen

	if (!window) // see if variable equals nullptr
	{
		std::cout << "Failed to create window" << std::endl;
		return false;
	}

	// creates opengl context so opengl can be used in our engine
	context = SDL_GL_CreateContext(window);
	SetPostAttributes();

	GLenum error = glewInit(); // initializes glew - glew is the library being used for any opengl calls
	if (error != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return false;
	}
	
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	glViewport(0, 0, width, height);
	
	return true;
}

void Window::OnDestroy()
{
	SDL_GL_DeleteContext(context); // closing the door to the graphics card
	SDL_DestroyWindow(window); // ensure that memory is been cleaned up properly
	window = nullptr; // call the sdl delete if the pointer is of type sdl then set to nullptr
}

// Gets window width
int Window::GetWidth() const
{
	return width;
}

// Gets window height
int Window::GetHeight() const
{
	return height;
}

// Gets window
SDL_Window* Window::GetWindow() const
{
	return window;
}

// Happens before the window is created 
void Window::SetPreAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // get rid of depracated functions
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Enables double buffering 
	SDL_GL_SetSwapInterval(1); // Set swap interval to be equal and synchronized with the vertical retrace of screen - Ask Shak about this..
	glewExperimental = GL_TRUE; // Allows the program to be able error track experimental gpu extensions - Ask Shak about
}

// Happens after the window is created 
void Window::SetPostAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32); // Sets depth buffer size to 32 bits - ask Shak about
}
