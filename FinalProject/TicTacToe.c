//
//  main.c
//  Final Project
//
//  By: Jerry Garcia and Marietta Asemwota
//  Copyright © 2018 Jerry Garcia. All rights reserved.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define SIZE 80 //for the stack

//prototypes
void playTheGame(void);
void resetTheGame(void);
void printTable(char[3][3]);
void isWinner(char[3][3], bool*, char);
bool isRoom(char[3][3]);
bool taken(int, int, char[3][3]);
void getInputs(int*, int*);

//the analysis part
void printStats(void);
void getShortestLongestGame(void);
void bubbleSort(int moves[], int games[], int size);
void printMoves(int game);
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

// the stack part
struct stackNode {
    struct stackNode *nextPtr; // stackNode pointer
    int data[]; // define data as an int array
};

typedef struct stackNode StackNode; // synonym for struct stackNode
typedef StackNode *StackNodePtr; // synonym for StackNode*

// prototypes
void push(StackNodePtr *topPtr, int*);
int *pop(StackNodePtr *topPtr);
int isEmpty(StackNodePtr topPtr);
void printStack(StackNodePtr currentPtr);

StackNodePtr stackPtr;
StackNodePtr gameMoves[10]; //array of each game stack


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
        
        movesCount[i-1] = moves; //keep track of how many moves this round
        gameMoves[i-1] = stackPtr; //keep track of the moves for this round
        
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

    //initialize the stack
    stackPtr = NULL; // points to stack top
    
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
        int move[] = {'x', row, column};
        push(&stackPtr, move);
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
            int move[] = {'o', row, column};
            push(&stackPtr, move);
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
    printMoves(shortestGame); //print the moves for the shortest game
    
    int longestMoves = movesCount[9];
    int longestGame = gameOrder[9];
    
    printf("Longest game was game %d with %d moves \n", longestGame, longestMoves);
    printMoves(longestGame); //print the moves for the longest game
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

/**
 For the given game, print the moves for that game in a table
 */
void printMoves(int game)
{
    StackNodePtr myStackPtr = gameMoves[game-1]; //get the game moves stack
    //printStack(myStackPtr);  //-- for testing
    
    char table[3][3] = {{'?', '?', '?'},{'?','?','?'},{'?','?','?'}};
    
    //place the moves back onto a table
    while (!isEmpty(myStackPtr)) {
        int *move = pop(&myStackPtr);
        char c =  move[0];
        int row = move[1];
        int column = move[2];
        
        table[row][column]= c;
    }
    
    //find out who won that game
    isWinner(table, &win1, 'x');
    isWinner(table, &win2, 'o');
    
    printTable(table);
    if(win1 == true)
    {
        printf("Which Player1 won\n\n");
        player1WinCount++;
    }
    else if(win2 == true)
    {
        printf("Which Player2 won\n\n");
        player2WinCount++;
    }
    else
    {
        printf("Which was a draw\n\n");
        drawCount++;
    }
    
    resetTheGame();
}



// insert a node at the stack top
void push(StackNodePtr *topPtr, int info[])
{
    StackNodePtr newPtr = malloc(sizeof(StackNode) + 18 * sizeof(int)); //array stored inside struct
    
    // insert the node at stack top
    if (newPtr != NULL) {
        newPtr->data[0] = info[0];
        newPtr->data[1] = info[1];
        newPtr->data[2] = info[2];
        newPtr->nextPtr = *topPtr;
        *topPtr = newPtr;
    }
    else { // no space available
        printf("%d not inserted. No memory available.\n", *info);
    }
}

// remove a node from the stack top
int *pop(StackNodePtr *topPtr)
{
    StackNodePtr tempPtr = *topPtr;
    int *popValue = (*topPtr)->data;
    *topPtr = (*topPtr)->nextPtr;
    free(tempPtr);
    return popValue;
}

// print the stack
void printStack(StackNodePtr currentPtr)
{
    // if stack is empty
    if (currentPtr == NULL) {
        puts("The stack is empty.\n");
    }
    else {
        puts("The stack is:");
        
        // while not the end of the stack
        while (currentPtr != NULL) {
            int *move = &(*currentPtr->data);
            char c =  move[0];
            printf("%c ", c);
            printf("%d ", move[1]);
            printf("%d --> ", move[2]);
            currentPtr = currentPtr->nextPtr;
        }
        
        puts("NULL\n");
    }
}

