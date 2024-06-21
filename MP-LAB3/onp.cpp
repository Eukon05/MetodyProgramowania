#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;

/*
    Uwaga!
    Program wykorzystuje skladnie jezyka C++ w wersji 17, aby go uruchomic nalezy upewnic sie, ze wybrany przez nas kompilator obsluguje te wersje jezyka lub nowsza!
*/

int getPriority(char c) {
    switch (c) {
    case '+':
    case '-':
        return 1;

    case '*':
    case '/':
    case 'm':
        return 2;

    case 's':
    case '^':
        return 3;

    case '(':
    case ')':
        return 0;

    default:
        return -1;
    }
}

void popOperator(stack<char>& operators, string& result) {
    if (char top = operators.top(); top == 's')
        result += "sqrt";
    else if (top == 'm')
        result += "mod";
    else
        result += top;

    operators.pop();
    result += ' ';
}

void popOperands(stack<double>& operands, double& left, double& right) {
    right = operands.top();
    operands.pop();
    left = operands.top();
    operands.pop();
}

vector<string> splitString(string param) {
    vector<string> parsed;

    string current = "";
    for (int i = 0; i < param.length(); i++) {
        if (param[i] == ' ') {
            parsed.push_back(current);
            current = "";
        }
        else {
            current += param[i];
        }
    }
    parsed.push_back(current);
    return parsed;
}

string createONP(string equation) {
    vector<string> parsed = splitString(equation);
    stack<char> operators;

    string result = "", current;

    char first, top;
    int topPriority;
    bool isPower;

    for (int i = 0; i < parsed.size(); i++) {
        current = parsed[i];
        first = current[0];

        if (first == '=') {
            break;
        }

        switch (first) {
        case '(': {
            operators.push(first);
            break;
        }

        case ')': {
            while (operators.top() != '(') {
                popOperator(operators, result);
            }
            operators.pop();
            break;
        }

        default: {
            if (int p = getPriority(first); p != -1) {
                while (!operators.empty()) {
                    top = operators.top();
                    topPriority = getPriority(top);
                    isPower = first == '^';

                    if ((isPower && p < topPriority) || (!isPower && p <= topPriority)) {
                        popOperator(operators, result);
                    }
                    else {
                        break;
                    }
                }
                operators.push(first);
            }
            else {
                result += current;
                result += ' ';
            }
            break;
        }
        }
    }

    // I put this logic here, in case the user forgot to put '=' at the end of the equation
    while (!operators.empty()) {
        popOperator(operators, result);
    }
    result += '=';
    return result;
}

double calculateONP(string equation) {
    vector<string> parsed = splitString(equation);
    stack<double> operands;

    string current;
    double left;
    double right;

    for (int i = 0; i < parsed.size(); i++) {
        current = parsed[i];

        if (current == "=") break;

        switch (current[0]) {
        case '+': {
            popOperands(operands, left, right);
            operands.push(left + right);
            break;
        }

        case '-': {
            popOperands(operands, left, right);
            operands.push(left - right);
            break;
        }

        case '*': {
            popOperands(operands, left, right);
            operands.push(left * right);
            break;
        }

        case '/': {
            popOperands(operands, left, right);
            operands.push(left / right);
            break;
        }

        case 'm': {
            if (current == "mod") {
                popOperands(operands, left, right);
                operands.push(fmod(left, right));
            }
            break;
        }

        case 's': {
            if (current == "sqrt") {
                right = operands.top();
                operands.pop();
                operands.push(sqrt(right));
            }
            break;
        }

        case '^': {
            popOperands(operands, left, right);
            operands.push(pow(left, right));
            break;
        }
        default: {
            for (int i = 0; i < current.length(); i++) {
                if (!isdigit(current[i])) {
                    cout << "Wprowadzone wyrazenie jest nieprawidlowe! Zawiera nieznane znaki!";
                    exit(-1);
                }
            }
            operands.push(stod(current));
            break;
        }
        }
    }
    double result = operands.top();
    operands.pop();

    if (!operands.empty()) {
        cout << "Wprowadzone wyrazenie jest nieprawidlowe! Na stosie pozostaly operandy!";
        exit(-1);
    }

    return result;
}

int main() {
    ofstream wy("wyjscie.txt");

    if (!wy.is_open()) {
        cout << "Nie mozna otworzyc pliku wyjscie.txt";
        exit(-1);
    }

    cout << "Lukasz Konieczny - LK4 - LAB 3" << endl;
    cout << "Program do obliczania wartosci dzialania" << endl;
    cout << "Jesli chcesz podac dzialanie z klawiaury, wpisz 1. W przeciwnym wypadku sprobujemy pobrac je z pliku wejscie.txt" << endl;
    cout << "Wpisz swoj wybor: ";

    int choice;
    string equation = "";

    cin >> choice;

    if (choice == 1) {
        cout << "Podaj dzialanie (w jednej linii): ";
        getline(cin, equation); //We have to get rid of garbage characters clogging the standard input
        getline(cin, equation);
    }
    else {
        ifstream we("wejscie.txt");

        if (!we.is_open()) {
            cout << "Nie mozna otworzyc pliku wejscie.txt";
            exit(-1);
        }

        getline(we, equation);
        we.close();
    }

    string onp = createONP(equation);
    cout << "Dzialanie po zamianie na ONP: " << onp << endl;

    double result =  calculateONP(onp);
    cout << "Wynik dzialania: " << result << endl;

    wy << result;
    cout << "Zapisano do pliku wyjscie.txt";

    wy.close();
    return 0;
}