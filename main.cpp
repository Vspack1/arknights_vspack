// // #include <ncurses.h>
// // #include <fstream>
// // #include <vector>
// // #include <string>
// // #include <map>
// // #include <nlohmann/json.hpp>
// // using json = nlohmann::json;

// // struct Operator {
// //     std::string name;
// //     char symbol;
// //     int cost;
// //     int range;
// //     int damage;
// //     int fireRate; // Lower is faster
// //     int level;
// //     int hp;
// // };

// // struct Tower {
// //     Operator op;
// //     int x, y;
// //     int cooldown;
// // };

// // struct Enemy {
// //     int x, y;
// //     int hp;
// // };

// // int gridW = 20, gridH = 10;
// // std::vector<std::string> mapGrid;
// // std::map<std::string, Operator> opConfigs;
// // std::vector<Tower> towers;
// // std::vector<Enemy> enemies;

// // int money = 100;
// // int selectedOpIndex = 0;
// // std::vector<std::string> opNames;

// // void loadOperators(const std::string &filename) {
// //     std::ifstream in(filename);
// //     json j;
// //     in >> j;
// //     for (auto& [key, val] : j.items()) {
// //         Operator op;
// //         op.name = key;
// //         op.symbol = val["symbol"].get<std::string>()[0];
// //         op.cost = val["cost"];
// //         op.range = val["range"];
// //         op.damage = val["damage"];
// //         op.fireRate = val["fireRate"];
// //         op.level = 1;
// //         op.hp = val["hp"];
// //         opConfigs[key] = op;
// //         opNames.push_back(key);
// //     }
// // }

// // void loadMap(const std::string &filename) {
// //     std::ifstream in(filename);
// //     json j;
// //     in >> j;
// //     mapGrid = j["map"].get<std::vector<std::string>>();
// // }

// // void saveMap(const std::string &filename) {
// //     json j;
// //     j["map"] = mapGrid;
// //     std::ofstream out(filename);
// //     out << j.dump(4);
// // }

// // void drawGame(int cursorX, int cursorY) {
// //     clear();
// //     for (int y = 0; y < gridH; ++y) {
// //         for (int x = 0; x < gridW; ++x) {
// //             bool drawn = false;
// //             for (const auto &t : towers) {
// //                 if (t.x == x && t.y == y) {
// //                     mvaddch(y, x, t.op.symbol);
// //                     drawn = true;
// //                     break;
// //                 }
// //             }
// //             if (!drawn) {
// //                 bool enemyHere = false;
// //                 for (const auto &e : enemies) {
// //                     if (e.x == x && e.y == y) {
// //                         mvaddch(y, x, 'E');
// //                         enemyHere = true;
// //                         break;
// //                     }
// //                 }
// //                 if (!enemyHere) {
// //                     if (y >= 0 && y < (int)mapGrid.size() && !mapGrid.empty() && x >= 0 && x < (int)mapGrid[y].size()) {
// //                         mvaddch(y, x, mapGrid[y][x]);
// //                     } else {
// //                         mvaddch(y, x, '.');
// //                     }
// //                 }
// //             }
// //         }
// //     }
// //     if (cursorY >= 0 && cursorY < gridH && cursorX >= 0 && cursorX < gridW) {
// //         mvaddch(cursorY, cursorX, 'X' | A_BOLD);
// //     }
// // }

// // int main() {
// //     loadOperators("operator.json");
// //     loadMap("map.json");

// //     int cursorX = 0;
// //     int cursorY = 0;

// //     initscr();
// //     cbreak();
// //     noecho();
// //     keypad(stdscr, TRUE);
// //     nodelay(stdscr, TRUE);
// //     curs_set(0);

// //     bool running = true;
// //     while (running) {
// //         drawGame(cursorX, cursorY);
// //         mvprintw(gridH + 1, 0, "Arrows: move | q: quit");
// //         refresh();

// //         int ch = getch();
// //         switch (ch) {
// //             case KEY_UP:    if (cursorY > 0) cursorY--; break;
// //             case KEY_DOWN:  if (cursorY < gridH - 1) cursorY++; break;
// //             case KEY_LEFT:  if (cursorX > 0) cursorX--; break;
// //             case KEY_RIGHT: if (cursorX < gridW - 1) cursorX++; break;
// //             case 'q':
// //                 running = false;
// //                 break;
// //             default:
// //                 break;
// //         }

