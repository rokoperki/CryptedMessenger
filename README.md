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
  - `safeMessagesPage.cpp`: Handles encryption and decryption using the Safe Messages algorithm.
  - `algorithmOption.cpp`: Implements the encryption and decryption algorithms.
- `CMakeLists.txt`: CMake configuration file for building the project.

## License

This project is licensed under the MIT License.
