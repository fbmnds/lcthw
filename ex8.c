#include <stdio.h>
#include <string.h>
#include <assert.h>

int
main(int argc, char *argv[]) {
    int             areas[] = {10, 20, 30, 40, 45};
    char            name[] = "Zed";
    char            full_name[] = {
        'Z', 'e', 'd', ' ', 'A', '.', ' ', 'S', 'h', 'a', 'w', '\0'
    };

    /*
     * My computer thinks an int is 4 bytes in size. Your computer might
     * use a different size if it’s a 32-bit vs. 64-bit.
     */
    printf("sizeof(int) = %ld\n", sizeof(int));
    /*
        The areas array has 5 integers in it, so it makes sense that my computer requires
        20 bytes to store it.
        */
    printf("> int areas[] = {10, 20, 30, 40, 45};\n");
    printf("sizeof(areas) = %ld\n", sizeof(areas));
    /*
        If we divide the size of areas by size of an int then we get 5 elements. Looking
        at the code, this matches what we put in the initializer.
        */
    printf("number of elements in areas[] = %ld\n", sizeof(areas) / sizeof(int));
    /*
        We then did an array access to get areas[0] and areas[1] which means C is "zero
        indexed" like Python and Ruby.
        */
    printf("first element of areas = %d, second element is = %d\n",
           areas[0], areas[1]);
    /*
        We repeat this for the name array, but notice something odd about the size of
        the array? It says it’s 4 bytes long, but we only typed "Zed" for 3 characters.
        Where’s the 4th one coming from?
        */
    printf("> char name[] = \"Zed\";\n");
    printf("sizeof(name) = %ld\n", sizeof(name));
    printf("number of chars = %ld\n", sizeof(name) / sizeof(char));
    /*
        We do the same thing with full_name and notice it gets this correct.
        */
    printf("sizeof(full_name) = %ld\n", sizeof(full_name));
    printf("number of chars = %ld\n", sizeof(full_name) / sizeof(char));
    /*
        Finally we just print out the name and full_name to prove that they actually are
        "strings" according to printf.
         */
    printf("name = %s\n", name);
    printf("full_name = %s\n", full_name);
    printf("strlen(full_name) = %ld\n", strlen(full_name));
    assert(strlen(full_name) + 1 == sizeof(full_name));

    return 0;
}
