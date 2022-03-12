#pragma once

#include <string>
#include <random>
#include <iostream>
#include <functional>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class Elemento
{
protected:
    ALLEGRO_BITMAP* fig[9];
    ALLEGRO_SAMPLE* audio;
    
    int  _x;
    int  _y;
    int  _h;
    int  _w;
    int  _velocidade;    
    int  _direcaoTiro;
    bool _vivo;

    std::function<void(void)> funcCallBack;

public:        
    void setX(const int x);
    int getX();

    void setY(const int y);
    int getY();

    void setW(const int w);
    int getW();

    void setH(const int h);
    int getH();

    void setVivo(const bool vivo);
    bool getVivo();

    void setVelocidade(const int velocidade);
    void carregaImgs(std::string arquivo, int nro);
    void carregaAudio(std::string arquivo);
    void setDirecao(const int direcao);
    int getNumeroRandomico(int numeroFinal);
    bool colidiu(Elemento* jogador);
    
    virtual void morreu() { /* Não obrigatorio */ };
};

