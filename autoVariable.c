#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
// #define BUFSIZ 10
// char databuf[BUFSIZ];

FILE * open_data(char *datafile){
    FILE * fp;
    char databuf[BUFSIZ];

    if((fp = fopen(datafile,"rw")) == NULL)
        return (NULL);
    if(setvbuf(fp, databuf, _IOLBF, BUFSIZ) != 0)
        return (NULL);
    return fp;
}

int cal(int a, int b){                      
    int z;
    z = a + b;
    return z;
}

int main(){
    FILE * fp, * fp2;
    char * line = NULL;
    size_t len = 0;                             
    ssize_t read = 0;
    int pos;
    int i = 4;
    int j = 5;
    int z;
    char databuf[BUFSIZ];
    //    fp = open_data("autoVariable.txt");
    //    fp2 = open_data("autoVariable2.txt");

    fp = fopen("autoVariable.txt", "r");
    /* if(setvbuf(fp, databuf, _IOFBF, BUFSIZ) != 0) */
    /*     return (NULL); */

    /* fp2 = fopen("autoVariable2.txt", "r"); */
    /* if(setvbuf(fp2, databuf, _IOFBF, BUFSIZ) != 0) */
    /*     return (NULL); */

    if(setvbuf(fp, (char *)NULL, _IOLBF, 0) != 0)
        return (NULL);

    fp2 = fopen("autoVariable2.txt", "w");
    /* if(setvbuf(fp2, (char *)NULL, _IOLBF, 0) != 0) */
    /*     return (NULL); */

    if(setvbuf(fp2, databuf, _IOFBF, BUFSIZ) != 0)
        return (NULL);

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu from file1 :\n", read);
        pos = ftell(fp);
        printf("%d in %s \n", pos, line);
        fputs(line, fp2);
    }
    /* char temp[100]; */
    /* fgets(temp, 100, fp); */
    /* fputs(temp,fp2); */
    
    /* char *line_stin; */
    /* line_stin = readline("Enter a line :"); */
    /* printf("The readline is %s \n", line_stin); */
    
    z= cal(i,j);
    printf("z is %d\n", z);

    while ((read = getline(&line, &len, fp2)) != -1) {
        printf("Retrieved line of length %zu :\n", read);
        pos = ftell(fp2);
        printf("%d in %s", pos, line);
    }


    
    fclose(fp);
    fclose(fp2);
    return 0;
}
