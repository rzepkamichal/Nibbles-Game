#include "Game.h"

Game::Game()  {

    //stworzenie dwuwymiarowej tablicy dynamicznej
    fieldStates = new FieldState*[ROW_NUMBER];

    for(int i = 0; i < ROW_NUMBER; i++){
        fieldStates[i] = new FieldState[COLUMN_NUMBER];
    }

    //inicjalizacja wartosci tablicy
    for(int i = 0; i < ROW_NUMBER; i++){
        for(int j = 0; j < COLUMN_NUMBER; j++){
            fieldStates[i][j].setPos((i+1)*CELL_SIZE,(j+1)*CELL_SIZE);
            fieldStates[i][j].setState(FREE);
        }
    }

    //otwarcie petli gry
    gameLoop = true;
}

void Game::UnmarkSnakeFromBoard() {

    //przypisanie wszystkim stanom SNAKE stanu FREE
    for(int i = 0; i < ROW_NUMBER; i++){
        for(int j = 0; j < COLUMN_NUMBER; j++){
            if(fieldStates[i][j].getState() == SNAKE){
                fieldStates[i][j].setState(FREE);
            }
        }
    }
}

void Game::InsertFood() {

    //zmienne pomocnicze na przechowanie pozycji
    int rowIndex;
    int colIndex;

    //flaga informujaca, czy dana pozycja na mapie jest wolna
    bool posIsFree = false;

    //petla iteruje, dopoki nie wygeneruje sie wolna pozycja
    while(!posIsFree) {

        //generowanie pozycji
        food.GeneratePosition();
        rowIndex = (food.getPosY() - CELL_SIZE) / CELL_SIZE;
        colIndex = (food.getPosX() - CELL_SIZE) / CELL_SIZE;

        //sprawdzenie, czy wygenerowana pozycja jest wolna
        //jesli tak, ustawiana jest pozycja
        if(fieldStates[rowIndex][colIndex].getState() == FREE){
            posIsFree = true;
            fieldStates[rowIndex][colIndex].setState(FOOD);//change to food
        }
    }

    //aktualizacja cyfry do wyswietlenia
    memset(buff,'0'+(char)food.getDrawNumber(),sizeof(buff)-1);

}

void Game::EatFood() {

    //inkrementacja cyfry do wyswietlenia
    food.setDrawNumber(food.getDrawNumber()+1);

    //ustalenie dlugosci kolejki dla nowego segmentu (w oparciu o dlugosc kolejki ostatniego segmentu)
    int lastNodeQueueLen = snake.getLastSegment().getQueue();

    //dodawanie okreslonej liczby segmentow
    for(int i = 0; i < SEGMENT_ADD_COEFF*food.getDrawNumber(); i++){
        snake.AddSegment();

        //kazdy nowy segment ma kolejke wieksza o 1 od poprzedniego
        snake.getLastSegment().IncreaseQueue(i+lastNodeQueueLen);
    }

    //zmienne pomocnicze na przechowanie pozycji
    //pozycja na mapie zamieniana jest na indeks wiersza i kolumny dla tablicy field states
    int rowIndex = (food.getPosY() - CELL_SIZE) / CELL_SIZE;
    int colIndex = (food.getPosX() - CELL_SIZE) / CELL_SIZE;

    //zwolnienie miejsca na mapie po wlasnie "zjedzonej" cyfrze
    fieldStates[rowIndex][colIndex].setState(FREE);

    //aktualizacja stanu weza, zeby nowe segmenty nie wygenerowaly sie na wezu
    for(int i = 0; i < snake.getSegments().getSize(); i++){

        rowIndex = (snake.getSegments().getNode(i).getPosY() - CELL_SIZE)/CELL_SIZE;
        colIndex = (snake.getSegments().getNode(i).getPosX() - CELL_SIZE)/CELL_SIZE;

        //ustawiane sa tylko pozycje tych segmentow, ktore nie sa poza plansza gry
        if(!snake.IsBeyondBoard(i)){
            fieldStates[rowIndex][colIndex].setState(SNAKE);
        }
    }

    //wstawienie nowej cyfry
    InsertFood();
}

