#ifndef NIBBELS_GAME_H
#define NIBBELS_GAME_H

#include <unistd.h>
#include <sstream>
#include <fstream>
#include <string>
#include "Obstacle.h"
#include "List.h"
#include "Snake.h"
#include "AllegroIncludes.h"
#include "FieldState.h"
#include "Food.h"

class Game {

private:

    //wskaźnikn na tablicę dynamiczną przechowującą stany pól gry
    FieldState** fieldStates;

    //obiekt reprezentujący węża w grze
    Snake snake;

    //obiekt reprezuntujący aktualnie wyświetlaną cyfrę
    Food food;

    //bufor znakowy służący do wypisywania kolejnych cyfr
    char buff[2];

    //lista obiektów reprezentująca poszczególne przeszkody rozlokowane na mapie
    List<Obstacle> obstacles;

    //flaga informująca o tym, czy pętla gry powinna zostać przerwana
    bool gameLoop;

public:

    /* Konstruktor domyślny
     * Alokuje pamięć dla tablicy fieldStates w zależności od liczby kolumn i wierszy (Consts.h)
     * Ustawia flagę gameLoop na true;
     */
    Game();

    /* Destruktor domyślny
     * Dealokuje pamięć tablicy fieldStates
     */
    ~Game();

    /*InsertFood -
     */
    void InsertFood();

    /*EatFood - obsługuje operację "zjedzenia" cyfry
     *Inkrementuje liczbę drawNumber w obiekcie food.
     *Do węża dodawana jest określona liczba segmentów.
     *(Współczynnik określony w Consts.h przemnożony przez drawNumber).
     *Dla nowych segmentów ustalana jest kolejka, tak żeby na ekranie pojawiały się one stopniowo.
     *Aktualizowany jest stan tablicy fieldStates.
     */
    void EatFood();

    /*UnmarkSnakeFromBoard - odznacza węża z tablicy fieldStates.
     *Elementy tablicy, których wartość jest równa SNAKE zostaje zamieniona na FREE.
     */
    void UnmarkSnakeFromBoard();

    /*DrawBorders
     *Rysuje ramkę stanowiącą granicę obszaru gry.
     */
    void DrawBorders();

    /*LoadObstacleMap - wczytuje mapę przeszkód.
     *Otwiera plik o ścieżce wskazanej przez parametr filename.
     *Z pliku wczytywane są kolejne elementy macierzy..
     *Jeżeli wczytana jest 1 - odpowiednie pole w fieldStates ustawiane jest na OBSTACLE.
     *Jeżeli wczytane jest 0 - opowiednie pole w fieldStates ustawiane jest na FREE.
     *Jeżeli nie powiedzie się otwarcie pliku lub odczytany zostanie niepoprawny znak, funkcja zwaraca false.
     *W przeciwnym przypadku zwraca true.
     */
    bool LoadObstacleMap(std::string &filename);

    /*PlayGameEvent - analizuje pozycję po wykonaniu ruchu węża, lecz przed narysowaniem.
     *Przed narysowaniem węża na ekranie sprawdzana jest jego pozycja.
     *Jeżeli "zjedzona" została ostatnia cyfra, przerywana jest pętla gry.
     *Aktualizowany jest stan tablicy fieldStates.
     *Jeżeli w tablicy fieldStates, w elemencie odpowiadającym pozycji głowy węża:
     * - jest stan SNAKE - przerywana jest pętla gry,
     * - jest stan FREE - stan elementu zmieniany jest na SNAKE.
     * - jest stan OBSTACLE - przerywana jest pętla gry,
     * - jest stan FOOD - wywoływana jest funkcja EatFood,
     */
    void PlayGameEvent();

    /*StartGame - obsługuje przebieg gry
     *Na początku inicjalizowana jest biblioteka Allegro.
     *Następnie w pętli  wyświetlane jest menu powitalne.
     *Po wciśnięciu dowolnego klawisza w pętli wyświetlane są kolejne klatki gry.
     *Pętla gry iteruje, dopóki zmienna gameLoop przechowuje wartość true.
     *Z kolejki zdarzeń event_queue odczytywane są kolejne zdarzenia klawiatury.
     *W zależności zdarzenia ustawiana jest zmienna dir reprezentująca kierunek.
     *W zależności od zmiennej dir jest ustawiany kierunek ruchu głowy węża.
     *Następnie aktualizowana jest pozycja każdego segmentu budującego węża.
     *Wywoływana jest funkcja PlayGameEvent analizująca nową pozycję węża.
     *Następnie na rzecz obiektów snake, food, obstacles wywoływana jest funkcja Draw.
     *Wywoływana jest też funkcja DrawBorders oraz funkcja wstawiająca tekst (cyfrę) w odpowiednie miesjce.
     *Jeżeli za sprawą funkcji PlayGameEvent wartość gameLoop została zmieniona
     *na false, wyświetlone zostaje menu pożegnalne, pętla programu jest przerywana.
     *Aktualizacja zmiennej dir odbywa się w chwilach czasu generowanych przez obiekt timer.
     *Wykonanie ruchu węża odbywa się w chwilach czasu generowanych przez obiekt frameTimer.
     */
    bool StartGame();
};


#endif //NIBBELS_GAME_H
