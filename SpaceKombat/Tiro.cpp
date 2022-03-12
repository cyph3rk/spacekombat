#include "Tiro.h"

Tiro::Tiro()
{
    this->carregaImgs("_fire.bmp", 1);

    this->_x = 0;
    this->_y = 0;
    this->_velocidade = 0;
    this->_vivo = false;
    this->_direcaoTiro = 0; // 0 = Acendente | 1 = descendente    
}

void Tiro::move()
{
    if (this->_vivo == true) {
        this->_y = (this->_y + this->_velocidade);

        if (this->_direcaoTiro) { // Tiro para baixo
            if (this->_y > 601) {
                this->_vivo = false;  
            }
        }
        else {              // Tiro para cima
            if (this->_y < 0) {
                this->_vivo = false;
                this->funcCallBack();
            }
        }
        this->draw();
    }
}

void Tiro::draw()
{
    if (this->_vivo) {
        al_draw_bitmap(this->fig[0], this->_x, this->_y, 0);
    }
}

void Tiro::atirou(int x, int y, int velocidade, int direcao, std::function<void(void)> f)
{   
    this->funcCallBack = f;
    this->atirou(x, y, velocidade, direcao);    
}

void Tiro::atirou(int x, int y, int velocidade, int direcao)
{
    this->_vivo = true;
    this->_x = x;
    this->_y = y;
    this->_velocidade = velocidade;
    this->_direcaoTiro = direcao;
}

void Tiro::morreu()
{
    this->_vivo = false;

    this->setX(900);
    this->setY(700);
}






