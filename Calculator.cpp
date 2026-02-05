#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>
#include <vector>
#include <string>

// Color codes for better UI
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RED "\033[31m"
#define BLUE "\033[34m"

// Utility functions
void clearInput()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

double getValidNumber(const std::string &prompt)
{
    double num;
    while (true)
    {
        std::cout << prompt;
        if (std::cin >> num)
        {
            return num;
        }
        std::cout << RED << "Invalid input! Please enter a valid number." << RESET << std::endl;
        clearInput();
    }
}

int getValidChoice(int min, int max)
{
    int choice;
    while (true)
    {
        std::cout << YELLOW << "Enter your choice (" << min << "-" << max << "): " << RESET;
        if (std::cin >> choice && choice >= min && choice <= max)
        {
            return choice;
        }
        std::cout << RED << "Invalid choice! Please enter a number between "
                  << min << " and " << max << "." << RESET << std::endl;
        clearInput();
    }
}

// Basic arithmetic operations
double add(double num1, double num2)
{
    return num1 + num2;
}

double subtract(double num1, double num2)
{
    return num1 - num2;
}

double multiply(double num1, double num2)
{
    return num1 * num2;
}

double divide(double num1, double num2)
{
    while (num2 == 0)
    {
        std::cout << RED << "Error: Division by zero is undefined!" << RESET << std::endl;
        num2 = getValidNumber("Enter divisor again: ");
    }
    return num1 / num2;
}

double modulus(double num1, double num2)
{
    while (num2 == 0)
    {
        std::cout << RED << "Error: Modulus by zero is undefined!" << RESET << std::endl;
        num2 = getValidNumber("Enter divisor again: ");
    }
    return std::fmod(num1, num2);
}

// Trigonometric functions
double sine()
{
    double num = getValidNumber("Enter angle in radians: ");
    return std::sin(num);
}

double cosine()
{
    double num = getValidNumber("Enter angle in radians: ");
    return std::cos(num);
}

double tangent()
{
    double num = getValidNumber("Enter angle in radians: ");
    return std::tan(num);
}

double arcsine()
{
    double num = getValidNumber("Enter value [-1, 1]: ");
    while (num < -1 || num > 1)
    {
        std::cout << RED << "Error: Input must be between -1 and 1!" << RESET << std::endl;
        num = getValidNumber("Enter value [-1, 1]: ");
    }
    return std::asin(num);
}

double arccosine()
{
    double num = getValidNumber("Enter value [-1, 1]: ");
    while (num < -1 || num > 1)
    {
        std::cout << RED << "Error: Input must be between -1 and 1!" << RESET << std::endl;
        num = getValidNumber("Enter value [-1, 1]: ");
    }
    return std::acos(num);
}

double arctangent()
{
    double num = getValidNumber("Enter value: ");
    return std::atan(num);
}

// Hyperbolic functions (NEW)
double hyperbolicSine()
{
    double num = getValidNumber("Enter value: ");
    return std::sinh(num);
}

double hyperbolicCosine()
{
    double num = getValidNumber("Enter value: ");
    return std::cosh(num);
}

double hyperbolicTangent()
{
    double num = getValidNumber("Enter value: ");
    return std::tanh(num);
}

// Exponential and logarithmic functions
double power()
{
    double base = getValidNumber("Enter base: ");
    double exponent = getValidNumber("Enter exponent: ");
    return std::pow(base, exponent);
}

double exponential()
{
    double num = getValidNumber("Enter value: ");
    return std::exp(num);
}

double naturalLog()
{
    double num = getValidNumber("Enter positive number: ");
    while (num <= 0)
    {
        std::cout << RED << "Error: Logarithm undefined for non-positive numbers!" << RESET << std::endl;
        num = getValidNumber("Enter positive number: ");
    }
    return std::log(num);
}

double log10()
{
    double num = getValidNumber("Enter positive number: ");
    while (num <= 0)
    {
        std::cout << RED << "Error: Logarithm undefined for non-positive numbers!" << RESET << std::endl;
        num = getValidNumber("Enter positive number: ");
    }
    return std::log10(num);
}

