case 5: { // Flip Image
        string photo;
        cout << "Enter the name of the file: ";
        cin >> photo;
        Image image(photo);

        // Prompt user to choose flip direction
        cout << "Choose flip direction:\n";
        cout << "1. Horizontal Flip\n";
        cout << "2. Vertical Flip\n";
        int flipChoice;
        cin >> flipChoice;

        if (flipChoice == 1) { // Horizontal Flip
            for (int i = 0; i < image.width / 2; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        swap(image(i, j, k), image(image.width - 1 - i, j, k));
                    }
                }
            }
        }
        else if (flipChoice == 2) { // Vertical Flip
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

        // Save and display the new image
        string newPhoto;
        cout << "Enter the image name to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
        cin >> newPhoto;
        image.saveImage(newPhoto);
        system(newPhoto.c_str());
        break;
    }
    default:
        cout << "Invalid choice!" << endl;
        return 1;
    }

    return 0;
}
