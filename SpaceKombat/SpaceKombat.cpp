#include "Globaish.h"

int main()
{
    ALLEGRO_DISPLAY*     display = NULL;
    ALLEGRO_EVENT_QUEUE* queue   = NULL;
    ALLEGRO_TIMER*       timer   = NULL;

    ALLEGRO_SAMPLE* playerDeadSound = NULL;
        
    if (!al_init()) {
        std::cout << "Falha Iniciar Allegro." << std::endl;
        return -1;
    }

    display = al_create_display(MAX_X, MAX_Y);
    if (!display) {
        std::cout << "Falha Iniciar Display." << std::endl;
        return -1;
    }

    queue = al_create_event_queue();
    if (!queue) {
        std::cout << "Falha Iniciar Queue (fila)." << std::endl;
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        std::cout << "Falha Iniciar Timer." << std::endl;
        return -1;
    }
    
    if (!al_install_keyboard()) {
        std::cout << "Falha Iniciar Teclado." << std::endl;
        return -1;
    }

    if (!al_init_acodec_addon()) {
        std::cout << "Falha Iniciar Codec Audio." << std::endl;
        return -1;
    }

    if (!al_install_audio()) {
        std::cout << "Falha Iniciar Audio." << std::endl;
        return -1;
    }

    if (!al_reserve_samples(10)) {
        std::cout << "Falha Iniciar Audio e Mixer." << std::endl;
        return 1;
    }
        
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_init_image_addon();
    
    playerDeadSound = al_load_sample("F:/SpaceKombat/SpaceKombat/audios/Explosao.ogg");
    assert(playerDeadSound != NULL);

    Fase fase;
    Jogador jogador;
    
    Pong pong1;    
    Pong pong2;
    Pong pong3;
        
    Bolinha bolinha1;    
    Bolinha bolinha2;
    Bolinha bolinha3;
    Bolinha bolinha4;
    Bolinha bolinha5;

    Senoide senoide;

    // TODO: Colocar isso em um container
    Elemento *elem[] = { &pong1, &pong2, &pong3, &bolinha1, &bolinha2, &bolinha3, &bolinha4, &bolinha5 };

    al_start_timer(timer);

    bool running = true;


    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }
                       
        ALLEGRO_KEYBOARD_STATE keyState;
        al_get_keyboard_state(&keyState);
        if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) {             
            jogador.paraDireita();
        }
        else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) {
            jogador.paraEsquerda();
        }
        else if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)) {            
            jogador.paraBaixo();
        }
        else if (al_key_down(&keyState, ALLEGRO_KEY_UP)) {
            jogador.paraCima();
        }
        else if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) {
            running = false;
        }
        else if (al_key_down(&keyState, ALLEGRO_KEY_SPACE)) {
            jogador.atirou();
        }

        if (event.type == ALLEGRO_EVENT_TIMER) {
            al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));
            fase.draw();

            pong1.draw();
            pong1.colidiu(&jogador);

            pong2.draw();
            pong2.colidiu(&jogador);

            pong3.draw();
            pong3.colidiu(&jogador);

            bolinha1.draw();
            bolinha1.colidiu(&jogador);

            bolinha2.draw();
            bolinha2.colidiu(&jogador);

            bolinha3.draw();
            bolinha3.colidiu(&jogador);

            bolinha4.draw();
            bolinha4.colidiu(&jogador);

            bolinha5.draw();
            bolinha5.colidiu(&jogador);

            senoide.draw();

            jogador.draw();
            jogador.acertou(elem);
            al_flip_display();
        }
        fase.move();
    }

    al_destroy_display(display);
    al_uninstall_keyboard();    
    al_destroy_timer(timer);
    al_uninstall_audio();
    al_uninstall_system();
    
    return 0;
}
