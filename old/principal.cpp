#include "globais.h"

void inicializa();
void finaliza();
void enemys_senoide(struct Inimigo *en);
void enemys_plot(struct Inimigo *en);
void enemys_pong(struct Inimigo *en);
void colide(struct Inimigo *en);
void destroy_enemys(struct Inimigo *en, int n, int s);
void game();

int main() {

    inicializa();
    game();
    finaliza();
    return 0;
}
END_OF_MAIN();

void game(){

    int cont = 0;

    clear(buffer);
    blit(background, buffer, 0, 2046, 0, 0, MAX_X, MAX_Y);

    cout << sizeof(enemy_sen);

    while(!ESCAPE) {

        cont++;

        clear(buffer);
        blit(background, buffer, scre_x, scre_y, 0, 0, MAX_X, MAX_Y);

        if (!side) {
          player.flg++;
          player.flg = (player.flg % 2);
        }
        side = false;

        if (scre_y >= 0) scre_y--;

        if (DIREITA){
            side = true;
            if ((player.flg % 2) == 0) player.flg = 3;
            else player.flg = 6;
            if (player.px <= 752) player.px+=5;
        }

        if (ESQUERDA){
            side = true;
            if ((player.flg % 2) == 0) player.flg = 5;
            else player.flg = 4;
            if (player.px >= 0) player.px-=5;
        }

        if (CIMA){
            if (player.py >= 0) player.py-=5;
        }

        if (BAIXO){
            side = true;
            if ((player.flg % 2) == 0) player.flg = 7;
            else player.flg = 8;
            if (player.py <= 558) player.py+=5;
        }

        if (SPACE){

            if (player.cont_tiro < 20) {
              bool achou = false;
              for (int i=0;i<=19;i++) {
                if ((player.fire[i].vivo == false) and (!achou)){
                    player.fire[i].vivo = true;
                    player.fire[i].tx = player.px+20;
                    player.fire[i].ty = player.py;
                    player.cont_tiro++;
                    achou = true;
                }
              }
            }
        }

        if (player.cont_tiro > 0) {
            for (int i=0;i<=19;i++) {
                if (player.fire[i].vivo == true) {
                    draw_sprite(buffer, player.fire[i].fig, player.fire[i].tx, player.fire[i].ty);
                    player.fire[i].ty -= player.fire[i].vel;
                    if (player.fire[i].ty <= 0) {
                        player.fire[i].vivo = false;
                        player.cont_tiro--;
                    }
                }
            }
        }

        colide(enemy_pong);
        colide(anemy_plot);
        colide(enemy_sen);

        draw_sprite(buffer, player.fig[player.flg], player.px, player.py);

        enemys_senoide(enemy_sen);
        enemys_plot(anemy_plot);
        enemys_pong(enemy_pong);

        draw_sprite(screen, buffer, 0, 0);
        rest(20);
    } //FIM da estrutura while
}

void enemys_senoide(struct Inimigo *en){
    if (cont < 20){
        for (int i=1;i<=10;i++) {
          draw_sprite(buffer, en[i].fig[en[i].flg], en[i].px+180, (en[i].py+(i*20)));
          cont++;
        }
    }else {
      cont=0;
      for (int i=1;i<=10;i++) {
        enemy_sen[i].seno.sx = enemy_sen[i].seno.length * fsin (enemy_sen[i].seno.angle);
        en[i].px = fixtoi(enemy_sen[i].seno.sx);
        en[i].py += en[i].vel;
        draw_sprite(buffer, en[i].fig[en[i].flg], en[i].px+180, (en[i].py+(i*20)));
        if (en[i].flg >= 2) en[i].flg = -1;
        en[i].flg++;
        en[i].seno.angle += en[i].seno.angle_stepsize;
        if (en[i].py >= 620){
          en[i].py = -180;
        }
      }
    }
}

void enemys_plot(struct Inimigo *en){

    bool achou = false;

    if (cont_enemy < 10) {
      if ((rand() % 15) == 2) {
          for (int i=1;i<10;i++){
              if ((en[i].vivo == false) and !achou ) {
                en[i].vivo = true;
                cont_enemy++;
                achou = true;
              }
          }
      }
    }

    for (int i=1;i<10;i++) {
      if (en[i].py > 600) {
        en[i].vivo = false;
        cont_enemy--;
        en[i].px = rand() % 800;
        en[i].py = -20;
      }

      if (en[i].vivo) {
          draw_sprite(buffer,en[i].fig[en[i].flg],en[i].px,en[i].py);
          if (en[i].flg >= 8) en[i].flg = -1;
          en[i].flg++;
          en[i].py += en[i].vel;
      }
    }
}

