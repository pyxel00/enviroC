#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>

int main(int argc, char** argv) {

    FILE* main;
    FILE* gitignore;
    int flag;
    char* filename = NULL;
    char source[7] = "./src/";
    char* fullpath = NULL;
    char command[60 + sizeof(fullpath)] = {'\0'};;
    bool doesGitExist = system("which git > /dev/null");
    bool doesGccExist = system("which gcc > /dev/null");

    while ((flag = getopt (argc, argv, "c:r:h")) != -1)
    switch (flag) {
    
    case 'c':
        filename = optarg;
        fullpath = strcat(source, filename);

        mkdir("./src", 0700);
        main = fopen(fullpath ,"w");
        gitignore = fopen(".gitignore", "w");
        fprintf(gitignore, "/output");
        if (doesGitExist) {
            printf("Git does not exist. Not creating a git repository\n");
        } else {
            system("git init; git add --all");
        }
        
        break;
    
    case 'r':
        if (doesGccExist) {
            printf("GCC does not exist.");
        } else {
            filename = optarg;
            fullpath = strcat(source, filename);

            mkdir("./output", 0700);
            sprintf(command, "gcc %s -o program; mv program ./output; ./output/program", fullpath);
            system(command);
        }
        break;
    
    case 'h':
        printf("enviroC is a C environment creator and runner. It is probably written very poorly but it works!\n flags:\n -h : Display this help screen!\n -c : Takes in a file name ending in .c. Theoretically it can create all types of files but it does not work very well with others. \nIt creates a unique file unless the specified name is the same for any of the others.\n -r : Compiles and runs the specified file. Only support gcc for now\n");
        break;

    default:
        abort();
    }

}