#include "Explosao.h"

void Explosao::draw()
{
	if (this->_vivo)
	{
		if (this->flg < 6)
		{
			al_draw_bitmap(this->fig[this->flg], this->_x, this->_y, 0);
			this->flg++;
		} 
	}	
}

void Explosao::explode()
{
	if (!this->_vivo) {
		this->_vivo = true;
		al_play_sample(this->audio, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);		
	}
}

Explosao::Explosao()
{
	this->carregaImgs("_kbum1.bmp", 6);
	this->carregaAudio("Explosao.ogg");

	this->flg = 0;
	this->_vivo = false;
}
