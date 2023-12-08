#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ROWS 25
#define COLS 25


//춘식이 위치 구조체
typedef struct  
{
    int x;
    int y;
} Position;

// 춘식이 몸무게, 애정도, 건강상태 관리구조체
typedef struct 
{
    double weight;
    int affection;
    int isSick;
} Chunsik;

//게임 맵을 출력하는 함수, 춘식이 위치와 벽을 시각적으로 표시
void printRoom(char room[][COLS], Position *chunsik)  
{
    for (int i = 0; i < ROWS; i++) 
    {
        for (int j = 0; j < COLS; j++) 
        {
            if (i == chunsik->x && j == chunsik->y)
                printf("🦁 ");
            else
                printf("%s ", (room[i][j] == '#') ? "🔥" : "◾");
        }
        printf("\n");
    }
}

//춘식이 랜덤 이동 함수
void moveChunsik(Position *chunsik, char room[][COLS]) 
{
    int direction = rand() % 4;
    int newX = chunsik->x + (direction == 0) - (direction == 1);
    int newY = chunsik->y + (direction == 2) - (direction == 3);

    if (room[newX][newY] != '#') 
    {
        chunsik->x = newX;
        chunsik->y = newY;
    }
}

// 춘식이 밥 먹고 나서 일어나는 상호작용 함수
void eatFood(Chunsik *chunsik) 
{
    chunsik->affection += 5;

    if (chunsik->isSick) 
    {
        printf("병에 걸려서 밥을 먹지 않습니다.\n");
        return;
    }

    chunsik->weight += 0.3;

    if (rand() % 2 == 0) 
    {
        printf("똥을 쌌습니다! -0.2 kg\n");
        chunsik->weight -= 0.2;
    }

    if (rand() % 10 == 0) 
    {
        chunsik->isSick = 1;
        printf("병에 걸렸습니다!\n");
    }
}

