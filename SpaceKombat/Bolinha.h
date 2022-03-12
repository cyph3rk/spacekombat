#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "Elemento.h"
#include "Tiro.h"
#include "Explosao.h"

class Bolinha : public Elemento
{
private:
    short int contaRespaw;
    short int tempoRespaw;
    bool respaw;

    Explosao explosao;

public:
    int flg;
    Tiro tiro;

public:
    Bolinha();

    void move();
    void draw();

    void morreu();
};
