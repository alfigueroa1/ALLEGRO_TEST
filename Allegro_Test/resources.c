/***************************************************************************//**
  @file     +resources.c+
  @brief    +Contiene funciones para el manejo de la interfaz grafica+
  @author   +Grupo 2: Alejo Figueroa, Olivia de Vincenti, Pablo Gonzalez+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include "resources.h"
#include <allegro5/allegro_image.h>


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/*FALTA COMENTAR*/
int create_resources(ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **event_queue, ALLEGRO_TIMER **timer, ALLEGRO_BITMAP **display_background){
    if(!al_init()) {
	fprintf(stderr, "No se pudo inicializar Allegro\n");
	return 0;
    } 
    else if( !al_init_image_addon()){
	fprintf(stderr,"No se pudo cargar la imagen\n"); //Igual que printf pero imprime al error std 
	al_uninstall_system();
	return -1;
    }
 
    if(!al_install_keyboard()) {
	fprintf(stderr, "No se pudo inicializar el teclado\n");
	return 0;
    }
    if(!al_init_primitives_addon()){
        fprintf(stderr, "No se pudo inicializar las primitivas\n");
        return 0;
    }
    *timer = al_create_timer(1.0 / FPS);
    if(!timer) {
    	fprintf(stderr, "No se pudo crear el timer\n");
	al_shutdown_primitives_addon();
        return 0;
    }
        
    *event_queue = al_create_event_queue();
    if(!(*event_queue)) {
    	fprintf(stderr, "No se pudo crear la cola de eventos\n");
    	al_destroy_timer(*timer);
        al_shutdown_primitives_addon();
	return 0;
    }
 
    *display = al_create_display(SCREEN_W, SCREEN_H);
    if(!(*display)) {
	fprintf(stderr, "No se pudo crear el display\n");
	al_destroy_timer(*timer);
        al_shutdown_primitives_addon();
	al_destroy_event_queue(*event_queue);
	return 0;
    }
    else if( !(*display_background = al_load_bitmap("PORT_A.png")) )
	{
            fprintf(stderr,"No se pudo cargar el fondo\n"); 
            al_uninstall_system();
            al_shutdown_image_addon();
            al_destroy_display(*display);
            al_destroy_timer(*timer);
            al_shutdown_primitives_addon();
            al_destroy_event_queue(*event_queue);
            return 0;
	}

    return 1;
}

/*FALTA COMENTAR*/
void destroy_resources(ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **event_queue, ALLEGRO_TIMER **timer){
    al_shutdown_primitives_addon();
    al_destroy_timer(*timer);
    al_destroy_display(*display);
    al_destroy_event_queue(*event_queue);
    al_uninstall_system();
    al_shutdown_image_addon();
    return;
}

/*******************************************************************************
 ******************************************************************************/