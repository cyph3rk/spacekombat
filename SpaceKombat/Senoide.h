#pragma once

#include <iostream>
#include <string>
#include <cmath>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define TOT_AUX 10

class Senoide
{
public:
    ALLEGRO_BITMAP* fig[TOT_AUX];
    int px[TOT_AUX];
    int py[TOT_AUX];
    int vel[TOT_AUX];
    int lado[TOT_AUX];
    bool sentido[TOT_AUX];
    int flg[TOT_AUX];
    bool vivo[TOT_AUX];
    int qtd[TOT_AUX];

    int length[TOT_AUX];
    al_fixed sx[TOT_AUX];
    al_fixed sy[TOT_AUX];
    al_fixed angle[TOT_AUX];
    al_fixed angle_stepsize[TOT_AUX];

    int count;

    Senoide();

    void move();
    void draw();
    void zeraStatu();
};

