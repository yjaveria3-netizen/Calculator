#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>
#include <vector>
#include <string>
#include <algorithm>
#include <complex>
#include <sstream>
#include <fstream>
#include <stack>
#include <cctype>
#include <map>
#include <ctime>
#include <chrono>

// Color Themes
enum ColorTheme
{
    DARK,
    LIGHT,
    MONOCHROME
};
ColorTheme currentTheme = DARK;

// Color code structures for different themes
struct ThemeColors
{
    std::string reset;
    std::string bold;
    std::string primary;
    std::string secondary;
    std::string success;
    std::string warning;
    std::string error;
    std::string accent;
};

ThemeColors darkTheme = {
    "\033[0m",  // reset
    "\033[1m",  // bold
    "\033[36m", // cyan - primary
    "\033[34m", // blue - secondary
    "\033[32m", // green - success
    "\033[33m", // yellow - warning
    "\033[31m", // red - error
    "\033[35m"  // magenta - accent
};

ThemeColors lightTheme = {
    "\033[0m",  // reset
    "\033[1m",  // bold
    "\033[96m", // bright cyan
    "\033[94m", // bright blue
    "\033[92m", // bright green
    "\033[93m", // bright yellow
    "\033[91m", // bright red
    "\033[95m"  // bright magenta
};

ThemeColors monochromeTheme = {
    "\033[0m", // reset
    "\033[1m", // bold
    "\033[1m", // bold for primary
    "\033[0m", // normal for secondary
    "\033[1m", // bold for success
    "\033[0m", // normal for warning
    "\033[1m", // bold for error
    "\033[4m"  // underline for accent
};

ThemeColors *theme = &darkTheme;

// Memory and History
std::vector<double> history;
std::vector<std::string> historyLabels;
double memory = 0.0;
const int MAX_HISTORY = 50;

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
        std::cout << theme->error << "Invalid input! Please enter a valid number." << theme->reset << std::endl;
        clearInput();
    }
}

int getValidChoice(int min, int max)
{
    int choice;
    while (true)
    {
        std::cout << theme->warning << "Enter your choice (" << min << "-" << max << "): " << theme->reset;
        if (std::cin >> choice && choice >= min && choice <= max)
        {
            return choice;
        }
        std::cout << theme->error << "Invalid choice! Please enter a number between "
                  << min << " and " << max << "." << theme->reset << std::endl;
        clearInput();
    }
}

void addToHistory(double value, const std::string &label = "")
{
    history.push_back(value);
    historyLabels.push_back(label);

    if (history.size() > MAX_HISTORY)
    {
        history.erase(history.begin());
        historyLabels.erase(historyLabels.begin());
    }
}

void displayHistory()
{
    if (history.empty())
    {
        std::cout << theme->warning << "\nNo history available yet." << theme->reset << std::endl;
        return;
    }

    std::cout << theme->primary << "\n╔══════════════════ CALCULATION HISTORY ══════════════════╗" << theme->reset << std::endl;
    int start = std::max(0, (int)history.size() - 10);
    for (int i = start; i < history.size(); i++)
    {
        std::cout << theme->secondary << "[" << i << "] " << theme->reset;
        if (!historyLabels[i].empty())
            std::cout << historyLabels[i] << " = ";
        std::cout << theme->success << history[i] << theme->reset << std::endl;
    }
    std::cout << theme->primary << "╚═══════════════════════════════════════════════════════════╝" << theme->reset << std::endl;
}

double getFromHistory()
{
    displayHistory();
    if (history.empty())
        return 0;

    std::cout << theme->warning << "Enter history index to use: " << theme->reset;
    int index;
    std::cin >> index;

    if (index >= 0 && index < history.size())
    {
        std::cout << theme->success << "Using value: " << history[index] << theme->reset << std::endl;
        return history[index];
    }

    std::cout << theme->error << "Invalid index!" << theme->reset << std::endl;
    return 0;
}

// Memory functions
void memoryStore(double value)
{
    memory = value;
    std::cout << theme->success << "Value " << value << " stored in memory." << theme->reset << std::endl;
}

void memoryRecall()
{
    std::cout << theme->success << "Memory: " << memory << theme->reset << std::endl;
}

void memoryClear()
{
    memory = 0;
    std::cout << theme->success << "Memory cleared." << theme->reset << std::endl;
}

void memoryAdd(double value)
{
    memory += value;
    std::cout << theme->success << "Added to memory. New value: " << memory << theme->reset << std::endl;
}

void memorySubtract(double value)
{
    memory -= value;
    std::cout << theme->success << "Subtracted from memory. New value: " << memory << theme->reset << std::endl;
}

// Expression Parser
int getPrecedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

double applyOperation(double a, double b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b == 0)
            throw std::runtime_error("Division by zero");
        return a / b;
    case '^':
        return std::pow(a, b);
    default:
        return 0;
    }
}

double evaluateExpression(const std::string &expr)
{
    std::stack<double> values;
    std::stack<char> ops;

    for (int i = 0; i < expr.length(); i++)
    {
        if (isspace(expr[i]))
            continue;

        if (isdigit(expr[i]) || expr[i] == '.')
        {
            std::string numStr;
            while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.'))
            {
                numStr += expr[i++];
            }
            i--;
            values.push(std::stod(numStr));
        }
        else if (expr[i] == '(')
        {
            ops.push(expr[i]);
        }
        else if (expr[i] == ')')
        {
            while (!ops.empty() && ops.top() != '(')
            {
                double b = values.top();
                values.pop();
                double a = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(applyOperation(a, b, op));
            }
            if (!ops.empty())
                ops.pop(); // Remove '('
        }
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/' || expr[i] == '^')
        {
            // Handle negative numbers
            if (expr[i] == '-' && (i == 0 || expr[i - 1] == '(' || expr[i - 1] == '+' ||
                                   expr[i - 1] == '-' || expr[i - 1] == '*' || expr[i - 1] == '/' || expr[i - 1] == '^'))
            {
                values.push(0);
            }

            while (!ops.empty() && getPrecedence(ops.top()) >= getPrecedence(expr[i]))
            {
                double b = values.top();
                values.pop();
                double a = values.top();
                values.pop();
                char op = ops.top();
                ops.pop();
                values.push(applyOperation(a, b, op));
            }
            ops.push(expr[i]);
        }
    }

    while (!ops.empty())
    {
        double b = values.top();
        values.pop();
        double a = values.top();
        values.pop();
        char op = ops.top();
        ops.pop();
        values.push(applyOperation(a, b, op));
    }

    return values.top();
}

