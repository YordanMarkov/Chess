#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct position {
    char figure[3];
    int x;
    int y;
    int moves;
};

void generate_field(int size, struct position* positions)
{
    char letter = 65;
    int number = size;
    int count = 0;
    int flag = 0;
    printf("\n");
    for(int i = 0; i<size; i++) {
        printf(" _ _ _");
    }
    printf("\n");

    for(int j = 0; j<size; j++) {
        for(int i = 0; i<size; i++) {
            printf("|     ");
        }
        printf("|\n");

        for(int i = 0; i<size; i++) {
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

        for(int i = 0; i<size; i++) {
            printf("|_ _ _");
        }
        printf("|\n");
        count = 0;
    }

    for(int i = 0; i<size; i++) {
        printf("   %c  ", letter);
        letter++;
    }

    return;
}

void generate_positions(int size, struct position* positions)
{
    //int detect = 0;
    time_t t;
    srand((unsigned) time(&t));

    for(int i = 0; i<4; i++){
        back: /*detect = 0*/;
        positions[i].x = (rand()%size) + 1;
        positions[i].y = (rand()%size) + 1;
    }

    for(int i = 0; i<4; i++) {
        for(int j = 0; j<4; j++){
            if(i == j){
                j++;
            }
            if(positions[i].x == positions[j].x && positions[i].y == positions[j].y){
                goto back;
                //detect = 1;
                //continue;
            }
        }

        //if(detect == 1){
        //    goto back;
        //}
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
    generate_field(size, positions);

    return;
}

void is_enemy_check_or_checkmate(int size, struct position* positions, int* result, int* checks) //to be edited
{
    int flag = 0;
    int save_pos[2];
    save_pos[0] = positions[0].x;
    save_pos[1] = positions[0].y;
    int pos_counter = 0;

    /*if((((positions[0].x == positions[2].x || positions[0].x + 1 == positions[3].x) || (positions[0].x + 1 == positions[2].x || positions[0].x == positions[3].x)) ||
       ((positions[0].y == positions[2].y || positions[0].y + 1 == positions[3].y) || (positions[0].y + 1 == positions[2].y || positions[0].y == positions[3].y))) &&
       (positions[1].y + 1 == positions[0].y || positions[1].y - 1 == positions[0].y)) {
        printf("\nCheckmate!");
        *result = 1;
        return;
    }

    if(positions[0].x == positions[2].x || positions[0].x == positions[3].x || positions[0].y == positions[2].y || positions[0].y == positions[3].y) {
        printf("\nCheck!");
        *result = 1;
        *checks+=1;
        return;
    }*/

    while((positions[0].x>save_pos[0]+1 || positions[0].x<save_pos[0]-1) || (positions[0].y>save_pos[1]+1 || positions[0].y<save_pos[1]-1) ||
        (positions[1].x+1 == positions[0].x && positions[1].y+1 == positions[0].y) || (positions[1].x-1 == positions[0].x && positions[1].y-1 == positions[0].y) ||
        (positions[1].x+1 == positions[0].x && positions[1].y-1 == positions[0].y) || (positions[1].x-1 == positions[0].x && positions[1].y+1 == positions[0].y) ||
        (positions[1].x+1 == positions[0].x && positions[1].y == positions[0].y) || (positions[1].x == positions[0].x && positions[1].y+1 == positions[0].y) ||
        (positions[1].x-1 == positions[0].x && positions[1].y == positions[0].y) || (positions[1].x == positions[0].x && positions[1].y-1 == positions[0].y) ||
        (positions[0].x == positions[2].x || positions[0].x == positions[3].x || positions[0].y == positions[2].y || positions[0].y == positions[3].y)){

        if(pos_counter==size*size*size) {
            break;
        }

        go_back: ;

        positions[0].x = (rand()%size) + 1;
        positions[0].y = (rand()%size) + 1;

        pos_counter++;

        if(flag == 0){
            printf("\nCheck");
            *checks+=1;
            flag = 1;
        }
    }

    if(positions[0].x == save_pos[0] && positions[0].y == save_pos[1]) {
            flag = 1;
            goto go_back;
    }

    if(pos_counter==size*size*size) {
        *result = 1;
        printf("mate!\n");
        return;
    }
    else {
        *result = 0;
        printf("\nEnemy's turn:");
        generate_field(size, positions);
        return;
    }
}

void change_position(int size, struct position* positions)
{
    char piece[3] = {"NO"};
    char pos[3];
    int is_valid_position = 0;
    printf("\nYour turn!\nChoose what piece to move by typing:\n KF for King\n R1 for Rook 1\n R2 for Rook 2\n");

    scanf("%s", &piece);
    while(strcmp(piece, "KF") != 0 && strcmp(piece, "R1") != 0 && strcmp(piece, "R2") != 0)
    {
        printf("Invalid piece! Try again: ");
        scanf("%s", &piece);
    }

    printf("Choose your position (Letters first, for example: A1, C5, F2): ");
    scanf("%s", &pos);

    while(is_valid_position == 0){
        if(strcmp(piece, positions[1].figure) == 0)
        {
            if(atoi(&pos[1])>size){
                is_valid_position = 0;
            }

            else if((pos[0] - 64)>size){
                is_valid_position = 0;
            }

            else if(((pos[0] - 64)>positions[1].x+1 || (pos[0] - 64)<positions[1].x-1) || (atoi(&pos[1])>positions[1].y+1 || atoi(&pos[1])<positions[1].y-1) ||
                    (positions[0].x+1 == (pos[0] - 64) && positions[0].y+1 == atoi(&pos[1])) || (positions[0].x-1 == (pos[0] - 64) && positions[0].y-1 == atoi(&pos[1])) ||
                    (positions[0].x+1 == (pos[0] - 64) && positions[0].y-1 == atoi(&pos[1])) || (positions[0].x-1 == (pos[0] - 64) && positions[0].y+1 == atoi(&pos[1])) ||
                    (positions[0].x+1 == (pos[0] - 64) && positions[0].y == atoi(&pos[1])) || (positions[0].x == (pos[0] - 64) && positions[0].y+1 == atoi(&pos[1])) ||
                    (positions[0].x-1 == (pos[0] - 64) && positions[0].y == atoi(&pos[1])) || (positions[0].x == (pos[0] - 64) && positions[0].y-1 == atoi(&pos[1]))){
                is_valid_position = 0;
            }

            else if((positions[2].x == (pos[0] - 64) && positions[2].y == atoi(&pos[1])) || (positions[3].x == (pos[0] - 64) && positions[3].y == atoi(&pos[1]))) {
                printf("Position occupied!\n");
                is_valid_position = 0;
            }

            else{
                is_valid_position = 1;
                positions[1].x = pos[0] - 64;
                positions[1].y = atoi(&pos[1]);
                positions[1].moves++;
            }
        }

        else if(strcmp(piece, positions[2].figure) == 0)
        {
            if(atoi(&pos[1])>size){
                is_valid_position = 0;
            }

            else if((pos[0] - 64)>size){
                is_valid_position = 0;
            }

            else if(((pos[0] - 64)>positions[2].x && atoi(&pos[1])>positions[2].y) || ((pos[0] - 64)<positions[2].x && atoi(&pos[1])<positions[2].y) ||
                    ((pos[0] - 64)<positions[2].x && atoi(&pos[1])>positions[2].y) || ((pos[0] - 64)>positions[2].x && atoi(&pos[1])<positions[2].y)){
                is_valid_position = 0;
            }

            else if((positions[1].x == (pos[0] - 64) && positions[1].y == atoi(&pos[1])) || (positions[3].x == (pos[0] - 64) && positions[3].y == atoi(&pos[1]))) {
                printf("Position occupied!\n");
                is_valid_position = 0;
            }

            else{
                is_valid_position = 1;
                positions[2].x = pos[0] - 64;
                positions[2].y = atoi(&pos[1]);
                positions[2].moves++;
            }
        }

        else if(strcmp(piece, positions[3].figure) == 0)
        {
            if(atoi(&pos[1])>size){
                is_valid_position = 0;
            }

            else if((pos[0] - 64)>size){
                is_valid_position = 0;
            }

            else if(((pos[0] - 64)>positions[3].x+1 && atoi(&pos[1])>positions[3].y+1) || ((pos[0] - 64)<positions[3].x-1 && atoi(&pos[1])<positions[3].y-1) ||
                    ((pos[0] - 64)<positions[3].x && atoi(&pos[1])>positions[3].y) || ((pos[0] - 64)>positions[3].x && atoi(&pos[1])<positions[3].y)){
                is_valid_position = 0;
            }

            else if((positions[1].x == (pos[0] - 64) && positions[1].y == atoi(&pos[1])) || (positions[2].x == (pos[0] - 64) && positions[2].y == atoi(&pos[1]))) {
                printf("Position occupied!\n");
                is_valid_position = 0;
            }

            else{
                is_valid_position = 1;
                positions[3].x = pos[0] - 64;
                positions[3].y = atoi(&pos[1]);
                positions[3].moves++;
            }
        }

        if(is_valid_position == 0) {
            printf("Invalid position! Try again: ");
            scanf("%s", &pos);
        }
    }

    generate_field(size, positions);

    return;
}

int main()
{
    int size;
    int result;
    int choice;
    int checks;
    struct position positions[4] = {{"KE", 0, 0, 0}, {"KF", 0, 0, 0}, {"R1", 0, 0, 0}, {"R2", 0, 0, 0}};
    FILE *fptr;

    back_start: ;
    result = 0;
    choice = 0;
    checks = 0;

    printf("\nChoose:\n 1 for New Game\n 2 for Change board size\n 3 for Replay\n 4 for Exit\n");
    scanf("%d", &choice);
    while(choice != 1 && choice != 2 && choice != 3 && choice != 4)
    {
        printf("Invalid option! Try again: ");
        scanf("%d", &choice);
    }

    switch(choice)
    {
        case 1: if(size != 6 && size != 8 && size != 10){
            printf("No size entered. Choose size from 6, 8 or 10: ");
            scanf("%d", &size);}
            while(size != 6 && size != 8 && size != 10) {
                printf("Choose size from 6, 8 or 10: ");
                scanf("%d", &size);
            }
            generate_positions(size, &positions);
            while(result != 1)
            {
                change_position(size, &positions);
                is_enemy_check_or_checkmate(size, &positions, &result, &checks);
            }
            printf("\nNumber of turns:\n KF - %d\n R1 - %d\n R2 - %d\n", positions[1].moves, positions[2].moves, positions[3].moves);
            printf("Number of checks: %d\n", checks-1);
        ; break;

        case 2:
            printf("Choose size from 6, 8 or 10: ")
            scanf("%d", &size);
            while(size != 6 && size != 8 && size != 10) {
                printf("Invalid size! Choose size from 6, 8 or 10: ");
                scanf("%d", &size);
        }; break;

        case 3://Replay

        case 4: return 0;
    }

    goto back_start;

    return 0;
}
