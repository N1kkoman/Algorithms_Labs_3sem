#include <iostream>
#include <stack>
#include <string>
#include <sstream>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

Node* buildTree(const string& treeInput) {
    if (treeInput.empty()) {
        return nullptr;
    }

    stack<Node*> st;
    Node* root = nullptr;

    stringstream ss(treeInput);
    string token;
    while (getline(ss, token, ' ')) {
        if (token == "" || token == "(") {
            continue;
        }
        else if (token == ")") {
            Node* right = st.top();
            st.pop();
            Node* left = st.top();
            st.pop();

            Node* parent = st.top();
            st.pop();

            parent->left = left;
            parent->right = right;

            st.push(parent);
        }
        else {
            int value = stoi(token);
            Node* node = new Node(value);
            st.push(node);

            if (root == nullptr) {
                root = node;
            }
        }
    }

    return root;
}

string treeToString(Node* root) {
    if (root == nullptr) {
        return "";
    }

    string result = "";
    stack<Node*> st;
    st.push(root);

    while (!st.empty()) {
        Node* current = st.top();
        st.pop();

        result += to_string(current->data) + " ";
        if (current->right != nullptr) {
            st.push(current->right);
        }
        if (current->left != nullptr) {
            st.push(current->left);
        }
    }

    return result;
}

Node* searchNode(Node* root, int value) {
    if (root == nullptr || root->data == value) {
        return root;
    }

    if (value < root->data) {
        return searchNode(root->left, value);
    }
    else {
        return searchNode(root->right, value);
    }
}

Node* insertNode(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }

    if (value < root->data) {
        root->left = insertNode(root->left, value);
    }
    else {
        root->right = insertNode(root->right, value);
    }

    return root;
}

Node* deleteNode(Node* root, int value) {
    if (root == nullptr) {
        return root;
    }

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    }
    else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    }
    else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = root->right;
        while (temp->left != nullptr) {
            temp = temp->left;
        }

        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

int main() {
    string treeInput;
    cout << "Введите дерево одной строкой: ";
    getline(cin, treeInput);

    Node* root = buildTree(treeInput);

    int choice;
    do {
        cout << endl;
        cout << "Меню операций:" << endl;
        cout << "1. Добавить вершину БДП" << endl;
        cout << "2. Удалить вершину БДП" << endl;
        cout << "3. Найти вершину БДП" << endl;
        cout << "4. Вывести БДП" << endl;
        cout << "5. Выход" << endl;
        cout << "Введите номер операции: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int value;
            cout << "Введите значение для добавления: ";
            cin >> value;
            root = insertNode(root, value);
            break;
        }
        case 2: {
            int value;
            cout << "Введите значение для удаления: ";
            cin >> value;
            root = deleteNode(root, value);
            break;
        }
        case 3: {
            int value;
            cout << "Введите значение для поиска: ";
            cin >> value;
            Node* node = searchNode(root, value);
            if (node) {
                cout << "Вершина найдена" << endl;
            }
            else {
                cout << "Вершина не найдена" << endl;
            }
            break;
        }
        case 4: {
            string treeString = treeToString(root);
            cout << "БДП: " << treeString << endl;
            break;
        }
        case 5:
            break;
        default:
            cout << "Неверный номер операции" << endl;
        }
    } while (choice != 5);

    // Освобождение памяти
    // ...

    return 0;
}
