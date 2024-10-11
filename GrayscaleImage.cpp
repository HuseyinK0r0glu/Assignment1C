#include "GrayscaleImage.h"
#include <iostream>
#include <cstring>  // For memcpy
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <stdexcept>


// Constructor: load from a file
GrayscaleImage::GrayscaleImage(const char* filename) {

    // Image loading code using stbi
    int channels;
    unsigned char* image = stbi_load(filename, &width, &height, &channels, STBI_grey);

    if (image == nullptr) {
        std::cerr << "Error: Could not load image " << filename << std::endl;
        exit(1);
    }

    // TODO: Your code goes here.

    data = new int*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new int[width];
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // convert unsigned char to int
            data[y][x] = static_cast<int>(image[y * width + x]);
        }
    }

    // Dynamically allocate memory for a 2D matrix based on the given dimensions.
    // Fill the matrix with pixel values from the image

    // Free the dynamically allocated memory of stbi image
    stbi_image_free(image);
}

// Constructor: initialize from a pre-existing data matrix
GrayscaleImage::GrayscaleImage(int** inputData, int h, int w) {
    // TODO: Your code goes here.

    data = new int*[h];
    for (int i = 0; i < h; ++i) {
        data[i] = new int[w];
    }

    for(int y = 0; y < h; ++y) {
        for(int x = 0; x < w; ++x) {
            data[y][x] = inputData[y][x];
        }
    }
    // Initialize the image with a pre-existing data matrix by copying the values.
    // Don't forget to dynamically allocate memory for the matrix.
}

// Constructor to create a blank image of given width and height
GrayscaleImage::GrayscaleImage(int w, int h) : width(w), height(h) {
    // TODO: Your code goes here.
    data = new int*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new int[width];
    }

    // initialize a blank image
    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) {
            data[y][x] = 0;
        }
    }

    // Just dynamically allocate the memory for the new matrix.
}

// Copy constructor
GrayscaleImage::GrayscaleImage(const GrayscaleImage& other) {

    // TODO: Your code goes here.
    // Copy constructor: dynamically allocate memory and
    // copy pixel values from another image.

    data = new int*[other.get_height()];

    for(int i = 0; i < other.get_height(); ++i) {
        data[i] = new int[other.get_width()];
    }

    for(int y = 0; y < other.get_height(); ++y) {
        for(int x = 0; x < other.get_width(); ++x) {
            data[y][x] = other.get_pixel(y,x);
        }
    }
}

// Destructor
GrayscaleImage::~GrayscaleImage() {
    // TODO: Your code goes here.

    for (int i = 0; i < height; ++i) {
        delete[] data[i];
    }

    delete[] data;

    // Destructor: deallocate memory for the matrix.
}

// Equality operator
bool GrayscaleImage::operator==(const GrayscaleImage& other) const {
    // TODO: Your code goes here.
    if(height != other.get_height() || width != other.get_width()) {
        return false;
    }

    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) {
            if(data[y][x] != other.get_pixel(y,x)) {
                return false;
            }
        }
    }

    // Check if two images have the same dimensions and pixel values.
    // If they do, return true.
    return true;
}

// Addition operator
GrayscaleImage GrayscaleImage::operator+(const GrayscaleImage& other) const {
    // Create a new image for the result
    GrayscaleImage result(width, height);

    // TODO: Your code goes here.
    // Add two images' pixel values and return a new image, clamping the results.

    // add pixels from image other and data and store the results in result image
    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) {
            int value = data[y][x] + other.get_pixel(y,x);
            result.set_pixel(y,x,(value > 255) ? 255 : value);
        }
    }
    return result;
}

// Subtraction operator
GrayscaleImage GrayscaleImage::operator-(const GrayscaleImage& other) const {
    // Create a new image for the result
    GrayscaleImage result(width, height);
    
    // TODO: Your code goes here.
    // Subtract pixel values of two images and return a new image, clamping the results.
    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) {
            int value = data[y][x] - other.get_pixel(y,x);
            result.set_pixel(y,x,(value < 0) ? 0 : value);
        }
    }
    return result;
}

// Get a specific pixel value
int GrayscaleImage::get_pixel(int row, int col) const {
    return data[row][col];
}

// Set a specific pixel value
void GrayscaleImage::set_pixel(int row, int col, int value) {
    data[row][col] = value;
}

/*
// Function to save the image to a PNG file
void GrayscaleImage::save_to_file(const char* filename) const {
    // Create a buffer to hold the image data in the format stb_image_write expects
    unsigned char* imageBuffer = new unsigned char[width * height];

    // Fill the buffer with pixel data (convert int to unsigned char)
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            imageBuffer[i * width + j] = static_cast<unsigned char>(data[i][j]);
        }
    }

    // Write the buffer to a PNG file
    if (!stbi_write_png(filename, width, height, 1, imageBuffer, width)) {
        std::cerr << "Error: Could not save image to file " << filename << std::endl;
    }

    // Clean up the allocated buffer
    delete[] imageBuffer;
}
*/
// Function to save the image to a PNG file
void GrayscaleImage::save_to_file(const char* filename) const {
    // Validate filename
    if (filename == nullptr) {
        std::cerr << "Error: Filename is null!" << std::endl;
        return;
    }

    // Create a buffer to hold the image data in the format stb_image_write expects
    unsigned char* imageBuffer = new unsigned char[width * height];

    // Fill the buffer with pixel data (convert int to unsigned char)
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            // Ensure pixel value is within the 0-255 range (grayscale values)
            int pixelValue = data[i][j];
            if (pixelValue < 0) pixelValue = 0;
            if (pixelValue > 255) pixelValue = 255;

            // Convert to unsigned char
            imageBuffer[i * width + j] = static_cast<unsigned char>(pixelValue);
        }
    }

    // Write the buffer to a PNG file using the stb_image_write library
    int stride_in_bytes = width; // Stride is the width in pixels (1 byte per pixel for grayscale)

    if (!stbi_write_png(filename, width, height, 1, imageBuffer, stride_in_bytes)) {
        std::cerr << "Error: Could not save image to file " << filename << std::endl;
    }

    // Clean up the allocated buffer
    delete[] imageBuffer;
}
