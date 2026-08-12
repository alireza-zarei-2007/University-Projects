/*
 * Course: Advanced Programming (Term 1)
 * Assignment: 04 - Task A
 * Description: We want to assign house numbers (plates) in a city such that no two houses have the same plate number.
                For this purpose, we have a "Plate Registration Office" that can store information for a maximum of MAX houses.
                A house is defined with the following fields:
                Plate number (integer)
                Street name (string with a maximum length of 50 characters)
                Unit number (integer)
                The registration office contains an array of houses and the current count of registered houses.
                Complete the function below that takes a pointer to a registry, and the information of a new house (plate, street, unit). 
                If the plate number has not been registered before, add the house to the end of the registry array and return 1. 
                If the plate number is a duplicate, do not add anything and return 0. 
                If the registry is full, return -1.
                int registerHouse(Registry* reg, int plate, char street[], int unit) {
                    // Your code here
                }
  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct House House;
typedef struct Registry Registry;

struct House {
    int PlateNum;
    char StreetName[50];
    int UnitNum;
};
struct Registry {
    struct House House[MAX];
    int NumRegistered;
};
int registerHouse(Registry *reg, int plate, char street[], int unit)
{
    if (reg->NumRegistered >= MAX) {
        return -1;
    }
    for (int i = 0; i < reg->NumRegistered; i++) {
        if (plate == reg->House[i].PlateNum) {
            return 0;
        }
    }
    reg->House[reg->NumRegistered].PlateNum = plate;
    strcpy(reg->House[reg->NumRegistered].StreetName, street);
    reg->House[reg->NumRegistered].UnitNum = unit;
    reg->NumRegistered++;

    return 1;
}
int main()
{
    Registry reg;
    int plate = 7, unit = 10;
    char street[20] = "street1";

    reg.House[0] = (House){1, "street1", 1};
    reg.House[1] = (House){2, "street2", 2};
    reg.House[2] = (House){3, "street3", 3};
    reg.House[3] = (House){4, "street4", 4};
    reg.House[4] = (House){5, "street5", 5};
    reg.House[5] = (House){6, "street6", 6};
    reg.NumRegistered = 6;

    printf("%d", registerHouse(&reg, plate, street, unit));
    return 0;
}
