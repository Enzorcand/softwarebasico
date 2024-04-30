#include <stdio.h>
#include <string.h>
//#include "lib_ppm.h"

struct pixel_s {
	unsigned char r, g, b;
};

struct image_s {
	int width;
	int height;
	struct pixel_s *pix;
};

int main() {

    struct image_s data;
    struct image_s *image_in = &data;
    struct image_s saida;
    struct image_s *image_out = &saida;
    int entry = 0;
    int j = 0;

    entry = read_ppm("lena.ppm", image_in);
    if(entry < 0)
    {
        printf("read_ppm error");
        return 0;
    }   

    entry = new_ppm(image_out, data.width*3, data.height*3);
    if( entry < 0)
    {
        printf("new_ppm error");
        return 0;
    }   

    int l = 0;
    for(int k = 0; k < data.height; k++){
        for(int m = 0; m < data.width; m++){
            int red = image_in->pix[k*image_in->width + m].r;
            int green = image_in->pix[k*image_in->width + m].g;
            int blue = image_in->pix[k*image_in->width + m].b;

            for(int n = 0; n < 3; n++){
                image_out->pix[k*image_in->width + n*image_in->width + l].r = red;
                image_out->pix[k*image_in->width + n*image_in->width + l].g = green;
                image_out->pix[k*image_in->width + n*image_in->width + l].b = blue;
                l++;
            }
        }
    }

    /* modificando o valor do pixel [20, 50] (posic¸˜ao X, Y) */
    //image->pix[50 * image->width + 20].r = 255;
    //image->pix[50 * image->width + 20].g = 255;
    //image->pix[50 * image->width + 20].b = 255;

    entry = write_ppm("copy.ppm", image_out);
    if( entry < 0)
    {
        printf("read_ppm error");
        return 0;
    }
}


int read_ppm(char *file, struct image_s *image)
{
	FILE *fptr;
	char *t;
	char buf[128];
	int r, d, i, j;
	struct pixel_s *img_data;
	
	fptr = fopen(file, "rb");
	if (!fptr)
		return -1;
		
	t = fgets(buf, sizeof(buf), fptr);
	if (!t)
		goto failread;
	
	if (strncmp(buf, "P6\n", 3) != 0)
		goto failread;

        do {
		t = fgets(buf, sizeof(buf), fptr);
		if (!t)
			goto failread;
				
	} while (strncmp(buf, "#", 1) == 0);
	
        r = sscanf(buf, "%u %u", &image->width, &image->height);
        if (r < 2)
		goto failread;

        r = fscanf(fptr, "%u", &d);
        if ((r < 1) || (d != 255))
		goto failread;
		
        fseek(fptr, 1, SEEK_CUR);
        
        img_data = malloc(image->width * image->height * sizeof(struct pixel_s));
        if (!img_data)
		goto failread;
        
        image->pix = img_data;
        
        for (j = 0; j < image->height; j++)
		for (i = 0; i < image->width; i++)
			fread(&img_data[j * image->width + i], 3, 1, fptr);
	
	fclose(fptr);

	return 0;
	
failread:
	fclose(fptr);
	
	return -1;
}


int write_ppm(char *file, struct image_s *image)
{
	FILE *fptr;
	int i, j;
	
	fptr = fopen(file, "wb");
	if (!fptr)
		return -1;
		
	fprintf(fptr, "P6\n%d %d\n255\n", image->width, image->height);
        for (j = 0; j < image->height; j++)
		for (i = 0; i < image->width; i++)
			fwrite(&image->pix[j * image->width + i], 3, 1, fptr);

	fclose(fptr);
	
	return 0;
}


int new_ppm(struct image_s *image, int width, int height)
{
	struct pixel_s *img_data;

	image->width = width;
	image->height = height;
	
        img_data = malloc(image->width * image->height * sizeof(struct pixel_s));
        if (!img_data)
		return -1;
        
        image->pix = img_data;
        memset(image->pix, 0, image->width * image->height * sizeof(struct pixel_s));
	
	return 0;
}


int free_ppm(struct image_s *image)
{
	if (image->pix) {
		free(image->pix);
		
		return 0;
	}
	
	return -1;
}
