#include "Snake.h"

Snake::Snake() {
    segments.PushBack(Segment());
    posX = segments.getNode(0).getPosX();
    posY = segments.getNode(0).getPosY();
}

void Snake::Draw() {
    //rysowanie glowy
    al_draw_filled_rounded_rectangle(segments.getNode(0).getPosX(),segments.getNode(0).getPosY(),segments.getNode(0).getSizeMovedPosX(),segments.getNode(0).getSizeMovedPosY(),8.0,5.0,HEAD_COLOR);

    //rysowanie pozostalych segmentow
    for(int i=1; i<segments.getSize();i++){

        //rysowanie odbywa sie tylko, jezeli nowo dodany segment nie jest poza obszarem mapy
        if(!IsBeyondBoard(i)) {
            if(segments.getNode(i).QueueReleased()) {
                al_draw_filled_rounded_rectangle(segments.getNode(i).getPosX(), segments.getNode(i).getPosY(),
                                                 segments.getNode(i).getSizeMovedPosX(),
                                                 segments.getNode(i).getSizeMovedPosY(), 10.0, 10.0, TAIL_COLOR);
            }
        }
    }

}

void Snake::Move(int speed, Direction dir) {


    //zapamietanie poprzedniej pozycji i kierunku poruszania sie glowy
    int prevPosX = segments.getNode(0).getPosX();
    int prevPosY = segments.getNode(0).getPosY();
    Direction prevDir = segments.getNode(0).getDir();

    //ustalenie nowej pozycji glowy w zaleznosci od kierunku poruszania sie
    switch (prevDir) {
        case DOWN:
            segments.getNode(0).changePosY(speed);
            break;
        case UP:
            segments.getNode(0).changePosY(-speed);

            break;
        case LEFT:
            segments.getNode(0).changePosX(-speed);
            break;
        case RIGHT:
            segments.getNode(0).changePosX(speed);

            break;
        default:
            break;
    }

    //zmienne pomocnicze do zapamietywania poprzednich pozycji i kierunku segmentow
    int tmpX, tmpY;
    Direction tmpDir;

    //zmienna przechowuje indeks segmentu narysowanego jako ostatniego
    int lastDrawnIndex = 0;

    //aktualizacja pozycji pozostalych segmentow
    for(int i = 1; i < segments.getSize(); i++){

        //aktualizacja odbya sie tylko, jezeli poszczegolne segmenty maja zerowa kolejke
        if(segments.getNode(i).QueueReleased()) {
            //przypisanie kolejnym segmentom pozycji i kierunku poprzedniego
            lastDrawnIndex = i;
            tmpX = segments.getNode(i).getPosX();
            tmpY = segments.getNode(i).getPosY();
            tmpDir = segments.getNode(i).getDir();
            segments.getNode(i).setPosX(prevPosX);
            segments.getNode(i).setPosY(prevPosY);
            segments.getNode(i).setDir(prevDir);
            prevPosX = tmpX;
            prevPosY = tmpY;
            prevDir = tmpDir;

        }else{
            //jezeli segment jest w kolejce, to otrzymuje pozycje od ostatniego narysowanego segmentu
            //kolejka jest dekrementowana
            segments.getNode(i).setPosX(segments.getNode(lastDrawnIndex).getPosX());
            segments.getNode(i).setPosY(segments.getNode(lastDrawnIndex).getPosY());
            segments.getNode(i).DecrementQueue();
        }
    }

    //ustawienie poprawnej pozycji glowy
    posX = segments.getNode(0).getPosX();
    posY = segments.getNode(0).getPosY();
}

void Snake::AddSegment() {

    //przypisanie do zmiennych pozycji i kierunku ostatniego segmentu
    int lastSegmentPosX = segments.getLast().getPosX();
    int lastSegmentPosY = segments.getLast().getPosY();
    Direction lastSegmentDir = segments.getLast().getDir();

    //dodanie nowego segmentu do listy
    //nowy semgment otrzymuje kierunek zgodny z ostatnim segmentem
    //w zaleznosci od kierunku i pozycji ostatniego segmenta dodawana jest wartosc rozmiaru segmentu
    //nastepnie jest przypisywana do nowego segmentu
    switch(lastSegmentDir){
        case DOWN:
            segments.PushBack(Segment(lastSegmentPosX,lastSegmentPosY-CELL_SIZE,lastSegmentDir));
            break;
        case UP:
            segments.PushBack(Segment(lastSegmentPosX,lastSegmentPosY+CELL_SIZE,lastSegmentDir));
            break;
        case LEFT:
            segments.PushBack(Segment(lastSegmentPosX+CELL_SIZE,lastSegmentPosY,lastSegmentDir));
            break;
        case RIGHT:
            segments.PushBack(Segment(lastSegmentPosX-CELL_SIZE,lastSegmentPosY,lastSegmentDir));
            break;
        default:
            break;
    }

}

int Snake::getHeadPosX() {
   return posX;
}

int Snake::getHeadPosY() {
    return posY;
}

void Snake::Move(int x, int y) {

}

List<Segment> &Snake::getSegments() {
    return this->segments;
}

bool Snake::IsBeyondBoard(int index) {

    int rowIndex = (segments.getNode(index).getPosY() - CELL_SIZE) / CELL_SIZE;
    int colIndex = (segments.getNode(index).getPosX() - CELL_SIZE) / CELL_SIZE;

    return !(rowIndex >= 0 && rowIndex < ROW_NUMBER && colIndex >= 0 && colIndex < COLUMN_NUMBER);
}

bool Snake::IsBeyondBoard() {
    int rowIndex = (posY - CELL_SIZE) / CELL_SIZE;
    int colIndex = (posX - CELL_SIZE) / CELL_SIZE;

    return rowIndex < 0 || rowIndex > ROW_NUMBER -1 || colIndex < 0 || colIndex > COLUMN_NUMBER -1;
}

Segment &Snake::getHead() {
    return segments.getNode(0);
}

void Snake::setHeadDir(Direction dir) {
    this->getHead().setDir(dir);
}

Segment &Snake::getLastSegment() {
    return segments.getLast();
}
