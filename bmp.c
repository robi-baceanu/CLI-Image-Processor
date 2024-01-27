#include "bmp_header.h"

void swap(int *x, int *y) {  // Function for swapping 2 integers
    int aux = *x;
    *x = *y;
    *y = aux;
}

void edit(char *fisier, bmp_fileheader *fileh,
bmp_infoheader *infoh, int ****pixel_matrix) {
    // Opening the file

    FILE* image = fopen(fisier, "rb");

    // Reading file header

    fread(&(fileh->fileMarker1), sizeof(char), 1, image);
    fread(&(fileh->fileMarker2), sizeof(char), 1, image);
    fread(&(fileh->bfSize), sizeof(int), 1, image);
    fread(&(fileh->unused1), sizeof(short), 1, image);
    fread(&(fileh->unused2), sizeof(short), 1, image);
    fread(&(fileh->imageDataOffset), sizeof(int), 1, image);

    // Reading info header

    fread(&(infoh->biSize), sizeof(int), 1, image);
    fread(&(infoh->width), sizeof(int), 1, image);
    fread(&(infoh->height), sizeof(int), 1, image);
    fread(&(infoh->planes), sizeof(short), 1, image);
    fread(&(infoh->bitPix), sizeof(short), 1, image);
    fread(&(infoh->biCompression), sizeof(int), 1, image);
    fread(&(infoh->biSizeImage), sizeof(int), 1, image);
    fread(&(infoh->biXPelsPerMeter), sizeof(int), 1, image);
    fread(&(infoh->biYPelsPerMeter), sizeof(int), 1, image);
    fread(&(infoh->biClrUsed), sizeof(int), 1, image);
    fread(&(infoh->biClrImportant), sizeof(int), 1, image);

    // Reading pixel matrix

    int width = infoh->width;
    int height = infoh->height;

    int padding = (4 - ((width * 3) % 4)) % 4;  // Calculating the padding

    *pixel_matrix = malloc(height * sizeof(int**));
    for (int i = 0; i < height; i++) {
        (*pixel_matrix)[i] = malloc((width + padding) * sizeof(int*));
        for (int j = 0; j < width + padding; j++) {
            (*pixel_matrix)[i][j] = malloc(3 * sizeof(int));
        }
    }

    for (int i = 0; i < height; i++) {
        unsigned char px = 0;
        for (int j = 0; j < width; j++)
            for (int k = 0; k < 3; k++) {
                fread(&px, sizeof(unsigned char), 1, image);
                (*pixel_matrix)[i][j][k] = px;
            }
        for (int j = 0; j < padding; j++)
            fread(&px, sizeof(unsigned char), 1, image);
    }

    fclose(image);
}

void save(char *fisier, bmp_fileheader *fileh,
bmp_infoheader *infoh, int ****pixel_matrix) {
    // Opening the file

    FILE* image = fopen(fisier, "wb");

    // Writing file header

    fwrite(&(fileh->fileMarker1), sizeof(char), 1, image);
    fwrite(&(fileh->fileMarker2), sizeof(char), 1, image);
    fwrite(&(fileh->bfSize), sizeof(int), 1, image);
    fwrite(&(fileh->unused1), sizeof(short), 1, image);
    fwrite(&(fileh->unused2), sizeof(short), 1, image);
    fwrite(&(fileh->imageDataOffset), sizeof(int), 1, image);

    // Writing info header

    fwrite(&(infoh->biSize), sizeof(int), 1, image);
    fwrite(&(infoh->width), sizeof(int), 1, image);
    fwrite(&(infoh->height), sizeof(int), 1, image);
    fwrite(&(infoh->planes), sizeof(short), 1, image);
    fwrite(&(infoh->bitPix), sizeof(short), 1, image);
    fwrite(&(infoh->biCompression), sizeof(int), 1, image);
    fwrite(&(infoh->biSizeImage), sizeof(int), 1, image);
    fwrite(&(infoh->biXPelsPerMeter), sizeof(int), 1, image);
    fwrite(&(infoh->biYPelsPerMeter), sizeof(int), 1, image);
    fwrite(&(infoh->biClrUsed), sizeof(int), 1, image);
    fwrite(&(infoh->biClrImportant), sizeof(int), 1, image);

    // Writing pixel matrix

    int width = infoh->width;
    int height = infoh->height;

    int padding = (4 - ((width * 3) % 4)) % 4;  // Calculating the padding

    for (int i = 0; i < height; i++) {
        unsigned char px = 0;
        for (int j = 0; j < width; j++)
            for (int k = 0; k < 3; k++) {
                px = (*pixel_matrix)[i][j][k];
                fwrite(&px, sizeof(unsigned char), 1, image);
            }
        if (padding) {
            for (int j = 0; j < padding; j++) {
                px = (*pixel_matrix)[i][width + j][0];
                fwrite(&px, sizeof(unsigned char), 1, image);
            }
        }
    }

    fclose(image);
}

