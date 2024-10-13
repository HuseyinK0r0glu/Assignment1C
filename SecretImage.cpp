#include "SecretImage.h"


// Constructor: split image into upper and lower triangular arrays
SecretImage::SecretImage(const GrayscaleImage& image) {
    // TODO: Your code goes here.
    // 1. Dynamically allocate the memory for the upper and lower triangular matrices.

    height = image.get_height();
    width = image.get_width();

    int upSize = width * (width + 1) / 2;
    int lowSize = width * (width - 1) / 2;

    upper_triangular = new int[upSize];
    lower_triangular = new int[lowSize];

    // 2. Fill both matrices with the pixels from the GrayscaleImage.

    int upperCount = 0;
    int lowerCount = 0;

    for(int y = 0;y<height;++y) {
        for(int x = 0;x<width;++x) {

            if(y <= x) {
                // upper triangular array
                upper_triangular[upperCount] = image.get_pixel(y,x);
                upperCount++;
            } else {
                // lower triangular array
                lower_triangular[lowerCount] = image.get_pixel(y,x);
                lowerCount++;
            }

        }
    }

}

// Constructor: instantiate based on data read from file
SecretImage::SecretImage(int w, int h, int * upper, int * lower) {
    // TODO: Your code goes here.
    // Since file reading part should dynamically allocate upper and lower matrices.
    // You should simply copy the parameters to instance variables.

    width = w;
    height = h;

    upper_triangular = new int[width * (width + 1) / 2];
    lower_triangular = new int[width * (width - 1) / 2];

    for(int i = 0;i<width * (width+1) / 2;++i) {
        upper_triangular[i] = upper[i];
    }

    for(int i = 0;i<width * (width - 1) / 2;++i) {
        lower_triangular[i] = lower[i];
    }
}


// Destructor: free the arrays
SecretImage::~SecretImage() {
    // TODO: Your code goes here.
    // Simply free the dynamically allocated memory
    // for the upper and lower triangular matrices.

    delete[] upper_triangular;
    delete[] lower_triangular;

}

// Reconstructs and returns the full image from upper and lower triangular matrices.
GrayscaleImage SecretImage::reconstruct() const {
    GrayscaleImage image(width, height);

    // TODO: Your code goes here.

    int upperCount = 0;
    int lowerCount = 0;

    for(int y = 0;y<image.get_height();++y) {
        for(int x = 0;x<image.get_width();++x) {

            if(y <= x) {
                image.set_pixel(y,x,upper_triangular[upperCount]);
                upperCount++;
            }else {
                image.set_pixel(y,x,lower_triangular[lowerCount]);
                lowerCount++;
            }

        }
    }

    return image;
}

// Save the filtered image back to the triangular arrays
void SecretImage::save_back(const GrayscaleImage& image) {
    // TODO: Your code goes here.
    // Update the lower and upper triangular matrices 
    // based on the GrayscaleImage given as the parameter.
    int upperCount = 0;
    int lowerCount = 0;

    for(int y = 0;y<image.get_height();++y) {
        for(int x = 0;x<image.get_width();++x) {

            if(y <= x) {
                // upper triangular array
                upper_triangular[upperCount] = image.get_pixel(y,x);
                upperCount++;
            } else {
                // lower triangular array
                lower_triangular[lowerCount] = image.get_pixel(y,x);
                lowerCount++;
            }

        }
    }
}

// Save the upper and lower triangular arrays to a file
void SecretImage::save_to_file(const std::string& filename) {
    // TODO: Your code goes here.
    std::ofstream file(filename);
    // 1. Write width and height on the first line, separated by a single space.
    if(file.is_open()) {
        file << width << " " << height << std::endl;
        // 2. Write the upper_triangular array to the second line.
        for(int i = 0;i<width * (width + 1) / 2;++i) {
            file << upper_triangular[i];

            if (i != width * (width + 1) / 2 - 1) {
                file << " ";
            }

        }
        file << std::endl;

        // Ensure that the elements are space-separated.
        // If there are 15 elements, write them as: "element1 element2 ... element15"
        // 3. Write the lower_triangular array to the third line in a similar manner
        for(int j = 0;j<width * (width - 1) / 2;++j) {
            file << lower_triangular[j];

            if (j != width * (width - 1) / 2 - 1) {
                file << " ";
            }

        }

        file << std::endl;
        // as the second line.
        file.close();
    }

}

// Static function to load a SecretImage from a file
SecretImage SecretImage::load_from_file(const std::string& filename) {
    // TODO: Your code goes here.
    // 1. Open the file and read width and height from the first line, separated by a space.
    std::ifstream file(filename);
    int width = 0;
    int height = 0;

    if(file.is_open()) {
        file >> width >> height;
    }

    // 2. Calculate the sizes of the upper and lower triangular arrays.
    int upSize = width * (width + 1) / 2;
    int lowSize = width * (width - 1) / 2;
    // 3. Allocate memory for both arrays.
    int* upper = new int[upSize];
    int* lower = new int[lowSize];
    // 4. Read the upper_triangular array from the second line, space-separated.
    for(int i = 0;i<upSize;++i) {
        file >> upper[i];
    }
    // 5. Read the lower_triangular array from the third line, space-separated.
    for(int j = 0;j<lowSize;++j) {
        file >> lower[j];
    }
    // 6. Close the file and return a SecretImage object initialized with the
    //    width, height, and triangular arrays.
    file.close();
    SecretImage secretImage(width, height, upper, lower);
    return secretImage;
}

// Returns a pointer to the upper triangular part of the secret image.
int * SecretImage::get_upper_triangular() const {
    return upper_triangular;
}

// Returns a pointer to the lower triangular part of the secret image.
int * SecretImage::get_lower_triangular() const {
    return lower_triangular;
}

// Returns the width of the secret image.
int SecretImage::get_width() const {
    return width;
}

// Returns the height of the secret image.
int SecretImage::get_height() const {
    return height;
}
