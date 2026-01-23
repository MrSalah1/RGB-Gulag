/*
Hello and welcome to RGB-Gulag!
This program provides multiple filters that users can apply to images.

Available Filters:
1- Gray Filter
2- Black and White Filter
3- Invert Colors
4- Flip Image Filter
5- Rotation Filter
6- Frame Filter
7- Image Cropping
8- Image Resizing
9- Averaging Two Images
10- Adding Sunlight to an Image
11- Changing Image Brightness
12- Blurring an Image
13- Edge Detection Filter
14- Oil Paint Filter

Team Details:
Abanob Ehab (20240001)
Omar Abdelsamad (20240377)
Ahmed Salah (20240738)
Section: S32

Work Breakdown:
Abanob (20240001) - Filters 1, 9, 10, 11, 13
Omar (20240377)   - Filters 2, 4, 7, 8
Ahmed (20240738)  - Filters 3, 5, 6, 12, 14

Video Demo: <https://youtu.be/EN-dfKWHtdU>
Shared Document: <https://1drv.ms/w/c/af63ed7cb1700daf/EU2FHIMFTUlHvSXDyH4fWZ0BSLWOpkQhTt9yisEAKKZlGQ?e=bFe0Gj>
Google Drive link : <https://drive.google.com/drive/folders/1W7Ndu0bbzhydXtwNZHSCngnIkQrnieBm?usp=drive_link>
github repository link: <https://github.com/MrSalah1/RGB-Gulag.git>
*/
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
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
Image resizeImage(const Image& input, int newWidth, int newHeight) {
    Image output(newWidth, newHeight);
    float x_ratio= input.width / static_cast<float>(newWidth);
    float y_ratio= input.height / static_cast<float>(newHeight);
    for (int i=0;i<newWidth; ++i) {
        for (int j=0;j<newHeight;++j) {
            int nearestX =static_cast<int>(i* x_ratio);
            int nearestY =static_cast<int>(j* y_ratio);
            for (int c =0;c<3;++c) {
                output(i,j,c) = input(nearestX,nearestY,c);
            }
        }
    }
    return output;
}
void adjust_brightness(Image& image, float percentage, bool lighten) {
    float factor;
    if (lighten) {
        factor = 1.0f + (percentage / 100.0f);
    } else {
        factor = 1.0f - (percentage / 100.0f);
    }

    for (int i =0; i < image.width; ++i) {
        for (int j = 0;j < image.height; ++j) {
            for (int k= 0; k < 3; ++k) {
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
            r = min(255, max(0, int(r * redFactor)));
            g = min(255, max(0, int(g * greenFactor)));
            b = min(255, max(0, int(b * blueFactor)));
            image(i, j, 0) = r;
            image(i, j, 1) = g;
            image(i, j, 2) = b;
        }
    }
}
void edge_detection(Image& image) {
    vector<vector<unsigned int>> Z(image.width ,vector<unsigned int>(image.height));
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
    else if (n == 'c') {
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
            unsigned  int avg = 0;

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
void Add_Frame(Image &img,char f,char color_choice) {
    const int thickness=20;
    unsigned char r,g,b;
    if (color_choice=='r'){r=255,g=0,b=0;}
    if (color_choice=='b'){r=0,g=0,b=255;}
    if (color_choice=='w') {
        r=255,g=255,b=255;
    }
    Image new_img(img.width+40 ,img.height+40);
    for (int y=0;y<new_img.height;y++) {
        for (int x=0;x<new_img.width;x++){
            if (x < thickness || x >= new_img.width - thickness ||
                             y < thickness || y >= new_img.height - thickness) {
                if (f=='1') {
                    new_img(x,y,0)=r;
                    new_img(x,y,1)=g;
                    new_img(x,y,2)=b;
                }
                else {
                    int pattern=(x/10 +y/10)%2;
                    if (pattern) {
                        new_img(x,y,0)=r;
                        new_img(x,y,1)=g;
                        new_img(x,y,2)=b;
                    } else {
                        new_img(x,y,0)=0;
                        new_img(x,y,1)=0;
                        new_img(x,y,2)=0;
                    }
                }
                             }
        }
    }
    for (int y =0;y < img.height;y++) {
        for (int x =0;x < img.width;x++) {
            for (int z =0;z < img.channels;z++) {
                new_img(x + 20,y+20, z) =img(x, y, z);
            }
        }
    }

    img =new_img;
}
void Oil_filter(Image &img) {
    Image new_img(img.width,img.height);
    const int radius=5;
    const int intensity_level =20;
    for (int y=0;y<img.height;y++) {
        for (int x=0;x<img.width;x++) {
            vector<int>count(20,0);
            vector<int>sum_r(20,0);
            vector<int>sum_g(20,0);
            vector<int>sum_b(20,0);
            for (int dy=-5;dy<=5;dy++) {
                for (int dx=-5;dx<=5;++dx) {
                    int new_y= y+dy;
                    int new_x= x+dx;
                    if (new_x>=0&& new_x < img.width && new_y >= 0 && new_y < img.height) {
                        unsigned char r = img(new_x, new_y, 0);
                        unsigned char g = img(new_x, new_y, 1);
                        unsigned char b = img(new_x, new_y, 2);
                        int intensity = ((r + g + b) / 3 * intensity_level) / 255;
                        if (intensity>=intensity_level){intensity =intensity_level - 1;}

                        count[intensity]++;
                        sum_r[intensity] += r;
                        sum_g[intensity] += g;
                        sum_b[intensity] += b;
                    }
                }
            }
            int max_i=max_element(count.begin(),count.end())-count.begin();
            int c=max(1,count[max_i]);
            new_img(x, y, 0) = sum_r[max_i] / c;
            new_img(x, y, 1) = sum_g[max_i] / c;
            new_img(x, y, 2) = sum_b[max_i] / c;
        }
    }
    img=new_img;
}
void box_blur(Image &img , int m) {
    Image new_img(img.width,img.height);
    for (int y=0;y<img.height;y++) {
        for (int x=0;x<img.width;x++) {
            for (int c=0;c<img.channels;c++) {
                int sum=0;
                int count=0;
                int e = m*10;
                for (int i=-e;i<=e;i++) {
                    for (int j=-e;j<=e;j++) {
                        int nx=x+j;
                        int ny=y+i;
                        if (nx>=0 && nx<img.width && ny>=0 &&ny<img.height) {
                            sum+=img(nx,ny,c);
                            count++;
                        }
                    }
                }
                new_img(x,y,c)=sum/count;
            }
        }
    }
    img=new_img;
}
void Crop_Image(Image &img) {
    int X;
    int Y;
    int cropWidth;
    int cropHeight;
    cin>>X;
    cin>>Y;
    cin>>cropWidth;
    cin>>cropHeight;
    Image cropped(cropWidth, cropHeight);
    for(int i=0;i<cropHeight;i++){
        for(int j=0;j<cropWidth;j++){
            for(int k=0;k<img.channels;k++){
                cropped(j,i,k)=img(j+X, i+Y, k);
            }
        }
    }
    img=cropped;
}
void Resize_Image(Image &img) {
    int newWidth;
    int newHeight;
    cin>>newWidth;
    cin>>newHeight;
    Image resized(newWidth, newHeight);
    double x_ratio=static_cast<double>(img.width) / newWidth;
    double y_ratio=static_cast<double>(img.height) / newHeight;
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
int main() {
    Image current_image;
    string filename;
    char choice;
    Greet();
    bool load=false;
    while (!load) {
        cin>>filename;
        /*current_image.loadNewImage(filename);*/
        try {
            if (!current_image.loadNewImage(filename)) {
                throw runtime_error("This file isn't in the project folder:"+filename);
            }
            load=true;
            cout<<"Image loaded succesfully.\n";
        } catch (const exception& e) {
            cout<<"Error: "<<e.what()<<"\n try again!\n";
        }
    }
    do {
        cout<<"\n--- Main Menu ---\n";

        cout<<" To load a new image enter l\n";
        cout<<" To apply gray scale filter enter 1\n";
        cout<<" To apply Black and white filter enter 2 \n";
        cout<<" To apply Invert Filter enter 3\n";
        cout<<" To apply Flip filter enter 4\n";
        cout<<" To apply rotation filter enter 5\n";
        cout<<" To apply a frame filter enter 6\n";
        cout<<" To Crop an image enter 7\n";
        cout<<" To resize an image enter 8\n";
        cout<<" To apply box blur filter enter 9\n";
        cout<< " To average two colored images enter a\n";
        cout<< " To add sunlight to the image enter g\n";
        cout<< " To change the brightness of the image enter c\n";
        cout<<" To apply oil paint filter enter o\n";
        cout<< " To apply edge detection enter p\n";
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
            case '6':
                cout<<"For simple frame enter 1 \n";
            cout<<"For ornamented frame enter 2\n";
            char f;
            cin>>f;
            cout<<"choose frame color :RED(r),blue(b),white(w)\n";
            char cc;
            cin>>cc;
            Add_Frame(current_image,f,cc);
            break;
            case '7':
                cout<<"Please enter the corners and the dimensions of the image:\n";
                Crop_Image(current_image);
                break;
            case '8':
                cout<<"Please enter the new dimensions\n";
                Resize_Image(current_image);
                cout<<"Image resized successfully\n";
                break;
            case '9':
                int m;
                cout<<"Enter blur level from 1-9:\n";
                cin>>m;
                box_blur(current_image,m);
                cout<<"Image blurred succesfully\n";
                break;
            case 'a':
                averageTwoImages(current_image);
                cout << "Done.\n";
                break;

            case 'g':
                applySunlightFilter(current_image);
                cout << "Done.\n";
                break;
            case 'c':
                process_image(current_image);
                cout << "Done.\n";
                break;
            case 'p':
                edge_detection(current_image);
                cout << "Done.\n";
                break;
            case 'o':
                Oil_filter(current_image);
            cout<<"Oil filter applied succesfully\n";
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
