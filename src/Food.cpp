#include "Food.h"

Food::Food() {

    this->posX = 0;
    this->posY = 0;
    this->drawNumber = 0;

}

void Food::GeneratePosition() {

    //wygenerowanie pseudolosowych pozycji
    int randX = rand()%(SCREEN_W-3*CELL_SIZE) + 2*CELL_SIZE;
    int randY = rand()%(SCREEN_H-4*CELL_SIZE) + 2*CELL_SIZE;


    if(randX%CELL_SIZE !=0 ){
        randX-= randX%CELL_SIZE;
    }

    if(randY%CELL_SIZE !=0){
        randY-= randY%CELL_SIZE;
    }
    this->posX = randX;
    this->posY = randY;

}

void Food::Draw() {
    al_draw_rectangle(posX,posY,posX+CELL_SIZE,posY+CELL_SIZE,FOOD_COLOR,4.0);
}

bool Food::IsBeyondBoard() {
    int rowIndex = (this->posY - CELL_SIZE) / CELL_SIZE;
    int colIndex = (this->posX - CELL_SIZE) / CELL_SIZE;
    return !(rowIndex >= 0 && rowIndex < ROW_NUMBER && colIndex >= 0 && colIndex < COLUMN_NUMBER);
}

void Food::Move(int dx, int dy) {

}

int Food::getPosX() {
    return this->posX;
}

int Food::getPosY() {
    return this->posY;
}

void Food::setDrawNumber(int number) {
    this->drawNumber = number;
}

int Food::getDrawNumber() {
    return this->drawNumber;
}
