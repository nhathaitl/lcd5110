//
//  main.cpp
//  terminal-snake
//
//  Created by Stephen Gowen on 4/28/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <termios.h>
#include <unistd.h>
#include <sstream>

#include "../lib/lcd_lib.h"


char getch()
{
    return getchar();
}

void changemode(int dir)
{
    static struct termios oldt, newt;
    
    if (dir == 1)
    {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    }
    else
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}

int kbhit()
{
    struct timeval tv;
    fd_set rdfs;
    
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    
    FD_ZERO(&rdfs);
    FD_SET (STDIN_FILENO, &rdfs);
    
    select(STDIN_FILENO + 1, &rdfs, NULL, NULL, &tv);
    
    return FD_ISSET(STDIN_FILENO, &rdfs);
}

void _sleep(int millis)
{
    usleep(millis * 1000);
}

void clearScreen()
{
    system("clear");
}

const int MAP_WIDTH = 84;
const int MAP_HEIGHT = 43;
const int MAP_SIZE = MAP_WIDTH * MAP_HEIGHT; // How many spaces there are in the map

const int TILE_FOOD = -3;
const int TILE_HORIZONTAL_WALL = -2;
const int TILE_VERTICAL_WALL = -1;
const int TILE_FREE_SPACE = 0;

const int DIRECTION_RIGHT = 0;
const int DIRECTION_UP = 1;
const int DIRECTION_LEFT = 2;
const int DIRECTION_DOWN = 3;

const int SNAKE_STARTING_LENGTH = 3;

int map[MAP_SIZE];

int headX = MAP_WIDTH / 2;
int headY = MAP_HEIGHT / 2;
int direction = DIRECTION_UP;
int length = SNAKE_STARTING_LENGTH;

bool exitGame = false;

void generateFoodOnMap()
{
    int x = 0;
    int y = 0;
    
    while (true)
    {
        x = rand() % (MAP_WIDTH - 2) + 1; // Generate random Y value between 1 and 23
        y = rand() % (MAP_HEIGHT - 2) + 1; // Generate random X value between 1 and 15
        
        if (map[y + x * MAP_HEIGHT] == TILE_FREE_SPACE)
        {
            break;
        }
    }
    
    // Place new food on map
    map[y + x * MAP_HEIGHT] = TILE_FOOD;
}

void changeSnakeDirection(char key)
{
    switch (key)
    {
        case 'w':
            if (direction != DIRECTION_DOWN)
            {
                direction = DIRECTION_UP;
            }
            break;
        case 'd':
            if (direction != DIRECTION_LEFT)
            {
                direction = DIRECTION_RIGHT;
            }
            break;
        case 's':
            if (direction != DIRECTION_UP)
            {
                direction = DIRECTION_DOWN;
            }
            break;
        case 'a':
            if (direction != DIRECTION_RIGHT)
            {
                direction = DIRECTION_LEFT;
            }
            break;
    }
}

void moveSnake(int dx, int dy)
{
    // determine new head position
    int newX = headX + dx;
    int newY = headY + dy;
    
    if (map[newY + newX * MAP_HEIGHT] == TILE_FOOD)
    {
        // The snake grows in length by 1 tile
        length++;
        
        generateFoodOnMap();
    }
    else if (map[newY + newX * MAP_HEIGHT] != TILE_FREE_SPACE)
    {
        // Snake has either ran into itself or a wall, so end the game
        exitGame = true;
    }
    
    // Move head to new location
    headX = newX;
    headY = newY;
    map[headY + headX * MAP_HEIGHT] = length + 1;
}

