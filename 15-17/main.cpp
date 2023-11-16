#include <iostream>
#include <stack>
#include <sstream>

// Класс узла дерева
class Node {
public:
    int value; // Значение узла
    Node* left; // Левый потомок
    Node* right; // Правый потомок

    // Конструктор узла
    Node(int value = 0) {
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
    }

    // Метод для вставки узла в дерево
    static void insert(Node* node, int value) {
        // Если значение корневого узла равно 0, то устанавливаем значение входного узла в значение value
        if (node->value == 0) {
            node->value = value;
            return;
        }
        // Если значение value меньше значения текущего узла, проверяем левый подузел
        if (value < node->value) {
            // Если левый подузел пустой, создаем новый узел с значением value и делаем его левым подузлом текущего узла
            if (node->left == nullptr) {
                node->left = new Node(value);
            }
            // Если левый подузел не пустой, рекурсивно вызываем метод insert для левого подузла
            else {
                insert(node->left, value);
            }
        }
        // Если значение value больше или равно значению текущего узла, проверяем правый подузел
        else if (value >= node->value) {
            // Если правый подузел пустой, создаем новый узел с значением value и делаем его правым подузлом текущего узла
            if (node->right == nullptr) {
                node->right = new Node(value);
            }
            // Если правый подузел не пустой, рекурсивно вызываем метод insert для правого подузла
            else {
                insert(node->right, value);
            }
        }
    }


    // Метод для поиска узла в дереве
    static Node* search(Node* node, int value) {
        // Если текущий узел пустой, возвращаем nullptr
        if (node == nullptr) {
            return nullptr;
        }
        // Если значение текущего узла равно искомому значению, возвращаем текущий узел
        if (node->value == value) {
            return node;
        }
        // Если искомое значение меньше значения текущего узла, рекурсивно выполняем поиск в левом поддереве
        if (value < node->value) {
            return search(node->left, value);
        }
        // Если искомое значение больше или равно значению текущего узла, рекурсивно выполняем поиск в правом поддереве
        else {
            return search(node->right, value);
        }
    }


    // Метод для поиска узла с минимальным значением в дереве
    static Node* getMin(Node* node) {
        // Если узел пустой, возвращаем nullptr
        if (node == nullptr) {
            return nullptr;
        }
        // Если у узла нет левого подузла, то это минимальный элемент
        if (node->left == nullptr) {
            return node;
        }
        // Если есть левое подузел, рекурсивно вызываем этот же метод для него
        return getMin(node->left);
    }


    // Метод для поиска узла с максимальным значением в дереве
    static Node* getMax(Node* node) {
        // Если узел равен nullptr, значит достигнут конец дерева и возвращается nullptr
        if (node == nullptr) {
            return nullptr;
        }
        // Если правый подузел узла равен nullptr, значит текущий узел является максимальным,
        // поэтому он возвращается
        if (node->right == nullptr) {
            return node;
        }
        // Если правый подузел не равен nullptr, рекурсивно вызывается функция getMax
        // для правого подузла, чтобы найти максимальный узел в правом поддереве
        return getMax(node->right);
    }


    // Метод для удаления узла из дерева
    static Node* deleteNode(Node* node, int value) {
        // Если узел пустой, возвращаем nullptr
        if (node == nullptr) {
            return nullptr;
        }
        // Если значение для удаления меньше значения текущего узла,
        // рекурсивно вызываем функцию для левого поддерева
        else if (value < node->value) {
            node->left = deleteNode(node->left, value);
        }
        // Если значение для удаления больше значения текущего узла,
        // рекурсивно вызываем функцию для правого поддерева
        else if (value > node->value) {
            node->right = deleteNode(node->right, value);
        }
        // Если значение для удаления равно значению текущего узла
        else {
            // Если у текущего узла нет левого или правого поддерева,
            // заменяем текущий узел на его непустой подузел (если есть)
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            // Если у текущего узла есть и левое, и правое поддерево,
            // находим минимальный узел в правом поддереве,
            // заменяем значение текущего узла на значение минимального узла,
            // а затем рекурсивно вызываем функцию для удаления минимального узла из правого поддерева
            else {
                Node* minRight = getMin(node->right);
                node->value = minRight->value;
                node->right = deleteNode(node->right, minRight->value);
            }
        }
        // Возвращаем обновленный узел
        return node;
    }


    // Метод для центрального обхода дерева (левое поддерево, корень, правое поддерево)
    static void inorderTraversal(Node* node) {
        if (node == nullptr) {
            return;
        }
        // Рекурсивно обходим левое поддерево
        inorderTraversal(node->left);
        // Выводим значение текущего узла
        std::cout << node->value << " ";
        // Рекурсивно обходим правое поддерево
        inorderTraversal(node->right);
    }


    // Метод для прямого обхода дерева (корень, левое поддерево, правое поддерево)
    static void preorderTraversal(Node* node) {
        // Если узел пустой, возвращаемся
        if (node == nullptr) {
            return;
        }
        // Выводим значение текущего узла
        std::cout << node->value << " ";
        // Рекурсивно вызываем прямой обход для левого поддерева
        preorderTraversal(node->left);
        // Рекурсивно вызываем прямой обход для правого поддерева
        preorderTraversal(node->right);
    }


