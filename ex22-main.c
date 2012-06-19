#include "ex22.h"

#define NL printf("\n")

const char      MY_NAME[] = "Joe Doe";

void
scope_demo(int count) {
    log_info("count = %d", count);
    if (count > 10) {
        int             count = 100;	/* never do this */
        log_info("count in if scope = %d", count);
    }
    log_info("count after if scope = %d", count);
    count = 3000;
    log_info("count before leaving the function = %d", count);
}

int
main(int argc, char *argv[]) {
    const double    value = 2.0;
    NL;
    log_info("name in ex22-main.c = %s, static int THE_AGE in ex22.c is = %d",
             MY_NAME, get_age());

    log_info("nset static int THE_AGE in ex22.c to 30:");
    set_age(30);
    log_info("static int THE_AGE in ex22.c in main() is now: %d", get_age());
    NL;
    log_info("can't directly access static int THE_AGE in ex22.c in main:");
    log_info("-> log_info(\"THE_AGE = %%d\", THE_AGE);");
    NL;
    log_info("can't directly access int THE_SIZE in ex22.c in main:");
    log_info("-> log_info(\"THE_SIZE = %%d\", THE_SIZE);");
    NL;
    log_info("can directly access int THE_EXTERN_SIZE in ex22.c in main:");
    log_info("THE_EXTERN_SIZE = %d", THE_EXTERN_SIZE);
    NL;
    log_info("update value to (double) THE_EXTERN_SIZE from %.1f",
             update_static((double) THE_EXTERN_SIZE));
    log_info("update value to const double value from %.1f", update_static(value));
    log_info("update value to 10.0 from %.1f", update_static(10.0));
    NL;

    return 0;
}
