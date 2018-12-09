//
//  main.c
//  Final Project
//
//  Created by Jerry Garcia on 12/4/18.
//  Copyright © 2018 Jerry Garcia. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>

//prototypes
void playTheGame(void);
void resetTheGame(void);
void printTable(char[3][3]);
void isWinner(char[3][3], bool*, char);
bool isRoom(char[3][3]);
bool taken(int, int, char[3][3]);
void getInputs(int*, int*);
void printStats(void);
void playFakeGame(void); 

//variables
bool win1 = false;
bool win2 = false;
bool winner = false;

int player1WinCount = 0;
int player2WinCount = 0;
int drawCount = 0;


int main(int argc, const char * argv[]) {
    puts("Welcome to Tic Tac Toe");
    puts("This will be a 10 round tournament");
    
    for(int i = 1; i <= 10; i++)
    {
        printf("Round %d \n", i);
        //playTheGame();
        playFakeGame();
        resetTheGame();
        puts(" ");
    }
    
    //statistics part
    printStats();
}

void playTheGame()
{
    char table[3][3] = {{'?', '?', '?'},{'?','?','?'},{'?','?','?'}};
    //first number is row, second is column
    int row = -1, column = -1;
    bool room = true;
    
    //plays the game
    while(winner == false && room){
        printTable(table);
        printf("Player 1, input coordinates\n");
        getInputs(&row, &column);
        
        //checks if position is already taken
        while(taken(row, column, table)){
            printf("That position is taken, try again\n");
            printf("Player 1, input coordinates\n");
            getInputs(&row, &column);
        }
        table[row][column]= 'x';
        isWinner(table, &win1, 'x');
        room = isRoom(table);
        
        if(win1 == false && room){
            printTable(table);
            printf("Player 2, input coordinates\n");
            getInputs(&row, &column);
            
            //checks if position is already taken
            while(taken(row, column, table)){
                printf("That position is taken, try again\n");
                printf("Player 2, input coordinates\n");
                getInputs(&row, &column);
            }
            table[row][column]= 'o';
            isWinner(table, &win2, 'o');
        }
        
    }
    printTable(table);
    if(win1 == true)
    {
        printf("Player1 has won!\n");
        player1WinCount++;
    }
    else if(win2 == true)
    {
        printf("Player2 has won!\n");
        player2WinCount++;
    }
    else
    {
        printf("It's a draw\n");
        drawCount++;
    }
}

void resetTheGame()
{
    win1 = false;
    win2 = false;
    winner = false;
}

void printTable(char table[3][3]){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            printf("%c ", table[i][j]);
        }
        printf("\n");
    }
}

void isWinner(char table[3][3], bool *won, char sym){
    for(int i = 0; i < 3; i++){
        if(sym == table[i][0] && sym == table[i][1] && sym == table[i][2]){
            *won = true;
            winner = true;
        }
    }
    for(int i = 0; i < 3; i++){
        if(sym == table[0][i] && sym == table[1][i] && sym == table[2][i]){
            *won = true;
            winner = true;
        }
    }

    if(sym == table[0][0] && sym == table[1][1] && sym == table[2][2]){
        *won = true;
        winner = true;
    }
    if(sym == table[0][2] && sym == table[1][1] && sym == table[2][0]){
        *won = true;
        winner = true;
    }
}

bool isRoom(char table[3][3]){
    for(int i = 0;i < 3; i++){
        for(int j = 0; j < 3;j++){
            if(table[i][j] == '?')
                return true;
        }
    }
    return false;
}

bool taken(int row, int column, char table[3][3]){
    if(table[row][column] == '?')
        return false;
    else
        return true;
}

void getInputs(int *rowptr, int *columnptr){
    printf("Enter row ");
    scanf("%d", rowptr);
    //checks row is a valid number
    while(*rowptr > 2 || *rowptr < 0){
        printf("Invalid input for row, please select a number between 0 and 2 ");
        scanf("%d", rowptr);
    }
    printf("Enter column ");
    scanf("%d", columnptr);
    //checks column is valid number
    while(*columnptr > 2 || *columnptr < 0){
        printf("Invalid input for column, please select a number between 0 and 2 ");
        scanf("%d", columnptr);
    }
}

void printStats()
{
    printf("Player 1 won %d times \n", player1WinCount);
    printf("Player 2 won %d times \n", player2WinCount);
    printf("It was a draw %d times \n", drawCount);
}

void playFakeGame()
{
    //plays a fake game where P1 wins
    
    char table[3][3] = {{'?', '?', '?'},{'?','?','?'},{'?','?','?'}};
    
    table[2][2]= 'x';
    table[0][0]= 'o';
    table[0][2]= 'x';
    table[1][1]= 'o';
    table[1][2]= 'x';
    
    isWinner(table, &win1, 'x');
    isWinner(table, &win2, 'o');
    
    printTable(table);
    if(win1 == true)
    {
        printf("Player1 has won!\n");
        player1WinCount++;
    }
    else if(win2 == true)
    {
        printf("Player2 has won!\n");
        player2WinCount++;
    }
    else
    {
        printf("It's a draw\n");
        drawCount++;
    }
}