    // Метод для концевого обхода дерева (левое поддерево, правое поддерево, корень)
    static void postorderTraversal(Node* node) {
        // Если узел пустой, возвращаемся
        if (node == nullptr) {
            return;
        }
        // Рекурсивно вызываем обход левого поддерева
        postorderTraversal(node->left);
        // Рекурсивно вызываем обход правого поддерева
        postorderTraversal(node->right);
        // Выводим значение узла
        std::cout << node->value << " ";
    }


    // Метод для прямого обхода дерева с использованием стека
    static void stackPreorderTraversal(Node* node) {
        // Создаем пустой стек для хранения узлов дерева
        std::stack<Node*> stack;
        // Пока есть узлы в дереве или в стеке
        while (node != nullptr || !stack.empty()) {
            if (node != nullptr) {
                std::cout << node->value << " ";
                // Если у узла есть правый потомок, помещаем его в стек
                if (node->right != nullptr) {
                    stack.push(node->right);
                }
                // Переходим к левому потомку
                node = node->left;
            }
            else {
                // Если узел пустой, извлекаем последний узел из стека и переходим к его правому потомку
                node = stack.top();
                stack.pop();
            }
        }
    }


    // Метод для создания дерева из строки вида "(1,2,(3,4))"
    void setWithLine(std::string line) {
        std::string notNumbers = "(), ";
        int end = 0; // Индекс конца очередного числа
        std::string tempLine = line; // Копия исходной строки
        while (tempLine.length() > 0) { // Пока строка не пуста
            if (notNumbers.find(tempLine[end]) != std::string::npos) { // Если текущий символ не является числом
                std::string num = tempLine.substr(0, end); // Получаем подстроку с числом
                if (!num.empty()) { // Если подстрока не пустая
                    insert(this, std::stoi(num)); // Преобразуем подстроку в число и добавляем его в дерево
                }
                tempLine = tempLine.substr(end + 1); // Обрезаем строку до следующего числа
                end = 0; // Сбрасываем индекс конца числа
            }
            else {
                end++; // Увеличиваем индекс конца числа
            }
        }
    }


    // Метод для вывода дерева в строку вида "(1,(2,),3)"
    static void printWithLine(Node* node) {
        // Если узел пустой, выходим из функции
        if (node == nullptr) {
            return;
        }
        // Выводим значение узла
        std::cout << node->value;
        // Если у узла есть хотя бы один потомок, выводим открывающую скобку
        if (node->left != nullptr || node->right != nullptr) {
            std::cout << " (";
        }
        // Рекурсивно вызываем функцию для левого поддерева
        printWithLine(node->left);
        // Если у узла есть хотя бы один потомок, выводим запятую
        if (node->left != nullptr || node->right != nullptr) {
            std::cout << ", ";
        }
        // Рекурсивно вызываем функцию для правого поддерева
        printWithLine(node->right);
        // Если у узла есть хотя бы один потомок, выводим закрывающую скобку
        if (node->left != nullptr || node->right != nullptr) {
            std::cout << ")";
        }
    }
};

int main() {
    std::cout << "input a binary tree: " << std::endl;
    std::string newline;
    std::getline(std::cin, newline);

    Node* Tree = new Node();
    Tree->setWithLine(newline);
    while (true) {
        std::cout << std::endl;
        std::cout << "What do you want to do with the tree?" << std::endl;
        std::cout << "1) insert" << std::endl;
        std::cout << "2) delete" << std::endl;
        std::cout << "3) search" << std::endl;
        std::cout << "4) print preorder" << std::endl;
        std::cout << "5) print inorder" << std::endl;
        std::cout << "6) print postorder" << std::endl;
        std::cout << "7) print with linear bracket view" << std::endl;
        std::cout << "8) print stack preorder" << std::endl;
        std::cout << "0) exit" << std::endl;
        int event;
        std::cin >> event;
        std::cin.ignore();

        switch (event) {
        case 1: {
            std::cout << "input a number to insert: ";
            int num;
            std::cin >> num;
            std::cin.ignore();
            Node::insert(Tree, num);
            break;
        }
        case 2: {
            std::cout << "input a number to delete: ";
            int num;
            std::cin >> num;
            std::cin.ignore();
            Node::deleteNode(Tree, num);
            break;
        }
        case 3: {
            std::cout << "input a number to search: ";
            int num;
            std::cin >> num;
            std::cin.ignore();
            Node* temp = Node::search(Tree, num);
            Node::printWithLine(temp);
            break;
        }
        case 4: {
            Node::preorderTraversal(Tree);
            break;
        }
        case 5: {
            Node::inorderTraversal(Tree);
            break;
        }
        case 6: {
            Node::postorderTraversal(Tree);
            break;
        }
        case 7: {
            Node::printWithLine(Tree);
            break;
        }
        case 8: {
            Node::stackPreorderTraversal(Tree);
            break;
        }
        case 0: {
            return 0;
        }
        }
    }
}

//         8
//        / \
//       /   \
//      3    10
//     / \     \
//    1   6     14
//       / \   /
//      4   7 13
