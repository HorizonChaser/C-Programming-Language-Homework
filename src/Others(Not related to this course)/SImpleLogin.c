#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char inputName[100], originalName[] = "originalname";
    scanf("%s", inputName);
    if (strcmp(inputName, originalName) == 0) {
        printf("Successfully Logged in as %s", originalName);
    } else {
        printf("Failed to Login");
    }
    return 0;
}