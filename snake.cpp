#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define COLS 30
#define ROWS 20
bool running = true;
char key = 77;
char storage = 77;
int snake_length = 2;
int snake[60][2] = {{ COLS / 2, ROWS / 2 }, { COLS / 2 - 1, ROWS / 2 }};
int random1 = rand() % (COLS - 2) + 2;
int random2 = rand() % (ROWS - 2) + 2;
int apple[2] = {random1, random2};
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

void move(){
    switch (key) {
        case KEY_UP:
            if (snake_length == 1) snake[0][1]--;
            else {
                for (int i = snake_length - 2; i >= 0; i--) {
                    snake[i + 1][0] = snake[i][0];
                    snake[i + 1][1] = snake[i][1];
                }
                snake[0][1]--;
            }
            break;
        
        case KEY_RIGHT:
            if (snake_length == 1) snake[0][0]++;
            else {
                for (int i = snake_length - 2; i >= 0; i--) {
                    snake[i + 1][0] = snake[i][0];
                    snake[i + 1][1] = snake[i][1];
                }
                snake[0][0]++;
            }
            break;
        
        case KEY_DOWN:
            if (snake_length == 1) snake[0][1]++;
            else {
                for (int i = snake_length - 2; i >= 0; i--) {
                    snake[i + 1][0] = snake[i][0];
                    snake[i + 1][1] = snake[i][1];
                }
                snake[0][1]++;
            }
            break;

        case KEY_LEFT:
            if (snake_length == 1) snake[0][0]--;
            else {
                for (int i = snake_length - 2; i >= 0; i--) {
                    snake[i + 1][0] = snake[i][0];
                    snake[i + 1][1] = snake[i][1];
                }
                snake[0][0]--;
            }
            break;

        default:
            break;
    }
    for (int i = 1; i < snake_length; i++) {
        if (snake[0][0] == snake[i][0] && snake[0][1] == snake[i][1]) {
            running = false;
            break;
        }
    }
}

int main() {
    srand(time(NULL));
    apple[0] = rand() % (COLS - 2) + 2;
    apple[1] = rand() % (ROWS - 2) + 2;
    while(running) {
        system("CLS");
        if (snake[0][0] == apple[0] && snake[0][1] == apple[1]) {
            snake[snake_length][0] = snake[0][0];
            snake[snake_length][1] = snake[0][1];
            snake_length++;
            apple[0] = rand() % (COLS - 2) + 2;
            apple[1] = rand() % (ROWS - 2) + 2;
        }
        
        if (snake[0][0] <= 1 || snake[0][0] >= COLS || snake[0][1] <= 1 || snake[0][1] >= ROWS) {
            running = false;
        }
        
        for (int j = 1; j <= ROWS; j++) {
            for (int i = 1; i <= COLS; i++) {
                if (i % (COLS - 1) == 1 || j % (ROWS - 1) == 1) {
                    cout << "#";
                    continue;
                } else if (i == apple[0] && j == apple[1]) {
                    SetConsoleTextAttribute(h, 4);
                    cout << "@";
                    SetConsoleTextAttribute(h, 15);
                    continue;
                } else if (i == snake[0][0] && j == snake[0][1]) {
                    SetConsoleTextAttribute(h, 2);
                    cout << "%";
                    SetConsoleTextAttribute(h, 15);
                    continue;
                } else {
                    bool isBody = false;
                    for (int x = 1; x <= snake_length; x++) {
                        if (snake[x][0] == i && snake[x][1] == j) {
                            isBody = true;
                            break;
                        }
                    }
                    if (isBody) {
                        SetConsoleTextAttribute(h, 10);
                        cout << "&";
                        SetConsoleTextAttribute(h, 15);
                        continue;
                    } else {
                        cout << " ";
                        continue;
                    }
                }
            }
            cout << endl;
        }
        if (_kbhit()) {
            switch (_getch()) {
                case 'w':
                    if (key == KEY_DOWN) break;
                    key = KEY_UP;
                    break;
                
                case 'a':
                    if (key == KEY_RIGHT) break;
                    key = KEY_LEFT;
                    break;
                
                case 's':
                    if (key == KEY_UP) break;
                    key = KEY_DOWN;
                    break;
                
                case 'd':
                    if (key == KEY_LEFT) break;
                    key = KEY_RIGHT;
                    break;
                
                default:
                    break;
            }
        }
        move();
    }
    getch();
}