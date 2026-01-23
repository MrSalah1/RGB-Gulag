#ifndef IMAGE_CLASS_H
#define IMAGE_CLASS_H

#include <iostream>
#include <vector>
#include <string>
#include <cstring> 
#include <algorithm>

// declarations only
#include "stb_image.h"
#include "stb_image_write.h"

class Image {
public:
    int width = 0;
    int height = 0;
    int channels = 3;
    unsigned char* imageData = nullptr;

    Image() : width(0), height(0), channels(3), imageData(nullptr) {}

    Image(std::string filename) {
        if (!loadNewImage(filename)) {
            std::cerr << "Error loading image: " << filename << std::endl;
        }
    }

    Image(int w, int h) : width(w), height(h), channels(3) {
        imageData = (unsigned char*)malloc(width * height * channels);
        if (imageData) {
            std::memset(imageData, 0, width * height * channels);
        }
    }

    Image(const Image& other) : width(other.width), height(other.height), channels(other.channels) {
        imageData = (unsigned char*)malloc(width * height * channels);
        if (imageData && other.imageData) {
            std::memcpy(imageData, other.imageData, width * height * channels);
        }
    }

    Image& operator=(const Image& other) {
        if (this != &other) {
            if (imageData) stbi_image_free(imageData);
            width = other.width;
            height = other.height;
            channels = other.channels;
            imageData = (unsigned char*)malloc(width * height * channels);
            if (imageData && other.imageData) {
                std::memcpy(imageData, other.imageData, width * height * channels);
            }
        }
        return *this;
    }

    ~Image() {
        if (imageData) stbi_image_free(imageData);
    }

    // Support for img(x, y, c) syntax
    unsigned char& operator()(int x, int y, int c) {
        static unsigned char dummy = 0;
        if (x < 0 || x >= width || y < 0 || y >= height || c < 0 || c >= channels) return dummy;
        return imageData[(y * width + x) * channels + c];
    }
    
    unsigned char operator()(int x, int y, int c) const {
        if (x < 0 || x >= width || y < 0 || y >= height || c < 0 || c >= channels) return 0;
        return imageData[(y * width + x) * channels + c];
    }

    bool loadNewImage(const std::string& filename) {
        if (imageData) {
            stbi_image_free(imageData);
            imageData = nullptr;
        }
        imageData = stbi_load(filename.c_str(), &width, &height, &channels, 3);
        channels = 3; 
        return imageData != nullptr;
    }

    bool saveImage(const std::string& filename) {
        const char* ext = strrchr(filename.c_str(), '.');
        if (!ext) return false;

        int success = 0;
        if (strcmp(ext, ".png") == 0) {
            success = stbi_write_png(filename.c_str(), width, height, 3, imageData, width * 3);
        } else if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0) {
            success = stbi_write_jpg(filename.c_str(), width, height, 3, imageData, 100);
        } else if (strcmp(ext, ".bmp") == 0) {
            success = stbi_write_bmp(filename.c_str(), width, height, 3, imageData);
        } else if (strcmp(ext, ".tga") == 0) {
            success = stbi_write_tga(filename.c_str(), width, height, 3, imageData);
        }
        return success != 0;
    }
    
    bool isValidFilename(const std::string& filename) {
        const char* ext = strrchr(filename.c_str(), '.');
        if (!ext) return false;
        return (strcmp(ext, ".png") == 0 || strcmp(ext, ".jpg") == 0 || 
                strcmp(ext, ".bmp") == 0 || strcmp(ext, ".tga") == 0);
    }
    
    // Legacy support
    unsigned char getPixel(int x, int y, int c) const { return (*this)(x,y,c); }
    void setPixel(int x, int y, int c, unsigned char val) { (*this)(x,y,c) = val; }
};

#endif // IMAGE_CLASS_H