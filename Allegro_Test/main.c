/***************************************************************************//**
  @file     +main.c+
  @brief    +VIsualizador grafico del PORTA+
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
#define BYTE    8           //Bits en un byte
#define Q_KEY   13          //Cantidad de teclas a tener en cuenta.
#define X0  142             //Punto inicial desde el que se dibuja el puerto.
#define SEPARATION  51      //Separacion entre cada LED.
#define RADIUS  10          //Radio de cada LED.

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static void draw_port();
static void hide_port();
/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

int main(void) {
    //Declaracion de recursos utilizados.
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *display_background = NULL;
    //Variables para el manejo del parpadeo.
    int blynk = 0;
    int blynk_state = -1;
    //Flags para la FSM.
    bool key_pressed[Q_KEY] = { true, true, true, true, true, true, true,
                             true, true, true, true, true, true}; //Estado de teclas, true cuando esta apretada
    bool redraw = false;
    bool do_exit = false;
    
    
    if(!create_resources(&display, &event_queue, &timer, &display_background))
        return -1;  //Se crean los recursos necesarios y se termina el programa si hay fallos.
    
    
    al_set_target_bitmap(al_get_backbuffer(display));   //Se trabajan los dibujos sobre el display.
    al_clear_to_color(al_map_rgb(255, 255, 255));
    
     
    al_register_event_source(event_queue, al_get_display_event_source(display));    //Se registra el display
    al_register_event_source(event_queue, al_get_timer_event_source(timer));        //Se registra el timer
    al_register_event_source(event_queue, al_get_keyboard_event_source());          //Se registra el teclado

    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_scaled_bitmap(display_background,
					0,0, al_get_bitmap_width(display_background),al_get_bitmap_height(display_background), //imagen
					0,0,al_get_display_width(display),al_get_display_height(display), //a que tamaño queres que se dibuje la imagen
					0); //Se carga el fondo.
    
    al_flip_display();          //Se dibuja por primera vez el display.
    al_start_timer(timer);      //Se inicia el timer.
    
    while(!do_exit)     //Se repite la FSM mientras no se pida salir del programa.
	{
		ALLEGRO_EVENT ev;
		if( al_get_next_event(event_queue, &ev) ) //Toma un evento de la cola.
		{ 
			if(ev.type == ALLEGRO_EVENT_TIMER) 
			{
				if(key_pressed[KEY_Q]) 
                                    al_clear_to_color(al_map_rgb(0,0,0));
                                if(blynk_state == 1){           //Se cambia el estado del parpadeo cada segundo.
                                    blynk ++;   
                                    if(blynk == 100){
                                        blynk = 0;
                                        blynk_state = 2;
                                    }
                                }
                                else if(blynk_state == 2){      //Se cambia el estado del parpadeo cada segundo.
                                    blynk ++;   
                                    if(blynk == 100){
                                        blynk = 0;
                                        blynk_state = 1;
                                    }
                                }
				redraw = true;      //Cada vez que se detecte el evento del timer, se vuelve a dibujar el display
			}

			else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
				do_exit = true;                     //Si se cierra el display, el programa termina.

			else if(ev.type == ALLEGRO_EVENT_KEY_DOWN)  //Cuando se presiona una tecla, se activa su funcion.
			{                                           //Siempre que no se registre multiples veces.
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
                       
			else if(ev.type == ALLEGRO_EVENT_KEY_UP)    //Si se suelta alguna tecla.
			{                                           //Se refrescan los flags de las teclas.
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
 
		if(redraw && al_is_event_queue_empty(event_queue))  //Cuando no hay mas eventos para resolver.
		{                                                   //Se dibuja el display 60 veces por segundo.
			redraw = false;                             //SE deshabilita el flag para volver a dibujar.
                        al_clear_to_color(al_map_rgb(255, 255, 255));
                        al_draw_scaled_bitmap(display_background,   //Se coloca la imagen de fondo.
					0,0, al_get_bitmap_width(display_background),al_get_bitmap_height(display_background),
					0,0,al_get_display_width(display),al_get_display_height(display),
					0);
                        if(blynk_state == 1)                        //Si el sistema esta parpadeando.
                            hide_port();                            //Se esconde el puerto.
                        else
                            draw_port();                            //Si no, se lo muestra.
                        
			al_flip_display();                          //Se refresca el display.
		}
	}
    
    destroy_resources(&display, &event_queue, &timer, &display_background);       //Cuando se sale del programa, se destruyen los recursos usados.
    return (EXIT_SUCCESS);
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/*Esta funcion no toma ningun parametro de entrada
  Imprime en el bitmap el puerto A tal y como esta guardado.*/
static void draw_port(){
    int i;
    for(i = 0; i < BYTE; i++){              //Se itera por el puerto.
        if(bitGet('A', i)){                 //Se analiza el bit y se lo muestra rojo si esta prendido.
            al_draw_filled_circle(X0 + (i*SEPARATION),SCREEN_H/2,RADIUS, al_map_rgb(255,0,0));
        }
        else{                               //Si esta apagado, se lo pinta de negro.
            al_draw_filled_circle(X0 + (i*SEPARATION),SCREEN_H/2,RADIUS, al_map_rgb(0,0,0));
        }
    }
}

/*Esta funcion no toma ningun parametro de entrada
  Imprime en el bitmap el puerto A apagado*/
static void hide_port(){
    int i;
    for(i = 0; i < BYTE; i++){
        al_draw_filled_circle(X0 + (i*SEPARATION),SCREEN_H/2,RADIUS, al_map_rgb(0,0,0));
    }
}

/*******************************************************************************
 ******************************************************************************/