Overview
This project is a C++ application that processes grayscale images using various filters applied through matrices. It utilizes the stb_image library for image loading and manipulation, enabling efficient image processing capabilities.

Features
Load and save grayscale images using the stb_image library.
Apply various image filters and operations, including:
Mean Filter: mean <img> <kernel_size>
Gaussian Smoothing: gauss <img> <kernel_size> <sigma>
Unsharp Mask: unsharp <img> <kernel_size> <amount>
Image Addition: add <img1> <img2>
Image Subtraction: sub <img1> <img2>
Image Comparison: equals <img1> <img2>
Image Disguise: disguise <img>
Image Reveal: reveal <dat>
Message Embedding: enc <img> <message>
Message Extraction: dec <img> <msg_len>
Requirements
C++ compiler (C++11 or later recommended)
stb_image library (include stb_image.h and stb_image_write.h)

Usage
Run the application with one of the following command formats:

./ClearVision mean <img> <kernel_size>
./ClearVision gauss <img> <kernel_size> <sigma>
./ClearVision unsharp <img> <kernel_size> <amount>
./ClearVision add <img1> <img2>
./ClearVision sub <img1> <img2>
./ClearVision equals <img1> <img2>
./ClearVision disguise <img>
./ClearVision reveal <dat>
./ClearVision enc <img> <message>
./ClearVision dec <img> <msg_len>
