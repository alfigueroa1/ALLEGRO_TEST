#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "resources.h"
#include "funbits.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>

#define BYTE    8

static void draw_port();
/*
 * 
 */
int main(void) {
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *cuadradito = NULL;
    bool key_pressed[4] = { false, false, false, false }; //Estado de teclas, true cuando esta apretada
    bool redraw = false;
    bool do_exit = false;
    
    
    if(!create_resources(&display, &event_queue, &timer))
        return -1;
    
    al_clear_to_color(al_map_rgb(255, 0, 255));
    al_set_target_bitmap(al_get_backbuffer(display));
  
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source()); //REGISTRAMOS EL TECLADO

    al_clear_to_color(al_map_rgb(0,255,0));
    al_flip_display();
    al_start_timer(timer);
    
    while(!do_exit)
	{
		ALLEGRO_EVENT ev;
		if( al_get_next_event(event_queue, &ev) ) //Toma un evento de la cola, VER RETURN EN DOCUMENT.
		{ 
			if(ev.type == ALLEGRO_EVENT_TIMER) 
			{
				if(key_pressed[KEY_Q]) 
                                    al_clear_to_color(al_map_rgb(0,0,0));
                                
				if(key_pressed[KEY_C])
                                    maskOff('A', 0xFF);
                                
				if(key_pressed[KEY_S]) 
                                    maskOn('A', 0xFF);
                                
				if(key_pressed[KEY_T]) 
                                    maskToggle('A', 0xFF);

				redraw = true;
			}

			else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
				do_exit = true;

			else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) 
			{
				switch(ev.keyboard.keycode){
					case ALLEGRO_KEY_Q:
						key_pressed[KEY_Q] = true;
						break;

					case ALLEGRO_KEY_C:
						key_pressed[KEY_C] = true;
						break;

					case ALLEGRO_KEY_S: 
						key_pressed[KEY_S] = true;
						break;

					case ALLEGRO_KEY_T:
						key_pressed[KEY_T] = true;
						break;
				}
			}

			else if(ev.type == ALLEGRO_EVENT_KEY_UP) 
			{
				switch(ev.keyboard.keycode) {

					case ALLEGRO_KEY_C:
						key_pressed[KEY_C] = false;
						break;

					case ALLEGRO_KEY_S: 
						key_pressed[KEY_S] = false;
						break;

					case ALLEGRO_KEY_T:
						key_pressed[KEY_T] = false;
						break;

					case ALLEGRO_KEY_Q:
						do_exit = true;
						break;
				}
			}
		}
 
		if(redraw && al_is_event_queue_empty(event_queue)) 
		{  
			redraw = false;
                        draw_port();
			al_flip_display();
		}
	}
    
    destroy_resources(&display, &event_queue,&timer);
    return (EXIT_SUCCESS);
}

void draw_port(){
    int i;
    for(i = 0; i < BYTE; i++){
        if(bitGet('A', i)){
            al_draw_filled_circle(50 + (i*30),200,10, al_map_rgb(255,255,255));
        }
        else{
            al_draw_filled_circle(50 + (i*30),200,10, al_map_rgb(0,0,0));
        }
    }
}