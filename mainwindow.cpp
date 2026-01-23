#include "mainwindow.h"
#include "filters.h" 
#include <QScrollBar>
#include <QGroupBox>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi();
}

MainWindow::~MainWindow() {
    delete originalImage;
    delete processedImage;
}

void MainWindow::setupUi() {
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    QGroupBox *grpOriginal = new QGroupBox("Original");
    QVBoxLayout *layoutOriginal = new QVBoxLayout(grpOriginal);
    originalScroll = new QScrollArea();
    originalLabel = new QLabel("No Image Loaded");
    originalLabel->setAlignment(Qt::AlignCenter);
    originalScroll->setWidget(originalLabel);
    originalScroll->setWidgetResizable(true);
    layoutOriginal->addWidget(originalScroll);

    QGroupBox *grpProcessed = new QGroupBox("Processed");
    QVBoxLayout *layoutProcessed = new QVBoxLayout(grpProcessed);
    processedScroll = new QScrollArea();
    processedLabel = new QLabel("No Image Loaded");
    processedLabel->setAlignment(Qt::AlignCenter);
    processedScroll->setWidget(processedLabel);
    processedScroll->setWidgetResizable(true);
    layoutProcessed->addWidget(processedScroll);

    QScrollArea *controlsScroll = new QScrollArea();
    controlsScroll->setFixedWidth(300);
    controlsScroll->setWidgetResizable(true);
    QWidget *controlsContainer = new QWidget();
    QVBoxLayout *controlsLayout = new QVBoxLayout(controlsContainer);

    controlsLayout->addWidget(new QLabel("<b>File Operations</b>"));
    QPushButton *btnLoad = new QPushButton("Load Image");
    QPushButton *btnSave = new QPushButton("Save Image");
    QPushButton *btnReset = new QPushButton("Reset to Original");
    btnLoad->setStyleSheet("background-color: #4CAF50; color: white; padding: 6px;");
    controlsLayout->addWidget(btnLoad);
    controlsLayout->addWidget(btnSave);
    controlsLayout->addWidget(btnReset);
    controlsLayout->addSpacing(20);

    controlsLayout->addWidget(new QLabel("<b>Filters</b>"));
    QPushButton *btnGray = new QPushButton("Grayscale");
    QPushButton *btnBW = new QPushButton("Black & White");
    QPushButton *btnInvert = new QPushButton("Invert Color");
    QPushButton *btnFlipH = new QPushButton("Flip Horizontal");
    QPushButton *btnFlipV = new QPushButton("Flip Vertical");
    QPushButton *btnRotate = new QPushButton("Rotate Image");
    QPushButton *btnDarken = new QPushButton("Adjust Brightness");
    QPushButton *btnCrop = new QPushButton("Crop Image");
    QPushButton *btnResize = new QPushButton("Resize Image");
    QPushButton *btnFrame = new QPushButton("Add Frame");
    QPushButton *btnEdge = new QPushButton("Edge Detection");
    QPushButton *btnSun = new QPushButton("Sunlight");
    QPushButton *btnOil = new QPushButton("Oil Painting");
    QPushButton *btnBlur = new QPushButton("Box Blur");
    QPushButton *btnAvg = new QPushButton("Average (Merge)");
    QPushButton *btnGreet = new QPushButton("Greet");

    controlsLayout->addWidget(btnGray);
    controlsLayout->addWidget(btnBW);
    controlsLayout->addWidget(btnInvert);
    controlsLayout->addWidget(btnFlipH);
    controlsLayout->addWidget(btnFlipV);
    controlsLayout->addWidget(btnRotate);
    controlsLayout->addWidget(btnDarken);
    controlsLayout->addWidget(btnCrop);
    controlsLayout->addWidget(btnResize);
    controlsLayout->addWidget(btnFrame);
    controlsLayout->addWidget(btnEdge);
    controlsLayout->addWidget(btnSun);
    controlsLayout->addWidget(btnOil);
    controlsLayout->addWidget(btnBlur);
    controlsLayout->addWidget(btnAvg);
    controlsLayout->addWidget(btnGreet);
    controlsLayout->addStretch();
    controlsScroll->setWidget(controlsContainer);

    mainLayout->addWidget(grpOriginal, 1);
    mainLayout->addWidget(grpProcessed, 1);
    mainLayout->addWidget(controlsScroll, 0);

    connect(btnLoad, &QPushButton::clicked, this, &MainWindow::onLoadImage);
    connect(btnSave, &QPushButton::clicked, this, &MainWindow::onSaveImage);
    connect(btnReset, &QPushButton::clicked, this, &MainWindow::onResetImage);
    connect(btnGray, &QPushButton::clicked, this, &MainWindow::filterGrayscale);
    connect(btnFlipH, &QPushButton::clicked, this, &MainWindow::filterFlipHorizontal);
    connect(btnFlipV, &QPushButton::clicked, this, &MainWindow::Flip_Vertical);
    connect(btnInvert, &QPushButton::clicked, this, &MainWindow::Invert_color);
    connect(btnBW, &QPushButton::clicked, this, &MainWindow::Convert_To_Black_And_White);
    connect(btnRotate, &QPushButton::clicked, this, &MainWindow::Rotate_img);
    connect(btnDarken, &QPushButton::clicked, this, &MainWindow::adjust_brightness);
    connect(btnCrop, &QPushButton::clicked, this, &MainWindow::Crop_Image);
    connect(btnResize, &QPushButton::clicked, this, &MainWindow::resizeImage);
    connect(btnFrame, &QPushButton::clicked, this, &MainWindow::Add_Frame);
    connect(btnEdge, &QPushButton::clicked, this, &MainWindow::edge_detection);
    connect(btnSun, &QPushButton::clicked, this, &MainWindow::applySunlightFilter);
    connect(btnOil, &QPushButton::clicked, this, &MainWindow::Oil_filter);
    connect(btnBlur, &QPushButton::clicked, this, &MainWindow::box_blur);
    connect(btnAvg, &QPushButton::clicked, this, &MainWindow::averageTwoImages);
    connect(btnGreet, &QPushButton::clicked, this, &MainWindow::Greet);

    connect(originalScroll->verticalScrollBar(), &QScrollBar::valueChanged, processedScroll->verticalScrollBar(), &QScrollBar::setValue);
    connect(processedScroll->verticalScrollBar(), &QScrollBar::valueChanged, originalScroll->verticalScrollBar(), &QScrollBar::setValue);
    connect(originalScroll->horizontalScrollBar(), &QScrollBar::valueChanged, processedScroll->horizontalScrollBar(), &QScrollBar::setValue);
    connect(processedScroll->horizontalScrollBar(), &QScrollBar::valueChanged, originalScroll->horizontalScrollBar(), &QScrollBar::setValue);
}

