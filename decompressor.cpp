#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Node {
public:
    char letter;
    Node *left, *right;

    Node() {
        letter = ' ';
        left = right = nullptr;
    }
};

class Table {
public:
    char letter;
    string output;

    Table(char letter, string temp) {
        this->letter = letter;
        this->output = temp;
    }
};

vector<Table> chart;
string filename;

bool read_string(const string &meta_data_path) {
    ifstream file(meta_data_path);
    if (!file) {
        cerr << "Error: Could not open metadata.txt" << endl;
        return false;
    }

    string line;
    getline(file, line);  
    if (line.find("filename:") != string::npos) {
        filename = line.substr(9); 
    } else {
        filename = "none";
    }

    while (getline(file, line)) {
        if (line.size() < 2) continue;
        char letter = line[0];
        string code = line.substr(2);
        chart.push_back(Table(letter, code));
    }

    file.close();
    cout << "Metadata collected." << endl;
    return true;
}

void display_chart() {
    for (const auto &entry : chart) {
        cout << entry.letter << " : " << entry.output << endl;
    }
}

stringstream get_process_text(const string &zipper_path, int &length) {
    ifstream file(zipper_path, ios::binary);
    stringstream text;

    if (!file) {
        cerr << "Error: Could not open zipped.bin" << endl;
        return text;
    }

    file.seekg(0, ios::end);
    length = file.tellg();
    file.seekg(0, ios::beg);

    text << file.rdbuf();
    file.close();
    return text;
}

Node *create_tree() {
    Node *root = new Node();
    for (const auto &entry : chart) {
        Node *current = root;
        for (char bit : entry.output) {
            if (bit == '0') {
                if (!current->left) current->left = new Node();
                current = current->left;
            } else {
                if (!current->right) current->right = new Node();
                current = current->right;
            }
        }
        current->letter = entry.letter;
    }
    return root;
}

string text_receive(Node *root, stringstream &text, int length) {
    string output;
    char byte;
    Node *current = root;

    while (text.get(byte) && length > 0) {
        for (int i = 7; i >= 0 && length > 0; i--) {
            bool bit = (byte >> i) & 1;
            current = bit ? current->right : current->left;
            if (current->letter != ' ') {
                output += current->letter;
                current = root;
            }
            length--;
        }
    }

    return output;
}

void set_file(const string &output) {
    if (filename == "none") {
        cout << "Decoded Output: " << output << endl;
    } else {
        ofstream file(filename);
        if (!file) {
            cerr << "Error: Could not create output file: " << filename << endl;
            return;
        }
        file << output;
        file.close();
    }
}

void help() {
    cout << "Usage:\n";
    cout << "  decompressor <meta_data_file_path> <zipper_path>\n";
    cout << "Extracted file will be saved with the original filename if available.\n";
}

int main(int argc, char **argv) {
    if (argc != 3) {
        help();
        return 1;
    }

    string meta_data_path = argv[1];
    string zipper_path = argv[2];

    int length = 0;
    if (!read_string(meta_data_path)) return 1;
    
    stringstream text = get_process_text(zipper_path, length);
    if (text.str().empty()) return 1;

    Node *root = create_tree();
    string output = text_receive(root, text, length);
    set_file(output);

    return 0;
}
