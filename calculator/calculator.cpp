#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

using namespace std;

// Функция для суммирования
double sum(const vector<double>& operands) {
    return accumulate(operands.begin(), operands.end(), 0.0);
}

// Функция для вычитания (из первого операнда всех остальных)
double subtract(const vector<double>& operands) {
    if (operands.empty()) return 0.0;
    
    double result = operands[0];
    for (size_t i = 1; i < operands.size(); ++i) {
        result -= operands[i];
    }
    return result;
}

// Функция для вывода справки
void printHelp() {
    cout << "Использование:\n";
    cout << "  calculator [ОПЦИИ] ОПЕРАНД1 ОПЕРАНД2 ОПЕРАНД3 ОПЕРАНД4 ОПЕРАНД5 [ОПЕРАНД6] [ОПЕРАНД7]\n\n";
    cout << "Опции:\n";
    cout << "  -h, --help              Показать эту справку и выйти\n";
    cout << "  -o, --operation OPERATION  Выполнить операцию (summa/subtract)\n\n";
    cout << "Операции:\n";
    cout << "  summa                   Суммирование всех операндов\n";
    cout << "  subtract                Вычитание (из первого операнда всех остальных)\n\n";
    cout << "Требования:\n";
    cout << "  - Количество операндов: от 5 до 7\n";
    cout << "  - Все операнды должны быть числами\n\n";
    cout << "Примеры:\n";
    cout << "  calculator -o summa 1 2 3 4 5\n";
    cout << "  calculator --operation subtract 100 10 5 2 1 2\n";
    cout << "  calculator -o summa 1.5 2.5 3.5 4.5 5.5 6.5 7.5\n";
    cout << "  calculator -h\n";
    cout << "  calculator --help\n";
}

int main(int argc, char* argv[]) {
    // Проверка на запрос справки
    if (argc == 2) {
        string arg = argv[1];
        if (arg == "-h" || arg == "--help") {
            printHelp();
            return 0;
        }
    }

    // Проверка на отсутствие параметров
    if (argc == 1) {
        printHelp();
        return 0;
    }

    string operation;
    vector<double> operands;

    // Парсинг аргументов командной строки
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        
        if (arg == "--operation" || arg == "-o") {
            if (i + 1 < argc) {
                operation = argv[++i];
            } else {
                cerr << "Ошибка: отсутствует значение для " << arg << endl;
                return 1;
            }
        } else if (arg == "-h" || arg == "--help") {
            printHelp();
            return 0;
        } else {
            // Парсинг операндов
            try {
                double operand = stod(arg);
                operands.push_back(operand);
            } catch (const exception& e) {
                cerr << "Ошибка: неверный формат операнда: " << arg << endl;
                return 1;
            }
        }
    }

    // Проверка наличия операции
    if (operation.empty()) {
        cerr << "Ошибка: не указана операция. Используйте --operation или -o" << endl;
        cerr << "Используйте -h или --help для просмотра справки" << endl;
        return 1;
    }

    // Проверка количества операндов
    if (operands.size() < 5 || operands.size() > 7) {
        cerr << "Ошибка: количество операндов должно быть от 5 до 7. Получено: " 
                  << operands.size() << endl;
        cerr << "Используйте -h или --help для просмотра справки" << endl;
        return 1;
    }

    // Выполнение операции
    double result;
    if (operation == "summa") {
        result = sum(operands);
        cout << "Сумма: ";
        for (size_t i = 0; i < operands.size(); ++i) {
            cout << operands[i];
            if (i < operands.size() - 1) cout << " + ";
        }
        cout << " = " << result << endl;
    } else if (operation == "subtract") {
        result = subtract(operands);
        cout << "Вычитание: ";
        cout << operands[0];
        for (size_t i = 1; i < operands.size(); ++i) {
            cout << " - " << operands[i];
        }
        cout << " = " << result << endl;
    } else {
        cerr << "Ошибка: неизвестная операция: " << operation << endl;
        cerr << "Поддерживаемые операции: summa, subtract" << endl;
        cerr << "Используйте -h или --help для просмотра справки" << endl;
        return 1;
    }

    return 0;
}
