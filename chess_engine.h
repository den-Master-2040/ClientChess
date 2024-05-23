#ifndef chess_Engine_H
#define chess_Engine_H



class chess_Engine
{

public:
    chess_Engine();
    bool hod(int figure, int user_hod);
    bool hod_player_1(int figure, int user_hod); //главная функция, вызывающая функцию хода конкретной фигуры.
    bool hod_player_2(int figure, int user_hod); //главная функция, вызывающая функцию хода конкретной фигуры.
    void print_chess_Engine_map();             //вывод
    void peshka_hod(int figure_i, int figure_j, int user_hod_i, int user_hod_j, int player);
    void hod_ladya(int figure_i, int figure_j, int user_hod_i, int user_hod_j, int player);
    bool proverka_ladya(int figure_i, int figure_j, int user_hod_i, int user_hod_j); //проверка,может ли сходить ладья - пустота ли впереди
    void hod_konb(int figure_i, int figure_j, int user_hod_i, int user_hod_j, int player);
    void hod_ferz(int figure_i, int figure_j, int user_hod_i, int user_hod_j, int player);
    void hod_corol(int figure_i, int figure_j, int user_hod_i, int user_hod_j, int player);
    void hod_coroleva (int figure_i, int figure_j, int user_hod_i, int user_hod_j, int player);
    bool mat();
    /*
     * Это неправильное объявление двумерного массива.
     *  Но если определить здесь только переменную, а
     *  инициализировать её в конструкторе, то возникнет
     *  ошибка "слишком много аргументов скалярного иницализатора"
     *
     *  This is an incorrect declaration of a two-dimensional array.
     *  But if you define only a variable here, and initialize it
     *  in the constructor, then the error "too many scalar
     *  initializer arguments" will occur
    */
    int chess_Engine_map[8][8] = {
        {2, 3, 4, 5, 6, 4, 3, 2},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {7, 7, 7, 7, 7, 7, 7, 7},
        {8, 9,10,11,12,10, 9, 8}
    };
};

#endif // chess_Engine_H