void Game::PlayGameEvent() {

    //sprawdzanie, czy nie zostala "zjedzona" ostatnia cyfra
    //jesli tak - gra sie konczy
    if(food.getDrawNumber() > MAX_FOOD_NUMBER){
        gameLoop = false;
        return;
    }

    //odznaczenie weza z tablicy
    UnmarkSnakeFromBoard();

    //zmienne pomocnicze na przechowanie pozycji segmentow
    int rowIndex;
    int colIndex;

    //aktualizacja pozycji weza na mapie
    for(int i = 1; i < snake.getSegments().getSize()-1; i++){
        rowIndex = (snake.getSegments().getNode(i).getPosY() - CELL_SIZE) / CELL_SIZE;
        colIndex = (snake.getSegments().getNode(i).getPosX() - CELL_SIZE) / CELL_SIZE;

        if(!snake.IsBeyondBoard(i)) {
            fieldStates[rowIndex][colIndex].setState(SNAKE);
        }
    }

    //przypisanie pod zmienne pomocnicze pozycji glowy
    rowIndex = (snake.getHeadPosY() - CELL_SIZE)/CELL_SIZE;
    colIndex = (snake.getHeadPosX() - CELL_SIZE)/CELL_SIZE;

    //sprawdzenie, czy waz nie jest poza obszarem mapy
    //jesli tak - koniec gry
    if(snake.IsBeyondBoard()){
        gameLoop = false;
        return;
    }

    //pobranie stanu pola przypisanego nowej pozycji glowy
    FState state = fieldStates[rowIndex][colIndex].getState();

    //w zaleznosci od stanu pola, na ktorym znalazla glowa, wykonywana jest akcja gry
    switch(state){

        //pole wolne, zaktualizowanie tablicy field states
        case FREE:
            fieldStates[rowIndex][colIndex].setState(SNAKE);
            break;
        //na polu znajduje sie "jedzenie", wywolanie odpowiedniej funkcji i aktualizacja pozycji glowy
        case FOOD:
            fieldStates[rowIndex][colIndex].setState(SNAKE);
            EatFood();
            break;
        //na polu znajduje sie juz jakis segment weza - przerwanie gry
        case SNAKE:
            gameLoop = false;
        //na polu znajduje sie przeszkoda - przerwanie gry
        case OBSTACLE:
            gameLoop = false;
    }
}

