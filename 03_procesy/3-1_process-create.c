#include <stdio.h>
#include <unistd.h>

int main(){
   printf("Start\n");
   fork();
   printf("End\n");
}
