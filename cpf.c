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
       printf("Error when opening the file: \n");
       return 0;
   }
   printf("File-open: SUCCESS! \n");
   int sizeOfFile = lseek(fd, 0, SEEK_END);
   char* buffer[sizeOfFile];
   lseek(fd, 0, SEEK_SET);
   read(fd, buffer, sizeof(buffer));
   int fd2 = open(newPath, O_WRONLY);

   if(fd2 < 0){
       fd2 = open(newPath, O_CREAT | O_WRONLY);
   }
   else printf("Owerwriting file \n");
   int success = write(fd2, buffer, sizeOfFile);

   if(success == sizeOfFile)printf("Successfully copied \n");
   close(fd);
   close(fd2);
   return 0;
 }
