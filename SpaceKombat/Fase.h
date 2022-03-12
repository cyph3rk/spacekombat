#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class Fase
{
private:
    ALLEGRO_BITMAP* background;
	ALLEGRO_SAMPLE* backgroundMusic;
	int x;
	int y;

public:
	Fase();

	void draw();
	void move();
};

