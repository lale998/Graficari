#pragma once

#include "Window.h"

class Engine
{
private:
	Window* m_wnd;
	void    update(void);
	void    render(void);

public:
	void    start(bool);
	Engine();
	~Engine();
};

