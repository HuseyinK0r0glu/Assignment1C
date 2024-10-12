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


    //??????????????????????????????????

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
    // 2. Normalize the kernel to ensure it sums to 1.
    // 3. For each pixel, compute the weighted sum using the kernel.
    // 4. Update the pixel values with the smoothed results.
}

// Unsharp Masking Filter
void Filter::apply_unsharp_mask(GrayscaleImage& image, int kernelSize, double amount) {
    // TODO: Your code goes here.
    // 1. Blur the image using Gaussian smoothing, use the default sigma given in the header.
    // 2. For each pixel, apply the unsharp mask formula: original + amount * (original - blurred).
    // 3. Clip values to ensure they are within a valid range [0-255].
}
