/*
Hello and welcome to RGB-gulag !
This program offers multiple filters that user can apply on images
1-Gray filter    (N.B:the numeration of filters differ from the assignment doc)
2-Black and white filter
3-Invert Colors
4-Flip Image filter
5-Rotation filter
Team details:
Abanob Ehab (20240001),Omar abdelsamad(20240377), Ahmed Salah(20240738)
enrolled in S34
Filter 1 designed by Abanob 0001
Filter 2,4 designed by Omar 0377
Filter 3,5 designed by Ahmed 0738
*/
#include <iostream>
#include <string>
#include "Image_Class.h"
using namespace std;
void Greet() {
    cout<<"Welcome to RBG Gulag\n";
    cout<<"Please enter the file name :)\n";
}
void Invert_color(Image &img) {
    for (int i=0;i<img.height;i++) {
        for (int j=0;j<img.width;j++) {
            for (int k=0;k<img.channels;k++) {
                unsigned char og_val=img(j,i,k);
                unsigned char inverted_val=255-og_val;
                img(j,i,k)=inverted_val;
            }
        }
    }
}
void Rotate_img(Image &img,char n) {
    if (n=='a') {
        Image new_img(img.height, img.width);

        for (int y = 0; y < img.height; y++) {
            for (int x = 0; x < img.width; x++) {
                for (int z=0;z<img.channels;z++) {
                    unsigned char p =img(x,y,z);
                    new_img(img.height-1-y,x,z)=p;
                }
            }
        }
        img = new_img;
    }
    else if (n=='b') {
        Image new_img(img.width,img.height);
        for (int y=0;y<img.height;y++) {
            for (int x=0;x<img.width;x++) {
                for (int z=0;z<img.channels;z++) {
                    unsigned char p2=img(x,y,z);
                    new_img(img.width-1-x,img.height-1-y,z)=p2;
                }
            }
        }
        img=new_img;
    }
    else if (n == 'c') { // 270° clockwise=90 counter
        Image new_img(img.height, img.width);

        for (int y = 0; y < img.height; y++) {
            for (int x = 0; x < img.width; x++) {
                for (int z = 0; z < img.channels; z++) {
                    unsigned char p3 = img(x, y, z);
                    new_img(y, img.width - 1 - x, z) = p3;
                }
            }
        }

        img = new_img;
    }
}
void grayscale(Image& image) {
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
}
void Convert_To_Black_And_White(Image &img) {
    for (int i = 0; i < img.height; i++) {
        for (int j = 0; j < img.width; j++) {
            unsigned char r = img(j, i, 0);
            unsigned char g = img(j, i, 1);
            unsigned char b = img(j, i, 2);
            unsigned char gray = (r + g + b) / 3;
            unsigned char Black_And_White = (gray > 128) ? 255 : 0;
            for (int k = 0; k < img.channels; k++) {
                img(j, i, k) = Black_And_White;
            }
        }
    }
}
void Flip_Horizontal(Image &img) {
    for (int i = 0; i < img.height; i++) {
        for (int j = 0; j < img.width / 2; j++) {
            for (int k = 0; k < img.channels; k++) {
                unsigned char temp = img(j, i, k);
                img(j, i, k) = img(img.width - 1 - j, i, k);
                img(img.width - 1 - j, i, k) = temp;
            }
        }
    }
}
void Flip_Vertical(Image &img) {
    for (int i = 0; i < img.height / 2; i++) {
        for (int j = 0; j < img.width; j++) {
            for (int k = 0; k < img.channels; k++) {
                unsigned char temp = img(j, i, k);
                img(j, i, k) = img(j, img.height - 1 - i, k);
                img(j, img.height - 1 - i, k) = temp;
            }
        }
    }
}
int main() {
    Image current_image;
    string filename;
    char choice;
    Greet();
    cin>>filename;
    current_image.loadNewImage(filename);
    do {
        cout<<"\n--- Main Menu ---\n";

        cout<<" To load a new image enter l\n";
        cout<<" To apply gray scale filter enter 1\n";
        cout<<" To apply Black and white filter enter 2 \n";
        cout<<" To apply Invert Filter enter 3\n";
        cout<<" To apply Flip filter enter 4\n";
        cout<<" To apply rotation filter enter 5\n";
        cout<<" To save the image enter s\n";
        cout<<" To exit the program enter x\n";
        cout<<" Please enter your choice : ";
        cin>>choice;
        switch (choice) {
            case 'l':
                cout<<"Enter the name of the new image file to load: ";
            cin>>filename;
            if (current_image.loadNewImage(filename)) {
                cout<<"New image loaded successfully.\n";
            }
            else {
                cout << "Error: Failed to load the new image. Keeping the current image.\n";
            }
              break;
            case '1' :
              grayscale(current_image);
              cout<<"Gray scale filter applied succesfully\n";
              break;
            case '2':
               Convert_To_Black_And_White(current_image);
               cout<<"Image converted to black and white successfully.\n";
                  break;
            case '3':
               Invert_color(current_image);
               cout<<"Invert colors filter applied succesfully\n";
            break;
            case '4' :
                cout<<"Horizontal or Vertical?\n";
                cin>>choice;
                if(choice == 'H') {
                Flip_Horizontal(current_image);
                } else {
                Flip_Vertical(current_image);
                 }
            cout<<"Image flipped successfully";
            break;
            case '5':
                cout<<"Degree of rotation? 90 enter 'a',180 'b',270 'c'.";
                char n;
                cin>>n;
                Rotate_img(current_image,n);
                break;

            case 's': {
                cout<<"Enter the name,extension of the img u want to save:\n";
                cin>>filename;
                int s1=filename.size();
                string extension= filename.substr(s1-3);

                if (extension=="jpg" ||extension=="bmp"||extension=="png" ) {
                    if (current_image.saveImage(filename)) {
                        cout << "Image saved successfully.\n";
                    } else {
                        cout << "Error: Failed to save the image.\n";
                    }
                } else {
                    cout<<"Please enter a supported extension!\n";
                }
                break;
            }
            case 'x':
                cout<< "Exiting program.\n";
            break;
            default:
                cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
        while (choice !='x');
    return 0;
}