void expressionCalculator()
{
    std::cout << theme->primary << "\n╔══════════ EXPRESSION CALCULATOR ══════════╗" << theme->reset << std::endl;
    std::cout << "Supports: +, -, *, /, ^, ( )\n";
    std::cout << "Example: 3+5*2, (10+5)/3, 2^3+4\n";
    std::cout << theme->primary << "╚════════════════════════════════════════════╝" << theme->reset << std::endl;

    clearInput();
    std::string expr;
    std::cout << theme->warning << "Enter expression: " << theme->reset;
    std::getline(std::cin, expr);

    try
    {
        double result = evaluateExpression(expr);
        std::cout << theme->success << "\nResult: " << theme->bold << result << theme->reset << std::endl;
        addToHistory(result, expr);
    }
    catch (const std::exception &e)
    {
        std::cout << theme->error << "Error: " << e.what() << theme->reset << std::endl;
    }
}

// Complex Number Operations
class ComplexCalculator
{
public:
    static void add()
    {
        std::cout << theme->primary << "\n=== Complex Addition ===" << theme->reset << std::endl;
        double r1 = getValidNumber("Enter real part of first number: ");
        double i1 = getValidNumber("Enter imaginary part of first number: ");
        double r2 = getValidNumber("Enter real part of second number: ");
        double i2 = getValidNumber("Enter imaginary part of second number: ");

        std::complex<double> c1(r1, i1);
        std::complex<double> c2(r2, i2);
        std::complex<double> result = c1 + c2;

        displayComplex(result, "Sum");
    }

    static void multiply()
    {
        std::cout << theme->primary << "\n=== Complex Multiplication ===" << theme->reset << std::endl;
        double r1 = getValidNumber("Enter real part of first number: ");
        double i1 = getValidNumber("Enter imaginary part of first number: ");
        double r2 = getValidNumber("Enter real part of second number: ");
        double i2 = getValidNumber("Enter imaginary part of second number: ");

        std::complex<double> c1(r1, i1);
        std::complex<double> c2(r2, i2);
        std::complex<double> result = c1 * c2;

        displayComplex(result, "Product");
    }

    static void magnitude()
    {
        std::cout << theme->primary << "\n=== Complex Magnitude ===" << theme->reset << std::endl;
        double r = getValidNumber("Enter real part: ");
        double i = getValidNumber("Enter imaginary part: ");

        std::complex<double> c(r, i);
        double mag = std::abs(c);

        std::cout << theme->success << "Magnitude: " << mag << theme->reset << std::endl;
        addToHistory(mag, "magnitude");
    }

    static void phase()
    {
        std::cout << theme->primary << "\n=== Complex Phase/Argument ===" << theme->reset << std::endl;
        double r = getValidNumber("Enter real part: ");
        double i = getValidNumber("Enter imaginary part: ");

        std::complex<double> c(r, i);
        double ph = std::arg(c);

        std::cout << theme->success << "Phase (radians): " << ph << theme->reset << std::endl;
        std::cout << theme->success << "Phase (degrees): " << (ph * 180.0 / M_PI) << theme->reset << std::endl;
        addToHistory(ph, "phase");
    }

    static void conjugate()
    {
        std::cout << theme->primary << "\n=== Complex Conjugate ===" << theme->reset << std::endl;
        double r = getValidNumber("Enter real part: ");
        double i = getValidNumber("Enter imaginary part: ");

        std::complex<double> c(r, i);
        std::complex<double> result = std::conj(c);

        displayComplex(result, "Conjugate");
    }

private:
    static void displayComplex(const std::complex<double> &c, const std::string &label)
    {
        std::cout << theme->success << "\n"
                  << label << ": ";
        std::cout << c.real();
        if (c.imag() >= 0)
            std::cout << " + " << c.imag() << "i";
        else
            std::cout << " - " << std::abs(c.imag()) << "i";
        std::cout << theme->reset << std::endl;
    }
};

void complexNumberMenu()
{
    std::cout << theme->accent << "\n┌─── Complex Number Operations ───┐" << theme->reset << std::endl;
    std::cout << "1. Addition\n";
    std::cout << "2. Multiplication\n";
    std::cout << "3. Magnitude\n";
    std::cout << "4. Phase/Argument\n";
    std::cout << "5. Conjugate\n";

    int choice = getValidChoice(1, 5);

    switch (choice)
    {
    case 1:
        ComplexCalculator::add();
        break;
    case 2:
        ComplexCalculator::multiply();
        break;
    case 3:
        ComplexCalculator::magnitude();
        break;
    case 4:
        ComplexCalculator::phase();
        break;
    case 5:
        ComplexCalculator::conjugate();
        break;
    }
}

