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
void getShortestLongestGame(void);
void bubbleSort(int moves[], int games[], int size);
void playFakeGames(char input);

//variables
bool win1 = false;
bool win2 = false;
bool winner = false;

int player1WinCount = 0;
int player2WinCount = 0;
int drawCount = 0;

int movesCount[10];
int moves;


int main(int argc, const char * argv[]) {
    puts("Welcome to Tic Tac Toe");
    
    ///*
    puts("This will be a 10 round tournament");
    
    for(int i = 1; i <= 10; i++)
    {
        printf("Round %d \n", i);
        //playTheGame();
        
        if(i == 5)
            playFakeGames('S');
        else if(i == 1)
            playFakeGames('D');
        else if(i % 2 == 0)
            playFakeGames('A');
        else
            playFakeGames('B');
        
        movesCount[i-1] = moves;
        
        printf("moves: %d\n", moves);
        
        resetTheGame();
        puts(" ");
    }
    
    //statistics part
    printStats();
    getShortestLongestGame();
    
   //*/
    
//    playTheGame();
//    printf("moves: %d\n", moves);
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
        moves++;
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
            moves++;
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
    
    moves = 0;
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
    printf("Player 1 won %d time(s) \n", player1WinCount);
    printf("Player 2 won %d time(s) \n", player2WinCount);
    printf("It was a draw %d time(s) \n\n", drawCount);
}

void getShortestLongestGame()
{
    int gameOrder[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    bubbleSort(movesCount, gameOrder, 10);
    
    int shortestMoves = movesCount[0];
    int shortestGame = gameOrder[0];
    
    printf("Shortest game was game %d with %d moves \n", shortestGame, shortestMoves);
    //print the moves for the shortest game
    
    
    int longestMoves = movesCount[9];
    int longestGame = gameOrder[9];
    
    printf("Longest game was game %d with %d moves \n", longestGame, longestMoves);
    
    //print the moves for the longest game
}

void bubbleSort(int moves[], int games[], int size)
{
    for (unsigned int pass = 1; pass < size; ++pass) {
        // loop to control number of comparisons per pass
        for (size_t i = 0; i < size - 1; ++i) {
            
            // compare adjacent elements and swap them if first
            // element is greater than second element
            if (moves[i] > moves[i + 1]) {
                int hold = moves[i];
                moves[i] = moves[i + 1];
                moves[i + 1] = hold;
                
                //also swap order of games for continuity
                hold = games[i];
                games[i] = games[i + 1];
                games[i + 1] = hold;
            }
        }
    }
}



/*
    FOR TESTING ONLY
 */

void playFakeGames(char input)
{
    char table[3][3] = {{'?', '?', '?'},{'?','?','?'},{'?','?','?'}};
    
    if(input == 'A')
    {
        //plays a fake game where P1 wins
        table[1][1]= 'x';
        table[0][0]= 'o';
        table[0][2]= 'x';
        table[2][0]= 'o';
        table[1][0]= 'x';
        table[0][1]= 'o';
        table[1][2]= 'x';
        
        moves = 7;
    }
    else if(input == 'B')
    {
        //plays a fake game where P2 wins
        table[2][2]= 'x';
        table[0][0]= 'o';
        table[1][1]= 'x';
        table[0][2]= 'o';
        table[2][0]= 'x';
        table[0][1]= 'o';
        
        moves = 6;
    }
    else if(input == 'S')
    {
        //plays a fake game where P1 wins and it's short
        table[2][2]= 'x';
        table[0][0]= 'o';
        table[0][2]= 'x';
        table[1][1]= 'o';
        table[1][2]= 'x';
        
        moves = 5;
    }
    else if(input == 'D')
    {
        //plays a fake game where they draw
        table[1][1]= 'x';
        table[0][0]= 'o';
        table[0][2]= 'x';
        table[2][0]= 'o';
        table[1][0]= 'x';
        table[1][2]= 'o';
        table[0][1]= 'x';
        table[2][1]= 'o';
        table[2][2]= 'x';
        
        moves = 9;
    }
    else
        puts("something went wrong");
    
    
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
