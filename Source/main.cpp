#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <list>
#include <array>
#include "Controller.h"
#include <thread>

int main()
{
	Controller CurrentController;
	CurrentController.run();
	return 0;
}