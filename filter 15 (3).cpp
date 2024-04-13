#include "Image_Class.h"
#include <iostream>
#include <random>

using namespace std;

// Function to add random static noise to an image
void AddNoise(Image& image, float noiseIntensity) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 255);

    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            for (int channel = 0; channel < image.channels; ++channel) {
                int noiseValue = dist(gen);
                image(x, y, channel) = min(255, (int)(image(x, y, channel) + noiseValue * noiseIntensity));
            }
        }
    }
}

// Function to add scanlines to an image
void AddScanlines(Image& image, int scanlineIntensity) {
    for (int y = 0; y < image.height; ++y) {
        // Darken pixels based on scanline intensity (adjust for effect)
        int darkeningFactor = (y % (scanlineIntensity * 2) == 0) ? scanlineIntensity : 0;
        for (int x = 0; x < image.width; ++x) {
            for (int channel = 0; channel < image.channels; ++channel) {
                int originalValue = image(x, y, channel);
                int newValue = max(0, originalValue - darkeningFactor);
                image(x, y, channel) = newValue;
            }
        }
    }
}

// Function to apply color distortion to an image
void ApplyColorDistortion(Image& image, int distortionLevel) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(-distortionLevel, distortionLevel);

    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            for (int channel = 0; channel < image.channels; ++channel) {
                int originalValue = image(x, y, channel);
                int noiseValue = dist(gen);
                int newValue = max(0, min(255, originalValue + noiseValue));
                image(x, y, channel) = newValue;
            }
        }
    }
}

int main() {
    // Prompt user for image filename
    string filename;
    cout << "Enter the image you want to process: ";
    cin >> filename;

    // Load the image
    Image image(filename);

    // Add static noise to simulate TV static
    float noiseIntensity = 0.1f; // Adjust for desired noise level (0.0 to 1.0)
    AddNoise(image, noiseIntensity);

    // Add scanlines for a more pronounced TV effect
    int scanlineWidth = 3; // Adjust for desired scanline width
    AddScanlines(image, scanlineWidth);

    // Apply color distortion for a vintage look
    int distortionLevel = 20; // Adjust for desired distortion level
    ApplyColorDistortion(image, distortionLevel);

    // Prompt user for output filename
    cout << "Enter the filename to save the Wano TV image: ";
    cin >> filename;

    // Save the filtered image
    image.saveImage(filename);
    return 0;
}
