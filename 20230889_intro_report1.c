#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int scores[10];
    int sum = 0;
    float average = 0.0f;
    
    srand(time(NULL));
    
    for (int i=0; i<10; i++) {
        scores[i] = rand() % 101;
        printf("%d번 학생 점수: %d\n", i+1, scores[i]);
        sum += scores[i];
    }
    
    average = (float)sum / 10;
    
    printf("\n----------------------\n");
    printf("전체 학생 점수 합계: %d\n", sum);
    printf("전체 학생 점수 평균: %.1f\n", average);
    
    return 0;
}
