#include <stdio.h>

#include "dbg.h"
#include <string.h>
#define NL printf("\n")

#define MAXDATA 11

typedef enum enumint {
    ONE, TWO, THREE, FOUR, FIVE, OTHER
}               enumint;

const char     *ENUMINTNAMES[] = {
    "ONE", "TWO", "THREE", "FOUR", "FIVE", "OTHER"
};

struct results {
    char            name[MAXDATA];
    int             value;
    enumint         prop;
};

int
main(int argc, char *argv[]) {
    struct results  res;
    char           *rc_cptr;
    int             rc;

    NL;
    printf("give name[MAXDATA = %d]: ", MAXDATA - 1);
    /* rc = fscanf(stdin, "%s", res.name);  *//* !! unsafe !! */
    rc_cptr = fgets(res.name, MAXDATA, stdin);
    check(rc_cptr, "name fscanf error");

    while (getchar() != '\n');	/* eat all until (including) '\n' */

    if (rc_cptr[MAXDATA - 1] == '\0' && res.name[MAXDATA - 1] == '\0')
        log_info("rc_cptr[MAXDATA - 1] = '\\0', res.name[MAXDATA - 1] = '\\0'");
    else
        log_info("rc_cptr[MAXDATA - 1] = '%c', res.name[MAXDATA - 1] = '%c'",
                 rc_cptr[MAXDATA - 1], res.name[MAXDATA - 1]);

    log_info("res.name = %s of strlen = %ld chars",
             res.name, (long) strlen(res.name));
    log_info("address rc_cptr = %ld, address res.name = %ld",
             (long) rc_cptr, (long) &res.name);
    NL;

    for (int i = ONE; i <= OTHER; i++)
        printf("%d) %s\n", i + 1, ENUMINTNAMES[i]);
    do {
        printf(" > ");
        rc = fscanf(stdin, "%d", (int *) &res.prop);
        check(rc, "error while reading result property");
        res.prop--;
    } while (res.prop < 0 || res.prop > OTHER);
    NL;
    log_info("res.prop = ENUMINTNAMES[%d] = %s",
             res.prop, ENUMINTNAMES[res.prop]);
    NL;



    return 0;
error:
    return 1;
}
