#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

unsigned char** img;

#pragma pack(push, 2)

struct BmpHeader {
    unsigned char b1, b2; // Символы BM (2 байта)
    unsigned long size; // Размер файла (4 байта)
    unsigned short notUse1; // (2 байта)
    unsigned short notUse2; // (2 байта)
    unsigned long massPos; // Местанахождение данных растрового массива (4 байта)

    unsigned long headerLength; // Длинна этого заголовка (4 байта)
    unsigned long width; // Ширина изображения (4 байта)
    unsigned long height; // Высота изображения (4 байта)
    unsigned short colorPlaneNumber; // Число цветовых плоскостей (2 байта)
    unsigned short bitPixel; // Бит/пиксель (2 байта)
    unsigned long compressMethod; // Метод сжатия (4 байта)
    unsigned long massLength; // Длинна массива с мусоро (4 байта)
    unsigned long massWidth; // Ширина массива с мусором (4 байта)
    unsigned long massHeight; // Высота массива с мусором (4 байта)
    unsigned long colorNumber; // Число цветов изображения (4 байта)
    unsigned long generalColorNumber; // Число основных цветов (4 байта)

} bmpHeader;

#pragma pack(pop)


int readBMP(char* path) {
    FILE* file;
    long long i, j, u, v;

    file = fopen(path, "rb");
    if (file == NULL) return 0;

    fread(&bmpHeader, sizeof(bmpHeader), 1, file);

    int mx = bmpHeader.width;
    int my = bmpHeader.height;
    int mx3 = (3 * mx + 3) & (-4);

    img = (unsigned char*)calloc(mx3 * my, sizeof(char));
    fread(img, 1, mx3 * my, file);
    int s = bmpHeader.height * bmpHeader.width;

    rotate(bmpHeader, img);

    rotate_2(bmpHeader, img);

    fclose(file);
}


int saveBMP(char* path) {
    FILE* file;
    int i, j;
    file = fopen(path, "wb");
    if (file == NULL) return 0;

    int mx = bmpHeader.width;
    int my = bmpHeader.height;
    int mx3 = (3 * mx + 3) & (-4);
    int filesize = 54 + my * mx3;


    fwrite(&bmpHeader, sizeof(bmpHeader), 1, file);


    fwrite(img, sizeof(char), mx3 * my, file);

    fclose(file);

    return 1;
}


void rotate(struct BmpHeader *head, unsigned char *img) {
    int i, j;
    int bytes = head->bitPixel / 8;
    int width = (bytes * head->width + bytes) & (-4);

    for (i = 0; i < head->height; ++i) {
        for (j = 0; j < head->width / 2; ++j) {
            swap(img + (i * width) + j * bytes,
                 img + (i * width) + (head->width - j - 1) * bytes,
                 bytes);
        }
    }
}

int swap(unsigned char* a, unsigned char* b, unsigned bytes) {
    unsigned char tmp;

    while (bytes--) {
        tmp = *a;
        *a++ = *b;
        *b++ = tmp;
    }
}

void rotate_2(const struct BmpHeader* head, unsigned char* img) {
    int i, j;
    int bytes = head->bitPixel / 8;
    int width = (bytes * head->width + bytes) & (-4);

    for (i = 0; i < head->height / 2; ++i) {
        for (j = 0; j < head->width; ++j) {
            swap(img + (width * i) + j * bytes,
                 img + (width * (head->height - i - 1)) + j * bytes,
                 bytes);
        }
    }
}

int main(){
    readBMP("img.bmp");
    saveBMP("img.bmp");
}