// File I/O functions
void saveHistoryToFile()
{
    if (history.empty())
    {
        std::cout << theme->warning << "No history to save." << theme->reset << std::endl;
        return;
    }

    std::ofstream file("calculator_history.txt");
    if (!file.is_open())
    {
        std::cout << theme->error << "Error opening file!" << theme->reset << std::endl;
        return;
    }

    time_t now = time(0);
    file << "Calculator History - " << ctime(&now) << std::endl;
    file << "================================\n\n";

    for (int i = 0; i < history.size(); i++)
    {
        file << "[" << i << "] ";
        if (!historyLabels[i].empty())
            file << historyLabels[i] << " = ";
        file << history[i] << std::endl;
    }

    file.close();
    std::cout << theme->success << "History saved to 'calculator_history.txt'" << theme->reset << std::endl;
}

void saveMatrixToFile(const std::vector<std::vector<double>> &matrix, const std::string &filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cout << theme->error << "Error opening file!" << theme->reset << std::endl;
        return;
    }

    file << "Matrix (" << matrix.size() << "x" << matrix[0].size() << ")\n";
    file << "================================\n\n";

    for (const auto &row : matrix)
    {
        for (double val : row)
        {
            file << std::setw(12) << std::fixed << std::setprecision(4) << val << " ";
        }
        file << std::endl;
    }

    file.close();
    std::cout << theme->success << "Matrix saved to '" << filename << "'" << theme->reset << std::endl;
}

void saveStatisticsToFile(const std::vector<double> &data)
{
    std::ofstream file("statistics_report.txt");
    if (!file.is_open())
    {
        std::cout << theme->error << "Error opening file!" << theme->reset << std::endl;
        return;
    }

    time_t now = time(0);
    file << "Statistics Report - " << ctime(&now) << std::endl;
    file << "================================\n\n";

    double sum = 0, mean, variance = 0;
    for (double num : data)
        sum += num;
    mean = sum / data.size();
    for (double num : data)
        variance += std::pow(num - mean, 2);
    variance /= data.size();

    std::vector<double> sorted = data;
    std::sort(sorted.begin(), sorted.end());
    double median = (sorted.size() % 2 == 0) ? (sorted[sorted.size() / 2 - 1] + sorted[sorted.size() / 2]) / 2.0 : sorted[sorted.size() / 2];

    // Calculate mode
    std::map<double, int> frequency;
    for (double num : data)
        frequency[num]++;

    int maxFreq = 0;
    std::vector<double> modes;
    for (const auto &pair : frequency)
    {
        if (pair.second > maxFreq)
        {
            maxFreq = pair.second;
            modes.clear();
            modes.push_back(pair.first);
        }
        else if (pair.second == maxFreq)
        {
            modes.push_back(pair.first);
        }
    }

    file << "Count: " << data.size() << std::endl;
    file << "Sum: " << sum << std::endl;
    file << "Mean: " << mean << std::endl;
    file << "Median: " << median << std::endl;
    file << "Mode: ";
    if (modes.size() == data.size())
        file << "No mode";
    else
    {
        for (int i = 0; i < modes.size(); i++)
        {
            file << modes[i];
            if (i < modes.size() - 1)
                file << ", ";
        }
    }
    file << std::endl;
    file << "Min: " << *std::min_element(data.begin(), data.end()) << std::endl;
    file << "Max: " << *std::max_element(data.begin(), data.end()) << std::endl;
    file << "Range: " << (*std::max_element(data.begin(), data.end()) - *std::min_element(data.begin(), data.end())) << std::endl;
    file << "Variance: " << variance << std::endl;
    file << "Std Dev: " << std::sqrt(variance) << std::endl;

    file << "\nData Points:\n";
    for (int i = 0; i < data.size(); i++)
    {
        file << "[" << i << "] " << data[i] << std::endl;
    }

    file.close();
    std::cout << theme->success << "Statistics saved to 'statistics_report.txt'" << theme->reset << std::endl;
}

// Theme switcher
void changeTheme()
{
    std::cout << theme->accent << "\n┌─── Color Themes ───┐" << theme->reset << std::endl;
    std::cout << "1. Dark Theme (Default)\n";
    std::cout << "2. Light Theme\n";
    std::cout << "3. Monochrome Theme\n";

    int choice = getValidChoice(1, 3);

    switch (choice)
    {
    case 1:
        theme = &darkTheme;
        currentTheme = DARK;
        std::cout << theme->success << "Dark theme activated!" << theme->reset << std::endl;
        break;
    case 2:
        theme = &lightTheme;
        currentTheme = LIGHT;
        std::cout << theme->success << "Light theme activated!" << theme->reset << std::endl;
        break;
    case 3:
        theme = &monochromeTheme;
        currentTheme = MONOCHROME;
        std::cout << theme->success << "Monochrome theme activated!" << theme->reset << std::endl;
        break;
    }
}

// Basic arithmetic operations
double add(double num1, double num2) { return num1 + num2; }
double subtract(double num1, double num2) { return num1 - num2; }
double multiply(double num1, double num2) { return num1 * num2; }

double divide(double num1, double num2)
{
    while (num2 == 0)
    {
        std::cout << theme->error << "Error: Division by zero is undefined!" << theme->reset << std::endl;
        num2 = getValidNumber("Enter divisor again: ");
    }
    return num1 / num2;
}

double modulus(double num1, double num2)
{
    while (num2 == 0)
    {
        std::cout << theme->error << "Error: Modulus by zero is undefined!" << theme->reset << std::endl;
        num2 = getValidNumber("Enter divisor again: ");
    }
    return std::fmod(num1, num2);
}

double percentage()
{
    double num = getValidNumber("Enter number: ");
    double percent = getValidNumber("Enter percentage: ");
    return (num * percent) / 100.0;
}

// Trigonometric functions
double sine() { return std::sin(getValidNumber("Enter angle in radians: ")); }
double cosine() { return std::cos(getValidNumber("Enter angle in radians: ")); }
double tangent() { return std::tan(getValidNumber("Enter angle in radians: ")); }

