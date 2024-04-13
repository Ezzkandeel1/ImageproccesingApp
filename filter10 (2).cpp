#include "Image_Class.h"
#include <iostream>
#include <cmath> // for mathematical functions

using namespace std;

int main() {
    // Prompt user for image filename
    string filename;
    cout << "Enter the image you want to process: ";
    cin >> filename;

    // Load the image
    Image image(filename);

    // Convert to grayscale (optional, consider grayscale images for better results)
    // ... (grayscale conversion code using Image_Class.h functions) ...

    // Image dimensions
    int width = image.width;
    int height = image.height;

    // Create a new image for the edge map (same dimensions as original)
    Image edgeImage(width, height);

    // Sobel filter kernels (pre-defined for horizontal and vertical gradients)
    int SobelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int SobelY[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

    // Loop through each pixel in the original image (avoid borders for Sobel filter)
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            int gx = 0, gy = 0; // Gradients in x and y directions

            // Apply Sobel filter (consider padding for edge cases)
            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    int neighborX = x + kx;
                    int neighborY = y + ky;
                    int intensity = image(neighborX, neighborY, 0); // Assuming grayscale

                    gx += SobelX[ky + 1][kx + 1] * intensity;
                    gy += SobelY[ky + 1][kx + 1] * intensity;
                }
            }

            // Combine gradients (consider alternative methods like magnitude)
            int edgeStrength = abs(gx) + abs(gy);  // Absolute value for edge strength

            // Invert for black background with white edges
            edgeStrength = 255 - edgeStrength;  // Higher edge strength -> higher intensity (closer to white)

            // Set values in the new image (all channels for black background)
            edgeImage(x, y, 0) = 0;  // Black for background
            edgeImage(x, y, 1) = 0;
            edgeImage(x, y, 2) = 0;

            // Set edge pixel values (all channels for white edges)
            if (edgeStrength > 0) {  // Consider a threshold if needed
                edgeImage(x, y, 0) = 255;  // White for edges
                edgeImage(x, y, 1) = 255;
                edgeImage(x, y, 2) = 255;
            }
        }
    }

    // Save the edge map image
    cout << "Enter the filename to save the edge image: ";
    cin >> filename;

    edgeImage.saveImage(filename);

    return 0;
}
