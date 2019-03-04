#include "Obstacle.h"
#include "AllegroIncludes.h"
#include "Consts.h"

Obstacle::Obstacle() {
    this->posX = 0;
    this->posY = 0;
}

Obstacle::Obstacle(int x, int y) {

    this->posX = x;
    this->posY = y;
}

void Obstacle::setPosX(int x) {
    this->posX = x;
}

void Obstacle::setPosY(int y) {
    this->posY = y;
}

int Obstacle::getPosX() {
    return this->posX;
}

int Obstacle::getPosY() {
    return this->posY;
}

void Obstacle::Draw() {
    al_draw_filled_rectangle(this->posX,this->posY,this->posX+CELL_SIZE,this->posY+CELL_SIZE,OBSTACLE_COLOR);
}

void Obstacle::Move(int dx, int dy) {

}

bool Obstacle::IsBeyondBoard() {
    return false;
}

