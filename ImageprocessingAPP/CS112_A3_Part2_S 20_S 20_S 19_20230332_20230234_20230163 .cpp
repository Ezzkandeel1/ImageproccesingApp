    /*
    File:CS112_A3_Part1_S 20_S 20_S 19_20230332_20230234_20230163
    Purpose: Image filtering 
    Author:Mohamed Hussien Mohamed Ali S 20  
        Zyad Wael El-Baz S 20 
        Ezz El-Deen Amr Abd El-Monem S 20  
    E-Mails: mohamedboka893@gmail.com
            zodawael54@gmail.com
            azzkandeel@gmail.com
    IDs:20230332 filter (5)
        20230163 filter (4)
        20230234 fliter (1,2,3,6)
    */
    #include <iostream>
    #include "Image_Class.h"
    #include <cstdlib>
    #include <cmath>
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
        int choice;

        cout << "1. Grey\n2. Black and White\n3. Invert\n4. Merge\n5. Flip Image\n6.cloackwise rotation\n7. brightness filter\n";
        cout <<"8. crop\n10.edge detection filter\n11.resize filter\n12.blur\n13. warm filter\n15.Tv filter\n16. purple filter\n17. infrared photography\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            string photo;
            cout << "Enter the name of the file: ";
            cin >> photo;
            Image image(photo);

            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    unsigned int avg = 0;
                    for (int k = 0; k < image.channels; ++k) {
                        avg += image(i, j, k);
                    }
                    avg /= image.channels;
                    for (int k = 0; k < image.channels; ++k) {
                        image(i, j, k) = avg;
                    }
                }
            }

            string newPhoto;
            cout << "Enter the image name to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
            cin >> newPhoto;
            image.saveImage(newPhoto);
            break;
        }
        case 2: {
            string photo;
            cout << "Enter the name of the file: ";
            cin >> photo;
            Image image(photo);
            const int blackAndWhiteThreshold = 128;
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    unsigned int avg = 0;
                    for (int k = 0; k < image.channels; ++k) {
                        avg += image(i, j, k);
                    }
                    avg /= image.channels;

                    if (avg >= blackAndWhiteThreshold) {
                        for (int k = 0; k < image.channels; ++k) {
                            image(i, j, k) = 255;
                        }
                    }
                    else {
                        for (int k = 0; k < image.channels; ++k) {
                            image(i, j, k) = 0;
                        }
                    }
                }
            }

            string newPhoto;
            cout << "Enter the image name to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
            cin >> newPhoto;
            image.saveImage(newPhoto);
            break;
        }
        case 3: {
            string photo;
            cout << "Enter the name of the file: ";
            cin >> photo;
            Image image(photo);
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        // Invert the pixel intensity
                        image(i, j, k) = 255 - image(i, j, k);
                    }
                }
            }

            string newPhoto;
            cout << "Enter the image name to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
            cin >> newPhoto;
            image.saveImage(newPhoto);
            break;
        }
        case 4: {            
                string photo1, photo2, mergedFileName;
                cout << "Enter the name of the first file: ";
                cin >> photo1;
                cout << "Enter the name of the second file: ";
                cin >> photo2;

                Image image1(photo1);
                Image image2(photo2);

                // Check which image has the larger dimensions
                Image* largerImage;
                Image* smallerImage;
                if (image1.width * image1.height > image2.width * image2.height) {
                    largerImage = &image1;
                    smallerImage = &image2;
                }
                else {
                    largerImage = &image2;
                    smallerImage = &image1;
                }

                // Crop the larger image to match the dimensions of the smaller one
                Image croppedImage(smallerImage->width, smallerImage->height);
                for (int i = 0; i < smallerImage->width; ++i) {
                    for (int j = 0; j < smallerImage->height; ++j) {
                        for (int k = 0; k < smallerImage->channels; ++k) {
                            croppedImage(i, j, k) = (*largerImage)(i, j, k);
                        }
                    }
                }

                // Merge the cropped image with the smaller image
                Image mergedImage(smallerImage->width, smallerImage->height);
                for (int i = 0; i < smallerImage->width; ++i) {
                    for (int j = 0; j < smallerImage->height; ++j) {
                        for (int k = 0; k < smallerImage->channels; ++k) {
                            // Average the pixel values from the two images
                            mergedImage(i, j, k) = (croppedImage(i, j, k) + (*smallerImage)(i, j, k)) / 2;
                        }
                    }
                }

                cout << "Enter the name of the file to save the merged image and specify extension (.jpg, .bmp, .png, .tga): ";
                cin >> mergedFileName;
                mergedImage.saveImage(mergedFileName);

                cout << "Merged image saved as: " << mergedFileName << endl;

                return 0;
            }

        case 5: {
            string photo;
            cout << "Enter the name of the file: ";
            cin >> photo;
            Image image(photo);

            cout << "Choose flip direction:\n";
            cout << "1. Horizontal Flip\n";
            cout << "2. Vertical Flip\n";
            int flipChoice;
            cin >> flipChoice;

            if (flipChoice == 1) {
                for (int i = 0; i < image.width / 2; ++i) {
                    for (int j = 0; j < image.height; ++j) {
                        for (int k = 0; k < image.channels; ++k) {
                            swap(image(i, j, k), image(image.width - 1 - i, j, k));
                        }
                    }
                }
            }
            else if (flipChoice == 2) {
                for (int i = 0; i < image.width; ++i) {
                    for (int j = 0; j < image.height / 2; ++j) {
                        for (int k = 0; k < image.channels; ++k) {
                            swap(image(i, j, k), image(i, image.height - 1 - j, k));
                        }
                    }
                }
            }
            else {
                cout << "Invalid choice!" << endl;
                break;
            }

            string newPhoto;
            cout << "Enter the image name to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
            cin >> newPhoto;
            image.saveImage(newPhoto);
            break;
        }
        case 6: {
        string photo;
        cout << "Enter the name of the file: ";
        cin >> photo;
        Image image(photo);
        int degree;
        cout << "Choose the degree you like (90, 180, or 270): ";
        cin >> degree;

        if (degree == 90 || degree == 270) {
            // Transpose the image
            Image transposedImage(image.height, image.width);
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        transposedImage(j, i, k) = image(i, j, k);
                    }
                }
            }

            // Flip the transposed image horizontally to rotate it clockwise by 90 or 270 degrees
            if (degree == 90) {
                for (int i = 0; i < transposedImage.width / 2; ++i) {
                    for (int j = 0; j < transposedImage.height; ++j) {
                        for (int k = 0; k < transposedImage.channels; ++k) {
                            swap(transposedImage(i, j, k), transposedImage(transposedImage.width - 1 - i, j, k));
                        }
                    }
                }
            } else if(degree == 270) { 
                for (int i = 0; i < transposedImage.width; ++i) {
                    for (int j = 0; j < transposedImage.height / 2; ++j) {
                        for (int k = 0; k < transposedImage.channels; ++k) {
                            swap(transposedImage(i, j, k), transposedImage(i, transposedImage.height - 1 - j, k));
                        }
                    }
                }
            }

            string newPhoto;
            cout << "Enter the image name to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
            cin >> newPhoto;
            transposedImage.saveImage(newPhoto);
        } else if (degree == 180) {
            // Flip the image horizontally
            for (int i = 0; i < image.width / 2; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        swap(image(i, j, k), image(image.width - 1 - i, j, k));
                    }
                }
            }

            // Flip the image vertically
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height / 2; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        swap(image(i, j, k), image(i, image.height - 1 - j, k));
                    }
                }
            }

            string newPhoto;
            cout << "Enter the image name to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
            cin >> newPhoto;
            image.saveImage(newPhoto);
        } else {
            cout << "Invalid choice!" << endl;
        }
        break;
    }
        case 7 : {
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
    case 8 : {
            string filename;
        cout << "Please enter the image name u want to crop: ";
        cin >> filename;

        Image image(filename);

        // Get input for the cropping region
        int x, y, width, height;
        cout << "Enter the coordinates of the top-left corner (x, y): ";
        cin >> x >> y;
        cout << "Enter the width and height of the new image: ";
        cin >> width >> height;

        // Perform cropping
        Image croppedImage(width, height);
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                for (int k = 0; k < image.channels; ++k) {
                    croppedImage(i, j, k) = image(x + i, y + j, k);
                }
            }
        }


        cout << "Please enter the image name to store the new image\n";
        cout << "and specify the extension .jpg, .bmp, .png, .tga: ";
        cin >> filename;
        croppedImage.saveImage(filename);
        system(filename.c_str());
        break;
    }
    case 10 : {
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
    case 11 : {


        string filename;
    cout << "Please enter the image you want to resize: ";
    cin >> filename;

    Image image(filename);

    // Get input for the new dimensions
    int newWidth, newHeight;
    cout << "Enter the new width of the image: ";
    cin >> newWidth;
    cout << "Enter the new height of the image: ";
    cin >> newHeight;

    // Calculate scaling ratios
    double widthRatio = (double)newWidth / image.width;
    double heightRatio = (double)newHeight / image.height;

    // Perform resizing with bi-linear interpolation
    Image resizedImage(newWidth, newHeight);
    for (int i = 0; i < newWidth; ++i) {
        for (int j = 0; j < newHeight; ++j) {
            double srcX = (double)i / widthRatio;
            double srcY = (double)j / heightRatio;

            int x1 = (int)srcX;
            int y1 = (int)srcY;
            int x2 = min(x1 + 1, image.width - 1);
            int y2 = min(y1 + 1, image.height - 1);

            double xWeight = srcX - x1;
            double yWeight = srcY - y1;

            for (int k = 0; k < image.channels; ++k) {
                double interpolatedValue = (1 - xWeight) * (1 - yWeight) * image(x1, y1, k) +
                                           xWeight * (1 - yWeight) * image(x2, y1, k) +
                                           (1 - xWeight) * yWeight * image(x1, y2, k) +
                                           xWeight * yWeight * image(x2, y2, k);

                resizedImage(i, j, k) = (unsigned int)interpolatedValue;
            }
        }
    }

    cout << "Please enter the image name to store the new image\n";
    cout << "and specify the extension .jpg, .bmp, .png, .tga: ";
    cin >> filename;
    resizedImage.saveImage(filename);
    system(filename.c_str());

    return 0;
}    
    case 12: { // Add a new case for the blur filter
                string photo;
                cout << "Enter the name of the file: ";
                cin >> photo;
                Image image(photo);

                // Apply the blur filter
                const int blurRadius = 5; // Adjust blur radius as needed
                const int passes = 5;      // Adjust the number of passes

                Image tempImage(image.width, image.height);
                Image blurredImage(image.width, image.height);

                // Multiple passes of simple averaging blur
                for (int pass = 0; pass < passes; ++pass) {
                    for (int i = blurRadius; i < image.width - blurRadius; ++i) {
                        for (int j = blurRadius; j < image.height - blurRadius; ++j) {
                            unsigned int avgRed = 0, avgGreen = 0, avgBlue = 0;
                            // Calculate average of neighboring pixels
                            for (int x = i - blurRadius; x <= i + blurRadius; ++x) {
                                for (int y = j - blurRadius; y <= j + blurRadius; ++y) {
                                    avgRed += image(x, y, 0);
                                    avgGreen += image(x, y, 1);
                                    avgBlue += image(x, y, 2);
                                }
                            }
                            avgRed /= ((2 * blurRadius + 1) * (2 * blurRadius + 1));
                            avgGreen /= ((2 * blurRadius + 1) * (2 * blurRadius + 1));
                            avgBlue /= ((2 * blurRadius + 1) * (2 * blurRadius + 1));

                            // Set the new pixel values to temporary image
                            tempImage(i, j, 0) = avgRed;
                            tempImage(i, j, 1) = avgGreen;
                            tempImage(i, j, 2) = avgBlue;
                        }
                    }
                    // Copy the temporary image back to the original image for the next pass
                    for (int i = 0; i < image.width; ++i) {
                        for (int j = 0; j < image.height; ++j) {
                            image(i, j, 0) = tempImage(i, j, 0);
                            image(i, j, 1) = tempImage(i, j, 1);
                            image(i, j, 2) = tempImage(i, j, 2);
                        }
                    }
                }

                // Copy the final result to the blurredImage
                for (int i = 0; i < image.width; ++i) {
                    for (int j = 0; j < image.height; ++j) {
                        blurredImage(i, j, 0) = image(i, j, 0);
                        blurredImage(i, j, 1) = image(i, j, 1);
                        blurredImage(i, j, 2) = image(i, j, 2);
                    }
                }

                string newPhoto;
                cout << "Enter the image name to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
                cin >> newPhoto;
                blurredImage.saveImage(newPhoto);
                break;
            } 
            
    case 13:  {

        string filename;
        cout << "Please enter the colored image name to turn it into warm filter: ";
        cin >> filename;

        Image image(filename);

        for (int i = 0 ; i < image.width ; ++i) {
            for (int j = 0; j < image.height; ++j) {
                int red = image(i, j, 0);
                int green = image(i, j, 1);
                int blue = image(i, j, 2);

                // Apply warm filter by increasing red and green channels more
                red += 30;
                green += 60;


                // Ensure values stay within [0, 255] range
                red = min(255, max(0, red));
                green = min(255, max(0, green));

                // Set the adjusted RGB values
                image(i, j, 0) = red;
                image(i, j, 1) = green;

                // Blue channel remains unchanged
            }
        }

        cout << "Please enter the image name to store the new image\n";
        cout << "and specify extension .jpg, .bmp, .png, .tga: ";
        cin >> filename;

        image.saveImage(filename);
        system(filename.c_str());
        break;
    }
    case 15 : {// Prompt user for image filename
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
    return 0;}
    case 16: {
        string filename;
        cout << "Please enter the colored image name to turn into a purple filter: ";
        cin >> filename;

        Image image(filename);

        const float brightnessFactor = 0.9f; // Adjust brightness factor as needed

        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                unsigned int red = image(i, j, 0);   // Red channel value
                unsigned int green = image(i, j, 1); // Green channel value
                unsigned int blue = image(i, j, 2);  // Blue channel value

                // Decrease brightness of all channels
                red = static_cast<unsigned int>(red * brightnessFactor);
                green = static_cast<unsigned int>(green * brightnessFactor);
                blue = static_cast<unsigned int>(blue * brightnessFactor);

                // Adjust pixels based on overall brightness to preserve yellow tones
                unsigned int avg = (red + green + blue) / 3;
                if (avg < 200) {
                    red = (10 * red + blue) / 11;         // Red channel contributes more to purple
                    green = (green + 2 * blue) / 3;       // Green channel contributes to purple
                    blue = (red + green + 2 * blue) / 4;  // Blue channel contributes to purple
                }

                // Set the new pixel values
                image(i, j, 0) = red;
                image(i, j, 1) = green;
                image(i, j, 2) = blue;
            }
        }

        cout << "Please enter the image name to store the new image\n";
        cout << "and specify the extension .jpg, .bmp, .png, .tga: ";

        cin >> filename;
        image.saveImage(filename);
        system(filename.c_str());
        break;
    } case 17 : {
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
        default:
            cout << "Invalid choice!" << endl;
            return 1;
        }

        return 0;
    }
