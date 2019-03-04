#ifndef NIBBELS_CONSTS_H
#define NIBBELS_CONSTS_H


//szerokość ekranu gry
#define SCREEN_W 1160

//wysokość ekranu gry
#define SCREEN_H 640

//rozmiary pojedynczego pola (koniecznie dzielnik SCREEN_W i SCREEN_H)
#define CELL_SIZE 20

//stała pomocnicza, określa liczbę kolumn o szerokości pojedynczego pola
#define COLUMN_NUMBER ((SCREEN_W-2*CELL_SIZE)/CELL_SIZE) // 56

//stała pomocnicza, okresla liczbę wierszy o wysokości pojedynczego pola
#define ROW_NUMBER ((SCREEN_H - 2*CELL_SIZE )/CELL_SIZE) // 30

//domyślna współrzędna startowa Y węża
#define DEFAULT_START_POS_Y (SCREEN_H/2 - CELL_SIZE)

//domyślna współrzędna startowa X węża
#define DEFAULT_START_POS_X (SCREEN_W/2 - CELL_SIZE)

//współczynnik dodawania segmentów - mnoży się przez niego zinkrementowaną wartość "zjedzonej"
#define SEGMENT_ADD_COEFF 4

//liczba klatek na sekundę
#define FPS 60

//szybkość poruszania się węża
#define SPEED 10

//ograniczenie górne wartości zjadanych cyfr
#define MAX_FOOD_NUMBER 9

#endif //NIBBELS_CONSTS_H
