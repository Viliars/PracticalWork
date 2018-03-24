#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string>
#include <algorithm>
#include "sort.h"
using namespace std;

typedef void(*sort_func)(int *a, int n);

struct sort_s {
   sort_func func;
   string    name;
} funcs [] = {
   {sort_bubble, "bubble"},
   {sort_insertion, "insertion"},
   {sort_shell,  "shell"},
   {sort_merge,  "merge"},
   {sort_heap,   "heap"},
   {sort_quick_recursive, "quick recursive"},
   {sort_vector, "vector"},
   {sort_qsort,  "qsort"},
   //{sort_radix,  "radix"},
};

int main(int argc, char **argv) {
    string kind = "random";
    if (argc > 1 && argv[1] == string("random")) {
        kind = "random";
        argc--; argv++;
    }
    if (argc > 1 && argv[1] == string("ascend")) {
        kind = "ascend";
        argc--; argv++;
    }
    if (argc > 1 && argv[1] == string("descend")) {
        kind = "descend";
        argc--; argv++;
    }
    int start_alg = 0;
    if (argc > 1 && argv[1] == string("fastest")) {
       argc--; argv++;
       start_alg = 2;
    }
    int n = 100000;
    if (argc > 1) {
        n = atoi(argv[1]);
    }
    int *copya = new int[n];
    if (kind == "random") {
       srand(time(NULL));
       for (int i = 0; i < n; i++) {
          copya[i] = rand();
       }
    } else if (kind == "ascend") {
       for (int i = 0; i < n; i++) {
           copya[i] = i * 2;
       }
    } else if (kind == "descend") {
       for (int i = 0; i < n; i++) {
           copya[i] = n*2 - i*2;
       }
    }
    int *a = new int[n];
    for (int alg = start_alg; alg < sizeof funcs/sizeof funcs[0]; alg++) {
       memcpy(a, copya, n * sizeof a[0]);
       printf("%30s: ", funcs[alg].name.c_str()); fflush(stdout);
       clock_t start = clock();
       funcs[alg].func(a, n);
       clock_t end = clock();
       printf("%.3f seconds\n", (end - start) / (double)CLOCKS_PER_SEC);
       for (int i = 0; i < n-1; i++) {
          if (a[i] > a[i+1]) {
             printf("sort failed: a[%d]=%d a[%d]=%d\n", i, a[i], i+1, a[i+1]);
             break;
          }
       }
    }
}

