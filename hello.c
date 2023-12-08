#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>

#define ROWS 25
#define COLS 25

typedef struct
{
    int x;
    int y;
} Position;

typedef struct
{
    int x;
    int y;
} Enemy;

void printMap(char map[][COLS], Position *pacman, Enemy *enemies, int numEnemies)
{
    system("clear"); // 화면을 지우는 명령

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            char symbol = ' ';
            if (i == pacman->x && j == pacman->y)
                symbol = 'C';
            else
            {
                for (int k = 0; k < numEnemies; k++)
                {
                    if (i == enemies[k].x && j == enemies[k].y)
                    {
                        symbol = 'E';
                        break;
                    }
                }
                if (map[i][j] == '#')
                    symbol = '■';
            }
            printf("%c ", symbol);
        }
        printf("\n");
    }
}

char getKeyPress()
{
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void movePacman(Position *pacman, char map[][COLS], Enemy *enemies, int numEnemies)
{
    // 최적의 방향을 찾기 위한 초기화
    int optimalDirection = -1; // -1은 초기값으로 설정
    int minDistance = ROWS * COLS; // 최소 거리를 초기화

    // 팩맨의 현재 위치
    int px = pacman->x;
    int py = pacman->y;

    // 모든 방향에 대해 거리를 계산하고 최적의 방향을 찾음
    for (int direction = 0; direction < 4; direction++)
    {
        int newX = px;
        int newY = py;

        switch (direction)
        {
        case 0:
            newX--;
            break;
        case 1:
            newX++;
            break;
        case 2:
            newY--;
            break;
        case 3:
            newY++;
            break;
        }

        if (newX >= 0 && newX < ROWS && newY >= 0 && newY < COLS && map[newX][newY] != '#')
        {
            // 팩맨이 해당 방향으로 이동했을 때의 거리 계산
            int totalDistance = 0;
            for (int i = 0; i < numEnemies; i++)
            {
                totalDistance += abs(enemies[i].x - newX) + abs(enemies[i].y - newY);
            }

            // 최소 거리보다 작으면 최적의 방향을 업데이트
            if (totalDistance < minDistance)
            {
                minDistance = totalDistance;
                optimalDirection = direction;
            }
        }
    }

    // 최적의 방향으로 팩맨 이동
    if (optimalDirection != -1)
    {
        switch (optimalDirection)
        {
        case 0:
            pacman->x--;
            break;
        case 1:
            pacman->x++;
            break;
        case 2:
            pacman->y--;
            break;
        case 3:
            pacman->y++;
            break;
        }
    }
}

void moveEnemies(Enemy *enemies, int numEnemies, Position *pacman)
{
    for (int i = 0; i < numEnemies; i++)
    {
        // 랜덤 방향 설정
        char directions[] = {'w', 's', 'a', 'd'};
        char direction = directions[rand() % 4];

        int deltaX = (enemies[i].x < pacman->x) ? 1 : (enemies[i].x > pacman->x) ? -1 : 0;
        int deltaY = (enemies[i].y < pacman->y) ? 1 : (enemies[i].y > pacman->y) ? -1 : 0;

        int newX = enemies[i].x + deltaX;
        int newY = enemies[i].y + deltaY;

        if (newX >= 0 && newX < ROWS && newY >= 0 && newY < COLS)
        {
            enemies[i].x = newX;
            enemies[i].y = newY;
        }
    }
}

int checkCollision(Position *pacman, Enemy *enemies, int numEnemies)
{
    for (int i = 0; i < numEnemies; i++)
    {
        if (pacman->x == enemies[i].x && pacman->y == enemies[i].y)
            return 1; // 충돌 발생
    }
    return 0; // 충돌 없음
}

int main(void)
{
    srand(time(NULL));

    char map[ROWS][COLS];
    Position pacman;
    Enemy enemies[0]; // 3개의 적 추가
    int numEnemies = sizeof(enemies) / sizeof(enemies[0]);

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            map[i][j] = (i == 0 || i == ROWS - 1 || j == 0 || j == COLS - 1 || (i == ROWS / 2 && j == COLS / 2)) ? '#' : ' ';
        }
    }

    pacman.x = ROWS / 2;
    pacman.y = COLS / 2;

    // 적의 초기 위치 설정
    for (int i = 0; i < numEnemies; i++)
    {
        enemies[i].x = rand() % ROWS;
        enemies[i].y = rand() % COLS;
    }

    printf("=== 간단한 팩맨 게임을 시작합니다 ===\n");

    while (1)
    {
        movePacman(&pacman, map, enemies, numEnemies);
        moveEnemies(enemies, numEnemies, &pacman);

        if (checkCollision(&pacman, enemies, numEnemies))
        {
            printf("게임 오버! 팩맨이 적에게 잡혔습니다.\n");
            break;
        }

        printf("\n");
        printMap(map, &pacman, enemies, numEnemies);

        usleep(300000);
    }

    return 0;
}