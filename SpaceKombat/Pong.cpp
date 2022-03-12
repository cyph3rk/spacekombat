#include "Pong.h"

Pong::Pong()
{
    this->carregaImgs("_en2.bmp", 6);
    this->carregaAudio("EnemyTiro.ogg");

    this->_x = this->getNumeroRandomico(500);
    this->_y = this->getNumeroRandomico(500);

    this->_velocidade = 5;
    this->_vivo = true;
    this->_direcaoTiro = 1; // 0 = Acendente | 1 = descendente

    this->flg = 0;
    this->lado = 5;

    this->tiro.carregaImgs("_tiro_ene.bmp", 1);    
}

void Pong::move()
{    
    if (this->_y > 600) {
        this->_vivo = false;
        this->_x = rand() % 800;
        this->_y = -20;
    }

    if (this->_vivo) {
        if (this->flg >= 5)
            this->flg = -1;
        if (this->_y >= 546)
            this->_velocidade = ((this->_velocidade) * (-1));
        if (this->_y <= 0)
            this->_velocidade = ((this->_velocidade) * (-1));
        if (this->_x >= 744)
            this->lado = ((this->lado) * (-1));
        if (this->_x <= 0)
            this->lado = ((this->lado) * (-1));

        this->flg++;
        this->_y += this->_velocidade;
        this->_x += this->lado;

        if (!this->tiro.getVivo()) {
            if ((rand() % 15) == 2) {
                al_play_sample(this->audio, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                this->tiro.atirou(this->_x + 20, this->_y + 40, 10, 1);
            }
        }   
    }
}

void Pong::draw()
{
    if (this->_vivo)
    {
        al_draw_bitmap(this->fig[this->flg], this->_x, this->_y, 0);
        this->move();
    } 

    this->tiro.move();    
    this->explosao.draw();
}


void Pong::morreu()
{
    this->_vivo = false;
    this->explosao.setX(this->getX());
    this->explosao.setY(this->getY());
    this->explosao.explode();

    this->setX(900);
    this->setY(700);
}
