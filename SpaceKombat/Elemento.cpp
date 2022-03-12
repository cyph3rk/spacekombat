#include "Elemento.h"

void Elemento::setX(int x)
{
	this->_x = x;
}

int Elemento::getX()
{
    return this->_x;
}

void Elemento::setY(int y)
{
	this->_y = y;
}

int Elemento::getY()
{
    return this->_y;
}

void Elemento::setW(int w)
{
    this->_w = _w;
}

int Elemento::getW()
{
    return this->_w;
}

void Elemento::setH(int h)
{
    this->_h = _h;
}

int Elemento::getH()
{
    return this->_h;
}

void Elemento::setVelocidade(int velocidade)
{
    this->_velocidade = velocidade;
}

void Elemento::setVivo(bool vivo)
{
    this->_vivo = vivo;
}

bool Elemento::getVivo()
{
    return this->_vivo;
}

void Elemento::carregaImgs(std::string arquivo, int nro)
{
    for (int i = 0; i < nro; i++) {
        std::string arqImagem = "F:/SpaceKombat/SpaceKombat/imagens/";
        arqImagem += std::to_string(i);
        arqImagem += arquivo;
        this->fig[i] = al_load_bitmap(arqImagem.c_str());
        assert(this->fig[i] != NULL);
        al_convert_mask_to_alpha(this->fig[i], al_map_rgb(255, 0, 255));

        this->_h = al_get_bitmap_height(this->fig[0]);
        this->_w = al_get_bitmap_width(this->fig[0]);        
    }
}

void Elemento::carregaAudio(std::string arquivo)
{
    std::string arqImagem = "F:/SpaceKombat/SpaceKombat/audios/";
    arqImagem += arquivo;
    this->audio = al_load_sample(arqImagem.c_str());
    assert(this->audio != NULL);
}

void Elemento::setDirecao(int direcao)
{
    this->_direcaoTiro = direcao;
}

int Elemento::getNumeroRandomico(int numeroFinal)
{
    std::random_device random_device;
    std::mt19937 random_engine{ random_device() };
    std::uniform_int_distribution<int> die_distribution{ 1, numeroFinal };
    int numero = die_distribution(random_engine);

    return numero;
}

bool Elemento::colidiu(Elemento* elemento)
{
    if (elemento->getVivo())
    {
        float x1 = elemento->getX();
        float y1 = elemento->getY();
        int w1 = elemento->_w;
        int h1 = elemento->_h;

        float x2 = this->getX();
        float y2 = this->getY();
        int w2 = this->_w;
        int h2 = this->_h;

        if ((abs(x1 - x2) < ((w1 + w2) / 2)) && (abs(y1 - y2) < ((h1 + h2) / 2))) {        
            elemento->morreu();
            this->morreu();

            return true;
        }
    }

    return false;
}




