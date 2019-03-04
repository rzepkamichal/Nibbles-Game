#ifndef NIBBELS_FOOD_H
#define NIBBELS_FOOD_H

#include <cstdlib>
#include "AllegroIncludes.h"
#include "GameObject.h"
#include "Consts.h"
#include "List.h"


class Food : public GameObject{
private:

    //aktualnie wyświetlana cyfra
    int drawNumber;


public:

    /*Konstruktor domyślny
     *Ustawia wartość wszystkich składowych na 0
     */
    Food();

    /*GeneratePosition()
     *W oparciu o funkcję rand() generowana jest pozycja
     */
    void GeneratePosition();

    /*Draw()
     *Rysuje ramkę otaczającą cyfrę na ekranie
     */
    void Draw() override;

    /*IsBeyondBoard
     *Zwraca:
     *  - true, jeżeli pozycja znajduje się poza obszarem gry
     *  - false - w przeciwnym razie
     */
    bool IsBeyondBoard() override;

    //gettery i settery
    int getPosX();
    int getPosY();
    void setDrawNumber(int number);
    int getDrawNumber();


    void Move(int dx, int dy);

};


#endif //NIBBELS_FOOD_H
