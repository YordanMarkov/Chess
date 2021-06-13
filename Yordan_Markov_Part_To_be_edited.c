#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct position {
    char figure[3];
    int x;
    int y;
};

void generate_field(int* size, struct position* positions)
{
    char letter = 65;
    int number = *size;
    int count = 0;
    int flag = 0;
    for(int i = 0; i<*size; i++) {
        printf(" _ _ _");
    }
    printf("\n");

    for(int j = 0; j<*size; j++) {
        for(int i = 0; i<*size; i++) {
            printf("|     ");
        }
        printf("|\n");

        for(int i = 0; i<*size; i++) {
            printf("|  ");
            for(count = 0; count<4; count++)
            {
                if(positions[count].x == i+1 && positions[count].y == number)
                {
                    printf("%s ", positions[count].figure);
                    flag = 1;
                }

            }
            if(flag == 0)
            {
                printf("   ");
            }
            flag = 0;

        }
        printf("| %d\n", number--);

        for(int i = 0; i<*size; i++) {
            printf("|_ _ _");
        }
        printf("|\n");
        count = 0;
    }

    for(int i = 0; i<*size; i++) {
        printf("   %c  ", letter);
        letter++;
    }

    return 0;
}

void generate_positions(int size, struct position* positions)
{
    int detect = 0;
    time_t t;
    srand((unsigned) time(&t));

    for(int i = 0; i<4; i++) {
        back: detect = 0;
        positions[i].x = (rand()%size) + 1;
        positions[i].y = (rand()%size) + 1;

        for(int j = 0; j<4; j++) {
            if(i == j) {
                j++;
            }
            if(positions[i].x == positions[j].x && positions[i].y == positions[j].y) {
                detect = 1;
                continue;
            }
        }

        if(detect == 1) {
            goto back;
        }

    }

    while(positions[0].x == positions[2].x || positions[0].x == positions[3].x || positions[0].y == positions[2].y || positions[0].y == positions[3].y) {
        positions[0].x = (rand()%size) + 1;
        positions[0].y = (rand()%size) + 1;
    }
    while(positions[0].y + 1 == positions[1].y || positions[0].y - 1 == positions[1].y ||
          (positions[0].y + 1 == positions[1].y && positions[0].x + 1 == positions[1].x) ||
          (positions[0].y - 1 == positions[1].y && positions[0].x - 1 == positions[1].x) ||
         (positions[0].y - 1 == positions[1].y && positions[0].x + 1 == positions[1].x) ||
          (positions[0].y + 1 == positions[1].y && positions[0].x - 1 == positions[1].x) ||
          positions[0].x + 1 == positions[1].x || positions[0].x - 1 == positions[1].x) {
        positions[1].x = (rand()%size) + 1;
        positions[1].y = (rand()%size) + 1;
    }

    /*for(int i = 0; i<4; i++) {
        printf("\nX = %d, Y = %d", positions[i].x, positions[i].y);
    }*/

    return 0;
}

void is_enemy_check_or_checkmate(int size, struct position* positions) //to be edited
{
    if((((positions[0].x == positions[2].x || positions[0].x + 1 == positions[3].x) || (positions[0].x + 1 == positions[2].x || positions[0].x == positions[3].x)) ||
       ((positions[0].y == positions[2].y || positions[0].y + 1 == positions[3].y) || (positions[0].y + 1 == positions[2].y || positions[0].y == positions[3].y))) &&
       (positions[1].y + 1 == positions[0].y || positions[1].y - 1 == positions[0].y)) {
        printf("Checkmate!");
        return 0;
    }

    if(positions[0].x == positions[2].x || positions[0].x == positions[3].x || positions[0].y == positions[2].y || positions[0].y == positions[3].y) {
        printf("Check!");
        return 0;
    }

    return 0;
}

int main()
{
    int size;

    while(size != 6 && size != 8 && size != 10) {
        printf("Choose size from 6, 8 or 10: ");
        scanf("%d", &size);
    }

    //printf("size = %d", size);

    struct position positions[4] = {{"KE", 0, 0}, {"KF", 0, 0}, {"R1", 0, 0}, {"R2", 0, 0}};

    generate_positions(size, &positions);

    is_enemy_check_or_checkmate(size, &positions);

    generate_field(&size, &positions);

    return 0;
}
