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
        cout<<" To apply Invert Filter enter 3\n";
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
            case '3':
                Invert_color(current_image);
            cout<<"Invert colors filter applied succesfully\n";
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
