#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

typedef struct{
    char name[30];
    char* content;
    char date[11];
}file;

typedef struct{
    file *arr;
    int size;
}list;

void instructions(){
    printf("Instructions:\n");
    printf("\tIn order to use a function, simply type it's number.\n");
    printf("\tThe list of options is:\n");
    printf("\t1.Read all file names\n\t2.Create new file\n\t3.Remove a file\n\t4.Exit\n");
}

void print(){
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

int validate(char c){
  if(c >= 'a' && c <= 'z') return 0;
  if(c >= 'A' && c <= 'Z') return 0;
  if(c == '.') return 0;
  if(c == ',') return 0;
  return 1;
}

int validate_date(char c, int index){
  if((index == 2 || index == 5) && c != '.') return 1;
  if(c >= '0' && c <= '9') return 0;
  if(c == '.' && (index == 2 || index == 5)) return 0;
  return 1;
}

void visualization(file story){
    system("cls");
    printf("Story's name: %s\nIt's date: %s\nAnd the Story itself:\n\t%s\n",story.name, story.date, story.content);
}


int main()
{
    file story;
    char answer[32];
    int ans;
    char file_type[] = ".bin";
    list *files; ///logikata tuk e da imame papka v koqto da gledame za vsichki fajlove
    menu:
    instructions();
    printf("\nPlease select an answer: (answer must be chosen between 1 and 4): ");
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
        if(!strcmp(answer,"yes") || !strcmp(answer,"Yes") || !strcmp(answer,"y")){
            system("cls");
            goto menu;
        }else{printf("Goodbye!");}
    }

    else if(ans == 2){ //create new file
        system("cls");
        char name [30];


        printf("You have selected the create option.\n\tPlease enter new story name: ");
        scanf("%s", story.name);

        for(int i=0; i<strlen(story.name); i++){
            if(validate(story.name[i]) == 1){

                printf("Invalid name!");
                printf("\nGo back to main menu? ");
                scanf("%s", answer);
                if(!strcmp(answer,"yes") || !strcmp(answer,"Yes") || !strcmp(answer,"y")){
                    system("cls");
                goto menu;
                }else{
                printf("Goodbye!");
                return 0;}
                }
        };

        char *fileName = calloc(34, sizeof(char));
        strcpy(fileName, story.name);
        strcat(fileName, file_type);

        printf("\tPlease enter story's date (dd.mm.yyyy):");
        scanf("%s", story.date);
        for(int i=0; i<strlen(story.date); i++){
            if(validate_date(story.date[i], i)){
                printf("Invalid date!");
                printf("\nGo back to main menu? ");
                scanf("%s", answer);
                if(!strcmp(answer,"yes") || !strcmp(answer,"Yes") || !strcmp(answer,"y")){
                    system("cls");
                goto menu;
                }else{
                printf("Goodbye!");
                return 0;
                }
            }
        };

        story.content = calloc(500, sizeof(char));
        char input;
        printf("\tPlease enter story's content: \n\t(to exit - type: ctrl + 'y' -> then: enter)\n\t");
        int j = 0;
        for(j = 0; input != 25; j++){
            input = getchar();
            story.content[j] = input;
        }
        story.content[j-1]='\0';

        visualization(story);

        FILE *f = fopen(fileName,"w+");
        printf("\nGo back to main menu? ");
        scanf("%s", answer);
        if(!strcmp(answer,"yes") || !strcmp(answer,"Yes") || !strcmp(answer,"y")){
            system("cls");
            goto menu;
        }else{
            printf("Goodbye!");}
    }

    else if(ans == 3){ //remove
        system("cls");
        printf("\tYou have selected remove a file option.\n\tPlease enter it's name: ");
        char name[32];
        scanf("%s", name);
        char fileName[34];
        strcpy(fileName, name);
        strcat(fileName, file_type);
        remove(fileName);
        printf("\tSuccess!");

        printf("\nGo back to main menu? ");
        scanf("%s", answer);
        if(!strcmp(answer,"yes") || !strcmp(answer,"Yes") || !strcmp(answer,"y")){
            system("cls");
            goto menu;
        }else{
            printf("Goodbye!");}
    }
    return 0;
}
