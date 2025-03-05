# Huffman Compression & Decompression

This project implements **Huffman Encoding and Decoding** in C++ with a **GUI interface in Python (PyQt6)** for ease of use.

## Features
- Compress text files using Huffman Encoding
- Decompress Huffman-encoded binary files
- Python GUI for easy interaction
- Command-line interface for advanced users

## Getting Started

### Prerequisites
Ensure you have the following installed:
- **C++ Compiler (GCC/MinGW/MSVC)**
- **Python 3**
- **PyQt6** (for GUI)

Install PyQt6:
```sh
pip install PyQt6
```
OR

Run `repo.bat` for windows for automatic python repository download


### Compilation
#### **Compile the Compressor (C++)**
```sh
g++ -o huffman_compressor compressor.cpp
```
#### **Compile the Decompressor (C++)**
```sh
g++ -o huffman_decryptor decryptor.cpp
```

### Running the GUI
Run the Python GUI:
```sh
python gui.py
```

## Usage

### **Compression (CLI Mode)**
To compress a file:
```sh
huffman_compressor -p input.txt
```
OR, to compress direct text input:
```sh
huffman_compressor -t "your text here"
```
This generates:
- `zipped.bin` (compressed file)
- `metadata.txt` (Huffman table for decompression)

### **Decompression (CLI Mode)**
To decompress:
```sh
huffman_decryptor metadata.txt zipped.bin
```
This restores the original text.

### **Using the GUI**
1. Open `gui.py`
2. Choose **Encrypt (Compress)** or **Decrypt (Decompress)**
3. Select the required files
4. View the output in the GUI

## File Structure
```
 Huffman Compression Project
│── huffman_compressor.cpp  # Compressor Code
│── huffman_decryptor.cpp   # Decompressor Code
│── gui.py                  # PyQt6 GUI
│── README.md               # Documentation
│── .gitignore              # Ignore compiled files
```

## Notes
- Ensure `metadata.txt` is always kept with `zipped.bin` for decompression.
- The GUI automatically detects missing files and errors.

## License
This project is open-source. Feel free to modify and distribute!

---

