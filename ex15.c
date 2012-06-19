#include <stdio.h>#include <assert.h>#define ARRLEN 5int main (int argc, char * argv[]) {    /*    Create two arrays, ages storing some int data, and names storing an array of    strings.    */    int ages[] = {50, 40, 30, 20, 10, 0 };    char * names[] = {"Adam", "Eva", "Kain", "Abel", "Jacob", NULL};    /*    Some variables for our for-loops later.    */    int * iptr = ages;    char ** cptr = names;    const int count_ages = (int) (sizeof(ages)/sizeof(int) - 1);    assert (count_ages == ARRLEN);    /*    You know this is just looping through the two arrays and printing how old each    person is. This is using i to index into the array.    Create a pointer that points at ages. Notice the use of int * to create a    "pointer to integer" type of pointer. That’s similar to char *, which is a    "pointer to char", and a string is an array of chars. Seeing the similarity yet?    Create a pointer that points at names. A char * is already a "pointer to char",    so that’s just a string. You however need 2 levels, since names is 2-dimensional,    that means you need char ** for a "pointer to (a pointer to char)" type. Study    that too, explain it to yourself.    */    printf("loop 1:\n");    while (*iptr && *cptr)        printf("%s is %d years old.\n", *cptr++, *iptr++);    /*    Loop through ages and names but instead use the pointers plus an offset of i.    Writing *(cur_name+i) is the same as writing name[i], and you read it as "the    value of (pointer cur_name plus i)".    This shows how the syntax to access an element of an array is the same for a    pointer and an array.    */    iptr = ages;    cptr = names;    printf("loop 2:\n");    for (int i = 0; i < ARRLEN; i++)        printf("%s is %d years old.\n", *(cptr+i), *(iptr+i));    /*    Another admittedly insane loop that does the same thing as the other two, but    instead it uses various pointer arithmetic methods:      Initialize our for-loop by setting cur_name and cur_age to the beginning of the      names and ages arrays.      The test portion of the for-loop then compares the distance of the pointer      cur_age from the start of ages. Why does that work?      The increment part of the for-loop then increments both cur_name and cur_age      so that they point at the next element of the name and age arrays.      The pointers cur_name and cur_age are now pointing at one element of the arrays      they work on, and we can print them out using just *cur_name and *cur_age, which      means "the value of wherever cur_name is pointing".    */    printf("loop 3:\n");    for (iptr = ages, cptr = names; iptr - ages < count_ages; iptr++, cptr++)        printf("%s is %d years old.\n", *cptr, *iptr);    return 0;}