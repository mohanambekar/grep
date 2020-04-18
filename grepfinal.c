#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<errno.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<getopt.h>
#include<dirent.h>
#include"grep.h"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

int match(char *regexp, char *text);
int matchhere(char *regexp, char *text);
int matchstar(int c, char *regexp, char *text);
int match(char *regexp, char *text) {
       if (regexp[0] == '^')
            return matchhere(regexp+1, text);
       do {   
            if (matchhere(regexp, text) == 1)
                return 1;
       } while (*text++ != '\0');
       return 0;
}
int matchhere(char *regexp, char *text) {
       if (regexp[0] == '\0')
            return 1;
       if (regexp[1] == '*')
            return matchstar(regexp[0], regexp+2, text);
       if (regexp[0] == '$' && regexp[1] == '\0')
            return *text == '\0';
       if (*text!='\0' && (regexp[0]=='.' || regexp[0]==*text))
            return matchhere(regexp+1, text+1);
       return 0;
}
int matchstar(int c, char *regexp, char *text) {
        do { 
            if (matchhere(regexp, text) == 1)
                return 1;
        } while (*text != '\0' && (*text++ == c || c == '.'));
        return 0;
}


int main(int argc, char *argv[]) {
       int option = 0, flag = 1, rflag = 2, iflag = 3, vflag = 4, fflag = 5, wflag = 6, cflag = 7, mflag = 8, bflag = 9, qflag = 10, Hflag = 11, hflag = 12, eflag = 13, fd, num, m = 0, n;
       char *str, pattern[1000][1000];
       str = (char*)malloc(1000);
       while ((option = getopt(argc, argv, "rivfwcm:bqHhe:")) != -1) {
             switch (option) {
                 case 'r':
                    rflag = 1;
                    break;
                 case 'i':
                    iflag = 1;
                    break;
                 case 'v':
                    vflag = 1;
                    break;
                 case 'f':
                    fflag = 1;
                    break;
                 case 'w':
                    wflag = 1;
                    break;
                 case 'c':
                    cflag = 1;
                    break;
                 case 'm':
                    mflag = 1;
                    num = atoi(optarg);
                    break;
                 case 'b':
                    bflag = 1;
                    break;
                 case 'q':
                    qflag = 1;
                    break;
                 case 'H':
                    Hflag = 1;
                    break;
                 case 'h':
                    hflag = 1;
                    break;
                 case 'e':
                    eflag = 1;
                    break;
                /* default :
                    flag = 1;*/
            }
       }
       //normal
       if(iflag != 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag != 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
            fd = open(argv[2], O_RDONLY);
            while(readline(fd, str)) {
                 if(find(argv[1], str) == 1) {
                    printf("%s\n", str);
                 }
            }
       }
       //i
       if(iflag == 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag != 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
            fd = open(argv[optind + 1], O_RDONLY);
            while(readline(fd, str)) {
                 if(ifind(argv[optind], str) == 1) {
                    printf("%s\n", str);
                 }
            }
       }
       //v
       if(iflag != 1 && vflag == 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag != 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
            fd = open(argv[optind + 1], O_RDONLY);
            while(readline(fd, str)) {
                 if(find(argv[optind], str) == 0) {
                    puts(str);
                 }
            }
       } 
       //iv
       if(iflag == 1 && vflag == 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag != 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
            fd = open(argv[optind + 1], O_RDONLY);
            while(readline(fd, str)) {
                 if(ifind(argv[optind], str) == 0) {
                    puts(str);
                 }
            }
       } 
       //w
       if(iflag != 1 && vflag != 1 && rflag != 1 && wflag == 1 && cflag != 1 && mflag != 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             char *q;
             q =(char*)malloc(100);
             fd = open(argv[optind + 1], O_RDONLY);
             while(readline(fd, str)) {
                q = wfind(argv[optind], str);
                  if(q != NULL) {
                     puts(str);
                  }
             }
       } 
       //iw
       if(iflag == 1 && vflag != 1 && rflag != 1 && wflag == 1 && cflag != 1 && mflag != 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             char *q;
             q =(char*)malloc(100);
             fd = open(argv[optind + 1], O_RDONLY);
             while(readline(fd, str)) {
                q = wifind(argv[optind], str);
                  if(q != NULL) {
                     puts(str);
                  }
             }
       }
       //ivw
       if(iflag == 1 && vflag == 1 && rflag != 1 && wflag == 1 && cflag != 1 && mflag != 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             char *q;
             q =(char*)malloc(100);
             fd = open(argv[optind + 1], O_RDONLY);
             while(readline(fd, str)) {
                q = wifind(argv[optind], str);
                  if(q == NULL) {
                     puts(str);
                  }
             }
       }
       //vw
       if(iflag != 1 && vflag == 1 && rflag != 1 && wflag == 1 && cflag != 1 && mflag != 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             char *q;
             q =(char*)malloc(100);
             fd = open(argv[optind + 1], O_RDONLY);
             while(readline(fd, str)) {
                q = wfind(argv[optind], str);
                  if(q == NULL) {
                     puts(str);
                  }
             }
       }
       //c
       if(iflag != 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             int count = 0;
             fd = open(argv[optind + 1], O_RDONLY);

             while(readline(fd, str)) {
                 if(find(argv[optind], str) == 1) {
                     count++;
                 }
             }
             printf("%d\n", count);
       }  
       //ic
       if(iflag == 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             int count = 0;
             fd = open(argv[optind + 1], O_RDONLY);
             while(readline(fd, str)) {
                 if(ifind(argv[optind], str) == 1) {
                     count++;
                 }
             }
             printf("%d\n", count);
       }  
       //cv
       if(iflag != 1 && vflag == 1 && rflag != 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             int count = 0;
             fd = open(argv[optind + 1], O_RDONLY);
             while(readline(fd, str)) {
                 if(find(argv[optind], str) == 0) {
                     count++;
                 }
             }
             printf("%d\n", count);
       } 
       //cw
       if(iflag != 1 && vflag != 1 && rflag != 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             char *q;
             int count = 0;
             q =(char*)malloc(100);
             fd = open(argv[optind + 1], O_RDONLY);
             while(readline(fd, str)) {
                q = wfind(argv[optind], str);
                  if(q != NULL) {
                     count++;
                  }
             }
             printf("%d\n", count);
       }
       //ivc
       if(iflag == 1 && vflag == 1 && rflag != 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
            int count = 0;
            fd = open(argv[optind + 1], O_RDONLY);
            while(readline(fd, str)) {
                 if(ifind(argv[optind], str) == 0) {
                      count++;
                 }
            }
            printf("%d\n", count);
       } 
       //vwc
       if(iflag != 1 && vflag == 1 && rflag != 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             char *q;
             int count = 0;
             q =(char*)malloc(100);
             fd = open(argv[optind + 1], O_RDONLY);
             while(readline(fd, str)) {
                q = wfind(argv[optind], str);
                  if(q == NULL) {
                     count++;
                  }
             }
             printf("%d\n", count);
       }
       //iwc
       if(iflag == 1 && vflag != 1 && rflag != 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             char *q;
             int count = 0;
             q =(char*)malloc(100);
             fd = open(argv[optind + 1], O_RDONLY);
             while(readline(fd, str)) {
                q = wifind(argv[optind], str);
                  if(q != NULL) {
                     count++;
                  }
             }
             printf("%d\n", count);
       }
       //civw
       if(iflag == 1 && vflag == 1 && rflag != 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             char *q;
             int count = 0;
             q =(char*)malloc(100);
             fd = open(argv[optind + 1], O_RDONLY);
             while(readline(fd, str)) {
                q = wifind(argv[optind], str);
                  if(q == NULL) {
                     count++;
                  }
             }
             printf("%d\n", count);
       }
       //m
       if(iflag != 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag == 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             int count = 0, i;
             fd = open(argv[optind + 1], O_RDONLY);
             while(readline(fd, str)) {
                  i = find(argv[optind], str);
                  if(i == 1) {
                     if(count < num ) {
                       puts(str);
                       count++;
                     }
                  }
             }
       }
       //vm
       if(iflag != 1 && vflag == 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag == 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             int count = 0, i;
             fd = open(argv[optind + 1], O_RDONLY);
             while(readline(fd, str)) {
                  i = find(argv[optind], str);
                  if(i == 0) {
                     if(count < num ) {
                       puts(str);
                       count++;
                     }
                  }
             }
       }
       //wm
       if(iflag != 1 && vflag != 1 && rflag != 1 && wflag == 1 && cflag != 1 && mflag == 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             int count = 0;
             char *i;
             fd = open(argv[optind + 1], O_RDONLY);
             while(readline(fd, str)) {
                  i = wfind(argv[optind], str);
                  if(i != NULL) {
                     if(count < num ) {
                       puts(str);
                       count++;
                     }
                  }
             }
       }
       //cm
       if(iflag != 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag == 1 && mflag == 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             int count = 0, i;
             fd = open(argv[optind + 1], O_RDONLY);
             while(readline(fd, str)) {
                  i = find(argv[optind], str);
                  if(i == 1) {
                     if(count < num ) {
                        count++;
                     }
                  }
             }
             printf("%d\n", count);
       }
       //ivm
       if(iflag == 1 && vflag == 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag == 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             int count = 0, i;
             fd = open(argv[optind + 1], O_RDONLY);
             while(readline(fd, str)) {
                  i = ifind(argv[optind], str);
                  if(i == 0) {
                     if(count < num ) {
                       puts(str);
                       count++;
                     }
                  }
             }
       }
       //iwm
       if(iflag == 1 && vflag != 1 && rflag != 1 && wflag == 1 && cflag != 1 && mflag == 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             int count = 0;
             char *i;
             fd = open(argv[optind + 1], O_RDONLY);
             while(readline(fd, str)) {
                  i = wifind(argv[optind], str);
                  if(i != NULL) {
                     if(count < num ) {
                       puts(str);
                       count++;
                     }
                  }
             }
       }
       //icm
       if(iflag == 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag == 1 && mflag == 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             int count = 0, i;
             fd = open(argv[optind + 1], O_RDONLY);
             while(readline(fd, str)) {
                  i = ifind(argv[optind], str);
                  if(i == 1) {
                     if(count < num) {
                        count++;
                     }
                  }
             }
             printf("%d\n", count);
       }
       //vwm
       if(iflag != 1 && vflag == 1 && rflag != 1 && wflag == 1 && cflag != 1 && mflag == 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             int count = 0;
             char *i;
             fd = open(argv[optind + 1], O_RDONLY);
             while(readline(fd, str)) {
                  i = wfind(argv[optind], str);
                  if(i == NULL) {
                     if(count < num ) {
                        puts(str);
                        count++;
                     }
                  }
             }
       }
       //vcm
       if(iflag != 1 && vflag == 1 && rflag != 1 && wflag != 1 && cflag == 1 && mflag == 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             int count = 0, i;
             fd = open(argv[optind + 1], O_RDONLY);
             while(readline(fd, str)) {
                  i = find(argv[optind], str);
                  if(i == 0) {
                     if(count < num ) {
                        count++;
                     }
                  }
             }
             printf("%d\n", count);
       }
       //wcm
       if(iflag != 1 && vflag != 1 && rflag != 1 && wflag == 1 && cflag == 1 && mflag == 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             int count = 0;
             char *i;
             fd = open(argv[optind + 1], O_RDONLY);
             while(readline(fd, str)) {
                  i = wfind(argv[optind], str);
                  if(i != NULL) {
                     if(count < num ) {
                         count++;
                     }
                  }
             }
             printf("%d\n", count);
       }
       //ivwm
       if(iflag == 1 && vflag == 1 && rflag != 1 && wflag == 1 && cflag != 1 && mflag == 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             int count = 0, i;
             fd = open(argv[optind + 1], O_RDONLY);
             while(readline(fd, str)) {
                  i = ifind(argv[optind], str);
                  if(i == 0) {
                     if(count < num ) {
                        count++;
                     }
                  }
             }
             printf("%d\n", count);
       }
       //ivcm
       if(iflag == 1 && vflag == 1 && rflag != 1 && wflag != 1 && cflag == 1 && mflag == 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             int count = 0, i;
             fd = open(argv[optind + 1], O_RDONLY);
             while(readline(fd, str)) {
                  i = ifind(argv[optind], str);
                  if(i == 0) {
                     if(count < num ) {
                        count++;
                     }
                  }
             }
             printf("%d\n", count);
       }
       //vwcm
       if(iflag != 1 && vflag == 1 && rflag != 1 && wflag == 1 && cflag == 1 && mflag == 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             int count = 0;
             char *i;
             fd = open(argv[optind + 1], O_RDONLY);
             while(readline(fd, str)) {
                  i = wfind(argv[optind], str);
                  if(i == NULL) {
                     if(count < num ) {
                         count++;
                     }
                  }
             }
             printf("%d\n", count);
       }
       //ivwcm
       if(iflag == 1 && vflag == 1 && rflag != 1 && wflag == 1 && cflag == 1 && mflag == 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             int count = 0;
             char *i;
             fd = open(argv[optind + 1], O_RDONLY);
             while(readline(fd, str)) {
                  i = wifind(argv[optind], str);
                  if(i == NULL) {
                     if(count < num ) {
                         count++;
                     }
                  }
             }
             printf("%d\n", count);
       }
       //q
       if(qflag == 1 && (vflag == 1 || vflag != 1 || rflag == 1 || rflag != 1 ||  wflag == 1 ||  wflag != 1 || cflag == 1 || cflag != 1|| mflag == 1 || mflag != 1 || bflag ==1 || bflag !=1 ||  iflag   == 1 || iflag != 1  || Hflag == 1  || Hflag != 1 || hflag == 1 ||  hflag != 1 || fflag == 1  || fflag != 1 || eflag == 1 || eflag != 1)) {
             exit(1);
       }
       //h or H
       if(iflag != 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag != 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
             int n = optind + 1, i;
             while(1) {
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = find(argv[optind], str);
                     if(i == 1) {
                         if(hflag == 1) {
                             printf("%s\n", str);
                         }
                         else
                             printf("%s:%s\n", argv[n], str);
                     }
                 }
                 n++;
             }
        }
        //ih or Hi
        if(iflag == 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag != 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
             int n = optind + 1, i;
             while(1) {
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = ifind(argv[optind], str);
                     if(i == 1) {
                         if(hflag == 1) {
                             printf("%s\n", str);
                         }
                         else
                             printf("%s%s%s:%s\n", MAGENTA, argv[n], RESET, str);
                     }
                 }
                 n++;
             }
        }
        //hv or Hv
        if(iflag != 1 && vflag == 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag != 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
             int n = optind + 1, i;
             while(1) {
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = find(argv[optind], str);
                     if(i == 0) {
                         if(hflag == 1) {
                             printf("%s\n", str);
                         }
                         else
                             printf("%s:%s\n", argv[n], str);
                     }
                 }
                 n++;
             }
        }
        //hw or Hw
        if(iflag != 1 && vflag != 1 && rflag != 1 && wflag == 1 && cflag != 1 && mflag != 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
             int n = optind + 1;
             char *i;
             while(1) {
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = wfind(argv[optind], str);
                     if(i != NULL) {
                         if(hflag == 1) {
                             printf("%s\n", str);
                         }
                         else
                             printf("%s:%s\n", argv[n], str);
                     }
                 }
                 n++;
             }
        }
        //hc or Hc
        if(iflag != 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
             int n = optind + 1, count, i;
             while(1) {
                 count = 0;
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = find(argv[optind], str);
                     if(i == 1) {
                         count++;
                     }
                 }
                 printf("%s:%d\n", argv[n], count);
                 n++;
             }
        }
        //hm or Hm
        if(iflag != 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag == 1 && bflag !=1 && qflag != 1  && (Hflag == 1  || hflag == 1) && fflag != 1  && eflag != 1) {
             int n = optind + 1, count, i;
             while(1) {
                 count = 0;
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = find(argv[optind], str);
                     if(i == 1) {
                         if(count < num) {
                              if(hflag == 1) {
                                 printf("%s\n", str);
                              }
                              else
                                 printf("%s:%s\n", argv[n], str);
                         }
                         count++;
                     }
                 }
                 n++;
             }
        }
        //ivh or ivH
        if(iflag == 1 && vflag == 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag != 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
             int n = optind + 1, i;
             while(1) {
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = ifind(argv[optind], str);
                     if(i == 0) {
                         if(hflag == 1) {
                              printf("%s\n", str);
                         }
                         else
                              printf("%s:%s\n", argv[n], str);
                     }
                 }
                 n++;
             }
        }
        //iwh or iwH
        if(iflag == 1 && vflag != 1 && rflag != 1 && wflag == 1 && cflag != 1 && mflag != 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
             int n = optind + 1;
             char *i;
             while(1) {
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = wifind(argv[optind], str);
                     if(i != NULL) {
                         if(hflag == 1) {
                              printf("%s\n", str);
                         }
                         else
                              printf("%s:%s\n", argv[n], str);
                     }
                 }
                 n++;
             }
        }
        //ich
        if(iflag == 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
             int n = optind + 1, count, i;
             while(1) {
                 count = 0;
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = ifind(argv[optind], str);
                     if(i == 1) {
                         count++;
                     }
                 }
                 if(hflag == 1) {
                     printf("%d\n", count);
                 }
                 else
                     printf("%s:%d\n", argv[n], count);
                 n++;
             }
        }
        //imh
        if(iflag == 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag == 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
             int n = optind + 1, count, i;
             while(1) {
                 count = 0;
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = ifind(argv[optind], str);
                     if(i == 1) {
                         if(count < num) {
                             if(hflag == 1) {
                                printf("%s\n", str);
                             }
                             else
                                printf("%s:%s\n", argv[n], str);
                             count++;
                         }
                     }
                 }
                 n++;
             }
        }
        //vwh
        if(iflag != 1 && vflag == 1 && rflag != 1 && wflag == 1 && cflag != 1 && mflag != 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
             int n = optind + 1;
             char *i;
             while(1) {
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = wfind(argv[optind], str);
                     if(i == NULL) {
                          if(hflag == 1) {
                             printf("%s\n", str);
                          }
                          else
                             printf("%s:%s\n", argv[n], str);
                     }
                 }
                 n++;
             }
        }
        //vch
        if(iflag != 1 && vflag == 1 && rflag != 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
             int n = optind + 1, count, i;
             while(1) {
                 count = 0;
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = find(argv[optind], str);
                     if(i == 0) {
                         count++;
                     }
                 }
                 if(hflag == 1) {
                     printf("%d\n", count);
                 }
                 else
                     printf("%s:%d\n", argv[n],count);
                 n++;
             }
        }
        //vmh
        if(iflag != 1 && vflag == 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag == 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
             int n = optind + 1, count, i;
             while(1) {
                 count = 0;
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = find(argv[optind], str);
                     if(i == 0) {
                         if(count < num) {
                             if(hflag == 1) {
                                printf("%s\n", str);
                             }
                             else
                                printf("%s:%s\n", argv[n], str);
                             count++;
                         }
                     }
                 }
                 n++;
             }
        }
        //wch
        if(iflag != 1 && vflag != 1 && rflag != 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)  && fflag != 1  && eflag != 1) {
             int n = optind + 1, count;
             char *i;
             while(1) {
                 count = 0;
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = wfind(argv[optind], str);
                     if(i != NULL) {
                         count++;
                     }
                 }
                 if(hflag == 1) {
                     printf("%d\n", count);
                 }
                 else
                     printf("%s:%d\n", argv[n], count);
                 n++;
             }
        }
        //wmh
        if(iflag != 1 && vflag != 1 && rflag != 1 && wflag == 1 && cflag != 1 && mflag == 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)   && fflag != 1  && eflag != 1) {
             int n = optind + 1, count;
             char *i;
             while(1) {
                 count = 0;
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = wfind(argv[optind], str);
                     if(i != NULL) {
                         if(count < num) {
                             if(hflag == 1) {
                                printf("%s\n", str);
                             }
                             else
                                printf("%s:%s\n", argv[n], str);
                             count++;
                         }
                     }
                 }
                 n++;
             }
        }
        //cmh
        if(iflag != 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag == 1 && mflag == 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)   && fflag != 1  && eflag != 1) {
             int n = optind + 1, count, i;
             while(1) {
                 count = 0;
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = find(argv[optind], str);
                     if(i == 1) {
                         if(count < num) {
                             count++;
                         }
                     }
                 }
                 if(hflag == 1) {
                     printf("%d\n", count);
                 }
                 else
                     printf("%s:%d\n", argv[n], count);
                 n++;
                 
             }
        }
        //ivwh
        if(iflag == 1 && vflag == 1 && rflag != 1 && wflag == 1 && cflag != 1 && mflag != 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)   && fflag != 1  && eflag != 1) {
             int n = optind + 1;
             char *i;
             while(1) {
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = wifind(argv[optind], str);
                     if(i == NULL) {
                          if(hflag == 1) {
                               printf("%s\n", str);
                          }
                          else
                               printf("%s:%s\n", argv[n], str);
                     }
                 }
                 n++;
             }
        }
        //ivch
        if(iflag == 1 && vflag == 1 && rflag != 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)   && fflag != 1  && eflag != 1) {
             int n = optind + 1, count, i;
             while(1) {
                 count = 0;
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = ifind(argv[optind], str);
                     if(i == 0) {
                         count++;
                     }
                 }
                 if(hflag == 1) {
                     printf("%d\n", count);
                 }
                 else
                     printf("%s:%d\n", argv[n], count);
                 n++;
            }
        }
        //ivmh
        if(iflag == 1 && vflag == 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag == 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)   && fflag != 1  && eflag != 1) {
             int n = optind + 1, count, i;
             while(1) {
                 count = 0;
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = ifind(argv[optind], str);
                     if(i == 0) {
                         if(count < num) {
                             if(hflag == 1) {
                                printf("%s\n", str);
                             }
                             else
                                printf("%s:%s\n", argv[n], str);
                             count++;
                         }
                     }
                 }
                 n++;
             }
        }
        //icmh
        if(iflag == 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag == 1 && mflag == 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)   && fflag != 1  && eflag != 1) {
             int n = optind + 1, count, i;
             while(1) {
                 count = 0;
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = ifind(argv[optind], str);
                     if(i == 1) {
                         if(count < num) {
                             count++;
                         }
                     }
                 }
                 if(hflag == 1) {
                     printf("%d\n", count);
                 }
                 else
                     printf("%s:%d\n", argv[n], count);
                 n++;
                 
             }
        }
        //icwh
        if(iflag == 1 && vflag != 1 && rflag != 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)   && fflag != 1  && eflag != 1) {
             int n = optind + 1, count;
             char *i;
             while(1) {
                 count = 0;
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = wifind(argv[optind], str);
                     if(i != NULL) {
                         count++;
                     }
                 }
                 if(hflag == 1) {
                     printf("%d\n", count);
                 }
                 else
                     printf("%s:%d\n", argv[n], count);
                 n++;
             }
        }
        //vcwh
        if(iflag != 1 && vflag == 1 && rflag != 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)   && fflag != 1  && eflag != 1) {
             int n = optind + 1, count;
             char *i;
             while(1) {
                 count = 0;
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = wfind(argv[optind], str);
                     if(i == NULL) {
                         count++;
                     }
                 }
                 if(hflag == 1) {
                     printf("%d\n", count);
                 }
                 else
                     printf("%s:%d\n", argv[n], count);
                 n++;
             }
        }
        //vwmh
        if(iflag != 1 && vflag == 1 && rflag != 1 && wflag == 1 && cflag != 1 && mflag == 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)   && fflag != 1  && eflag != 1) {
             int n = optind + 1, count;
             char *i;
             while(1) {
                 count = 0;
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = wfind(argv[optind], str);
                     if(i == NULL) {
                         if(count < num) {
                             if(hflag == 1) {
                                printf("%s\n", str);
                             }
                             else
                                printf("%s:%s\n", argv[n], str);
                             count++;
                         }
                     }
                 }
                 n++;
             }
        }
        //vcmh
        if(iflag != 1 && vflag == 1 && rflag != 1 && wflag != 1 && cflag == 1 && mflag == 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)   && fflag != 1  && eflag != 1) {
             int n = optind + 1, count, i;
             while(1) {
                 count = 0;
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = find(argv[optind], str);
                     if(i == 0) {
                         if(count < num) {
                             count++;
                         }
                     }
                 }
                 if(hflag == 1) {
                     printf("%d\n", count);
                 }
                 else
                     printf("%s:%d\n", argv[n], count);
                 n++;
             }
        }
        //iwhm
        if(iflag == 1 && vflag != 1 && rflag != 1 && wflag == 1 && cflag != 1 && mflag == 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)   && fflag != 1  && eflag != 1) {
             int n = optind + 1, count;
             char *i;
             while(1) {
                 count = 0;
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = wifind(argv[optind], str);
                     if(i != NULL) {
                         if(count < num) {
                             if(hflag == 1) {
                                printf("%s\n", str);
                             }
                             else
                                printf("%s:%s\n", argv[n], str);
                             count++;
                         }
                     }
                 }
                 n++;
             }
        }
        //wchm
        if(iflag != 1 && vflag != 1 && rflag != 1 && wflag == 1 && cflag == 1 && mflag == 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)   && fflag != 1  && eflag != 1) {
             int n = optind + 1, count;
             char *i;
             while(1) {
                 count = 0;
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = wfind(argv[optind], str);
                     if(i != NULL) {
                         if(count < num) {
                             count++;
                         }
                     }
                 }
                 if(hflag == 1) {
                     printf("%d\n", count);
                 }
                 else
                     printf("%s:%d\n", argv[n], count);
                 n++;
             }
        }
        //ivwch
        if(iflag == 1 && vflag == 1 && rflag != 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)   && fflag != 1  && eflag != 1) {
             int n = optind + 1, count;
             char *i;
             while(1) {
                 count = 0;
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = wifind(argv[optind], str);
                     if(i == NULL) {
                         count++;
                     }
                 }
                 if(hflag == 1) {
                     printf("%d\n", count);
                 }
                 else
                     printf("%s:%d\n", argv[n], count);
                 n++;
             }
        }
        //iwchm
        if(iflag == 1 && vflag != 1 && rflag != 1 && wflag == 1 && cflag == 1 && mflag == 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)   && fflag != 1  && eflag != 1) {
             int n = optind + 1, count;
             char *i;
             while(1) {
                 count = 0;
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = wifind(argv[optind], str);
                     if(i != NULL) {
                         if(count < num) {
                             count++;
                         }
                     }
                 }
                 if(hflag == 1) {
                     printf("%d\n", count);
                 }
                 else
                     printf("%s:%d\n", argv[n], count);
                 n++;
             }
        }
        //iwvmh
        if(iflag == 1 && vflag == 1 && rflag != 1 && wflag == 1 && cflag != 1 && mflag == 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)   && fflag != 1  && eflag != 1) {
             int n = optind + 1, count;
             char *i;
             while(1) {
                 count = 0;
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = wifind(argv[optind], str);
                     if(i == NULL) {
                         if(count < num) {
                             if(hflag == 1) {
                                printf("%s\n", str);
                             }
                             else
                                printf("%s:%s\n", argv[n], str);
                             count++;
                         }
                     }
                 }
                 n++;
             }
        }
        //ivcmh
        if(iflag == 1 && vflag == 1 && rflag != 1 && wflag != 1 && cflag == 1 && mflag == 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)   && fflag != 1  && eflag != 1) {
             int n = optind + 1, count, i;
             while(1) {
                 count = 0;
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = ifind(argv[optind], str);
                     if(i == 0) {
                         if(count < num) {
                             count++;
                         }
                     }
                 }
                 if(hflag == 1) {
                     printf("%d\n", count);
                 }
                 else
                     printf("%s:%d\n", argv[n], count);
                 n++;
             }
        }
        //vwchm
        if(iflag != 1 && vflag == 1 && rflag != 1 && wflag == 1 && cflag == 1 && mflag == 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)   && fflag != 1  && eflag != 1) {
             int n = optind + 1, count;
             char *i;
             while(1) {
                 count = 0;
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = wfind(argv[optind], str);
                     if(i == NULL) {
                         if(count < num) {
                             count++;
                         }
                     }
                 }
                 if(hflag == 1) {
                     printf("%d\n", count);
                 }
                 else
                     printf("%s:%d\n", argv[n], count);
                 n++;
             }
        }
        //ivwcmh or ivwcmHq
        if(iflag == 1 && vflag == 1 && rflag != 1 && wflag == 1 && cflag == 1 && mflag == 1 && bflag !=1 && qflag != 1  && (Hflag == 1 || hflag == 1)   && fflag != 1  && eflag != 1) {
             int n = optind + 1, count;
             char *i;
             while(1) {
                 count = 0;
	         fd = open(argv[n], O_RDONLY);
                 if(fd == -1) {
                     break;
                 }
                 while(readline(fd, str)) {
                     i = wifind(argv[optind], str);
                     if(i == NULL) {
                         if(count < num) {
                             count++;
                         }
                     }
                 }
                 if(hflag == 1) {
                     printf("%d\n", count);
                 }
                 else
                     printf("%s:%d\n", argv[n], count);
                 n++;
             }
        }
        //r
        if(iflag != 1 && vflag != 1 && rflag == 1 && wflag != 1 && cflag != 1 && mflag != 1 && bflag !=1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             char *path, *word;
             path = (char*)malloc(500);
             word = (char*)malloc(500);
             strcpy(word, argv[optind]);
             strcpy(path, argv[optind + 1]);
             listFilesRecursively(path, word);
        }
        //r and combinations
        if((iflag == 1 || vflag == 1 || wflag == 1 || cflag == 1 || mflag == 1 || bflag == 1 || qflag == 1 || Hflag == 1 || hflag == 1 || fflag == 1 || eflag == 1) && rflag == 1) {
             char *path, *word;
             path = (char*)malloc(500);
             word = (char*)malloc(500);
             strcpy(word, argv[optind]);
             strcpy(path, argv[optind + 1]);
             listFilesRecursively1(path, word, iflag, vflag, wflag, cflag, mflag, bflag, qflag, Hflag, hflag, fflag, eflag, num);
        }
        //b
        if(bflag == 1 && iflag != 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             char str[1000];
	     FILE *fp;
	     char ch, a[1000];
	     int count = 0, i = 0, bb;
	     fp = fopen(argv[optind + 1],"r");
	     while(!feof(fp)) {
		  ch = fgetc(fp);
		  if(ch != '\n') {
			a[i] = ch;
			i++;
			count++;
	          }
	          else {
		        a[i] = '\0';
		        count++;
		        if(strstr(a, argv[optind])) {
                             bb = count - strlen(a) - 1;
			     printf("%d : %s\n", bb, a);
                        }
		        i = 0;
	          }
	     }
         }
         //b
         if(bflag == 1 && (iflag == 1 || vflag == 1 || rflag == 1 || wflag == 1 || cflag == 1 || mflag == 1 || qflag == 1 || Hflag == 1 ||  hflag == 1 ||  fflag == 1  || eflag == 1)) {
             char str[1000];
	     FILE *fp;
	     char ch, a[1000];
	     int count = 0, i = 0, bb, count1 = -1;
	     fp = fopen(argv[optind + 1],"r");
	     while(!feof(fp)) {
		  ch = fgetc(fp);
		  if(ch != '\n') {
			a[i] = ch;
			i++;
			count++;
	          }
	          else {
		        a[i] = '\0';
		        count++;
                        if(iflag == 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
		            if(strcasestr(a, argv[optind])) {
                                bb = count - strlen(a) - 1;
			        printf("%d:%s\n", bb, a);
                            }
		            i = 0;
                        }
                        if(iflag != 1 && vflag == 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
		            if(strstr(a, argv[optind]) == NULL) {
                                bb = count - strlen(a) - 1;
			        printf("%d:%s\n", bb, a);
                            }
		            i = 0;
                        }
                        if(iflag != 1 && vflag != 1 && rflag != 1 && wflag == 1 && cflag != 1 && mflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
		            if(wfind(argv[optind], a) != NULL) {
                                bb = count - strlen(a) - 1;
			        printf("%d:%s\n", bb, a);
                            }
		            i = 0;
                        }
                        if(iflag != 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag == 1 && mflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
		            if(strstr(a, argv[optind]) == NULL) {
                                bb = count - strlen(a) - 1;
			        //printf("%d:%s\n", bb, a);
                                count1++;
                            }
		            i = 0;
                        }
	          }
	     }
             
         }
         //pattern
      /*   if(iflag != 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1  && Hflag != 1  && hflag != 1  && fflag != 1  && eflag != 1) {
             char *word, *word1, *str, *p1, *p2, *p3, *add, *word2;
             char string[] = "^", string1[] = "$", string2[] = ".";
             int i, j, length, n = 2, count = 0, k, length1, molen, mm, mm1, mmcount, mm1count;
             word = (char*)malloc(1000);
             str = (char*)malloc(1000);
             word1 = (char*)malloc(1000);
             word2 = (char*)malloc(1000);
             strcpy(word, argv[1]);
             length = strlen(word);
             strncpy(word1, word + 1, length - 1);
             strncpy(word2, word, length - 1);
             
            // printf("1\n");
             p1 = strstr(word, string);
             p2 = strstr(word, string1);
             p3 = strstr(word, string2);
             if(p1 != NULL && p2 == NULL && p3 == NULL) {
                while(1) {
	            fd = open(argv[n], O_RDONLY);
                    if(fd == -1) {
                       break;
                    }
                    while(readline(fd, str)) {
                        i = find(word1, str);
                        if(i == 1) {
                             if(strncmp(word1, str, length - 1) == 0) {
                                 if(hflag == 1) {
                                     puts(str);
                                 }
                                 else
                                     printf("%s:%s\n", argv[n], str);
                             }
                        }
                    }
                    n++;
                }
            } 
            if(p1 == NULL && p2 != NULL && p3 == NULL) {
                while(1) {
	            fd = open(argv[n], O_RDONLY);
                    if(fd == -1) {
                       break;
                    }
                    while(readline(fd, str)) {
                        i = find(word2, str);
                        if(i == 1) {
                             length1 = strlen(str);
                             add = strstr(str, word2);
                             if(add = &(str[length1 - length - 1])) {
                                  if(argv[3] == NULL) {
                                       puts(str);
                                  }
                                  else
                                       printf("%s:%s\n", argv[n], str);
                             }
                                  
                        }
                    }
                    n++;
                }
            }  
         }    */   
         /*   if(p1 == NULL && p2 == NULL && p3 != NULL) {
                while(1) {
	            fd = open(argv[n], O_RDONLY);
                    if(fd == -1) {
                       break;
                    }
                    while(readline(fd, str)) {
                        i = find(word1, str);
                        molen = strlen(str);
                        if(i == 1) {
                             for(mm = 0; mm < molen; ) {
                                    mm1 = 0;
                                    mmcount = 0;
                                    while(str[mm] == word1[mm1]) {
                                         mmcount++;
                                         mm++;
                                         mm1++;
                                    }
                                    if(mmcount == length - 1) {
                                         mm1count++;
                                         mmcount = 0;
                                    }
                                    else
                                         mm++;
                             }
                             if(mm1count == 1) {
                                    if(strncmp(word1, str, length - 1) == 0) {
                                    
                                         puts(str);
                                    
                                    }
                             }
                             if(mm1count > 1) {
                                    puts(str);
                             }
                                    
                        }
                    }
                    n++;
                }
            } 
         }  */
         //f
         if(iflag != 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1 && Hflag != 1 && hflag != 1  && fflag == 1 && eflag != 1){
                int fd, fd1, n = optind + 1, i;
                char *str1, *str2;
                str1 = (char*)malloc(1000);  
                str2 = (char*)malloc(1000);   
                while(1) {            
                     fd = open(argv[n], O_RDONLY);
                     if(fd == -1) {
                           break;
                     }
                     while(readline(fd, str2)) {
                           fd1 = open(argv[optind], O_RDONLY);
                           while(readline1(fd1, str1)) {
                                 if(find(str1, str2) == 1) {
                                      if(argv[optind + 2] == NULL) {
                                            puts(str2);
                                      }
                                      else
                                            printf("%s:%s\n", argv[n], str2);
                                      break;
                                 }
                           }
                           close(fd1);
                     }
                     close(fd);
                     n++;
                }
          }
          //if
          if(iflag == 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1 && Hflag != 1 && hflag != 1  && fflag == 1 && eflag!= 1) {
                int fd, fd1, n = optind + 1, i;
                char *str1, *str2;
                str1 = (char*)malloc(1000);  
                str2 = (char*)malloc(1000);   
                while(1) {            
                     fd = open(argv[n], O_RDONLY);
                     if(fd == -1) {
                           break;
                     }
                     while(readline(fd, str2)) {
                           fd1 = open(argv[optind], O_RDONLY);
                           while(readline1(fd1, str1)) {
                                 if(ifind(str1, str2) == 1) {
                                      if(argv[optind + 2] == NULL) {
                                            puts(str2);
                                      }
                                      else
                                            printf("%s:%s\n", argv[n], str2);
                                      break;
                                 }
                           }
                           close(fd1);
                     }
                     close(fd);
                     n++;
                }
          }
          //vf
        /*  if(iflag != 1 && vflag == 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1 && Hflag != 1 && hflag != 1  && fflag == 1 && eflag!= 1) {
                int fd, fd1, n = optind + 1, i;
                char *str1, *str2;
                str1 = (char*)malloc(1000);  
                str2 = (char*)malloc(1000);   
                while(1) {            
                     fd = open(argv[n], O_RDONLY);
                     if(fd == -1) {
                           break;
                     }
                     while(readline(fd, str2)) {
                           fd1 = open(argv[optind], O_RDONLY);
                           while(readline1(fd1, str1)) {
                                 if(find(str1, str2) == 0) {
                                      if(argv[optind + 2] == NULL) {
                                            puts(str2);
                                      }
                                      else
                                            printf("%s:%s\n", argv[n], str2);
                                      break;
                                 }
                           }
                           close(fd1);
                     }
                     close(fd);
                     n++;
                }
          }*/
          //wf
          if(iflag != 1 && vflag != 1 && rflag != 1 && wflag == 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1 && Hflag != 1 && hflag != 1  && fflag == 1 && eflag != 1){
                int fd, fd1, n = optind + 1, i;
                char *str1, *str2;
                str1 = (char*)malloc(1000);  
                str2 = (char*)malloc(1000);   
                while(1) {            
                     fd = open(argv[n], O_RDONLY);
                     if(fd == -1) {
                           break;
                     }
                     while(readline(fd, str2)) {
                           fd1 = open(argv[optind], O_RDONLY);
                           while(readline1(fd1, str1)) {
                                 if(wfind(str1, str2) != NULL) {
                                      if(argv[optind + 2] == NULL) {
                                            puts(str2);
                                      }
                                      else
                                            printf("%s:%s\n", argv[n], str2);
                                      break;
                                 }
                           }
                           close(fd1);
                     }
                     close(fd);
                     n++;
                }
          }
          //cf
          if(iflag != 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1 && Hflag != 1 && hflag != 1  && fflag == 1 && eflag != 1){
                int fd, fd1, n = optind + 1, i, ct = 0;
                char *str1, *str2;
                str1 = (char*)malloc(1000);  
                str2 = (char*)malloc(1000);   
                while(1) {            
                     fd = open(argv[n], O_RDONLY);
                     if(fd == -1) {
                           break;
                     }
                     while(readline(fd, str2)) {
                           fd1 = open(argv[optind], O_RDONLY);
                           while(readline1(fd1, str1)) {
                                 if(find(str1, str2) == 1) {
                                      /*if(argv[optind + 2] == NULL) {
                                            puts(str2);
                                      }
                                      else*/
                                            //printf("%s:%s\n", argv[n], str2);
                                      ct++;
                                      break;
                                 }
                           }
                           close(fd1);
                           
                     }
                     printf("%s:%d\n", argv[n], ct); 
                     close(fd);
                     n++;
                     ct = 0;
                }
          }
          /*
          if(iflag != 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag == 1 && bflag != 1 && qflag != 1 && Hflag != 1 && hflag != 1  && fflag == 1 && eflag != 1){
                int fd, fd1, n = optind + 1, i, count = 0;
                char *str1, *str2;
                str1 = (char*)malloc(1000);  
                str2 = (char*)malloc(1000);   
                while(1) {            
                     fd = open(argv[n], O_RDONLY);
                     if(fd == -1) {
                           break;
                     }
                     while(readline(fd, str2)) {
                           fd1 = open(argv[optind], O_RDONLY);
                           while(readline1(fd1, str1)) {
                                 if(find(str1, str2) == 1) {
                                      if(argv[optind + 2] == NULL) {
                                            if(count < num) {
                                               puts(str2);
                                            }
                                            count++;
                                      }
                                      else {
                                            if(count < num) {
                                               printf("%s:%s\n", argv[n], str2); 
                                            }
                                            count++;
                                      }
                                      break;
                                 }
                           }
                           close(fd1);
                     }
                     close(fd);
                     n++;
                     count = 0;
                }
          }*/
          //fh or H
          if(iflag != 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1 && (Hflag == 1 || hflag == 1)  && fflag == 1 && eflag != 1){
                int fd, fd1, n = optind + 1, i;
                char *str1, *str2;
                str1 = (char*)malloc(1000);  
                str2 = (char*)malloc(1000);   
                while(1) {            
                     fd = open(argv[n], O_RDONLY);
                     if(fd == -1) {
                           break;
                     }
                     while(readline(fd, str2)) {
                           fd1 = open(argv[optind], O_RDONLY);
                           while(readline1(fd1, str1)) {
                                 if(find(str1, str2) == 1) {
                                      if(argv[optind + 2] == NULL) {
                                            puts(str2);
                                      }
                                      else
                                            if(Hflag == 1) {
                                                printf("%s:%s\n", argv[n], str2);
                                            }
                                            else
                                                puts(str2);
                                      break;
                                 }
                           }
                           close(fd1);
                     }
                     close(fd);
                     n++;
                }
          }
          //fiw
          if(iflag == 1 && vflag != 1 && rflag != 1 && wflag == 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1 && Hflag != 1 && hflag != 1  && fflag == 1 && eflag != 1){
                int fd, fd1, n = optind + 1, i;
                char *str1, *str2;
                str1 = (char*)malloc(1000);  
                str2 = (char*)malloc(1000);   
                while(1) {            
                     fd = open(argv[n], O_RDONLY);
                     if(fd == -1) {
                           break;
                     }
                     while(readline(fd, str2)) {
                           fd1 = open(argv[optind], O_RDONLY);
                           while(readline1(fd1, str1)) {
                                 if(wifind(str1, str2) != NULL) {
                                      if(argv[optind + 2] == NULL) {
                                            puts(str2);
                                      }
                                      else
                                            printf("%s:%s\n", argv[n], str2);
                                      break;
                                 }
                           }
                           close(fd1);
                     }
                     close(fd);
                     n++;
                }
          }
          //cif
          if(iflag == 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1 && Hflag != 1 && hflag != 1  && fflag == 1 && eflag != 1){
                int fd, fd1, n = optind + 1, i, ct = 0;
                char *str1, *str2;
                str1 = (char*)malloc(1000);  
                str2 = (char*)malloc(1000);   
                while(1) {            
                     fd = open(argv[n], O_RDONLY);
                     if(fd == -1) {
                           break;
                     }
                     while(readline(fd, str2)) {
                           fd1 = open(argv[optind], O_RDONLY);
                           while(readline1(fd1, str1)) {
                                 if(ifind(str1, str2) == 1) {
                                      /*if(argv[optind + 2] == NULL) {
                                            puts(str2);
                                      }
                                      else*/
                                            //printf("%s:%s\n", argv[n], str2);
                                      ct++;
                                      break;
                                 }
                           }
                           close(fd1);
                           
                     }
                     printf("%s:%d\n", argv[n], ct); 
                     close(fd);
                     n++;
                     ct = 0;
                }
          }
          //fih or H
          if(iflag == 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1 && (Hflag == 1 || hflag == 1)  && fflag == 1 && eflag != 1){
                int fd, fd1, n = optind + 1, i;
                char *str1, *str2;
                str1 = (char*)malloc(1000);  
                str2 = (char*)malloc(1000);   
                while(1) {            
                     fd = open(argv[n], O_RDONLY);
                     if(fd == -1) {
                           break;
                     }
                     while(readline(fd, str2)) {
                           fd1 = open(argv[optind], O_RDONLY);
                           while(readline1(fd1, str1)) {
                                 if(ifind(str1, str2) == 1) {
                                      if(argv[optind + 2] == NULL) {
                                            puts(str2);
                                      }
                                      else
                                            if(Hflag == 1) {
                                                printf("%s:%s\n", argv[n], str2);
                                            }
                                            else
                                                puts(str2);
                                      break;
                                 }
                           }
                           close(fd1);
                     }
                     close(fd);
                     n++;
                }
          }
          //fwc
          if(iflag != 1 && vflag != 1 && rflag != 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1 && Hflag != 1 && hflag != 1  && fflag == 1 && eflag != 1){
                int fd, fd1, n = optind + 1, i, ct = 0;
                char *str1, *str2;
                str1 = (char*)malloc(1000);  
                str2 = (char*)malloc(1000);   
                while(1) {            
                     fd = open(argv[n], O_RDONLY);
                     if(fd == -1) {
                           break;
                     }
                     while(readline(fd, str2)) {
                           fd1 = open(argv[optind], O_RDONLY);
                           while(readline1(fd1, str1)) {
                                 if(wfind(str1, str2) != NULL) {
                                      /*if(argv[optind + 2] == NULL) {
                                            puts(str2);
                                      }
                                      else*/
                                            //printf("%s:%s\n", argv[n], str2);
                                      ct++;
                                      break;
                                 }
                           }
                           close(fd1);
                           
                     }
                     printf("%s:%d\n", argv[n], ct); 
                     close(fd);
                     n++;
                     ct = 0;
                }
          }
          //fch
          if(iflag != 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1 && (Hflag == 1 || hflag == 1)  && fflag == 1 && eflag != 1){
                int fd, fd1, n = optind + 1, i, ct = 0;
                char *str1, *str2;
                str1 = (char*)malloc(1000);  
                str2 = (char*)malloc(1000);   
                while(1) {            
                     fd = open(argv[n], O_RDONLY);
                     if(fd == -1) {
                           break;
                     }
                     while(readline(fd, str2)) {
                           fd1 = open(argv[optind], O_RDONLY);
                           while(readline1(fd1, str1)) {
                                 if(find(str1, str2) == 1) {
                                      /*if(argv[optind + 2] == NULL) {
                                            puts(str2);
                                      }
                                      else*/
                                            //printf("%s:%s\n", argv[n], str2);
                                      ct++;
                                      break;
                                 }
                           }
                           close(fd1);
                           
                     }
                     if(Hflag == 1) {
                           printf("%s:%d\n", argv[n], ct);
                     }
                     else
                           printf("%d\n", ct); 
                     close(fd);
                     n++;
                     ct = 0;
                }
          }
          //fwh or fwH
          if(iflag != 1 && vflag != 1 && rflag != 1 && wflag == 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1 && (Hflag == 1 || hflag == 1)  && fflag == 1 && eflag != 1){
                int fd, fd1, n = optind + 1, i;
                char *str1, *str2;
                str1 = (char*)malloc(1000);  
                str2 = (char*)malloc(1000);   
                while(1) {            
                     fd = open(argv[n], O_RDONLY);
                     if(fd == -1) {
                           break;
                     }
                     while(readline(fd, str2)) {
                           fd1 = open(argv[optind], O_RDONLY);
                           while(readline1(fd1, str1)) {
                                 if(wfind(str1, str2) != NULL) {
                                      if(argv[optind + 2] == NULL) {
                                            puts(str2);
                                      }
                                      else
                                            if(Hflag == 1) {
                                                printf("%s:%s\n", argv[n], str2);
                                            }
                                            else
                                                puts(str2);
                                      break;
                                 }
                           }
                           close(fd1);
                     }
                     close(fd);
                     n++;
                }
          }
          //fiwc
          if(iflag == 1 && vflag != 1 && rflag != 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1 && Hflag != 1 && hflag != 1  && fflag == 1 && eflag != 1){
                int fd, fd1, n = optind + 1, i, ct = 0;
                char *str1, *str2;
                str1 = (char*)malloc(1000);  
                str2 = (char*)malloc(1000);   
                while(1) {            
                     fd = open(argv[n], O_RDONLY);
                     if(fd == -1) {
                           break;
                     }
                     while(readline(fd, str2)) {
                           fd1 = open(argv[optind], O_RDONLY);
                           while(readline1(fd1, str1)) {
                                 if(wifind(str1, str2) != NULL) {
                                      /*if(argv[optind + 2] == NULL) {
                                            puts(str2);
                                      }
                                      else*/
                                            //printf("%s:%s\n", argv[n], str2);
                                      ct++;
                                      break;
                                 }
                           }
                           close(fd1);
                           
                     }
                     printf("%s:%d\n", argv[n], ct); 
                     close(fd);
                     n++;
                     ct = 0;
                }
          }
          //fiwh or fiwH
          if(iflag == 1 && vflag != 1 && rflag != 1 && wflag == 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1 && (Hflag == 1 || hflag == 1)  && fflag == 1 && eflag != 1){
                int fd, fd1, n = optind + 1, i;
                char *str1, *str2;
                str1 = (char*)malloc(1000);  
                str2 = (char*)malloc(1000);   
                while(1) {            
                     fd = open(argv[n], O_RDONLY);
                     if(fd == -1) {
                           break;
                     }
                     while(readline(fd, str2)) {
                           fd1 = open(argv[optind], O_RDONLY);
                           while(readline1(fd1, str1)) {
                                 if(wifind(str1, str2) != NULL) {
                                      if(argv[optind + 2] == NULL) {
                                            puts(str2);
                                      }
                                      else
                                            if(Hflag == 1) {
                                                printf("%s:%s\n", argv[n], str2);
                                            }
                                            else
                                                puts(str2);
                                      break;
                                 }
                           }
                           close(fd1);
                     }
                     close(fd);
                     n++;
                }
          }
          //fich
          if(iflag == 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1 && (Hflag == 1 || hflag == 1)  && fflag == 1 && eflag != 1){
                int fd, fd1, n = optind + 1, i, ct = 0;
                char *str1, *str2;
                str1 = (char*)malloc(1000);  
                str2 = (char*)malloc(1000);   
                while(1) {            
                     fd = open(argv[n], O_RDONLY);
                     if(fd == -1) {
                           break;
                     }
                     while(readline(fd, str2)) {
                           fd1 = open(argv[optind], O_RDONLY);
                           while(readline1(fd1, str1)) {
                                 if(ifind(str1, str2) == 1) {
                                      /*if(argv[optind + 2] == NULL) {
                                            puts(str2);
                                      }
                                      else*/
                                            //printf("%s:%s\n", argv[n], str2);
                                      ct++;
                                      break;
                                 }
                           }
                           close(fd1);
                           
                     }
                     if(Hflag == 1) {
                           printf("%s:%d\n", argv[n], ct);
                     }
                     else
                           printf("%d\n", ct); 
                     close(fd);
                     n++;
                     ct = 0;
                }
          }
          //fwch
          if(iflag != 1 && vflag != 1 && rflag != 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1 && (Hflag == 1 || hflag == 1)  && fflag == 1 && eflag != 1){
                int fd, fd1, n = optind + 1, i, ct = 0;
                char *str1, *str2;
                str1 = (char*)malloc(1000);  
                str2 = (char*)malloc(1000);   
                while(1) {            
                     fd = open(argv[n], O_RDONLY);
                     if(fd == -1) {
                           break;
                     }
                     while(readline(fd, str2)) {
                           fd1 = open(argv[optind], O_RDONLY);
                           while(readline1(fd1, str1)) {
                                 if(wfind(str1, str2) != NULL) {
                                      /*if(argv[optind + 2] == NULL) {
                                            puts(str2);
                                      }
                                      else*/
                                            //printf("%s:%s\n", argv[n], str2);
                                      ct++;
                                      break;
                                 }
                           }
                           close(fd1);
                           
                     }
                     if(Hflag == 1) {
                           printf("%s:%d\n", argv[n], ct);
                     }
                     else
                           printf("%d\n", ct); 
                     close(fd);
                     n++;
                     ct = 0;
                }
          }
          //fiwch
          if(iflag == 1 && vflag != 1 && rflag != 1 && wflag == 1 && cflag == 1 && mflag != 1 && bflag != 1 && qflag != 1 && (Hflag == 1 || hflag == 1)  && fflag == 1 && eflag != 1){
                int fd, fd1, n = optind + 1, i, ct = 0;
                char *str1, *str2;
                str1 = (char*)malloc(1000);  
                str2 = (char*)malloc(1000);   
                while(1) {            
                     fd = open(argv[n], O_RDONLY);
                     if(fd == -1) {
                           break;
                     }
                     while(readline(fd, str2)) {
                           fd1 = open(argv[optind], O_RDONLY);
                           while(readline1(fd1, str1)) {
                                 if(wifind(str1, str2) != NULL) {
                                      /*if(argv[optind + 2] == NULL) {
                                            puts(str2);
                                      }
                                      else*/
                                            //printf("%s:%s\n", argv[n], str2);
                                      ct++;
                                      break;
                                 }
                           }
                           close(fd1);
                           
                     }
                     if(Hflag == 1) {
                           printf("%s:%d\n", argv[n], ct);
                     }
                     else
                           printf("%d\n", ct); 
                     close(fd);
                     n++;
                     ct = 0;
                }
          }
          //e
       /*   if(iflag != 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1 && Hflag != 1 && hflag != 1  && fflag != 1 && eflag == 1){
                int m = 1, n = optind + 1, fd, k = 2, z = 0; 
                char *str1, string[] = "-e", *str2;
                str1 = (char*)malloc(1000); 
                str2 = (char*)malloc(1000);  
                strcpy(str2, string);         
                while(strcmp(argv[m], str2) == 0) {
                      m = m + 2;
                      //printf("%d\n", m);
                }
                n = m;
                while(1) {
                     fd = open(argv[n], O_RDONLY);
                     if(fd == -1) {
                            break;
                     }
                     while(1) {
                            strcpy(str2, pattern[z][1000]);
                            while(readline(fd, str2)) {
                                 if(find(str1, str2)) {
                                      printf("%s:%s\n", argv[n], str2);
                                 }
                            }
                            k = k + 2;
                     }
                     n++;
                }
                            
          }*/
          //regex
          if(iflag != 1 && vflag != 1 && rflag != 1 && wflag != 1 && cflag != 1 && mflag != 1 && bflag != 1 && qflag != 1 && Hflag != 1 && hflag != 1  && fflag != 1 && eflag != 1) {
                int fd, n = 2, i, length;
                char *regexp, *str1, string[] = "^", string1[] = "$", string2[] = ".", string3[] = "*", *p1, *p2, *p3, *p4;
                str1 = (char*)malloc(1000);
                regexp = (char*)malloc(1000);
                strcpy(regexp, argv[1]);
                length = strlen(regexp);
                p1 = strstr(regexp, string);
                p2 = strstr(regexp, string1);
                p3 = strstr(regexp, string2);
                p4 = strstr(regexp, string3);
                
                if(p1 != NULL && p2 == NULL && p3 == NULL && p4 == NULL) {
                  while(1) {
	             fd = open(argv[n], O_RDONLY);
                     if(fd == -1) {
                        break;
                     }
                     while(readline(fd, str1)) {
                        i = match(regexp, str1);
                        if(i == 1) {
                           if(argv[3] == NULL) {
                              printf("%s\n", str1);
                           }
                           else
                              printf("%s:%s\n", argv[n], str1);
                        }
                     }
                     n++;
                  }
                }
                if(p1 == NULL && p2 != NULL && p3 == NULL && p4 == NULL) {
                  while(1) {
	             fd = open(argv[n], O_RDONLY);
                     if(fd == -1) {
                        break;
                     }
                     while(readline(fd, str1)) {
                        i = match(regexp, str1);
                        if(i == 1) {
                           if(argv[3] == NULL) {
                              printf("%s\n", str1);
                           }
                           else
                              printf("%s:%s\n", argv[n], str1);
                        }
                     }
                     n++;
                  }
                }
                if(p1 == NULL && p2 == NULL && p3 != NULL && p4 == NULL) {
                  while(1) {
	             fd = open(argv[n], O_RDONLY);
                     if(fd == -1) {
                        break;
                     }
                     while(readline(fd, str1)) {
                        i = match(regexp, str1);
                        if(i == 1) {
                           if(argv[3] == NULL) {
                              printf("%s\n", str1);
                           }
                           else
                              printf("%s:%s\n", argv[n], str1);
                        }
                     }
                     n++;
                  }
                }
                if(p1 == NULL && p2 == NULL && p3 == NULL && p4 != NULL) {
                  while(1) {
	             fd = open(argv[n], O_RDONLY);
                     if(fd == -1) {
                        break;
                     }
                     while(readline(fd, str1)) {
                        i = match(regexp, str1);
                        if(i == 1) {
                           if(argv[3] == NULL) {
                              printf("%s\n", str1);
                           }
                           else
                              printf("%s:%s\n", argv[n], str1);
                        }
                     }
                     n++;
                  }
                }


            }
                   
        
        
        
        
        
        
        
        
       
       
       
}
       
