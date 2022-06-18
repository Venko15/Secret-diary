#include <stdio.h>
#include <stdlib.h>
#include<signal.h>
#include <string.h>

typedef struct{
    char name[50];
}file;

typedef struct{
    file *arr;
    int size;
}list;

void instructions(){
    FILE *f = fopen("instruction.txt","r");
    char buffer[255];
    while(fgets(buffer, 255, f)){
        printf("%s", buffer);
    }
    fclose(f);
}

void print(list *files){
    for (int i = 0; i < files->size; i++){
    printf("%d: %s\n", i+1, files->arr[i].name);
    };
}

int find_file_by_index(list *files, int index){
    int i = 0;
    while(i < files->size){
        if(i+1 == index){
            return files->arr[i].name;
        }else{i++;};
    }
}

int remove(const char * filename);

int main()
{
    file file;
    char answer[32];
    int ans;
    int index;
    struct list *files; ///logikata tuk e da imame papka v koqto da gledame za vsichki fajlove
    menu:
    instructions();
    printf("Please select an answer: (answer must be chosen between 0 and )");
    scanf("%d", &ans);

    if(ans == 0){
        printf("Goodbye!");
        return 0;
    }

    else if(ans == 1){ //read all files' names
        system("cls"); //clearing screen
        printf("The files of diary\n-----------------------------------\n");
        print(files);
        printf("-----------------------------------");

        printf("\nGo back to main menu? ");
        scanf("%s", answer);
        if(!strcmp(answer,"yes") || !strcmp(answer,"Yes")){
            system("cls");
            goto menu;
        }else{printf("Goodbye!");}
    }

    else if(ans == 2){ //edit a file
        system("cls");
        printf("You have selected the edit option.\nPlease select the file you want to edit by its index: ");
        scanf("%d",&index);
        printf("Excellent! Now you can edit (%d)\n",index);
        char *fileName;
        fileName = find_file_by_index(files, index);///maj ne raboti taka
        FILE *f = fopen("filename.txt","w");
        //signal(SIGINT, );
        printf("Success!");

        printf("\nGo back to main menu? ");
        scanf("%s", answer);
        if(!strcmp(answer,"yes") || !strcmp(answer,"Yes")){
            system("cls");
            goto menu;
        }else{
            printf("Goodbye!");}
    }

    else if(ans == 3){ //create new file
        system("cls");
        char name [50];
        char *fileName;
        printf("You have selected the add option.\nPlease enter new file name.\n");
        scanf("%s", &name);
        //file temp;
        //strcpy(temp.name, name);
        fileName = name;
        FILE *f = fopen(fileName,"w+");

        printf("\nGo back to main menu? ");
        scanf("%s", answer);
        if(!strcmp(answer,"yes") || !strcmp(answer,"Yes")){
            system("cls");
            goto menu;
        }else{
            printf("Goodbye!");}
    }

    else if(ans == 4){ //remove
        system("cls");
        printf("You have selected remove a file option.\nPlease select the file you want to remove by his index: ");
        scanf("%d", &index);
        char *fileName = find_by_index(files, index);
        printf("Success!");

        printf("\nGo back to main menu? ");
        scanf("%s", answer);
        if(!strcmp(answer,"yes") || !strcmp(answer,"Yes")){
            system("cls");
            goto menu;
        }else{
            printf("Goodbye!");}
    }
    return 0;
}