void insert(char *fisier, bmp_fileheader *fileh,
bmp_infoheader *infoh, int ****pixel_matrix) {
    int y = 0, x = 0;
    fscanf(stdin, "%d", &x);
    fscanf(stdin, "%d", &y);

    // Opening the inserted file

    FILE* insert_image = fopen(fisier, "rb");

    bmp_fileheader insert_fh;
    bmp_infoheader insert_ih;

    // Reading file header for inserted file

    fread(&(insert_fh.fileMarker1), sizeof(char), 1, insert_image);
    fread(&(insert_fh.fileMarker2), sizeof(char), 1, insert_image);
    fread(&(insert_fh.bfSize), sizeof(int), 1, insert_image);
    fread(&(insert_fh.unused1), sizeof(short), 1, insert_image);
    fread(&(insert_fh.unused2), sizeof(short), 1, insert_image);
    fread(&(insert_fh.imageDataOffset), sizeof(int), 1, insert_image);

    // Reading info header for inserted file

    fread(&(insert_ih.biSize), sizeof(int), 1, insert_image);
    fread(&(insert_ih.width), sizeof(int), 1, insert_image);
    fread(&(insert_ih.height), sizeof(int), 1, insert_image);
    fread(&(insert_ih.planes), sizeof(short), 1, insert_image);
    fread(&(insert_ih.bitPix), sizeof(short), 1, insert_image);
    fread(&(insert_ih.biCompression), sizeof(int), 1, insert_image);
    fread(&(insert_ih.biSizeImage), sizeof(int), 1, insert_image);
    fread(&(insert_ih.biXPelsPerMeter), sizeof(int), 1, insert_image);
    fread(&(insert_ih.biYPelsPerMeter), sizeof(int), 1, insert_image);
    fread(&(insert_ih.biClrUsed), sizeof(int), 1, insert_image);
    fread(&(insert_ih.biClrImportant), sizeof(int), 1, insert_image);

    int inserth = insert_ih.height;
    int insertw = insert_ih.width;
    int insertpad = (4 - ((insertw * 3) % 4)) % 4;

    int editedh = infoh->height;
    int editedw = infoh->width;

    for (int i = 0; i < inserth; i++) {
        unsigned char px = 0;
        for (int j = 0; j < insertw; j++)
            for (int k = 0; k < 3; k++) {
                fread(&px, sizeof(unsigned char), 1, insert_image);
                if (i + y < editedh && j + x < editedw)
                    (*pixel_matrix)[i + y][j + x][k] = px;
            }

        for (int j = 0; j < insertpad; j++)
            fread(&px, sizeof(unsigned char), 1, insert_image);
    }

    fclose(insert_image);
}

void set(unsigned char **pencil) {
    char *set_command = malloc(BUFFER * sizeof(char));
    fscanf(stdin, "%s", set_command);

    if (!strcmp(set_command, "draw_color")) {
        unsigned char color = 0;
        for (int i = 3; i >= 1; i--) {
            fscanf(stdin, "%hhu", &color);
            (*pencil)[i] = color;
        }
    } else if (!strcmp(set_command, "line_width")) {
        unsigned char linew = 0;
        fscanf(stdin, "%hhu", &linew);
        (*pencil)[0] = linew;
    }

    free(set_command);
}

void point(int x, int y, int width, int height,
int ****pixel_matrix, unsigned char **pencil) {
    int ray = (*pencil)[0] / 2;
    for (int i = x - ray; i <= x + ray; i++)
        if (i >= 0 && i < height) {
            for (int j = y - ray; j <= y + ray; j++)
                if (j >= 0 && j < width) {
                    for (int k = 0; k < 3; k++)
                        (*pixel_matrix)[i][j][k] = (*pencil)[k + 1];
                }
        }
}

