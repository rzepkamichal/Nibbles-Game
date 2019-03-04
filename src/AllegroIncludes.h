#ifndef NIBBELS_ALLEGROINCLUDES_H
#define NIBBELS_ALLEGROINCLUDES_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

//kolor czarny
#define BLACK al_map_rgb(0,0,0)

//kolor ogona węża
#define TAIL_COLOR al_map_rgb(30,144,255)

//kolor głowy węża
#define HEAD_COLOR al_map_rgb(230,70,70)

//kolor obramowania cyfry
#define FOOD_COLOR al_map_rgb(255,255,0)

//kolor granic mapy
#define BORDER_COLOR al_map_rgb(75,0,130)

//kolor przeszkody
#define OBSTACLE_COLOR al_map_rgb(50,180,50)
#endif
