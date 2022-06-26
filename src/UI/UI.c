#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include <string.h>

typedef struct{
    char name[50];
    char* content;
    char data_and_time[11];
}file;

typedef struct{
    file *arr;
    int size;
}list;

void instructions(){
    printf("Instructions:\n");
    printf("\tIn order to use a function, simply type it's number.\n");
    printf("\tThe list of options is:\n");
    printf("\t1.Read all file names\n\t2.Edit a file\n\t3.Create new file\n\t4.Remove a file\n\t0.Exit\n");
}

void print(){
     // directory stream variable for accessing the directory
  DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d)
    {
        int i = 1;
        while ((dir = readdir(d)) != NULL){
            printf("%d.%s\n",i, dir->d_name);
            i++;
        }
        closedir(d);

    }

}

char* find_file_by_index(list *files, int index){
    return &(files->arr[index].name[0]);
}

list* read_from_file(char *fileName){
    FILE *f = fopen(fileName,"rb");

    if (!f) {
        puts("Error!");
        return NULL;
    }
    int size;
    fread(&size,sizeof(int), 1, f);

    file *fileArr = (file*) malloc(size * sizeof(file));
    fread(fileArr,sizeof(file), size, f);

    fclose(f);

    list *output = (list*) malloc(sizeof(list));
    output->size = size;
    output->arr = fileArr;
    return output;
}

int main()
{
    file file;
    char answer[32];
    int ans;
    int index;
    list *files; ///logikata tuk e da imame papka v koqto da gledame za vsichki fajlove
    menu:
    instructions();
    printf("Please select an answer: (answer must be chosen between 1 and 5)");
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
       // fileName = find_file_by_index(files, index);///maj ne raboti taka
        strcpy(fileName, files->arr[index].name);
        FILE *f = fopen(fileName,"w");
        read_from_file(fileName);
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
        printf("\tYou have selected remove a file option.\n\tPlease select the file you want to remove by his index: ");
        scanf("%d", &index);
        char *fileName = find_file_by_index(files, index);
        printf("point 1");
        printf("%s", fileName);
        remove(fileName);
        printf("point 2");
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
