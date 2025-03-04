# Huffman Compression & Decompression GUI

This is a **PyQt6-based GUI** for Huffman encoding and decoding using `huffman_compressor.exe` and `huffman_decryptor.exe`. The application allows users to **compress text files or direct input** and **decompress binary files with metadata**.

## 📌 Features
- **Compression (Encryption)**:
  - Choose between **Text File Input** or **Direct Text Input**.
  - Uses `huffman_compressor.exe` for encoding.
- **Decompression (Decryption)**:
  - Select **compressed file (`zipped.bin`)** and **metadata (`metadata.txt`)**.
  - Uses `huffman_decryptor.exe` for decoding.
- **Error Handling**:
  - Checks for missing files and displays command output.
- **Simple GUI** using PyQt6.

---

## 🛠 Requirements
- Python 3.x
- PyQt6 (`pip install PyQt6`)
- Compiled `huffman_compressor.exe` and `huffman_decryptor.exe`

- OR run `repo.bat` as administrator for repository download (Automated). 

---

## 🚀 Installation & Usage

1️⃣ **Install Dependencies**:
```sh
pip install PyQt6
```

2️⃣ **Ensure `huffman_compressor.exe` and `huffman_decryptor.exe` are in the same directory.**

3️⃣ **Run the GUI**:
```sh
python GUI.py
```

---

## 📚 How to Use

### 🔹 Compression (Encrypt)
1. Click **"Encrypt (Compress)"**.
2. Choose:
   - **Text File** → Select a `.txt` file.
   - **Direct Text Input** → Enter text manually.
3. The GUI will execute `huffman_compressor.exe`.
4. Compressed data is saved in `zipped.bin` and metadata in `metadata.txt`.

### 🔹 Decompression (Decrypt)
1. Click **"Decrypt (Decompress)"**.
2. Select the compressed **`zipped.bin`** file.
3. Select the **`metadata.txt`** file.
4. The GUI will execute `huffman_decryptor.exe`.
5. The decoded output is displayed.

---

## 🛠 Troubleshooting
- **Error: File not found** → Ensure `huffman_compressor.exe` and `huffman_decryptor.exe` are present.
- **Output not displayed** → Check for errors in the GUI output window.

---

## 📜 License
This project is for educational purposes. Modify and distribute as needed!

---

### ✨ Developed with PyQt6 & C++

