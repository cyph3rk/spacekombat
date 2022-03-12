#include "Jogador.h"

Jogador::Jogador()
{       
    this->carregaImgs("_pl.bmp", 9);
    this->carregaAudio("PlayerTiro.ogg");
    this->_x = 50;
    this->_y = 600;
    this->_velocidade = 10;
    this->_vivo = true;    
    this->flg = 1;
    this->lado = false;

    this->_direcaoTiro = 0; // 0 = Acendente | 1 = descendente
}

void Jogador::paraEsquerda()
{    
    this->lado = true;
    if ((this->flg % 2) == 0) this->flg = 5;
    else this->flg = 4;
    if (this->_x >= 0) this->_x -= 5;
}

void Jogador::paraDireita()
{
    this->lado = true;
    if ((this->flg % 2) == 0) this->flg = 3;
    else this->flg = 2;
    if (this->_x <= 752) this->_x += 5;
}

void Jogador::paraBaixo()
{
    this->lado = true;
    if ((this->flg % 2) == 0) this->flg = 7;
    else this->flg = 6;
    if (this->_y < 565) this->_y += 5;
}

void Jogador::paraCima()
{
    this->lado = false;
    if (this->_y > 0) this->_y -= 5;
}

void Jogador::cbLiberaTiro() {
    std::cout << "CallBack Tiro " << std::endl;
}

void Jogador::atirou()
{
    if (!this->tiro.getVivo()) {
        auto callback = std::bind(&Jogador::cbLiberaTiro, Jogador());
        this->tiro.atirou(this->_x+20, this->_y, -10, this->_direcaoTiro, callback);
        al_play_sample(this->audio, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    }
}

void Jogador::draw()
{
    if (this->_vivo) {
        if (!this->lado) {
            this->flg++;
            this->flg = (this->flg % 2);
        }
        this->lado = false;

        al_draw_bitmap(this->fig[this->flg], this->_x, this->_y, 0);
    }
            
    this->tiro.move();
    this->explosao.draw();
}

void Jogador::morreu()
{
    this->_vivo = false;
    this->explosao.setX(this->getX());
    this->explosao.setY(this->getY());
    this->explosao.explode();
    
    this->setX(900);
    this->setY(700);
}

bool Jogador::acertou(Elemento * elem[])
{
    // TODO: Melhorar esse for
    for (int i = 0; i < 8; i++) {        
        if (this->tiro.colidiu(elem[i])) {
            this->tiro.setVivo(false);
        }
    }

    return false;
}
