#include "Senoide.h"

Senoide::Senoide()
{
    for (int i = 0; i < TOT_AUX; i++) {

        std::string arquivo = "_en1.bmp";        
        std::string arqImagem = "F:/SpaceKombat/SpaceKombat/imagens/";
        arqImagem += std::to_string(i);
        arqImagem += arquivo;
        this->fig[i] = al_load_bitmap(arqImagem.c_str());
        assert(this->fig[i] != NULL);
        al_convert_mask_to_alpha(this->fig[i], al_map_rgb(255, 0, 255));

        this->zeraStatu();
    }
    this->count = 0;
}

void Senoide::move()
{
    if (this->count < 1) {
        count++;
    }
    else {
        for (int i = 0; i < TOT_AUX; i++) {
            this->sx[i] = this->length[i] * al_fixsin(this->angle[i]);
            this->px[i] =  al_fixtoi(this->sx[i]);
            this->py[i] += this->vel[i];
            this->angle[i] += this->angle_stepsize[i];
            if (this->py[i] >= 620) {
                this->zeraStatu();
            }
        }
        this->count = 0;
    }
}

void Senoide::draw()
{
    for (int i = 0; i < TOT_AUX; i++) {
        al_draw_bitmap(this->fig[i], this->px[i]+180, (this->py[i] + (i * 20)), 0);
    }
    this->move();
}

void Senoide::zeraStatu()
{
    for (int i = 0; i < TOT_AUX; i++) {
        this->px[i] = 250;
        this->py[i] = -200;
        this->vel[i] = 10;
        this->vivo[i] = true;
        this->lado[i] = 10;
        this->sentido[i] = false;
        this->flg[i] = 0;
        this->length[i] = 20;
        this->sx[i] = 250;
        this->sy[i] = 0;
        this->angle_stepsize[i] = al_itofix(i);
        this->angle[i] = al_itofix(i);
        this->qtd[i] = 10;
    }
}
