#pragma once

#include <iostream>
#include <functional>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "Elemento.h"

class Tiro : public Elemento
{
private:    
    std::function<void(void)> funcCallBack;

public:
    Tiro();
    
    void move();
    void draw();

    void atirou(int x, int y, int velocidade, int direcao, std::function<void(void)> f);
    void atirou(int x, int y, int velocidade, int direcao);

    void morreu();

};