//춘식이 병걸렸을 때 상호작용 함수
void handleSickness(Chunsik *chunsik) 
{
    if (chunsik->isSick) 
    {
        printf("병때문에 춘식이는 굶었습니다. -0.5kg!!\n");

        chunsik->weight -= 0.5;

        double recoveryChance = chunsik->affection * 0.1;
        if ((rand() % 100) < recoveryChance) 
        {
            printf("회복했습니다!\n");
            chunsik->isSick = 0;
            return;
        }

        if(chunsik->weight <= 0.0)
        {
            printf("게임 오버! 춘식이가 굶어 죽어버렸습니다.\n");
            printf("죽었을때 몸무게:%.1f kg, 애정도:%d\n", chunsik->weight, chunsik->affection);
            printf("⠀⠀⠀⠀⣀⣀⣀⣀⣀⡀⣀⣀⣀⣀⢀⣀⣀⡀⣀⣀⣀⣀⣀⣀⣀⣀⣀⠀⠀⠀\n");
            printf("⠀⠀⢠⣼⡟⢩⣭⣭⣽⣿⠛⢩⡉⢻⣿⡏⠙⢻⠛⠉⣿⠉⢩⣭⣭⣭⣿⠀⠀⠀\n");
            printf("⠀⠀⢸⡇⠀⣿⣯⠉⢹⡇⠘⠛⠛⠀⢸⡇⢠⡄⣤⠀⣿⠀⢨⣭⣭⣿⢀⠀⠀⠀\n");
            printf("⠀⠀⠘⢻⣷⣈⣉⣀⣸⣇⣸⣿⣿⣀⣼⣇⣸⣿⣿⣀⣿⣀⣈⣉⣉⣉⣿⠀⠀⠀\n");
            printf("⠀⠀⢰⡾⠏⣉⣉⠙⢷⡏⢹⣿⣿⠉⢱⡍⢉⣉⣉⣉⣷⠉⢉⣉⡉⠹⣶⠀⠀⠀\n");
            printf("⠀⠀⢸⡇⠀⣿⣿⠀⢸⣇⠈⠹⠉⢀⣸⡇⢈⣉⣉⣹⣿⠀⠸⠿⢁⣀⣿⠀⠀⠀\n");
            printf("⠀⠀⠸⢧⣄⣛⣛⣠⡼⠟⢿⣄⣤⠿⢻⣇⣘⣛⣛⣛⣿⣀⣸⣤⣀⣙⣿⠀⠀⠀\n");
            printf("⠀⠀⠀⠈⠉⠉⠉⠉⠁⠀⠈⠉⠉⠀⠈⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠀⠀⠀\n");
            printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
            printf("⠀⠀⠀⠀⠀⠀⢀⡀⢀⡏⠁⠉⠉⠉⠉⠉⠙⠓⠒⠒⢲⡀⠀⠀⠀⠀⠀⠀⠀⠀\n");
            printf("⠀⠀⠀⠀⠀⠀⢈⡼⠃⠀⠀⢠⡀⠀⠀⢀⡀⠀⠀⠀⠘⢧⠠⡀⠀⠀⠀⠀⠀⠀\n");
            printf("⠀⠀⠀⠀⠀⢀⡞⠀⢀⡤⢰⣶⠁⠀⠀⢨⡳⡄⡀⠀⠀⠈⢳⠡⠀⠀⠀⠀⠀⠀\n");
            printf("⠀⠀⠀⠀⠀⡞⢠⡖⣋⡞⣲⡖⠚⠛⠒⢦⡭⢦⡙⣆⠀⠀⠘⡇⠇⠀⠀⠀⠀⠀\n");
            printf("⠀⠀⠀⠀⠐⣧⠞⣰⠇⠀⠉⠳⢞⣓⠦⠞⠛⠈⢧⡙⢦⠀⠀⡇⠀⠀⠀⠀⠀⠀\n");
            printf("⠀⠀⢀⡠⠀⢿⢸⠁⠀⠀⠀⠀⠘⠙⠀⠀⠀⠀⠀⢧⡘⢦⢸⣃⣀⠲⢄⡀⠀⠀\n");
            printf("⠀⠀⠉⡴⠒⠛⠻⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣇⣸⠏⠀⠉⠉⠳⣄⠀⠀\n");
            printf("⠀⠀⢸⡅⠀⠀⠀⠈⠛⠶⠦⣤⣤⣤⣤⣤⣤⣤⠶⠞⠋⠀⠀⠀⠀⠀⠀⡼⠀⠀\n");
            printf("⠀⠀⠀⠑⠶⠶⠶⠒⢦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣶⠒⠒⠒⠚⠁⠀⠀\n");
            printf("⠀⠀⠀⠀⠀⠀⠀⠀⠘⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀\n");
            exit(0);
        }

        if (rand() % 10 == 0) 
        {
            printf("게임 오버! 춘식이가 병으로 죽었습니다.\n");
            printf("죽었을때 몸무게:%.1f kg, 애정도:%d\n", chunsik->weight, chunsik->affection);
            printf("⠀⠀⠀⠀⣀⣀⣀⣀⣀⡀⣀⣀⣀⣀⢀⣀⣀⡀⣀⣀⣀⣀⣀⣀⣀⣀⣀⠀⠀⠀\n");
            printf("⠀⠀⢠⣼⡟⢩⣭⣭⣽⣿⠛⢩⡉⢻⣿⡏⠙⢻⠛⠉⣿⠉⢩⣭⣭⣭⣿⠀⠀⠀\n");
            printf("⠀⠀⢸⡇⠀⣿⣯⠉⢹⡇⠘⠛⠛⠀⢸⡇⢠⡄⣤⠀⣿⠀⢨⣭⣭⣿⢀⠀⠀⠀\n");
            printf("⠀⠀⠘⢻⣷⣈⣉⣀⣸⣇⣸⣿⣿⣀⣼⣇⣸⣿⣿⣀⣿⣀⣈⣉⣉⣉⣿⠀⠀⠀\n");
            printf("⠀⠀⢰⡾⠏⣉⣉⠙⢷⡏⢹⣿⣿⠉⢱⡍⢉⣉⣉⣉⣷⠉⢉⣉⡉⠹⣶⠀⠀⠀\n");
            printf("⠀⠀⢸⡇⠀⣿⣿⠀⢸⣇⠈⠹⠉⢀⣸⡇⢈⣉⣉⣹⣿⠀⠸⠿⢁⣀⣿⠀⠀⠀\n");
            printf("⠀⠀⠸⢧⣄⣛⣛⣠⡼⠟⢿⣄⣤⠿⢻⣇⣘⣛⣛⣛⣿⣀⣸⣤⣀⣙⣿⠀⠀⠀\n");
            printf("⠀⠀⠀⠈⠉⠉⠉⠉⠁⠀⠈⠉⠉⠀⠈⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠀⠀⠀\n");
            printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
            printf("⠀⠀⠀⠀⠀⠀⢀⡀⢀⡏⠁⠉⠉⠉⠉⠉⠙⠓⠒⠒⢲⡀⠀⠀⠀⠀⠀⠀⠀⠀\n");
            printf("⠀⠀⠀⠀⠀⠀⢈⡼⠃⠀⠀⢠⡀⠀⠀⢀⡀⠀⠀⠀⠘⢧⠠⡀⠀⠀⠀⠀⠀⠀\n");
            printf("⠀⠀⠀⠀⠀⢀⡞⠀⢀⡤⢰⣶⠁⠀⠀⢨⡳⡄⡀⠀⠀⠈⢳⠡⠀⠀⠀⠀⠀⠀\n");
            printf("⠀⠀⠀⠀⠀⡞⢠⡖⣋⡞⣲⡖⠚⠛⠒⢦⡭⢦⡙⣆⠀⠀⠘⡇⠇⠀⠀⠀⠀⠀\n");
            printf("⠀⠀⠀⠀⠐⣧⠞⣰⠇⠀⠉⠳⢞⣓⠦⠞⠛⠈⢧⡙⢦⠀⠀⡇⠀⠀⠀⠀⠀⠀\n");
            printf("⠀⠀⢀⡠⠀⢿⢸⠁⠀⠀⠀⠀⠘⠙⠀⠀⠀⠀⠀⢧⡘⢦⢸⣃⣀⠲⢄⡀⠀⠀\n");
            printf("⠀⠀⠉⡴⠒⠛⠻⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣇⣸⠏⠀⠉⠉⠳⣄⠀⠀\n");
            printf("⠀⠀⢸⡅⠀⠀⠀⠈⠛⠶⠦⣤⣤⣤⣤⣤⣤⣤⠶⠞⠋⠀⠀⠀⠀⠀⠀⡼⠀⠀\n");
            printf("⠀⠀⠀⠑⠶⠶⠶⠒⢦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣶⠒⠒⠒⠚⠁⠀⠀\n");
            printf("⠀⠀⠀⠀⠀⠀⠀⠀⠘⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀\n");
            exit(0);
        }
    }
}