// //         napms(60);
// //     }

// //     endwin();
// //     return 0;
// // }

// #include <ncurses.h>
// #include <fstream>
// #include <vector>
// #include <string>
// #include <map>
// #include <iostream>
// #include <unistd.h> // for usleep
// #include <nlohmann/json.hpp>

// using json = nlohmann::json;

// struct Operator {
//     std::string name;
//     char symbol;
//     int cost;
//     int range;
//     int damage;
//     int fireRate; // Lower is faster
//     int level;
//     int hp;
// };

// struct Tower {
//     Operator op;
//     int x, y;
//     int cooldown;
// };

// struct Enemy {
//     int x, y;
//     int hp;
// };

// int gridW = 20, gridH = 10;
// std::vector<std::string> mapGrid;
// std::map<std::string, Operator> opConfigs;
// std::vector<Tower> towers;
// std::vector<Enemy> enemies;

// int money = 100;
// int selectedOpIndex = 0;
// std::vector<std::string> opNames;

// void createDefaultFiles() {
//     // Create default operator.json if it doesn't exist
//     std::ifstream testOp("operator.json");
//     if (!testOp.good()) {
//         json opJson;
//         opJson["Sniper"] = {
//             {"symbol", "S"},
//             {"cost", 50},
//             {"range", 5},
//             {"damage", 30},
//             {"fireRate", 3},
//             {"hp", 100}
//         };
//         opJson["Artillery"] = {
//             {"symbol", "A"},
//             {"cost", 80},
//             {"range", 7},
//             {"damage", 50},
//             {"fireRate", 5},
//             {"hp", 120}
//         };
//         opJson["Guard"] = {
//             {"symbol", "G"},
//             {"cost", 30},
//             {"range", 2},
//             {"damage", 15},
//             {"fireRate", 1},
//             {"hp", 200}
//         };
        
//         std::ofstream out("operator.json");
//         out << opJson.dump(4);
//         out.close();
//     }
//     testOp.close();
    
//     // Create default map.json if it doesn't exist
//     std::ifstream testMap("map.json");
//     if (!testMap.good()) {
//         json mapJson;
//         std::vector<std::string> defaultMap = {
//             "....................",
//             "....................",
//             "..---.....----......",
//             "....................",
//             "....................",
//             "....................",
//             "..###.....####......",
//             "....................",
//             "....................",
//             "...................."
//         };
//         mapJson["map"] = defaultMap;
        
//         std::ofstream out("map.json");
//         out << mapJson.dump(4);
//         out.close();
//     }
//     testMap.close();
// }

// bool loadOperators(const std::string &filename) {
//     try {
//         std::ifstream in(filename);
//         if (!in.good()) {
//             return false;
//         }
        
//         json j;
//         in >> j;
        
//         for (auto& [key, val] : j.items()) {
//             Operator op;
//             op.name = key;
//             op.symbol = val["symbol"].get<std::string>()[0];
//             op.cost = val["cost"];
//             op.range = val["range"];
//             op.damage = val["damage"];
//             op.fireRate = val["fireRate"];
//             op.level = 1;
//             op.hp = val["hp"];
//             opConfigs[key] = op;
//             opNames.push_back(key);
//         }
//         return true;
//     } catch (const std::exception& e) {
//         return false;
//     }
// }

// bool loadMap(const std::string &filename) {
//     try {
//         std::ifstream in(filename);
//         if (!in.good()) {
//             return false;
//         }
        
//         json j;
//         in >> j;
//         mapGrid = j["map"].get<std::vector<std::string>>();
        
//         // Ensure grid has proper dimensions
//         while ((int)mapGrid.size() < gridH) {
//             mapGrid.push_back(std::string(gridW, '.'));
//         }
//         for (auto& row : mapGrid) {
//             while ((int)row.size() < gridW) {
//                 row += '.';
//             }
//             if ((int)row.size() > gridW) {
//                 row = row.substr(0, gridW);
//             }
//         }
//         return true;
//     } catch (const std::exception& e) {
//         return false;
//     }
// }

