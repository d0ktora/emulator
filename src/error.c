#include "stdio.h"
#include "error.h"

void panic(char *s){
    printf("[!] PANIC :[%s]\n",s);
    while(TRUE){
        ;
    };

    return;
}
