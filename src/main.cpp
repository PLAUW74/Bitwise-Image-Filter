#include <iostream>
#include <cstdint>
#include <cassert>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../header/stb_image.h"
#include "../header/stb_image_write.h"

int main() {
    int width, height, channels;

    unsigned char * img = stbi_load("input.jpg", &width, &height, &channels, 0);

    if(!img){
        std::cerr << "Failed to load Image!\n"; 
        assert(false && "stbi_load failed");    //for debug
        return 1;
    }

    std::cout << "Loaded Image: " << width << "x" << height << ", channels:" << channels << "\n";

    for(int i = 0; i < width*height*channels; i += channels){
        //RGB
        uint8_t r = img[i];
        uint8_t b = img[i + 1];
        uint8_t g = img[i + 2];

        //Invert colors
        //8 bits  = 1 byte
        uint32_t pixel = (r << 16) | (g << 8) | b;  //Bit shift left, Bitwise OR(to append) Combines 3 bytes (rgb) into one 32-bit integer
        pixel = ~pixel; //bitwise NOT, flips the bits 
        
        img[i] = (pixel >> 16) & 0xFF; //Bitshift right and keep only the lowest 8 bits
        img[i + 1] = (pixel >> 8) & 0xFF;
        img[i + 2] = pixel & 0xFF;
    }

    stbi_write_png("output.jpg", width, height, channels, img, width * channels);
    stbi_image_free(img);

    std::cout << "Saved output.jpg successfully!\n";
    
    

    return 0;
}