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


void read_line(FILE* file, char* line)
{
    char ch = getc(file);
    int count = 0;

    while ((ch != '\n') && (ch != EOF)) {
        line[count] = ch;
        count++;
        ch = getc(file);
    }
    line[count] = '\0';
}

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



char is_new_position(struct position* positions, int count, int x, int y)
{
    for(int i = 0; i < count; i++) {
        if(positions[i].x == x && positions[i].y == y) {
            return 0;
        }
    }
    return 1;
}




void generate_positions(int size, struct position* positions)
{
    time_t t;
    srand((unsigned) time(&t));

    int x, y;
    for(int i = 0; i<4; i++){
        x = (rand()%size) + 1;
        y = (rand()%size) + 1;
        if(i > 0 && (is_new_position(&positions, (i-1), x, y) == 0)) {
            i--;
            continue;
        }
        positions[i].x = x;
        positions[i].y = y;
    }

    int is_near_king;
    while(1) {
        is_near_king = 0;
        for(int i = 2; i<4; i++){
            if(positions[0].x == positions[i].x || positions[0].y == positions[i].y) {
                positions[0].x = (rand()%size) + 1;
                positions[0].y = (rand()%size) + 1;
                is_near_king = 1;
                break;
            }
        }
        if(is_near_king == 0) {
            break;
        }
    }

    while(positions[0].y + 1 == positions[1].y || positions[0].y - 1 == positions[1].y || //KE
          (positions[0].y + 1 == positions[1].y && positions[0].x + 1 == positions[1].x) ||
          (positions[0].y - 1 == positions[1].y && positions[0].x - 1 == positions[1].x) ||
         (positions[0].y - 1 == positions[1].y && positions[0].x + 1 == positions[1].x) ||
          (positions[0].y + 1 == positions[1].y && positions[0].x - 1 == positions[1].x) ||
          positions[0].x + 1 == positions[1].x || positions[0].x - 1 == positions[1].x) {
        do {
        positions[1].x = (rand()%size) + 1;
        positions[1].y = (rand()%size) + 1;
        } while((positions[1].x == positions[0].x && positions[1].y == positions[0].y) ||
                (positions[1].x == positions[2].x && positions[1].y == positions[2].y) ||
                (positions[1].x == positions[3].x && positions[1].y == positions[3].y));
        //positions[1].x = (rand()%size) + 1;
        //positions[1].y = (rand()%size) + 1;
    }

    FILE *replay;
    replay = fopen("replay.txt", "a+");
    for(int i = 0; i < 4; i++) {
        fprintf(replay, "%d\n%d\n", positions[i].x, positions[i].y);
    }
    fclose(replay);

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
    } else {
        *result = 0;
        printf("\nEnemy's turn:");
        generate_field(size, positions);
        FILE* replay = fopen("replay.txt", "a+");
        fprintf(replay, "%d\n%d\n", positions[0].x, positions[0].y);

        fclose(replay);
        return;
    }
}

