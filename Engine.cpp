#include "Engine.h"

Engine::Engine()
	:m_wnd(nullptr)  // set the class attribute m_wnd to null
{

	if(glfwInit() == false)	// Initialize glfw and check if failed
	{
		std::cout << "Error on GLFW init" << std::endl;
		exit(-1);
	}
}

Engine::~Engine()
{
	delete m_wnd;	//delete window
	std::cout << "Terminating glfw" << std::endl;
	glfwTerminate(); // terminate the glfw lib
}

/**
	Initializes the glew lib & window 
	Starts the main loop

	@param fullscreen - does the engine start in fullscreen
*/
void Engine::start(bool fullscreen)
{
	GLenum err;
	m_wnd            = new Window(1280, 720, "PROZOR", fullscreen);		// create new window
	glewExperimental = GL_TRUE;											// without this program has a chance to crash
	err              = glewInit();										// init glew lib and check for errors

	if (err != GLEW_OK)
	{
		std::cout << "Error loading glew: " << glewGetErrorString(err) << std::endl;
		delete m_wnd;
		glfwTerminate();
		exit(-1);
	}

	glClearColor(0, 0.2f, 0.85f, 1);									//set clear color of the window

	do
	{
		glfwPollEvents();				
		update();
		render();
		
	} while (glfwWindowShouldClose(m_wnd->getWindow()) == false);		//the main loop

}

/**
	Polls events and updates everything

	@param deltaTime - time passed between frames
*/
void Engine::update(void)
{
	glfwPollEvents();													//set all event flags and check them
}

/**
	Renders everything
*/
void Engine::render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);					// clears Color buffers and depth buffers of the window
	glfwSwapBuffers(m_wnd->getWindow());								// swaps front and back buffer so we can see the new frame
}