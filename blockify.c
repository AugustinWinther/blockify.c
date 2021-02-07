// Define which sleep function to use based on OS
// Credit: Dženan (https://stackoverflow.com/a/15861509/8437578)
#ifdef _WINDOWS
    #include <windows.h>
#else
    #include <unistd.h>
    #define Sleep(x) usleep((x)*1000)
#endif


#include <stdio.h>
#include <string.h>


int main(int argc, char* argv[])  {
    
    if (argc < 2){
        printf("ERROR: No input image...\n");
        Sleep(3000);
        exit(1);
    }

    char* inputImage = argv[1];
    char* imageType = inputImage + (strlen(inputImage) - 4);  // Credit: Baptiste E. Prunier 
                                                              // https://bit.ly/2MZNq66
    if (strcmp(imageType, ".png") != 0){
        printf("ERROR: Unsupported image type...\n");
        printf("       Please use PNG\n");
        Sleep(5000);
        exit(1);
    }

    printf("Using image: %s", inputImage);
    Sleep(5000);
}