void enemys_pong(struct Inimigo *en){

    bool achou = false;

    if (cont_pong <= 3) {
      if ((rand() % 15) == 2) {
          for (int i=1;i<=3;i++){
              if ((en[i].vivo == false) and !achou ) {
                en[i].vivo = true;
                cont_pong++;
                achou = true;
              }
          }
      }
    }

    for (int y=0;y<=3;y++) {
      if ((rand() % 15) == 2) {
        if (en[y].cont_tiro < 5) {
              bool achou = false;
              for (int i=0;i<=4;i++) {
                if ((en[y].fire[i].vivo == false) and (!achou)){
                    en[y].fire[i].vivo = true;
                    en[y].fire[i].tx = en[y].px+20;
                    en[y].fire[i].ty = en[y].py+40;
                    en[y].cont_tiro++;
                    achou = true;
                }
              }
        }
      }
    }

    for (int i=1;i<=3;i++) {
      if (en[i].py > 600) {
        en[i].vivo = false;
        cont_pong--;
        en[i].px = rand() % 800;
        en[i].py = -20;
      }

      if (en[i].vivo) {
          draw_sprite(buffer, en[i].fig[en[i].flg], en[i].px, en[i].py);
          if (en[i].flg >= 5)
            en[i].flg = -1;
          if (en[i].py >= 546)
            en[i].vel = ((en[i].vel)*(-1));
          if (en[i].py <= 0)
            en[i].vel = ((en[i].vel)*(-1));
          if (en[i].px >= 744)
            en[i].lado = ((en[i].lado)*(-1));
          if (en[i].px <= 0)
            en[i].lado = ((en[i].lado)*(-1));

          en[i].flg++;
          en[i].py += en[i].vel;
          en[i].px += en[i].lado;

          for (int f=0;f<=4;f++) {
                if (en[i].fire[f].vivo == true) {
                    draw_sprite(buffer, en[i].fire[f].fig, en[i].fire[f].tx, en[i].fire[f].ty);
                    en[i].fire[f].ty += en[i].fire[f].vel;
                    if (en[i].fire[f].ty >= 605) {
                        en[i].fire[f].vivo = false;
                        en[i].cont_tiro--;
                    }
                }
          }
      }
    }
}

void colide(struct Inimigo *en){

  for (int i=1;i<=en[1].qtd;i++) {
      if (en[i].vivo) {
          if ((player.px >= en[i].px) && (player.px <= (en[i].px+en[i].fig[1]->w)) &&
              (player.py >= en[i].py) && (player.py <= (en[i].py+en[i].fig[1]->h))) {
                cout << "colidiu-A" << i << "\n";
          }

          for (int f=0;f<=4;f++) {
              if (en[i].fire[f].vivo) {
                if ((player.px >= en[i].fire[f].tx) &&
                    (player.px <= (en[i].fire[f].tx+en[i].fire[f].fig->w)) &&
                    (player.px >= en[i].py) &&
                    (player.py <= (en[i].fire[f].ty+en[i].fire[f].fig->h))) {
                      cout << "colidiu-B" << f << "\n";
                }
              }
          }
      }
  }
}

