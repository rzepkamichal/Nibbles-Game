#ifndef NIBBELS_GAMEOBJECT_H
#define NIBBELS_GAMEOBJECT_H


class GameObject {
protected:

    //pozycja obiektu na mapie (X)
    int posX;

    //pozycja na obiektu mapie (Y)
    int posY;
public:

    /*domyślny konstruktor
     */
    GameObject();

    /*Draw
     *Rysuje obiekt na ekranie.
     */
    virtual void Draw() = 0;

    /*Move
     *Dodaje wartości dx i dy do PosX i PosY
     */
    virtual void Move(int dx, int dy) = 0;

    /*IsBeyondBoard
     *Zwraca:
     *  - true, jeżeli pozycja obiektu znajduje się poza obszarem gry
     *  - false, jeżeli pozycja obiektu znajduje się w obrębie obszaru gry
     */
    virtual bool IsBeyondBoard() = 0;
};


#endif //NIBBELS_GAMEOBJECT_H
