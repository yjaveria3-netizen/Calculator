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

    int choice = getValidChoice(1, 4);

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

    file << "Count: " << data.size() << std::endl;
    file << "Sum: " << sum << std::endl;
    file << "Mean: " << mean << std::endl;
    file << "Median: " << median << std::endl;
    file << "Min: " << *std::min_element(data.begin(), data.end()) << std::endl;
    file << "Max: " << *std::max_element(data.begin(), data.end()) << std::endl;
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

// Trigonometric functions
double sine() { return std::sin(getValidNumber("Enter angle in radians: ")); }
double cosine() { return std::cos(getValidNumber("Enter angle in radians: ")); }
double tangent() { return std::tan(getValidNumber("Enter angle in radians: ")); }

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

    std::cout << theme->success << "\n=== Statistics ===" << theme->reset << std::endl;
    std::cout << "Count: " << n << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Mean: " << mean << std::endl;
    std::cout << "Median: " << median << std::endl;
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
        std::cout << theme->error << "Error: Matrix 1 columns must equal Matrix 2 rows!" << theme->reset << std::endl;
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
        for (int j = 0; j < cols1; j++)
            matrix1[i][j] = getValidNumber("Element [" + std::to_string(i) + "][" + std::to_string(j) + "]: ");

    std::cout << "\nEnter elements of Matrix 2:" << std::endl;
    for (int i = 0; i < rows2; i++)
        for (int j = 0; j < cols2; j++)
            matrix2[i][j] = getValidNumber("Element [" + std::to_string(i) + "][" + std::to_string(j) + "]: ");

    for (int i = 0; i < rows1; i++)
        for (int j = 0; j < cols2; j++)
            for (int k = 0; k < cols1; k++)
                result[i][j] += matrix1[i][k] * matrix2[k][j];

    std::cout << theme->success << "\n=== Result Matrix ===" << theme->reset << std::endl;
    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols2; j++)
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

// Number System Conversions
void numberSystemConversion()
{
    std::cout << theme->primary << "\n=== Number System Conversion ===" << theme->reset << std::endl;
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
    {
        num = static_cast<long long>(getValidNumber("Enter decimal number: "));
        std::cout << theme->success << "Binary: ";
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
        std::cout << theme->reset << std::endl;
        break;
    }

    case 2:
    {
        num = static_cast<long long>(getValidNumber("Enter decimal number: "));
        std::cout << theme->success << "Octal: " << std::oct << num << theme->reset << std::endl;
        break;
    }

    case 3:
    {
        num = static_cast<long long>(getValidNumber("Enter decimal number: "));
        std::cout << theme->success << "Hexadecimal: " << std::hex << std::uppercase << num << theme->reset << std::endl;
        break;
    }

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
                std::cout << theme->error << "Invalid binary number!" << theme->reset << std::endl;
                return;
            }
            decimal = decimal * 2 + (c - '0');
        }
        std::cout << theme->success << "Decimal: " << decimal << theme->reset << std::endl;
        addToHistory(decimal, "binary->decimal");
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
                std::cout << theme->error << "Invalid octal number!" << theme->reset << std::endl;
                return;
            }
            decimal = decimal * 8 + (c - '0');
        }
        std::cout << theme->success << "Decimal: " << decimal << theme->reset << std::endl;
        addToHistory(decimal, "octal->decimal");
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
                std::cout << theme->error << "Invalid hexadecimal number!" << theme->reset << std::endl;
                return;
            }
            int digit = (c >= 'A') ? (c - 'A' + 10) : (c - '0');
            decimal = decimal * 16 + digit;
        }
        std::cout << theme->success << "Decimal: " << decimal << theme->reset << std::endl;
        addToHistory(decimal, "hex->decimal");
        break;
    }
    }
}