// NEW: Reciprocal trigonometric functions
double cosecant()
{
    double angle = getValidNumber("Enter angle in radians: ");
    double sinVal = std::sin(angle);
    if (std::abs(sinVal) < 1e-10)
    {
        std::cout << theme->error << "Error: Cosecant undefined (sin = 0)" << theme->reset << std::endl;
        return std::numeric_limits<double>::infinity();
    }
    return 1.0 / sinVal;
}

double secant()
{
    double angle = getValidNumber("Enter angle in radians: ");
    double cosVal = std::cos(angle);
    if (std::abs(cosVal) < 1e-10)
    {
        std::cout << theme->error << "Error: Secant undefined (cos = 0)" << theme->reset << std::endl;
        return std::numeric_limits<double>::infinity();
    }
    return 1.0 / cosVal;
}

double cotangent()
{
    double angle = getValidNumber("Enter angle in radians: ");
    double tanVal = std::tan(angle);
    if (std::abs(tanVal) < 1e-10)
    {
        std::cout << theme->error << "Error: Cotangent undefined (tan = 0)" << theme->reset << std::endl;
        return std::numeric_limits<double>::infinity();
    }
    return 1.0 / tanVal;
}

double arcsine()
{
    double num = getValidNumber("Enter value [-1, 1]: ");
    while (num < -1 || num > 1)
    {
        std::cout << theme->error << "Error: Input must be between -1 and 1!" << theme->reset << std::endl;
        num = getValidNumber("Enter value [-1, 1]: ");
    }
    return std::asin(num);
}

double arccosine()
{
    double num = getValidNumber("Enter value [-1, 1]: ");
    while (num < -1 || num > 1)
    {
        std::cout << theme->error << "Error: Input must be between -1 and 1!" << theme->reset << std::endl;
        num = getValidNumber("Enter value [-1, 1]: ");
    }
    return std::acos(num);
}

double arctangent() { return std::atan(getValidNumber("Enter value: ")); }
double hyperbolicSine() { return std::sinh(getValidNumber("Enter value: ")); }
double hyperbolicCosine() { return std::cosh(getValidNumber("Enter value: ")); }
double hyperbolicTangent() { return std::tanh(getValidNumber("Enter value: ")); }

// Exponential and logarithmic functions
double power()
{
    double base = getValidNumber("Enter base: ");
    double exponent = getValidNumber("Enter exponent: ");
    return std::pow(base, exponent);
}

double exponential() { return std::exp(getValidNumber("Enter value: ")); }

double naturalLog()
{
    double num = getValidNumber("Enter positive number: ");
    while (num <= 0)
    {
        std::cout << theme->error << "Error: Logarithm undefined for non-positive numbers!" << theme->reset << std::endl;
        num = getValidNumber("Enter positive number: ");
    }
    return std::log(num);
}

double log10Func()
{
    double num = getValidNumber("Enter positive number: ");
    while (num <= 0)
    {
        std::cout << theme->error << "Error: Logarithm undefined for non-positive numbers!" << theme->reset << std::endl;
        num = getValidNumber("Enter positive number: ");
    }
    return std::log10(num);
}

double log2Func()
{
    double num = getValidNumber("Enter positive number: ");
    while (num <= 0)
    {
        std::cout << theme->error << "Error: Logarithm undefined for non-positive numbers!" << theme->reset << std::endl;
        num = getValidNumber("Enter positive number: ");
    }
    return std::log2(num);
}

double logBase()
{
    double num = getValidNumber("Enter positive number: ");
    while (num <= 0)
    {
        std::cout << theme->error << "Error: Logarithm undefined for non-positive numbers!" << theme->reset << std::endl;
        num = getValidNumber("Enter positive number: ");
    }
    double base = getValidNumber("Enter positive base (≠ 1): ");
    while (base <= 0 || base == 1)
    {
        std::cout << theme->error << "Error: Base must be positive and not equal to 1!" << theme->reset << std::endl;
        base = getValidNumber("Enter positive base (≠ 1): ");
    }
    return std::log(num) / std::log(base);
}

// Root functions
double squareRoot()
{
    double num = getValidNumber("Enter non-negative number: ");
    while (num < 0)
    {
        std::cout << theme->error << "Error: Square root of negative number is complex!" << theme->reset << std::endl;
        num = getValidNumber("Enter non-negative number: ");
    }
    return std::sqrt(num);
}

double cubeRoot() { return std::cbrt(getValidNumber("Enter number: ")); }

double nthRoot()
{
    double num = getValidNumber("Enter number: ");
    double n = getValidNumber("Enter root degree: ");
    while (n == 0)
    {
        std::cout << theme->error << "Error: Root degree cannot be zero!" << theme->reset << std::endl;
        n = getValidNumber("Enter root degree: ");
    }
    return std::pow(num, 1.0 / n);
}

// Advanced functions
double absoluteValue() { return std::abs(getValidNumber("Enter number: ")); }

double factorial()
{
    int num;
    while (true)
    {
        num = static_cast<int>(getValidNumber("Enter non-negative integer: "));
        if (num >= 0 && num <= 20)
            break;
        std::cout << theme->error << "Error: Enter a value between 0 and 20!" << theme->reset << std::endl;
    }
    double result = 1;
    for (int i = 2; i <= num; i++)
        result *= i;
    return result;
}

double ceiling() { return std::ceil(getValidNumber("Enter number: ")); }
double floor() { return std::floor(getValidNumber("Enter number: ")); }
double roundNum() { return std::round(getValidNumber("Enter number: ")); }

// NEW: Truncate function
double truncateNum() { return std::trunc(getValidNumber("Enter number: ")); }

