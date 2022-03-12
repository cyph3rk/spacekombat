#include "Bolinha.h"

Bolinha::Bolinha()
{
    this->carregaImgs("_en1.bmp", 9);
    this->_x = this->getNumeroRandomico(550);
    this->_y = 0;
    this->_velocidade = 3;
    this->_vivo = true;
    this->_direcaoTiro = 1; // 0 = Acendente | 1 = descendente
    this->flg = 0;
    this->respaw = false;

    this->contaRespaw = 0;
    this->tempoRespaw = this->getNumeroRandomico(100);
}

void Bolinha::move()
{
    if ( (this->contaRespaw > this->tempoRespaw) && (this->respaw == false) ) {
        this->respaw = true;
        this->contaRespaw = 0;
    }
    else contaRespaw++;

    if (this->_y > 601) {
        this->_x = this->getNumeroRandomico(550);
        this->_y = 0;        
        this->contaRespaw = 0;
    }

    if (this->_vivo) {        
        if (this->flg > 7) this->flg = -1;
        this->flg++;
        this->_y += this->_velocidade;

        if (!this->tiro.getVivo() ) {
            if ((rand() % 50) == 2) {
                this->tiro.atirou(this->_x + 10, this->_y, 5, 1);
            }
        }
    }    
}

void Bolinha::draw()
{
    if (this->_vivo) {
        al_draw_bitmap(this->fig[this->flg], this->_x, this->_y, 0);        
    }
    this->move();

    this->tiro.move();
    this->explosao.draw();
}

void Bolinha::morreu()
{
    this->_vivo = false;
    this->explosao.setX(this->getX());
    this->explosao.setY(this->getY());
    this->explosao.explode();

    this->setX(900);
    this->setY(700);
}
