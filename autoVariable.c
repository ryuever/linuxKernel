#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
// #define BUFSIZ 10
// char databuf[BUFSIZ];

FILE * open_data(char *datafile){
    FILE * fp;
    char dbuf[BUFSIZ];

    if((fp = fopen(datafile,"rw")) == NULL)
        return (NULL);
    if(setvbuf(fp, dbuf, _IOLBF, BUFSIZ) != 0)
        return (NULL);
    return fp;
}

int main(){
    FILE * fp, * fp2;
    char * line = NULL;
    size_t len = 0;                             
    ssize_t read = 0;
    int pos;
    char c;
    char databuf[BUFSIZ],databuf2[BUFSIZ];
    //    fp = open_data("autoVariable.txt");
    //    fp2 = open_data("autoVariable2.txt");

    // for testing read with full buffered, write with line buffered
    fp = fopen("autoVariable.txt", "r");
    if(setvbuf(fp, databuf, _IOFBF, BUFSIZ) != 0)
        return (NULL);
    fp2 = fopen("autoVariable2.txt", "w");
    if(setvbuf(fp2, databuf2, _IOLBF, BUFSIZ) != 0)
        return (NULL);
    while ((c = fgetc(fp)) != EOF) {
        printf("Retrieved line of length %c :\n", c);
        fputc(c, fp2);
    }

    /* // for testing read with unbuffered, write with line buffered */
    /* fp = fopen("autoVariable.txt", "r"); */
    /* if(setvbuf(fp, (char *)NULL, _IONBF, 0) != 0) */
    /*     return (NULL); */
    /* fp2 = fopen("autoVariable2.txt", "w"); */
    /* if(setvbuf(fp2, databuf2, _IOFBF, BUFSIZ) != 0) */
    /*     return (NULL); */
    /* while ((c = fgetc(fp)) != EOF) { */
    /*     printf("Retrieved line of length %c :\n", c); */
    /*     fputc(c, fp2); */
    /* } */
    
    /* while ((read = getline(&line, &len, stdin)) != -1) { */
    /*     printf("Retrieved line of length %zu from file1 :\n", read); */
    /*     //        pos = ftell(fp); */
    /*     printf("%d in %s \n", pos, line); */
    /*     fputs(line, fp2); */
    /* } */
    
    /* char *line_stin; */
    /* line_stin = readline("Enter a line :"); */
    /* printf("The readline is %s \n", line_stin); */

    /* while ((read = getline(&line, &len, fp2)) != -1) { */
    /*     printf("Retrieved line of length %zu :\n", read); */
    /*     pos = ftell(fp2); */
    /*     printf("%d in %s", pos, line); */
    /* } */
    
    fclose(fp);
    fclose(fp2);
    return 0;
}
