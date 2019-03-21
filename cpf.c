#include "stdio.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

 struct stat attributes;
 int main(int argc, char const *argv[]) {
   if(argc != 3)return 0;
   const char* originPath = argv[1];
   const char* newPath = argv[2];
   int fd = open(originPath, O_RDONLY);
   if(fd < 0){
       printf("Error when opening the file: \n" + fd);
       return 0;
   }
   printf("File-open: SUCCESS!\n");
   int sizeOfFile = lseek(fd, 0, SEEK_END);
   char* buffer[sizeOfFile];
   read(fd, buffer, sizeof(buffer));
   int fd2 = open(newPath, O_WRONLY);
   if(fd2 != 0){
       mkdir(newPath, O_WRONLY);
       fd2 = open(newPath, O_WRONLY);
   }
   int success = write(fd, buffer, sizeof(buffer));

   if(success == 0)printf("Successfully copied");
   close(fd);
   close(fd2);
   return 0;
 }
