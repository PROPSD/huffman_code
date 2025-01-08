#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string.h>
using namespace std;

class node{

    public:
        int value;
        char letter;
        node * left;
        node * right;


        node(char letter){
            this->value = 1;
            this->letter = letter;
            node * left = NULL;
            node * right = NULL;
        }

        node(int value){
            this->value = value;
            this->letter = ' ';
            node * left = nullptr;
            node * right = nullptr;
        }
};


class table{
    public:
        char letter;
        string output;

        table(char letter,string temp){
            this->letter = letter;
            this->output = temp;
        }
};

vector<table> chart;

int read_string(){
    fstream file("metadata.txt",ios::in);
    stringstream text;
    char l;
    while(file.get(l)){
        bool string_ended = false;
        char letter = l;
        file.get(l);file.get(l);
        string temp;
        while(l == '0' or l =='1'){
            temp = temp + l;
            file.get(l);
        }
        chart.push_back(table(letter,temp));
    }
    file.close();
    return chart.size();
    cout << "metadata collected ."<< endl;
}

void display_chart(){
    for(auto it : chart){
        if(it.letter == '\n'){
            cout << "next line  : " << it.output << endl;
            continue; 
        }
        cout << it.letter << " : " << it.output << endl;
    }
}

stringstream get_process_text(){
    stringstream text;
    fstream file("zipped.bin",ios::in);
    char l;
    while(file.get(l)){
        text << l;
    }
    file.close();  
    return text;

}
/*
node * create_tree(node * root){
    node * start = root;
    for(auto it : chart){
        string temp = it.output;
        for(int i = 0; i < temp.size(); i++){
            if(it.output[i] == '0'){
                if(root->left == NULL){
                    node * temp = new node(0);
                    root->left = temp;
                }
                root = root->left;
            }
            if(it.output[i] == '1'){
                if(root->right == NULL){
                    node * temp = new node(0);
                    root->right = temp;
                }
                root = root->right;
            }
        }
        root->letter = it.letter;
        root = start;
    }
    return start;
}
*/

void preorder(node * root){
    if (root == NULL) return;
    preorder(root->left);
    if(root->left == nullptr && root->right == nullptr) cout << root->letter << " : " << root->value  << endl;    
    preorder(root->right);
}

int main(){
    int x = read_string();
    stringstream text = get_process_text();
    node * root = new node(0);
    display_chart();
   // root = create_tree(root);
   // preorder(root);
    return 0;
    
}