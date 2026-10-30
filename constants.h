#pragma once

// ---- Старые константы (не трогаем) ----
constexpr int MAX_ITEMS       = 10;
constexpr int INVENTORY_SIZE  = 10;
constexpr int HOURS_IN_DAY    = 24;
constexpr int MAX_NAME_LEN    = 64;
constexpr int FARMER_NAME_LEN = 64;   // ← было 32, увеличено (русские буквы = 2 байта в UTF-8)
constexpr int MAX_WORK_HOURS  = 8;
constexpr int INPUT_FLUSH_LIMIT = 10000;

constexpr int ID_nothing = 0;
constexpr int ID_wood    = 1;
constexpr int ID_stone   = 2;
constexpr int ID_seed    = 3;
constexpr int ID_iron    = 4;
constexpr int ID_bread   = 5;
constexpr int ID_gold    = 6;
constexpr int ID_diamond = 7;
constexpr int ID_coal    = 8;
constexpr int ID_torch   = 9;

// ---- Карта ----
constexpr int MAP_MIN_SIZE         = 5;
constexpr int MAP_MAX_SIZE         = 30;
constexpr int OBSTACLE_PERCENT_MIN = 15;
constexpr int OBSTACLE_PERCENT_MAX = 30;
constexpr int MAX_GENERATION_TRIES = 1000;

constexpr char TILE_WALL      = '#';
constexpr char TILE_FLOOR     = '.';
constexpr char TILE_TREE      = 'T';
constexpr char TILE_ROCK      = 'R';
constexpr char TILE_HERO      = '@';

// ---- Сквозняк (вариант «Сквозняк») ----
// ВАЖНО: символы латинские. ^ = 94, v = 118, < = 60, > = 62
constexpr char TILE_WIND_UP    = '^';
constexpr char TILE_WIND_DOWN  = 'v';
constexpr char TILE_WIND_LEFT  = '<';
constexpr char TILE_WIND_RIGHT = '>';
constexpr int  WIND_PUSH_DIST  = 3;   // на сколько клеток сдувает
constexpr int  WIND_PERCENT    = 10;  // вероятность появления на карте, % (для теста 10, потом можно 5)

constexpr int MENU_ITEMS_COUNT = 10;