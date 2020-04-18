#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<errno.h>
#include<unistd.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<dirent.h>
#include"grep.h"
char *readline(int fd, char* str) {
        char ch = ' ';
        int i = 0, x;
        while(ch != '\n') {
               x =  read(fd, &ch, 1);
		if(x == 0)
			return NULL;
                str[i] = ch;
                i++;
        }
        str[i-1] = '\0';
        return str;
}
int find(char *word, char *str) {
        char *q;
        q = strstr(str, word);
        if(q != NULL) {
            return 1;
        } 
        else {
            return 0;
        } 
}
int ifind(char *word,char *str) {
        char *q;
        q = strcasestr(str, word);
        if(q != NULL) {
            return 1;
        } 
        else {
            return 0;
        } 
}
char *wfind(char *word,char *str) {
         char *p = NULL;
         size_t len = strlen(word);
         if (len > 0) {
             for (p = str; (p = strstr(p, word)) != NULL; p++) {
                if (p == str || !isalnum((unsigned char)p[-1])) {
                   if (!isalnum((unsigned char)p[len]))
                     break;  /* we have a match! */
                     p += len;   /* next match is at least len+1 bytes away */ 
                   }
                }
         }
         return p;
}
char *wifind(char *word,char *str) {
         char *p = NULL;
         size_t len = strlen(word);
         if (len > 0) {
             for (p = str; (p = strcasestr(p, word)) != NULL; p++) {
                if (p == str || !isalnum((unsigned char)p[-1])) {
                   if (!isalnum((unsigned char)p[len]))
                     break;  /* we have a match! */
                     p += len;   /* next match is at least len+1 bytes away */ 
                   }
                }
         }
         return p;
}
void listFilesRecursively(char *basePath, char* word) {
    char path[1000], str[1000];
    int fd, i;
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    // Unable to open directory stream
    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
           // printf("%s/%s\n", basePath, dp->d_name);
            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
            if(opendir(path) != NULL) {
               listFilesRecursively(path, word);
            }
            else {
               fd = open(path, O_RDONLY);
               while(readline(fd, str)) {
                   i = find(word, str);
                   if(i == 1) {
                      printf("%s:%s\n", path, str);
                   }
               }
               close(fd);
            }
        }
    }
}
char *readline1(int fd1, char* str1) {
        char ch = ' ';
        int i = 0, x;
        while(ch != '\n') {
               x =  read(fd1, &ch, 1);
		if(x == 0)
			return NULL;
                str1[i] = ch;
                i++;
        }
        str1[i-1] = '\0';
        return str1;
}
void listFilesRecursively1(char *basePath, char* word, int iflag, int vflag, int wflag, int cflag, int mflag, int bflag, int qflag, int Hflag, int hflag, int fflag, int eflag, int num) {
    char path[1000], str[1000];
    int fd, i, count = 0, count1 = 0, count2 = 0, count3 = 0, count4 = 0, count5 = 0, count6 = 0, count7 = 0, count8 = 0, count9 = 0, count10 = 0, count11 = 0, count12 = 0, count13 = 0, count14 = 0;
    int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0, c7 = 0, c8 = 0, c9 = 0, c10 = 0, c11 = 0, c12 = 0, c13 = 0, c14 = 0, c15 = 0, c16 = 0, c17 = 0, c18 = 0, c19 = 0, c20 = 0;
    char *point;
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    point = (char*)malloc(1000);
    // Unable to open directory stream
    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
           // printf("%s/%s\n", basePath, dp->d_name);
            // Construct new path from our base path
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
            if(opendir(path) != NULL) {
               listFilesRecursively(path, word);
            }
            else {
               fd = open(path, O_RDONLY);
               while(readline(fd, str)) {
                   //ri
                   if(iflag == 1 && vflag != 1 && wflag != 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         i = ifind(word, str);
                         if(i == 1) {
                             printf("%s:%s\n", path, str);
                         }
                   }
                   //rv
                   if(iflag != 1 && vflag == 1 && wflag != 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         i = find(word, str);
                         if(i == 0) {
                             printf("%s:%s\n", path, str);
                         }
                   }
                   //rw
                   if(iflag != 1 && vflag != 1 && wflag == 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         point = wfind(word, str);
                         if(point != NULL) {
                             printf("%s:%s\n", path, str);
                         }
                   }
                   //rc
                   if(iflag != 1 && vflag != 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         i = find(word, str);
                         if(i == 1) {
                             count++;
                         }
                   }
                   //rm
                   if(iflag != 1 && vflag != 1 && wflag != 1 && cflag != 1 && mflag == 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         i = find(word, str);
                         if(i == 1) {
                             if(count1 < num) {
                                printf("%s:%s\n", path, str);
                                count1++;
                             }
                         }
                   }
                   //rh
                   if(iflag != 1 && vflag != 1 && wflag != 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         i = find(word, str);
                         if(i == 1) {
                             if(hflag == 1) {
                                 puts(str);
                             }
                             else
                                 printf("%s:%s\n", path, str);
                         }
                   }
                   //riv
                   if(iflag == 1 && vflag == 1 && wflag != 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         i = ifind(word, str);
                         if(i == 0) {
                             printf("%s:%s\n", path, str);
                         }
                   }
                   //riw
                   if(iflag == 1 && vflag != 1 && wflag == 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         point = wifind(word, str);
                         if(point != NULL) {
                             printf("%s:%s\n", path, str);
                         }
                   }
                   //ric
                   if(iflag == 1 && vflag != 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         i = ifind(word, str);
                         if(i == 1) {
                             count2++;
                         }
                   }
                   //rim
                   if(iflag == 1 && vflag != 1 && wflag != 1 && cflag != 1 && mflag == 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         i = ifind(word, str);
                         if(i == 1) {
                             if(count1 < num) {
                                printf("%s:%s\n", path, str);
                                count1++;
                             }
                         }
                   }
                   //rih
                   if(iflag == 1 && vflag != 1 && wflag != 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         i = ifind(word, str);
                         if(i == 1) {
                             if(hflag == 1) {
                                 puts(str);
                             }
                             else
                                 printf("%s:%s\n", path, str);
                         }
                   }
                   //rvw
                   if(iflag != 1 && vflag == 1 && wflag == 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         point = wfind(word, str);
                         if(point == NULL) {
                             printf("%s:%s\n", path, str);
                         }
                   }
                   //rvc
                   if(iflag != 1 && vflag == 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         i = find(word, str);
                         if(i == 0) {
                             count3++;
                         }
                   }
                   //rvm
                   if(iflag != 1 && vflag == 1 && wflag != 1 && cflag != 1 && mflag == 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         i = find(word, str);
                         if(i == 0) {
                             if(count1 < num) {
                                printf("%s:%s\n", path, str);
                                count1++;
                             }
                         }
                   }
                   //rvh
                   if(iflag != 1 && vflag == 1 && wflag != 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         i = find(word, str);
                         if(i == 0) {
                             if(hflag == 1) {
                                 puts(str);
                             }
                             else
                                 printf("%s:%s\n", path, str);
                         }
                   }
                   //rwc
                   if(iflag != 1 && vflag != 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         point = wfind(word, str);
                         if(point != NULL) {
                             count4++;
                         }
                   }
                   //rwm
                   if(iflag != 1 && vflag != 1 && wflag == 1 && cflag != 1 && mflag == 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         point = wfind(word, str);
                         if(point != NULL) {
                             if(count5 < num) {
                                printf("%s:%s\n", path, str);
                                count5++;
                             }
                         }
                   }
                   //rwh
                   if(iflag != 1 && vflag != 1 && wflag == 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         point = wfind(word, str);
                         if(point != NULL) {
                             if(hflag == 1) {
                                 puts(str);
                             }
                             else
                                 printf("%s:%s\n", path, str);
                         }
                   }
                   //rcm
                   if(iflag != 1 && vflag != 1 && wflag != 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         i = find(word, str);
                         if(i == 1) {
                              if(count6 < num ) {
                                  count6++;
                              }
                         }
                   }
                   //rch
                   if(iflag != 1 && vflag != 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         i = find(word, str);
                         if(i == 1) {
                             count7++;
                         }
                   }
                   //rmh
                   if(iflag != 1 && vflag != 1 && wflag != 1 && cflag != 1 && mflag == 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         i = find(word, str);
                         if(i == 1) {
                             if(count8 < num ) {
                                  if(hflag == 1) {
                                     puts(str);
                                  }
                                  else 
                                     printf("%s:%s\n", path, str);
                             }
                             count8++;
                         }
                   }
                   //rivw
                   if(iflag == 1 && vflag == 1 && wflag == 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         point = wifind(word, str);
                         if(point == NULL) {
                             printf("%s:%s\n", path, str);
                         }
                   }
                   //rivc
                   if(iflag == 1 && vflag == 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         i = ifind(word, str);
                         if(i == 0) {
                             count9++;
                         }
                   }
                   //rivm
                   if(iflag == 1 && vflag == 1 && wflag != 1 && cflag != 1 && mflag == 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         i = ifind(word, str);
                         if(i == 0) {
                             if(count1 < num) {
                                printf("%s:%s\n", path, str);
                                count1++;
                             }
                         }
                   }
                   //rivh or rivH
                   if(iflag == 1 && vflag == 1 && wflag != 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         i = ifind(word, str);
                         if(i == 0) {
                             if(hflag == 1) {
                                 puts(str);
                             }
                             else
                                 printf("%s:%s\n", path, str);
                         }
                   }
                   //riwc
                   if(iflag == 1 && vflag != 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         point = wifind(word, str);
                         if(point != NULL) {
                             count10++;
                         }
                   }
                   //riwm
                   if(iflag == 1 && vflag != 1 && wflag == 1 && cflag != 1 && mflag == 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         point = wifind(word, str);
                         if(point != NULL) {
                             if(count5 < num) {
                                printf("%s:%s\n", path, str);
                                count5++;
                             }
                         }
                   }
                   //riwh
                   if(iflag == 1 && vflag != 1 && wflag == 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         point = wifind(word, str);
                         if(point != NULL) {
                             if(hflag == 1) {
                                 puts(str);
                             }
                             else
                                 printf("%s:%s\n", path, str);
                         }
                   }
                   //rvwc
                   if(iflag != 1 && vflag == 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         point = wfind(word, str);
                         if(point == NULL) {
                             count11++;
                         }
                   }
                   //rvwm
                   if(iflag != 1 && vflag == 1 && wflag == 1 && cflag != 1 && mflag == 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         point = wfind(word, str);
                         if(point == NULL) {
                             if(count5 < num) {
                                printf("%s:%s\n", path, str);
                                count5++;
                             }
                         }
                   }
                   //rvwhor H
                   if(iflag != 1 && vflag == 1 && wflag == 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         point = wfind(word, str);
                         if(point == NULL) {
                             if(hflag == 1) {
                                 puts(str);
                             }
                             else
                                 printf("%s:%s\n", path, str);
                         }
                   }
                   //rvcm
                   if(iflag != 1 && vflag == 1 && wflag != 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         i = find(word, str);
                         if(i == 0) {
                              if(count12 < num ) {
                                  count12++;
                              }
                         }
                   }
                   //rvmh
                   if(iflag != 1 && vflag != 1 && wflag != 1 && cflag != 1 && mflag == 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         i = find(word, str);
                         if(i == 0) {
                             if(count8 < num ) {
                                  if(hflag == 1) {
                                     puts(str);
                                  }
                                  else 
                                     printf("%s:%s\n", path, str);
                             }
                             count8++;
                         }
                   }
                   //rvch
                   if(iflag != 1 && vflag == 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         i = find(word, str);
                         if(i == 0) {
                             count13++;
                         }
                   }
                   //rimh
                   if(iflag != 1 && vflag != 1 && wflag != 1 && cflag != 1 && mflag == 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         i = ifind(word, str);
                         if(i == 1) {
                             if(count8 < num ) {
                                  if(hflag == 1) {
                                     puts(str);
                                  }
                                  else 
                                     printf("%s:%s\n", path, str);
                             }
                             count8++;
                         }
                   }
                   //rwcm
                   if(iflag != 1 && vflag != 1 && wflag == 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         point = wfind(word, str);
                         if(point != NULL) {
                             if(count14 < num) {
                                //printf("%s:%s\n", path, str);
                                count14++;
                             }
                         }
                   }
                   //rwmh
                   if(iflag != 1 && vflag != 1 && wflag == 1 && cflag != 1 && mflag == 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         point = wfind(word, str);
                         if(point != NULL) {
                             if(count8 < num ) {
                                  if(hflag == 1) {
                                     puts(str);
                                  }
                                  else 
                                     printf("%s:%s\n", path, str);
                             }
                             count8++;
                         }
                   }
                   //rcmh
                   if(iflag != 1 && vflag != 1 && wflag != 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         i = find(word, str);
                         if(i == 1) {
                             if(c1 < num) {
                                c1++;
                             }
                         }
                   } 
                   //rich
                   if(iflag == 1 && vflag != 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         i = ifind(word, str);
                         if(i == 1) {
                             c2++;
                         }
                   } 
                   //ricm
                   if(iflag == 1 && vflag != 1 && wflag != 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         i = ifind(word, str);
                         if(i == 1) {
                              if(c3 < num ) {
                                  c3++;
                              }
                         }
                   }  
                   //rwch
                   if(iflag != 1 && vflag != 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         point = wfind(word, str);
                         if(point != NULL) {
                             c8++;
                         }
                   }
                   //rivwc
                   if(iflag == 1 && vflag == 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         point = wifind(word, str);
                         if(point == NULL) {
                             c4++;
                         }
                   }
                   //rivwm
                   if(iflag == 1 && vflag == 1 && wflag == 1 && cflag != 1 && mflag == 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         point = wifind(word, str);
                         if(point == NULL) {
                             if(count5 < num) {
                                printf("%s:%s\n", path, str);
                                count5++;
                             }
                         }
                   }
                   //rivwh
                   if(iflag == 1 && vflag == 1 && wflag == 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         point = wifind(word, str);
                         if(point == NULL) {
                             if(hflag == 1) {
                                 puts(str);
                             }
                             else
                                 printf("%s:%s\n", path, str);
                         }
                   } 
                   //rivcm
                   if(iflag == 1 && vflag == 1 && wflag != 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         i = ifind(word, str);
                         if(i == 0) {
                              if(c5 < num ) {
                                  c5++;
                              }
                         }
                   } 
                   //rivch
                   if(iflag == 1 && vflag == 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         i = ifind(word, str);
                         if(i == 0) {
                             c6++;
                         }
                   }
                   //rivmh
                   if(iflag == 1 && vflag == 1 && wflag != 1 && cflag != 1 && mflag == 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         i = ifind(word, str);
                         if(i == 0) {
                             if(count8 < num ) {
                                  if(hflag == 1) {
                                     puts(str);
                                  }
                                  else 
                                     printf("%s:%s\n", path, str);
                             }
                             count8++;
                         }
                   }
                   //riwmh
                   if(iflag == 1 && vflag != 1 && wflag == 1 && cflag != 1 && mflag == 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         point = wifind(word, str);
                         if(point != NULL) {
                             if(count8 < num ) {
                                  if(hflag == 1) {
                                     puts(str);
                                  }
                                  else 
                                     printf("%s:%s\n", path, str);
                             }
                             count8++;
                         }
                   }
                   //rvwmh    
                   if(iflag != 1 && vflag == 1 && wflag == 1 && cflag != 1 && mflag == 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         point = wfind(word, str);
                         if(point == NULL) {
                             if(count8 < num ) {
                                  if(hflag == 1) {
                                     puts(str);
                                  }
                                  else 
                                     printf("%s:%s\n", path, str);
                             }
                             count8++;
                         }
                   }
                   //riwcm
                   if(iflag == 1 && vflag != 1 && wflag == 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         point = wifind(word, str);
                         if(point != NULL) {
                             if(c7 < num) {
                                //printf("%s:%s\n", path, str);
                                c7++;
                             }
                         }
                   }
                   //riwch
                   if(iflag == 1 && vflag != 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         point = wifind(word, str);
                         if(point != NULL) {
                             c9++;
                         }
                   }
                   //ricmh
                   if(iflag == 1 && vflag != 1 && wflag != 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         i = ifind(word, str);
                         if(i == 1) {
                             if(c10 < num) {
                                c10++;
                             }
                         }
                   } 
                   //rvwcm
                   if(iflag != 1 && vflag == 1 && wflag == 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         point = wfind(word, str);
                         if(point == NULL) {
                             if(c11 < num) {
                                //printf("%s:%s\n", path, str);
                                c11++;
                             }
                         }
                   }
                   //rvwch
                   if(iflag != 1 && vflag == 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         point = wfind(word, str);
                         if(point == NULL) {
                             c12++;
                         }
                   }
                   //rwcmh
                    if(iflag != 1 && vflag != 1 && wflag == 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         point = wfind(word, str);
                         if(point != NULL) {
                             if(c13 < num) {
                                c13++;
                             }
                         }
                   } 
                   //rcmvh
                   if(iflag != 1 && vflag == 1 && wflag != 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         i = find(word, str);
                         if(i == 0) {
                             if(c14 < num) {
                                c14++;
                             }
                         }
                   } 
                   //rivwcm
                   if(iflag == 1 && vflag == 1 && wflag == 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                         point = wifind(word, str);
                         if(point == NULL) {
                             if(c15 < num) {
                                //printf("%s:%s\n", path, str);
                                c15++;
                             }
                         }
                   }
                   //rivwmh
                   if(iflag == 1 && vflag == 1 && wflag == 1 && cflag != 1 && mflag == 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         point = wifind(word, str);
                         if(point == NULL) {
                             if(count8 < num ) {
                                  if(hflag == 1) {
                                     puts(str);
                                  }
                                  else 
                                     printf("%s:%s\n", path, str);
                             }
                             count8++;
                         }
                   }
                   //rivwch
                   if(iflag == 1 && vflag == 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         point = wifind(word, str);
                         if(point == NULL) {
                             c16++;
                         }
                   }
                   //rvwcmh
                   if(iflag != 1 && vflag == 1 && wflag == 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         point = wfind(word, str);
                         if(point == NULL) {
                             if(c17 < num) {
                                c17++;
                             }
                         }
                   } 
                   //rwcmhi
                   if(iflag == 1 && vflag != 1 && wflag == 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         point = wifind(word, str);
                         if(point != NULL) {
                             if(c18 < num) {
                                c18++;
                             }
                         }
                   }
                   //rcmhvi
                   if(iflag == 1 && vflag == 1 && wflag != 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         i = ifind(word, str);
                         if(i == 0) {
                             if(c19 < num) {
                                c19++;
                             }
                         }
                   }
                   //rcmhviw
                   if(iflag == 1 && vflag == 1 && wflag == 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                         point = wifind(word, str);
                         if(point == NULL) {
                             if(c20 < num) {
                                c20++;
                             }
                         }
                   }  
               }
               if(iflag != 1 && vflag != 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                   printf("%s:%d\n", path, count);
               }
               if(iflag == 1 && vflag != 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                   printf("%s:%d\n", path, count2);
               }
               if(iflag != 1 && vflag == 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                   printf("%s:%d\n", path, count3);
               }
               if(iflag != 1 && vflag != 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                   printf("%s:%d\n", path, count4);
               }
               if(iflag != 1 && vflag != 1 && wflag != 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                   printf("%s:%d\n", path, count6);
               }
               if(iflag != 1 && vflag != 1 && wflag != 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                   printf("%s:%d\n", path, count6);
               }
               if(iflag != 1 && vflag != 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                   if(Hflag == 1) {
                       printf("%s:%d\n", path, count7);
                   }
                   else
                       printf("%d\n", count7);
               }
               if(iflag == 1 && vflag == 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                   printf("%s:%d\n", path, count9);
               }
               if(iflag == 1 && vflag != 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                   printf("%s:%d\n", path, count10);
               }
               if(iflag != 1 && vflag == 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                   printf("%s:%d\n", path, count11);
               }
               if(iflag != 1 && vflag == 1 && wflag != 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
                   printf("%s:%d\n", path, count12);
               }
               if(iflag != 1 && vflag == 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                   printf("%s:%d\n", path, count13);
               }
               if(iflag != 1 && vflag != 1 && wflag == 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && Hflag != 1 && hflag != 1  && fflag != 1  && eflag != 1) {
                   printf("%s:%d\n", path, count14);
               }
               if(iflag != 1 && vflag != 1 && wflag != 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                   if(Hflag == 1) {
                       printf("%s:%d\n", path, c1);
                   }
                   else
                       printf("%d\n", c1);
               }
               if(iflag == 1 && vflag != 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                   if(Hflag == 1) {
                       printf("%s:%d\n", path, c2);
                   }
                   else
                       printf("%d\n", c2);
               }
               if(iflag == 1 && vflag != 1 && wflag != 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && Hflag != 1 && hflag != 1  && fflag != 1  && eflag != 1) {
                   printf("%s:%d\n", path, c3);
               }
               if(iflag == 1 && vflag == 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && Hflag != 1 && hflag != 1  && fflag != 1  && eflag != 1) {
                   printf("%s:%d\n", path, c4);
               }
               if(iflag == 1 && vflag == 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                   if(Hflag == 1) {
                       printf("%s:%d\n", path, c6);
                   }
                   else
                       printf("%d\n", c6);
               }
               if(iflag == 1 && vflag != 1 && wflag == 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && Hflag != 1 && hflag != 1  && fflag != 1  && eflag != 1) {
                   printf("%s:%d\n", path, c7);
               }
               if(iflag != 1 && vflag != 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                   if(Hflag == 1) {
                       printf("%s:%d\n", path, c8);
                   }
                   else
                       printf("%d\n", c8);
               }
               if(iflag == 1 && vflag != 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                   if(Hflag == 1) {
                       printf("%s:%d\n", path, c9);
                   }
                   else
                       printf("%d\n", c9);
               }
               if(iflag == 1 && vflag != 1 && wflag != 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                   if(Hflag == 1) {
                       printf("%s:%d\n", path, c10);
                   }
                   else
                       printf("%d\n", c10);
               }
               if(iflag != 1 && vflag== 1 && wflag == 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && Hflag != 1 && hflag != 1  && fflag != 1  && eflag != 1) {
                   printf("%s:%d\n", path, c11);
               }
               if(iflag != 1 && vflag== 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                   if(Hflag == 1) {
                       printf("%s:%d\n", path, c12);
                   }
                   else
                       printf("%d\n", c12);
               }
               if(iflag != 1 && vflag != 1 && wflag == 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                   if(Hflag == 1) {
                       printf("%s:%d\n", path, c13);
                   }
                   else
                       printf("%d\n", c13);
               }
               if(iflag != 1 && vflag == 1 && wflag != 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                   if(Hflag == 1) {
                       printf("%s:%d\n", path, c14);
                   }
                   else
                       printf("%d\n", c14);
               }
               if(iflag == 1 && vflag== 1 && wflag == 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && Hflag != 1 && hflag != 1  && fflag != 1  && eflag != 1) {
                   printf("%s:%d\n", path, c15);
               }
               if(iflag == 1 && vflag == 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                   if(Hflag == 1) {
                       printf("%s:%d\n", path, c16);
                   }
                   else
                       printf("%d\n", c16);
               }
               if(iflag != 1 && vflag == 1 && wflag == 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                   if(Hflag == 1) {
                       printf("%s:%d\n", path, c17);
                   }
                   else
                       printf("%d\n", c17);
               }
               if(iflag == 1 && vflag != 1 && wflag == 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                   if(Hflag == 1) {
                       printf("%s:%d\n", path, c18);
                   }
                   else
                       printf("%d\n", c18);
               }
               if(iflag == 1 && vflag == 1 && wflag != 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                   if(Hflag == 1) {
                       printf("%s:%d\n", path, c19);
                   }
                   else
                       printf("%d\n", c19);
               }
               if(iflag == 1 && vflag == 1 && wflag == 1 && cflag == 1 && mflag == 1 && bflag != 1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
                   if(Hflag == 1) {
                       printf("%s:%d\n", path, c20);
                   }
                   else
                       printf("%d\n", c20);
               }
               close(fd);
               count1 = 0;
               count = 0;
               count2 = 0;
               count3 = 0;
               count4 = 0;
               count5 = 0;
               count6 = 0;
               count7 = 0;
               count8 = 0;
               count9 = 0;
               count10 = 0;
               count11 = 0;
               count12 = 0;
               count13 = 0;
               count14 = 0;
               c1 = 0;
               c2 = 0;
               c3 = 0;
               c4 = 0;
               c5 = 0;
               c6 = 0;
               c7 = 0;
               c8 = 0;
               c9 = 0;
               c10 = 0;
               c11 = 0;
               c12 = 0;
               c13 = 0;
               c14 = 0;
               c15 = 0;
               c16 = 0;
               c17 = 0;
               c18 = 0;
               c19 = 0;
            }
        }
    }
}
