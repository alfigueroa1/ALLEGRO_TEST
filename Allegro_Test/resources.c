#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include "resources.h"
    
int create_resources(ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **event_queue, ALLEGRO_TIMER **timer){
    if(!al_init()) {
	fprintf(stderr, "failed to initialize allegro!\n");
	return 0;
    }
 
    if(!al_install_keyboard()) {
	fprintf(stderr, "failed to initialize the keyboard!\n");
	return 0;
    }
    if(!al_init_primitives_addon()){
        fprintf(stderr, "failed to initialize primitives!\n");
        return 0;
    }
    *timer = al_create_timer(5.0 / FPS);
    if(!timer) {
    	fprintf(stderr, "failed to create timer!\n");
	al_shutdown_primitives_addon();
        return 0;
    }
        
    *event_queue = al_create_event_queue();
    if(!(*event_queue)) {
    	fprintf(stderr, "failed to create event_queue!\n");
    	al_destroy_timer(*timer);
        al_shutdown_primitives_addon();
	return 0;
    }
 
    *display = al_create_display(SCREEN_W, SCREEN_H);
    if(!(*display)) {
	fprintf(stderr, "failed to create display!\n");
	al_destroy_timer(*timer);
        al_shutdown_primitives_addon();
	al_destroy_event_queue(*event_queue);
	return 0;
    }
    return 1;
}

void destroy_resources(ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **event_queue, ALLEGRO_TIMER **timer){
    al_shutdown_primitives_addon();
    al_destroy_timer(*timer);
    al_destroy_display(*display);
    al_destroy_event_queue(*event_queue);
    return;
}