void inicializa() {

    char numero[33];
    char *arquivo;

    allegro_init();
    install_keyboard();
    set_color_depth(SET_COLOR);
    set_gfx_mode(GFX_MODE, MAX_X, MAX_Y, 0, 0);

    install_timer();

    background = load_bitmap("BackGround.bmp",NULL);
    buffer = create_bitmap(MAX_X,MAX_Y);

    scre_x = 0;  scre_y= 2046;
    side = false;

    arquivo = "_pl.bmp";
    for(int j=0; j<=8; j++) {
            itoa(j, numero, 10);
            strcat(numero, arquivo);
            player.fig[j] = load_bitmap(numero,NULL);
    }
    player.px = 250;
    player.py = 250;
    player.flg = 1;
    player.cont_tiro = 0;
    for (int f = 0; f <= 19; f++) {
        player.fire[f].fig = load_bitmap("1_fire.bmp",NULL);
        player.fire[f].tx = 5;
        player.fire[f].ty = 5;
        player.fire[f].vel = 5;
        player.fire[f].flg = 0;
        player.fire[f].vivo = false;
    }

// ********************************************************
// Inimigos Senoide
// ********************************************************
    for (int i=1;i<=10;i++) {
      arquivo = "_en1.bmp";
      for(int j=0; j<=5; j++) {
            itoa(j, numero, 10);
            strcat(numero, arquivo);
            enemy_sen[i].fig[j] = load_bitmap(numero,NULL);
      }
      enemy_sen[i].px = 250;
      enemy_sen[i].py = -200;
      enemy_sen[i].vel = 10;
      enemy_sen[i].vivo = true;
      enemy_sen[i].lado = 10;
      enemy_sen[i].sentido = false;
      enemy_sen[i].flg = 0;
      enemy_sen[i].seno.length = 20;
      enemy_sen[i].seno.sx = 0;
      enemy_sen[i].seno.sy = 0;
      enemy_sen[i].seno.angle = (0);
      enemy_sen[i].seno.angle_stepsize = itofix (i);
      for (int f=0;f<=4;f++) {
        enemy_sen[i].fire[f].fig = load_bitmap("en2_tiro.bmp",NULL);
        enemy_sen[i].fire[f].tx = 0;
        enemy_sen[i].fire[f].ty = 0;
        enemy_sen[i].fire[f].vel = 5;
        enemy_sen[i].fire[f].flg = 0;
        enemy_sen[i].fire[f].vivo = false;
      }
      enemy_sen[i].qtd = 10;
      // ********************************************************

      // ********************************************************
      // Inimigos aleat�rios
      // ********************************************************
      arquivo = "_en1.bmp";
      for(int j=0; j<=8; j++) {
            itoa(j, numero, 10);
            strcat(numero, arquivo);
            anemy_plot[i].fig[j] = load_bitmap(numero,NULL);
      }
      anemy_plot[i].px = rand() % 800;
      anemy_plot[i].py = -20;
      anemy_plot[i].vel = 3;
      anemy_plot[i].vivo = false;
      anemy_plot[i].lado = 3;
      anemy_plot[i].sentido = false;
      anemy_plot[i].flg = 0;
      for (int f=0;f<=4;f++) {
        anemy_plot[i].fire[f].fig = load_bitmap("en2_tiro.bmp",NULL);
        anemy_plot[i].fire[f].tx = 0;
        anemy_plot[i].fire[f].ty = 0;
        anemy_plot[i].fire[f].vel = 5;
        anemy_plot[i].fire[f].flg = 0;
        anemy_plot[i].fire[f].vivo = false;
      }
      anemy_plot[i].qtd = 10;
    }
    // ********************************************************

    // ********************************************************
    // Inimigos Pongs
    // ********************************************************
    for (int i=1;i<=4;i++) {
      arquivo = "_en2.bmp";
      for(int j=0; j<=5; j++) {
            itoa(j, numero, 10);
            strcat(numero, arquivo);
            enemy_pong[i].fig[j] = load_bitmap(numero,NULL);
      }
      enemy_pong[i].px = 150*i;;
      enemy_pong[i].py = 1;
      enemy_pong[i].vel = 5;
      enemy_pong[i].vivo = false;
      enemy_pong[i].lado = 5;
      enemy_pong[i].sentido = true;
      enemy_pong[i].flg = 0;
      enemy_pong[i].cont_tiro = 0;
      for (int f=0;f<=4;f++) {
        enemy_pong[i].fire[f].fig = load_bitmap("en1_tiro.bmp",NULL);
        enemy_pong[i].fire[f].tx = 0;
        enemy_pong[i].fire[f].ty = 0;
        enemy_pong[i].fire[f].vel = 10;
        enemy_pong[i].fire[f].flg = 0;
        enemy_pong[i].fire[f].vivo = false;
      }
      enemy_pong[i].qtd = 4;
    }

    // ********************************************************

    // ********************************************************
    // boom
    // ********************************************************

    arquivo = "_kbum1.bmp";
    for(int j=0; j<=5; j++) {
        itoa(j, numero, 10);
        strcat(numero, arquivo);
        boom.fig[j] = load_bitmap(numero,NULL);
    }
    boom.kx;
    boom.ky;
    // ********************************************************

    cont_enemy = 0;
    cont_pong = 0;
    cont = 0;
}

void destroy_enemys(struct Inimigo *en, int n, int s){
    for (int i=1;i<=n;i++) {
        for (int t=0;t<=s;t++)
          destroy_bitmap(en[i].fig[t]);
        for (int f=0;f<5;f++)
          destroy_bitmap(en[i].fire[f].fig);
    }
}

void finaliza(){

    destroy_bitmap(background);
    destroy_bitmap(buffer);

    destroy_enemys(anemy_plot, 10, 5);
    destroy_enemys(enemy_sen, 10, 5);
    destroy_enemys(enemy_pong, 4, 5);
    //destroy_enemys(player, 1, 20);


    for (int i=0;i<=8;i++) {
        destroy_bitmap(player.fig[i]);
    }
    for (int f=0;f<19;f++)
          destroy_bitmap(player.fire[f].fig);
    for (int g=0;g<5;g++)
          destroy_bitmap(boom.fig[g]);

}




