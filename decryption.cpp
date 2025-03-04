#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Node {
public:
    int value;
    char letter;
    Node *left, *right;

    Node(char letter) {
        this->value = 1;
        this->letter = letter;
        this->left = nullptr;
        this->right = nullptr;
    }

    Node(int value) {
        this->value = value;
        this->letter = ' ';
        this->left = nullptr;
        this->right = nullptr;
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

int read_string() {
    fstream file("metadata.txt", ios::in);
    if (!file) {
        cerr << "Error: Could not open metadata.txt" << endl;
        return 0;
    }

    char l;
    while (file.get(l)) {
        file.get(l);
        file.get(l); 
        string temp;

        while (l == '0' || l == '1') {
            temp += l;
            file.get(l);
        }

        chart.push_back(Table(l, temp));
    }

    file.close();
    cout << "Metadata collected." << endl;
    return chart.size();
}

void display_chart() {
    for (auto it : chart) {
        if (it.letter == '\n') {
            cout << "Newline : " << it.output << endl;
        } else {
            cout << it.letter << " : " << it.output << endl;
        }
    }
}

stringstream get_process_text(int &length) {
    stringstream text;
    fstream file("zipped.bin", ios::in | ios::binary);
    
    if (!file) {
        cerr << "Error: Could not open zipped.bin" << endl;
        return text;
    }

    char l;
    while (file.get(l)) {
        text << l;
        length++;
    }

    file.close();
    return text;
}

Node *create_tree(Node *root) {
    Node *start = root;
    for (auto it : chart) {
        string temp = it.output;
        for (char bit : temp) {
            if (bit == '0') {
                if (root->left == nullptr)
                    root->left = new Node(0);
                root = root->left;
            } else if (bit == '1') {
                if (root->right == nullptr)
                    root->right = new Node(0);
                root = root->right;
            }
        }
        root->letter = it.letter;
        root = start;
    }
    return start;
}

void preorder(Node *root) {
    if (root == nullptr)
        return;
    preorder(root->left);
    if (root->left == nullptr && root->right == nullptr)
        cout << root->letter << " : " << root->value << endl;
    preorder(root->right);
}

string text_receive(Node *root, stringstream &text, int &length) {
    string output;
    char l;
    while (text.get(l) && length > 0) {
        Node *temp = root;
        for (int i = 7; i >= 0 && length > 0; i--) { 
            length--;
            bool bit = (l >> i) & 1;
            temp = bit ? temp->right : temp->left;
            if (temp->letter != ' ') {
                output += temp->letter;
                break;
            }
        }
    }
    return output;
}

int main() {
    int length = 0;
    read_string();
    stringstream text = get_process_text(length);
    Node *root = new Node(0);
    display_chart();
    root = create_tree(root);
    preorder(root);
    string output = text_receive(root, text, length);
    cout << "Decoded Output: " << output << endl;
    return 0;
}