QImage MainWindow::convertToQImage(Image *img) {
    if (!img) return QImage();
    QImage qImg(img->width, img->height, QImage::Format_RGB888);
    for (int y = 0; y < img->height; ++y) {
        for (int x = 0; x < img->width; ++x) {
            unsigned char r = img->getPixel(x, y, 0);
            unsigned char g = img->getPixel(x, y, 1);
            unsigned char b = img->getPixel(x, y, 2);
            qImg.setPixelColor(x, y, QColor(r, g, b));
        }
    }
    return qImg;
}

void MainWindow::updateDisplay() {
    if (originalImage) {
        QImage qOrig = convertToQImage(originalImage);
        originalLabel->setPixmap(QPixmap::fromImage(qOrig));
        originalLabel->adjustSize();
    }
    if (processedImage) {
        QImage qProc = convertToQImage(processedImage);
        processedLabel->setPixmap(QPixmap::fromImage(qProc));
        processedLabel->adjustSize();
    }
}

void MainWindow::onLoadImage() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image", "", "Images (*.png *.jpg *.bmp *.tga)");
    if (fileName.isEmpty()) return;
    try {
        if (originalImage) delete originalImage;
        if (processedImage) delete processedImage;
        originalImage = new Image(fileName.toStdString());
        processedImage = new Image(*originalImage);
        currentFilePath = fileName;
        updateDisplay();
    } catch (...) {
        QMessageBox::critical(this, "Error", "Failed to load image.");
    }
}

void MainWindow::onSaveImage() {
    if (!processedImage) return;
    QString fileName = QFileDialog::getSaveFileName(this, "Save Image", "", "Images (*.png *.jpg *.bmp *.tga)");
    if (fileName.isEmpty()) return;
    processedImage->saveImage(fileName.toStdString());
}

void MainWindow::onResetImage() {
    if (!originalImage) return;
    delete processedImage;
    processedImage = new Image(*originalImage);
    updateDisplay();
}

