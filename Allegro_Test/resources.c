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

/*Esta funcion toma como parametros los recursos utilizados en el programa, los crea, y destruye todo si no puede crearse algo*/
int create_resources(ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **event_queue, ALLEGRO_TIMER **timer, ALLEGRO_BITMAP **display_background){
    if(!al_init()) {
	fprintf(stderr, "No se pudo inicializar Allegro\n");
	return 0;
    } 
    if( !al_init_image_addon()){            //Se inicializa el agregado de imagenes.
	fprintf(stderr,"No se pudo cargar la imagen\n"); //Igual que printf pero imprime al error std 
	al_uninstall_system();
	return -1;
    }
 
    if(!al_install_keyboard()) {            //Se instala el teclado.
	fprintf(stderr, "No se pudo inicializar el teclado\n");
	return 0;
    }
    if(!al_init_primitives_addon()){        //Se inicializa el agregado de primitivas.
        fprintf(stderr, "No se pudo inicializar las primitivas\n");
        return 0;
    }
    *timer = al_create_timer(1.0 / FPS);    //El timer se usa para dibujar periodicamente el display y seguir el tiempo.
    if(!timer) {                        //Se crea el timer y se destruyen los otros recursos de no poder ser creado.
    	fprintf(stderr, "No se pudo crear el timer\n");
	al_shutdown_primitives_addon();
        return 0;
    }
        
    *event_queue = al_create_event_queue();
    if(!(*event_queue)) {              //Se crea la cola de eventos y se destruyen los otros recursos de no poder ser creado.
    	fprintf(stderr, "No se pudo crear la cola de eventos\n");
    	al_destroy_timer(*timer);
        al_shutdown_primitives_addon();
	return 0;
    }
 
    *display = al_create_display(SCREEN_W, SCREEN_H);
    if(!(*display)) {                   //Se crea el display y se destruyen los otros recursos de no poder ser creado.
	fprintf(stderr, "No se pudo crear el display\n");
	al_destroy_timer(*timer);
        al_shutdown_primitives_addon();
	al_destroy_event_queue(*event_queue);
	return 0;
    }
    *display_background = al_load_bitmap("PORT_A.png"); //Se asigna la imagen PORT_A.jpg a display_background.
    if( !(*display_background) )        //Se crea el fondo y se destruyen los otros recursos de no poder ser creado.
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

/*Esta funcion toma como parametros los recursos utilizados en el programa, los crea, y destruye todo si no puede crearse algo*/
void destroy_resources(ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **event_queue, ALLEGRO_TIMER **timer, ALLEGRO_BITMAP **display_background){
    al_uninstall_system();
    al_shutdown_image_addon();
    al_shutdown_primitives_addon();
    al_destroy_timer(*timer);
    al_destroy_event_queue(*event_queue);
    al_destroy_display(*display);
    al_destroy_bitmap(*display_background);
    return;
}

/*******************************************************************************
 ******************************************************************************/