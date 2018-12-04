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

bool win1 = false;
bool win2 = false;
bool winner = false;

int main(int argc, const char * argv[]) {
    char table[3][3] = {{'?', '?', '?'},{'?','?','?'},{'?','?','?'}};
    //first number is row, second is column
    int row = -1, column = -1;

    printTable(table);

    while(winner == false){
        printTable(table);
        printf("Player 1, input coordinates\nEnter row ");
        scanf("%d", &row);
        printf("Enter column ");
        scanf("%d", &column);
        table[row][column]= 'x';
        isWinner(table, &win1, 'x');
        
        if(win1 == false){
            printTable(table);
            printf("Player 2, input coordinates\nEnter row ");
            scanf("%d", &row);
            printf("Enter column ");
            scanf("%d", &column);
            table[row][column]= 'o';
            isWinner(table, &win1, 'o');
        }

    }
    printTable(table);
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
