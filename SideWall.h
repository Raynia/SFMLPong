#pragma once

#include <SFML/Graphics.hpp>
#include "EnumLibrary.h"

using namespace sf;

class SideWall
{
public:
	FloatRect wallArea;
	WallSide wallSide; // WallSide enum

	SideWall(FloatRect wallArea, WallSide wallSide) : wallArea(wallArea), wallSide(wallSide) {};
};