void MainWindow::filterGrayscale() { if (processedImage) { ::filterGrayscale(*processedImage); updateDisplay(); } }
void MainWindow::filterFlipHorizontal() { if (processedImage) { ::filterFlipHorizontal(*processedImage); updateDisplay(); } }
void MainWindow::Flip_Vertical() { if (processedImage) { ::Flip_Vertical(*processedImage); updateDisplay(); } }
void MainWindow::Greet() { QMessageBox::information(this, "Welcome", "Welcome to RGB Gulag Image Processor!"); }
void MainWindow::Oil_filter() { if (processedImage) { ::Oil_filter(*processedImage); updateDisplay(); } }
void MainWindow::Invert_color() { if (processedImage) { ::Invert_color(*processedImage); updateDisplay(); } }
void MainWindow::process_image() {}
void MainWindow::applySunlightFilter() { if (processedImage) { ::applySunlightFilter(*processedImage); updateDisplay(); } }
void MainWindow::edge_detection() { if (processedImage) { ::edge_detection(*processedImage); updateDisplay(); } }
void MainWindow::Convert_To_Black_And_White() { if (processedImage) { ::Convert_To_Black_And_White(*processedImage); updateDisplay(); } }

void MainWindow::box_blur() {
    if (!processedImage) return;
    bool ok;
    int m = QInputDialog::getInt(this, "Box Blur", "Enter blur strength:", 10, 1, 100, 1, &ok);
    if (ok) { ::box_blur(*processedImage, m); updateDisplay(); }
}

void MainWindow::Rotate_img() {
    if (!processedImage) return;
    QStringList items; items << "90 Degrees" << "180 Degrees" << "270 Degrees";
    bool ok;
    QString item = QInputDialog::getItem(this, "Rotate", "Select rotation:", items, 0, false, &ok);
    if (ok) {
        char n = (item == "180 Degrees") ? 'b' : (item == "270 Degrees") ? 'c' : 'a';
        ::Rotate_img(*processedImage, n); updateDisplay();
    }
}

void MainWindow::Add_Frame() {
    if (!processedImage) return;
    QStringList types; types << "Type 1" << "Type 2";
    bool ok1;
    QString typeStr = QInputDialog::getItem(this, "Frame Type", "Select Frame Style:", types, 0, false, &ok1);
    if (!ok1) return;
    char f = (typeStr == "Type 1") ? '1' : '2';

    QStringList colors; colors << "Red" << "Green" << "Blue" << "White";
    bool ok2;
    QString colStr = QInputDialog::getItem(this, "Frame Color", "Select Color:", colors, 0, false, &ok2);
    if (!ok2) return;
    char c = (colStr == "Red") ? 'r' : (colStr == "Green") ? 'g' : (colStr == "Blue") ? 'b' : 'w';
    ::Add_Frame(*processedImage, f, c); updateDisplay();
}

void MainWindow::adjust_brightness() {
    if (!processedImage) return;
    QStringList opts; opts << "Lighten" << "Darken";
    bool ok;
    QString mode = QInputDialog::getItem(this, "Brightness", "Mode:", opts, 0, false, &ok);
    if (!ok) return;
    double val = QInputDialog::getDouble(this, "Brightness", "Enter percentage (0-100):", 50.0, 0.0, 100.0, 1, &ok);
    if (ok) { ::adjust_brightness(*processedImage, (float)val, mode == "Lighten"); updateDisplay(); }
}

void MainWindow::resizeImage() {
    if (!processedImage) return;
    bool okW, okH;
    int w = QInputDialog::getInt(this, "Resize", "Enter new Width:", processedImage->width, 1, 5000, 1, &okW);
    if (!okW) return;
    int h = QInputDialog::getInt(this, "Resize", "Enter new Height:", processedImage->height, 1, 5000, 1, &okH);
    if (!okH) return;
    ::Resize_Image(*processedImage, w, h);
    updateDisplay();
}

void MainWindow::averageTwoImages() {
    if (!processedImage) return;
    QString fileName = QFileDialog::getOpenFileName(this, "Select Image to Merge", "", "Images (*.png *.jpg *.bmp)");
    if (fileName.isEmpty()) return;
    Image secondImage(fileName.toStdString());
    if (secondImage.width == 0) return;
    ::averageTwoImages(*processedImage, secondImage);
    updateDisplay();
}

void MainWindow::Crop_Image() {
    if (!processedImage) return;
    bool okX, okY, okW, okH;
    int x = QInputDialog::getInt(this, "Crop", "Start X:", 0, 0, processedImage->width, 1, &okX);
    if (!okX) return;
    int y = QInputDialog::getInt(this, "Crop", "Start Y:", 0, 0, processedImage->height, 1, &okY);
    if (!okY) return;
    int w = QInputDialog::getInt(this, "Crop", "Width:", processedImage->width - x, 1, processedImage->width, 1, &okW);
    if (!okW) return;
    int h = QInputDialog::getInt(this, "Crop", "Height:", processedImage->height - y, 1, processedImage->height, 1, &okH);
    if (!okH) return;
    ::Crop_Image(*processedImage, x, y, w, h);
    updateDisplay();
}