double log2()
{
    double num = getValidNumber("Enter positive number: ");
    while (num <= 0)
    {
        std::cout << RED << "Error: Logarithm undefined for non-positive numbers!" << RESET << std::endl;
        num = getValidNumber("Enter positive number: ");
    }
    return std::log2(num);
}

// Root functions
double squareRoot()
{
    double num = getValidNumber("Enter non-negative number: ");
    while (num < 0)
    {
        std::cout << RED << "Error: Square root of negative number is complex!" << RESET << std::endl;
        num = getValidNumber("Enter non-negative number: ");
    }
    return std::sqrt(num);
}

double cubeRoot()
{
    double num = getValidNumber("Enter number: ");
    return std::cbrt(num);
}

double nthRoot()
{
    double num = getValidNumber("Enter number: ");
    double n = getValidNumber("Enter root degree: ");
    while (n == 0)
    {
        std::cout << RED << "Error: Root degree cannot be zero!" << RESET << std::endl;
        n = getValidNumber("Enter root degree: ");
    }
    return std::pow(num, 1.0 / n);
}

// Advanced functions (NEW)
double absoluteValue()
{
    double num = getValidNumber("Enter number: ");
    return std::abs(num);
}

double factorial()
{
    int num;
    while (true)
    {
        num = static_cast<int>(getValidNumber("Enter non-negative integer: "));
        if (num >= 0 && num <= 20)
            break;
        std::cout << RED << "Error: Enter a value between 0 and 20!" << RESET << std::endl;
    }
    double result = 1;
    for (int i = 2; i <= num; i++)
    {
        result *= i;
    }
    return result;
}

double ceiling()
{
    double num = getValidNumber("Enter number: ");
    return std::ceil(num);
}

double floor()
{
    double num = getValidNumber("Enter number: ");
    return std::floor(num);
}

double roundNum()
{
    double num = getValidNumber("Enter number: ");
    return std::round(num);
}

// Conversion functions (NEW)
double degreeToRadian()
{
    double degrees = getValidNumber("Enter angle in degrees: ");
    return degrees * M_PI / 180.0;
}

double radianToDegree()
{
    double radians = getValidNumber("Enter angle in radians: ");
    return radians * 180.0 / M_PI;
}

// Statistical functions (NEW)
void statistics()
{
    int n;
    std::cout << "How many numbers? ";
    std::cin >> n;

    std::vector<double> numbers(n);
    double sum = 0, mean, variance = 0;

    for (int i = 0; i < n; i++)
    {
        numbers[i] = getValidNumber("Enter number " + std::to_string(i + 1) + ": ");
        sum += numbers[i];
    }

    mean = sum / n;

    for (int i = 0; i < n; i++)
    {
        variance += std::pow(numbers[i] - mean, 2);
    }
    variance /= n;

    std::cout << GREEN << "\n=== Statistics ===" << RESET << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Mean: " << mean << std::endl;
    std::cout << "Variance: " << variance << std::endl;
    std::cout << "Standard Deviation: " << std::sqrt(variance) << std::endl;
}

// Display menu
void displayMenu()
{
    std::cout << "\n"
              << BOLD << CYAN;
    std::cout << "╔════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║           ADVANCED SCIENTIFIC CALCULATOR                       ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════════╝\n";
    std::cout << RESET;

    std::cout << BLUE << "\n┌─── Basic Operations ───┐" << RESET << std::endl;
    std::cout << " 1. Addition (+)         2. Subtraction (-)      3. Multiplication (*)\n";
    std::cout << " 4. Division (/)         5. Modulus (%)          6. Absolute Value\n";

    std::cout << BLUE << "\n┌─── Trigonometric Functions ───┐" << RESET << std::endl;
    std::cout << " 7. sin()                8. cos()                9. tan()\n";
    std::cout << "10. arcsin()            11. arccos()            12. arctan()\n";
    std::cout << "13. sinh()              14. cosh()              15. tanh()\n";

    std::cout << BLUE << "\n┌─── Exponential & Logarithmic ───┐" << RESET << std::endl;
    std::cout << "16. Power (x^y)         17. e^x                 18. ln(x)\n";
    std::cout << "19. log10(x)            20. log2(x)\n";

    std::cout << BLUE << "\n┌─── Root Functions ───┐" << RESET << std::endl;
    std::cout << "21. Square Root         22. Cube Root           23. nth Root\n";

    std::cout << BLUE << "\n┌─── Advanced Functions ───┐" << RESET << std::endl;
    std::cout << "24. Factorial (n!)      25. Ceiling             26. Floor\n";
    std::cout << "27. Round               28. Statistics          \n";

    std::cout << BLUE << "\n┌─── Conversions ───┐" << RESET << std::endl;
    std::cout << "29. Degrees to Radians  30. Radians to Degrees\n";

    std::cout << RED << "\n 0. Exit Calculator\n"
              << RESET << std::endl;
}

