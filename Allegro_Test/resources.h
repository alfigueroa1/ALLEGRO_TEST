/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   resources.h
 * Author: ale
 *
 * Created on May 29, 2019, 12:50 PM
 */

#ifndef RESOURCES_H
#define RESOURCES_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#define FPS				60.0
#define SCREEN_W		640
#define SCREEN_H		480
#define CUADRADITO_SIZE	32
#define MOVE_RATE		4.0


enum MYKEYS {
	KEY_Q, KEY_C, KEY_S, KEY_T, KEY_B, KEY_0, KEY_1, KEY_2, KEY_3,
        KEY_4, KEY_5, KEY_6, KEY_7//arrow keys
};
int create_resources(ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **event_queue, ALLEGRO_TIMER **timer);
void destroy_resources(ALLEGRO_DISPLAY **display, ALLEGRO_EVENT_QUEUE **event_queue, ALLEGRO_TIMER **timer);

#endif /* RESOURCES_H */

