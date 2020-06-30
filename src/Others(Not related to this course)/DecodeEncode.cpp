#include <string.h>

#include <cstdio>
#include <iostream>
using namespace std;

int EncodeFunc(const char* pSource, const char* pKey, char* pEncrypted) {
    int keyLen = strlen(pKey);
    int sourceLen = strlen(pSource);
    if (keyLen == 0)
        return 0;

    int key[keyLen];
    int currKeyPos = 0;

    for (int i = 0; i < keyLen; i++) {
        if (pKey[i] < '0' || pKey[i] > '9')
            return 0;
        key[i] = pKey[i] - '0';
    }
    for (int currResPos = 0; currResPos < sourceLen; currResPos++) {
        if (!isalpha(pSource[currResPos])) {
            pEncrypted[currResPos] = pSource[currResPos];
            currKeyPos++;
            if (currKeyPos == keyLen)
                currKeyPos = 0;
            continue;
        }

        pEncrypted[currResPos] = pSource[currResPos] + key[currKeyPos];
        currKeyPos++;
        if (currKeyPos == keyLen)
            currKeyPos = 0;
    }
    pEncrypted[sourceLen] = '\0';
    return 1;
}

int DecodeFunc(const char* pEncrypted, const char* pKey, char* pSource) {
    int keyLen = strlen(pKey);
    int sourceLen = strlen(pEncrypted);
    if (keyLen == 0)
        return 0;

    int key[keyLen];
    int currKeyPos = 0;

    for (int i = 0; i < keyLen; i++) {
        if (pKey[i] < '0' || pKey[i] > '9')
            return 0;
        key[i] = pKey[i] - '0';
    }
    for (int currResPos = 0; currResPos < sourceLen; currResPos++) {
        if (!isalpha(pEncrypted[currResPos])) {
            pSource[currResPos] = pEncrypted[currResPos];
            currKeyPos++;
            if (currKeyPos == keyLen)
                currKeyPos = 0;
            continue;
        }

        pSource[currResPos] = pEncrypted[currResPos] - key[currKeyPos];
        currKeyPos++;
        if (currKeyPos == keyLen)
            currKeyPos = 0;
    }
    pSource[sourceLen] = '\0';
    return 1;
}
int main(void) {
    char* res = (char*)malloc(1000 * sizeof(char));
    printf("%d\n", EncodeFunc("I am a student.", "1314", res));
    printf("%s", res);
    return 0;
}