// Unit Conversions
void unitConversions()
{
    std::cout << theme->primary << "\n=== Unit Conversions ===" << theme->reset << std::endl;
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
            std::cout << theme->success << value << "°C = " << result << "°F" << theme->reset << std::endl;
            break;
        case 2:
            result = (value - 32) * 5 / 9;
            std::cout << theme->success << value << "°F = " << result << "°C" << theme->reset << std::endl;
            break;
        case 3:
            result = value + 273.15;
            std::cout << theme->success << value << "°C = " << result << "K" << theme->reset << std::endl;
            break;
        case 4:
            result = value - 273.15;
            std::cout << theme->success << value << "K = " << result << "°C" << theme->reset << std::endl;
            break;
        }
        addToHistory(result, "temp conversion");
        break;
    }

    case 2: // Length
    {
        std::cout << "1. Meters to Feet\n2. Feet to Meters\n3. Meters to Inches\n4. Inches to Meters\n";
        int lenChoice = getValidChoice(1, 4);
        value = getValidNumber("Enter value: ");
        switch (lenChoice)
        {
        case 1:
            result = value * 3.28084;
            std::cout << theme->success << value << " m = " << result << " ft" << theme->reset << std::endl;
            break;
        case 2:
            result = value / 3.28084;
            std::cout << theme->success << value << " ft = " << result << " m" << theme->reset << std::endl;
            break;
        case 3:
            result = value * 39.3701;
            std::cout << theme->success << value << " m = " << result << " in" << theme->reset << std::endl;
            break;
        case 4:
            result = value / 39.3701;
            std::cout << theme->success << value << " in = " << result << " m" << theme->reset << std::endl;
            break;
        }
        addToHistory(result, "length conversion");
        break;
    }

    case 3: // Weight
    {
        std::cout << "1. Kilograms to Pounds\n2. Pounds to Kilograms\n3. Kilograms to Ounces\n4. Ounces to Kilograms\n";
        int weightChoice = getValidChoice(1, 4);
        value = getValidNumber("Enter value: ");
        switch (weightChoice)
        {
        case 1:
            result = value * 2.20462;
            std::cout << theme->success << value << " kg = " << result << " lb" << theme->reset << std::endl;
            break;
        case 2:
            result = value / 2.20462;
            std::cout << theme->success << value << " lb = " << result << " kg" << theme->reset << std::endl;
            break;
        case 3:
            result = value * 35.274;
            std::cout << theme->success << value << " kg = " << result << " oz" << theme->reset << std::endl;
            break;
        case 4:
            result = value / 35.274;
            std::cout << theme->success << value << " oz = " << result << " kg" << theme->reset << std::endl;
            break;
        }
        addToHistory(result, "weight conversion");
        break;
    }

    case 4: // Speed
    {
        std::cout << "1. km/h to mph\n2. mph to km/h\n3. m/s to km/h\n4. km/h to m/s\n";
        int speedChoice = getValidChoice(1, 4);
        value = getValidNumber("Enter value: ");
        switch (speedChoice)
        {
        case 1:
            result = value * 0.621371;
            std::cout << theme->success << value << " km/h = " << result << " mph" << theme->reset << std::endl;
            break;
        case 2:
            result = value / 0.621371;
            std::cout << theme->success << value << " mph = " << result << " km/h" << theme->reset << std::endl;
            break;
        case 3:
            result = value * 3.6;
            std::cout << theme->success << value << " m/s = " << result << " km/h" << theme->reset << std::endl;
            break;
        case 4:
            result = value / 3.6;
            std::cout << theme->success << value << " km/h = " << result << " m/s" << theme->reset << std::endl;
            break;
        }
        addToHistory(result, "speed conversion");
        break;
    }

    case 5: // Area
    {
        std::cout << "1. m² to ft²\n2. ft² to m²\n3. m² to acres\n4. acres to m²\n";
        int areaChoice = getValidChoice(1, 4);
        value = getValidNumber("Enter value: ");
        switch (areaChoice)
        {
        case 1:
            result = value * 10.7639;
            std::cout << theme->success << value << " m² = " << result << " ft²" << theme->reset << std::endl;
            break;
        case 2:
            result = value / 10.7639;
            std::cout << theme->success << value << " ft² = " << result << " m²" << theme->reset << std::endl;
            break;
        case 3:
            result = value / 4046.86;
            std::cout << theme->success << value << " m² = " << result << " acres" << theme->reset << std::endl;
            break;
        case 4:
            result = value * 4046.86;
            std::cout << theme->success << value << " acres = " << result << " m²" << theme->reset << std::endl;
            break;
        }
        addToHistory(result, "area conversion");
        break;
    }

    case 6: // Volume
    {
        std::cout << "1. Liters to Gallons\n2. Gallons to Liters\n3. Liters to Milliliters\n4. Milliliters to Liters\n";
        int volChoice = getValidChoice(1, 4);
        value = getValidNumber("Enter value: ");
        switch (volChoice)
        {
        case 1:
            result = value * 0.264172;
            std::cout << theme->success << value << " L = " << result << " gal" << theme->reset << std::endl;
            break;
        case 2:
            result = value / 0.264172;
            std::cout << theme->success << value << " gal = " << result << " L" << theme->reset << std::endl;
            break;
        case 3:
            result = value * 1000;
            std::cout << theme->success << value << " L = " << result << " mL" << theme->reset << std::endl;
            break;
        case 4:
            result = value / 1000;
            std::cout << theme->success << value << " mL = " << result << " L" << theme->reset << std::endl;
            break;
        }
        addToHistory(result, "volume conversion");
        break;
    }
    }
}

