#ifndef NIBBELS_FIELDSTATE_H
#define NIBBELS_FIELDSTATE_H

/*enum FState - reprezentuje stan pojedynczego pola gry
 * FREE - Wolne
 * FOOD - Znajduje się na nim cyfra
 * SNAKE - Znajduje się na nim segment węża
 * OBSTACLE - Znajduje się na nim przeszkoda
 */
enum FState{
    //stan pola: wolne
    FREE,
    //stan pola: zajęte przez cyfę
    FOOD,
    //stan pola: zajęte przez węża
    SNAKE,
    //stan pola: zajęte przez przeszkodę
    OBSTACLE
};
class FieldState {
private:

    //pozycja pola na ekranie (X)
    int posX;

    //pozycja pola na ekranie (Y)
    int posY;

    //stan pola
    FState state;

public:

    /*Konstruktur domyślny
     *Przypisuje wszystkim składowym typu int wartość zero.
     *Składowej typu FState przypisuje wartość FREE
     */
    FieldState();

    /*Konstruktor inicjalizujący pola za pomocą parametrów

     */
    FieldState(int x, int y, FState state);

    //gettery i settery
    void setPos(int x, int y);
    void setState(FState state);
    int getPosX();
    int getPosY();
    FState getState();
};


#endif //NIBBELS_FIELDSTATE_H
