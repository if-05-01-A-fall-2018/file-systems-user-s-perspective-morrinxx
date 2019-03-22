#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <dirent.h>

int main(int argc, char const *argv[]) {
    struct dirent *direntry;

    DIR *directory = opendir(".");

    if (directory == NULL)
    {
        printf("Error when opening directory" );
        return 0;
    }
    while ((direntry = readdir(directory)) != NULL) {
        struct stat attributes;
        if(stat(direntry->d_name, &attributes) < 0) return 1;

        printf("\n");
        if(S_ISBLK(attributes.st_mode)) printf("b");
        else if (S_ISREG(attributes.st_mode)) printf("-");
        else if (S_ISDIR(attributes.st_mode)) printf("d");
        else if (S_ISCHR(attributes.st_mode)) printf("c");
        else if (S_ISLNK(attributes.st_mode)) printf("l");
        (attributes.st_mode & S_IRUSR) ? printf("r") : printf("-");
        (attributes.st_mode & S_IWUSR) ? printf("w") : printf("-");
        (attributes.st_mode & S_IXUSR) ? printf("x") : printf("-");
        (attributes.st_mode & S_IRGRP) ? printf("r") : printf("-");
        (attributes.st_mode & S_IWGRP) ? printf("w") : printf("-");
        (attributes.st_mode & S_IXGRP) ? printf("x") : printf("-");
        (attributes.st_mode & S_IROTH) ? printf("r") : printf("-");
        (attributes.st_mode & S_IWOTH) ? printf("w") : printf("-");
        (attributes.st_mode & S_IXOTH) ? printf("x ") : printf("- ");
        printf("%d ",attributes.st_uid);
        printf("%d ",attributes.st_gid);
        printf("%ld \t",attributes.st_size);
        char time[18];
        strftime(time, 18, "%Y-%m-%d-%H-%M", localtime(&attributes.st_mtime));
        printf("%s ",time);
        printf("%s",direntry->d_name );

    }
    closedir(directory);
    return 0;
}