bool Game::StartGame() {

        //test inicjalizacji allegro lib
        if (!al_init()) {
            al_show_native_message_box(nullptr, nullptr, nullptr, "failed to init allegro!", nullptr, 0);
            return false;
        }

        //inicjalizacja ekranu gry
        al_set_new_display_flags(ALLEGRO_WINDOWED);

        //wskaznik na ekran gry
        ALLEGRO_DISPLAY *display = al_create_display(SCREEN_W, SCREEN_H);

        //ustawienie tytulu okna
        al_set_window_title(display, "Nibbels Game by Michal Rzepka");

        //sprawdzenie, czy wskaznik na ekran gry zostal poprawnie zainicjalizowany
        if (!display) {
            al_show_native_message_box(nullptr, nullptr, nullptr, "failed to init display!", nullptr, 0);
            return false;
        }

        //instalacja i inicjalizacja elementow biblioteki allegro
        al_install_keyboard();
        al_install_mouse();
        al_init_primitives_addon();
        al_init_image_addon();
        al_init_font_addon();
        al_init_ttf_addon();

        //kolejka zdarzen
        ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

        //timer gry
        ALLEGRO_TIMER *timer = al_create_timer(1.0/FPS);

        //timer aktualizacji ruchow weza
        ALLEGRO_TIMER *frameTimer = al_create_timer(1.0/SPEED);

        //przechowanie stanow klawiatury
        ALLEGRO_KEYBOARD_STATE keyState;

        //inicjalizacja czionki
        ALLEGRO_FONT *font = al_load_ttf_font("fonts\\data-latin.ttf", 18, 0);

        //inicjalizacja zrodel zdarzen
        al_register_event_source(event_queue,al_get_keyboard_event_source());
        al_register_event_source(event_queue,al_get_timer_event_source(timer));
        al_register_event_source(event_queue,al_get_timer_event_source(frameTimer));

    //ustawienie ekranu powitalnego
    al_clear_to_color(BLACK);
    al_draw_text(font, al_map_rgb(255,255,255), SCREEN_W/2, SCREEN_H/2-80,ALLEGRO_ALIGN_CENTRE,"NIBBELS GAME");
    al_draw_text(font, al_map_rgb(255,255,255), SCREEN_W/2, SCREEN_H/2-20,ALLEGRO_ALIGN_CENTRE,"WCISNIJ DOWOLNY KLAWISZ, ABY ROZPOCZAC.");
    al_flip_display();

    //petla oczekujaca na wcisniecie dowolnego klawisza
    while(gameLoop){
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue,&events);

        if(events.type == ALLEGRO_EVENT_KEY_DOWN){
            al_clear_to_color(BLACK);
            al_flip_display();
            break;
        }
    }

    //zmienna na odczyt kierunku ruchu z klawiatury
    Direction dir = DOWN;

    //flaga informujaca, czy ma sie odbyc rysowanie elementow na ekranie
    bool draw = true;

    //wstawienie pierwszej cyfry
    InsertFood();

    //rozpoczecie dzialania timerow
    al_start_timer(timer);
    al_start_timer(frameTimer);

    //glowna petla gry
    while(gameLoop){

        //zmienna przechowujaca aktualne zdarzenie
        ALLEGRO_EVENT events;

        //pobranie zdarzenia z kolejki
        al_wait_for_event(event_queue, &events);

        //odczytanie stanu klawiatury
        al_get_keyboard_state(&keyState);

            //ustawienie kierunku poruszania sie w zaleznosci od stanu klawiatury
            if(events.timer.source == timer) {
                if(al_key_down(&keyState, ALLEGRO_KEY_DOWN)){
                    if (dir != UP && dir != DOWN) {
                        dir = DOWN;
                    }
                }else if(al_key_down(&keyState, ALLEGRO_KEY_UP)){
                    if (dir != DOWN && dir != UP) {
                        dir = UP;
                    }
                }else if(al_key_down(&keyState,ALLEGRO_KEY_LEFT)){
                    if (dir != RIGHT && dir != LEFT) {
                        dir = LEFT;
                    }
                }else if(al_key_down(&keyState,ALLEGRO_KEY_RIGHT)){
                    if (dir != LEFT && dir != RIGHT) {
                        dir = RIGHT;
                    }
                }
            }

        //ustawienie nowego kierunku poruszania sie glowy
        snake.setHeadDir(dir);

        //aktualizacja pozycji weza (poruszenie w nowym kierunku)
        if(events.timer.source == frameTimer) {
            snake.Move(CELL_SIZE, dir);
            PlayGameEvent();
            draw = true;
        }

        //wyswietlenie menu pozegnalnego, jezeli gra zostanie przerwana
        if(!gameLoop){
            gameLoop = true;
            draw = false;

            al_clear_to_color(BLACK);
            al_draw_text(font, al_map_rgb(255,255,255), SCREEN_W/2, SCREEN_H/2-40,ALLEGRO_ALIGN_CENTRE,"KONIEC GRY. Wcisnij ESC, aby wyjsc.");
            al_flip_display();

            while(gameLoop){
                al_wait_for_event(event_queue,&events);
                if(events.type == ALLEGRO_EVENT_KEY_DOWN){
                    if(events.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                        al_clear_to_color(BLACK);
                        al_flip_display();
                        gameLoop = false;
                    }
                }
            }
        }

        //rysowanie obiektow
        if (draw){
            draw = false;
            //rysowanie przeszkod
            for (int i = 0; i < obstacles.getSize(); i++) {
                obstacles.getNode(i).Draw();
            }

            //rysowanie obramowania cyfry
            food.Draw();
            //rysowanie cyfry
            al_draw_text(font, al_map_rgb(255,255,255), food.getPosX() + 10, food.getPosY(),ALLEGRO_ALIGN_CENTRE,buff);

            //rysowanie weza
            snake.Draw();

            //rysowanie krawedzi ekranu
            DrawBorders();
            al_flip_display();
            al_clear_to_color(BLACK);
        }
    }


    //usuniecie dynamicznie stworzonych obiektow
    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);

    return true;
}

