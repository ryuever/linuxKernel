#include <stdio.h>
#define BUFSIZ 400

FILE * open_data(char *datafile){
    FILE * fp;
    char databuf[BUFSIZ];

    if((fp = fopen(datafile,"r")) == NULL)
        return (NULL);
    if(setvbuf(fp, databuf, _IOLBF, BUFSIZ) != 0)
        return (NULL);
    return fp;
}

int main(){
    FILE * fp, * fp2;
    char * line = NULL;
    size_t len = 0;                             
    ssize_t read = 0;
    int pos;
    fp = open_data("autoVariable.txt");
    fp2 = open_data("autoVariable2.txt");
    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu :\n", read);
        pos = ftell(fp);
        printf("%d in %s \n", pos, line);
    }

    while ((read = getline(&line, &len, fp2)) != -1) {
        printf("Retrieved line of length %zu :\n", read);
        pos = ftell(fp2);
        printf("%d in %s", pos, line);
    }

    printf("fp is %s \n", &fp);
    printf("fp2 is %s \n", &fp2);

    return 0;
}


