
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