// Conversion functions
double degreeToRadian() { return getValidNumber("Enter angle in degrees: ") * M_PI / 180.0; }
double radianToDegree() { return getValidNumber("Enter angle in radians: ") * 180.0 / M_PI; }

// Statistical functions with file save option
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
        variance += std::pow(numbers[i] - mean, 2);
    variance /= n;

    double minVal = *std::min_element(numbers.begin(), numbers.end());
    double maxVal = *std::max_element(numbers.begin(), numbers.end());

    std::vector<double> sorted = numbers;
    std::sort(sorted.begin(), sorted.end());
    double median = (n % 2 == 0) ? (sorted[n / 2 - 1] + sorted[n / 2]) / 2.0 : sorted[n / 2];

    // Calculate mode
    std::map<double, int> frequency;
    for (double num : numbers)
        frequency[num]++;

    int maxFreq = 0;
    std::vector<double> modes;
    for (const auto &pair : frequency)
    {
        if (pair.second > maxFreq)
        {
            maxFreq = pair.second;
            modes.clear();
            modes.push_back(pair.first);
        }
        else if (pair.second == maxFreq)
        {
            modes.push_back(pair.first);
        }
    }

    std::cout << theme->success << "\n=== Statistics ===" << theme->reset << std::endl;
    std::cout << "Count: " << n << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Mean: " << mean << std::endl;
    std::cout << "Median: " << median << std::endl;
    std::cout << "Mode: ";
    if (modes.size() == numbers.size())
        std::cout << "No mode";
    else
    {
        for (int i = 0; i < modes.size(); i++)
        {
            std::cout << modes[i];
            if (i < modes.size() - 1)
                std::cout << ", ";
        }
    }
    std::cout << std::endl;
    std::cout << "Minimum: " << minVal << std::endl;
    std::cout << "Maximum: " << maxVal << std::endl;
    std::cout << "Range: " << (maxVal - minVal) << std::endl;
    std::cout << "Variance: " << variance << std::endl;
    std::cout << "Standard Deviation: " << std::sqrt(variance) << std::endl;

    addToHistory(mean, "mean");

    std::cout << theme->warning << "\nSave to file? (y/n): " << theme->reset;
    char save;
    std::cin >> save;
    if (save == 'y' || save == 'Y')
    {
        saveStatisticsToFile(numbers);
    }
}

// Permutation and Combination
double permutation()
{
    int n = static_cast<int>(getValidNumber("Enter n: "));
    int r = static_cast<int>(getValidNumber("Enter r: "));

    while (n < 0 || r < 0 || r > n || n > 20)
    {
        std::cout << theme->error << "Error: Invalid values! (0 <= r <= n <= 20)" << theme->reset << std::endl;
        n = static_cast<int>(getValidNumber("Enter n: "));
        r = static_cast<int>(getValidNumber("Enter r: "));
    }

    double result = 1;
    for (int i = 0; i < r; i++)
        result *= (n - i);
    return result;
}

