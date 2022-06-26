#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "src/crypting/encrypt.c"
#include "src/searching/trie.c"
#include "src/searching/hashmap.c"

#define KEY "dsajlkdsaljkdsaj"
#define FILE_SUFFIX ".bin"

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
    printf("\t1.Read all file names\n\t2.Create new file\n\t3.Remove a file\n\t4.Find a story by name\n\t5.Find a story by date\n\t6.Exit\n");
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

void visualization(file *story){
    system("cls");
    printf("Story's name: %s\nIt's date: %s\nAnd the Story itself:\n\t%s\n",story->name, story->date, story->content);
}

file *extract(char *filename_, char *key){
	char *filename = calloc(100, sizeof(char));
	strcpy(filename, filename_);
	strcat(filename, FILE_SUFFIX);
    FILE *f = fopen(filename, "rb");
	if(!f){
		printf("Couldn't open such file\n");
		exit(0);
	}

    int file_sz;
    fseek(f, 0, SEEK_END);
    file_sz = ftell(f);
	if(file_sz == 0){
		printf("There is no information in this file\n");
		exit(0);
	}
    rewind(f);
    char *buffer = (char *)calloc(file_sz,sizeof(char)); 
    
    fread(buffer, sizeof(char), file_sz, f);

    char *decrypted = decrypt(buffer, key, file_sz);
    char *content = calloc(strlen(decrypted)+1, sizeof(char));
    char *date = calloc(11,sizeof(char));
    int i = 0;
    for(i = 0; decrypted[i]!='$' ;i++){
        date[i] = decrypted[i];
    }
    date[i] = '\0';
    
    strcpy(content,decrypted+strlen(date)+1);
    file *extraction = calloc(1, sizeof(file));
    printf("\n%s\n",content);
    strcpy(extraction->date,date);
    extraction->content = calloc(strlen(content)+1, sizeof(char));
    strcpy(extraction->content,content);
    extraction->content[strlen(content)+1] = '\0';
    strcpy(extraction->name,filename);
    return extraction;
}

char* fix_date(char *date){
    int *tokens = tokenize_date(date);    
    if(tokens[0] > 31 || tokens[1] > 12) return NULL;
    char *result = calloc(11, sizeof(char));
    result[10] = '\0';
    result[2] = '.';
    result[5] = '.';
    for(int i = 0; i < 2; i++){
        result[3 * i] = '0' + tokens[i] / 10;    
        result[1 + 3 * i] = '0' + tokens[i] % 10;
    }
    for(int i = 0; i < 4; i++){
        result[6 + i] = '0' + (tokens[2] / intpow(10, 3 - i)) % 10;
    }
    return result;
}

int main()
{
    char key[255];
    printf("ENTER PASSWORD FOR DIARY: ");
    scanf("%s", key);
    if(rsa(key)){
        printf("wrong password ||| ABORTING\n");
        return -1;
    }
    file story;
    char answer[32];
    int ans;
    char file_type[] = ".bin";
    list *files; ///logikata tuk e da imame papka v koqto da gledame za vsichki fajlove
    menu:
    instructions();
    printf("\nPlease select an answer: (answer must be chosen between 1 and 7): ");
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
    
        visualization(&story);

        FILE *f = fopen(fileName,"w");
        strcpy(story.date,fix_date(story.date));
        int text_len = strlen(story.date)+strlen(story.content)+1;
        char *text = calloc(text_len, sizeof(char));

        strcat(text,story.date);
        strcat(text,"$");
        strcat(text,story.content);

        char *encrypted = encrypt(text,key,text_len);
        printf("\nGo back to main menu? ");
        fwrite(encrypted, sizeof(char), text_len,f);
        scanf("%s", answer);
        fclose(f);
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

    }else if(ans == 4){
		system("cls");
		char *filename = calloc(100, sizeof(char));
		printf("Enter the file's name: ");
		scanf("%s", filename);
        visualization(extract(filename, key));
		free(filename);

    }else if(ans == 5){
		char *date = calloc(20, sizeof(char));
		printf("Enter the date: ");
		scanf("%s", date);
		char *excluded[] = {
			".",
			"..",
			".git",
			"src",
			"tests",
			".gitignore",
			"LICENSE",
			"main.c"
		};
		int data_len = 1;
		file **data;
		DIR *d;
		struct dirent *dir;
		d = opendir(".");
		if (d){
			while ((dir = readdir(d)) != NULL){
				//printf("%s\n",dir->d_name);
				int skip = 0;
				for(int i = 0; i < 8; i++){
					if(!strcmp(dir->d_name, excluded[i])) skip = 1; 
				}	
				if(skip == 1) continue;
				data = realloc(data, data_len * sizeof(file*));
				data[data_len - 1] = extract(dir->d_name, key);
				data_len++;
			}
			closedir(d);
		}
		hashmap_date_t *hashmap = hashmap_date_init(100);
		for(int i = 0; i < data_len; i++){
			hashmap_date_insert(hashmap, data[i]->date, data[i]);
		}
		file* result = hashmap_date_find(hashmap, date);
		if(result == NULL){
			system("cls");
			printf("No file with such date was found.\n");
		}else{
			visualization(result); 
		}
        printf("\nGo back to main menu? ");
        scanf("%s", answer);
        
        if(!strcmp(answer,"yes") || !strcmp(answer,"Yes") || !strcmp(answer,"y")){
            system("cls");
            goto menu;
        }else{
            printf("Goodbye!");
		}

	}else if(ans == 6){
		return 0;
	}
    return 0;
}
