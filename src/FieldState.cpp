#include "FieldState.h"

FieldState::FieldState(){

    this->posX = 0;
    this->posY = 0;
    this->state = FREE;
}

FieldState::FieldState(int x, int y, FState state) {
    this->posX = x;
    this->posY = y;
    this->state = state;
}

int FieldState::getPosX() {
    return posX;
}

int FieldState::getPosY() {
    return posY;
}

void FieldState::setPos(int x, int y) {
    this->posX = x;
    this->posY = y;
}

void FieldState::setState(FState state) {

    this->state = state;
}

FState FieldState::getState() {
    return this->state;
}
