// #include <stdio.h>
// #include <stdlib.h>

// int main(void)
// {
//     int * ptr1 = (int *)malloc(sizeof(int));
//     int * ptr2 = (int *)malloc(sizeof(int)*7);
//     int i;

//     *ptr1=20;
//     for(i=0; i<7; i++)
//         ptr2[i]=i+1;
    
//     printf("%d \n", *ptr1);
//     for(i=0; i<7; i++)
//         printf("%d ", ptr2[i]);
    
//     free(ptr1);
//     free(ptr2);
//     return 0;
// }


// #include <stdio.h>
// #include <stdlib.h>

// char*ReadUserName(void)
// {
//     char*name = (char*)malloc(sizeof(char)*30);
//     printf("What your name? ");
//     gets(name);
//     return name;
// }

// int main(void)
// {
//     char * name1;
//     char * name2;
//     name1=ReadUserName();
//     printf("name1: %s \n", name1);
//     name2=ReadUserName();
//     printf("name2: %s \n", name2);

//     printf("again name1: %s \n", name1);
//     printf("again name2: %s \n", name2);
//     free(name1);
//     free(name2);
//     return 0;
// }

// //25-문제2
// #include <stdio.h>
// #include <stdlib.h>

// int main(void)
// {
//     int arrlen=5;
//     int idx=0;
//     int i;
//     int * arr=(int*)malloc(sizeof(int)*arrlen);

//     while(1)
//     {
//         printf("정수 입력:");
//         scanf("%d", &arr[idx]);
//         if(arr[idx]==-1)
//             break;
        
//         if(arrlen==idx+1)
//         {
//             arrlen+=3;
//             arr=(int*)realloc(arr, sizeof(int)*arrlen);
//         }
//         idx++;
//     }
//     for(i=0; i<idx; i++)
//         printf("%d ", arr[i]);
//     free(arr);
//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>

// int main(void)
// {
//     int*pi;
//     double*pd;

//     pi=(int*)malloc(sizeof(int));
//     if(pi==NULL)
//     {
//         printf("#으로 메모리가 부족합니다.\n");
//         exit(1);
//     }
//     pd=(double*)malloc(sizeof(double));

//     *pi=10;
//     *pd=3.4;

//     printf("정수형으로 사용: %d\n", *pi);
//     printf("실수형으로 사용: %lf\n", *pd);

//     free(pi);
//     free(pd);

//     return 0;
// }

// #include <stdio.h>

// int disp_menu()
// {
//     int sel;
//     printf("1.볶음짬뽕\n");
//     printf("2.콩나물국밥\n");
//     printf("3.바지락칼국수\n\n");

//     printf("# 메뉴를 선택하세요: ");
//     scanf("%d", &sel);
//     return sel;
// }


// int main(void)
// {
//     int sel;
//     sel=disp_menu();
//     printf("선택된 메뉴는 %d번 입니다.\n", sel);

//     return 0;
// }

// #include <stdio.h>

// int sum(int n) {
//     int result = 0;
//     for (int i = 1; i <= n; i++) {
//         result += i;
//     }
//     return result;
// }

// int main(void) {
//     printf("1부터 10까지의 합: %d\n", sum(10));
//     printf("1부터 100까지의 합: %d\n", sum(100));

//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// typedef struct 
// {
//     char author[30];
//     char title[50];
//     int pages;
// }Book;

// int main(void)
// {
//     Book*books=(Book*)malloc(sizeof(Book)*3);
    
//     printf("도서 정보 입력\n");
//     for(int i=0; i<3; i++)
//     {
//         printf("저자:");
//         fgets(books[i].author,sizeof(books[i].author),stdin);
//         books[i].author[strlen(books[i].author)-1]=0;
//         printf("제목:");
//         fgets(books[i].title,sizeof(books[i].title),stdin);
//         books[i].title[strlen(books[i].title)-1]=0;
//         printf("페이지 수:");
//         scanf("%d",&books[i].pages);

//         getchar();
//         printf("\n");        
//     }
//     for(int i=0; i<3; i++)
//     {
//         printf("book %d\n",i+1);
//         printf("저자: %s\n",books[i].author);
//         printf("제목: %s\n",books[i].title);
//         printf("페이지 수: %d \n\n",books[i].pages);
//     }
//     free(books);
//     return 0;
// }

// #include <stdio.h>

// int main(void)
// {
//     int num1, num2;
//     int i;

//     printf("정수 2개를 입력해주세요:");
//     scanf("%d %d", &num1, &num2);

//     printf("1.더하기\n2.빼기\n3.곱하기\n4.나누기\n");
//     printf("계산하기 위해 원하시는 번호를 선택해주세요:\n");
//     scanf("%d", &i);