double combination()
{
    int n = static_cast<int>(getValidNumber("Enter n: "));
    int r = static_cast<int>(getValidNumber("Enter r: "));

    while (n < 0 || r < 0 || r > n || n > 20)
    {
        std::cout << theme->error << "Error: Invalid values! (0 <= r <= n <= 20)" << theme->reset << std::endl;
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

    std::cout << theme->success << "\n=== Results ===" << theme->reset << std::endl;
    std::cout << "GCD: " << gcdVal << std::endl;
    std::cout << "LCM: " << lcmVal << std::endl;

    addToHistory(gcdVal, "GCD");
    addToHistory(lcmVal, "LCM");
}

// NEW: Prime number checker
bool isPrime(int n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;

    for (int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

void primeChecker()
{
    int num = static_cast<int>(getValidNumber("Enter a positive integer: "));

    if (num <= 0)
    {
        std::cout << theme->error << "Please enter a positive integer!" << theme->reset << std::endl;
        return;
    }

    std::cout << theme->success << "\n=== Prime Check ===" << theme->reset << std::endl;
    std::cout << "Number: " << num << std::endl;

    if (isPrime(num))
    {
        std::cout << theme->success << num << " is a PRIME number!" << theme->reset << std::endl;
    }
    else
    {
        std::cout << theme->warning << num << " is NOT a prime number." << theme->reset << std::endl;

        // Show factors
        std::cout << "Factors: ";
        for (int i = 1; i <= num; i++)
        {
            if (num % i == 0)
                std::cout << i << " ";
        }
        std::cout << std::endl;
    }
}

// Quadratic Equation Solver
void quadraticSolver()
{
    std::cout << theme->primary << "\nSolving: ax² + bx + c = 0" << theme->reset << std::endl;
    double a = getValidNumber("Enter a: ");
    while (a == 0)
    {
        std::cout << theme->error << "Coefficient 'a' cannot be zero!" << theme->reset << std::endl;
        a = getValidNumber("Enter a: ");
    }
    double b = getValidNumber("Enter b: ");
    double c = getValidNumber("Enter c: ");

    double discriminant = b * b - 4 * a * c;

    std::cout << theme->success << "\n=== Solution ===" << theme->reset << std::endl;
    std::cout << "Discriminant: " << discriminant << std::endl;

    if (discriminant > 0)
    {
        double x1 = (-b + std::sqrt(discriminant)) / (2 * a);
        double x2 = (-b - std::sqrt(discriminant)) / (2 * a);
        std::cout << "Two real roots:" << std::endl;
        std::cout << "x₁ = " << x1 << std::endl;
        std::cout << "x₂ = " << x2 << std::endl;
        addToHistory(x1, "root1");
        addToHistory(x2, "root2");
    }
    else if (discriminant == 0)
    {
        double x = -b / (2 * a);
        std::cout << "One real root:" << std::endl;
        std::cout << "x = " << x << std::endl;
        addToHistory(x, "root");
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

// Matrix Operations with file save
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
        for (int j = 0; j < cols; j++)
            matrix1[i][j] = getValidNumber("Element [" + std::to_string(i) + "][" + std::to_string(j) + "]: ");

    std::cout << "\nEnter elements of Matrix 2:" << std::endl;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix2[i][j] = getValidNumber("Element [" + std::to_string(i) + "][" + std::to_string(j) + "]: ");

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result[i][j] = matrix1[i][j] + matrix2[i][j];

    std::cout << theme->success << "\n=== Result Matrix ===" << theme->reset << std::endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            std::cout << std::setw(10) << result[i][j] << " ";
        std::cout << std::endl;
    }

    std::cout << theme->warning << "\nSave to file? (y/n): " << theme->reset;
    char save;
    std::cin >> save;
    if (save == 'y' || save == 'Y')
    {
        saveMatrixToFile(result, "matrix_result.txt");
    }
}

void matrixMultiplication()
{
    int r1, c1, r2, c2;
    std::cout << "Enter rows for Matrix 1: ";
    std::cin >> r1;
    std::cout << "Enter columns for Matrix 1: ";
    std::cin >> c1;
    std::cout << "Enter rows for Matrix 2: ";
    std::cin >> r2;
    std::cout << "Enter columns for Matrix 2: ";
    std::cin >> c2;

    if (c1 != r2)
    {
        std::cout << theme->error << "Error: Matrix 1 columns must equal Matrix 2 rows!" << theme->reset << std::endl;
        return;
    }

    std::vector<std::vector<double>> matrix1(r1, std::vector<double>(c1));
    std::vector<std::vector<double>> matrix2(r2, std::vector<double>(c2));
    std::vector<std::vector<double>> result(r1, std::vector<double>(c2, 0));

    std::cout << "\nEnter elements of Matrix 1:" << std::endl;
    for (int i = 0; i < r1; i++)
        for (int j = 0; j < c1; j++)
            matrix1[i][j] = getValidNumber("Element [" + std::to_string(i) + "][" + std::to_string(j) + "]: ");

    std::cout << "\nEnter elements of Matrix 2:" << std::endl;
    for (int i = 0; i < r2; i++)
        for (int j = 0; j < c2; j++)
            matrix2[i][j] = getValidNumber("Element [" + std::to_string(i) + "][" + std::to_string(j) + "]: ");

    for (int i = 0; i < r1; i++)
        for (int j = 0; j < c2; j++)
            for (int k = 0; k < c1; k++)
                result[i][j] += matrix1[i][k] * matrix2[k][j];

    std::cout << theme->success << "\n=== Result Matrix ===" << theme->reset << std::endl;
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
            std::cout << std::setw(10) << result[i][j] << " ";
        std::cout << std::endl;
    }

    std::cout << theme->warning << "\nSave to file? (y/n): " << theme->reset;
    char save;
    std::cin >> save;
    if (save == 'y' || save == 'Y')
    {
        saveMatrixToFile(result, "matrix_result.txt");
    }
}

// NEW: Matrix Transpose
void matrixTranspose()
{
    int rows, cols;
    std::cout << "Enter number of rows: ";
    std::cin >> rows;
    std::cout << "Enter number of columns: ";
    std::cin >> cols;

    std::vector<std::vector<double>> matrix(rows, std::vector<double>(cols));
    std::vector<std::vector<double>> transpose(cols, std::vector<double>(rows));

    std::cout << "\nEnter elements of Matrix:" << std::endl;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][j] = getValidNumber("Element [" + std::to_string(i) + "][" + std::to_string(j) + "]: ");

    // Transpose
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            transpose[j][i] = matrix[i][j];

    std::cout << theme->success << "\n=== Original Matrix ===" << theme->reset << std::endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            std::cout << std::setw(10) << matrix[i][j] << " ";
        std::cout << std::endl;
    }

    std::cout << theme->success << "\n=== Transposed Matrix ===" << theme->reset << std::endl;
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
            std::cout << std::setw(10) << transpose[i][j] << " ";
        std::cout << std::endl;
    }
}

// Number System Conversions
void numberSystemConversion()
{
    std::cout << theme->accent << "\n┌─── Number System Conversion ───┐" << theme->reset << std::endl;
    std::cout << "1. Decimal to Binary\n";
    std::cout << "2. Decimal to Octal\n";
    std::cout << "3. Decimal to Hexadecimal\n";
    std::cout << "4. Binary to Decimal\n";
    std::cout << "5. Octal to Decimal\n";
    std::cout << "6. Hexadecimal to Decimal\n";

    int choice = getValidChoice(1, 6);
    long long num;
    std::string input;

    switch (choice)
    {
    case 1:
        num = static_cast<long long>(getValidNumber("Enter decimal number: "));
        std::cout << theme->success << "Binary: ";
        if (num == 0)
            std::cout << "0";
        else
        {
            std::string binary = "";
            long long temp = num;
            while (temp > 0)
            {
                binary = (char)('0' + temp % 2) + binary;
                temp /= 2;
            }
            std::cout << binary;
        }
        std::cout << theme->reset << std::endl;
        break;

    case 2:
        num = static_cast<long long>(getValidNumber("Enter decimal number: "));
        std::cout << theme->success << "Octal: " << std::oct << num << std::dec << theme->reset << std::endl;
        break;

    case 3:
        num = static_cast<long long>(getValidNumber("Enter decimal number: "));
        std::cout << theme->success << "Hexadecimal: " << std::hex << num << std::dec << theme->reset << std::endl;
        break;

    case 4:
        clearInput();
        std::cout << "Enter binary number: ";
        std::cin >> input;
        num = std::stoll(input, nullptr, 2);
        std::cout << theme->success << "Decimal: " << num << theme->reset << std::endl;
        addToHistory(num, "binary->decimal");
        break;

    case 5:
        clearInput();
        std::cout << "Enter octal number: ";
        std::cin >> input;
        num = std::stoll(input, nullptr, 8);
        std::cout << theme->success << "Decimal: " << num << theme->reset << std::endl;
        addToHistory(num, "octal->decimal");
        break;

    case 6:
        clearInput();
        std::cout << "Enter hexadecimal number: ";
        std::cin >> input;
        num = std::stoll(input, nullptr, 16);
        std::cout << theme->success << "Decimal: " << num << theme->reset << std::endl;
        addToHistory(num, "hex->decimal");
        break;
    }
}

