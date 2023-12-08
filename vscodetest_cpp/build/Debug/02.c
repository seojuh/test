#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    // 변수 지정 시작
    int battle_cnt = 0;    // 전투 횟수
    int win_cnt = 0;       // 이긴 횟수
    int lose_cnt = 0;      // 진 횟수
    int warning_point = 0; // 경험치 0일 때 경고주기. 2되면 게임오버
    int user_level = 1;    // 사용자 레벨. 1부터 시작하고 50되면 게임 종료(사용자 승리)
    float user_exp = 0;    // 사용자 경험치
    char test;             // 게임 시작 함수 -> 필요없는 값
    int level_up = 100;    // 임의로 정한 1레벨당 경험치
    int game_over = 0;     // 버그수정을 위해 게임종료변수추가_ 제발일해
    int enemy_level;       // 적의 레벨 난수로 결정
    int plus_or_minus;     // 적의 레벨 높낮이 난수로 결정
    int wanna_game;        // 다시게임할지 물음

    // 게임 시작
    printf("  코딩                  수련생\n");
    printf("  몬스터                 lv.1\n");
    printf("  ( •_•)                (•_• )\n");
    printf("   ( ง )ง               ୧( ୧ )\n");
    printf("   /︶\\                  /︶\\\n");
    printf("==========================================================\n");
    printf("게임을 시작합니다! 여기는 코딩 인내의 숲길\n");
    printf("C언어 몬스터를 물리쳐야 이곳을 빠져나갈 수 있습니다.\n");
    printf("하지만 당신의 현실은 평범한 수련생 1...\n");
    printf("열심히 수련해 레벨 50이 되면 던전파티에 껴준다고 합니다.\n");
    printf("수련을 위해 수련장으로 이동합니다...\n");
    printf("시작하려면 엔터를 눌러 주세요...");
    scanf("%c", &test); // 형식 지정자를 %c로 하면 엔터(enter)도 하나의 공백 문자로서 입력 받을 수 있다.
    system("clear");

    while (game_over != 1)
    {
        printf("==========================================================\n");
        printf("수련장에 도착했습니다.\n");

        // 적들 등장
        printf("당신의 현재 레벨은 %d입니다.\n", user_level);
        printf("가위바위보를 5343422시간동안 마스터한 적들이 등장합니다...\n");
        printf("==========================================================\n");
        srand(time(NULL));              // 타임값으로 시드값 결정
        enemy_level = rand() % 3 + 1;   // 적의 레벨 난수로 결정
        plus_or_minus = rand() % 2 + 1; // 적의 레벨 높낮이 난수로 결정
        if (plus_or_minus == 1)
        { // 마이너스(-)
            if (user_level - enemy_level <= 0)
            { // 유저 레벨 - 몬스터 레벨이 마이너스 값이 나오면
                enemy_level = 1;
            } // 0을 반환해줌
            if (user_level - enemy_level > 0)
            {
                enemy_level = user_level - enemy_level; // 그렇지 않으면 양수값 반환
            }
        }
        if (plus_or_minus == 2) // 플러스(+)
        {
            enemy_level = enemy_level + user_level;
        }
        printf("사용자:%d, 적: %d", user_level, enemy_level); // 겜제작자 위한 레벨 비교부분
        printf("레벨 %d의 몬스터가 등장했습니다!\n", enemy_level);

        // 적들과 레벨 비교. 유저가 더 높으면 자동 승리
        if (enemy_level >= user_level)
        {
            printf("이기기 조금 힘든 상대 같습니다...\n게임에 응하시겠습니까?\n");
            printf("1. 게임 참가, 2. 도망친다: ");
            scanf("%d", &wanna_game);
            system("clear");
            if (wanna_game == 1)
            { // 유저가 전투에 참가 결정
                battle_cnt++;
                int computer_choice = rand() % 3 + 1; // 몬스터가 선택하는 가위바위보
                int user_choice;                      // 사용자 선택 함수
                int win_cnt = 0;                      // 사용자가 적보다 레벨이 낮을 때 이긴 횟수 세줌
                while (1)
                { // 가위바위보 게임 시작
                    printf("전투를 시작합니다!\n");
                    printf("1. 가위, 2.주먹, 3.보 \n");
                    printf("선택하세요: \n");
                    scanf("%d", &user_choice);
                    getchar();
                    if (user_choice == computer_choice)
                    {
                        printf("비겼습니다...다시 전투를 시작합니다!\n");
                        continue;
                    }
                    else if (user_choice - computer_choice == -2 || user_choice - computer_choice == 1)
                    {
                        printf("이겼습니다!\n");
                        win_cnt++;
                        if (user_level < enemy_level)
                        {
                            if (win_cnt == 2)
                            {
                                printf("당신은 %d레벨만큼 높은 몬스터를 물리쳤습니다!\n", enemy_level - user_level);
                                printf("보상으로 %d의 경험치가 주어집니다.\n", 2 * level_up);
                                user_exp = user_exp + 2 * level_up;
                                break;
                            }
                            else
                            {
                                printf("하지만 상대가 너무 강합니다... 한번 더 전투를 진행합니다!\n");
                                continue;
                            }
                        }
                        else if (user_level == enemy_level)
                        {
                            printf("당신의 레벨과 같은 상대를 이겼습니다!\n");
                            printf("보상으로 %d의 경험치가 주어집니다.\n", level_up);
                            user_exp = user_exp + level_up;
                            break;
                        }
                    }
                    else
                    {
                        printf("졌습니다...");
                        if (user_exp == 0)
                        {
                            if (warning_point < 2)
                            {
                                warning_point++;
                                printf("당신은 경험치가 부족합니다!\n");
                                printf("%d번 더 패배하면 게임 종료입니다.\n", 2 - warning_point);
                                break;
                            }
                            if (warning_point == 2)
                            {
                                game_over = 1;
                                printf("당신은 패배했습니다.\n조금 더 가위바위보를 수련하세요.\n");
                                break;
                            }
                        }
                        else if (user_exp > 0)
                        {
                            printf("당신은 전투에서 졌지만 소량의 경험치를 얻었습니다!\n");
                            user_exp = user_exp + level_up * 2 / 3;
                            break;
                        }
                        else
                        {
                            break; // 설마 여기때문에 오류났나? 그러면 너무고마워 제발 이게마지막이라고해줘
                        }
                    }
                }
            }
            else
            { // 유저가 전투 포기시
                printf("당신은 가까스로 몬스터에게서 도망쳤습니다!\n");
                printf("하지만 경험치는 얻지 못했습니다...\n");
                continue;
            }
        }
        if (enemy_level < user_level)
        {
            printf("이기기 매우 쉬운 상대 같습니다...\n게임에 응하시겠습니까?\n");
            printf("1. 게임 참가, 2. 도망친다: ");
            scanf("%d", &wanna_game);
            getchar();
            system("clear");
            // 사용자가 승리
            // 여기에 레벨 넣는 방식 추가
            if (user_level > enemy_level)
            {
                printf("당신보다 %d레벨 낮은 몬스터를 물리쳤습니다!\n", user_level - enemy_level);
                printf("보상으로 %.2f의 경험치가 주어집니다.\n", (double)2 / 3 * level_up);
                user_exp = user_exp + (2 / 3 * level_up);
            }
        }

        // 경험치 출력
        int i = 1;
        while (1)
        {
            if (user_exp <= i * 100)
            {
                user_level = i;
                break;
            }
            else
            {
                i++;
            }
        }
        user_level = i;
        printf("현재 %d레벨입니다\n", i);
        printf("당신의 경험치는 %.2fexp입니다.\n", (double)user_exp);

        // 레벨 비교 부분
        if (user_level >= 50)
        {
            game_over = 1;
            printf("YOU WIN !!\n");                                                  // 나중에 꾸미기
            printf("당신은 %d번 싸우고 2차전직할 준비가 되었습니다.\n", battle_cnt); // 나중에 꾸미기
            printf("\n");                                                            // 나중에 꾸미기
            break;                                                                   // while문 빠져나가기
        }
        else
        {
            printf("이 던전에서 빠져나가기 위해서는 수련이 필요합니다.\n");
            printf("다시 파티장으로 이동합니다...\n");
            printf("돌아가려면 엔터를 눌러 주세요...");
            scanf("%c", &test); // 형식 지정자를 %c로 하면 엔터(enter)도 하나의 공백 문자로서 입력 받을 수 있다.
            system("clear");
            continue; // 게임 반복하기 (이 모든 부분을 while문으로 묶기)
        }
    }
    return 0;
}