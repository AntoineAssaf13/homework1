#include "types.h"
#include "stat.h"
#include "user.h"

char array[99999];

int length(char* str) {
    int count = 0;
    int j = 0;
    int roller = 1;
    while(roller){
        if (str[j] == '\0'){
            break;
        }
        count++;
        j++;
    }
    return count;
}

void sed(char* old, char* new, int textFile){
    int cursor, reader;
    int searchedWord, count = 0;
    int i;
    while((reader = read(textFile, array, sizeof(array))) > 0){
        for(cursor=0; cursor<reader; cursor++){
            for(i = 1; i < length(new); i++){
                if(array[cursor+(i-1)] != old[i]){
                    searchedWord=0;
                    break;
                }
                else{
                    if(array[cursor+(i-1)] == old[i]){
                        if(i == length(old)-1){
                            searchedWord=1;
                            count+=1;
                        }
                    }
                }
            }
                
            if(searchedWord == 1){
                for(i = 1; i < length(old); i++){
                    printf(1,"%c",new[i]);
                }
                cursor += length(old)-2;
            }
                

            if(!searchedWord) {
                printf(1, "%c", array[cursor]);
            }
        }
    }
    printf(1, "Found and Replaced %d Occurences.\n", count);
}



int main(int argc, char *argv[]){
    int textFile;
    if (argc <= 1){
        sed("-the", "-xyz", 0);
        exit();
    }
    else if(argc == 2){
        if((textFile = open(argv[1],0) < 0)){
            printf(1, "Error: cannot open %s\n", argv[1]);
            exit();
        }
        else{
            textFile = open(argv[1],0);
            sed("-the", "-xyz", textFile);
            close(textFile);
        }
    }
    else if(argc ==4){
        if((textFile = open(argv[3],0)) < 0){
            printf(1, "Error: cannot open %s\n", argv[1]);
            exit();
        }
        sed(argv[1], argv[2], textFile);
        close(textFile);
    }
    exit();
}