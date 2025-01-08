#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;
void gather_string(string);
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

vector<node*> charecter;
vector<table> chart;
/*
string modify_name(string &file_name){
    int l = file_name.length();
    int pos = -1;
    for(int i=0;i<l;i++){
        if (file_name[i] != '.') pos++;
        else break;
    }
    pos++;
    string temp = "_compressed";
    for(char it : temp){
        file_name.insert(file_name.begin() + pos, it);
        pos++;
    }
    cout << file_name;
    return file_name;
}
*/

void get_strings(string file_name) {
    fstream file(file_name, ios::in);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << file_name << endl;
        return;
    }

    char ch;
    int i=0;
    string temp;
    while (file.get(ch)) { 
        i+=1;
        temp = temp + ch;        
    }
    temp += '\0';
    cout << "A total of "<< i <<" charecters have been read .";
    gather_string(temp);
    file.close();
}

void swap_node(node* &a, node* &b) {
    node temp =* a;
    *a =* b;
   * b = temp;
}

void sort(){
    int l = charecter.size();
    for(int i=0;i<l;i++){
        for(int j=0;j<l-i-1;j++){
            if (charecter[j]->value > charecter[j+1]->value){
                swap_node(charecter[j],charecter[j+1]);
            }
        }
    }
}
void single_sort(){
    int l = charecter.size();
    for(int i=0;i<l;i++){
        if (charecter[i]->value > charecter[i+1]->value){
                swap_node(charecter[i],charecter[i+1]);
            }
            else break;

    }
}

void print(){
    for(auto it : charecter){
        cout << it->letter << "  " << it->value << endl;
    }
}


node * tree(){
    sort();
    while(charecter.size() > 1){
        
        print();
        node * new_node = new node(charecter[0]->value + charecter[1]->value);
        new_node->left = charecter[0];
        new_node->right = charecter[1]; 
        charecter.erase(charecter.begin());
        charecter.erase(charecter.begin());
        charecter.push_back(new_node);
        single_sort();

    }
    return charecter[0];
}

void assign_string(node* root, string temp, vector<table>& chart) {
    if (root == NULL) return;

    if (root->letter != ' ') { // Leaf node
        chart.push_back(table(root->letter, temp));
        cout << "Assigned code to character [" 
             << (root->letter == ' ' ? "Space" : string(1, root->letter)) 
             << "]: " << temp << endl;
    } else { // Internal node
        assign_string(root->left, temp + '0', chart);
        assign_string(root->right, temp + '1', chart);
    }
}

void gather_string(string str) {
    for (char it : str) {
        bool found = false;
        for (int i = 0; i < charecter.size(); i++) {
            if (charecter[i]->letter == it) {
                charecter[i]->value++;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "New character: [" << (it == ' ' ? "Space" : string(1, it)) << "]" << endl;
            charecter.push_back(new node(it));
        }
    }
}


node * start(){
    sort();
    node * root = tree();
    assign_string(root,"", chart);

    for(auto it : chart){
        if (it.letter == '\n'){
            cout << " \n " << it.output << endl;
            continue;   
        }
        cout << it.letter << " : " << it.output << endl;
    }
    return root;
}

stringstream print_strings(string file_name) {
    fstream initial(file_name, ios::in);
    stringstream output;

    if (!initial.is_open()) {
        cerr << "Error opening file!" << endl;
        return output;
    }

    char l;
    while (initial.get(l)) {
        bool found = false;
        for (auto& it : chart) {
            if (it.letter == l) {
                output << it.output;
                found = true;
                break;
            }
        }
        if (!found) {
            cerr << "Error: Character [" 
                 << (l == ' ' ? "Space" : string(1, l)) 
                 << "] not found in chart!" << endl;
        }
    }
    initial.close();
    return output;
}


int binary(string temp) {
    int sum = 0;
    int len = temp.length();

    for (int i = 0; i < len; ++i) {
        if (temp[len - 1 - i] == '1') {
            sum += (1 << i); 
        }
    }
    return sum;
}
void store_metadata(){
    string name = "metadata.txt";
    fstream file(name,ios::app);
    for(auto it : chart){
        file << it.letter <<":"<< it.output << endl;
    }
    file.close();
}

stringstream convert_binary(stringstream &output){
    
    stringstream total;
    char l;
    string temp;
    while (output.get(l))
    {
        total << static_cast<char>(l);
    }
    return total;
}

void send_text(stringstream &str,string file_name){
    fstream file(file_name,ios::out);
    char l;
    while(str.get(l)){
        file << l;
    }
    file.close();
}


int main(){

    string file_name;
    //cout << "\nEnter the file name with extension (test.txt) to compress : ";
    file_name = "test.txt";
    //getline(cin,file_name);
    get_strings(file_name);
    node * root = start();
    stringstream output = print_strings(file_name);
    stringstream str = convert_binary(output);
    //file_name = modify_name(file_name);
    file_name = "zipped.bin";
    send_text(str,file_name);
    store_metadata();

    return 0;

    
}