#include <allegro.h>
//#include <stdio.h>
#include <iostream.h>

#define SET_COLOR  32
#define MAX_X     800
#define MAX_Y     600
#define GFX_MODE  GFX_AUTODETECT_WINDOWED

#define ESCAPE    key[KEY_ESC]
#define ESQUERDA  key[KEY_LEFT]
#define DIREITA   key[KEY_RIGHT]
#define CIMA      key[KEY_UP]
#define BAIXO     key[KEY_DOWN]
#define SPACE     key[KEY_SPACE]
#define CONTROL   key[KEY_LCONTROL]

BITMAP *background;
BITMAP *buffer;

int scre_x, scre_y;
bool side;
//FILE *arquivoTrace;

int cont_enemy;
int cont_pong;
int cont;

struct Tiro {
    BITMAP *fig;
    int tx;
    int ty;
    int vel;
    int flg;
    bool vivo;
};

struct Kbum {
    BITMAP *fig[6];
    int kx;
    int ky;
} boom;

struct Senoide {
  int length;
  fixed sx;
  fixed sy;
  fixed angle;
  fixed angle_stepsize;
} mov_Sen;

struct Inimigo {
    BITMAP *fig[9];
    int px;
    int py;
    int vel;
    int lado;
    bool sentido;
    int flg;
    bool vivo;
    int cont_tiro;
    int qtd;
    struct Tiro fire[20];
    struct Senoide seno;
} player, enemy_sen[10], anemy_plot[10], enemy_pong[4];
