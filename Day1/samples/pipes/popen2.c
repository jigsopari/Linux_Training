/*
 * program to demonstrate use of popen with pwd
 */
#include <stdio.h>

#define MAXLINE   255

main()
{
        FILE  *fp;
        char  line[MAXLINE];

        if ( (fp = popen("/bin/pwd", "r")) == NULL)
                err_sys("popen error");
                
        if (fgets(line, MAXLINE, fp) == NULL)
                err_sys("fgets error");

        printf("%s", line);        /* pwd inserts the newline */

        pclose(fp);
        exit(0);
}

/* display err message and exit */

err_sys(char *s)
{
  printf("%s\n", s);
  exit(1);
}