// void saveMap(const std::string &filename) {
//     try {
//         json j;
//         j["map"] = mapGrid;
//         std::ofstream out(filename);
//         out << j.dump(4);
//         out.close();
//     } catch (const std::exception& e) {
//         // Ignore save errors for now
//     }
// }

// void drawGame(int cursorX, int cursorY) {
//     clear();
    
//     // Draw the game grid
//     for (int y = 0; y < gridH; ++y) {
//         for (int x = 0; x < gridW; ++x) {
//             bool drawn = false;
            
//             // Draw towers first
//             for (const auto &t : towers) {
//                 if (t.x == x && t.y == y) {
//                     mvaddch(y, x, t.op.symbol);
//                     drawn = true;
//                     break;
//                 }
//             }
            
//             if (!drawn) {
//                 // Draw enemies
//                 bool enemyHere = false;
//                 for (const auto &e : enemies) {
//                     if (e.x == x && e.y == y) {
//                         mvaddch(y, x, 'E');
//                         enemyHere = true;
//                         break;
//                     }
//                 }
                
//                 if (!enemyHere) {
//                     // Draw map terrain
//                     if (y >= 0 && y < (int)mapGrid.size() && x >= 0 && x < (int)mapGrid[y].size()) {
//                         mvaddch(y, x, mapGrid[y][x]);
//                     } else {
//                         mvaddch(y, x, '.');
//                     }
//                 }
//             }
//         }
//     }
    
//     // Draw cursor
//     if (cursorY >= 0 && cursorY < gridH && cursorX >= 0 && cursorX < gridW) {
//         mvaddch(cursorY, cursorX, 'X' | A_REVERSE);
//     }
    
//     // Draw UI
//     mvprintw(gridH + 1, 0, "Money: $%d | Towers: %d | Enemies: %d", 
//              money, (int)towers.size(), (int)enemies.size());
//     mvprintw(gridH + 2, 0, "Controls: Arrows=move | SPACE=place tower | q=quit | e=spawn enemy");
    
//     if (!opNames.empty()) {
//         mvprintw(gridH + 3, 0, "Selected: %s (Cost: $%d) | TAB=switch operator", 
//                  opNames[selectedOpIndex].c_str(), 
//                  opConfigs[opNames[selectedOpIndex]].cost);
//     }
// }

// void placeTower(int x, int y) {
//     if (opNames.empty()) return;
    
//     std::string selectedOp = opNames[selectedOpIndex];
//     Operator op = opConfigs[selectedOp];
    
//     // Check if we have enough money
//     if (money < op.cost) {
//         mvprintw(gridH + 4, 0, "Not enough money! Need $%d", op.cost);
//         refresh();
//         usleep(500000); // Show message for 0.5 seconds
//         return;
//     }
    
//     // Check if position is valid (not on path or another tower)
//     if (y >= 0 && y < (int)mapGrid.size() && x >= 0 && x < (int)mapGrid[y].size()) {
//         if (mapGrid[y][x] != '.' && mapGrid[y][x] != ' ') {
//             mvprintw(gridH + 4, 0, "Cannot place tower here!");
//             refresh();
//             usleep(500000);
//             return;
//         }
//     }
    
//     // Check if there's already a tower here
//     for (const auto& t : towers) {
//         if (t.x == x && t.y == y) {
//             mvprintw(gridH + 4, 0, "Tower already exists here!");
//             refresh();
//             usleep(500000);
//             return;
//         }
//     }
    
//     // Place the tower
//     Tower newTower;
//     newTower.op = op;
//     newTower.x = x;
//     newTower.y = y;
//     newTower.cooldown = 0;
//     towers.push_back(newTower);
//     money -= op.cost;
    
//     mvprintw(gridH + 4, 0, "Tower placed! Remaining: $%d", money);
//     refresh();
//     usleep(300000);
// }

// void spawnEnemy() {
//     Enemy newEnemy;
//     newEnemy.x = 0;
//     newEnemy.y = gridH / 2;
//     newEnemy.hp = 50;
//     enemies.push_back(newEnemy);
// }

