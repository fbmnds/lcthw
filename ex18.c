#include "ex18.h"

int
inc_order(const int a, const int b) {
    return (a - b);
}

int
dec_order(const int a, const int b) {
    return (b - a);
}

int
oddeven_order(const int a, const int b) {
    return (!(a % 2));
}

int            *
bubble_sort(int *source, const int count, compare_cb cmp) {
    int             i, j;
    int            *sorted = malloc(count * sizeof(int));
    int             tmp;

    check_mem(sorted);
    memcpy(sorted, source, count * sizeof(int));	/* trust count */

    for (i = 0; i < count; i++)
        for (j = 0; j < count - 1; j++)
            if (cmp(sorted[j], sorted[j + 1]) > 0) {
                tmp = sorted[j + 1];
                sorted[j + 1] = sorted[j];
                sorted[j] = tmp;
            }
    return sorted;
error:
    return NULL;
}

void
print_numbers(const int *sorted, const int count) {
    for (int i = 0; i < count; i++)
        printf("%d ", sorted[i]);
    printf("\n");
}


int
test_sorting(int *source, const int count) {
    int            *sorted;

    sorted = bubble_sort(source, /* 2* */ count, inc_order);	/* lie here unnoticed */
    check(sorted, "inc_order sort failed");
    print_numbers(sorted, count);
    cfree(sorted);

    sorted = bubble_sort(source, count, dec_order);
    check(sorted, "dec_order sort failed");
    print_numbers(sorted, count);
    cfree(sorted);

    sorted = bubble_sort(source, count, oddeven_order);
    check(sorted, "oddeven_order sort failed");
    print_numbers(sorted, count);
    cfree(sorted);

    return 0;
error:
    if (sorted)
        cfree(sorted);
    return 1;
}

int
main(int argc, char *argv[]) {
    int             count = argc - 1;
    int            *source;

    if (argc < 2) {
        printf("usage: %s 5 3 4 1 2\n", argv[0]);
        goto error;
    }
    source = malloc(count * sizeof(int));
    check_mem(source);

    for (int i = 0; i < count; i++)
        source[i] = atoi(argv[i + 1]);
    print_numbers(source, count);
    printf("\n");

    check(!(test_sorting(source, count)), "test sorting failed");
    cfree(source);
    return 0;
error:
    return 1;
}
