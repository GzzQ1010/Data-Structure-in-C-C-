#include <stdio.h>
#include <stdlib.h>
#include<time.h>

//Inser function Prototype
int *insert( int *array, int length, int index, int value);

//Main function

int main(){
    const int INSERTS_PER_READING =1000;
    int *array=NULL;
    int length=0;

    srand(time(NULL)); //randon generation

    printf("Array length\tSeconds per insert\n");
    for(int i=0; i<60;i++){
        clock_t start_time=clock();
        for (int j=0; j<INSERTS_PER_READING;j++){
            int index=rand() % (length+1);
            int value= rand();
            array=insert(array, length, index, value);
            if (!array){
                printf("Memory allocation error!");
                exit(1);
            }
            length++;
        }
        clock_t stop_time=clock();
        double time_pre_insert=(double)(stop_time - start_time)/CLOCKS_PER_SEC/INSERTS_PER_READING;
        printf("%d\t%.6f\n",length, time_pre_insert);
    }
    free(array);
    return 0;
}

//Insert function 
int *insert(int *array , int length, int index, int value){
    if(length==0){
        int *newArray = (int*) malloc(sizeof(int));
        if(!newArray) 
            return NULL;//handle memory allocation failure
        newArray[0]=value;
        return newArray;
    } else{
        int *newArray =(int *)malloc((length+1)*sizeof(int));
        if (!newArray)
            return NULL;
        for (int i=0; i<index;i++)
            newArray[i]=array[i];
            newArray[index]=value;
        for(int i= index; i<length; i++)
            newArray[i+1]==array[i];
        free(array);
        return newArray;
    }
}


