#include <ncurses.h>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

struct Operator {
    std::string name;
    char symbol;
    int cost;
    int range;
    int damage;
    int fireRate; // Lower is faster
    int level;
    int hp;
};

struct Tower {
    Operator op;
    int x, y;
    int cooldown;
};

struct Enemy {
    int x, y;
    int hp;
};

int gridW = 20, gridH = 10;
std::vector<std::string> mapGrid;
std::map<std::string, Operator> opConfigs;
std::vector<Tower> towers;
std::vector<Enemy> enemies;

int money = 100;
int selectedOpIndex = 0;
std::vector<std::string> opNames;

void loadOperators(const std::string &filename) {
    std::ifstream in(filename);
    json j;
    in >> j;
    for (auto& [key, val] : j.items()) {
        Operator op;
        op.name = key;
        op.symbol = val["symbol"].get<std::string>()[0];
        op.cost = val["cost"];
        op.range = val["range"];
        op.damage = val["damage"];
        op.fireRate = val["fireRate"];
        op.level = 1;
        op.hp = val["hp"];
        opConfigs[key] = op;
        opNames.push_back(key);
    }
}

void loadMap(const std::string &filename) {
    std::ifstream in(filename);
    json j;
    in >> j;
    mapGrid = j["map"].get<std::vector<std::string>>();
}

void saveMap(const std::string &filename) {
    json j;
    j["map"] = mapGrid;
    std::ofstream out(filename);
    out << j.dump(4);
}

void drawGame(int cursorX, int cursorY) {
    clear();
    for (int y = 0; y < gridH; ++y) {
        for (int x = 0; x < gridW; ++x) {
            bool drawn = false;
            for (const auto &t : towers) {
                if (t.x == x && t.y == y) {
                    mvaddch(y, x, t.op.symbol);
                    drawn = true;
                    break;
                }
            }
            if (!drawn) {
                bool enemyHere = false;
                for (const auto &e : enemies) {
                    if (e.x == x && e.y == y) {
                        mvaddch(y, x, 'E');
                        enemyHere = true;
                        break;
                    }
                }
                if (!enemyHere) {
                    if (y >= 0 && y < (int)mapGrid.size() && !mapGrid.empty() && x >= 0 && x < (int)mapGrid[y].size()) {
                        mvaddch(y, x, mapGrid[y][x]);
                    } else {
                        mvaddch(y, x, '.');
                    }
                }
            }
        }
    }
    if (cursorY >= 0 && cursorY < gridH && cursorX >= 0 && cursorX < gridW) {
        mvaddch(cursorY, cursorX, 'X' | A_BOLD);
    }
}

int main() {
    loadOperators("operator.json");
    loadMap("map.json");

    int cursorX = 0;
    int cursorY = 0;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    bool running = true;
    while (running) {
        drawGame(cursorX, cursorY);
        mvprintw(gridH + 1, 0, "Arrows: move | q: quit");
        refresh();

        int ch = getch();
        switch (ch) {
            case KEY_UP:    if (cursorY > 0) cursorY--; break;
            case KEY_DOWN:  if (cursorY < gridH - 1) cursorY++; break;
            case KEY_LEFT:  if (cursorX > 0) cursorX--; break;
            case KEY_RIGHT: if (cursorX < gridW - 1) cursorX++; break;
            case 'q':
                running = false;
                break;
            default:
                break;
        }

        napms(60);
    }

    endwin();
    return 0;
}
