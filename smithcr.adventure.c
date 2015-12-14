
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h> 
#include <unistd.h>
//#include <math.h>


// I had to make my own power function cause without this I would have to use the -lm in the gcc command
// to link the files better. But the specifications say that I can't do that so this is what I am doing instead.

/*
 * int my_pow(int, int)
 * 		This takes in two integers the first being the numner you want to have the power done to and the
 *		second being the power you want to raise it to.
 *		It returns first number to the power of the second number in the form of a long.
 */
int my_pow(int a, int b) {
	int i = 1;
	int num = 1;
	if (a == 0) {
		return 0;
	}
	for (i; i <= b; i++) {
		num = num * a;
	}

	return num;
}

/*
 * is_bi_part(int, int)
 *      This takes in two integers and then looks at the first as a number
 *
 *        The way I use the key variable is kinda weird, but I wanted a way to check if a name
 *        in the array of names had been used or not without checking the files names and doing a string
 *        compare. So I thought of this way of a kind of binary.
 *
 *        0	  1   2   3   4     power of 2
 *        1 + 2 + 4 + 8 + 16 =  31
 *        (2 ^ (4 + 1)) - 1  =  31
 *
 *        if 3 is chosen
 *        31 - 8 = 23
 *
 *        if 3 is chosen again
 *        23 % (8 * 2) = 7
 *        23 % (8)	   = 7
 *        try again
 *
 *        2 is chosen
 *        23 - 2 = 21
 *
 *        2 is chosen again
 *        21 % (4 * 2) = 1
 *        21 % 4       = 1
 *
 *
 *
 */
int is_bi_part(int key, int sug) {
    return ( ((key % (my_pow(2, sug) * 2))) - ((key % (my_pow(2, sug)))) );
}


