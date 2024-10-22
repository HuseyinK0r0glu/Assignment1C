# ClearVision

## Project Overview
ClearVision is a C++ application that processes grayscale images using various filters and operations applied through matrices. It utilizes the `stb_image` and `stb_image_write` libraries for image loading, manipulation, and saving. This project offers numerous image processing features such as smoothing, sharpening, image arithmetic, comparison, and even message encoding/decoding within images.

## Features
- **Load and Save Grayscale Images** using the `stb_image` library.
- **Image Filters and Operations**:
  - **Mean Filter**: Apply a mean filter to smooth the image using a specified kernel size.
  - **Gaussian Smoothing**: Perform Gaussian smoothing on the image with a custom kernel size.
  - **Unsharp Mask**: Apply an unsharp mask to sharpen the image.
  - **Image Addition**: Combine two grayscale images pixel-by-pixel.
  - **Image Subtraction**: Subtract one grayscale image from another pixel-by-pixel.
  - **Image Comparison**: Check if two images are identical.
  - **Image Disguise and Reveal**: Disguise and reveal images using a custom encoding.
  - **Message Embedding (Encoding)**: Hide a secret message in an image.
  - **Message Extraction (Decoding)**: Extract a hidden message from an image.

## Technologies Used
- **C++**: Core language for implementing the application.
- **stb_image**: A lightweight library for loading and writing images.
- **C++ Standard Libraries**: For handling file I/O, image processing, and memory management.

## Requirements
- C++ compiler supporting **C++11** or later.
- Include the following files in your project:
  - `stb_image.h`
  - `stb_image_write.h`

## Setup and Installation

1. **Clone the Repository**:
   ```bash
   git clone <repository_url>
