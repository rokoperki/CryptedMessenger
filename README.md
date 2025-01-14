# CryptedMessenger

CryptedMessenger is a Qt-based application that provides encryption and decryption functionalities using various algorithms.

## Features

- **Caesar Cipher**: Encrypt and decrypt text using the Caesar cipher.
- **XOR Cipher**: Encrypt and decrypt text using the XOR cipher.
- **Reverse Cipher**: Encrypt and decrypt text by reversing the text.
- **Safe Messages**: Encrypt and decrypt text using the Safe Messages algorithm.
- **File Operations**: Save encrypted text to a file and load text from a file.

## Build Instructions

### Prerequisites

- CMake 3.10 or higher
- Qt 6
- A C++17 compatible compiler

### Steps

1. Clone the repository:
    ```sh
    git clone <repository-url>
    cd CryptedMessenger
    ```

2. Configure the project:
    ```sh
    cmake -B build
    ```

3. Build the project:
    ```sh
    cmake --build build
    ```

4. Run the application:
    ```sh
    ./build/CryptedMessenger
    ```

## File Structure

- `src/`: Contains the source code for the application.
  - `cryptPage.cpp`: Handles encryption operations and file saving.
  - `decryptPage.cpp`: Handles decryption operations and file loading.
  - `algorithmOption.cpp`: Implements the encryption and decryption algorithms.
- `CMakeLists.txt`: CMake configuration file for building the project.

## Usage

### Encrypting Text

1. Enter the text to be encrypted in the input field.
2. Select the desired encryption algorithm.
3. Click the "Encrypt" button.
4. The encrypted text will be displayed in the output field.
5. You can copy the encrypted text to the clipboard or save it to a file.

### Decrypting Text

1. Enter the text to be decrypted in the input field.
2. Select the desired decryption algorithm.
3. Click the "Decrypt" button.
4. The decrypted text will be displayed in the output field.
5. You can copy the decrypted text to the clipboard or load it from a file.

## License

This project is licensed under the MIT License.