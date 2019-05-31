/***************************************************************************//**
  @file     +main.c+
  @brief    +FALTA COMENTAR+
  @author   +Grupo 2: Alejo Figueroa, Olivia de Vincenti, Pablo Gonzalez+
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "resources.h"
#include "funbits.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define BYTE    8
#define Q_KEY   13
#define X0  142
#define SEPARATION  51
#define RADIUS  10

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static void draw_port();
static void hide_port();

/*
 * 
 */

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/*FALTA COMENTAR*/
int main(void) {
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *display_background;
    
    int blynk = 0;
    int blynk_state = -1;
    
    bool key_pressed[Q_KEY] = { true, true, true, true, true, true, true,
                             true, true, true, true, true, true}; //Estado de teclas, true cuando esta apretada
    bool redraw = false;
    bool do_exit = false;
    
    
    if(!create_resources(&display, &event_queue, &timer, &display_background))
        return -1;
    
    
    al_set_target_bitmap(al_get_backbuffer(display));
    al_clear_to_color(al_map_rgb(255, 255, 255));
    
     
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source()); //REGISTRAMOS EL TECLADO

    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_scaled_bitmap(display_background,
					0,0, al_get_bitmap_width(display_background),al_get_bitmap_height(display_background), //imagen
					0,0,al_get_display_width(display),al_get_display_height(display), //a que tamaño queres que se dibuje la imagen
					0); //SIn flags podrian usar ALLEGRO_FLIP_HORIZONTAL o ALLEGRO_FLIP_VERTICAL muy utiles

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
                                if(blynk_state == 1){
                                    blynk ++;   
                                    if(blynk == 60){
                                        blynk = 0;
                                        blynk_state = 2;
                                    }
                                }
                                else if(blynk_state == 2){
                                    blynk ++;   
                                    if(blynk == 60){
                                        blynk = 0;
                                        blynk_state = 1;
                                    }
                                }
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
						if(key_pressed[KEY_C]){
                                                    maskOff('A', 0xFF);  key_pressed[KEY_C] = false;}
						break;
					case ALLEGRO_KEY_S: 
						if(key_pressed[KEY_S]){
                                                    maskOn('A', 0xFF);  key_pressed[KEY_S] = false;}
						break;
					case ALLEGRO_KEY_T:
						if(key_pressed[KEY_T]){
                                                    maskToggle('A', 0xFF);  key_pressed[KEY_T] = false;}
						break;
                                        case ALLEGRO_KEY_B:
						if(key_pressed[KEY_B]){
                                                    if(blynk_state == -1)
                                                        blynk_state = 1;
                                                    else
                                                        blynk_state = -1;
                                                    key_pressed[KEY_B] = false;
						}
                                                break;
                                        case ALLEGRO_KEY_0:
						if(key_pressed[KEY_0]){
                                                    bitToggle('A', 0);  key_pressed[KEY_0] = false;}
						break;
                                        case ALLEGRO_KEY_1:
						if(key_pressed[KEY_1]){
                                                    bitToggle('A', 1);  key_pressed[KEY_1] = false;}
						break;
                                        case ALLEGRO_KEY_2:
						if(key_pressed[KEY_2]){
                                                    bitToggle('A', 2);  key_pressed[KEY_2] = false;}
						break;
                                        case ALLEGRO_KEY_3:
						if(key_pressed[KEY_3]){
                                                    bitToggle('A', 3);  key_pressed[KEY_3] = false;}
						break;;
                                        case ALLEGRO_KEY_4:
						if(key_pressed[KEY_4]){
                                                    bitToggle('A', 4);  key_pressed[KEY_4] = false;}
						break;
                                        case ALLEGRO_KEY_5:
						if(key_pressed[KEY_5]){
                                                    bitToggle('A', 5);  key_pressed[KEY_5] = false;}
						break;
                                        case ALLEGRO_KEY_6:
						if(key_pressed[KEY_6]){
                                                    bitToggle('A', 6);  key_pressed[KEY_6] = false;}
						break;
                                        case ALLEGRO_KEY_7:
						if(key_pressed[KEY_7]){
                                                    bitToggle('A', 7);  key_pressed[KEY_7] = false;}
						break;
				}
			}
                       
			else if(ev.type == ALLEGRO_EVENT_KEY_UP) 
			{
				switch(ev.keyboard.keycode) {

					case ALLEGRO_KEY_C:
						key_pressed[KEY_C] = true;
						break;
					case ALLEGRO_KEY_S: 
						key_pressed[KEY_S] = true;
						break;
					case ALLEGRO_KEY_T:
						key_pressed[KEY_T] = true;
						break;
					case ALLEGRO_KEY_Q:
						do_exit = true;
						break;
                                        case ALLEGRO_KEY_B:
						key_pressed[KEY_B] = true;
						break;
                                        case ALLEGRO_KEY_0:
						key_pressed[KEY_0] = true;
						break;
                                        case ALLEGRO_KEY_1:
						key_pressed[KEY_1] = true;
						break;
                                        case ALLEGRO_KEY_2:
						key_pressed[KEY_2] = true;
						break;
                                        case ALLEGRO_KEY_3:
						key_pressed[KEY_3] = true;
						break;
                                        case ALLEGRO_KEY_4:
						key_pressed[KEY_4] = true;
						break;
                                        case ALLEGRO_KEY_5:
						key_pressed[KEY_5] = true;
						break;
                                        case ALLEGRO_KEY_6:
						key_pressed[KEY_6] = true;
						break;
                                        case ALLEGRO_KEY_7:
						key_pressed[KEY_7] = true;
						break;
				}
			}
		}
 
		if(redraw && al_is_event_queue_empty(event_queue)) 
		{  
			redraw = false;
                        al_clear_to_color(al_map_rgb(255, 255, 255));
                        al_draw_scaled_bitmap(display_background,
					0,0, al_get_bitmap_width(display_background),al_get_bitmap_height(display_background), //imagen
					0,0,al_get_display_width(display),al_get_display_height(display), //a que tamaño queres que se dibuje la imagen
					0);
                        if(blynk_state == 1)
                            hide_port();
                        else
                            draw_port();
                        
			al_flip_display();
		}
	}
    
    destroy_resources(&display, &event_queue,&timer);
    return (EXIT_SUCCESS);
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/*FALTA COMENTAR Y PERDI*/
static void draw_port(){
    int i;
    for(i = 0; i < BYTE; i++){
        if(bitGet('A', i)){
            al_draw_filled_circle(X0 + (i*SEPARATION),SCREEN_H/2,RADIUS, al_map_rgb(255,0,0));
        }
        else{
            al_draw_filled_circle(X0 + (i*SEPARATION),SCREEN_H/2,RADIUS, al_map_rgb(0,0,0));
        }
    }
}

/*FALTA COMENTAR*/
static void hide_port(){
    int i;
    for(i = 0; i < BYTE; i++){
        al_draw_filled_circle(X0 + (i*SEPARATION),SCREEN_H/2,RADIUS, al_map_rgb(0,0,0));
    }
}

/*******************************************************************************
 ******************************************************************************/