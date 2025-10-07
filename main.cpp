#include <iostream>
#include <string>
#include "Image_Class.h"
#include "vector"
using namespace std;

void Greet() {
    cout << "Welcome to RBG Gulag\n";
    cout << "Please enter the file name :)\n";
}

void Invert_color(Image &img) {
    for (int i = 0; i < img.height; i++) {
        for (int j = 0; j < img.width; j++) {
            for (int k = 0; k < img.channels; k++) {
                unsigned char og_val = img(j, i, k);
                unsigned char inverted_val = 255 - og_val;
                img(j, i, k) = inverted_val;
            }
        }
    }
}

void grayscale(Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k);
            }
            avg /= 3;
            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }
}

Image resizeImage(const Image& input, int newWidth, int newHeight) {
    Image output(newWidth, newHeight);
    float x_ratio = input.width / static_cast<float>(newWidth);
    float y_ratio = input.height / static_cast<float>(newHeight);
    for (int i = 0; i < newWidth; ++i) {
        for (int j = 0; j < newHeight; ++j) {
            int nearestX = static_cast<int>(i * x_ratio);
            int nearestY = static_cast<int>(j * y_ratio);
            for (int c = 0; c < 3; ++c) {
                output(i, j, c) = input(nearestX, nearestY, c);
            }
        }
    }
    return output;
}

void averageTwoImages(Image& image) {
    string filename2;
    cout << "Pls enter the second colored image name to average with the current image: ";
    cin >> filename2;
    Image image2(filename2);
    if (image.width != image2.width || image.height != image2.height) {
        cout << "Images have different sizes. Resizing second image to match the first..." << endl;
        image2 = resizeImage(image2, image.width, image.height);
    }
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avgR = 0, avgG = 0, avgB = 0;
            avgR = (image(i, j, 0) + image2(i, j, 0)) / 2;
            avgG = (image(i, j, 1) + image2(i, j, 1)) / 2;
            avgB = (image(i, j, 2) + image2(i, j, 2)) / 2;
            image(i, j, 0) = avgR;
            image(i, j, 1) = avgG;
            image(i, j, 2) = avgB;
        }
    }
    cout << "Averaging complete. Use option 's' to save the result if desired.\n";
}



void applySunlightFilter(Image &image, double redFactor = 1.1, double greenFactor = 1.04, double blueFactor = 0.7) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int r = image(i, j, 0);
            int g = image(i, j, 1);
            int b = image(i, j, 2);

            // Apply adjustments with clamping
            r = min(255, max(0, int(r * redFactor)));
            g = min(255, max(0, int(g * greenFactor)));
            b = min(255, max(0, int(b * blueFactor)));

            image(i, j, 0) = r;
            image(i, j, 1) = g;
            image(i, j, 2) = b;
        }
    }
}


void adjust_brightness(Image& image, float percentage, bool lighten) {
    float factor;
    if (lighten) {
        factor = 1.0f + (percentage / 100.0f);
    } else {
        factor = 1.0f - (percentage / 100.0f);
    }

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                int value = static_cast<int>(image(i, j, k) * factor);
                if (value > 255) value = 255;
                if (value < 0) value = 0;
                image(i, j, k) = static_cast<unsigned char>(value);
            }
        }
    }
}

void process_image(Image& image) {
    char choice;
    cout << "Do you want to (l)ighten or (d)arken the image? ";
    cin >> choice;

    float percentage;
    cout << "Enter percentage (0 to 100): ";
    cin >> percentage;

    if (percentage < 0) percentage = 0;
    if (percentage > 100) percentage = 100;

    bool lighten = (choice == 'l' || choice == 'L');
    adjust_brightness(image, percentage, lighten);

}


void edge_detection(Image& image) {
    vector<vector<unsigned int>> Z(image.width , vector<unsigned int>(image.height));
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k);
            }
            avg /= 3;
            Z[i][j] = avg;
        }
    }
    for (int i = 0; i < image.width-1; ++i) {
        for (int j = 0; j < image.height-1; ++j) {
            unsigned int edge_value = abs((int)Z[i+1][j] - (int)Z[i][j]) + abs((int)Z[i][j+1] - (int)Z[i][j]);
            unsigned int color = 0;
            if (edge_value > 50) {
                color = 0;
            }
            else{
                color = 255;
            }
            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = color;
            }
        }
    }
}


int main() {
    Image current_image;
    string filename;
    char choice;

    Greet();
    cin >> filename;
    current_image.loadNewImage(filename);

    do {
        cout << "\n--- Main Menu ---\n";
        cout << " To load a new image enter 1\n";
        cout << " To apply Invert Filter enter 3\n";
        cout << " To save the image enter s\n";
        cout << " To exit the program enter x\n";
        cout << " To display the image in grayscale enter f\n";
        cout << " To average two colored images enter a\n";
        cout << " To add sunlight to the image enter g\n";
        cout << " To change the brightness of the image enter o\n";
        cout << " To apply edge detection enter p\n";
        cout << " Please enter your choice : ";
        cin >> choice;

        switch (choice) {
            case '1':
                cout << "Enter the name of the new image file to load: ";
                cin >> filename;
                if (current_image.loadNewImage(filename)) {
                    cout << "New image loaded successfully.\n";
                } else {
                    cout << "Error: Failed to load the new image. Keeping the current image.\n";
                }
                break;

            case '3':
                Invert_color(current_image);
                cout << "Invert colors filter applied successfully\n";
                break;

            case 's':
                cout << "Enter the name of the image you want to save:\n";
                cin >> filename;
                if (current_image.saveImage(filename)) {
                    cout << "Image saved successfully.\n";
                } else {
                    cout << "Error: Failed to save the image.\n";
                }
                break;

            case 'x':
                cout << "Exiting program.\n";
                break;

            case 'f':
                grayscale(current_image);
                cout << "Done.\n";
                break;


            case 'a':
                averageTwoImages(current_image);
                cout << "Done.\n";
                break;

            case 'g':
                applySunlightFilter(current_image);
                cout << "Done.\n";
                break;
            case 'o':
                process_image(current_image);
                cout << "Done.\n";
                break;
            case 'p':
                edge_detection(current_image);
                cout << "Done.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 'x');

    return 0;
}


