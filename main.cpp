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
        cout<<" To load a new image enter 1\n";
        cout<<" To convert to a Black and White filter enter 2\n";
        cout<<" To apply Invert Filter enter 3\n";
        cout<<" To apply Flip Filter enter 4\n";
        cout<<" To save the image enter s\n";
        cout<<" To exit the program enter x\n";
        cout<<" Please enter your choice : ";
        cin>>choice;
        switch (choice) {
            case '1':
                cout<<"Enter the name of the new image file to load: ";
            cin>>filename;
            if (current_image.loadNewImage(filename)) {
                cout<<"New image loaded successfully.\n";
            }
            else {
                cout << "Error: Failed to load the new image. Keeping the current image.\n";
            }
                break;
            case '2':
                Convert_To_Black_And_White(current_image);
                cout<<"Image converted successfully.\n";
                break;
            case '3':
                Invert_color(current_image);
            cout<<"Invert colors filter applied succesfully\n";
                break;
            case '4':
                cout<<"Horizontal or Vertical?\n";
                cin>>choice;
                if(choice == 'H') {
                    Flip_Horizontal(current_image);
                }else {
                    Flip_Vertical(current_image);
                }
                cout<<"Image flipped successfully";
                break;
            case 's':
                cout<<"Enter the name of the img u want to save:\n";
            cin>>filename;
            if (current_image.saveImage(filename)) {
                cout << "Image saved successfully.\n";
            } else {
                cout << "Error: Failed to save the image.\n";
            }
                break;
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