int main()
{
    double a, b, result;
    int choice;
    char continueCalc;

    std::cout << std::fixed << std::setprecision(6);

    do
    {
        displayMenu();
        choice = getValidChoice(0, 30);

        if (choice == 0)
        {
            std::cout << GREEN << "\n╔═══════════════════════════════════════╗\n";
            std::cout << "║  Thank you for using the calculator!  ║\n";
            std::cout << "╚═══════════════════════════════════════╝\n"
                      << RESET;
            break;
        }

        bool validOperation = true;

        switch (choice)
        {
        // Basic operations
        case 1:
            a = getValidNumber("Enter first number: ");
            b = getValidNumber("Enter second number: ");
            result = add(a, b);
            break;
        case 2:
            a = getValidNumber("Enter first number: ");
            b = getValidNumber("Enter second number: ");
            result = subtract(a, b);
            break;
        case 3:
            a = getValidNumber("Enter first number: ");
            b = getValidNumber("Enter second number: ");
            result = multiply(a, b);
            break;
        case 4:
            a = getValidNumber("Enter dividend: ");
            b = getValidNumber("Enter divisor: ");
            result = divide(a, b);
            break;
        case 5:
            a = getValidNumber("Enter first number: ");
            b = getValidNumber("Enter second number: ");
            result = modulus(a, b);
            break;
        case 6:
            result = absoluteValue();
            break;

        // Trigonometric functions
        case 7:
            result = sine();
            break;
        case 8:
            result = cosine();
            break;
        case 9:
            result = tangent();
            break;
        case 10:
            result = arcsine();
            break;
        case 11:
            result = arccosine();
            break;
        case 12:
            result = arctangent();
            break;
        case 13:
            result = hyperbolicSine();
            break;
        case 14:
            result = hyperbolicCosine();
            break;
        case 15:
            result = hyperbolicTangent();
            break;

        // Exponential and logarithmic
        case 16:
            result = power();
            break;
        case 17:
            result = exponential();
            break;
        case 18:
            result = naturalLog();
            break;
        case 19:
            result = log10();
            break;
        case 20:
            result = log2();
            break;

        // Roots
        case 21:
            result = squareRoot();
            break;
        case 22:
            result = cubeRoot();
            break;
        case 23:
            result = nthRoot();
            break;

        // Advanced functions
        case 24:
            result = factorial();
            break;
        case 25:
            result = ceiling();
            break;
        case 26:
            result = floor();
            break;
        case 27:
            result = roundNum();
            break;
        case 28:
            statistics();
            validOperation = false;
            break;

        // Conversions
        case 29:
            result = degreeToRadian();
            break;
        case 30:
            result = radianToDegree();
            break;

        default:
            validOperation = false;
            break;
        }

        if (validOperation && choice != 28)
        {
            std::cout << GREEN << "\n┌─────────────────────┐\n";
            std::cout << "│ Result: " << BOLD << result << RESET << GREEN << "\n";
            std::cout << "└─────────────────────┘\n"
                      << RESET;
        }

        std::cout << YELLOW << "\nDo you want to perform another calculation? (y/n): " << RESET;
        std::cin >> continueCalc;
        clearInput();

    } while (continueCalc == 'y' || continueCalc == 'Y');

    return 0;
}