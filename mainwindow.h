#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QPixmap>
#include "Image_Class.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    private slots:
        void onLoadImage();
    void onSaveImage();
    void onResetImage();

    void filterGrayscale();
    void filterFlipHorizontal();
    void Flip_Vertical();
    void Greet();
    void Oil_filter();
    void box_blur();
    void Invert_color();
    void Rotate_img();
    void Add_Frame();
    void process_image();
    void applySunlightFilter();
    void adjust_brightness();
    void resizeImage();
    void averageTwoImages();
    void edge_detection();
    void Convert_To_Black_And_White();
    void Crop_Image();

private:
    QWidget *centralWidget;
    QLabel *originalLabel;
    QLabel *processedLabel;
    QScrollArea *originalScroll;
    QScrollArea *processedScroll;
    QString currentFilePath;
    Image *originalImage = nullptr;
    Image *processedImage = nullptr;

    void setupUi();
    void updateDisplay();
    QImage convertToQImage(Image *img);
};

#endif // MAINWINDOW_H