//     if (i == 1)
//         printf("%d + %d = %d", num1, num2, num1 + num2);
//     else if (i == 2)
//         printf("%d - %d = %d", num1, num2, num1 - num2);
//     else if (i == 3)
//         printf("%d x %d = %d", num1, num2, num1 * num2);
//     else if (i == 4)
//     {
//         if (num2 != 0)
//             printf("%d / %d = %.2lf", num1, num2, (double)num1 / num2);
//         else
//             printf("0으로 나눌 수 없습니다.");
//     }
//     else
//         printf("잘못된 선택 입니다.");

//     return 0;
// }

// #include <stdio.h>

// void reverseString(char str[])
// {
//     int length = strlen(str);
//     int start = 0;
//     int end = length -1;

//     while(start<end)
//     {
//         char temp=str[start];
//         str[start]=str[end];
//         str[end]=temp;

//         start++;
//         end--;
//     }
// }

// int main()
// {
//     char inputspring[100];

//     printf("문자열을 입력하세요:");
//     scanf("%s", &inputspring);

//     reverseString(inputspring);

//     printf("뒤집힌 문자열: %s \n", inputspring);
//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>

// struct Student
// {
//     char name[20];
//     int age;
//     float gpa;
// };

// int main(void)
// {
//     int numStudents;

//     printf("학생 수를 입력해주세요:");
//     scanf("%d",&numStudents);

//     struct Student*students = (struct Student*)malloc(numStudents*sizeof(struct Student));
    
//     if(students== NULL)
//     {
//         fprintf(stderr,"메모리 할당 오류\n");
//         return 1;
//     }
//     for(int i=0; i<numStudents; i++)
//     {
//         printf("학생 %d 정보 입력\n", i+1);
//         printf("이름: ");
//         scanf("%s", &students[i].name);
//         printf("나이: ");
//         scanf("%d", &students[i].age);
//         printf("평점: ");
//         scanf("%f", &students[i].gpa);
//     }
//     printf("\n입력 받은 학생 정보\n");
//     for(int i=0; i< numStudents; i++)
//     {
//         printf("학생 %d\n", i+1);
//         printf("이름: %s\n", students[i].name);
//         printf("나이: %d\n", students[i].age);
//         printf("평점: %.2f\n", students[i].gpa);
//         printf("\n");
//     }
//     free(students);

//     return 0;
// }

// //도전 3
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// typedef struct 
// {
//     double real;
//     double imaginary;
// }Complex;

// int main(void)
// {
//     Complex*complexes=(Complex*)calloc(2,sizeof(Complex));
//     double res_real = 0, res_imaginary=0;

// for (int i = 0; i < 2; i++)
// {
//     printf("복소수 입력 %d [실수 허수]: ", i + 1);
//     scanf("%lf %lf", &complexes[i].real, &complexes[i].imaginary); 
// }

//     for(int i=0; i<2; i++)
//     {
//         res_real +=complexes[i].real;
//         res_imaginary+=complexes[i].imaginary;
//     }

//     printf("합의 결과: 실수: %lf, 허수: %lf\n", res_real,res_imaginary);

//     res_real=complexes[0].real*complexes[1].real - complexes[0].imaginary*complexes[1].imaginary;
//     res_imaginary=complexes[0].real*complexes[1].imaginary+complexes[0].imaginary*complexes[1].real;

//     printf("곱의 결과- 실수:%lf, 허수:%lf\n", res_real, res_imaginary);
//     return 0;
// }

// //학생 입력
// #include <stdio.h>
// #include <stdlib.h>

// struct Student
// {
//     char name[20];
//     int age;
//     float gpa;
// };

// int main(void)
// {
//     int numStudents;

//     printf("학생 수를 입력해주세요:");
//     scanf("%d",&numStudents);

//     struct Student*students = (struct Student*)malloc(numStudents*sizeof(struct Student));
    
//     if(students== NULL)
//     {
//         fprintf(stderr,"메모리 할당 오류\n");
//         return 1;
//     }
//     for(int i=0; i<numStudents; i++)
//     {
//         printf("학생 %d 정보 입력\n", i+1);
//         printf("이름: ");
//         scanf("%s", &students[i].name);
//         printf("나이: ");
//         scanf("%d", &students[i].age);
//         printf("평점: ");
//         scanf("%f", &students[i].gpa);
//     }
//     printf("\n입력 받은 학생 정보\n");
//     for(int i=0; i< numStudents; i++)
//     {
//         printf("학생 %d\n", i+1);
//         printf("이름: %s\n", students[i].name);
//         printf("나이: %d\n", students[i].age);
//         printf("평점: %.2f\n", students[i].gpa);
//         printf("\n");
//     }
//     free(students);

//     return 0;
// }

#include <stdio.h>

