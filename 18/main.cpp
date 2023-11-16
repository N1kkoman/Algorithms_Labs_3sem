#include <iostream>
#include <sstream>

struct Node {
    int key;
    Node* left;
    Node* right;
};

Node* createNode(int key) {
    Node* newNode = new Node();
    if (newNode == nullptr) {
        std::cout << "Ошибка: не удалось выделить память для нового узла." << std::endl;
        exit(1);
    }
    newNode->key = key;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

void insertNode(Node*& root, int key) {
    // Если корневой узел пустой, создаем новый узел и делаем его корневым
    if (root == nullptr) {
        root = createNode(key);
        return;
    }
    // Если ключ меньше ключа корневого узла, рекурсивно вставляем его в левое поддерево
    if (key < root->key) {
        insertNode(root->left, key);
    } else {
        // Иначе, рекурсивно вставляем его в правое поддерево
        insertNode(root->right, key);
    }
}

// Метод для центрального обхода дерева (левое поддерево, корень, правое поддерево)
void inOrderTraversal(Node* root) {
    // Если корневой узел пустой, возвращаемся
    if (root == nullptr) {
        return;
    }
    // Рекурсивно выполняем обход левого поддерева
    inOrderTraversal(root->left);
    // Выводим значение ключа текущего узла
    std::cout << root->key << " ";
    // Рекурсивно выполняем обход правого поддерева
    inOrderTraversal(root->right);
}

int main() {
    std::setlocale(LC_ALL, "Russian");
    Node* root = nullptr;
    int x;
    while (std::cin >> x) {
        // Вводим числа и вставляем их в БДП
        insertNode(root, x);
        if (std::cin.get() == '\n') { 
            break; 
        }
    }

    std::cout << "Отсортированные элементы БДП: ";
    // Выполняем обход БДП в порядке возрастания ключей и выводим значения на экран
    inOrderTraversal(root);

    return 0;
}