// int main() {
//     // Create default files if they don't exist
//     createDefaultFiles();
    
//     // Load game data
//     if (!loadOperators("operator.json")) {
//         std::cout << "Error: Could not load operator.json" << std::endl;
//         return 1;
//     }
    
//     if (!loadMap("map.json")) {
//         std::cout << "Error: Could not load map.json" << std::endl;
//         return 1;
//     }

//     int cursorX = 0;
//     int cursorY = 0;

//     initscr();
//     cbreak();
//     noecho();
//     keypad(stdscr, TRUE);
//     nodelay(stdscr, TRUE);
//     curs_set(0);

//     bool running = true;
//     int gameTime = 0;
    
//     while (running) {
//         drawGame(cursorX, cursorY);
//         refresh();

//         int ch = getch();
//         switch (ch) {
//             case KEY_UP:    
//                 if (cursorY > 0) cursorY--; 
//                 break;
//             case KEY_DOWN:  
//                 if (cursorY < gridH - 1) cursorY++; 
//                 break;
//             case KEY_LEFT:  
//                 if (cursorX > 0) cursorX--; 
//                 break;
//             case KEY_RIGHT: 
//                 if (cursorX < gridW - 1) cursorX++; 
//                 break;
//             case ' ': // Space to place tower
//                 placeTower(cursorX, cursorY);
//                 break;
//             case '\t': // Tab to switch operator
//                 if (!opNames.empty()) {
//                     selectedOpIndex = (selectedOpIndex + 1) % opNames.size();
//                 }
//                 break;
//             case 'e': // Spawn enemy for testing
//                 spawnEnemy();
//                 break;
//             case 'q':
//                 running = false;
//                 break;
//             default:
//                 break;
//         }

//         // Simple game logic
//         gameTime++;
        
//         // Move enemies (very basic)
//         for (auto& enemy : enemies) {
//             if (gameTime % 10 == 0) { // Move every 10 frames
//                 enemy.x++;
//                 if (enemy.x >= gridW) {
//                     enemy.x = 0; // Reset to start
//                 }
//             }
//         }
        
//         // Tower shooting (basic)
//         for (auto& tower : towers) {
//             if (tower.cooldown > 0) {
//                 tower.cooldown--;
//             } else {
//                 // Look for enemies in range
//                 for (auto& enemy : enemies) {
//                     int dx = enemy.x - tower.x;
//                     int dy = enemy.y - tower.y;
//                     int distance = dx*dx + dy*dy;
                    
//                     if (distance <= tower.op.range * tower.op.range) {
//                         enemy.hp -= tower.op.damage;
//                         tower.cooldown = tower.op.fireRate;
//                         break; // Only shoot one enemy
//                     }
//                 }
//             }
//         }
        
//         // Remove dead enemies
//         enemies.erase(
//             std::remove_if(enemies.begin(), enemies.end(), 
//                           [](const Enemy& e) { return e.hp <= 0; }),
//             enemies.end()
//         );

//         usleep(16000); // ~60 FPS
//     }

//     endwin();
//     saveMap("map.json");
//     return 0;
// }

#include <ncurses.h>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>
#include <unistd.h>
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
    int maxHp;
};

int gridW = 20, gridH = 10;
std::vector<std::string> mapGrid;
std::map<std::string, Operator> opConfigs;
std::vector<Tower> towers;
std::vector<Enemy> enemies;

int money = 100;
int selectedOpIndex = 0;
std::vector<std::string> opNames;
int gameTime = 0;
int score = 0;

