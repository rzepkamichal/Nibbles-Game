#ifndef NIBBELS_SEGMENT_H
#define NIBBELS_SEGMENT_H

#include "Consts.h"
#include <iostream>
using namespace std;

enum Direction{
    //kierunek poruszania: w dół
    DOWN,
    //kierunek poruszania: w górę
    UP,
    //kierunek poruszania: w lewo
    LEFT,
    //kierunek poruszania: w prawo
    RIGHT
};
class Segment {

private:
    //pozycja na ekranie (X)
    int posX;

    //pozycja na ekranie (Y)
    int posY;

    //rozmiar
    int size = CELL_SIZE;

    //aktualny kierunek poruszania się
    Direction dir;

    //długość kolejki
    int queue;

public:
    /*Konstruktor domyślny
     *Ustawia pozyjcę na domyślną (Consts.h)
     *dir ustawiane jest na DOWN
     *queue ustaiane jest na 0
     */
    Segment();

    /*Konstruktor inicjalizujący pozycję i kierunek
     */
    Segment(int x , int y, Direction dir);

    /*Destruktor domyślny
     *
     */
    ~Segment();

    /*changePosX
     *Do posX dodaje wartość dx
     */
    void changePosX(int dx);

    /*changePosY
     *Do posY dodaje wartość dy
     */
    void changePosY(int dy);

    /*IncreaseQueue
     *Do queue dodaje wartość val
     */
    void IncreaseQueue(int val);

    /*DecrementQueue
     *Dekrementuje wartość queue
     */
    void DecrementQueue();

    /*QueueReleased
     *Zwraca:
     *  - true, jeżelie queue jest równe 0
     *  - false - w przeciwnym razie
     */
    bool QueueReleased();

    //gettery i settery
    int getPosX();
    int getPosY();
    int getSize();
    void setPosX(int x);
    void setPosY(int y);
    void setDir(Direction dir);
    Direction getDir();
    int getSizeMovedPosX();
    int getSizeMovedPosY();
    int getQueue();



};
#endif
