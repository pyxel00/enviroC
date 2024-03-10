#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>

int main(int argc, char** argv) {

    FILE* main;
    FILE* git_ignore;
    
    char flag;
    char main_code[90] = "#include <stdio.h>\n#include <stdlib.h>\nint main(int argc, char** argv) {\n\treturn 0;\n}";
    char compile_command[] = {'\0'};

    while ((flag = getopt(argc, argv, "cr:h")) != -1)

    switch(flag) {
    case 'c':
        int git_exists = system("which git > /dev/null");
        mkdir("./src", 0755);

        main = fopen("./src/main.c", "w");
        git_ignore = fopen("./.gitignore", "w");

        fprintf(main, main_code);
        fprintf(git_ignore, "/output");

        if (git_exists == 0) {
            printf("Found git. Commencing..\n");
            system("git init; git add --all");
        } else {
            printf("Git not found..");
            continue;
        }

        break;

    case 'r':
        int gcc_exists = system("which gcc > /dev/null");
        mkdir("./output", 0755);

        char* filepath = optarg;

        if (gcc_exists == 0) {
            sprintf(compile_command, "gcc %s -o ./output/program; ./output/program", filepath);
            system(compile_command);
        } else {
            printf("GCC does not exist. Aborting.");
            abort();
        }
        break;

    case 'h':
        printf("enviroC is a C environment creator and runner. It is probably written very poorly but it works!\n flags:\n -h : Display this help screen!\n -c : Creates a main.c file inside src folder.\n -r : Compiles and runs the specified file. Requires full path of the file. Only support gcc for now\n");
        break;

    default:
        abort();
    }
}
