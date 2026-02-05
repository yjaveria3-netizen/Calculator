#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>
#include <vector>
#include <string>
#include <algorithm>
#include <complex>
#include <sstream>

// Color codes for better UI
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"

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

// Hyperbolic functions
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

// Advanced functions
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

// Conversion functions
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

// Statistical functions
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

    // Find min and max
    double minVal = *std::min_element(numbers.begin(), numbers.end());
    double maxVal = *std::max_element(numbers.begin(), numbers.end());

    // Sort for median
    std::vector<double> sorted = numbers;
    std::sort(sorted.begin(), sorted.end());
    double median;
    if (n % 2 == 0)
    {
        median = (sorted[n / 2 - 1] + sorted[n / 2]) / 2.0;
    }
    else
    {
        median = sorted[n / 2];
    }

    std::cout << GREEN << "\n=== Statistics ===" << RESET << std::endl;
    std::cout << "Count: " << n << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Mean: " << mean << std::endl;
    std::cout << "Median: " << median << std::endl;
    std::cout << "Minimum: " << minVal << std::endl;
    std::cout << "Maximum: " << maxVal << std::endl;
    std::cout << "Range: " << (maxVal - minVal) << std::endl;
    std::cout << "Variance: " << variance << std::endl;
    std::cout << "Standard Deviation: " << std::sqrt(variance) << std::endl;
}

// ========== NEW FEATURES ==========

// Permutation and Combination
double permutation()
{
    int n = static_cast<int>(getValidNumber("Enter n: "));
    int r = static_cast<int>(getValidNumber("Enter r: "));

    while (n < 0 || r < 0 || r > n || n > 20)
    {
        std::cout << RED << "Error: Invalid values! (0 <= r <= n <= 20)" << RESET << std::endl;
        n = static_cast<int>(getValidNumber("Enter n: "));
        r = static_cast<int>(getValidNumber("Enter r: "));
    }

    double result = 1;
    for (int i = 0; i < r; i++)
    {
        result *= (n - i);
    }
    return result;
}

double combination()
{
    int n = static_cast<int>(getValidNumber("Enter n: "));
    int r = static_cast<int>(getValidNumber("Enter r: "));

    while (n < 0 || r < 0 || r > n || n > 20)
    {
        std::cout << RED << "Error: Invalid values! (0 <= r <= n <= 20)" << RESET << std::endl;
        n = static_cast<int>(getValidNumber("Enter n: "));
        r = static_cast<int>(getValidNumber("Enter r: "));
    }

    double numerator = 1, denominator = 1;
    for (int i = 0; i < r; i++)
    {
        numerator *= (n - i);
        denominator *= (i + 1);
    }
    return numerator / denominator;
}