void change_position(int size, struct position* positions)
{
    char piece[3] = {"NO"};
    char pos[4];
    int is_valid_position = 0;
    printf("\nYour turn!\nChoose what piece to move by typing:\n KF for King\n R1 for Rook 1\n R2 for Rook 2\n");

    scanf("%s", &piece);
    while(strcmp(piece, "KF") != 0 && strcmp(piece, "R1") != 0 && strcmp(piece, "R2") != 0)
    {
        printf("Invalid piece! Try again: ");
        scanf("%s", &piece);
    }

    FILE *replay;
    replay = fopen("replay.txt", "a+");
    fprintf(replay, "%s\n", piece);

    fclose(replay);

    printf("Choose your position (Letters first, for example: A1, C5, F2): ");
    scanf("%s", &pos);
    int pos_x = pos[0] - 64;

    char str[3];

    int i;
    for(i = 1; i < strlen(pos); i++) {
        str[i-1] = pos[i];
    }
    str[i] = '\0';
    int pos_y = atoi(str);

    while(is_valid_position == 0){
        if(strcmp(piece, positions[1].figure) == 0)
        {
            printf("position: %s", positions[1].figure);
            if(pos_y>size){
                is_valid_position = 0;
                printf("\nUnknown number.");
            }

            else if(pos_x > size){
                is_valid_position = 0;
                printf("\nUnknown letter.");
            }

            else if((pos_x>positions[1].x+1 || pos_x<positions[1].x-1) || (pos_y>positions[1].y+1 || pos_y<positions[1].y-1) ||
                    (positions[0].x+1 == pos_x && positions[0].y+1 == pos_y) || (positions[0].x-1 == pos_x && positions[0].y-1 == pos_y) ||
                    (positions[0].x+1 == pos_x && positions[0].y-1 == pos_y) || (positions[0].x-1 == pos_x && positions[0].y+1 == pos_y) ||
                    (positions[0].x+1 == pos_x && positions[0].y == pos_y) || (positions[0].x == pos_x && positions[0].y+1 == pos_y) ||
                    (positions[0].x-1 == pos_x && positions[0].y == pos_y) || (positions[0].x == pos_x && positions[0].y-1 == pos_y)){
                is_valid_position = 0;
            }

            else if((positions[2].x == pos_x && positions[2].y == pos_y) || (positions[3].x == pos_x) && positions[3].y == pos_y) {
                printf("Position occupied!\n");
                is_valid_position = 0;
            }

            else{
                is_valid_position = 1;
                positions[1].x = pos_x;
                positions[1].y = pos_y;
                positions[1].moves++;
            }
        }

        else if(strcmp(piece, positions[2].figure) == 0)
        {
            printf("position: %s", positions[1].figure);
            if(pos_y>size){
                is_valid_position = 0;
                printf("\nUnknown number.");
            }

            else if(pos_x>size){
                is_valid_position = 0;
                printf("\nUnknown letter.");
            }

            else if((pos_x>positions[2].x && pos_y>positions[2].y) || (pos_x<positions[2].x && pos_y<positions[2].y) ||
                    (pos_x<positions[2].x && pos_y>positions[2].y) || (pos_x>positions[2].x && pos_y<positions[2].y)){
                is_valid_position = 0;
            }

            else if((positions[1].x == pos_x && positions[1].y == pos_y) || (positions[3].x == pos_x && positions[3].y == pos_y)) {
                printf("Position occupied!\n");
                is_valid_position = 0;
            }

            else{
                is_valid_position = 1;
                positions[2].x = pos_x;
                positions[2].y = pos_y;
                positions[2].moves++;
            }
        }

        else if(strcmp(piece, positions[3].figure) == 0)
        {
            if(pos_y>size){
                printf("\nUnknown number.");
                is_valid_position = 0;
            }

            else if(pos_x>size){
                printf("\nUnknown letter.");
                is_valid_position = 0;
            }

            else if((pos_x>positions[3].x && pos_y>positions[3].y) || (pos_x<positions[3].x && pos_y<positions[3].y) ||
                    (pos_x<positions[3].x && pos_y>positions[3].y) || (pos_x>positions[3].x && pos_y<positions[3].y)){
                is_valid_position = 0;
            }

            else if((positions[1].x == pos_x && positions[1].y == pos_y) || (positions[2].x == pos_x && positions[2].y == pos_y)) {
                printf("Position occupied!\n");
                is_valid_position = 0;
            }

            else{
                is_valid_position = 1;
                positions[3].x = pos_x;
                positions[3].y = pos_y;
                positions[3].moves++;
            }
        }

        if(is_valid_position == 0) {
            printf("Invalid position! Try again: ");
            scanf("%s", &pos);
        }
    }
    replay = fopen("replay.txt", "a+");
    fprintf(replay, "%s\n", pos);

    fclose(replay);
    generate_field(size, positions);

    return;
}








