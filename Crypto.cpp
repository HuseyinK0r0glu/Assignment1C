#include "Crypto.h"

#include <valarray>

#include "GrayscaleImage.h"


    // Extract the least significant bits (LSBs) from SecretImage, calculating x, y based on message length
    std::vector<int> Crypto::extract_LSBits(SecretImage& secret_image, int message_length) {
        std::vector<int> LSB_array;
        // TODO: Your code goes here.

        // 1. Reconstruct the SecretImage to a GrayscaleImage.
        GrayscaleImage image = secret_image.reconstruct();
        // 2. Calculate the image dimensions.
        int width = image.get_width();
        int height = image.get_height();
        // 3. Determine the total bits required based on message length.
        int bits = message_length * 7;
        int total = width * height ;
        // 4. Ensure the image has enough pixels; if not, throw an error.
        if(total < bits) {
            throw std::invalid_argument("The message length is too big");
        }
        // 5. Calculate the starting pixel from the message_length knowing that
        //    the last LSB to extract is in the last pixel of the image.
        int start = total - bits;

        for(int i = start;i<total;i++) {
            int y = i / width;
            int x = i % width;

            int pixel = image.get_pixel(y,x);
            LSB_array.push_back(pixel & 1);
        }

        // 6. Extract LSBs from the image pixels and return the result.

        return LSB_array;
    }


// Decrypt message by converting LSB array into ASCII characters
std::string Crypto::decrypt_message(const std::vector<int>& LSB_array) {
    std::string message;
    // TODO: Your code goes here.

    // 1. Verify that the LSB array size is a multiple of 7, else throw an error.
    if(LSB_array.size() % 7 != 0) {
        throw std::invalid_argument("LSB must be a multiple of 7");
    }

    // 2. Convert each group of 7 bits into an ASCII character.
    // 3. Collect the characters to form the decrypted message.

    for(int i = 0; i < LSB_array.size(); i += 7) {

        int value = 0;
        int exp = 0;

        for(int j = 6; j>=0 ; j--) {
            value += static_cast<int>(LSB_array[i+j] * pow(2, exp++));
        }

        message += static_cast<char>(value);
    }

    // 4. Return the resulting message.

    return message;
}

// Encrypt message by converting ASCII characters into LSBs
std::vector<int> Crypto::encrypt_message(const std::string& message) {
    std::vector<int> LSB_array;
    // TODO: Your code goes here.

    // 1. Convert each character of the message into a 7-bit binary representation.
    //    You can use std::bitset.
    // 2. Collect the bits into the LSB array.

    for(char ch : message) {
        std::bitset<7> bits(static_cast<long>(ch));

        for(int j = 6; j >= 0; j--) {
            LSB_array.push_back(bits[j]);
        }

    }

    // 3. Return the array of bits.

    return LSB_array;
}

// Embed LSB array into GrayscaleImage starting from the last bit of the image
SecretImage Crypto::embed_LSBits(GrayscaleImage& image, const std::vector<int>& LSB_array) {
    // TODO: Your code goes here.

        int width = image.get_width();
        int height = image.get_height();
        int total = width * height ;

    // 1. Ensure the image has enough pixels to store the LSB array, else throw an error.
        if(total < LSB_array.size()) {
            throw std::invalid_argument("The message length is too big");
        }
    // 2. Find the starting pixel based on the message length knowing that
    //    the last LSB to embed should end up in the last pixel of the image.
        int start = static_cast<int>(total - LSB_array.size());
    // 3. Iterate over the image pixels, embedding LSBs from the array.
        for(int i = start;i<total;i++) {
            int y = i / width;
            int x = i % width;
            int pixel = image.get_pixel(y,x);

            pixel &= ~1;

            pixel |= LSB_array[i - start];

            image.set_pixel(y,x,pixel);
        }
    // 4. Return a SecretImage object constructed from the given GrayscaleImage
    //    with the embedded message.

    SecretImage secret_image(image);

    return secret_image;
}
