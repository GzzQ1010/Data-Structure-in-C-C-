#include <stdio.h>
#include "heap.h"
#include <string.h>

typedef struct Person_ {
    const char *name;
    int age;
    double height;
} Person;

void outputSorted(const Person people[], int numPeople, int (*compare)(const void *pKey1, const void *pKey2)) {
    Heap heap;
    heap_init(&heap, compare, NULL);

    // Insert people into the heap
    for (int i = 0; i < numPeople; i++) {
        heap_insert(&heap, &people[i]);
    }

    // Extract and output each person in sorted order
    void *data;
    while (heap_size(&heap) > 0) {
        heap_extract(&heap, &data);
        Person *person = (Person *)data;
        printf("Name: %s, Age: %d, Height: %.2f\n", person->name, person->age, person->height);
    }

    heap_destroy(&heap);
}
int compareByName(const void *pKey1, const void *pKey2) {
    Person *person1 = (Person *)pKey1;
    Person *person2 = (Person *)pKey2;
    return strcmp(person1->name, person2->name);
}

int compareByAge(const void *pKey1, const void *pKey2) {
    Person *person1 = (Person *)pKey1;
    Person *person2 = (Person *)pKey2;
    return person1->age - person2->age;
}

int compareByHeight(const void *pKey1, const void *pKey2) {
    Person *person1 = (Person *)pKey1;
    Person *person2 = (Person *)pKey2;
    if (person1->height < person2->height) return -1;
    if (person1->height > person2->height) return 1;
    return 0;
}

int main(){
    Person people[] = {
    {"Alice", 30, 5.5},
    {"Bob", 25, 5.8},
    {"Charlie", 35, 5.6},
    {"Dave", 20, 5.9},
    {"Eve", 22, 5.7}};

printf("Sorted by Name:\n");
outputSorted(people, 5, compareByName);

printf("\nSorted by Age:\n");
outputSorted(people, 5, compareByAge);

printf("\nSorted by Height");
outputSorted(people, 5, compareByHeight);

return 0;

}