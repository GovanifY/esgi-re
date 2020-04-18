#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>

void stage2(unsigned int result, char* argv[]) {
    unsigned int x = rand() & 0xff;
    x |= (rand() & 0xff) << 8;
    x |= (rand() & 0xff) << 16;
    x |= (rand() & 0xff) << 24;

    char buffer[64];
    int * p_tgr = &x; 
    printf("pointeur vers target: %x\n", p_tgr);


    while (1) {
        printf("Ecrivez: ");
        fgets(buffer, 64, stdin);
        printf("Vous avez écrit: ");
        // format string
        printf(buffer);
        printf("\n");


        if(x == result) {
            printf("Tout est ok! Affichons le fichier en argument:\n");
            char cmd[50] = "cat ";
            // command injection
            strcat(cmd,argv[1]);
            system(cmd);
            return;
        } else {
            printf("Raté\n");
        }
    }
}

int main(int argc, char *argv[])
{

    uid_t uid=getuid(), euid=geteuid();
    if (uid<0 || uid!=euid || euid==0 || uid==0) {
        printf("Ne me lancez pas en root!\n");
        return EXIT_FAILURE;
    }

    FILE * fp;
    fp = fopen ("/tmp/user","w");

    register struct passwd *pw; 
    pw = getpwuid(getuid());
    fprintf (fp, pw->pw_name);
    fclose (fp);

    // race condition
    sleep(3);

    fp = fopen ("/tmp/user","r");
    char *line = NULL;
    size_t len = 0;
    getline(&line, &len, fp);
    if(strcmp(line, "root")!=0) {
        printf("Raté\n");
        exit(EXIT_FAILURE);
    }
    stage2(0x10000, argv);


}