bool loadOperators(const std::string &filename) {
    try {
        std::ifstream in(filename);
        if (!in.good()) {
            return false;
        }
        
        json j;
        in >> j;
        
        opConfigs.clear();
        opNames.clear();
        
        for (auto& [key, val] : j.items()) {
            Operator op;
            op.name = key;
            std::string symbolStr = val["symbol"];
            op.symbol = symbolStr.empty() ? '?' : symbolStr[0];
            op.cost = val["cost"];
            op.range = val["range"];
            op.damage = val["damage"];
            op.fireRate = val["fireRate"];
            op.level = 1;
            op.hp = val["hp"];
            opConfigs[key] = op;
            opNames.push_back(key);
        }
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

bool loadMap(const std::string &filename) {
    try {
        std::ifstream in(filename);
        if (!in.good()) {
            return false;
        }
        
        json j;
        in >> j;
        mapGrid = j["map"].get<std::vector<std::string>>();
        
        // Ensure grid has proper dimensions
        while ((int)mapGrid.size() < gridH) {
            mapGrid.push_back(std::string(gridW, '.'));
        }
        for (auto& row : mapGrid) {
            while ((int)row.size() < gridW) {
                row += '.';
            }
            if ((int)row.size() > gridW) {
                row = row.substr(0, gridW);
            }
        }
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

void saveMap(const std::string &filename) {
    try {
        json j;
        j["map"] = mapGrid;
        std::ofstream out(filename);
        out << j.dump(4);
        out.close();
    } catch (const std::exception& e) {
        // Ignore save errors
    }
}

void drawGame(int cursorX, int cursorY) {
    clear();
    
    // Draw the game grid
    for (int y = 0; y < gridH; ++y) {
        for (int x = 0; x < gridW; ++x) {
            bool drawn = false;
            
            // Draw towers first
            for (const auto &t : towers) {
                if (t.x == x && t.y == y) {
                    if (t.cooldown > 0) {
                        mvaddch(y, x, t.op.symbol | A_BOLD); // Highlight when shooting
                    } else {
                        mvaddch(y, x, t.op.symbol);
                    }
                    drawn = true;
                    break;
                }
            }
            
            if (!drawn) {
                // Draw enemies
                bool enemyHere = false;
                for (const auto &e : enemies) {
                    if (e.x == x && e.y == y) {
                        if (e.hp < e.maxHp / 2) {
                            mvaddch(y, x, 'e'); // Damaged enemy
                        } else {
                            mvaddch(y, x, 'E'); // Healthy enemy
                        }
                        enemyHere = true;
                        break;
                    }
                }
                
                if (!enemyHere) {
                    // Draw map terrain
                    if (y >= 0 && y < (int)mapGrid.size() && x >= 0 && x < (int)mapGrid[y].size()) {
                        mvaddch(y, x, mapGrid[y][x]);
                    } else {
                        mvaddch(y, x, '.');
                    }
                }
            }
        }
    }
    
    // Draw cursor
    if (cursorY >= 0 && cursorY < gridH && cursorX >= 0 && cursorX < gridW) {
        mvaddch(cursorY, cursorX, '+' | A_REVERSE | A_BOLD);
    }
    
    // Draw UI
    mvprintw(gridH + 1, 0, "Money: $%d | Score: %d | Towers: %d | Enemies: %d", 
             money, score, (int)towers.size(), (int)enemies.size());
    mvprintw(gridH + 2, 0, "Controls: Arrows=move | SPACE=place | TAB=switch | E=enemy | Q=quit");
    
    if (!opNames.empty()) {
        const auto& op = opConfigs[opNames[selectedOpIndex]];
        mvprintw(gridH + 3, 0, "Selected: %s (%c) | Cost: $%d | Range: %d | Damage: %d", 
                 opNames[selectedOpIndex].c_str(), op.symbol, op.cost, op.range, op.damage);
    }
    
    // Show placement validity
    if (cursorY >= 0 && cursorY < (int)mapGrid.size() && 
        cursorX >= 0 && cursorX < (int)mapGrid[cursorY].size()) {
        char terrain = mapGrid[cursorY][cursorX];
        bool canPlace = (terrain == '.' || terrain == ' ');
        
        // Check for existing tower
        for (const auto& t : towers) {
            if (t.x == cursorX && t.y == cursorY) {
                canPlace = false;
                break;
            }
        }
        
        if (canPlace && !opNames.empty()) {
            mvprintw(gridH + 4, 0, "Can place here! Press SPACE");
        } else {
            mvprintw(gridH + 4, 0, "Cannot place tower here");
        }
    }
}

void placeTower(int x, int y) {
    if (opNames.empty()) return;
    
    std::string selectedOp = opNames[selectedOpIndex];
    Operator op = opConfigs[selectedOp];
    
    // Check if we have enough money
    if (money < op.cost) {
        return;
    }
    
    // Check if position is valid
    if (y >= 0 && y < (int)mapGrid.size() && x >= 0 && x < (int)mapGrid[y].size()) {
        char terrain = mapGrid[y][x];
        if (terrain != '.' && terrain != ' ') {
            return;
        }
    } else {
        return;
    }
    
    // Check if there's already a tower here
    for (const auto& t : towers) {
        if (t.x == x && t.y == y) {
            return;
        }
    }
    
    // Place the tower
    Tower newTower;
    newTower.op = op;
    newTower.x = x;
    newTower.y = y;
    newTower.cooldown = 0;
    towers.push_back(newTower);
    money -= op.cost;
}

void spawnEnemy() {
    Enemy newEnemy;
    newEnemy.x = 0;
    newEnemy.y = gridH / 2;
    newEnemy.hp = 30;
    newEnemy.maxHp = 30;
    enemies.push_back(newEnemy);
}

void updateGame() {
    gameTime++;
    
    // Move enemies along path
    for (auto& enemy : enemies) {
        if (gameTime % 15 == 0) { // Move every 15 frames
            enemy.x++;
            if (enemy.x >= gridW) {
                enemy.x = 0; // Loop back
            }
        }
    }
    
    // Tower shooting
    for (auto& tower : towers) {
        if (tower.cooldown > 0) {
            tower.cooldown--;
        } else {
            // Look for enemies in range
            for (auto& enemy : enemies) {
                int dx = enemy.x - tower.x;
                int dy = enemy.y - tower.y;
                int distanceSq = dx*dx + dy*dy;
                
                if (distanceSq <= tower.op.range * tower.op.range) {
                    enemy.hp -= tower.op.damage;
                    tower.cooldown = tower.op.fireRate * 10; // Convert to frames
                    break;
                }
            }
        }
    }
    
    // Remove dead enemies and add score
    int enemiesBefore = enemies.size();
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(), 
                      [](const Enemy& e) { return e.hp <= 0; }),
        enemies.end()
    );
    int enemiesKilled = enemiesBefore - enemies.size();
    score += enemiesKilled * 10;
    money += enemiesKilled * 5;
    
    // Auto-spawn enemies occasionally
    if (gameTime % 180 == 0) { // Every 3 seconds
        spawnEnemy();
    }
}

int main() {
    // Load game data
    if (!loadOperators("operator.json")) {
        std::cerr << "Error: Could not load operator.json" << std::endl;
        std::cerr << "Make sure the file exists and has valid JSON format" << std::endl;
        return 1;
    }
    
    if (!loadMap("map.json")) {
        std::cerr << "Error: Could not load map.json" << std::endl;
        return 1;
    }

    if (opNames.empty()) {
        std::cerr << "Error: No operators loaded from operator.json" << std::endl;
        return 1;
    }

    int cursorX = gridW / 2;
    int cursorY = gridH / 2;

    initscr();
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    }
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    bool running = true;
    
    while (running) {
        updateGame();
        drawGame(cursorX, cursorY);
        refresh();

        int ch = getch();
        switch (ch) {
            case KEY_UP:    
                if (cursorY > 0) cursorY--; 
                break;
            case KEY_DOWN:  
                if (cursorY < gridH - 1) cursorY++; 
                break;
            case KEY_LEFT:  
                if (cursorX > 0) cursorX--; 
                break;
            case KEY_RIGHT: 
                if (cursorX < gridW - 1) cursorX++; 
                break;
            case ' ': // Space to place tower
                placeTower(cursorX, cursorY);
                break;
            case '\t': // Tab to switch operator
            case KEY_TAB:
                if (!opNames.empty()) {
                    selectedOpIndex = (selectedOpIndex + 1) % opNames.size();
                }
                break;
            case 'e':
            case 'E': // Spawn enemy for testing
                spawnEnemy();
                break;
            case 'q':
            case 'Q':
                running = false;
                break;
            default:
                break;
        }

        usleep(16666); // ~60 FPS
    }

    endwin();
    
    std::cout << "Game Over!" << std::endl;
    std::cout << "Final Score: " << score << std::endl;
    std::cout << "Towers Built: " << towers.size() << std::endl;
    
    return 0;
}