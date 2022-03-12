#pragma once

#include <List>
#include<functional>
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "Tiro.h"

class ControlaTiro
{
public:
	std::list<Tiro> tiros;

	void atirou(int x, int y, int vel, std::string quemAtirou);

	void moveTiros();

};

