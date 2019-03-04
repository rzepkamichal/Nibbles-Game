#include "Segment.h"

Segment::Segment() {
    this->posX = DEFAULT_START_POS_X;
    this->posY = DEFAULT_START_POS_Y;
    this->dir = DOWN;
    this->queue = 0;
}

Segment::Segment(int x, int y, Direction dir) {

    this->posX = x;
    this->posY = y;
    this->dir = dir;
    this->queue = 0;
}

int Segment::getPosX() {
    return this->posX;
}

int Segment::getPosY() {
    return this->posY;
}

int Segment::getSize() {
    return this->size;
}

void Segment::changePosX(int dx) {

    this->posX += dx;
}

void Segment::changePosY(int dy) {

    //cout << "dy:" << dy << endl;
    //cout << posY << endl;
    this->posY += dy;
    //cout << posY << endl;
}

int Segment::getSizeMovedPosX() {
    return posX + size;
}

int Segment::getSizeMovedPosY() {
    return posY + size;
}

void Segment::setPosX(int x) {
    this->posX = x;
}

void Segment::setPosY(int y) {
    this->posY = y;
}

void Segment::setDir(Direction dir) {
    this->dir = dir;
}

Direction Segment::getDir() {
    return this->dir;
}

void Segment::IncreaseQueue(int val) {
    this->queue += val;
}

void Segment::DecrementQueue() {
    this->queue--;
}

bool Segment::QueueReleased() {
    return this->queue == 0;
}

int Segment::getQueue() {
    return this->queue;
}

Segment::~Segment() = default;
