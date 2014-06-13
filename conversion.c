#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main(){
    //==============================================================================
    // atoi : C-string str interpreting its content as an integral number
    //==============================================================================
    char a[]="-100";
    char b[]="123";
    int c;
    c = atoi(a)+atoi(b);
    printf("c=%d\n",c);

    float n;
    char *str="12345.67";
    n=atoi(str);
    printf("string=%s integer=%f\n",str,n);

    //==============================================================================
    // inet_pton : convert IPv4 and IPv6 addresses from text to binary form
    //==============================================================================
    int temp;
    inet_pton(AF_INET,"192.168.1.2",&temp);
    printf("temp is %d.\n",temp);
    return 0;
}
