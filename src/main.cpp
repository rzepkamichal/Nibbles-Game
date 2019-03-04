
#include <random>
#include <chrono>
#include <sstream>
#include "Segment.h"
#include "List.h"
#include "Game.h"

int main() {

    //ustawienie ziarna generatora liczb losowych
    srand(time(NULL));

    //ścieżka do pliku z mapą
    string filepath = "maps\\map";

    //deklaracja obiektu Gra
    Game game;

    //próba odczytu mapy
    if(game.LoadObstacleMap(filepath)){
        cout << "Wczytano mape" << endl;
    }else{
        cout << "Nie wczytano mapy" << endl;
    }

    //rozpoczęcie gry
    bool gameInitializer = game.StartGame();

    //sprawdzenie, czy inicjalizacja gry się powiodła
    if(!gameInitializer){
        cout << "A problem in game initialization has occured. Program will be closed." << endl;
    }

    return 0;
}