#include <cstdlib>
#include <iostream>
#include "Image_Class.h" // Assuming Image_Class is defined elsewhere

using namespace std;

int main() {
    string filename;
    int choice;

    cout << "Please enter the colored image name: ";
    cin >> filename;

    Image image(filename);

    cout << "Select filter:\n";
    cout << "1. Darken image by 50%\n";
    cout << "2. Lighten image by 50%\n";
    cout << "Enter your choice: ";
    cin >> choice;

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int red = image(i, j, 0);
            unsigned int green = image(i, j, 1);
            unsigned int blue = image(i, j, 2);

            // Calculate new values based on user selection
            double factor = 1.0; // No change
            switch (choice) {
                case 1:
                    factor = 0.5; // Darken (multiply by 0.5)
                    break;
                case 2:
                    factor = 1.5; // Lighten (multiply by 1.5)
                    break;
                default:
                    cout << "Invalid choice. Skipping pixel.\n";
                    continue; // Skip pixel for invalid choice
            }

            // Apply factor to each channel (clamp to valid range)
            red = std::max(0u, std::min(255u, static_cast<unsigned int>(red * factor)));
            green = std::max(0u, std::min(255u, static_cast<unsigned int>(green * factor)));
            blue = std::max(0u, std::min(255u, static_cast<unsigned int>(blue * factor)));

            // Set new pixel values
            image(i, j, 0) = red;
            image(i, j, 1) = green;
            image(i, j, 2) = blue;
        }
    }

    cout << "Please enter the image name to store the modified image\n";
    cout << "and specify the extension .jpg, .bmp, .png, .tga: ";

    cin >> filename;
    image.saveImage(filename);

    return 0;
}