int main() {
	srand(time(NULL));
        
    // the rooms directory
    char pid[20];
    snprintf(pid, 10,"%d",(int)getppid());  // get the PID and turn it into a string
    char dir_name[75];                  
    strcpy(dir_name, "smithcr.rooms.");     // Create the file name with the <username>.rooms.<pid> format
    strcat(dir_name, pid);                  // cat the file name and the <pid> 
    //printf("%s\n", dir_name);

    mkdir(dir_name, 0755);                  // make the directory
    
    // 10 room names 
    char rooms[10][24];
    strcpy(rooms[0], "Fairy");
    strcpy(rooms[1], "Poopy");
    strcpy(rooms[2], "Master");
    strcpy(rooms[3], "Zelda");
    strcpy(rooms[4], "Zoomba");
    strcpy(rooms[5], "Marias");
    strcpy(rooms[6], "Kooppas");
    strcpy(rooms[7], "Frungles");
    strcpy(rooms[8], "Crungles");
    strcpy(rooms[9], "Shmlorbs");

    // Create 7 files
    int i = 0;
    int number_of_rooms = 7;
    int number_of_possible_rooms = 10;
    int min_conn = 3;
    int max_conn = 6;
    int used_name = my_pow(2, number_of_possible_rooms + 1) - 1;    // This is me trying to be cool and creative using binary to keep track of the used room names. 
    //printf("%d\n", used_name);
    if (number_of_rooms > 0 && number_of_rooms <= 9) {
        for (i; i < number_of_rooms;  i++) {
            
            /*  
                The way I use the used_name variable is kinda weird, but I wanted a way to check if a name
                in the array of names had been used or not without checking the files names and doing a string 
                compare. So I thought of this way of a kind of binary. We start with the number 21111111111.
                Ten 1s, and a 1 for each possible file meaning the file name is still avaliable. Once we use the file name 
                a 0 is put in that position. 
             
             *        The way I use the key variable is kinda weird, but I wanted a way to check if a name
             *        in the array of names had been used or not without checking the files names and doing a string
             *        compare. So I thought of this way of a kind of binary.
             *
             *        0   1   2   3   4     power of 2
             *        1 + 2 + 4 + 8 + 16 =  31
             *        (2 ^ (4 + 1)) - 1  =  31
             *
             *        if 3 is chosen
             *        31 - 8 = 23
             *
             *        if 3 is chosen again
             *        23 % (8 * 2) = 7
             *        23 % (8)     = 7
             *        try again
             *
             *        2 is chosen
             *        23 - 2 = 21
             *
             *        2 is chosen again
             *        21 % (4 * 2) = 1
             *        21 % 4       = 1
             */


            int random_room;
            int binary_room;
            do {
                random_room = (rand() % number_of_possible_rooms);
            } while ( is_bi_part(used_name, random_room) == 0);
            used_name = used_name - my_pow(2, random_room); 

            
            //printf("\n%s the num %d\n", rooms[random_room], used_name);
            
            // filling the directory with the files
            char file_loc[256]; 
            strcpy(file_loc, dir_name);
            strcat(file_loc, "/");
            strcat(file_loc, rooms[random_room]);
            //printf("%s\n", file_loc);
            FILE *current_file; 
            current_file = fopen(file_loc, "w+");       // Creating the files               
            fputs("CURRENT LOCATION: ", current_file);
            fputs(rooms[random_room], current_file);    // adding the current location line
            fputs("\n", current_file);

            fclose(current_file);
        }
    }                                                   // 7 files have been created created
   
    i = 0;
    int number_of_connections[10];                      // the amount of connections that this file will have
    int connections_made[10];                            // the amount of connections this file currently has
    int binary_connections[10];                          // the binary representation of the files that this file is connected to
    int total_connections_count = 0;                       
    for (i; i < number_of_possible_rooms; i++) {
        if (is_bi_part(used_name, i) == 0 ) {
            number_of_connections[i] = (rand() % 4) + 3;
            total_connections_count = total_connections_count + number_of_connections[i];
            connections_made[i] = 0;
            binary_connections[i] = (my_pow(2, number_of_possible_rooms + 1) - 1);
        } else {
            connections_made[i] = -1;
            number_of_connections[i] = -1;
            binary_connections[i] = -1;
        }
    }
    
   
    // chose two random files 
    i = 0;
    int STOP = 1;
    for (i; i < total_connections_count && STOP == 1; i = i + 2) {
        int room1;
        int room2;
        int count = 0;
        do {
            count++;
            if (count == 1000) {
                STOP = 0;                       // sometime it got in an infinite loop and this will catch that and stop everything 
            }
            room1 = (rand() % number_of_possible_rooms); 
            room2 = (rand() % number_of_possible_rooms); 
        } while ((number_of_connections[room1] <= 0 || number_of_connections[room2] <= 0 || room2 == room1 || is_bi_part(binary_connections[room2], room1) == 0 || is_bi_part(binary_connections[room1], room2) == 0) && STOP == 1) ;
        
        
        if (STOP == 1) {
            connections_made[room1]++;
            connections_made[room2]++;
            
            FILE* fp_one;
            char file_location_one[100];                        // open the file
            strcpy(file_location_one, dir_name);
            strcat(file_location_one, "/");
            strcat(file_location_one, rooms[room1]);                // the file the loop is on
            fp_one = fopen(file_location_one, "a+");            // append
            fputs("CONNECTION ", fp_one);
            fprintf(fp_one, "%d: ", connections_made[room1]);
            fputs(rooms[room2], fp_one);
            fputs("\n", fp_one);
            fclose(fp_one);                                     // close this file

            FILE* fp_two;
            char file_location_two[100];                        // open the file
            strcpy(file_location_two, dir_name);
            strcat(file_location_two, "/");                     // the room2 room
            strcat(file_location_two, rooms[room2]);
            fp_two = fopen(file_location_two, "a+");
            fputs("CONNECTION ", fp_two);
            fprintf(fp_two, "%d: ", connections_made[room2]);
            fputs(rooms[room1], fp_two);
            fputs("\n", fp_two);
            fclose(fp_two);                                     // close this file
            
            number_of_connections[room2]--;
            number_of_connections[room1]--;
            binary_connections[room1] = binary_connections[room1] - my_pow(2, room2);
            binary_connections[room2] = binary_connections[room2] - my_pow(2, room1);
            
            // printf("[%s <-> %s]\n", rooms[room1], rooms[room2]); 
            // printf("[l:%d m:%d bi:%d] ", number_of_connections[room1], connections_made[room1], binary_connections[room1]);
            // printf("[l:%d m:%d bi:%d] ", number_of_connections[room2], connections_made[room2], binary_connections[room2]);
            // printf("\n\n");
        }
    }

    int beginning;
    int end;
    do {
        beginning = (rand() % number_of_possible_rooms); 
        end = (rand() % number_of_possible_rooms); 
    } while (beginning == end || is_bi_part(used_name, end) != 0 || is_bi_part(used_name, beginning) != 0);


    FILE* fp;
    char file_location_start[100];                        // open the file
    strcpy(file_location_start, dir_name);
    strcat(file_location_start, "/");
    strcat(file_location_start, rooms[end]);                // the end
    fp = fopen(file_location_start, "a+");              // append
    fputs("ROOM TYPE: END_ROOM\n", fp);
    fclose(fp); 

    
    char file_location_end[100];                        // open the file
    strcpy(file_location_end, dir_name);
    strcat(file_location_end, "/");
    strcat(file_location_end, rooms[beginning]);        // the end       
    fp = fopen(file_location_end, "a+");            // append
    fputs("ROOM TYPE: START_ROOM\n", fp);
    fclose(fp); 

    i = 0;
    for (i; i < number_of_possible_rooms; i++) {
        if (is_bi_part(used_name, i) == 0 && i != end && i != beginning) {
            char file_location_mid[100];                        // open the file
            strcpy(file_location_mid, dir_name);
            strcat(file_location_mid, "/");
            strcat(file_location_mid, rooms[i]);                // the file the loop is on
            fp = fopen(file_location_mid, "a+");            // append
            fputs("ROOM TYPE: MID_ROOM\n", fp);
            fclose(fp); 
        }
    }
    /// MAP == MADE! 
    
    // now to play the actual game 
    // find start file
    i = 0;
    char start_file_name[24];
    char start_file_location[100];
    for(i; i < number_of_possible_rooms; i++) {
        FILE* start;
        if (is_bi_part(used_name, i) == 0 ) {
            strcpy(start_file_location, dir_name);
            strcat(start_file_location, "/");
            strcat(start_file_location, rooms[i]);  
            
            start = fopen(start_file_location, "r");
            if (start == NULL) {
                printf("%s\n", start_file_location);
            }
            char line[256];
            char *c;
            const char colon[2] = ":";
            while (fgets(line, 256, start) != NULL) {
                //printf("%s", line);
                c = strtok(line, colon);    
                c = strtok(NULL, colon);

                if (strcmp(c, " START_ROOM\n") == 0) {
                    strcpy(start_file_name, rooms[i]);

                }    
            }
            
        }
    }

    // file the ending file 
    i = 0;
    char end_file_name[24];
    char end_file_location[100];
    for(i; i < number_of_possible_rooms; i++) {
        FILE* start;
        if (is_bi_part(used_name, i) == 0 ) {
            strcpy(end_file_location, dir_name);
            strcat(end_file_location, "/");
            strcat(end_file_location, rooms[i]);  
            
            start = fopen(end_file_location, "r");
            if (start == NULL) {
                printf("%s\n", end_file_location);
            }
            char line[256];
            char *c;
            const char colon[2] = ":";
            while (fgets(line, 256, start) != NULL) {
                //printf("%s", line);
                c = strtok(line, colon);    
                c = strtok(NULL, colon);

                if (strcmp(c, " END_ROOM\n") == 0) {
                    strcpy(end_file_name, rooms[i]);

                }    
            }
            
        }
    }
    
    // start file = current file
    char in_file[256];
    char in_file_location[256];
    char connects_that_are_here[10][24];
    strcpy(in_file, start_file_name);
    int num_connections_found = 0;
    int playing = 0;
    int step_number = 1;
    char steps[200][24];                    // save the steps
    strcpy(steps[0], start_file_name);

    // play the game 
    do {
        FILE* here;
        strcpy(in_file_location, dir_name);
        strcat(in_file_location, "/");
        strcat(in_file_location, in_file);
        here = fopen(in_file_location, "r");
        char line[256];
        
        fgets(line, 256, here);
        strtok(line, "\n");
        printf("%s\n", line);               // print out the current location
        char *c;
        const char colon[2] = ":";
        printf("POSSIBLE CONNECTIONS: ");
        num_connections_found = 0;
        while (fgets(line, 256, here) != NULL) {
            c = strtok(line, colon);    
            c = strtok(NULL, colon);
            if (strcmp(c, " END_ROOM\n") != 0 && strcmp(c, " START_ROOM\n") != 0 && strcmp(c, " MID_ROOM\n") != 0) {
                strtok(c, "\n" );
                strcpy(connects_that_are_here[num_connections_found], c);
                num_connections_found++;
            }
        }
        i = 0;
        for (i; i < num_connections_found; ++i) {                   // print out the connecting rooms 
            if(i == num_connections_found - 1) {
                printf("%s.\n", connects_that_are_here[i] );
            } else {
                printf("%s,", connects_that_are_here[i]);
            }
        }
        char next[100];
        int asking = 0;
        do {                                                        // ask the user for the next room to go to
            printf("WHERE TO? > ");
            scanf("%s", &next);
            //printf("%s\n", next );
            i = 0;
            for (i; i < num_connections_found; ++i) {
                char actual[25] = " ";
                strcat(actual, next);
                if (strcmp(actual, connects_that_are_here[i]) == 0) {
                    if (strcmp(next, end_file_name) == 0) {        // if the next room is the end the game is over
                        playing = 1;
                    }
                    strcpy(in_file, next);  
                    asking = 1;                                     
                }  
            }
        } while(asking == 0);                                       // ask the user until he inputs a connecting room
        printf("\n");
        step_number++;                                              // add to steps
        strcat(steps[step_number], next);
    } while (playing == 0);

    // GAME OVER!

    printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
	printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", step_number);    
    i = 0;
    for (i; i <= step_number; ++i) {                                // print out steps that the user took
         printf("%s\n", steps[i]);
     } 

	return 0;
}