void initMap()
{
    lcd_clear_screen();
    // Place Snake Head on map
    map[headY + headX * MAP_HEIGHT] = 1;
    
    // Places top and bottom walls on map
    for (int x = 0; x < MAP_HEIGHT; ++x)
    {
        map[x] = TILE_VERTICAL_WALL;
        map[x + (MAP_WIDTH - 1) * MAP_HEIGHT] = TILE_VERTICAL_WALL;
    }
    
    // Places left and right walls on map
    for (int y = 0; y < MAP_WIDTH; ++y)
    {
        map[y * MAP_HEIGHT] = TILE_HORIZONTAL_WALL;
        map[(MAP_HEIGHT - 1) + y * MAP_HEIGHT] = TILE_HORIZONTAL_WALL;
    }
    
    generateFoodOnMap();
}

char getMapCharForValue(int value)
{
    if (value == length)
    {
        // Snake Head
        switch (direction)
        {
            case DIRECTION_RIGHT:
                return '>';
            case DIRECTION_UP:
                return '^';
            case DIRECTION_LEFT:
                return '<';
            case DIRECTION_DOWN:
            default:
                return 'v';
        }
    }
    else if (value > TILE_FREE_SPACE)
    {
        // Snake Body
        return 'o';
    }
    
    switch (value)
    {
        case TILE_VERTICAL_WALL:
            return '|';
        case TILE_HORIZONTAL_WALL:
            return '-';
        case TILE_FOOD:
            return '*';
        case TILE_FREE_SPACE:
        default:
            return ' ';
    }
}

int calcScore()
{
    return length - SNAKE_STARTING_LENGTH;
}
 
void update()
{
    switch (direction)
    {
        case DIRECTION_RIGHT:
            moveSnake(1, 0);
            break;
        case DIRECTION_UP:
            moveSnake(0, -1);
            break;
        case DIRECTION_LEFT:
            moveSnake(-1, 0);
            break;
        case DIRECTION_DOWN:
        default:
            moveSnake(0, 1);
            break;
    }
    
    // Reduce snake values on map by 1 to convey movement
    for (int i = 0; i < MAP_SIZE; ++i)
    {
        if (map[i] > TILE_FREE_SPACE)
        {
            map[i]--;
        }
    }
}

using namespace std;

void render()
{
    // lcd_clear_screen();
// =====================
        lcd_gotoxy(2,0);
        draw_string("Score: " , Pixel_Set, FontSize_3x5);
        int charTmp = calcScore();
        std::stringstream t;

        t << charTmp;
        char const *n_char = 
            t.str().c_str();
        draw_string(n_char, Pixel_Set, FontSize_3x5);
        lcd_send_buff();
// ================
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            int value = map[y + x * MAP_HEIGHT];
            char character = getMapCharForValue(value);

            if(character != ' ') {
                lcd_draw_pixel(x , y + 5, Pixel_Set);
                // draw_string(&character, Pixel_Set, FontSize_3x5);
                lcd_send_buff();
            }
            else {
                lcd_draw_pixel(x , y + 5, Pixel_Clear);
                lcd_send_buff();
            }
        }
    }
}

void runGame()
{
    initMap();
    
    while (!exitGame)
    {
        if (kbhit())
        {
            // If a key is pressed
            changeSnakeDirection(getch());
        }
        
        update();
        
        render();
        
        // Wait for a 1/3 second, meaning the game runs at 3 FPS (frames per second)
        // _sleep(30);
    }
    lcd_clear_screen();
    lcd_gotoxy(0,0);
	draw_string("Game over!" , Pixel_Set, FontSize_3x5);
    lcd_gotoxy(0,6);
    draw_string("Score: " , Pixel_Set, FontSize_3x5);

    int charTmp = calcScore();
    std::stringstream t;

	t << charTmp;
	char const *n_char = 
		t.str().c_str();
	draw_string(n_char, Pixel_Set, FontSize_3x5);
    lcd_send_buff();

    // cout << endl << "Game over!" << endl << "Score: " << calcScore() << endl << endl;
    
    // Stop console from closing instantly
    cin.ignore();
}

int main()
{
    changemode(1);
    
    runGame();
    
    changemode(0);
    
    return 0;
}
