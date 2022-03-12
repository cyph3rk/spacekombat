/* Fonte 
https://www.allegro.cc/forums/thread/607037
*/


class Animation {

protected :
   ALLEGRO_BITMAP** frames;
   double duration;
   double frames_per_sec;
   double frametime;
   int num_frames;
   int frame_num;
   
public :
   Animation() : frames(0), duration(0.0), frames_per_sec(0.0), frametime(0.0), num_frames(0), frame_num(0)
   {}

   ~Animation() {Free();}

   void Free() {
      if (frames) {
         delete [] frames;
         frames = 0;
      }
   }

   void Setup(double play_duration , int number_of_frames) {
      Free();
      assert(number_of_frames > 0);
      assert(play_duration > 0.0);
      duration = play_duration;
      num_frames = number_of_frames;
      frames = new ALLEGRO_BITMAP*[num_frames];
      frames_per_sec = (double)num_frames / duration;
      SetFrameTime(0.0);
   }

   void AdvanceFrameTime(double delta_time) {
      SetFrameTime(frametime + delta_time);
   }

   void SetFrameTime(double new_frame_time) {
      while(new_frame_time < 0.0) {new_frame_time += duration;}
      while(new_frame_time >= duration) {new_frame_time -= duration;}
      frametime = new_frame_time;
      frame_num = (int)(frametime*frames_per_sec);
   }

   void SetBitmap(ALLEGRO_BITMAP* bmp, int frame_number) {
      assert(frames);
      assert((frame_number >= 0) && (frame_number < num_frames));
      frames[frame_number] = bmp;
   }

   void Display(int x , int y) {
      assert(frames);
      assert(frames[frame_num]);
      al_draw_bitmap(frames[frame_num] , (float)x , (float)y , 0);
   }

};




int main(int argc, char **argv)
{
    /*
    ALLEGRO DECLARATIONS
    */
    
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    

    /*
    VARIABLES
    */

  bool key[4] = {false, false, false, false };
  bool redraw = true;
  bool doexit = false;
  
  float sprite_x = (SCREEN_W/2);
  float sprite_y = (SCREEN_H/2);
  
  player sprite;

    /*
    CONFIGURATION
    */
    
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

    
double duration = 10.0;
int number_of_frames = 40;
Animation anime;
anime.Setup(duration , number_of_frames);

ALLEGRO_BITMAP* bmp = al_load_bitmap("player.png"); //converts the sprite sheet's magenta background to transparent pixels al_convert_mask_to_alpha(bmp, (al_map_rgb(255, 0, 255)));
int i = 0;
ALLEGRO_BITMAP* bmp_array[40];
for(int x = 0; x < 8; x++) {
   for(int y = 0; y < 5; y++) {
      bmp_array[x][y] = al_create_sub_bitmap(bmp, 32*x, 32*y, 32, 32);
      anime.SetBitmap(bmp_array[x][y] , i);
      ++i;
   }
}
    
    while(!doexit)
  {

   


// Event loop
   while (1) {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue , &ev);
      if (ev.type == ALLEGRO_EVENT_TIMER) {
         anime.AdvanceFrameTime(SECONDS_PER_TICK);
         redraw = true;
      }
      if (al_is_event_queue_empty(event_queue)) {break};
   }
   if (redraw) {
      al_clear_to_color(al_map_rgb(0,0,0));
      anime.Draw(400 - al_get_bitmap_width(bmp)/2 , 300 - al_get_bitmap_height(bmp)/2);
      al_flip_display();
   }
}


  }
  
  al_destroy_timer(timer);
  al_destroy_display(display);
  al_destroy_event_queue(event_queue);
  //destroy bitmaps

  return 0;
  }