// Memory Menu
void memoryMenu()
{
    std::cout << theme->accent << "\n┌─── Memory Operations ───┐" << theme->reset << std::endl;
    std::cout << "1. Store to Memory (M+)\n";
    std::cout << "2. Recall Memory (MR)\n";
    std::cout << "3. Clear Memory (MC)\n";
    std::cout << "4. Add to Memory\n";

    int choice = getValidChoice(1, 4);

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

    std::cout << theme->secondary << "\n┌─── Trigonometric ───┐" << theme->reset << std::endl;
    std::cout << " 7. sin()               8. cos()               9. tan()\n";
    std::cout << "10. arcsin()           11. arccos()           12. arctan()\n";
    std::cout << "13. sinh()             14. cosh()             15. tanh()\n";

    std::cout << theme->secondary << "\n┌─── Exponential & Log ───┐" << theme->reset << std::endl;
    std::cout << "16. Power (x^y)        17. e^x                18. ln(x)\n";
    std::cout << "19. log10(x)           20. log2(x)\n";

    std::cout << theme->secondary << "\n┌─── Roots & Advanced ───┐" << theme->reset << std::endl;
    std::cout << "21. Square Root        22. Cube Root          23. nth Root\n";
    std::cout << "24. Factorial          25. Ceiling            26. Floor\n";
    std::cout << "27. Round              28. Statistics\n";

    std::cout << theme->secondary << "\n┌─── Conversions ───┐" << theme->reset << std::endl;
    std::cout << "29. Deg ↔ Rad          30. Number Systems     31. Units\n";

    std::cout << theme->secondary << "\n┌─── Advanced Math ───┐" << theme->reset << std::endl;
    std::cout << "32. Permutation        33. Combination        34. GCD & LCM\n";
    std::cout << "35. Quadratic Solver   36. Matrix Add         37. Matrix Multiply\n";

    std::cout << theme->accent << "\n┌─── ADVANCED FEATURES ───┐" << theme->reset << std::endl;
    std::cout << "38. Expression Parser  39. Complex Numbers    40. Memory Ops\n";
    std::cout << "41. View History       42. Save History       43. Use History Value\n";
    std::cout << "44. Change Theme\n";

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
        choice = getValidChoice(0, 44);

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
            result = log10Func();
            break;
        case 20:
            result = log2Func();
            break;
        case 21:
            result = squareRoot();
            break;
        case 22:
            result = cubeRoot();
            break;
        case 23:
            result = nthRoot();
            break;
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
        case 29:
        {
            std::cout << "1. Degrees to Radians\n2. Radians to Degrees\n";
            int convChoice = getValidChoice(1, 2);
            result = (convChoice == 1) ? degreeToRadian() : radianToDegree();
            break;
        }
        case 30:
            numberSystemConversion();
            validOperation = false;
            break;
        case 31:
            unitConversions();
            validOperation = false;
            break;
        case 32:
            result = permutation();
            break;
        case 33:
            result = combination();
            break;
        case 34:
            gcdLcm();
            validOperation = false;
            break;
        case 35:
            quadraticSolver();
            validOperation = false;
            break;
        case 36:
            matrixAddition();
            validOperation = false;
            break;
        case 37:
            matrixMultiplication();
            validOperation = false;
            break;
        case 38:
            expressionCalculator();
            validOperation = false;
            break;
        case 39:
            complexNumberMenu();
            validOperation = false;
            break;
        case 40:
            memoryMenu();
            validOperation = false;
            break;
        case 41:
            displayHistory();
            validOperation = false;
            break;
        case 42:
            saveHistoryToFile();
            validOperation = false;
            break;
        case 43:
            result = getFromHistory();
            break;
        case 44:
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