// return 1 if the stack is empty, 0 otherwise
int isEmpty(StackNodePtr topPtr)
{
    return topPtr == NULL;
}


/*
    FOR TESTING ONLY
 */

void playFakeGames(char input)
{
    char table[3][3] = {{'?', '?', '?'},{'?','?','?'},{'?','?','?'}};
    
    //initialize the stack
    stackPtr = NULL; // points to stack top
    
    if(input == 'A')
    {
        //plays a fake game where P1 wins
        table[1][1]= 'x'; //1
        table[0][0]= 'o'; //2
        table[0][2]= 'x'; //3
        table[2][0]= 'o'; //4
        table[1][0]= 'x'; //5
        table[0][1]= 'o'; //6
        table[1][2]= 'x'; //7
        
        int move[] = {'x', 1, 1};
        push(&stackPtr, move);
        int move2[] = {'o', 0, 0};
        push(&stackPtr, move2);
        int move3[] = {'x', 0, 2};
        push(&stackPtr, move3);
        int move4[] = {'o', 2, 0};
        push(&stackPtr, move4);
        int move5[] = {'x', 1, 0};
        push(&stackPtr, move5);
        int move6[] = {'o', 0, 1};
        push(&stackPtr, move6);
        int move7[] = {'x', 1, 2};
        push(&stackPtr, move7);
        
        moves = 7;
    }
    else if(input == 'B')
    {
        //plays a fake game where P2 wins
        table[2][2]= 'x'; //1
        table[0][0]= 'o'; //2
        table[1][1]= 'x'; //3
        table[0][2]= 'o'; //4
        table[2][0]= 'x'; //5
        table[0][1]= 'o'; //6
        
        int move1[] = {'x', 2, 2};
        push(&stackPtr, move1);
        int move2[] = {'o', 0, 0};
        push(&stackPtr, move2);
        int move3[] = {'x', 1, 1};
        push(&stackPtr, move3);
        int move4[] = {'o', 0, 2};
        push(&stackPtr, move4);
        int move5[] = {'x', 2, 0};
        push(&stackPtr, move5);
        int move6[] = {'o', 0, 1};
        push(&stackPtr, move6);
        
        moves = 6;
    }
    else if(input == 'S')
    {
        //plays a fake game where P1 wins and it's short
        table[2][2]= 'x'; //1
        table[0][0]= 'o'; //2
        table[0][2]= 'x'; //3
        table[1][1]= 'o'; //4
        table[1][2]= 'x'; //5
        
        int move1[] = {'x', 2, 2};
        push(&stackPtr, move1);
        int move2[] = {'o', 0, 0};
        push(&stackPtr, move2);
        int move3[] = {'x', 0, 2};
        push(&stackPtr, move3);
        int move4[] = {'o', 1, 1};
        push(&stackPtr, move4);
        int move5[] = {'x', 1, 2};
        push(&stackPtr, move5);
        
        moves = 5;
    }
    else if(input == 'D')
    {
        //plays a fake game where they draw
        table[1][1]= 'x'; //1
        table[0][0]= 'o'; //2
        table[0][2]= 'x'; //3
        table[2][0]= 'o'; //4
        table[1][0]= 'x'; //5
        table[1][2]= 'o'; //6
        table[0][1]= 'x'; //7
        table[2][1]= 'o'; //8
        table[2][2]= 'x'; //9
        
        int move1[] = {'x', 1, 1};
        push(&stackPtr, move1);
        int move2[] = {'o', 0, 0};
        push(&stackPtr, move2);
        int move3[] = {'x', 0, 2};
        push(&stackPtr, move3);
        int move4[] = {'o', 2, 0};
        push(&stackPtr, move4);
        int move5[] = {'x', 1, 0};
        push(&stackPtr, move5);
        int move6[] = {'o', 1, 2};
        push(&stackPtr, move6);
        int move7[] = {'x', 0, 1};
        push(&stackPtr, move7);
        int move8[] = {'o', 2, 1};
        push(&stackPtr, move8);
        int move9[] = {'x', 2, 2};
        push(&stackPtr, move9);
        
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
    
    //printStack(stackPtr);
}
