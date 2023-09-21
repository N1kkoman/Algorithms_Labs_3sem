#include <iostream>
#include <stack>
#include <string>


using namespace std;

// Функция для проверки, является ли символ оператором
bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

// Функция для определения приоритета оператора
int precedence(char ch) {
    if (ch == '+' || ch == '-') {
        return 1;
    }
    else if (ch == '*' || ch == '/') {
        return 2;
    }
    else {
        return 0;
    }
}

// Функция для выполнения арифметической операции
double calculate(double left, double right, char op) {
    if (op == '+') {
        return left + right;
    }
    else if (op == '-') {
        return left - right;
    }
    else if (op == '*') {
        return left * right;
    }
    else if (op == '/') {
        if (right == 0) {
            cout << "Division by zero." << endl;
            exit(1);
        }
        else {
            return left / right;
        }
    }
}

// Функция, которая вычисляет значение арифметического выражения
double evaluateExpression(string expression) {
    // Создаем стеки для чисел и операторов
    stack<double> values;
    stack<char> operators;

    // Проходим по каждому символу в выражении
    for (int i = 0; i < expression.length(); i++) {
        char ch = expression[i];

        // Если символ - открывающая скобка, добавляем ее в стек операторов
        if (ch == '(') {
            operators.push(ch);
        }
        // Если символ - цифра, считываем число и добавляем его в стек значений
        else if (isdigit(ch)) {
            double num = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                num = num * 10 + expression[i] - '0'; // склейка числа из цифр
                i++;
            }
            i--;
            values.push(num);
        }
        // Если символ - оператор, выталкиваем из стека операторов все операторы с большим или равным приоритетом
        // и вычисляем результат для двух последних значений в стеке значений
        else if (isOperator(ch)) {
            while (!operators.empty() && isOperator(operators.top()) && precedence(operators.top()) >= precedence(ch)) {
                double right = values.top();
                values.pop();

                double left = values.top();
                values.pop();

                char op = operators.top();
                operators.pop();

                double result = calculate(left, right, op);
                values.push(result);
            }
            operators.push(ch);
        }
        // Если символ - закрывающая скобка, выталкиваем из стека операторов все операторы до открывающей скобки
        // и вычисляем результат для двух последних значений в стеке значений
        else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                double right = values.top();
                values.pop();

                double left = values.top();
                values.pop();

                char op = operators.top();
                operators.pop();

                double result = calculate(left, right, op);
                values.push(result);
            }
            operators.pop();
        }
        else if (ch == '=') {
            // Проверяем, что после символа '=' ничего нет 
            if (i + 1 < expression.length()) {
                cout << "Invalid expression! Extra characters after '='." << endl;
                exit(1);
            }
            while (!operators.empty()) {
                double right = values.top();
                values.pop();

                double left = values.top();
                values.pop();

                char op = operators.top();
                operators.pop();

                double result = calculate(left, right, op);
                values.push(result);
            }
        }
        else { // Если символ не цифра, оператор, скобка - это неправильный символ
            cout << "Invalid expression! Invalid character: " << ch << endl;
            exit(1);
        }
    }

    return values.top();
}





// Функция для проверки корректности выражения (правильные скобки)
bool isValidExpression(string expression) {
    stack<char> brackets; // Стек для хранения скобок

    for (char ch : expression) {
        if (ch == '(') {
            brackets.push(ch); // Если символ '(' - добавляем его в стек скобок
        }
        else if (ch == ')') {
            if (!brackets.empty() && brackets.top() == '(') {
                brackets.pop(); // Если символ ')' и верхняя скобка в стеке - '(', удаляем верхнюю скобку из стека
            }
            else {
                return false;
            }
        }
    }

    return brackets.empty(); // Если в стеке скобок больше нет, то выражение верное
}

int main() {
    string expression;
    cout << "Enter an arithmetic expression: ";
    getline(cin, expression);

    if (!isValidExpression(expression)) {
        cout << "Invalid expression! Check the parentheses." << endl;
        return 0;
    }

    double result = evaluateExpression(expression);
    cout << "Result: " << result << endl;

    return 0;
}