// Unit Conversions
void unitConversions()
{
    std::cout << theme->accent << "\n┌─── Unit Conversions ───┐" << theme->reset << std::endl;
    std::cout << "1. Celsius to Fahrenheit\n";
    std::cout << "2. Fahrenheit to Celsius\n";
    std::cout << "3. Celsius to Kelvin\n";
    std::cout << "4. Kelvin to Celsius\n";
    std::cout << "5. Meters to Feet\n";
    std::cout << "6. Feet to Meters\n";
    std::cout << "7. Kilometers to Miles\n";
    std::cout << "8. Miles to Kilometers\n";
    std::cout << "9. Kilograms to Pounds\n";
    std::cout << "10. Pounds to Kilograms\n";

    int choice = getValidChoice(1, 10);
    double value, result;

    switch (choice)
    {
    case 1:
        value = getValidNumber("Enter temperature in Celsius: ");
        result = (value * 9.0 / 5.0) + 32;
        std::cout << theme->success << value << "°C = " << result << "°F" << theme->reset << std::endl;
        addToHistory(result, "C->F");
        break;
    case 2:
        value = getValidNumber("Enter temperature in Fahrenheit: ");
        result = (value - 32) * 5.0 / 9.0;
        std::cout << theme->success << value << "°F = " << result << "°C" << theme->reset << std::endl;
        addToHistory(result, "F->C");
        break;
    case 3:
        value = getValidNumber("Enter temperature in Celsius: ");
        result = value + 273.15;
        std::cout << theme->success << value << "°C = " << result << "K" << theme->reset << std::endl;
        addToHistory(result, "C->K");
        break;
    case 4:
        value = getValidNumber("Enter temperature in Kelvin: ");
        result = value - 273.15;
        std::cout << theme->success << value << "K = " << result << "°C" << theme->reset << std::endl;
        addToHistory(result, "K->C");
        break;
    case 5:
        value = getValidNumber("Enter length in meters: ");
        result = value * 3.28084;
        std::cout << theme->success << value << " m = " << result << " ft" << theme->reset << std::endl;
        addToHistory(result, "m->ft");
        break;
    case 6:
        value = getValidNumber("Enter length in feet: ");
        result = value / 3.28084;
        std::cout << theme->success << value << " ft = " << result << " m" << theme->reset << std::endl;
        addToHistory(result, "ft->m");
        break;
    case 7:
        value = getValidNumber("Enter distance in kilometers: ");
        result = value * 0.621371;
        std::cout << theme->success << value << " km = " << result << " mi" << theme->reset << std::endl;
        addToHistory(result, "km->mi");
        break;
    case 8:
        value = getValidNumber("Enter distance in miles: ");
        result = value / 0.621371;
        std::cout << theme->success << value << " mi = " << result << " km" << theme->reset << std::endl;
        addToHistory(result, "mi->km");
        break;
    case 9:
        value = getValidNumber("Enter weight in kilograms: ");
        result = value * 2.20462;
        std::cout << theme->success << value << " kg = " << result << " lbs" << theme->reset << std::endl;
        addToHistory(result, "kg->lbs");
        break;
    case 10:
        value = getValidNumber("Enter weight in pounds: ");
        result = value / 2.20462;
        std::cout << theme->success << value << " lbs = " << result << " kg" << theme->reset << std::endl;
        addToHistory(result, "lbs->kg");
        break;
    }
}

// Memory operations menu
void memoryMenu()
{
    std::cout << theme->accent << "\n┌─── Memory Operations ───┐" << theme->reset << std::endl;
    std::cout << "1. Store (MS)\n";
    std::cout << "2. Recall (MR)\n";
    std::cout << "3. Clear (MC)\n";
    std::cout << "4. Add (M+)\n";
    std::cout << "5. Subtract (M-)\n";

    int choice = getValidChoice(1, 5);

    switch (choice)
    {
    case 1:
    {
        double val = getValidNumber("Enter value to store: ");
        memoryStore(val);
        break;
    }
    case 2:
        memoryRecall();
        break;
    case 3:
        memoryClear();
        break;
    case 4:
    {
        double val = getValidNumber("Enter value to add: ");
        memoryAdd(val);
        break;
    }
    case 5:
    {
        double val = getValidNumber("Enter value to subtract: ");
        memorySubtract(val);
        break;
    }
    }
}

