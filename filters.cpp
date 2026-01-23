#include "filters.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

void Greet() {
    cout << "Welcome to RGB Gulag\n";
}

void Invert_color(Image &img) {
    for (int i=0;i<img.height;i++) {
        for (int j=0;j<img.width;j++) {
            for (int k=0;k<img.channels;k++) {
                img(j,i,k) = 255 - img(j,i,k);
            }
        }
    }
}

void Resize_Image(Image &img, int newWidth, int newHeight) {
    Image resized(newWidth, newHeight);
    double x_ratio = static_cast<double>(img.width) / newWidth;
    double y_ratio = static_cast<double>(img.height) / newHeight;

    for(int i=0; i<newHeight; i++) {
        for(int j=0; j<newWidth; j++) {
            int NewX = static_cast<int>(j * x_ratio);
            int NewY = static_cast<int>(i * y_ratio);
            for(int k=0; k<img.channels; k++) {
                resized(j, i, k) = img(NewX, NewY, k);
            }
        }
    }
    img = resized;
}

void adjust_brightness(Image& image, float percentage, bool lighten) {
    float factor = lighten ? (1.0f + percentage/100.0f) : (1.0f - percentage/100.0f);
    for (int i =0; i < image.width; ++i) {
        for (int j = 0;j < image.height; ++j) {
            for (int k= 0; k < 3; ++k) {
                int value = static_cast<int>(image(i, j, k) * factor);
                image(i, j, k) = static_cast<unsigned char>(std::clamp(value, 0, 255));
            }
        }
    }
}

void process_image(Image& image) {
    // Empty stub: GUI handles logic
}

void averageTwoImages(Image& image, Image& image2) {
    if (image.width != image2.width || image.height != image2.height) {
        Resize_Image(image2, image.width, image.height);
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for(int k=0; k<3; ++k) {
                image(i,j,k) = (image(i,j,k) + image2(i,j,k)) / 2;
            }
        }
    }
}

void applySunlightFilter(Image &image, double redFactor, double greenFactor, double blueFactor) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            image(i,j,0) = min(255, max(0, int(image(i,j,0) * redFactor)));
            image(i,j,1) = min(255, max(0, int(image(i,j,1) * greenFactor)));
            image(i,j,2) = min(255, max(0, int(image(i,j,2) * blueFactor)));
        }
    }
}

void edge_detection(Image& image) {
    vector<vector<unsigned int>> Z(image.width ,vector<unsigned int>(image.height));
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = (image(i,j,0) + image(i,j,1) + image(i,j,2)) / 3;
            Z[i][j] = avg;
        }
    }
    for (int i = 0; i < image.width-1; ++i) {
        for (int j = 0; j < image.height-1; ++j) {
            unsigned int edge = abs((int)Z[i+1][j] - (int)Z[i][j]) + abs((int)Z[i][j+1] - (int)Z[i][j]);
            unsigned char c = (edge > 50) ? 0 : 255;
            for (int k = 0; k < 3; ++k) image(i, j, k) = c;
        }
    }
}

void Rotate_img(Image &img, char n) {
    if (n=='a') { // 90
        Image new_img(img.height, img.width);
        for (int y = 0; y < img.height; y++)
            for (int x = 0; x < img.width; x++)
                for (int z=0;z<img.channels;z++)
                    new_img(img.height-1-y,x,z) = img(x,y,z);
        img = new_img;
    } else if (n=='b') { // 180
        Image new_img(img.width,img.height);
        for (int y=0;y<img.height;y++)
            for (int x=0;x<img.width;x++)
                for (int z=0;z<img.channels;z++)
                    new_img(img.width-1-x,img.height-1-y,z) = img(x,y,z);
        img = new_img;
    } else if (n == 'c') { // 270
        Image new_img(img.height, img.width);
        for (int y = 0; y < img.height; y++)
            for (int x = 0; x < img.width; x++)
                for (int z = 0; z < img.channels; z++)
                    new_img(y, img.width - 1 - x, z) = img(x, y, z);
        img = new_img;
    }
}

void filterGrayscale(Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = (image(i,j,0) + image(i,j,1) + image(i,j,2)) / 3;
            for (int k = 0; k < 3; ++k) image(i, j, k) = avg;
        }
    }
}

void Convert_To_Black_And_White(Image &img) {
    for (int i = 0; i < img.height; i++) {
        for (int j = 0; j < img.width; j++) {
            unsigned char gray = (img(j,i,0) + img(j,i,1) + img(j,i,2)) / 3;
            unsigned char bw = (gray > 128) ? 255 : 0;
            for (int k = 0; k < 3; k++) img(j, i, k) = bw;
        }
    }
}

