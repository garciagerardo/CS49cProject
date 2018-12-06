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
void printTable(char[3][3]);
void isWinner(char[3][3], bool*, char);
bool isRoom(char[3][3]);
bool taken(int, int, char[3][3]);

//variables
bool win1 = false;
bool win2 = false;
bool winner = false;

int main(int argc, const char * argv[]) {
    char table[3][3] = {{'?', '?', '?'},{'?','?','?'},{'?','?','?'}};
    //first number is row, second is column
    int row = -1, column = -1;
    bool room = true;

    //plays the game
    while(winner == false && room){
        printTable(table);
        printf("Player 1, input coordinates\nEnter row ");
        scanf("%d", &row);
        //checks row is a valid number
        while(row > 2 || row < 0){
            printf("Invalid input for row, please select a number between 0 and 2 ");
            scanf("%d", &row);
        }
        printf("Enter column ");
        scanf("%d", &column);
        //checks column is valid number
        while(column > 2 || column < 0){
            printf("Invalid input for column, please select a number between 0 and 2 ");
            scanf("%d", &column);
        }
        //checks if position is already taken
        while(taken(row, column, table)){
            printf("That position is taken, try again\n");
            printf("Player 1, input coordinates\nEnter row ");
            scanf("%d", &row);
            //checks row is valid number
            while(row > 2 || row < 0){
                printf("Invalid input for row, please select a number between 0 and 2 ");
                scanf("%d", &row);
            }
            printf("Enter column ");
            scanf("%d", &column);
            //checks column is valid number
            while(column > 2 || column < 0){
                printf("Invalid input for column, please select a number between 0 and 2 ");
                scanf("%d", &column);
            }
        }
        table[row][column]= 'x';
        isWinner(table, &win1, 'x');
        room = isRoom(table);
        
        if(win1 == false && room){
            printTable(table);
            printf("Player 2, input coordinates\nEnter row ");
            scanf("%d", &row);
            //checks row is valid number
            while(row > 2 || row < 0){
                printf("Invalid input for row, please select a number between 0 and 2 ");
                scanf("%d", &row);
            }
            printf("Enter column ");
            scanf("%d", &column);
            //checks column is valid number
            while(column > 2 || column < 0){
                printf("Invalid input for column, please select a number between 0 and 2 ");
                scanf("%d", &column);
            }
            //checks if position is already taken
            while(taken(row, column, table)){
                printf("That position is taken, try again\n");
                printf("Player 2, input coordinates\nEnter row ");
                scanf("%d", &row);
                //checks row is valid number
                while(row > 2 || row < 0){
                    printf("Invalid input for row, please select a number between 0 and 2 ");
                    scanf("%d", &row);
                }
                printf("Enter column ");
                scanf("%d", &column);
                //checks column is valid number
                while(column > 2 || column < 0){
                    printf("Invalid input for column, please select a number between 0 and 2 ");
                    scanf("%d", &column);
                }
            }
            table[row][column]= 'o';
            isWinner(table, &win2, 'o');
        }

    }
    printTable(table);
    if(win1 == true)
        printf("Player1 has won!\n");
    else if(win2 == true)
        printf("Player2 has won!\n");
    else
        printf("It's a draw\n");
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
