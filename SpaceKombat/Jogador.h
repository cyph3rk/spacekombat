#pragma once

#include <iostream>
#include <string>
#include <cstdio>
#include <functional>


#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "Tiro.h"
#include "Elemento.h"
#include "Explosao.h"

class Jogador : public Elemento
{
private:
    int   flg;
    bool  lado;
    Tiro  tiro;
    Explosao explosao;
        
public:
    Jogador();

    void paraEsquerda();
    void paraDireita();
    void paraBaixo();
    void paraCima();
    void atirou();    
    void draw();
    void morreu();
    bool acertou(Elemento * elem[]);

    void cbLiberaTiro();
};

