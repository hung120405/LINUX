#ifndef PERSON_H
#define PERSON_H

#include <stdio.h>

typedef struct {
    char name[50];
    int age;
} Person;

void displayPerson(Person p);

#endif 