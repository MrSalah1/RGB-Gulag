# 🎨 RGB-Gulag

A C++ Graphical User Interface image processing tool developed for a CS213 Object-Oriented Programming assignment. It allows users to load, save, and manipulate images with filters such as grayscale conversion, rotation, blurring, and more. This project showcases core C++ concepts and fundamental image manipulation algorithms.

---

## 🚀 Features
* **Grayscale Conversion:** Convert colored images to black-and-white using channel averaging.
* **Image Manipulation:** Apply various filters like rotation and blurring.
* **Format Support:** Load and save images in `.jpg`, `.bmp`, `.png`, and `.tga` formats.
* **Graphical Interface:** Built to provide an accessible GUI for testing image manipulation algorithms.

---

## 🛠️ Requirements
* **C++ Compiler:** GCC, Clang, or MSVC.
* **Standard:** C++11 or higher.

---

## 📂 Project Structure
```text
.
|-- CS213_A1_Part1_...cpp        # Assignment-specific logic
|-- ImageProcessingDemo.cpp      # Grayscale conversion demo
|-- Image_Class.h                # Core Image handling class
|-- main.cpp                     # Main entry point
|-- stb_image.h                  # Image loading library
|-- stb_image_write.h            # Image saving library
|-- LICENSE
`-- README.md
```

---

## 🚦 How to Run (Demo)

1. **Clone the repository:**
```bash
git clone [https://github.com/MrSalah1/RGB-Gulag.git](https://github.com/MrSalah1/RGB-Gulag.git)
```

2. **Navigate to the repository folder:**
```bash
cd RGB-Gulag
```

3. **Compile the demo code:**
```bash
g++ ImageProcessingDemo.cpp -o demo
```

4. **Run the application:**
```bash
./demo
```

---

## 🎮 Usage

Once the demo starts, use the console to process your images:

**1. Enter the source image name:**
```text
Pls enter colored image name to turn to gray scale: input.jpg
```

**2. Enter the output image name and specify the extension:**
```text
Pls enter image name to store new image
and specify extension .jpg, .bmp, .png, .tga: output.png
```

---

## 📝 License
This project is open-source and available under the [MIT License](LICENSE).
