#include <stdio.h>
#include "qksort.h" 

int compareCarsByMakeThenModel(const void *car1, const void *car2);

int compareCarsByDescendingMPG(const void *car1, const void *car2) ;

int compareCarsByMakeThenDescendingMPG(const void *car1, const void *car2) ;


#define MAX_STRING_LENGTH 100

typedef struct Car_ {
    char make[MAX_STRING_LENGTH];
    char model[MAX_STRING_LENGTH];
    int mpg; /* Miles per gallon */
} Car;

// [Include the functions from parts a, b, and c here]

void printCars(Car cars[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%s %s: %d MPG\n", cars[i].make, cars[i].model, cars[i].mpg);
    }
}

int main() {
    Car cars[] = {
        {"Toyota", "Camry", 33},
        {"Ford", "Focus", 40},
        {"Honda", "Accord", 34},
        {"Ford", "Mustang", 31},
        {"Honda", "Civic", 39},
        {"Toyota", "Prius", 48},
        {"Honda", "Fit", 35},
        {"Toyota", "Corolla", 35},
        {"Ford", "Taurus", 28}
    };
    int size = sizeof(cars) / sizeof(cars[0]);

    printf("Original order:\n");
    printCars(cars, size);
    printf("\n");

    qksort(cars, size, sizeof(Car), 0, size-1, compareCarsByMakeThenModel);
    printf("Sorted by make then model:\n");
    printCars(cars, size);
    printf("\n");

    qksort(cars, size, sizeof(Car), 0, size-1, compareCarsByDescendingMPG);
    printf("Sorted by descending MPG:\n");
    printCars(cars, size);
    printf("\n");

    qksort(cars, size, sizeof(Car), 0, size-1, compareCarsByMakeThenDescendingMPG);
    printf("Sorted by make then descending MPG:\n");
    printCars(cars, size);
    printf("\n");

    return 0;
}

int compareCarsByMakeThenModel(const void *car1, const void *car2) {
    Car *c1 = (Car *)car1;
    Car *c2 = (Car *)car2;

    int cmp = strcmp(c1->make, c2->make);
    if (cmp == 0) {  // If makes are the same
        return strcmp(c1->model, c2->model);
    }
    return cmp;
}
int compareCarsByDescendingMPG(const void *car1, const void *car2) {
    Car *c1 = (Car *)car1;
    Car *c2 = (Car *)car2;

    return c2->mpg - c1->mpg;  // Descending order
}
int compareCarsByMakeThenDescendingMPG(const void *car1, const void *car2) {
    Car *c1 = (Car *)car1;
    Car *c2 = (Car *)car2;

    int cmp = strcmp(c1->make, c2->make);
    if (cmp == 0) {  // If makes are the same
        return c2->mpg - c1->mpg;  // Descending order
    }
    return cmp;
}