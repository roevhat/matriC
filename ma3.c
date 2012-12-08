/*
    RELEASED UNDER BEER-LICENSE!
    Joakim Børlum Petersen \ #roevhat
    AAU
*/

/*
TODO + BUGS + DIV.
==================
(X) Gem til fil.

(X) Herefter løse alle problemer vi kan blive stillet overfor i LIAL-eksamen
    -> Alt egenvektor og egenværdi-halløjet især
    -> Måske finde en cool måde at lave sets på? Ellers bare som matrix.
    -> Wootz.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "matrix.h"

int timeNow();

int outputRref(matrix * entity, int all, int timer);

int outputInverse(matrix * entity, int all, int timer);

int outputDet(matrix * entity, int all, int timer);

int main(int argc, char *argv[]){
    int timer = 0;
    int all   = 0;
    int file  = 0;

    if (argc < 2){
        printf("%s\n", "matriC needs additional arguments!");
    } else {

        if (strstr(argv[1], "t")){
            timer = 1;
        }

        if (strstr(argv[1], "all")){
            all = 1;
        }

        if (strstr(argv[1], "f")){
            file = 1;
        }

        if (strstr(argv[1], "R")){
            matrix input;
            if (file){
                input = parseInput(argv[2], 1);
            } else {
                input = parseInput(argv[2], 0);
            }
            outputRref(&input, all, timer);

        } else if (strstr(argv[1], "I")){
            matrix input;
            if (file){
                input = parseInput(argv[2], 1);
            } else {
                input = parseInput(argv[2], 0);
            }
            outputInverse(&input, all, timer);

        } else if (strstr(argv[1], "D")){
            matrix input;
            if (file){
                input = parseInput(argv[2], 1);
            } else {
                input = parseInput(argv[2], 0);
            }
            outputDet(&input, all, timer);
        } else {
            printf("%s\n", "matriC needs a primary function specified as an argument:");
            printf("%s\n", "    -> R (reduced row echelon form)");
            printf("%s\n", "    -> I (inverse)");
            printf("%s\n", "    -> D (determinant)");
        }      
    }
}

int timeNow(){
    struct timeval tv1;
    gettimeofday(&tv1, NULL);
    int time1 = (tv1.tv_sec) * 1000000 + (tv1.tv_usec);

    return time1;
}

int outputRref(matrix * entity, int all, int timer){
    if (all){
        printf("{INPUT(%ix%i)}\n", entity->m, entity->n);
        printf("\n");
        printMatrix(entity);
        printf("\n");
    }

    int t1 = timeNow();

    matrix rowEchelonForm;
    if (all){
        rowEchelonForm = toRowEchelonForm(entity, 1);
    } else {
        rowEchelonForm = toRowEchelonForm(entity, 0);
    }

    if (all){
        printf("%s\n", "{ROW ECHELON FORM}");
        printf("\n");
        printMatrix(&rowEchelonForm);
        printf("\n");
    }

    matrix reducedRowEchelonForm;

    if (all){
        reducedRowEchelonForm = toReducedRowEchelonForm(&rowEchelonForm, 1);
    } else {
        reducedRowEchelonForm = toReducedRowEchelonForm(&rowEchelonForm, 0);
    }
    

    int t2    = timeNow();
    int tDiff = t2-t1;

    if (all){
        printf("%s\n", "{REDUCED ROW ECHELON FORM}");
        printf("\n");
    }

    printMatrix(&reducedRowEchelonForm);

    if (all){
        printf("\n");
        printf("%s\n", "{RANK AND NULLITY}");
        printf("Rank is %i and nullity is %i\n", matrixRank(&reducedRowEchelonForm), matrixNullity(&reducedRowEchelonForm));
    }

    if (timer){
        printf("\n");
        printf("%s\n", "{TIMER}");
        printf("It took %i microseconds!\n", tDiff);
        printf("\n");
    }

    return 1;
}

int outputInverse(matrix * entity, int all, int timer){
    if (all){
        printf("{INPUT(%ix%i)}\n", entity->m, entity->n);
        printf("\n");
        printMatrix(entity);
        printf("\n");
    }

    int t1 = timeNow();

    matrix inverse = inverseOfMatrix(entity);

    int t2    = timeNow();
    int tDiff = t2-t1;

    if (all){
        printf("%s\n", "{INVERSE OF MATRIX}");
        printf("\n");
    }

    printMatrix(&inverse);

    if (timer){
        printf("\n");
        printf("%s\n", "{TIMER}");
        printf("It took %i microseconds!\n", tDiff);
        printf("\n");
    }

    return 1;

}

int outputDet(matrix * entity, int all, int timer){
    if (all){
        printf("{INPUT(%ix%i)}\n", entity->m, entity->n);
        printf("\n");
        printMatrix(entity);
        printf("\n");
    }

    int t1 = timeNow();

    float det = cofactorExpansion(entity, 1);

    int t2    = timeNow();
    int tDiff = t2-t1;

    if (all){
        printf("%s\n", "{DETERMINANT OF MATRIX}");
        printf("\n");
    }

    printf("det(INPUT) = %f\n", det);

    if (timer){
        printf("\n");
        printf("%s\n", "{TIMER}");
        printf("It took %i microseconds!\n", tDiff);
        printf("\n");
    }

    return 1;

}