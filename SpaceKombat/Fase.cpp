#include "Fase.h"

Fase::Fase()
{
    this->background = al_load_bitmap("F:/SpaceKombat/SpaceKombat/imagens/BackGround.bmp");
    assert(this->background != NULL);
        
    this->backgroundMusic = al_load_sample("F:/SpaceKombat/SpaceKombat/audios/ThemeFase.ogg");
    assert(this->backgroundMusic != NULL);

    al_play_sample(this->backgroundMusic, 0.1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

    this->x = 0;
    this->y = -2046;
}

void Fase::draw()
{
    al_draw_bitmap(this->background, this->x, this->y, 0);
}

void Fase::move()
{
    if (this->y <= 0) this->y++;
}