void filterFlipHorizontal(Image &img) {
    for (int i = 0; i < img.height; i++) {
        for (int j = 0; j < img.width / 2; j++) {
            for (int k = 0; k < 3; k++) {
                swap(img(j, i, k), img(img.width - 1 - j, i, k));
            }
        }
    }
}

void Flip_Vertical(Image &img) {
    for (int i = 0; i < img.height / 2; i++) {
        for (int j = 0; j < img.width; j++) {
            for (int k = 0; k < 3; k++) {
                swap(img(j, i, k), img(j, img.height - 1 - i, k));
            }
        }
    }
}

void Add_Frame(Image &img, char f, char color_choice) {
    const int t=20;
    unsigned char r=255, g=255, b=255;
    if (color_choice=='r') {r=255; g=0; b=0;}
    else if (color_choice=='b') {r=0; g=0; b=255;}
    else if (color_choice=='g') {r=0; g=255; b=0;}

    Image new_img(img.width+40, img.height+40);
    for (int y=0; y<new_img.height; y++) {
        for (int x=0; x<new_img.width; x++) {
            if (x < t || x >= new_img.width - t || y < t || y >= new_img.height - t) {
                if (f=='1') {
                    new_img(x,y,0)=r; new_img(x,y,1)=g; new_img(x,y,2)=b;
                } else {
                    if ((x/10 + y/10)%2) {
                        new_img(x,y,0)=r; new_img(x,y,1)=g; new_img(x,y,2)=b;
                    } else {
                        new_img(x,y,0)=255; new_img(x,y,1)=255; new_img(x,y,2)=255;
                    }
                }
            } else {
                int ox = x-20, oy = y-20;
                if(ox >=0 && ox < img.width && oy >=0 && oy < img.height) {
                    for(int k=0; k<3; ++k) new_img(x,y,k) = img(ox, oy, k);
                }
            }
        }
    }
    img = new_img;
}

void Oil_filter(Image &img) {
    Image new_img(img.width,img.height);
    const int intensity_level = 20;
    for (int y=0; y<img.height; y++) {
        for (int x=0; x<img.width; x++) {
            int count[20] = {0};
            int sum_r[20] = {0};
            int sum_g[20] = {0};
            int sum_b[20] = {0};

            for (int dy=-3; dy<=3; dy++) {
                for (int dx=-3; dx<=3; dx++) {
                    int ny= y+dy, nx= x+dx;
                    if (nx>=0 && nx < img.width && ny >= 0 && ny < img.height) {
                        unsigned char r = img(nx, ny, 0);
                        unsigned char g = img(nx, ny, 1);
                        unsigned char b = img(nx, ny, 2);
                        int cur_int = ((r+g+b)/3 * intensity_level) / 255;
                        if(cur_int > 19) cur_int = 19;

                        count[cur_int]++;
                        sum_r[cur_int]+=r; sum_g[cur_int]+=g; sum_b[cur_int]+=b;
                    }
                }
            }
            int max_c = 0, max_i = 0;
            for(int i=0; i<20; ++i) {
                if(count[i] > max_c) { max_c = count[i]; max_i = i; }
            }
            if(max_c == 0) max_c = 1;
            new_img(x,y,0) = sum_r[max_i]/max_c;
            new_img(x,y,1) = sum_g[max_i]/max_c;
            new_img(x,y,2) = sum_b[max_i]/max_c;
        }
    }
    img = new_img;
}

void box_blur(Image &img , int m) {
    Image new_img(img.width,img.height);
    int r = max(1, m/2);
    for (int y=0; y<img.height; y++) {
        for (int x=0; x<img.width; x++) {
            for (int c=0; c<3; c++) {
                int sum=0, count=0;
                for (int i=-r; i<=r; i++) {
                    for (int j=-r; j<=r; j++) {
                        int nx=x+j, ny=y+i;
                        if (nx>=0 && nx<img.width && ny>=0 && ny<img.height) {
                            sum += img(nx,ny,c);
                            count++;
                        }
                    }
                }
                new_img(x,y,c) = sum/count;
            }
        }
    }
    img = new_img;
}

void Crop_Image(Image &img, int X, int Y, int w, int h) {
    if(X < 0) X=0; if(Y < 0) Y=0;
    if(X+w > img.width) w = img.width-X;
    if(Y+h > img.height) h = img.height-Y;

    Image cropped(w, h);
    for(int i=0; i<h; i++){
        for(int j=0; j<w; j++){
            for(int k=0; k<3; k++){
                cropped(j,i,k) = img(j+X, i+Y, k);
            }
        }
    }
    img = cropped;
}