#include "Image_Class.h"
#include <iostream>

using namespace std;

int main() {
    // Prompt user for image filename
    string filename;
    cout << "Enter the image you want to make it infrared:";
    cin >> filename;

    // Load the image
    Image image(filename);

    // Image dimensions
    int width = image.width;
    int height = image.height;

    // Create a new image for the effect (same dimensions as original)
    Image newImage(width, height);

    // Loop through each pixel in the original image
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Extract red, green, and blue channels
            int red = image(x, y, 0);
            int green = image(x, y, 1);
            int blue = image(x, y, 2);

            // Apply effect (red set to 230, others inverted)
            int newRed = 230;
            int newGreen = 255 - green;
            int newBlue = 255 - blue;

            // Clip values to prevent overflow (ensure values stay between 0 and 255)
            newRed = min(255, newRed);
            newGreen = min(255, newGreen);
            newBlue = min(255, newBlue);

            // Set new pixel values in the new image
            newImage(x, y, 0) = newRed;
            newImage(x, y, 1) = newGreen;
            newImage(x, y, 2) = newBlue;
        }
    }

    // Save the new image
    cout << "Enter the filename to save the processed image: ";
    cin >> filename;

    newImage.saveImage(filename);

    return 0;
}
