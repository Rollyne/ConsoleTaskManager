#pragma once
#include "MenuItems.h"
class AdministrationView
{
private:
	AdminMenuItems RenderMenu();
public:
	void Run();
	AdministrationView();
	~AdministrationView();
};