// GCD and LCM
int gcd(int a, int b)
{
    a = std::abs(a);
    b = std::abs(b);
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void gcdLcm()
{
    int a = static_cast<int>(getValidNumber("Enter first integer: "));
    int b = static_cast<int>(getValidNumber("Enter second integer: "));

    int gcdVal = gcd(a, b);
    int lcmVal = std::abs(a * b) / gcdVal;

    std::cout << GREEN << "\n=== Results ===" << RESET << std::endl;
    std::cout << "GCD: " << gcdVal << std::endl;
    std::cout << "LCM: " << lcmVal << std::endl;
}

// Quadratic Equation Solver
void quadraticSolver()
{
    std::cout << CYAN << "\nSolving: ax² + bx + c = 0" << RESET << std::endl;
    double a = getValidNumber("Enter a: ");
    while (a == 0)
    {
        std::cout << RED << "Coefficient 'a' cannot be zero!" << RESET << std::endl;
        a = getValidNumber("Enter a: ");
    }
    double b = getValidNumber("Enter b: ");
    double c = getValidNumber("Enter c: ");

    double discriminant = b * b - 4 * a * c;

    std::cout << GREEN << "\n=== Solution ===" << RESET << std::endl;
    std::cout << "Discriminant: " << discriminant << std::endl;

    if (discriminant > 0)
    {
        double x1 = (-b + std::sqrt(discriminant)) / (2 * a);
        double x2 = (-b - std::sqrt(discriminant)) / (2 * a);
        std::cout << "Two real roots:" << std::endl;
        std::cout << "x₁ = " << x1 << std::endl;
        std::cout << "x₂ = " << x2 << std::endl;
    }
    else if (discriminant == 0)
    {
        double x = -b / (2 * a);
        std::cout << "One real root:" << std::endl;
        std::cout << "x = " << x << std::endl;
    }
    else
    {
        double realPart = -b / (2 * a);
        double imagPart = std::sqrt(-discriminant) / (2 * a);
        std::cout << "Two complex roots:" << std::endl;
        std::cout << "x₁ = " << realPart << " + " << imagPart << "i" << std::endl;
        std::cout << "x₂ = " << realPart << " - " << imagPart << "i" << std::endl;
    }
}

// Matrix Operations
void matrixAddition()
{
    int rows, cols;
    std::cout << "Enter number of rows: ";
    std::cin >> rows;
    std::cout << "Enter number of columns: ";
    std::cin >> cols;

    std::vector<std::vector<double>> matrix1(rows, std::vector<double>(cols));
    std::vector<std::vector<double>> matrix2(rows, std::vector<double>(cols));
    std::vector<std::vector<double>> result(rows, std::vector<double>(cols));

    std::cout << "\nEnter elements of Matrix 1:" << std::endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix1[i][j] = getValidNumber("Element [" + std::to_string(i) + "][" + std::to_string(j) + "]: ");
        }
    }

    std::cout << "\nEnter elements of Matrix 2:" << std::endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix2[i][j] = getValidNumber("Element [" + std::to_string(i) + "][" + std::to_string(j) + "]: ");
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    std::cout << GREEN << "\n=== Result Matrix ===" << RESET << std::endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << std::setw(10) << result[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void matrixMultiplication()
{
    int rows1, cols1, rows2, cols2;
    std::cout << "Matrix 1 - Enter number of rows: ";
    std::cin >> rows1;
    std::cout << "Matrix 1 - Enter number of columns: ";
    std::cin >> cols1;
    std::cout << "Matrix 2 - Enter number of rows: ";
    std::cin >> rows2;
    std::cout << "Matrix 2 - Enter number of columns: ";
    std::cin >> cols2;

    while (cols1 != rows2)
    {
        std::cout << RED << "Error: Matrix 1 columns must equal Matrix 2 rows!" << RESET << std::endl;
        std::cout << "Matrix 1 - Enter number of columns: ";
        std::cin >> cols1;
        std::cout << "Matrix 2 - Enter number of rows: ";
        std::cin >> rows2;
    }

    std::vector<std::vector<double>> matrix1(rows1, std::vector<double>(cols1));
    std::vector<std::vector<double>> matrix2(rows2, std::vector<double>(cols2));
    std::vector<std::vector<double>> result(rows1, std::vector<double>(cols2, 0));

    std::cout << "\nEnter elements of Matrix 1:" << std::endl;
    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols1; j++)
        {
            matrix1[i][j] = getValidNumber("Element [" + std::to_string(i) + "][" + std::to_string(j) + "]: ");
        }
    }

    std::cout << "\nEnter elements of Matrix 2:" << std::endl;
    for (int i = 0; i < rows2; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            matrix2[i][j] = getValidNumber("Element [" + std::to_string(i) + "][" + std::to_string(j) + "]: ");
        }
    }

    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            for (int k = 0; k < cols1; k++)
            {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    std::cout << GREEN << "\n=== Result Matrix ===" << RESET << std::endl;
    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            std::cout << std::setw(10) << result[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Number System Conversions
void numberSystemConversion()
{
    std::cout << CYAN << "\n=== Number System Conversion ===" << RESET << std::endl;
    std::cout << "1. Decimal to Binary\n";
    std::cout << "2. Decimal to Octal\n";
    std::cout << "3. Decimal to Hexadecimal\n";
    std::cout << "4. Binary to Decimal\n";
    std::cout << "5. Octal to Decimal\n";
    std::cout << "6. Hexadecimal to Decimal\n";

    int choice = getValidChoice(1, 6);
    long long num;

    switch (choice)
    {
    case 1:
        num = static_cast<long long>(getValidNumber("Enter decimal number: "));
        std::cout << GREEN << "Binary: ";
        if (num == 0)
            std::cout << "0";
        else
        {
            std::string binary = "";
            long long temp = std::abs(num);
            while (temp > 0)
            {
                binary = std::to_string(temp % 2) + binary;
                temp /= 2;
            }
            if (num < 0)
                std::cout << "-";
            std::cout << binary;
        }
        std::cout << RESET << std::endl;
        break;

    case 2:
        num = static_cast<long long>(getValidNumber("Enter decimal number: "));
        std::cout << GREEN << "Octal: " << std::oct << num << RESET << std::endl;
        break;

    case 3:
        num = static_cast<long long>(getValidNumber("Enter decimal number: "));
        std::cout << GREEN << "Hexadecimal: " << std::hex << std::uppercase << num << RESET << std::endl;
        break;

    case 4:
    {
        std::string binary;
        std::cout << "Enter binary number: ";
        std::cin >> binary;
        long long decimal = 0;
        for (char c : binary)
        {
            if (c != '0' && c != '1')
            {
                std::cout << RED << "Invalid binary number!" << RESET << std::endl;
                return;
            }
            decimal = decimal * 2 + (c - '0');
        }
        std::cout << GREEN << "Decimal: " << decimal << RESET << std::endl;
        break;
    }

    case 5:
    {
        std::string octal;
        std::cout << "Enter octal number: ";
        std::cin >> octal;
        long long decimal = 0;
        for (char c : octal)
        {
            if (c < '0' || c > '7')
            {
                std::cout << RED << "Invalid octal number!" << RESET << std::endl;
                return;
            }
            decimal = decimal * 8 + (c - '0');
        }
        std::cout << GREEN << "Decimal: " << decimal << RESET << std::endl;
        break;
    }

    case 6:
    {
        std::string hex;
        std::cout << "Enter hexadecimal number: ";
        std::cin >> hex;
        long long decimal = 0;
        for (char c : hex)
        {
            c = toupper(c);
            if ((c < '0' || c > '9') && (c < 'A' || c > 'F'))
            {
                std::cout << RED << "Invalid hexadecimal number!" << RESET << std::endl;
                return;
            }
            int digit = (c >= 'A') ? (c - 'A' + 10) : (c - '0');
            decimal = decimal * 16 + digit;
        }
        std::cout << GREEN << "Decimal: " << decimal << RESET << std::endl;
        break;
    }
    }
}

// Unit Conversions
void unitConversions()
{
    std::cout << CYAN << "\n=== Unit Conversions ===" << RESET << std::endl;
    std::cout << "1. Temperature (C ↔ F ↔ K)\n";
    std::cout << "2. Length (m ↔ ft ↔ in)\n";
    std::cout << "3. Weight (kg ↔ lb ↔ oz)\n";
    std::cout << "4. Speed (km/h ↔ mph ↔ m/s)\n";
    std::cout << "5. Area (m² ↔ ft² ↔ acres)\n";
    std::cout << "6. Volume (L ↔ gal ↔ ml)\n";

    int choice = getValidChoice(1, 6);
    double value, result;

    switch (choice)
    {
    case 1: // Temperature
    {
        std::cout << "1. Celsius to Fahrenheit\n";
        std::cout << "2. Fahrenheit to Celsius\n";
        std::cout << "3. Celsius to Kelvin\n";
        std::cout << "4. Kelvin to Celsius\n";
        int tempChoice = getValidChoice(1, 4);
        value = getValidNumber("Enter value: ");
        switch (tempChoice)
        {
        case 1:
            result = (value * 9 / 5) + 32;
            std::cout << GREEN << value << "°C = " << result << "°F" << RESET << std::endl;
            break;
        case 2:
            result = (value - 32) * 5 / 9;
            std::cout << GREEN << value << "°F = " << result << "°C" << RESET << std::endl;
            break;
        case 3:
            result = value + 273.15;
            std::cout << GREEN << value << "°C = " << result << "K" << RESET << std::endl;
            break;
        case 4:
            result = value - 273.15;
            std::cout << GREEN << value << "K = " << result << "°C" << RESET << std::endl;
            break;
        }
        break;
    }

    case 2: // Length
    {
        std::cout << "1. Meters to Feet\n";
        std::cout << "2. Feet to Meters\n";
        std::cout << "3. Meters to Inches\n";
        std::cout << "4. Inches to Meters\n";
        int lenChoice = getValidChoice(1, 4);
        value = getValidNumber("Enter value: ");
        switch (lenChoice)
        {
        case 1:
            result = value * 3.28084;
            std::cout << GREEN << value << " m = " << result << " ft" << RESET << std::endl;
            break;
        case 2:
            result = value / 3.28084;
            std::cout << GREEN << value << " ft = " << result << " m" << RESET << std::endl;
            break;
        case 3:
            result = value * 39.3701;
            std::cout << GREEN << value << " m = " << result << " in" << RESET << std::endl;
            break;
        case 4:
            result = value / 39.3701;
            std::cout << GREEN << value << " in = " << result << " m" << RESET << std::endl;
            break;
        }
        break;
    }

    case 3: // Weight
    {
        std::cout << "1. Kilograms to Pounds\n";
        std::cout << "2. Pounds to Kilograms\n";
        std::cout << "3. Kilograms to Ounces\n";
        std::cout << "4. Ounces to Kilograms\n";
        int weightChoice = getValidChoice(1, 4);
        value = getValidNumber("Enter value: ");
        switch (weightChoice)
        {
        case 1:
            result = value * 2.20462;
            std::cout << GREEN << value << " kg = " << result << " lb" << RESET << std::endl;
            break;
        case 2:
            result = value / 2.20462;
            std::cout << GREEN << value << " lb = " << result << " kg" << RESET << std::endl;
            break;
        case 3:
            result = value * 35.274;
            std::cout << GREEN << value << " kg = " << result << " oz" << RESET << std::endl;
            break;
        case 4:
            result = value / 35.274;
            std::cout << GREEN << value << " oz = " << result << " kg" << RESET << std::endl;
            break;
        }
        break;
    }

    case 4: // Speed
    {
        std::cout << "1. km/h to mph\n";
        std::cout << "2. mph to km/h\n";
        std::cout << "3. m/s to km/h\n";
        std::cout << "4. km/h to m/s\n";
        int speedChoice = getValidChoice(1, 4);
        value = getValidNumber("Enter value: ");
        switch (speedChoice)
        {
        case 1:
            result = value * 0.621371;
            std::cout << GREEN << value << " km/h = " << result << " mph" << RESET << std::endl;
            break;
        case 2:
            result = value / 0.621371;
            std::cout << GREEN << value << " mph = " << result << " km/h" << RESET << std::endl;
            break;
        case 3:
            result = value * 3.6;
            std::cout << GREEN << value << " m/s = " << result << " km/h" << RESET << std::endl;
            break;
        case 4:
            result = value / 3.6;
            std::cout << GREEN << value << " km/h = " << result << " m/s" << RESET << std::endl;
            break;
        }
        break;
    }

    case 5: // Area
    {
        std::cout << "1. m² to ft²\n";
        std::cout << "2. ft² to m²\n";
        std::cout << "3. m² to acres\n";
        std::cout << "4. acres to m²\n";
        int areaChoice = getValidChoice(1, 4);
        value = getValidNumber("Enter value: ");
        switch (areaChoice)
        {
        case 1:
            result = value * 10.7639;
            std::cout << GREEN << value << " m² = " << result << " ft²" << RESET << std::endl;
            break;
        case 2:
            result = value / 10.7639;
            std::cout << GREEN << value << " ft² = " << result << " m²" << RESET << std::endl;
            break;
        case 3:
            result = value / 4046.86;
            std::cout << GREEN << value << " m² = " << result << " acres" << RESET << std::endl;
            break;
        case 4:
            result = value * 4046.86;
            std::cout << GREEN << value << " acres = " << result << " m²" << RESET << std::endl;
            break;
        }
        break;
    }

    case 6: // Volume
    {
        std::cout << "1. Liters to Gallons\n";
        std::cout << "2. Gallons to Liters\n";
        std::cout << "3. Liters to Milliliters\n";
        std::cout << "4. Milliliters to Liters\n";
        int volChoice = getValidChoice(1, 4);
        value = getValidNumber("Enter value: ");
        switch (volChoice)
        {
        case 1:
            result = value * 0.264172;
            std::cout << GREEN << value << " L = " << result << " gal" << RESET << std::endl;
            break;
        case 2:
            result = value / 0.264172;
            std::cout << GREEN << value << " gal = " << result << " L" << RESET << std::endl;
            break;
        case 3:
            result = value * 1000;
            std::cout << GREEN << value << " L = " << result << " mL" << RESET << std::endl;
            break;
        case 4:
            result = value / 1000;
            std::cout << GREEN << value << " mL = " << result << " L" << RESET << std::endl;
            break;
        }
        break;
    }
    }
}

// Display menu
void displayMenu()
{
    std::cout << "\n"
              << BOLD << CYAN;
    std::cout << "╔════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║                ULTIMATE SCIENTIFIC CALCULATOR                  ║\n";
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

    std::cout << BLUE << "\n┌─── Angular Conversions ───┐" << RESET << std::endl;
    std::cout << "29. Degrees to Radians  30. Radians to Degrees\n";

    std::cout << MAGENTA << "\n┌─── Advanced Math ───┐" << RESET << std::endl;
    std::cout << "31. Permutation (nPr)   32. Combination (nCr)   33. GCD & LCM\n";
    std::cout << "34. Quadratic Solver    35. Matrix Addition     36. Matrix Multiplication\n";

    std::cout << MAGENTA << "\n┌─── Conversions ───┐" << RESET << std::endl;
    std::cout << "37. Number Systems      38. Unit Conversions\n";

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
        choice = getValidChoice(0, 38);

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

        // NEW FEATURES
        case 31:
            result = permutation();
            break;
        case 32:
            result = combination();
            break;
        case 33:
            gcdLcm();
            validOperation = false;
            break;
        case 34:
            quadraticSolver();
            validOperation = false;
            break;
        case 35:
            matrixAddition();
            validOperation = false;
            break;
        case 36:
            matrixMultiplication();
            validOperation = false;
            break;
        case 37:
            numberSystemConversion();
            validOperation = false;
            break;
        case 38:
            unitConversions();
            validOperation = false;
            break;

        default:
            validOperation = false;
            break;
        }

        if (validOperation && choice != 28 && choice != 33 && choice != 34 && choice != 35 && choice != 36 && choice != 37 && choice != 38)
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