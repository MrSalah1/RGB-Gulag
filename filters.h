#ifndef FILTERS_H
#define FILTERS_H

#include "Image_Class.h"

// Basic
void Greet();
void filterGrayscale(Image& img);
void Convert_To_Black_And_White(Image &img);
void Invert_color(Image &img);

// Geometry
void filterFlipHorizontal(Image &img);
void Flip_Vertical(Image &img);
void Rotate_img(Image &img, char n);
void Crop_Image(Image &img, int x, int y, int w, int h); // Takes args now
void Resize_Image(Image &img, int newW, int newH);       // Takes args now

// Artistic
void adjust_brightness(Image& image, float percentage, bool lighten);
void applySunlightFilter(Image &image, double redFactor = 1.1, double greenFactor = 1.04, double blueFactor = 0.7);
void Oil_filter(Image &img);
void box_blur(Image &img, int m);
void Add_Frame(Image &img, char f, char color_choice);
void edge_detection(Image& image);
void averageTwoImages(Image& image, Image& image2);

// Helper
void process_image(Image& image);

#endif // FILTERS_H