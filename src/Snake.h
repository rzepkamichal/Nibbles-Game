#ifndef NIBBELS_SNAKE_H
#define NIBBELS_SNAKE_H

#include "Segment.h"
#include "List.h"
#include "AllegroIncludes.h"
#include "GameObject.h"

class Snake : public GameObject{

private:
    //lista segmentów
    List<Segment> segments;

public:
    /*Konstruktor domyślny
     *Dodaje pierwszy segment na koniec listy - głowę.
     *Do posX i posY przypisywana jest pozycja głowy lsity.
     */
    Snake();

    /*Domyślny destruktor
     */
    ~Snake() = default;

    /*Draw
     *Rysuje węża na ekranie
     */
    void Draw() override;

    /*IsBeyondBoard(int index)
     *Zwraca:
     *  - true, jeśli index-ty element listy segments jest poza obszarem gry
     *  - false - w przeciwnym razie
     */
    bool IsBeyondBoard(int index);

    /*IsBeyondBoard
     *Zwraca:
     *  - true, jeżeli głowa listy segments jest poza obszarem gry
     *  - false - w przeciwnym razie
     */
    bool IsBeyondBoard() override ;

    /*Move - przesuwa węża w kierunku dir o wartość speed.
     *W zależności od kierunku poruszania się dir,
     *do odpowiedniej współrzędnej dodaje wartość speed.
     */
    void Move(int speed, Direction dir);

    /*AddSegment - dodaje nowy obiekt na koniec listy segments
     */
    void AddSegment();

    //gettery i settery
    int getHeadPosX();
    int getHeadPosY();
    List<Segment>& getSegments();
    Segment& getHead();
    Segment& getLastSegment();
    void setHeadDir(Direction dir);


    void Move(int x, int y) override;

};

#endif
