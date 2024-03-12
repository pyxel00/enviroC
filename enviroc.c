#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>

int main(int argc, char** argv) {
    FILE* main;
    FILE* git_ignore;

    int git_exists = system("which git > /dev/null 2>&1");
    int gcc_exists = system("which gcc > /dev/null 2>&1");

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] = '-') {
            switch (argv[i][1]) {
            case 'h':
                printf("enviroC is a C environment creator and runner. It is probably written very poorly but it works!\n commands :\n -h : Display this help screen!\n -c : Creates a main.c file inside src folder.\n -r : Compiles and runs the main.c file in the src file. Only supports gcc for now\n");
                abort();
                break;
            
            case 'c':
                mkdir("./src", 0755);
                main = fopen("./src/main.c", "w");
                git_ignore = fopen("./.gitignore", "w");

                fprintf(main, "#include <stdio.h>\n#include <stdlib.h>\n\nint main(int argc, char** argv) {\n\tprintf(\"Hello World!\");\n\treturn 0;\n}");
                fprintf(git_ignore, "./output");

                if(git_exists == 0) {
                    system("git init; git add --all");
                } else {
                    printf("Git not found. \n");
                }

                break;
            
            case 'r':
                mkdir("./output", 0755);

                if (gcc_exists == 0) {
                    system("gcc ./src/main.c -o ./output/program; ./output/program;");
                } else {
                    printf("GCC does not exist. Aborting");
                    abort();
                }

                break;

            default:
                printf("Unknown flag : %s\n", argv[i]);
                exit(1);
            }
        }
    }
}