// 춘식이의 상태, 크기에 따른 변화를 출력하는 함수
void printChunsik(Chunsik *chunsik) 
{
    printf("\n현재 몸무게: %.1f kg, 애정도: %d, %s\n크기: ",
           chunsik->weight, chunsik->affection,
           chunsik->isSick ? "병에 걸렸습니다." : "건강합니다.");

    if (chunsik->weight < 20.0) 
        printf("애기 춘식\n");
    else if (chunsik->weight < 50.0) 
        printf("중간 춘식\n");
    else if (chunsik->weight < 80.0)
        printf("큰 춘식\n");
    else if(chunsik->weight< 100.0)
        printf("대춘식\n");
    else
        printf("거대 춘식\n");
    
}

int main(void) 
{
    srand(time(NULL));

    char room[ROWS][COLS];
    Position chunsik;
    Chunsik myChunsik;

    for (int i = 0; i < ROWS; i++) 
    {
        for (int j = 0; j < COLS; j++) 
        {
            room[i][j] = (i == 0 || i == ROWS - 1 || j == 0 || j == COLS - 1) ? '#' : ' ';
        }
    }

    chunsik.x = rand() % (ROWS - 2) + 1;
    chunsik.y = rand() % (COLS - 2) + 1;

    myChunsik.weight = 10.0;
    myChunsik.affection = 0;
    myChunsik.isSick = 0;

    printf("=== 춘식이 키우기 게임을 시작하겠습니다 ===");
    int turn = 0;
    while (myChunsik.weight < 100.0) 
    {
        printf("\n=== 턴:%d ===\n", turn++);

        moveChunsik(&chunsik, room);

        printf("밥을 먹는다.\n");
        eatFood(&myChunsik);
        handleSickness(&myChunsik);

        printChunsik(&myChunsik);
        printRoom(room, &chunsik);

        usleep(100000); 

        system("clear"); 
    }

    printf("\n=== 축하합니다! 거대 춘식이로 성장했습니다! ===");
    printChunsik(&myChunsik);
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⢀⠤⡄⠀⡀⠀⠀⠀⠀⡀⢀⠠⠀⢀⠄⠀⢄⣞⠍⠄⣱⣂⣀⠀⠀⠀⠀⠀⢠⠆⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⣰⠫⢞⡔⣅⣖⣼⣣⠖⡎⣧⢅⡒⢻⢏⢉⢀⡿⣑⡚⣿⡫⣃⣀⡤⢠⢤⠮⢠⠏⠐⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⢰⠇⢄⡏⡽⣹⢡⢿⣇⡌⣼⣱⢻⢧⠏⡯⠿⡾⠽⠵⣸⢿⢽⡡⡽⢣⢏⢼⡇⠄⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⢿⣠⠞⠛⠁⠡⣨⢆⡼⠙⠃⠅⠈⠺⠐⣀⣐⣡⣤⣦⣥⡀⠀⠀⡀⠈⣡⠞⠀⠐⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠈⠁⠀⠀⠠⠀⠈⠉⠀⠀⣀⡤⠖⠚⠋⠭⠁⠀⠄⠒⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⣩⣿⣽⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣤⣄⢸⣇⡀⠀\n");
    printf("⠀⠀⣭⣼⣧⣤⠀⢀⣠⠼⠛⠷⠶⢶⣤⣀⡀⠀⣀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠋⢸⠏⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⢀⡟⠁⠀⠀⠀⠀⠀⠈⠹⣧⠀⣀⣈⠉⠛⠳⠀⢀⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⣿⣄⡈⠉⠛⢢⡴⣶⣿⣿⣿⣿⣿⣿⣶⣤⡀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⢀⣤⣞⣿⣦⣀⠀⠀⠀⠀⢀⣠⡿⢛⣷⠀⠀⢸⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠻⢶⣤⣀⠀⠀\n");
    printf("⠀⠀⢀⡰⣿⣿⣿⣿⣯⡛⠻⠿⠶⠿⢛⣫⣴⠟⠁⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⡟⠛⠉⠀⠀⣤⠀⠈⠹⣦⠀\n");
    printf("⠀⢠⣿⣿⣿⣿⣿⣿⣿⣿⣦⣀⣴⠶⠛⠉⠀⠀⠀⠀⠀⠀⠀⠈⠻⣿⣿⠿⣿⠃⠀⠘⣻⡆⣰⣿⣦⠀⣹⡇\n");
    printf("⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⣦⣿⡄⠀⠀⠹⣿⣯⡾⠟⣳⣿⣆\n");
    printf("⠀⠈⠙⠻⣿⣿⣿⠟⠋⠀⠀⢠⡶⢶⣤⣤⣄⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢿⣿⣦⣀⣀⣙⣩⣴⠿⣿⡿⠃\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⡞⠃⠀⢠⡄⠀⣉⡙⠛⢻⡆⠀⠀⠀⠀⠀⠀⠀⠀⠘⢿⣭⣛⣹⡟⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⢀⣤⣼⡇⠀⢀⣸⣿⣅⡀⣯⡅⠀⠈⢿⡄⠀⠀⠀⠀⠀⣀⣤⠆⠀⠈⠉⠉⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⣿⠀⣿⠀⠀⠸⢿⣭⣉⣻⡿⠀⠀⠀⢸⡇⠀⠀⢀⣤⠞⠋⢀⣴⠞⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠹⣧⢻⣧⡀⠀⢸⣿⡿⠋⠁⠀⣀⣴⡾⠷⢦⡀⠈⠁⣠⠾⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠙⣷⡙⠻⢶⣦⣭⣤⣄⣤⡾⠋⠁⠀⢀⣼⠇⠰⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⢀⣴⣶⣼⣷⣶⣦⣬⣍⡉⠉⠉⠀⢀⣤⡶⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⢾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣼⠟⠁⠀⠀⢠⣶⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠈⠻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡀⠀⠀⢀⣸⣿⣅⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠙⠻⢿⣿⣿⣿⣿⣿⣿⠀⠀⠈⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠛⠛⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    return 0;
}