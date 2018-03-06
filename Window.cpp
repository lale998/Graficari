#include "Window.h"

Window::Window(const int width, const int height, const std::string& title,bool fullscreen)
	:m_width(width),
	 m_height(height),
	 m_fullsc(fullscreen)															 //sets the attributes m_width,m_height and m_fullsc to their values
{
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);									 //gives OpenGL hints about which version to use , we use 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	m_window = glfwCreateWindow(m_width, m_height, title.c_str(), nullptr, nullptr); // create new window with width,height and title

	if(!m_window)																	 //checks if new window is created ok
	{
		std::cout << "Failed on window create" << std::endl;
		exit(-1);
	}

	glfwSetWindowUserPointer(m_window, this);					//sets the window object as the internal object of this glfw window
	glfwSetWindowSizeCallback(m_window, resizeCallback);        //sets the resizeCallback function as the function which gets called when any window gets resized
	glfwSetKeyCallback(m_window, key_callback);					//sets the key_callback   function as the function which gets called when any key is pressed while the window is focused

	glfwMakeContextCurrent(m_window);							//makes this window the current context (opengl renders to it)
	glfwSwapInterval(0);										//enables vsync

	if (fullscreen)
	{
		setFullScreen(fullscreen);								//if fullscreen is requested sets the window to fullscreen
	}

}

/**
    Sets the window to fullscreen

	@param fullscreen - is the window fullscreen
*/
void Window::setFullScreen(bool fullscreen)
{
	m_fullsc = fullscreen;					

	if (fullscreen)
	{
		int				   mon_count   = -1;													//we get the video mode and the monitor so we can set the window monitor to fullscreen
		const GLFWvidmode  *mode       = glfwGetVideoMode(glfwGetPrimaryMonitor());
		GLFWmonitor		   **mon_list  = glfwGetMonitors(&mon_count);

		glfwGetWindowPos(m_window, &m_initPosX, &m_initPosY);									// we must save the initial window position so it doesnt look all wierd once we exit the fullscreen
		glfwSetWindowMonitor(m_window, mon_list[0], 0, 0, mode->width, mode->height, 0);		//sets the new monitor to mode dimensions (sets fullscreen)
	}
	else
	{
		glfwSetWindowMonitor(m_window, nullptr, m_initPosX, m_initPosY, m_width, m_height, 0);  // reverts the window back to its pre fullscreen state
	}

	resize(0, 0);																				// calls resize to set the viewport
}

/**
	Handles resizing of the window, also handles fullscreen resize

	@param cx - x coordinate of the window center
	@param cy - y coordinate of the window center
*/
void Window::resize(int cx, int cy)
{
	int w, h;									//we must use temporary width & height variables
	glfwGetFramebufferSize(m_window, &w, &h);	//get the new window size
	glViewport(cx, cy, w, h);					//tell opengl to render to the whole thing

	if (!m_fullsc)								//fullscreen also counts as a resize callback so we need to check
	{
		m_width = w;							//we only change the local width & height if it is not a fullscreen callback
		m_height = h;
	}
}

/**
	Callback for resizing the window.
	Catches which window is resized and calls its resize method.

	@param window - window that was resized
	@param cx     - x coordinate of the resized window
	@param cy     - y coordinate of the resized window
*/
void Window::resizeCallback(GLFWwindow* window, int cx, int cy)
{

	void *ptr = glfwGetWindowUserPointer(window);		// we get the window object connected to the glfw window
	if (Window *wndPtr = static_cast<Window*>(ptr))		//see if it is really a Window* 
		wndPtr->resize(cx, cy);							//if it is we can call its resize to ajust viewport
}

/**
	Callback for key events.

	@param window   - window in which the key was pressed
	@param key      - the code of the pressed key
	@param scancode - unique number for every key press
	@param action   - GLFW_PRESS / GLFW_REPEAT  / GLFW_RELEASE
	@param mods     - mods like GLFW_STICKY_KEYS 

*/
void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_F11 && action == GLFW_PRESS)		// if F11 pressed
	{
		void *ptr = glfwGetWindowUserPointer(window);		//get the window object connected to this glfw window
		if (Window *wndPtr = static_cast<Window*>(ptr))		//check if it is really the Window* 
		{	
			wndPtr->setFullScreen(!wndPtr->isFullScreen());	//Set the fullscreen = !fullscreen
		}
	}
}

Window::~Window()
{
	std::cout << "Closing window" << std::endl;
	glfwDestroyWindow(m_window);
}
