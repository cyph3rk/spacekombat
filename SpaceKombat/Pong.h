#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "Tiro.h"
#include "Elemento.h"
#include "Jogador.h"
#include "Explosao.h"

class Pong : public Elemento
{
public:
    int flg;
    int lado;
    Tiro tiro;

    Explosao explosao;   

public:
    Pong();

    void move();
    void draw();  

    void morreu();
};

