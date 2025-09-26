// A demo for converting image to gray scale

#include <iostream>
using namespace std;
#include "Image_Class.h"
void Flip_img(Image &img, char flip) {
    Image new_img1(img.width, img.height, img.channels);

    for (int y = 0; y < img.height;y++) {
        for (int x = 0; x < img.width; x++) {
            int nx = x;
            int ny= y;

            if (flip== 'h') {
                nx = img.width - 1 - x;
            }
      else if (flip== 'v') {
                ny = img.height - 1 - y;
            }
                else if (flip == 'b') {
                nx = img.width - 1 - x;
                ny = img.height - 1 - y;
            }

         for (int z = 0; z < img.channels; z++) {
                new_img1(nx, ny, z) = img(x, y, z);
            }
        }
    }

    img = new_img1;
}


int main() {
    string filename;
    cout << "Pls enter colored image name to turn to gray scale: ";
    cin >> filename;

    Image image(filename);

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned  int avg = 0; // Initialize average value

            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k); // Accumulate pixel values
            }

            avg /= 3; // Calculate average

            // Set all channels to the average value
            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }

    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";

    cin >> filename;
    image.saveImage(filename);

    return 0;
}
