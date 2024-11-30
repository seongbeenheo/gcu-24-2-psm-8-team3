#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5       // 맵의 크기
#define MINES 5      // 지뢰의 수

// 게임 보드 및 표시를 위한 배열 선언
char board[SIZE][SIZE];
char display[SIZE][SIZE];
int mines[SIZE][SIZE]; // 지뢰 위치를 표시하는 배열

// 함수 선언
void initialize();
void placeMines();
void calculateMines();
void printBoard();
int checkMine(int row, int col);
void reveal(int row, int col);

int main() {
    int row, col;
    int safeSquares = SIZE * SIZE - MINES; // 지뢰가 없는 칸의 수
    int moves = 0;
    clock_t start, end; // 시간을 저장할 변수 선언

    start = clock(); // 게임 시작 시간 기록

    initialize();
    placeMines();
    calculateMines();

    while (1) {
        printBoard();

        printf("Enter row and column to reveal (0-%d): ", SIZE - 1);
        scanf("%d %d", &row, &col);

        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) {
            printf("Invalid position. Try again.\n");
            continue;
        }

        if (checkMine(row, col)) {
            printf("BOOM! You hit a mine. Game Over.\n");
            break;
        } else {
            reveal(row, col);
            moves++;

            if (moves == safeSquares) {
                end = clock(); // 게임 종료 시간 기록
                double timeTaken = (double)(end - start) / CLOCKS_PER_SEC; // 경과 시간 계산
                printf("Congratulations! You've cleared the board without hitting a mine.\n");
                printf("Time taken: %.2f seconds\n", timeTaken);
                break;
            }
        }
    }

    return 0;
}

// 게임 초기화 함수
void initialize() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '0';
            display[i][j] = '-';
            mines[i][j] = 0;
        }
    }
}

// 지뢰 배치 함수
void placeMines() {
    srand(time(NULL));
    int placedMines = 0;

    while (placedMines < MINES) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;

        if (mines[row][col] == 0) {
            mines[row][col] = 1;
            board[row][col] = '*';
            placedMines++;
        }
    }
}

// 주변 지뢰 개수 계산 함수
void calculateMines() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (mines[i][j] == 1) continue;

            int count = 0;
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    int ni = i + x, nj = j + y;
                    if (ni >= 0 && ni < SIZE && nj >= 0 && nj < SIZE && mines[ni][nj] == 1)
                        count++;
                }
            }
            board[i][j] = '0' + count;
        }
    }
}

// 현재 보드 출력 함수
void printBoard() {
    printf("\nCurrent Board:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", display[i][j]);
        }
        printf("\n");
    }
}

// 지뢰 확인 함수
int checkMine(int row, int col) {
    return mines[row][col] == 1;
}

// 칸 열기 함수
void reveal(int row, int col) {
    if (display[row][col] != '-') return;
    display[row][col] = board[row][col];
    if (board[row][col] == '0') {
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                int ni = row + x, nj = col + y;
                if (ni >= 0 && ni < SIZE && nj >= 0 && nj < SIZE)
                    reveal(ni, nj);
            }
        }
    }
}
