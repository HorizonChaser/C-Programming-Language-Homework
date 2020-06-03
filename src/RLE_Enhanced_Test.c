#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char *getFullFileData(char *filePath, int *length) {
    FILE *file;
    unsigned char *data;

    file = fopen(filePath, "rb+");
    if (file == NULL) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    *length = ftell(file);
    data = (unsigned char *)malloc((*length + 1) * sizeof(char));
    rewind(file);
    *length = fread(data, 1, *length, file);
    data[*length] = '\0';
    fclose(file);
    return data;
}

bool checkRepetition(unsigned char *in, int rest) {
    if (rest < 2)
        return false;
    else {
        if (*in == *(in + 1) && *in == *(in + 2))
            return true;
        else
            return false;
    }
}

int getNonRepetitiveSeq(unsigned char *in, int rest) {
    if (rest <= 2)
        return rest + 1;
    else {
        int c = 0, restc = rest;
        unsigned char *g = in;
        while (!checkRepetition(g, restc)) {
            g++;
            restc--;
            c++;
            if (c >= 128) return c;
            if (restc == 0) return c + 1;
        }
        return c;
    }
}

int enhancedCompress(char *inPath, char *outPath) {
    int insize = 0;

    unsigned char *src = getFullFileData(inPath, &insize);
    unsigned char *outbuf =
        (unsigned char *)malloc((insize * 1.2) * sizeof(unsigned char));

    unsigned char *outBufPos = outbuf;

    for (int i = 0; i < 100; i++) {
        printf("%d ", src[i]);
    }

    int rest = insize - 1;
    int outrest = insize * 1.2;
    int count = -1;
    int flag = 0;
    while (rest >= 0) {
        flag = 0;
        count = -1;
        if (checkRepetition(src, rest)) {
            while (rest >= 0) {
                if (count == 127) break;
                if (*src == *(src + 1)) {
                    rest--;
                    count++;
                    src++;
                } else {
                    count++;
                    if (count == 127) {
                        flag = 1;
                    }
                    break;
                }
            }
            if (outrest < 2) return -1;
            *outbuf = count | 128;
            outbuf++;
            *outbuf = *src;
            outbuf++;
            outrest -= 2;

            if (count != 127 || flag == 1) {
                src++;
                rest--;
            }

        } else {
            if (checkRepetition(src, rest)) continue;
            int num = getNonRepetitiveSeq(src, rest);
            int i;
            if (outrest < (num + 1)) return -1;
            *outbuf = num - 1;
            outbuf++;
            for (i = 0; i < num; i++) {
                *outbuf = *(src + i);
                outbuf++;
            }
            src += num;
            rest -= num;
            outrest -= num + 1;
        }
    }

    for (int i = 0; i < 100; i++) {
        printf("%x ", outBufPos[i]);
    }

    FILE *outFile = fopen(outPath, "wb+");
    fwrite(outBufPos, 1, (insize * 1.2), outFile);
    fclose(outFile);
    return (insize * 1.2) - outrest;
}

int Rle_Decode(unsigned char *inbuf, int insize, unsigned char *outbuf,
               int outsize) {
    int inrest = insize;
    int outrest = outsize;
    int i;
    unsigned char *in = inbuf;
    unsigned char *out = outbuf;
    int ns;
    unsigned char tmp;
    while (inrest >= 0) {
        ns = *in + 1;
        if (ns > 129) {
            if ((outrest - ns + 128) < 0) return -1;
            tmp = *(in + 1);
            for (i = 0; i < ns - 128; i++) {
                *out = tmp;
                out++;
            }
            in += 2;
            inrest -= 2;
            outrest -= ns - 128;

        } else {
            if ((outrest - ns) < 0) return -1;
            in++;
            for (i = 0; i < ns; i++) {
                *out = *in;
                out++;
                in++;
            }
            inrest -= 1 + ns;
            outrest -= ns;
        }
    }
    return outsize - outrest;
}

int main(void) {
    char inPath[20] = "demo.bmp";
    char outPath[20] = "out_enhanced.erle";

    int len = enhancedCompress(inPath, outPath);

    return 0;
}