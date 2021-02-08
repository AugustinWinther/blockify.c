// Define which sleep function to use based on OS
// Credit: Dženan (https://stackoverflow.com/a/15861509/8437578)
#ifdef _WINDOWS
    #include <windows.h>
#else
    #include <unistd.h>
    #define Sleep(x) usleep((x)*1000)
#endif

// Standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Third party Libraries
#define STB_IMAGE_IMPLEMENTATION
#define STBI_MAX_DIMENSIONS 20000
#define STBI_ONLY_PNG
#include "include/stb_image.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "include/stb_image_resize.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "include/stb_image_write.h"

int main(int argc, char* argv[])  {
    
    // Check if argument is passed
    if (argc < 2){
        printf("ERROR: No input image...\n");
        Sleep(3000);
        exit(1);
    }

    char* inputImage = argv[1];
    char* imageType = inputImage + (strlen(inputImage) - 4);  // Credit: Baptiste E. Prunier 
                                                              // https://bit.ly/2MZNq66
    if (strcmp(imageType, ".png") != 0){
        printf("ERROR: Unsupported file type...\n");
        printf("       Please use PNG\n");
        Sleep(5000);
        exit(1);
    }

    // Load inputImage into memory
    int width, height, channels;
    unsigned char* inImage = stbi_load(inputImage, &width, &height, &channels, 0);
    
    if(inImage == NULL) {
        printf("ERROR: Couldn't load image...\n");
        exit(1);
    }

    printf("INFO: Loaded image: %s\n", inputImage);
    printf("            Width : %d px\n", width);
    printf("           Height : %d px\n", height);
    printf("         Channels : %d\n\n", channels);

    // Create blockified resolution
    int blockHeight = 194;  // Max block height (256) - sea level (62)
    int blockWidth = round(width * ((float)blockHeight / height));  // Keeps ratio
    printf("INFO: Blockified resolution!\n");
    printf("      Block Width : %d blocks\n", blockWidth);
    printf("     Block Height : %d blocks\n\n", blockHeight);

    // Allocate output image variables memory
    char* outImage = (unsigned char *) malloc(blockWidth * blockHeight * channels);

    // Resize input image to blockified resolution
    stbir_resize_uint8(inImage , width , height , 0,
                       outImage, blockWidth, blockHeight, 0, channels);
    printf("INFO: Resized image!\n\n");

    // Save modified image
    stbi_write_png("blockifiy.png", blockWidth, blockHeight, channels, outImage, blockWidth * channels);    
    printf("INFO: Saved resized image!\n\n");              

    Sleep(5000);
}