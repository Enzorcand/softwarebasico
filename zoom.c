#include <stdlib.h>
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

    entry = read_ppm("/workspaces/softwarebasico/lena.ppm", image_in);
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

    int j = 0;
    for(int k = 0; k < data.height; k++){    
        int i = 0;
        for(int m = 0; m < data.width; m++){
            int red = image_in->pix[k*image_in->width + m].r;
            int green = image_in->pix[k*image_in->width + m].g;
            int blue = image_in->pix[k*image_in->width + m].b;
            for (int l = 0; l < 3; l++){
                for(int n = 0; n < 3; n++){
                    image_out->pix[(j)*image_in->width + i + n].r = red;
                    image_out->pix[(j)*image_in->width + i + n].g = green;
                    image_out->pix[(j)*image_in->width + i + n].b = blue;
                }
            }
            i += 3;
        }
        j += 9;
    }

    /* modificando o valor do pixel [20, 50] (posic¸˜ao X, Y) */
    //image->pix[50 * image->width + 20].r = 255;
    //image->pix[50 * image->width + 20].g = 255;
    //image->pix[50 * image->width + 20].b = 255;

    entry = write_ppm("copy.ppm", image_out);
    if( entry < 0)
    {
        printf("write_ppm error");
        return 0;
    }
}

{
	if (image->pix) {
		free(image->pix);
		
		return 0;
	}
	
	return -1;
}