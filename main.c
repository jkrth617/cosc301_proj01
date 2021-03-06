/*
 *
 * author name(s), date, and other info here
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "list.h"


void process_data(FILE *input_file) {
	struct rusage usage;
	char str[1024]; 
	memset(str, '\0', sizeof(char)*1024);
	struct node * head = NULL;
	while (fgets(str, (sizeof(char)*1024), input_file) != NULL){
		for(int i = 0; i<strlen(str); i++){
			if (str[i] == '#'){
				str[i] = '\0'; // kill line after the comment	
			}
		}
		char* tok= strtok(str," ,\n\t");
		while(tok!=NULL){
			validity_create(&head, tok);
			tok = strtok(NULL," ,\n\t");
		}	
	}
	list_print(head);
	list_destroy(head);
	
	//for making the Utime larger	
	/*for(int k = 0; k < 1000000000; k++){
	  }*/

	getrusage(RUSAGE_SELF, &usage);
	printf("User time: %ld.%lds\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
	printf("system time: %ld.%lds\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
	return;
}


void usage(char *program) {
    fprintf(stderr, "usage: %s [<datafile>]\n", program);
    exit(1);
}

#ifndef AUTOTEST
int main(int argc, char **argv) {
    FILE *datafile = NULL;

    /* find out how we got invoked and deal with it */
    switch (argc) {
        case 1:
	    printf("we are in case 1 using stdin\n");
            /* only one program argument (the program name) */ 
            /* just equate stdin with our datafile */
            datafile = stdin;        
            break;

        case 2:
            /* two arguments: program name and input file */
            /* open the file, assign to datafile */
            datafile = fopen(argv[1], "r");
            if (datafile == NULL) {
                printf("Unable to open file %s: %s\n", argv[1], strerror(errno));              
		exit(-1);
            }
            break;

        default:
            /* more than two arguments?  throw hands up in resignation */
            usage(argv[0]);
    }

    /* 
     * you should be able to just read from datafile regardless 
     * whether it's stdin or a "real" file.
     */
    process_data(datafile);
    fclose(datafile);
    return 0;
}
#endif
