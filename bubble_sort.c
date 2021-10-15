#include <cs50.h>
#include <stdio.h>

int array[]={4,3,2,1};

int main (void){
    for (int j=3;j>=0;j--){
        for (int i=0;i<3;i++){
                if (array[i]>array[i+1]){
                    int aux = array[i+1];
                    array[i+1]=array[i];
                    array[i]= aux;
                    }
            }

    }
    for (int i=0;i<4;i++){
    printf ("%i ", array[i]);
}
    printf ("\n");
}
