/***************************************************************************//**
  @file     +resources.h+
  @brief    +Contiene funciones para el manejo de la interfaz grafica+
  @author   +Grupo 2: Alejo Figueroa, Olivia de Vincenti, Pablo Gonzalez+
 ******************************************************************************/

#ifndef RESOURCES_H
#define RESOURCES_H

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define FPS                     60.0        //Velocidad del parpadeo
#define SCREEN_W		640         //Ancho de la pantalla
#define SCREEN_H		480         //Altura de la pantalla

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
enum MYKEYS {
	KEY_Q, KEY_C, KEY_S, KEY_T, KEY_B, KEY_0, KEY_1, KEY_2, KEY_3,
        KEY_4, KEY_5, KEY_6, KEY_7          //teclas
};

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/*FALTA COMENTAR*/
int create_resources(ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **event_queue, ALLEGRO_TIMER **timer, ALLEGRO_BITMAP **display_background);

/*FALTA COMENTAR*/
void destroy_resources(ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **event_queue, ALLEGRO_TIMER **timer);

#endif /* RESOURCES_H */

