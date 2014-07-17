#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
    int i,j,k,z;
    unsigned int tvalue;
    tvalue = (unsigned)time(NULL);
    
    printf("tvalue is %u\n", tvalue);
    srand(tvalue);
    
    for(i=0;i<5;i++){
        // randomfloat number between 4 ~ 7
        z = rand();
        printf("%d\n",z);
        printf("%lf\n",z / (float)(RAND_MAX)*4+3);

        z = rand();
        printf("second : %d\n",z);
        // random integer number between 0 ~ 4
        j = 1+(int)(4.0*z / (RAND_MAX+1.0));
        printf("%d\n", j );
        
        k = rand()%15;
        printf("randomized integer between [0,14] : %d\n",k);
    }

    int seed;
    for(seed = 1; seed < 10; seed++) {
        srand(seed);
        printf("%4d %16d\n", seed, rand());
    }

    // if the seed value is stable, comparing two times of grogram execution.
    // the results are the same.
    srand(2);
    for(i = 0; i < 5; i++)
        printf("rand() is %d\n",rand());

    return 0;
}
