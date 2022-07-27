#include "ExtraLife.h"
#include <iostream>

ExtraLife::ExtraLife(int x, int y)
	: PlacableActor(x, y)
{

}

void ExtraLife::Draw()
{
	std::cout << "1";
}
