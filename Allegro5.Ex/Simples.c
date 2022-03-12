

/* Fonte
https://www.allegro.cc/forums/thread/607037
*/

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

/* CONSTANTS */

const int SCREEN_W = 640;
const int SCREEN_H = 480;
const float FPS = 60;

enum MYKEYS {
    KEY_UP, KEY_DOWN, KEY_W, KEY_S
};

/* FUNCTIONS */

/* OBJECTS */

class player
{  
private: 
  ALLEGRO_BITMAP *bmp;
  ALLEGRO_BITMAP *animation;
  int animationWidth;
  int animationHeight;
  
public:  
  //Construtor
  player();
  //Draws the sprite from areas x and y from the sprite sheet
  void draw(float x, float y);
};

  player::player()
  {
      //loads the entire spritesheet
      bmp = al_load_bitmap("player.png");
      //converts the sprite sheet's magenta background to transparent pixels
      al_convert_mask_to_alpha(bmp, (al_map_rgb(255, 0, 255)));
      
      //each animation in the sprite sheet is 32X32 pixels
      animationWidth = al_get_bitmap_width(bmp)/32;
      animationHeight = al_get_bitmap_height(bmp)/32;
  }
  
  void player::draw(float x, float y)
  {
      //draw section of sprite sheet
      //target bitmap, region x, region y, width, height, destination x, destination y, flag(0)
      al_draw_bitmap_region(bmp, 0, 0, animationWidth, animationHeight, x, y, 0);
  }

/* MAIN */

int main(int argc, char **argv)
{
    /* ALLEGRO DECLARATIONS */
    
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    
    /* VARIABLES */

  bool key[4] = {false, false, false, false };
  bool redraw = true;
  bool doexit = false;
  
  float sprite_x = (SCREEN_W/2);
  float sprite_y = (SCREEN_H/2);
  
  player sprite;

    /* CONFIGURATION */
    
    if(!al_init()) {
        fprintf(stderr, "failed to initialized allegro\n");
        return -1;
    }
    
    if(!al_install_keyboard()) {
        fprintf(stderr, "failed to install keyboard\n");
        return -1;
    }

    //initialize display (w, h)
    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display) {
        fprintf(stderr, "failed to create display\n");
        return -1;
    }
    
    timer = al_create_timer(1.0/FPS);
    if(!timer) {
        fprintf(stderr, "failed to create timer\n");
        return -1;
    }

    al_set_target_bitmap(al_get_backbuffer(display));

    event_queue = al_create_event_queue();
    if(!event_queue) {
        fprintf(stderr, "failed to create event queue\n");
        return -1;
    }
    
    al_register_event_source(event_queue, al_get_display_event_source(display));
    
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    
    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_flip_display();
    
    al_start_timer(timer);

    /* MAIN LOOP */
    
    while(!doexit)
    {

    ALLEGRO_EVENT ev;

    al_wait_for_event(event_queue, &ev);

    if(ev.type == ALLEGRO_EVENT_TIMER) 
    {
      redraw = true;
    }

    else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
      break;
    }
    else if(ev.type == ALLEGRO_EVENT_KEY_UP) 
    {

        // Essa Forma de pegar o evento do teclado, pega aperto a aperto. Não pega se a tecla ficar pressionada
        switch(ev.keyboard.keycode) 
        {
      case ALLEGRO_KEY_ESCAPE:
          doexit = true;
          break;
        }
    }

    if(redraw && al_is_event_queue_empty(event_queue))
    {
      redraw = false;
      al_clear_to_color(al_map_rgb(0,0,0));

      //redraw bitmaps
      

      //draw player
      sprite.draw(sprite_x, sprite_y);
      
      al_flip_display();

    }


  }
  
  al_destroy_timer(timer);
  al_destroy_display(display);
  al_destroy_event_queue(event_queue);
  //destroy bitmaps

  return 0;
  }