#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <set>

struct Point {
    double x, y;

    Point(double x, double y) : x(x), y(y) {}
};

struct Circle {
    Point center;
    double radius;

    Circle(Point c, double r) : center(c), radius(r) {}
};

bool canFormQuadrilateral() {
    return true;
}


double distance(const Point& a, const Point& b) {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// Функция для проверки, лежит ли точка внутри треугольника
bool isPointInsideTriangle(const Point& p, const Point& a, const Point& b, const Point& c) {
    double d1, d2, d3;
    bool has_neg, has_pos;

    auto sign = [](const Point& p1, const Point& p2, const Point& p3) {
        return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
    };

    d1 = sign(p, a, b);
    d2 = sign(p, b, c);
    d3 = sign(p, c, a);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

// три точки образуют треугольник
bool isTriangle(const Point& a, const Point& b, const Point& c) {
    double area = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
    return std::abs(area) > 1e-6; // Проверяем, что площадь не равна нулю с учётом погрешности вычислений
}

// Функция для получения уравнения окружности по трём точкам
Circle getCircleEquation(const Point& A, const Point& B, const Point& C) {
    double D = 2 * (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
    if (D == 0) {
        return Circle(Point(0, 0), -1); // Окружность не определена
    }

    double Ux = ((A.x * A.x + A.y * A.y) * (B.y - C.y) + (B.x * B.x + B.y * B.y) * (C.y - A.y) + (C.x * C.x + C.y * C.y) * (A.y - B.y)) / D;
    double Uy = ((A.x * A.x + A.y * A.y) * (C.x - B.x) + (B.x * B.x + B.y * B.y) * (A.x - C.x) + (C.x * C.x + C.y * C.y) * (B.x - A.x)) / D;
    Point center(Ux, Uy);
    double radius = distance(center, A);
    
    return Circle(center, radius);
}

// Функция для проверки, лежит ли точка внутри круга
bool isInsideCircle(const Point& point, const Circle& circle) {
    return distance(point, circle.center) <= circle.radius;
}

// Функция для чтения точек из файла
std::vector<Point> readPointsFromFile(const std::string& filename) {
    std::vector<Point> points;
    std::ifstream file(filename);
    std::string line;
    double x, y;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        char ignore;
        if (!(iss >> ignore >> x >> ignore >> y >> ignore)) { 
            break; // Ошибка в формате строки
        }
        points.emplace_back(x, y);
    }

    return points;
}

int main() {
    std::setlocale(LC_ALL, "Russian");
    // Чтение точек из файла
    std::vector<Point> points = readPointsFromFile("input.txt");

    // Проверка на минимальное количество точек для выполнения задачи
    if (points.size() < 10) {
        std::cerr << "Недостаточно точек для определения системы" << std::endl;
        return 1;
    }

    // Перебор всех комбинаций треугольников
    for (size_t i = 0; i < points.size() - 2; ++i) {
        for (size_t j = i + 1; j < points.size() - 1; ++j) {
            for (size_t k = j + 1; k < points.size(); ++k) {
                if (isTriangle(points[i], points[j], points[k])) {
                    std::set<size_t> trianglePoints = {i, j, k};

                    // Перебор всех комбинаций окружностей
                    for (size_t a = 0; a < points.size() - 2; ++a) {
                        if (trianglePoints.count(a)) continue;
                        for (size_t b = a + 1; b < points.size() - 1; ++b) {
                            if (trianglePoints.count(b)) continue;
                            for (size_t c = b + 1; c < points.size(); ++c) {
                                if (trianglePoints.count(c)) continue;
                                if (isTriangle(points[a], points[b], points[c])) {
                                    Circle circle = getCircleEquation(points[a], points[b], points[c]);

                                    // Проверяем, что остальные точки не лежат внутри окружности
                                    bool allOutside = true;
                                    for (size_t p = 0; p < points.size(); ++p) {
                                        if (trianglePoints.count(p) || p == a || p == b || p == c) continue;
                                        if (isInsideCircle(points[p], circle)) {
                                            allOutside = false;
                                            break;
                                        }
                                    }

                                    if (allOutside) {
                                        // Перебор всех комбинаций четырехугольников
                                        for (size_t q = 0; q < points.size(); ++q) {
                                            if (trianglePoints.count(q) || q == a || q == b || q == c) continue;
                                            // продолжить перебор для оставшихся точек и проверку четырехугольника...

                                            // Если нашли подходящий четырехугольник
                                            if (canFormQuadrilateral()) {
                                                // Выводим результат
                                                std::cout << "Треугольник: " << i << " " << j << " " << k << std::endl;
                                                std::cout << "Окружность: " << a << " " << b << " " << c << std::endl;
                                                return 0; 
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    std::cout << "Решение не найдено" << std::endl;
    return 0;
}