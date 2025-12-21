#include <iostream>
#include <cmath>
#include <iomanip>



// Functions

double add(double num1, double num2) {
    double result = num1 + num2;
    return result;
}

double subtract(double num1, double num2) {
    double result = num1 - num2;
    return result;
}

double multiply(double num1, double num2) {
    double result = num1 * num2;
    return result;
}

double divide(double num1, double num2) {
    do {
        if (num2 == 0) {
            std::cout << "Error: Division by zero is undefined...." << std::endl;
            std::cout << "Enter Number 2 again: ";
            std::cin >> num2;
        }
    } while (num2 == 0);

    double result = num1 / num2; // fixed division order
    return result;
}

// Trigonometric ratios

double sin() {
    double num;
    std::cout << "Enter number in radian: ";
    std::cin >> num;
    double result = std::sin(num);
    return result;
}

double cos() {
    double num;
    std::cout << "Enter number in radian: ";
    std::cin >> num;
    double result = std::cos(num);
    return result;
}

double tan() {
    double num;
    std::cout << "Enter number in radian: ";
    std::cin >> num;
    double result = std::tan(num);
    return result;
}

double negsin() {
    double num;
    std::cout << "Enter number in radian: ";
    std::cin >> num;
    double result = std::asin(num);
    return result;
}

double negcos() {
    double num;
    std::cout << "Enter number in radian: ";
    std::cin >> num;
    double result = std::acos(num);
    return result;
}

double negtan() {
    double num;
    std::cout << "Enter number in radian: ";
    std::cin >> num;
    double result = std::atan(num);
    return result;
}

// Exponential functions

double power() {
    double base;
    std::cout << "Enter base: ";
    std::cin >> base;
    double exponent;
    std::cout << "Enter power: ";
    std::cin >> exponent;
    double result = std::pow(base, exponent);
    return result;
}

double expo() {
    double num;
    std::cout << "Enter a number: ";
    std::cin >> num;
    double result = std::exp(num);
    return result;
}

double logarithm() {
    double num;
    std::cout << "Enter a number: ";
    std::cin >> num;
    double result = std::log(num);
    return result;
}

double logarithm10() {
    double num;
    std::cout << "Enter a number: ";
    std::cin >> num;
    double result = std::log10(num);
    return result;
}

// Roots

double square_root() {
    double num;
    std::cout << "Enter a number: ";
    std::cin >> num;
    double result = std::sqrt(num);
    return result;
}

double cube_root() {
    double num;
    std::cout << "Enter a number: ";
    std::cin >> num;
    double result = std::cbrt(num);
    return result;
}

// Main program

int main() {
    double a, b;
    int choice;
    double answer;
    char user;

    do {
        std::cout << std::setw(70) << "Science Calculator" << std::endl;

        // Menu
        std::cout << "|Basic Operation|" << std::setw(35) << "|Trigonometric Functions|" 
                  << std::setw(35) << "|Exponential_Log Functions|" 
                  << std::setw(30) << "|Roots Function|" << std::endl;

        std::cout << " 1.Addition(+)" << std::setw(23) << " 5.sin()"
                  << std::setw(40) << " 11.exp(e^x)" 
                  << std::setw(40) << " 15.Square root" << std::endl;

        std::cout << " 2.Subtraction(-)" << std::setw(20) << " 6.cos()"
                  << std::setw(45) << " 12.pow(base^exp)" 
                  << std::setw(33) << " 16.Cube Root" << std::endl;

        std::cout << " 3.Multipication(*)" << std::setw(18) << " 7.tan()"
                  << std::setw(37) << " 13.log()" << std::endl;

        std::cout << " 4.Division(/)" << std::setw(26) << " 8.sin^(-1)" 
                  << std::setw(36) << " 14.log10()" << std::endl;

        std::cout << std::setw(40) << "9.cos^(-1)" << std::endl;
        std::cout << std::setw(40) << "10.tan^(-1)" << std::endl;

        // Taking choice from user
        std::cout << "Enter your choice (1-16): ";
        std::cin >> choice;

        // Error handling
        while (choice < 1 || choice > 16) {
            std::cout << "Invalid choice. Please enter a valid option(1-16): ";
            std::cin >> choice;
        }

        switch (choice) {
            case 1: std::cout << "Enter your 1st number:\t"; std::cin >> a;
                    std::cout << "Enter your 2nd number:\t"; std::cin >> b;
                    answer = add(a, b); break;

            case 2: std::cout << "Enter your 1st number:\t"; std::cin >> a;
                    std::cout << "Enter your 2nd number:\t"; std::cin >> b;
                    answer = subtract(a, b); break;

            case 3: std::cout << "Enter your 1st number:\t"; std::cin >> a;
                    std::cout << "Enter your 2nd number:\t"; std::cin >> b;
                    answer = multiply(a, b); break;

            case 4: std::cout << "Enter your 1st number:\t"; std::cin >> a;
                    std::cout << "Enter your 2nd number:\t"; std::cin >> b;
                    answer = divide(a, b); break;

            case 5: answer = sin(); break;
            case 6: answer = cos(); break;
            case 7: answer = tan(); break;
            case 8: answer = negsin(); break;
            case 9: answer = negcos(); break;
            case 10: answer = negtan(); break;
            case 11: answer = expo(); break;
            case 12: answer = power(); break;
            case 13: answer = logarithm(); break;
            case 14: answer = logarithm10(); break;
            case 15: answer = square_root(); break;
            case 16: answer = cube_root(); break;

            default: return 0;
        }

        // Displaying answer
        std::cout << "Result: " << answer << std::endl;
        std::cout << "Do you want to continue? (y/n): ";
        std::cin >> user;
       

    } while (user == 'y' || user == 'Y');

    std::cout << "Exiting Calculator......";
   
}