bool Game::LoadObstacleMap(std::string &filename) {

    //otwarcie strumienia z pliku
    ifstream file;
    file.open(filename);

    //przerwanie, gdy nie udalo sie zaladowac pliku
    if(!file) return false;

    //bufor na odczyt poszczegolnych wierszy
    string lineBuff;

    //liczniki wierszy i kolumn
    int rowCounter = 0;
    int colCounter = 0;

    //zmienne pomocnicze na odczyt pozycji na mapie
    int PosX, PosY;

    //odczytywanie kolejnych wierszy w petli
    while(getline(file, lineBuff)){

        //inicjalizacja strumienia string za pomoca bufora wierszy
        //pozwala latwo pominac biale znaki
        stringstream stream(lineBuff);

        //bfor na kolejne znaki
        string signBuff;

        //odczytywanie w petli kolejnych znakow z kolumn
        while(stream >> signBuff){
            if(stoi(signBuff) == 1){
                //odzcytano 1 - ma zostac wstawiona przeszkoda

                //konwersja stanow licznikow na pozycje na mapie
                PosX = colCounter * CELL_SIZE + CELL_SIZE;
                PosY = rowCounter * CELL_SIZE + CELL_SIZE;

                //dodanie nowej przeszkody do listy i inicjalizacja jej pozycji
                obstacles.PushBack(Obstacle(PosX,PosY));

                //oznaczenie pola jako OBSTACLE
                fieldStates[rowCounter][colCounter].setState(OBSTACLE);

            }else if(stoi(signBuff) == 0){
                //odczytano 0 - brak przeszkody, dalszy odczyt
                colCounter++;
                continue;
            }else{
                //odczytano inny znak niz 1 albo 0
                return false;
            }
            colCounter++;
        }


        rowCounter++;
        colCounter = 0;
    }

    file.close();
    return true;
}

void Game::DrawBorders() {

    //rysowanie linii horyzontalnych
    for(int i = 0; i < SCREEN_W; i += CELL_SIZE){
        al_draw_filled_rectangle(i,0,i+CELL_SIZE,CELL_SIZE,BORDER_COLOR);
        al_draw_filled_rectangle(i,SCREEN_H-CELL_SIZE,i+CELL_SIZE,SCREEN_H,BORDER_COLOR);
    }

    //rysowanie linii wertykalnych
    for(int i = 0; i < SCREEN_H; i += CELL_SIZE){
        al_draw_filled_rectangle(0,i,CELL_SIZE,i+CELL_SIZE,BORDER_COLOR);
        al_draw_filled_rectangle(SCREEN_W-CELL_SIZE,i,SCREEN_W,i+CELL_SIZE,BORDER_COLOR);
    }
}

Game::~Game() {
    //zwolnienie zaalokowanej pamieci
    for(int i = 0; i < ROW_NUMBER; i++)
        delete[] fieldStates[i];
    delete[] fieldStates;
}