void replay_change_position(int size, struct position* positions, char* current_piece, char* current_pos)
{
    char piece[3] = {"NO"};
    char pos[4];
    int is_valid_position = 0;
    printf("\nYour turn!\nChoose what piece to move by typing:\n KF for King\n R1 for Rook 1\n R2 for Rook 2\n");

    strcpy(piece, current_piece);
    printf("\nChosen: %s\n", piece);
    printf("Choose your position (Letters first, for example: A1, C5, F2): ");

    strcpy(pos, current_pos);
    printf("\nChosen: %s\n", pos);
    int pos_x = pos[0] - 64;
    char str[3];

    int i;
    for(i = 1; i < strlen(pos); i++) {
        str[i-1] = pos[i];
    }
    str[i] = '\0';
    int pos_y = atoi(str);

    while(is_valid_position == 0){
        if(strcmp(piece, positions[1].figure) == 0)
        {
            if(pos_y>size){
                is_valid_position = 0;
                printf("\nUnknown number.");
            }

            else if(pos_x > size){
                is_valid_position = 0;
                printf("\nUnknown letter.");
            }

            else if((pos_x>positions[1].x+1 || pos_x<positions[1].x-1) || (pos_y>positions[1].y+1 || pos_y<positions[1].y-1) ||
                    (positions[0].x+1 == pos_x && positions[0].y+1 == pos_y) || (positions[0].x-1 == pos_x && positions[0].y-1 == pos_y) ||
                    (positions[0].x+1 == pos_x && positions[0].y-1 == pos_y) || (positions[0].x-1 == pos_x && positions[0].y+1 == pos_y) ||
                    (positions[0].x+1 == pos_x && positions[0].y == pos_y) || (positions[0].x == pos_x && positions[0].y+1 == pos_y) ||
                    (positions[0].x-1 == pos_x && positions[0].y == pos_y) || (positions[0].x == pos_x && positions[0].y-1 == pos_y)){
                is_valid_position = 0;
            }

            else if((positions[2].x == pos_x && positions[2].y == pos_y) || (positions[3].x == pos_x) && positions[3].y == pos_y) {
                printf("Position occupied!\n");
                is_valid_position = 0;
            }

            else{
                is_valid_position = 1;
                positions[1].x = pos_x;
                positions[1].y = pos_y;
                positions[1].moves++;
            }
        }

        else if(strcmp(piece, positions[2].figure) == 0)
        {
            if(pos_y>size){
                is_valid_position = 0;
                printf("\nUnknown number.");
            }

            else if(pos_x>size){
                is_valid_position = 0;
                printf("\nUnknown letter.");
            }

            else if((pos_x>positions[2].x && pos_y>positions[2].y) || (pos_x<positions[2].x && pos_y<positions[2].y) ||
                    (pos_x<positions[2].x && pos_y>positions[2].y) || (pos_x>positions[2].x && pos_y<positions[2].y)){
                is_valid_position = 0;
            }

            else if((positions[1].x == pos_x && positions[1].y == pos_y) || (positions[3].x == pos_x && positions[3].y == pos_y)) {
                printf("Position occupied!\n");
                is_valid_position = 0;
            }

            else{
                is_valid_position = 1;
                positions[2].x = pos_x;
                positions[2].y = pos_y;
                positions[2].moves++;
            }
        }

        else if(strcmp(piece, positions[3].figure) == 0)
        {
            if(pos_y>size){
                printf("\nUnknown number.");
                is_valid_position = 0;
            }

            else if(pos_x>size){
                printf("\nUnknown letter.");
                is_valid_position = 0;
            }

            else if((pos_x>positions[3].x && pos_y>positions[3].y) || (pos_x<positions[3].x && pos_y<positions[3].y) ||
                    (pos_x<positions[3].x && pos_y>positions[3].y) || (pos_x>positions[3].x && pos_y<positions[3].y)){
                is_valid_position = 0;
            }

            else if((positions[1].x == pos_x && positions[1].y == pos_y) || (positions[2].x == pos_x && positions[2].y == pos_y)) {
                printf("Position occupied!\n");
                is_valid_position = 0;
            }

            else{
                is_valid_position = 1;
                positions[3].x = pos_x;
                positions[3].y = pos_y;
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
        case 1: {
            FILE *replay;
            replay = fopen("replay.txt", "w");
            fclose(replay);

            if(size != 6 && size != 8 && size != 10){
            printf("No size entered. Choose size from 6, 8 or 10: ");
            scanf("%d", &size);}
            while(size != 6 && size != 8 && size != 10) {
                printf("Choose size from 6, 8 or 10: ");
                scanf("%d", &size);
            }
            replay = fopen("replay.txt", "a");
            fprintf(replay, "%d\n", size);
            fclose(replay);
            generate_positions(size, &positions);
            while(result != 1)
            {
                change_position(size, &positions);
                is_enemy_check_or_checkmate(size, &positions, &result, &checks);
            }
            printf("\nNumber of turns:\n KF - %d\n R1 - %d\n R2 - %d\n", positions[1].moves, positions[2].moves, positions[3].moves);
            printf("Number of checks: %d\n", checks-1);
            replay = fopen("replay.txt", "a+");
            fprintf(replay, "END");
            fclose(replay);
        ; }
        break;

        case 2:
            printf("Choose size from 6, 8 or 10: ");
            scanf("%d", &size);
            while(size != 6 && size != 8 && size != 10) {
                printf("Invalid size! Choose size from 6, 8 or 10: ");
                scanf("%d", &size);
        }; break;

        case 3: {
            FILE *replay;
            replay = fopen("replay.txt", "r");
            char line[10];
            int array[8];
            char current_piece[3];
            char current_pos[4];
            int KE_Letter;
            int KE_Pos;
            int saved_letter;
            int saved_pos;
            read_line(replay, &line);
            int size = atoi(line);
            for(int i = 0; i < 8; i++) {
                read_line(replay, &line);
                array[i] = atoi(line);
            }
            struct position positions[4] = {{"KE", array[0], array[1], 0}, {"KF", array[2], array[3], 0}, {"R1", array[4], array[5], 0}, {"R2", array[6], array[7], 0}};
            generate_field(size, positions);
            int counter = 1;
            while(strcmp(line, "END") != 0) {
                read_line(replay, &line);
                switch(counter)
                {
                    case 1: strcpy(current_piece, line); counter++; break;
                    case 2: strcpy(current_pos, line); counter++; break;
                    case 3: KE_Letter = atoi(line); counter++; break;
                    case 4: KE_Pos = atoi(line); counter++; break;
                }
                if(counter == 5) {
                    saved_letter = KE_Letter;
                    saved_pos = KE_Pos;
                    positions[0].x = KE_Letter;
                    positions[0].y = KE_Pos;
                    replay_change_position(size, &positions, &current_piece, &current_pos);
                    counter = 1;
                }
            }
            positions[0].x = saved_letter;
            positions[0].y = saved_pos;
            replay_change_position(size, &positions, &current_piece, &current_pos);
            printf("\nCheckmate!\n");
        }
            break;

        case 4: return 0;
    }

    goto back_start;

    return 0;
}
