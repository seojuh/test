#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ROWS 25
#define COLS 25

#define SMALL_SIZE_THRESHOLD 20.0
#define MEDIUM_SIZE_THRESHOLD 50.0
#define LARGE_SIZE_THRESHOLD 80.0
#define GIANT_SIZE_THRESHOLD 100.0

typedef struct 
{
    int x;
    int y;
}Position;

typedef struct
{
    double weight; 
    int affection;
    int issick;
}Chunsik;

void printroom(char room[][COLS], Position*chunsik)
{
    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLS; j++)
        {
            if(i==chunsik->x && j==chunsik->y)
                printf("🦁 ");
            else
                printf("%s ",(room[i][j]=='#')?"🔥":"◾");
        }
        printf("\n");
    }
}

void moveChunsik(Position*chunsik, char room[][COLS])
{
    int direction = rand()%4;
    int newX= chunsik->x + (direction == 0) - (direction ==1);
    int newY= chunsik->y + (direction == 2) - (direction == 3);

    if(room[newX][newY] != '#')
    {
            chunsik->x = newX;
            chunsik->y = newY;
    }
}

void eatFood(Chunsik*chunsik)
{
    chunsik->affection +=5;

    if(chunsik->issick)
    {
        printf("병에 걸려서 밥을 먹지 않습니다.\n");
        return;
    }
    chunsik->weight+=0.3;
    if(rand()%2 == 0)
    {
        printf("똥을 쌌습니다! -0.2kg\n");
        chunsik->weight -=0.2;
    }
    if(rand()%10 == 0)
    {
        chunsik ->issick =1;
        printf("병에 걸렸습니다\n");
    }
}

void handleSickness(Chunsik*chunsik)
{
    if(chunsik->issick)
    {
        printf("병때문에 춘식이는 굶었습니다. -0.5kg!!\n");

        chunsik ->weight -=0.5;

        double recoverychance = chunsik->affection*0.1;
        if((rand()%100)< recoverychance)
        {
            printf("회복했습니다!\n");
            chunsik ->issick = 0;
            return;
        }

        if(chunsik->weight <=0.0)
        {
            printf("게임오버! 춘식이가 굶어 죽어버렸습니다!\n");
            printf("죽었을때 몸무게:%.1fkg, 애정도:%d\n",chunsik->weight, chunsik->affection);
            exit(0);
        }
        if(rand()%10==0)
        {
            printf("게임오버! 춘식이가 병에 걸려 죽어버렸습니다!\n");
            printf("죽었을때 몸무게:%.1fkg, 애정도:%d\n",chunsik->weight, chunsik->affection);
            exit(0);
        }
    }
}

void printChunsik(Chunsik*chunsik)
{
    printf("\n현재 몸무게:%.1f kg, 애정도:%d, %s\n크기: ", chunsik->weight, chunsik->affection, chunsik->issick ? "병에 걸렸습니다.":"건강합니다");

    if(chunsik->weight<SMALL_SIZE_THRESHOLD)
        printf("애기춘식\n");
    else if(chunsik->weight<MEDIUM_SIZE_THRESHOLD)
        printf("중간춘식\n");
    else if(chunsik->weight<LARGE_SIZE_THRESHOLD)
        printf("큰춘식\n");
    else if(chunsik->weight<GIANT_SIZE_THRESHOLD)
        printf("대춘식\n");
    else
        printf("거대춘식\n");    
}

int main(void)
{
    srand(time(NULL));

    char room[ROWS][COLS];
    Position chunsik;
    Chunsik mychunsik;

    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLS; j++)
        {
            room[i][j]=(i==0 || i==ROWS-1 || j==0 || j==COLS-1)?'#':' ';

        }
    }
    chunsik.x = rand() % (ROWS -2)+1;
    chunsik.y = rand() % (COLS- 2)+1;

    mychunsik.weight = 10.0;
    mychunsik.affection=0;
    mychunsik.issick=0;
    
    printf("===춘식이 키우기 게임을 시작하겠습니다 ===");
    int turn = 0;
    while(mychunsik.weight<100.0)
    {
        printf("\n===턴:%d===\n", turn++);

        moveChunsik(&chunsik,room);

        printf("밥을먹는다.\n");
        eatFood(&mychunsik);
        handleSickness(&mychunsik);

        printChunsik(&mychunsik);
        printroom(room, &chunsik);

        usleep(100000);

        system("clear");
    }
    printf("\n=== 축하합니다! 거대 춘식이로 성장했습니다!===\n");
    printChunsik(&mychunsik);
    return 0;
}