void line(bmp_infoheader *infoh, int ****pixel_matrix,
unsigned char **pencil, int y1, int x1, int y2, int x2) {
    int width = infoh->width;
    int height = infoh->height;

    point(x1, y1, width, height, pixel_matrix, pencil);
    point(x2, y2, width, height, pixel_matrix, pencil);

    if (y1 == y2) {
        if (x1 > x2)
            swap(&x1, &x2);
        for (int i = x1 + 1; i < x2; i++) {
            point(i, y1, width, height, pixel_matrix, pencil);
        }
    } else if (x1 == x2) {
        if (y1 > y2)
            swap(&y1, &y2);
        for (int j = y1 + 1; j < y2; j++) {
            point(x1, j, width, height, pixel_matrix, pencil);
        }
    } else if (abs(x1 - x2) > abs(y1 - y2)) {
        if (x1 > x2) {
            swap(&x1, &x2);
            swap(&y1, &y2);
        }

        for (int i = x1 + 1; i < x2; i++) {
            double y = 1.0 * (i - x1) * (y2 - y1) / (x2 - x1) + y1;
            point(i, (int)y, width, height, pixel_matrix, pencil);
        }
    } else {
        if (y1 > y2) {
            swap(&x1, &x2);
            swap(&y1, &y2);
        }

        for (int j = y1 + 1; j < y2; j++) {
            double x = 1.0 * (j - y1) * (x2 - x1) / (y2 - y1) + x1;
            point((int)x, j, width, height, pixel_matrix, pencil);
        }
    }
}

void rectangle(bmp_infoheader *infoh, int ****pixel_matrix,
unsigned char **pencil) {
    int x = 0, y = 0, w = 0, h = 0;

    fscanf(stdin, "%d", &y);
    fscanf(stdin, "%d", &x);
    fscanf(stdin, "%d", &w);
    fscanf(stdin, "%d", &h);

    line(infoh, pixel_matrix, pencil, y, x, y, x + h);
    line(infoh, pixel_matrix, pencil, y, x + h, y + w, x + h);
    line(infoh, pixel_matrix, pencil, y + w, x + h, y + w, x);
    line(infoh, pixel_matrix, pencil, y + w, x, y, x);
}

void triangle(bmp_infoheader *infoh, int ****pixel_matrix,
unsigned char **pencil) {
    int y1 = 0, x1 = 0, y2 = 0, x2 = 0, y3 = 0, x3 = 0;

    fscanf(stdin, "%d", &y1);
    fscanf(stdin, "%d", &x1);
    fscanf(stdin, "%d", &y2);
    fscanf(stdin, "%d", &x2);
    fscanf(stdin, "%d", &y3);
    fscanf(stdin, "%d", &x3);

    line(infoh, pixel_matrix, pencil, y1, x1, y2, x2);
    line(infoh, pixel_matrix, pencil, y1, x1, y3, x3);
    line(infoh, pixel_matrix, pencil, y2, x2, y3, x3);
}

