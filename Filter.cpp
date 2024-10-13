#include "Filter.h"
#include <algorithm>
#include <cmath>
#include <vector>
#include <numeric>
#include <math.h>

// Mean Filter
void Filter::apply_mean_filter(GrayscaleImage& image, int kernelSize) {
    // TODO: Your code goes here.
    // 1. Copy the original image for reference.
    GrayscaleImage copyImage(image);
    // 2. For each pixel, calculate the mean value of its neighbors using a kernel.
    // 3. Update each pixel with the computed mean.
    for(int y = 0; y < copyImage.get_height(); ++y) {
        for(int x = 0; x < copyImage.get_width(); ++x) {
            // mean filter operation
            int sum = 0;
            for(int i = y-(kernelSize/2);i<=y+(kernelSize/2);++i) {
                for(int j = x-(kernelSize/2);j<=x+(kernelSize/2);++j) {
                    if(i >= 0 && i < copyImage.get_height() && j>=0 && j < copyImage.get_width()) {
                        sum += copyImage.get_pixel(i,j);
                    }
                }
            }
            image.set_pixel(y, x, static_cast<int>(std::floor(sum / (kernelSize * kernelSize))));
        }
    }
}

// Gaussian Smoothing Filter
void Filter::apply_gaussian_smoothing(GrayscaleImage& image, int kernelSize, double sigma) {
    // TODO: Your code goes here.
    // 1. Create a Gaussian kernel based on the given sigma value.

    std::vector<std::vector<double> > kernel(kernelSize, std::vector<double>(kernelSize));
    double sum = 0.0;
    double pi = 3.14159265358979323846;
    for(int i = 0;i<kernelSize;++i) {
        for(int j = 0;j<kernelSize;++j) {
            int xDist = j - kernelSize / 2;
            int yDist = i - kernelSize / 2;
            double exponent = -( (xDist * xDist + yDist * yDist) / (2 * sigma * sigma ));
            double weight = (1.0 / (2 * pi * sigma * sigma)) * exp(exponent);
            kernel[i][j] = weight;
            sum += kernel[i][j];
        }
    }

    // 2. Normalize the kernel to ensure it sums to 1.
    for(int i = 0;i<kernelSize;++i) {
        for(int j = 0;j<kernelSize;++j) {
            if(sum != 0.0) {
                kernel[i][j] /= sum;
            }
        }
    }

    // 3. For each pixel, compute the weighted sum using the kernel.
    // 4. Update the pixel values with the smoothed results.

    GrayscaleImage copyImage(image);
    for(int y = 0; y < copyImage.get_height(); ++y) {
        for(int x = 0; x < copyImage.get_width(); ++x) {
            // gaussian filter operation
            double sum = 0;
            for(int i = 0;i<kernelSize;++i) {
                for(int j = 0;j<kernelSize;++j) {
                    int xDist = x + (j - kernelSize / 2);
                    int yDist = y + (i - kernelSize / 2);
                    if(xDist >= 0 && xDist < copyImage.get_width() && yDist >= 0 && yDist < copyImage.get_height()) {
                        sum += copyImage.get_pixel(yDist,xDist) * kernel[i][j];
                    }
                }
            }
            if(sum < 0.0) {
                image.set_pixel(y, x,0);
                continue;
            }if(sum > 255.0) {
                image.set_pixel(y, x, 255);
                continue;
            }
            image.set_pixel(y, x, static_cast<int>(std::floor(sum)));
        }
    }
}

// Unsharp Masking Filter
void Filter::apply_unsharp_mask(GrayscaleImage& image, int kernelSize, double amount) {
    // TODO: Your code goes here.
    // 1. Blur the image using Gaussian smoothing, use the default sigma given in the header.
    GrayscaleImage copyImage(image);
    apply_gaussian_smoothing(copyImage, kernelSize, 1);
    // 2. For each pixel, apply the unsharp mask formula: original + amount * (original - blurred).
    // 3. Clip values to ensure they are within a valid range [0-255].
    for(int y = 0; y < image.get_height(); ++y) {
        for(int x = 0; x < image.get_width(); ++x) {
            double pixelValue = image.get_pixel(y,x) + amount * (image.get_pixel(y,x) - copyImage.get_pixel(y,x));
            if(pixelValue > 255.0) {
                image.set_pixel(y, x,255);
                continue;
            }

            if(pixelValue < 0.0) {
                image.set_pixel(y, x,0);
                continue;
            }

            image.set_pixel(y, x, static_cast<int>(pixelValue));
        }
    }

}
