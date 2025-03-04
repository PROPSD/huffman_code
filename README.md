# Huffman Compression Decoder

## Overview
This project implements a Huffman Compression Decoder in C++. It reads a metadata file (`metadata.txt`) containing Huffman codes for different characters and a binary file (`zipped.bin`) containing the compressed text. The program reconstructs the Huffman tree, decodes the compressed data, and outputs the original text.

## Features
- Reads and parses Huffman codes from `metadata.txt`
- Reads encoded binary data from `zipped.bin`
- Constructs a Huffman tree based on the provided metadata
- Decodes the compressed binary data to retrieve the original text
- Displays the Huffman encoding table

## Files
- `main.cpp`: The main program that executes the decoding process.
- `metadata.txt`: Contains the Huffman encoding table.
- `zipped.bin`: The compressed file that needs to be decoded.

## Compilation and Execution
### Compile the program:
```sh
 g++ -o decoder main.cpp
```

### Run the program:
```sh
 ./decoder
```

## Expected Input Files
### `metadata.txt` Format
Each line should contain a character followed by its Huffman encoding, for example:
```
a 101
b 111
c 110
```

### `zipped.bin`
This file contains the binary-encoded text that needs to be decoded.

## Output
The program will display the Huffman encoding table and the decoded text from `zipped.bin`.

## License
This project is open-source and free to use.