void fill(bmp_infoheader *infoh, int ****pixel_matrix,
unsigned char **pencil) {
    int y = 0, x = 0;

    fscanf(stdin, "%d", &y);
    fscanf(stdin, "%d", &x);

    int width = infoh->width;
    int height = infoh->height;

    // Creating a "frequency" matrix, to check which pixels to color

    int **freq = NULL;
    freq = malloc(height * sizeof(int*));
    for (int i = 0; i < height; i++)
        freq[i] = malloc(width * sizeof(int));

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            freq[i][j] = 0;

    freq[x][y] = 1;

    int replaced = 1;

    do {
    replaced = 0;

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            if (freq[i][j] == 1) {
                if (i + 1 < height) {
                    if (freq[i + 1][j] == 0) {
                if ((*pixel_matrix)[i + 1][j][0] == (*pixel_matrix)[x][y][0] &&
                    (*pixel_matrix)[i + 1][j][1] == (*pixel_matrix)[x][y][1] &&
                    (*pixel_matrix)[i + 1][j][2] == (*pixel_matrix)[x][y][2]) {
                            freq[i + 1][j] = 1;
                            replaced = 1;
                        }
                    }
                }
                if (i - 1 >= 0) {
                    if (freq[i - 1][j] == 0) {
                if ((*pixel_matrix)[i - 1][j][0] == (*pixel_matrix)[x][y][0] &&
                    (*pixel_matrix)[i - 1][j][1] == (*pixel_matrix)[x][y][1] &&
                    (*pixel_matrix)[i - 1][j][2] == (*pixel_matrix)[x][y][2]) {
                            freq[i - 1][j] = 1;
                            replaced = 1;
                        }
                    }
                }
                if (j + 1 < width) {
                    if (freq[i][j + 1] == 0) {
                if ((*pixel_matrix)[i][j + 1][0] == (*pixel_matrix)[x][y][0] &&
                    (*pixel_matrix)[i][j + 1][1] == (*pixel_matrix)[x][y][1] &&
                    (*pixel_matrix)[i][j + 1][2] == (*pixel_matrix)[x][y][2]) {
                            freq[i][j + 1] = 1;
                            replaced = 1;
                        }
                    }
                }
                if (j - 1 >= 0) {
                    if (freq[i][j - 1] == 0) {
                if ((*pixel_matrix)[i][j - 1][0] == (*pixel_matrix)[x][y][0] &&
                    (*pixel_matrix)[i][j - 1][1] == (*pixel_matrix)[x][y][1] &&
                    (*pixel_matrix)[i][j - 1][2] == (*pixel_matrix)[x][y][2]) {
                            freq[i][j - 1] = 1;
                            replaced = 1;
                        }
                    }
                }
            }
    } while (replaced == 1);

    // Coloring the pixels

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            if (freq[i][j] == 1) {
                for (int k = 0; k < 3; k++)
                    (*pixel_matrix)[i][j][k] = (*pencil)[k + 1];
            }
    for (int i = 0; i < height; i++)
        free(freq[i]);
    free(freq);
}

int main() {
    char *command = malloc(BUFFER * sizeof(char));

    bmp_fileheader fileh;
    bmp_infoheader infoh;

    int ***pixel_matrix = NULL;
    int openmatrix = 0;  // 1 if matrix is malloc'd, 0 else

    unsigned char *pencil = malloc(4 * sizeof(unsigned char));
    pencil[0] = 1;

    while (1) {
        fscanf(stdin, "%s", command);

        if (!strcmp(command, "save")) {
            char *fisier = malloc(BUFFER * sizeof(char));
            fscanf(stdin, "%s", fisier);
            save(fisier, &fileh, &infoh, &pixel_matrix);
            free(fisier);
        } else if (!strcmp(command, "edit")) {
            char *fisier = malloc(BUFFER * sizeof(char));
            fscanf(stdin, "%s", fisier);
            edit(fisier, &fileh, &infoh, &pixel_matrix);
            openmatrix = 1;
            free(fisier);
        } else if (!strcmp(command, "insert")) {
            char *fisier = malloc(BUFFER * sizeof(char));
            fscanf(stdin, "%s", fisier);

            insert(fisier, &fileh, &infoh, &pixel_matrix);
            free(fisier);
        } else if (!strcmp(command, "set")) {
            set(&pencil);
        } else if (!strcmp(command, "draw")) {
            char *draw_command = malloc(BUFFER * sizeof(char));
            fscanf(stdin, "%s", draw_command);

            if (!strcmp(draw_command, "line")) {
                int y1 = 0, x1 = 0, y2 = 0, x2 = 0;

                fscanf(stdin, "%d", &y1);
                fscanf(stdin, "%d", &x1);
                fscanf(stdin, "%d", &y2);
                fscanf(stdin, "%d", &x2);

                line(&infoh, &pixel_matrix, &pencil, y1, x1, y2, x2);
            } else if (!strcmp(draw_command, "rectangle")) {
                rectangle(&infoh, &pixel_matrix, &pencil);
            } else if (!strcmp(draw_command, "triangle")) {
                triangle(&infoh, &pixel_matrix, &pencil);
            }
            free(draw_command);
        } else if (!strcmp(command, "fill")) {
            fill(&infoh, &pixel_matrix, &pencil);
        } else if (!strcmp(command, "quit")) {
            if (openmatrix) {
                int width = infoh.width;
                int height = infoh.height;
                int padding = (4 - ((width * 3) % 4)) % 4;

                for (int i = 0; i < height; i++) {
                    for (int j = 0; j < width + padding; j++)
                        free(pixel_matrix[i][j]);
                    free(pixel_matrix[i]);
                }
                free(pixel_matrix);
            }
            free(command);
            free(pencil);
            return 0;
        }
    }

    return 0;
}
