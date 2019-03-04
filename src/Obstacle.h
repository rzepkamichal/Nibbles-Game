#ifndef NIBBELS_OBSTACLE_H
#define NIBBELS_OBSTACLE_H

#include <string>
#include <fstream>
#include "GameObject.h"
#include "Obstacle.h"
#include "AllegroIncludes.h"

class Obstacle : GameObject {

public:

    /*Konstruktor domyślny
     *Ustawia wartości składowych na 0
     */
    Obstacle();

    /*Konstruktor inicjalizujący pola posX i posY odpowiednio parametrami x i y.
     */
    Obstacle(int x, int y);

    /*Draw()
     *Rysuje przeszkode na ekranie gry.
     */
    void Draw() override;

    //gettery i settery
    void setPosX(int x);
    void setPosY(int y);
    int getPosX();
    int getPosY();


    void Move(int dx, int dy) override;
    bool IsBeyondBoard() override;

};


#endif //NIBBELS_OBSTACLE_H
