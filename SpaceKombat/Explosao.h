#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "Elemento.h"

class Explosao : public Elemento
{
private:
	int flg;

public:
	Explosao();

	void draw();	
	void explode();

};

