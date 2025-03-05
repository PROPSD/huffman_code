import sys
import subprocess
import os
from PyQt6.QtWidgets import (
    QApplication, QWidget, QVBoxLayout, QPushButton, QFileDialog,
    QTextEdit, QLabel, QInputDialog
)


class HuffmanApp(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle("Huffman Compression & Decompression")
        self.setGeometry(100, 100, 600, 400)

        layout = QVBoxLayout()

        self.label = QLabel("Choose an operation:")
        layout.addWidget(self.label)

        self.encrypt_button = QPushButton("Encrypt (Compress)")
        self.encrypt_button.clicked.connect(self.encrypt)
        layout.addWidget(self.encrypt_button)

        self.decrypt_button = QPushButton("Decrypt (Decompress)")
        self.decrypt_button.clicked.connect(self.decrypt)
        layout.addWidget(self.decrypt_button)

        self.output_text = QTextEdit()
        self.output_text.setReadOnly(True)
        layout.addWidget(self.output_text)

        self.setLayout(layout)

    def encrypt(self):
        choice, ok = QInputDialog.getItem(self, "Choose Input Type",
                                          "How do you want to provide input?",
                                          ["Text File", "Direct Text Input"], 0, False)
        if not ok:
            return

        if choice == "Text File":
            file_name, _ = QFileDialog.getOpenFileName(self, "Select Text File", "",
                                                       "Text Files (*.txt);;All Files (*)")
            if file_name:
                self.run_compressor(["huffman_compressor.exe", file_name])

        elif choice == "Direct Text Input":
            text, ok = QInputDialog.getText(self, "Enter Text", "Enter text to compress:")
            if ok and text:
                temp_file = "temp_input.txt"
                with open(temp_file, "w") as f:
                    f.write(text)
                self.run_compressor(["huffman_compressor.exe", temp_file])

    def decrypt(self):
        metadata_file, _ = QFileDialog.getOpenFileName(self, "Select Metadata File", "",
                                                       "Text Files (*.txt);;All Files (*)")
        if not metadata_file:
            return

        zipped_file, _ = QFileDialog.getOpenFileName(self, "Select Zipped File", "",
                                                     "Binary Files (*.bin);;All Files (*)")
        if not zipped_file:
            return

        self.run_compressor(["huffman_decompressor.exe", metadata_file, zipped_file])

    def run_compressor(self, command):
        if not os.path.exists(command[0]):
            self.output_text.setText(f"Error: {command[0]} not found. Please compile the C++ file first.")
            return

        try:
            result = subprocess.run(command, capture_output=True, text=True)
            self.output_text.setText(result.stdout)
            if result.stderr:
                self.output_text.append("\nErrors:\n" + result.stderr)
        except Exception as e:
            self.output_text.setText(f"Failed to execute {command[0]}: {e}")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = HuffmanApp()
    window.show()
    sys.exit(app.exec())