// Display menu
void displayMenu()
{
    std::cout << "\n"
              << theme->bold << theme->primary;
    std::cout << "╔════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║               ULTIMATE SCIENTIFIC CALCULATOR                   ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════════╝\n";
    std::cout << theme->reset;

    std::cout << theme->secondary << "\n┌─── Basic Operations ───┐" << theme->reset << std::endl;
    std::cout << " 1. Addition            2. Subtraction         3. Multiplication\n";
    std::cout << " 4. Division            5. Modulus             6. Absolute Value\n";
    std::cout << " 7. Percentage\n";

    std::cout << theme->secondary << "\n┌─── Trigonometric ───┐" << theme->reset << std::endl;
    std::cout << " 8. sin()               9. cos()              10. tan()\n";
    std::cout << "11. cosec()            12. sec()              13. cot()\n";
    std::cout << "14. arcsin()           15. arccos()           16. arctan()\n";
    std::cout << "17. sinh()             18. cosh()             19. tanh()\n";

    std::cout << theme->secondary << "\n┌─── Exponential & Log ───┐" << theme->reset << std::endl;
    std::cout << "20. Power (x^y)        21. e^x                22. ln(x)\n";
    std::cout << "23. log10(x)           24. log2(x)            25. logₐ(x)\n";

    std::cout << theme->secondary << "\n┌─── Roots & Advanced ───┐" << theme->reset << std::endl;
    std::cout << "26. Square Root        27. Cube Root          28. nth Root\n";
    std::cout << "29. Factorial          30. Ceiling            31. Floor\n";
    std::cout << "32. Round              33. Truncate           34. Statistics\n";

    std::cout << theme->secondary << "\n┌─── Conversions ───┐" << theme->reset << std::endl;
    std::cout << "35. Deg ↔ Rad          36. Number Systems     37. Units\n";

    std::cout << theme->secondary << "\n┌─── Advanced Math ───┐" << theme->reset << std::endl;
    std::cout << "38. Permutation        39. Combination        40. GCD & LCM\n";
    std::cout << "41. Prime Check        42. Quadratic Solver   43. Matrix Add\n";
    std::cout << "44. Matrix Multiply    45. Matrix Transpose\n";

    std::cout << theme->accent << "\n┌─── ADVANCED FEATURES ───┐" << theme->reset << std::endl;
    std::cout << "46. Expression Parser  47. Complex Numbers    48. Memory Ops\n";
    std::cout << "49. View History       50. Save History       51. Use History Value\n";
    std::cout << "52. Change Theme\n";

    std::cout << theme->error << "\n 0. Exit Calculator\n"
              << theme->reset << std::endl;
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
        choice = getValidChoice(0, 52);

        if (choice == 0)
        {
            std::cout << theme->success << "\n╔═══════════════════════════════════════╗\n";
            std::cout << "║  Thank you for using the calculator!  ║\n";
            std::cout << "╚═══════════════════════════════════════╝\n"
                      << theme->reset;
            break;
        }

        bool validOperation = true;

        switch (choice)
        {
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
        case 7:
            result = percentage();
            break;
        case 8:
            result = sine();
            break;
        case 9:
            result = cosine();
            break;
        case 10:
            result = tangent();
            break;
        case 11:
            result = cosecant();
            break;
        case 12:
            result = secant();
            break;
        case 13:
            result = cotangent();
            break;
        case 14:
            result = arcsine();
            break;
        case 15:
            result = arccosine();
            break;
        case 16:
            result = arctangent();
            break;
        case 17:
            result = hyperbolicSine();
            break;
        case 18:
            result = hyperbolicCosine();
            break;
        case 19:
            result = hyperbolicTangent();
            break;
        case 20:
            result = power();
            break;
        case 21:
            result = exponential();
            break;
        case 22:
            result = naturalLog();
            break;
        case 23:
            result = log10Func();
            break;
        case 24:
            result = log2Func();
            break;
        case 25:
            result = logBase();
            break;
        case 26:
            result = squareRoot();
            break;
        case 27:
            result = cubeRoot();
            break;
        case 28:
            result = nthRoot();
            break;
        case 29:
            result = factorial();
            break;
        case 30:
            result = ceiling();
            break;
        case 31:
            result = floor();
            break;
        case 32:
            result = roundNum();
            break;
        case 33:
            result = truncateNum();
            break;
        case 34:
            statistics();
            validOperation = false;
            break;
        case 35:
        {
            std::cout << "1. Degrees to Radians\n2. Radians to Degrees\n";
            int convChoice = getValidChoice(1, 2);
            result = (convChoice == 1) ? degreeToRadian() : radianToDegree();
            break;
        }
        case 36:
            numberSystemConversion();
            validOperation = false;
            break;
        case 37:
            unitConversions();
            validOperation = false;
            break;
        case 38:
            result = permutation();
            break;
        case 39:
            result = combination();
            break;
        case 40:
            gcdLcm();
            validOperation = false;
            break;
        case 41:
            primeChecker();
            validOperation = false;
            break;
        case 42:
            quadraticSolver();
            validOperation = false;
            break;
        case 43:
            matrixAddition();
            validOperation = false;
            break;
        case 44:
            matrixMultiplication();
            validOperation = false;
            break;
        case 45:
            matrixTranspose();
            validOperation = false;
            break;
        case 46:
            expressionCalculator();
            validOperation = false;
            break;
        case 47:
            complexNumberMenu();
            validOperation = false;
            break;
        case 48:
            memoryMenu();
            validOperation = false;
            break;
        case 49:
            displayHistory();
            validOperation = false;
            break;
        case 50:
            saveHistoryToFile();
            validOperation = false;
            break;
        case 51:
            result = getFromHistory();
            break;
        case 52:
            changeTheme();
            validOperation = false;
            break;
        default:
            validOperation = false;
            break;
        }

        if (validOperation)
        {
            std::cout << theme->success << "\n┌─────────────────────┐\n";
            std::cout << "│ Result: " << theme->bold << result << theme->reset << theme->success << "\n";
            std::cout << "└─────────────────────┘\n"
                      << theme->reset;
            addToHistory(result);
        }

        std::cout << theme->warning << "\nContinue? (y/n): " << theme->reset;
        std::cin >> continueCalc;
        clearInput();

    } while (continueCalc == 'y' || continueCalc == 'Y');

    return 0;
}