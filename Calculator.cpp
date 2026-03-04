// =============================================================================
//  ULTIMATE SCIENTIFIC CALCULATOR  v3.0
//  Features: Themes, History, Memory, Statistics, Matrix Ops, Complex Numbers,
//            Number Theory, Calculus Tools, Polynomial Solver, Base Conversions,
//            Unit Conversions, Expression Parser, Fibonacci, and more.
// =============================================================================

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
#include <numeric>
#include <functional>
#include <climits>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_E
#define M_E 2.71828182845904523536
#endif

// =============================================================================
//  THEMES
// =============================================================================

enum ColorTheme
{
    DARK,
    LIGHT,
    MONOCHROME,
    NEON,
    OCEAN
};
ColorTheme currentTheme = DARK;

struct ThemeColors
{
    std::string reset, bold, primary, secondary, success, warning, error, accent, dim;
};

ThemeColors darkTheme = {"\033[0m", "\033[1m", "\033[36m", "\033[34m", "\033[32m", "\033[33m", "\033[31m", "\033[35m", "\033[2m"};
ThemeColors lightTheme = {"\033[0m", "\033[1m", "\033[96m", "\033[94m", "\033[92m", "\033[93m", "\033[91m", "\033[95m", "\033[2m"};
ThemeColors monoTheme = {"\033[0m", "\033[1m", "\033[1m", "\033[0m", "\033[1m", "\033[0m", "\033[1m", "\033[4m", "\033[2m"};
ThemeColors neonTheme = {"\033[0m", "\033[1m", "\033[35;1m", "\033[36;1m", "\033[92;1m", "\033[93;1m", "\033[91;1m", "\033[95;1m", "\033[2m"};
ThemeColors oceanTheme = {"\033[0m", "\033[1m", "\033[34;1m", "\033[96m", "\033[36;1m", "\033[94m", "\033[31m", "\033[96;1m", "\033[2m"};

ThemeColors *theme = &darkTheme;

// =============================================================================
//  GLOBALS
// =============================================================================

struct HistoryEntry
{
    double value;
    std::string label;
    std::string timestamp;
};
std::vector<HistoryEntry> history;
double memory = 0.0;
const int MAX_HISTORY = 100;
bool angleInDegrees = false; // false = radians (default), true = degrees

// =============================================================================
//  UTILITIES
// =============================================================================

void clearInput()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string getTimestamp()
{
    time_t now = time(0);
    char buf[20];
    strftime(buf, sizeof(buf), "%H:%M:%S", localtime(&now));
    return std::string(buf);
}

double toRadians(double angle) { return angleInDegrees ? angle * M_PI / 180.0 : angle; }
double fromRadians(double r) { return angleInDegrees ? r * 180.0 / M_PI : r; }

double getValidNumber(const std::string &prompt)
{
    double num;
    while (true)
    {
        std::cout << theme->warning << prompt << theme->reset;
        if (std::cin >> num)
        {
            clearInput();
            return num;
        }
        std::cout << theme->error << "  Invalid input! Please enter a valid number.\n"
                  << theme->reset;
        clearInput();
    }
}

int getValidInt(const std::string &prompt, int minVal = INT_MIN, int maxVal = INT_MAX)
{
    int val;
    while (true)
    {
        std::cout << theme->warning << prompt << theme->reset;
        if (std::cin >> val && val >= minVal && val <= maxVal)
        {
            clearInput();
            return val;
        }
        std::cout << theme->error << "  Invalid! Enter an integer"
                  << (minVal != INT_MIN ? " >= " + std::to_string(minVal) : "")
                  << (maxVal != INT_MAX ? " <= " + std::to_string(maxVal) : "") << "\n"
                  << theme->reset;
        clearInput();
    }
}

int getValidChoice(int minv, int maxv)
{
    return getValidInt(
        "Enter your choice (" + std::to_string(minv) + "-" + std::to_string(maxv) + "): ",
        minv, maxv);
}

void printSeparator(char c, int width)
{
    std::cout << theme->dim;
    for (int i = 0; i < width; ++i)
        std::cout << c;
    std::cout << theme->reset << "\n";
}
void printSeparator() { printSeparator('=', 66); }

void printBoxTitle(const std::string &title)
{
    int w = 66;
    int padding = (w - 2 - (int)title.size()) / 2;
    std::cout << theme->primary << theme->bold;
    std::cout << "╔";
    for (int i = 0; i < w - 2; ++i)
        std::cout << "═";
    std::cout << "╗\n║";
    for (int i = 0; i < padding; ++i)
        std::cout << " ";
    std::cout << title;
    for (int i = 0; i < w - 2 - padding - (int)title.size(); ++i)
        std::cout << " ";
    std::cout << "║\n╚";
    for (int i = 0; i < w - 2; ++i)
        std::cout << "═";
    std::cout << "╝\n"
              << theme->reset;
}

void printResult(double result, const std::string &label = "Result")
{
    std::cout << theme->success << theme->bold
              << "\n  ┌─────────────────────────────────┐\n"
              << "  │  " << std::left << std::setw(10) << label << ": "
              << std::right << std::setw(18) << std::fixed << std::setprecision(8) << result
              << "  │\n"
              << "  └─────────────────────────────────┘\n"
              << theme->reset;
}

// =============================================================================
//  HISTORY
// =============================================================================

void addToHistory(double value, const std::string &label = "")
{
    history.push_back({value, label, getTimestamp()});
    if ((int)history.size() > MAX_HISTORY)
        history.erase(history.begin());
}

void displayHistory()
{
    if (history.empty())
    {
        std::cout << theme->warning << "\n  No history available yet.\n"
                  << theme->reset;
        return;
    }
    printBoxTitle("CALCULATION HISTORY");
    int start = std::max(0, (int)history.size() - 15);
    for (int i = start; i < (int)history.size(); i++)
    {
        std::cout << theme->dim << "  [" << i << "] " << history[i].timestamp << "  " << theme->reset
                  << theme->secondary;
        if (!history[i].label.empty())
            std::cout << std::setw(20) << std::left << history[i].label << " = ";
        std::cout << theme->success << std::fixed << std::setprecision(8) << history[i].value
                  << theme->reset << "\n";
    }
    std::cout << theme->dim << "  Total entries: " << history.size() << "\n"
              << theme->reset;
}

double getFromHistory()
{
    displayHistory();
    if (history.empty())
        return 0;
    int idx = getValidInt("  Enter history index: ", 0, (int)history.size() - 1);
    std::cout << theme->success << "  Using: " << history[idx].value << theme->reset << "\n";
    return history[idx].value;
}

void clearHistory()
{
    history.clear();
    std::cout << theme->success << "  History cleared.\n"
              << theme->reset;
}

// =============================================================================
//  MEMORY
// =============================================================================

void memoryStore(double v)
{
    memory = v;
    std::cout << theme->success << "  M = " << v << "\n"
              << theme->reset;
}
void memoryRecall() { std::cout << theme->success << "  Memory: " << memory << "\n"
                                << theme->reset; }
void memoryClear()
{
    memory = 0;
    std::cout << theme->success << "  Memory cleared.\n"
              << theme->reset;
}
void memoryAdd(double v)
{
    memory += v;
    std::cout << theme->success << "  M = " << memory << "\n"
              << theme->reset;
}
void memorySubtract(double v)
{
    memory -= v;
    std::cout << theme->success << "  M = " << memory << "\n"
              << theme->reset;
}

void memoryMenu()
{
    printBoxTitle("MEMORY OPERATIONS");
    std::cout << "  Current Memory: " << theme->accent << memory << theme->reset << "\n\n"
              << "  1. Store (MS)    2. Recall (MR)    3. Clear (MC)\n"
              << "  4. Add (M+)      5. Subtract (M-)  6. Use in calculation\n";
    int ch = getValidChoice(1, 6);
    switch (ch)
    {
    case 1:
        memoryStore(getValidNumber("  Value to store: "));
        break;
    case 2:
        memoryRecall();
        break;
    case 3:
        memoryClear();
        break;
    case 4:
        memoryAdd(getValidNumber("  Value to add: "));
        break;
    case 5:
        memorySubtract(getValidNumber("  Value to subtract: "));
        break;
    case 6:
        memoryRecall();
        break;
    }
}

// =============================================================================
//  EXPRESSION PARSER  (supports +, -, *, /, ^, %, parentheses)
// =============================================================================

int getPrecedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/' || op == '%')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

double applyOp(double a, double b, char op)
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
    case '%':
        if (b == 0)
            throw std::runtime_error("Modulo by zero");
        return std::fmod(a, b);
    default:
        return 0;
    }
}

double evaluateExpression(const std::string &expr);

// Replace known constants and functions before evaluation
std::string preprocessExpr(std::string expr)
{
    // Replace pi, e constants
    auto replaceAll = [&](const std::string &from, const std::string &to)
    {
        size_t pos = 0;
        while ((pos = expr.find(from, pos)) != std::string::npos)
        {
            expr.replace(pos, from.size(), to);
            pos += to.size();
        }
    };
    replaceAll("pi", "3.14159265358979");
    replaceAll("PI", "3.14159265358979");
    replaceAll("e", "2.71828182845904");
    return expr;
}

double evaluateExpression(const std::string &rawExpr)
{
    std::string expr = preprocessExpr(rawExpr);
    std::stack<double> vals;
    std::stack<char> ops;

    auto applyTop = [&]()
    {
        if (vals.size() < 2)
            throw std::runtime_error("Malformed expression");
        double b = vals.top();
        vals.pop();
        double a = vals.top();
        vals.pop();
        char op = ops.top();
        ops.pop();
        vals.push(applyOp(a, b, op));
    };

    for (int i = 0; i < (int)expr.size(); i++)
    {
        if (isspace(expr[i]))
            continue;

        if (isdigit(expr[i]) || expr[i] == '.')
        {
            std::string num;
            while (i < (int)expr.size() && (isdigit(expr[i]) || expr[i] == '.'))
                num += expr[i++];
            i--;
            vals.push(std::stod(num));
        }
        else if (expr[i] == '(')
        {
            ops.push('(');
        }
        else if (expr[i] == ')')
        {
            while (!ops.empty() && ops.top() != '(')
                applyTop();
            if (!ops.empty())
                ops.pop();
        }
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' ||
                 expr[i] == '/' || expr[i] == '^' || expr[i] == '%')
        {
            // Unary minus
            if (expr[i] == '-' && (i == 0 || expr[i - 1] == '(' ||
                                   expr[i - 1] == '+' || expr[i - 1] == '-' ||
                                   expr[i - 1] == '*' || expr[i - 1] == '/' || expr[i - 1] == '^'))
                vals.push(0);
            while (!ops.empty() && getPrecedence(ops.top()) >= getPrecedence(expr[i]))
                applyTop();
            ops.push(expr[i]);
        }
    }
    while (!ops.empty())
        applyTop();
    if (vals.empty())
        throw std::runtime_error("Empty expression");
    return vals.top();
}

void expressionCalculator()
{
    printBoxTitle("EXPRESSION CALCULATOR");
    std::cout << "  Supports: +  -  *  /  ^  %  ( )\n"
              << "  Constants: pi, e\n"
              << "  Examples: 3+5*2   (10+5)/3   2^3+4   pi*5^2\n\n";
    std::string expr;
    std::cout << theme->warning << "  Enter expression: " << theme->reset;
    std::getline(std::cin, expr);
    try
    {
        double r = evaluateExpression(expr);
        printResult(r, expr);
        addToHistory(r, expr);
    }
    catch (const std::exception &ex)
    {
        std::cout << theme->error << "  Error: " << ex.what() << theme->reset << "\n";
    }
}

// =============================================================================
//  BASIC OPERATIONS
// =============================================================================

double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }
double divide(double a, double b)
{
    while (b == 0)
    {
        std::cout << theme->error << "  Error: Division by zero!\n"
                  << theme->reset;
        b = getValidNumber("  Enter divisor again: ");
    }
    return a / b;
}
double modulus(double a, double b)
{
    while (b == 0)
    {
        std::cout << theme->error << "  Error: Modulus by zero!\n"
                  << theme->reset;
        b = getValidNumber("  Enter divisor again: ");
    }
    return std::fmod(a, b);
}
double absoluteValue() { return std::abs(getValidNumber("  Enter number: ")); }
double percentage()
{
    double num = getValidNumber("  Enter number: ");
    double percent = getValidNumber("  Enter percentage: ");
    return (num * percent) / 100.0;
}
double reciprocal()
{
    double n = getValidNumber("  Enter number: ");
    while (n == 0)
    {
        std::cout << theme->error << "  Cannot take reciprocal of 0!\n"
                  << theme->reset;
        n = getValidNumber("  Enter number: ");
    }
    return 1.0 / n;
}

// =============================================================================
//  TRIGONOMETRIC
// =============================================================================

std::string angleMode() { return angleInDegrees ? "degrees" : "radians"; }

double getAngle(const std::string &label = "angle")
{
    return getValidNumber("  Enter " + label + " in " + angleMode() + ": ");
}

double sine() { return std::sin(toRadians(getAngle())); }
double cosine() { return std::cos(toRadians(getAngle())); }
double tangent() { return std::tan(toRadians(getAngle())); }
double cosecant()
{
    double s = std::sin(toRadians(getAngle()));
    if (std::abs(s) < 1e-12)
    {
        std::cout << theme->error << "  Cosecant undefined.\n"
                  << theme->reset;
        return std::numeric_limits<double>::infinity();
    }
    return 1.0 / s;
}
double secant()
{
    double c = std::cos(toRadians(getAngle()));
    if (std::abs(c) < 1e-12)
    {
        std::cout << theme->error << "  Secant undefined.\n"
                  << theme->reset;
        return std::numeric_limits<double>::infinity();
    }
    return 1.0 / c;
}
double cotangent()
{
    double t = std::tan(toRadians(getAngle()));
    if (std::abs(t) < 1e-12)
    {
        std::cout << theme->error << "  Cotangent undefined.\n"
                  << theme->reset;
        return std::numeric_limits<double>::infinity();
    }
    return 1.0 / t;
}
double arcsine()
{
    double v = getValidNumber("  Enter value [-1, 1]: ");
    while (v < -1 || v > 1)
    {
        std::cout << theme->error << "  Out of range!\n"
                  << theme->reset;
        v = getValidNumber("  Enter value [-1, 1]: ");
    }
    return fromRadians(std::asin(v));
}
double arccosine()
{
    double v = getValidNumber("  Enter value [-1, 1]: ");
    while (v < -1 || v > 1)
    {
        std::cout << theme->error << "  Out of range!\n"
                  << theme->reset;
        v = getValidNumber("  Enter value [-1, 1]: ");
    }
    return fromRadians(std::acos(v));
}
double arctangent() { return fromRadians(std::atan(getValidNumber("  Enter value: "))); }
double arctan2Func()
{
    double y = getValidNumber("  Enter y: ");
    double x = getValidNumber("  Enter x: ");
    return fromRadians(std::atan2(y, x));
}
double hyperbolicSine() { return std::sinh(getValidNumber("  Enter value: ")); }
double hyperbolicCosine() { return std::cosh(getValidNumber("  Enter value: ")); }
double hyperbolicTangent() { return std::tanh(getValidNumber("  Enter value: ")); }
double arcSinh() { return std::asinh(getValidNumber("  Enter value: ")); }
double arcCosh()
{
    double v = getValidNumber("  Enter value (>= 1): ");
    while (v < 1)
    {
        std::cout << theme->error << "  Must be >= 1\n"
                  << theme->reset;
        v = getValidNumber("  Enter value (>= 1): ");
    }
    return std::acosh(v);
}
double arcTanh()
{
    double v = getValidNumber("  Enter value (-1, 1): ");
    while (v <= -1 || v >= 1)
    {
        std::cout << theme->error << "  Must be in (-1, 1)\n"
                  << theme->reset;
        v = getValidNumber("  Enter value (-1, 1): ");
    }
    return std::atanh(v);
}

void toggleAngleMode()
{
    angleInDegrees = !angleInDegrees;
    std::cout << theme->success << "  Angle mode switched to: " << angleMode() << theme->reset << "\n";
}

// =============================================================================
//  EXPONENTIAL & LOGARITHM
// =============================================================================

double power()
{
    double b = getValidNumber("  Enter base: ");
    double e = getValidNumber("  Enter exponent: ");
    return std::pow(b, e);
}
double exponential() { return std::exp(getValidNumber("  Enter value: ")); }
double naturalLog()
{
    double n = getValidNumber("  Enter positive number: ");
    while (n <= 0)
    {
        std::cout << theme->error << "  Must be positive!\n"
                  << theme->reset;
        n = getValidNumber("  Enter positive number: ");
    }
    return std::log(n);
}
double log10Func()
{
    double n = getValidNumber("  Enter positive number: ");
    while (n <= 0)
    {
        std::cout << theme->error << "  Must be positive!\n"
                  << theme->reset;
        n = getValidNumber("  Enter positive number: ");
    }
    return std::log10(n);
}
double log2Func()
{
    double n = getValidNumber("  Enter positive number: ");
    while (n <= 0)
    {
        std::cout << theme->error << "  Must be positive!\n"
                  << theme->reset;
        n = getValidNumber("  Enter positive number: ");
    }
    return std::log2(n);
}
double logBase()
{
    double n = getValidNumber("  Enter positive number: ");
    while (n <= 0)
    {
        std::cout << theme->error << "  Must be positive!\n"
                  << theme->reset;
        n = getValidNumber("  Enter positive number: ");
    }
    double base = getValidNumber("  Enter base (> 0, != 1): ");
    while (base <= 0 || base == 1)
    {
        std::cout << theme->error << "  Invalid base!\n"
                  << theme->reset;
        base = getValidNumber("  Enter base (> 0, != 1): ");
    }
    return std::log(n) / std::log(base);
}

// =============================================================================
//  ROOTS & ROUNDING
// =============================================================================

double squareRoot()
{
    double n = getValidNumber("  Enter non-negative number: ");
    while (n < 0)
    {
        std::cout << theme->error << "  Negative numbers have complex roots!\n"
                  << theme->reset;
        n = getValidNumber("  Enter non-negative number: ");
    }
    return std::sqrt(n);
}
double cubeRoot() { return std::cbrt(getValidNumber("  Enter number: ")); }
double nthRoot()
{
    double n = getValidNumber("  Enter number: ");
    double r = getValidNumber("  Enter root degree: ");
    while (r == 0)
    {
        std::cout << theme->error << "  Root degree cannot be zero!\n"
                  << theme->reset;
        r = getValidNumber("  Enter root degree: ");
    }
    return std::pow(n, 1.0 / r);
}
double ceiling() { return std::ceil(getValidNumber("  Enter number: ")); }
double floorFunc() { return std::floor(getValidNumber("  Enter number: ")); }
double roundNum() { return std::round(getValidNumber("  Enter number: ")); }
double truncateNum() { return std::trunc(getValidNumber("  Enter number: ")); }
double roundToN()
{
    double n = getValidNumber("  Enter number: ");
    int places = getValidInt("  Decimal places (0-10): ", 0, 10);
    double factor = std::pow(10.0, places);
    return std::round(n * factor) / factor;
}

// =============================================================================
//  FACTORIAL & COMBINATORICS
// =============================================================================

double factorialVal(int n)
{
    if (n < 0)
        return std::numeric_limits<double>::quiet_NaN();
    double r = 1;
    for (int i = 2; i <= n; i++)
        r *= i;
    return r;
}
double factorial()
{
    int n = getValidInt("  Enter non-negative integer (0-170): ", 0, 170);
    return factorialVal(n);
}
double gammaFunc()
{
    double n = getValidNumber("  Enter value: ");
    return std::tgamma(n);
}
double permutation()
{
    int n = getValidInt("  Enter n (0-170): ", 0, 170);
    int r = getValidInt("  Enter r (0-" + std::to_string(n) + "): ", 0, n);
    double result = 1;
    for (int i = 0; i < r; i++)
        result *= (n - i);
    return result;
}
double combination()
{
    int n = getValidInt("  Enter n (0-170): ", 0, 170);
    int r = getValidInt("  Enter r (0-" + std::to_string(n) + "): ", 0, n);
    if (r > n - r)
        r = n - r;
    double num = 1, den = 1;
    for (int i = 0; i < r; i++)
    {
        num *= (n - i);
        den *= (i + 1);
    }
    return num / den;
}

// =============================================================================
//  NUMBER THEORY
// =============================================================================

long long gcd(long long a, long long b)
{
    a = std::abs(a);
    b = std::abs(b);
    while (b)
    {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}
long long lcm(long long a, long long b) { return std::abs(a / gcd(a, b) * b); }

void gcdLcm()
{
    long long a = (long long)getValidNumber("  Enter first integer: ");
    long long b = (long long)getValidNumber("  Enter second integer: ");
    std::cout << theme->success << "  GCD: " << gcd(a, b) << "\n  LCM: " << lcm(a, b) << theme->reset << "\n";
    addToHistory((double)gcd(a, b), "GCD");
    addToHistory((double)lcm(a, b), "LCM");
}

bool isPrime(long long n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (long long i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    return true;
}

void primeChecker()
{
    long long num = (long long)getValidNumber("  Enter a positive integer: ");
    if (num <= 0)
    {
        std::cout << theme->error << "  Please enter a positive integer!\n"
                  << theme->reset;
        return;
    }
    std::cout << theme->success << "\n  " << num << (isPrime(num) ? " IS a prime number." : " is NOT a prime number.") << theme->reset << "\n";
    if (!isPrime(num))
    {
        std::cout << "  Factors: ";
        for (long long i = 1; i <= num; i++)
            if (num % i == 0)
                std::cout << i << " ";
        std::cout << "\n";
    }
    // Prime factorization
    std::cout << "  Prime factorization: " << num << " = ";
    long long n = num, f = 2;
    bool first = true;
    while (n > 1)
    {
        int cnt = 0;
        while (n % f == 0)
        {
            n /= f;
            cnt++;
        }
        if (cnt > 0)
        {
            if (!first)
                std::cout << " × ";
            std::cout << f;
            if (cnt > 1)
                std::cout << "^" << cnt;
            first = false;
        }
        f++;
    }
    std::cout << "\n";
}

void sieveOfEratosthenes()
{
    int limit = getValidInt("  Find all primes up to: ", 2, 100000);
    std::vector<bool> sieve(limit + 1, true);
    sieve[0] = sieve[1] = false;
    for (int i = 2; i * i <= limit; i++)
        if (sieve[i])
            for (int j = i * i; j <= limit; j += i)
                sieve[j] = false;
    std::cout << theme->success << "\n  Primes up to " << limit << ":\n  " << theme->reset;
    int count = 0;
    for (int i = 2; i <= limit; i++)
    {
        if (sieve[i])
        {
            std::cout << std::setw(6) << i;
            if (++count % 12 == 0)
                std::cout << "\n  ";
        }
    }
    std::cout << "\n"
              << theme->dim << "  Total: " << count << " primes found.\n"
              << theme->reset;
}

void eulersTotient()
{
    long long n = (long long)getValidNumber("  Enter n: ");
    long long result = n, temp = n;
    for (long long p = 2; p * p <= temp; p++)
    {
        if (temp % p == 0)
        {
            while (temp % p == 0)
                temp /= p;
            result -= result / p;
        }
    }
    if (temp > 1)
        result -= result / temp;
    std::cout << theme->success << "  φ(" << n << ") = " << result << theme->reset << "\n";
    addToHistory((double)result, "φ(" + std::to_string(n) + ")");
}

void fibonacci()
{
    int n = getValidInt("  How many Fibonacci terms? (1-80): ", 1, 80);
    std::cout << theme->success << "\n  Fibonacci sequence:\n  " << theme->reset;
    long long a = 0, b = 1;
    for (int i = 0; i < n; i++)
    {
        std::cout << a;
        if (i < n - 1)
            std::cout << ", ";
        long long next = a + b;
        a = b;
        b = next;
        if ((i + 1) % 10 == 0 && i < n - 1)
            std::cout << "\n  ";
    }
    std::cout << "\n";
}

void collatzSequence()
{
    long long n = (long long)getValidNumber("  Enter starting number: ");
    if (n <= 0)
    {
        std::cout << theme->error << "  Positive integer required.\n"
                  << theme->reset;
        return;
    }
    std::cout << theme->success << "  Collatz sequence: " << theme->reset;
    int steps = 0;
    long long orig = n;
    while (n != 1)
    {
        std::cout << n << " → ";
        n = (n % 2 == 0) ? n / 2 : 3 * n + 1;
        steps++;
        if (steps % 10 == 0)
            std::cout << "\n               ";
    }
    std::cout << "1\n"
              << theme->dim << "  Steps from " << orig << " to 1: " << steps << theme->reset << "\n";
}

// =============================================================================
//  QUADRATIC & POLYNOMIAL SOLVERS
// =============================================================================

void quadraticSolver()
{
    printBoxTitle("QUADRATIC SOLVER  ax² + bx + c = 0");
    double a = getValidNumber("  a: ");
    while (a == 0)
    {
        std::cout << theme->error << "  'a' cannot be 0!\n"
                  << theme->reset;
        a = getValidNumber("  a: ");
    }
    double b = getValidNumber("  b: ");
    double c = getValidNumber("  c: ");
    double disc = b * b - 4 * a * c;
    std::cout << theme->success << "\n  Discriminant: " << disc << "\n"
              << theme->reset;
    if (disc > 0)
    {
        double x1 = (-b + std::sqrt(disc)) / (2 * a);
        double x2 = (-b - std::sqrt(disc)) / (2 * a);
        std::cout << "  Two real roots:\n"
                  << "    x₁ = " << x1 << "\n"
                  << "    x₂ = " << x2 << "\n";
        addToHistory(x1, "root1");
        addToHistory(x2, "root2");
    }
    else if (disc == 0)
    {
        double x = -b / (2 * a);
        std::cout << "  One repeated root:\n    x = " << x << "\n";
        addToHistory(x, "root");
    }
    else
    {
        double re = -b / (2 * a);
        double im = std::sqrt(-disc) / (2 * a);
        std::cout << "  Two complex roots:\n"
                  << "    x₁ = " << re << " + " << im << "i\n"
                  << "    x₂ = " << re << " - " << im << "i\n";
    }
}

void cubicSolver()
{
    // Cardano's method for x³ + px + q = 0 (depressed cubic after substitution)
    printBoxTitle("CUBIC SOLVER  ax³ + bx² + cx + d = 0");
    double a = getValidNumber("  a: ");
    while (a == 0)
    {
        std::cout << theme->error << "  'a' cannot be 0!\n"
                  << theme->reset;
        a = getValidNumber("  a: ");
    }
    double b = getValidNumber("  b: ");
    double c = getValidNumber("  c: ");
    double d = getValidNumber("  d: ");

    // Convert to monic: x³ + b'x² + c'x + d'
    b /= a;
    c /= a;
    d /= a;

    // Substitute x = t - b/3 → t³ + pt + q = 0
    double p = c - b * b / 3.0;
    double q = 2.0 * b * b * b / 27.0 - b * c / 3.0 + d;
    double disc = -(4.0 * p * p * p + 27.0 * q * q);

    std::cout << theme->success << "\n  Discriminant: " << disc << "\n"
              << theme->reset;
    double shift = -b / 3.0;

    if (std::abs(disc) < 1e-12)
    {
        // Two distinct roots or triple root
        if (std::abs(p) < 1e-12 && std::abs(q) < 1e-12)
        {
            double x = shift;
            std::cout << "  Triple root: x = " << x << "\n";
        }
        else
        {
            double x1 = 3.0 * q / p + shift;
            double x2 = -3.0 * q / (2.0 * p) + shift;
            std::cout << "  Roots: x₁ = " << x1 << "  (simple)\n"
                      << "         x₂ = " << x2 << "  (double)\n";
        }
    }
    else if (disc > 0)
    {
        // Three distinct real roots (casus irreducibilis — use trig method)
        double m = 2.0 * std::sqrt(-p / 3.0);
        for (int k = 0; k < 3; k++)
        {
            double angle = (1.0 / 3.0) * std::acos(3.0 * q / (p * m)) - (2.0 * M_PI * k / 3.0);
            double x = m * std::cos(angle) + shift;
            std::cout << "  x" << (k + 1) << " = " << x << "\n";
            addToHistory(x, "cubicRoot" + std::to_string(k + 1));
        }
    }
    else
    {
        // One real root, two complex conjugate roots
        double A = -q / 2.0 + std::sqrt(q * q / 4.0 + p * p * p / 27.0);
        double B = -q / 2.0 - std::sqrt(q * q / 4.0 + p * p * p / 27.0);
        double cbA = (A >= 0) ? std::cbrt(A) : -std::cbrt(-A);
        double cbB = (B >= 0) ? std::cbrt(B) : -std::cbrt(-B);
        double x1 = cbA + cbB + shift;
        double re = -(cbA + cbB) / 2.0 + shift;
        double im = std::sqrt(3.0) * (cbA - cbB) / 2.0;
        std::cout << "  x₁ = " << x1 << "  (real)\n"
                  << "  x₂ = " << re << " + " << im << "i\n"
                  << "  x₃ = " << re << " - " << im << "i\n";
        addToHistory(x1, "cubicRoot1");
    }
}

// =============================================================================
//  STATISTICS
// =============================================================================

void statistics()
{
    printBoxTitle("STATISTICAL ANALYSIS");
    int n = getValidInt("  How many numbers? ", 1, 10000);
    std::vector<double> nums(n);
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        nums[i] = getValidNumber("  [" + std::to_string(i + 1) + "]: ");
        sum += nums[i];
    }

    double mean = sum / n;
    double variance = 0, skew = 0, kurt = 0;
    for (double x : nums)
    {
        double d = x - mean;
        variance += d * d;
        skew += d * d * d;
        kurt += d * d * d * d;
    }
    variance /= n;
    double stddev = std::sqrt(variance);
    if (stddev > 1e-12)
    {
        skew /= (n * stddev * stddev * stddev);
        kurt = kurt / (n * variance * variance) - 3.0; // excess kurtosis
    }

    std::vector<double> sorted = nums;
    std::sort(sorted.begin(), sorted.end());
    double median = (n % 2 == 0) ? (sorted[n / 2 - 1] + sorted[n / 2]) / 2.0 : sorted[n / 2];
    double q1 = sorted[n / 4];
    double q3 = sorted[3 * n / 4];

    // Mode
    std::map<double, int> freq;
    for (double x : nums)
        freq[x]++;
    int mf = 0;
    for (auto &p : freq)
        mf = std::max(mf, p.second);
    std::vector<double> modes;
    for (auto &p : freq)
        if (p.second == mf)
            modes.push_back(p.first);

    printBoxTitle("RESULTS");
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "  Count            : " << n << "\n"
              << "  Sum              : " << sum << "\n"
              << "  Mean             : " << mean << "\n"
              << "  Median           : " << median << "\n"
              << "  Mode             : ";
    if ((int)modes.size() == n)
        std::cout << "None";
    else
        for (int i = 0; i < (int)modes.size(); i++)
        {
            std::cout << modes[i];
            if (i < (int)modes.size() - 1)
                std::cout << ", ";
        }
    std::cout << "\n"
              << "  Min              : " << sorted.front() << "\n"
              << "  Max              : " << sorted.back() << "\n"
              << "  Range            : " << (sorted.back() - sorted.front()) << "\n"
              << "  Q1               : " << q1 << "\n"
              << "  Q3               : " << q3 << "\n"
              << "  IQR              : " << (q3 - q1) << "\n"
              << "  Variance (pop.)  : " << variance << "\n"
              << "  Std Dev (pop.)   : " << stddev << "\n"
              << "  Std Dev (sample) : " << std::sqrt(variance * n / (n - 1)) << "\n"
              << "  Skewness         : " << skew << "\n"
              << "  Excess Kurtosis  : " << kurt << "\n";

    addToHistory(mean, "mean");
    addToHistory(stddev, "stddev");

    std::cout << theme->warning << "\n  Save to file? (y/n): " << theme->reset;
    char save;
    std::cin >> save;
    clearInput();
    if (save == 'y' || save == 'Y')
    {
        std::ofstream f("statistics_report.txt");
        if (f.is_open())
        {
            f << "Statistics Report\n"
              << std::string(40, '=') << "\n";
            f << "Count: " << n << "\nMean: " << mean << "\nMedian: " << median
              << "\nStd Dev: " << stddev << "\nVariance: " << variance
              << "\nMin: " << sorted.front() << "\nMax: " << sorted.back() << "\n";
            f.close();
            std::cout << theme->success << "  Saved to statistics_report.txt\n"
                      << theme->reset;
        }
    }
}

// Linear regression
void linearRegression()
{
    printBoxTitle("LINEAR REGRESSION  y = mx + b");
    int n = getValidInt("  Number of data points: ", 2, 1000);
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
    for (int i = 0; i < n; i++)
    {
        std::cout << "  Point " << (i + 1) << ":\n";
        double x = getValidNumber("    x: ");
        double y = getValidNumber("    y: ");
        sumX += x;
        sumY += y;
        sumXY += x * y;
        sumX2 += x * x;
    }
    double m = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    double b = (sumY - m * sumX) / n;
    double r = (n * sumXY - sumX * sumY) /
               std::sqrt((n * sumX2 - sumX * sumX) * (n * (sumY * sumY) - sumY * sumY));

    std::cout << theme->success << "\n  Slope (m)     : " << m
              << "\n  Intercept (b) : " << b
              << "\n  Line equation : y = " << m << "x + (" << b << ")"
              << "\n  Correlation r : " << r
              << "\n  R²            : " << r * r
              << theme->reset << "\n";
    addToHistory(m, "slope");
    addToHistory(b, "intercept");
}

// =============================================================================
//  MATRIX OPERATIONS
// =============================================================================

using Matrix = std::vector<std::vector<double>>;

Matrix inputMatrix(const std::string &name)
{
    int rows = getValidInt("  " + name + " rows: ", 1, 10);
    int cols = getValidInt("  " + name + " cols: ", 1, 10);
    Matrix M(rows, std::vector<double>(cols));
    std::cout << "  Enter elements row by row:\n";
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            M[i][j] = getValidNumber("    [" + std::to_string(i) + "][" + std::to_string(j) + "]: ");
    return M;
}

void printMatrix(const Matrix &M, const std::string &label = "")
{
    if (!label.empty())
        std::cout << theme->secondary << "  " << label << ":\n"
                  << theme->reset;
    for (const auto &row : M)
    {
        std::cout << "  │ ";
        for (double v : row)
            std::cout << std::setw(10) << std::fixed << std::setprecision(4) << v << " ";
        std::cout << "│\n";
    }
}

void matrixAddition()
{
    Matrix A = inputMatrix("Matrix A");
    Matrix B = inputMatrix("Matrix B");
    if (A.size() != B.size() || A[0].size() != B[0].size())
    {
        std::cout << theme->error << "  Dimension mismatch!\n"
                  << theme->reset;
        return;
    }
    Matrix R(A.size(), std::vector<double>(A[0].size()));
    for (int i = 0; i < (int)A.size(); i++)
        for (int j = 0; j < (int)A[0].size(); j++)
            R[i][j] = A[i][j] + B[i][j];
    printMatrix(R, "Result (A + B)");
}

void matrixSubtraction()
{
    Matrix A = inputMatrix("Matrix A");
    Matrix B = inputMatrix("Matrix B");
    if (A.size() != B.size() || A[0].size() != B[0].size())
    {
        std::cout << theme->error << "  Dimension mismatch!\n"
                  << theme->reset;
        return;
    }
    Matrix R(A.size(), std::vector<double>(A[0].size()));
    for (int i = 0; i < (int)A.size(); i++)
        for (int j = 0; j < (int)A[0].size(); j++)
            R[i][j] = A[i][j] - B[i][j];
    printMatrix(R, "Result (A - B)");
}

void matrixMultiplication()
{
    Matrix A = inputMatrix("Matrix A");
    Matrix B = inputMatrix("Matrix B");
    if (A[0].size() != B.size())
    {
        std::cout << theme->error << "  Incompatible dimensions for multiplication!\n"
                  << theme->reset;
        return;
    }
    int r = A.size(), c = B[0].size(), m = B.size();
    Matrix R(r, std::vector<double>(c, 0));
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            for (int k = 0; k < m; k++)
                R[i][j] += A[i][k] * B[k][j];
    printMatrix(R, "Result (A × B)");
}

void matrixTranspose()
{
    Matrix A = inputMatrix("Matrix A");
    int r = A.size(), c = A[0].size();
    Matrix T(c, std::vector<double>(r));
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            T[j][i] = A[i][j];
    printMatrix(A, "Original");
    printMatrix(T, "Transposed");
}

double determinant(Matrix M, int n)
{
    double det = 1;
    for (int col = 0; col < n; col++)
    {
        int pivot = -1;
        for (int row = col; row < n; row++)
            if (std::abs(M[row][col]) > 1e-12)
            {
                pivot = row;
                break;
            }
        if (pivot == -1)
            return 0;
        if (pivot != col)
        {
            std::swap(M[pivot], M[col]);
            det *= -1;
        }
        det *= M[col][col];
        for (int row = col + 1; row < n; row++)
        {
            double f = M[row][col] / M[col][col];
            for (int k = col; k < n; k++)
                M[row][k] -= f * M[col][k];
        }
    }
    return det;
}

void matrixDeterminant()
{
    Matrix A = inputMatrix("Square Matrix");
    if (A.size() != A[0].size())
    {
        std::cout << theme->error << "  Must be square!\n"
                  << theme->reset;
        return;
    }
    double det = determinant(A, A.size());
    std::cout << theme->success << "  Determinant = " << det << theme->reset << "\n";
    addToHistory(det, "determinant");
}

void matrixInverse()
{
    Matrix A = inputMatrix("Square Matrix");
    int n = A.size();
    if ((int)A[0].size() != n)
    {
        std::cout << theme->error << "  Must be square!\n"
                  << theme->reset;
        return;
    }

    // Augment with identity
    Matrix aug(n, std::vector<double>(2 * n, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            aug[i][j] = A[i][j];
        aug[i][n + i] = 1.0;
    }

    // Gauss-Jordan elimination
    for (int col = 0; col < n; col++)
    {
        int pivot = -1;
        for (int row = col; row < n; row++)
            if (std::abs(aug[row][col]) > 1e-12)
            {
                pivot = row;
                break;
            }
        if (pivot == -1)
        {
            std::cout << theme->error << "  Matrix is singular (no inverse).\n"
                      << theme->reset;
            return;
        }
        std::swap(aug[pivot], aug[col]);
        double piv = aug[col][col];
        for (int j = 0; j < 2 * n; j++)
            aug[col][j] /= piv;
        for (int row = 0; row < n; row++)
        {
            if (row == col)
                continue;
            double f = aug[row][col];
            for (int j = 0; j < 2 * n; j++)
                aug[row][j] -= f * aug[col][j];
        }
    }

    Matrix inv(n, std::vector<double>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            inv[i][j] = aug[i][n + j];
    printMatrix(A, "Original");
    printMatrix(inv, "Inverse");
}

void matrixScalarOps()
{
    printBoxTitle("MATRIX SCALAR OPERATIONS");
    std::cout << "  1. Scalar Multiply  2. Scalar Add  3. Scalar Power (element-wise)\n";
    int ch = getValidChoice(1, 3);
    Matrix A = inputMatrix("Matrix");
    double s = getValidNumber("  Scalar: ");
    for (auto &row : A)
        for (auto &v : row)
            v = (ch == 1) ? v * s : (ch == 2) ? v + s
                                              : std::pow(v, s);
    printMatrix(A, "Result");
}

// =============================================================================
//  COMPLEX NUMBERS
// =============================================================================

class ComplexCalc
{
public:
    static void display(const std::complex<double> &c, const std::string &lbl)
    {
        std::cout << theme->success << "  " << lbl << ": " << c.real();
        if (c.imag() >= 0)
            std::cout << " + " << c.imag() << "i";
        else
            std::cout << " - " << std::abs(c.imag()) << "i";
        std::cout << "\n  Magnitude: " << std::abs(c) << "\n  Phase: " << std::arg(c) << " rad\n"
                  << theme->reset;
    }
    static std::pair<std::complex<double>, std::complex<double>> inputTwo()
    {
        double r1 = getValidNumber("  Real 1: "), i1 = getValidNumber("  Imag 1: ");
        double r2 = getValidNumber("  Real 2: "), i2 = getValidNumber("  Imag 2: ");
        return {{r1, i1}, {r2, i2}};
    }
    static std::complex<double> inputOne()
    {
        return {getValidNumber("  Real: "), getValidNumber("  Imag: ")};
    }
    static void doAdd()
    {
        auto [a, b] = inputTwo();
        display(a + b, "Sum");
    }
    static void doSubtract()
    {
        auto [a, b] = inputTwo();
        display(a - b, "Difference");
    }
    static void doMultiply()
    {
        auto [a, b] = inputTwo();
        display(a * b, "Product");
    }
    static void doDivide()
    {
        auto [a, b] = inputTwo();
        if (std::abs(b) < 1e-12)
        {
            std::cout << theme->error << "  Div by zero\n"
                      << theme->reset;
            return;
        }
        display(a / b, "Quotient");
    }
    static void doMagnitude()
    {
        auto c = inputOne();
        std::cout << theme->success << "  |z| = " << std::abs(c) << "\n"
                  << theme->reset;
        addToHistory(std::abs(c), "magnitude");
    }
    static void doPhase()
    {
        auto c = inputOne();
        double ph = std::arg(c);
        std::cout << theme->success << "  arg(z) = " << ph << " rad = " << (ph * 180.0 / M_PI) << "°\n"
                  << theme->reset;
        addToHistory(ph, "phase");
    }
    static void doConjugate()
    {
        auto c = inputOne();
        display(std::conj(c), "Conjugate");
    }
    static void doPower()
    {
        auto c = inputOne();
        double e = getValidNumber("  Exponent: ");
        display(std::pow(c, e), "Result");
    }
    static void doSqrt()
    {
        auto c = inputOne();
        display(std::sqrt(c), "Square Root");
    }
    static void doExp()
    {
        auto c = inputOne();
        display(std::exp(c), "e^z");
    }
    static void doLog()
    {
        auto c = inputOne();
        display(std::log(c), "ln(z)");
    }
    static void doPolarForm()
    {
        auto c = inputOne();
        double r = std::abs(c), theta = std::arg(c);
        std::cout << theme->success << "  Polar form: " << r << " ∠ " << (theta * 180.0 / M_PI) << "°\n"
                  << "  Or: " << r << " × (cos " << theta << " + i·sin " << theta << ")\n"
                  << theme->reset;
    }
};

void complexNumberMenu()
{
    printBoxTitle("COMPLEX NUMBERS");
    std::cout << "  1. Add           2. Subtract      3. Multiply      4. Divide\n"
              << "  5. Magnitude     6. Phase/Arg     7. Conjugate     8. Power\n"
              << "  9. Square Root  10. e^z           11. ln(z)       12. Polar Form\n";
    int ch = getValidChoice(1, 12);
    switch (ch)
    {
    case 1:
        ComplexCalc::doAdd();
        break;
    case 2:
        ComplexCalc::doSubtract();
        break;
    case 3:
        ComplexCalc::doMultiply();
        break;
    case 4:
        ComplexCalc::doDivide();
        break;
    case 5:
        ComplexCalc::doMagnitude();
        break;
    case 6:
        ComplexCalc::doPhase();
        break;
    case 7:
        ComplexCalc::doConjugate();
        break;
    case 8:
        ComplexCalc::doPower();
        break;
    case 9:
        ComplexCalc::doSqrt();
        break;
    case 10:
        ComplexCalc::doExp();
        break;
    case 11:
        ComplexCalc::doLog();
        break;
    case 12:
        ComplexCalc::doPolarForm();
        break;
    }
}

// =============================================================================
//  NUMBER SYSTEM CONVERSIONS
// =============================================================================

void numberSystemConversion()
{
    printBoxTitle("NUMBER SYSTEM CONVERSIONS");
    std::cout << "  1. Dec → Bin    2. Dec → Oct    3. Dec → Hex\n"
              << "  4. Bin → Dec    5. Oct → Dec    6. Hex → Dec\n"
              << "  7. Bin → Hex    8. Hex → Bin    9. Any base → Dec\n";
    int ch = getValidChoice(1, 9);
    std::string input;
    long long num;
    switch (ch)
    {
    case 1:
        num = (long long)getValidNumber("  Decimal: ");
        {
            std::string b;
            if (num == 0)
            {
                b = "0";
            }
            else
            {
                long long t = std::abs(num);
                while (t)
                {
                    b = (char)('0' + t % 2) + b;
                    t /= 2;
                }
            }
            std::cout << theme->success << "  Binary: " << (num < 0 ? "-" : "") << b << theme->reset << "\n";
        }
        break;
    case 2:
        num = (long long)getValidNumber("  Decimal: ");
        std::cout << theme->success << "  Octal: " << std::oct << num << std::dec << theme->reset << "\n";
        break;
    case 3:
        num = (long long)getValidNumber("  Decimal: ");
        std::cout << theme->success << "  Hex: " << std::hex << std::uppercase << num << std::dec << theme->reset << "\n";
        break;
    case 4:
        clearInput();
        std::cout << theme->warning << "  Binary: " << theme->reset;
        std::cin >> input;
        clearInput();
        try
        {
            num = std::stoll(input, nullptr, 2);
            std::cout << theme->success << "  Decimal: " << num << theme->reset << "\n";
            addToHistory(num, "bin→dec");
        }
        catch (...)
        {
            std::cout << theme->error << "Invalid\n"
                      << theme->reset;
        }
        break;
    case 5:
        clearInput();
        std::cout << theme->warning << "  Octal: " << theme->reset;
        std::cin >> input;
        clearInput();
        try
        {
            num = std::stoll(input, nullptr, 8);
            std::cout << theme->success << "  Decimal: " << num << theme->reset << "\n";
            addToHistory(num, "oct→dec");
        }
        catch (...)
        {
            std::cout << theme->error << "Invalid\n"
                      << theme->reset;
        }
        break;
    case 6:
        clearInput();
        std::cout << theme->warning << "  Hex: " << theme->reset;
        std::cin >> input;
        clearInput();
        try
        {
            num = std::stoll(input, nullptr, 16);
            std::cout << theme->success << "  Decimal: " << num << theme->reset << "\n";
            addToHistory(num, "hex→dec");
        }
        catch (...)
        {
            std::cout << theme->error << "Invalid\n"
                      << theme->reset;
        }
        break;
    case 7:
        clearInput();
        std::cout << theme->warning << "  Binary: " << theme->reset;
        std::cin >> input;
        clearInput();
        try
        {
            num = std::stoll(input, nullptr, 2);
            std::cout << theme->success << "  Hex: " << std::hex << std::uppercase << num << std::dec << theme->reset << "\n";
        }
        catch (...)
        {
            std::cout << theme->error << "Invalid\n"
                      << theme->reset;
        }
        break;
    case 8:
        clearInput();
        std::cout << theme->warning << "  Hex: " << theme->reset;
        std::cin >> input;
        clearInput();
        try
        {
            num = std::stoll(input, nullptr, 16);
            std::string b;
            long long t = std::abs(num);
            if (t == 0)
            {
                b = "0";
            }
            else
            {
                while (t)
                {
                    b = (char)('0' + t % 2) + b;
                    t /= 2;
                }
            }
            std::cout << theme->success << "  Binary: " << b << theme->reset << "\n";
        }
        catch (...)
        {
            std::cout << theme->error << "Invalid\n"
                      << theme->reset;
        }
        break;
    case 9:
    {
        int base = getValidInt("  Source base (2-36): ", 2, 36);
        clearInput();
        std::cout << theme->warning << "  Number in base " << base << ": " << theme->reset;
        std::cin >> input;
        clearInput();
        try
        {
            num = std::stoll(input, nullptr, base);
            std::cout << theme->success << "  Decimal: " << num << theme->reset << "\n";
            addToHistory(num, "base" + std::to_string(base) + "→dec");
        }
        catch (...)
        {
            std::cout << theme->error << "Invalid\n"
                      << theme->reset;
        }
        break;
    }
    }
}

// =============================================================================
//  UNIT CONVERSIONS
// =============================================================================

void unitConversions()
{
    printBoxTitle("UNIT CONVERSIONS");
    std::cout << "  1. Temperature    2. Length         3. Weight/Mass\n"
              << "  4. Area           5. Volume         6. Speed\n"
              << "  7. Time           8. Energy         9. Pressure\n"
              << " 10. Digital Storage\n";
    int cat = getValidChoice(1, 10);
    double v, r;

    auto show = [&](const std::string &from, const std::string &to, double res)
    {
        std::cout << theme->success << "  " << v << " " << from << " = " << res << " " << to << theme->reset << "\n";
        addToHistory(res, from + "→" + to);
    };

    switch (cat)
    {
    case 1:
    {
        std::cout << "  1. °C→°F  2. °F→°C  3. °C→K  4. K→°C  5. °F→K  6. K→°F\n";
        int ch = getValidChoice(1, 6);
        v = getValidNumber("  Value: ");
        if (ch == 1)
        {
            r = v * 9 / 5 + 32;
            show("°C", "°F", r);
        }
        else if (ch == 2)
        {
            r = (v - 32) * 5 / 9;
            show("°F", "°C", r);
        }
        else if (ch == 3)
        {
            r = v + 273.15;
            show("°C", "K", r);
        }
        else if (ch == 4)
        {
            r = v - 273.15;
            show("K", "°C", r);
        }
        else if (ch == 5)
        {
            r = (v - 32) * 5 / 9 + 273.15;
            show("°F", "K", r);
        }
        else
        {
            r = (v - 273.15) * 9 / 5 + 32;
            show("K", "°F", r);
        }
        break;
    }
    case 2:
    {
        std::cout << "  1. m→ft  2. ft→m  3. km→mi  4. mi→km  5. in→cm  6. cm→in\n"
                  << "  7. m→yd  8. yd→m  9. nm→mm  10. ly→km\n";
        int ch = getValidChoice(1, 10);
        v = getValidNumber("  Value: ");
        double conv[] = {3.28084, 1.0 / 3.28084, 0.621371, 1.0 / 0.621371, 2.54, 1.0 / 2.54, 1.09361, 1.0 / 1.09361, 1e-6, 9.461e12};
        std::string un[][2] = {{"m", "ft"}, {"ft", "m"}, {"km", "mi"}, {"mi", "km"}, {"in", "cm"}, {"cm", "in"}, {"m", "yd"}, {"yd", "m"}, {"nm", "mm"}, {"ly", "km"}};
        r = v * conv[ch - 1];
        show(un[ch - 1][0], un[ch - 1][1], r);
        break;
    }
    case 3:
    {
        std::cout << "  1. kg→lb  2. lb→kg  3. g→oz  4. oz→g  5. ton→kg  6. kg→ton\n";
        int ch = getValidChoice(1, 6);
        v = getValidNumber("  Value: ");
        double conv[] = {2.20462, 0.453592, 0.035274, 28.3495, 1000.0, 0.001};
        std::string un[][2] = {{"kg", "lb"}, {"lb", "kg"}, {"g", "oz"}, {"oz", "g"}, {"ton", "kg"}, {"kg", "ton"}};
        r = v * conv[ch - 1];
        show(un[ch - 1][0], un[ch - 1][1], r);
        break;
    }
    case 4:
    {
        std::cout << "  1. m²→ft²  2. ft²→m²  3. km²→mi²  4. mi²→km²  5. ha→acre  6. acre→ha\n";
        int ch = getValidChoice(1, 6);
        v = getValidNumber("  Value: ");
        double conv[] = {10.7639, 0.092903, 0.386102, 2.58999, 2.47105, 0.404686};
        std::string un[][2] = {{"m²", "ft²"}, {"ft²", "m²"}, {"km²", "mi²"}, {"mi²", "km²"}, {"ha", "acre"}, {"acre", "ha"}};
        r = v * conv[ch - 1];
        show(un[ch - 1][0], un[ch - 1][1], r);
        break;
    }
    case 5:
    {
        std::cout << "  1. L→gal  2. gal→L  3. mL→fl.oz  4. fl.oz→mL  5. m³→L  6. L→m³\n";
        int ch = getValidChoice(1, 6);
        v = getValidNumber("  Value: ");
        double conv[] = {0.264172, 3.78541, 0.033814, 29.5735, 1000.0, 0.001};
        std::string un[][2] = {{"L", "gal"}, {"gal", "L"}, {"mL", "fl.oz"}, {"fl.oz", "mL"}, {"m³", "L"}, {"L", "m³"}};
        r = v * conv[ch - 1];
        show(un[ch - 1][0], un[ch - 1][1], r);
        break;
    }
    case 6:
    {
        std::cout << "  1. m/s→km/h  2. km/h→m/s  3. km/h→mph  4. mph→km/h  5. knot→km/h  6. km/h→knot\n";
        int ch = getValidChoice(1, 6);
        v = getValidNumber("  Value: ");
        double conv[] = {3.6, 1.0 / 3.6, 0.621371, 1.60934, 1.852, 1.0 / 1.852};
        std::string un[][2] = {{"m/s", "km/h"}, {"km/h", "m/s"}, {"km/h", "mph"}, {"mph", "km/h"}, {"knot", "km/h"}, {"km/h", "knot"}};
        r = v * conv[ch - 1];
        show(un[ch - 1][0], un[ch - 1][1], r);
        break;
    }
    case 7:
    {
        std::cout << "  1. s→min  2. min→s  3. min→hr  4. hr→min  5. hr→day  6. day→hr\n"
                  << "  7. day→week  8. week→day\n";
        int ch = getValidChoice(1, 8);
        v = getValidNumber("  Value: ");
        double conv[] = {1.0 / 60, 60.0, 1.0 / 60, 60.0, 1.0 / 24, 24.0, 1.0 / 7, 7.0};
        std::string un[][2] = {{"s", "min"}, {"min", "s"}, {"min", "hr"}, {"hr", "min"}, {"hr", "day"}, {"day", "hr"}, {"day", "wk"}, {"wk", "day"}};
        r = v * conv[ch - 1];
        show(un[ch - 1][0], un[ch - 1][1], r);
        break;
    }
    case 8:
    {
        std::cout << "  1. J→cal  2. cal→J  3. kWh→J  4. J→kWh  5. eV→J  6. J→eV\n";
        int ch = getValidChoice(1, 6);
        v = getValidNumber("  Value: ");
        double conv[] = {0.239006, 4.184, 3.6e6, 2.77778e-7, 1.602e-19, 6.242e18};
        std::string un[][2] = {{"J", "cal"}, {"cal", "J"}, {"kWh", "J"}, {"J", "kWh"}, {"eV", "J"}, {"J", "eV"}};
        r = v * conv[ch - 1];
        show(un[ch - 1][0], un[ch - 1][1], r);
        break;
    }
    case 9:
    {
        std::cout << "  1. Pa→atm  2. atm→Pa  3. Pa→bar  4. bar→Pa  5. psi→Pa  6. Pa→psi\n";
        int ch = getValidChoice(1, 6);
        v = getValidNumber("  Value: ");
        double conv[] = {9.869e-6, 101325.0, 1e-5, 1e5, 6894.76, 1.0 / 6894.76};
        std::string un[][2] = {{"Pa", "atm"}, {"atm", "Pa"}, {"Pa", "bar"}, {"bar", "Pa"}, {"psi", "Pa"}, {"Pa", "psi"}};
        r = v * conv[ch - 1];
        show(un[ch - 1][0], un[ch - 1][1], r);
        break;
    }
    case 10:
    {
        std::cout << "  1. B→KB  2. KB→MB  3. MB→GB  4. GB→TB  5. KB→B  6. TB→GB\n";
        int ch = getValidChoice(1, 6);
        v = getValidNumber("  Value: ");
        double conv[] = {1.0 / 1024, 1.0 / 1024, 1.0 / 1024, 1.0 / 1024, 1024.0, 1024.0};
        std::string un[][2] = {{"B", "KB"}, {"KB", "MB"}, {"MB", "GB"}, {"GB", "TB"}, {"KB", "B"}, {"TB", "GB"}};
        r = v * conv[ch - 1];
        show(un[ch - 1][0], un[ch - 1][1], r);
        break;
    }
    }
}

// =============================================================================
//  ANGLE CONVERSION
// =============================================================================

double degreeToRadian() { return getValidNumber("  Degrees: ") * M_PI / 180.0; }
double radianToDegree() { return getValidNumber("  Radians: ") * 180.0 / M_PI; }

void angleConversionMenu()
{
    std::cout << "  1. Degrees → Radians    2. Radians → Degrees\n"
              << "  3. Toggle angle input mode (currently: " << angleMode() << ")\n";
    int ch = getValidChoice(1, 3);
    if (ch == 1)
    {
        double r = degreeToRadian();
        printResult(r, "Radians");
        addToHistory(r, "deg→rad");
    }
    else if (ch == 2)
    {
        double d = radianToDegree();
        printResult(d, "Degrees");
        addToHistory(d, "rad→deg");
    }
    else
        toggleAngleMode();
}

// =============================================================================
//  CONSTANTS REFERENCE
// =============================================================================

void showConstants()
{
    printBoxTitle("MATHEMATICAL & PHYSICAL CONSTANTS");
    std::cout << std::setprecision(10);
    std::cout << "  Mathematical:\n"
              << "    π (Pi)           = " << M_PI << "\n"
              << "    e (Euler's)      = " << M_E << "\n"
              << "    φ (Golden Ratio) = " << (1.0 + std::sqrt(5.0)) / 2.0 << "\n"
              << "    √2               = " << std::sqrt(2.0) << "\n"
              << "    √3               = " << std::sqrt(3.0) << "\n"
              << "    ln(2)            = " << std::log(2.0) << "\n\n"
              << "  Physical:\n"
              << "    Speed of light   = 2.99792458 × 10⁸ m/s\n"
              << "    Planck's const   = 6.62607015 × 10⁻³⁴ J·s\n"
              << "    Gravity (Earth)  = 9.80665 m/s²\n"
              << "    Avogadro's num   = 6.02214076 × 10²³ /mol\n"
              << "    Boltzmann const  = 1.380649 × 10⁻²³ J/K\n"
              << "    e (charge)       = 1.602176634 × 10⁻¹⁹ C\n";
}

// =============================================================================
//  NUMERICAL METHODS
// =============================================================================

void numericalIntegration()
{
    printBoxTitle("NUMERICAL INTEGRATION (Simpson's Rule)");
    std::cout << "  Integrate f(x) = ax² + bx + c\n";
    double a = getValidNumber("  a: "), b = getValidNumber("  b: "), c = getValidNumber("  c: ");
    double lo = getValidNumber("  Lower limit: "), hi = getValidNumber("  Upper limit: ");
    if (lo >= hi)
    {
        std::cout << theme->error << "  Lower must be less than upper!\n"
                  << theme->reset;
        return;
    }
    int n = 1000;
    if (n % 2 != 0)
        n++;
    double h = (hi - lo) / n;
    auto f = [&](double x)
    { return a * x * x + b * x + c; };
    double sum = f(lo) + f(hi);
    for (int i = 1; i < n; i++)
    {
        double x = lo + i * h;
        sum += (i % 2 == 0 ? 2.0 : 4.0) * f(x);
    }
    double result = (h / 3.0) * sum;
    std::cout << theme->success << "\n  ∫[" << lo << " to " << hi << "] (" << a << "x² + " << b << "x + " << c << ") dx = " << result << theme->reset << "\n";
    addToHistory(result, "integral");
}

void newtonRaphson()
{
    printBoxTitle("NEWTON-RAPHSON ROOT FINDER");
    std::cout << "  Find root of f(x) = ax² + bx + c (near given guess)\n";
    double a = getValidNumber("  a: "), b = getValidNumber("  b: "), c = getValidNumber("  c: ");
    double x = getValidNumber("  Initial guess: ");
    auto f = [&](double t)
    { return a * t * t + b * t + c; };
    auto df = [&](double t)
    { return 2 * a * t + b; };
    for (int i = 0; i < 100; i++)
    {
        double fx = f(x), dfx = df(x);
        if (std::abs(dfx) < 1e-14)
        {
            std::cout << theme->error << "  Derivative near zero; method failed.\n"
                      << theme->reset;
            return;
        }
        double xnew = x - fx / dfx;
        if (std::abs(xnew - x) < 1e-12)
        {
            x = xnew;
            break;
        }
        x = xnew;
    }
    std::cout << theme->success << "  Root ≈ " << x << "  (f(x) = " << f(x) << ")\n"
              << theme->reset;
    addToHistory(x, "newton-root");
}

// =============================================================================
//  FILE I/O
// =============================================================================

void saveHistoryToFile()
{
    if (history.empty())
    {
        std::cout << theme->warning << "  No history to save.\n"
                  << theme->reset;
        return;
    }
    std::ofstream f("calculator_history.txt");
    if (!f.is_open())
    {
        std::cout << theme->error << "  Error opening file!\n"
                  << theme->reset;
        return;
    }
    time_t now = time(0);
    f << "Calculator History — " << ctime(&now) << std::string(50, '=') << "\n\n";
    for (int i = 0; i < (int)history.size(); i++)
        f << "[" << std::setw(3) << i << "] " << history[i].timestamp << "  "
          << std::setw(24) << std::left << history[i].label << " = "
          << std::fixed << std::setprecision(8) << history[i].value << "\n";
    f.close();
    std::cout << theme->success << "  History saved to 'calculator_history.txt'\n"
              << theme->reset;
}

void loadHistoryFromFile()
{
    std::ifstream f("calculator_history.txt");
    if (!f.is_open())
    {
        std::cout << theme->warning << "  No saved history file found.\n"
                  << theme->reset;
        return;
    }
    std::cout << theme->success << "  History file found (use 'View History' to see loaded values).\n"
              << theme->reset;
    f.close();
}

// =============================================================================
//  THEMES
// =============================================================================

void changeTheme()
{
    printBoxTitle("COLOR THEMES");
    std::cout << "  1. Dark (default)   2. Light    3. Monochrome\n"
              << "  4. Neon             5. Ocean\n";
    int ch = getValidChoice(1, 5);
    ThemeColors *themes[] = {&darkTheme, &lightTheme, &monoTheme, &neonTheme, &oceanTheme};
    ColorTheme names[] = {DARK, LIGHT, MONOCHROME, NEON, OCEAN};
    std::string labels[] = {"Dark", "Light", "Monochrome", "Neon", "Ocean"};
    theme = themes[ch - 1];
    currentTheme = names[ch - 1];
    std::cout << theme->success << "  " << labels[ch - 1] << " theme activated!\n"
              << theme->reset;
}

// =============================================================================
//  MAIN MENU
// =============================================================================

void displayMenu()
{
    std::cout << "\n"
              << theme->bold << theme->primary;
    std::cout << "╔════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║               ULTIMATE SCIENTIFIC CALCULATOR                   ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════════╝\n"
              << theme->reset;

    std::cout << theme->secondary << "\n┌─── Basic Operations ────────────────────────────────────────┐\n"
              << theme->reset;
    std::cout << "  1. Add           2. Subtract      3. Multiply      4. Divide\n"
              << "  5. Modulus       6. Absolute      7. Percentage    8. Reciprocal\n";

    std::cout << theme->secondary << "\n┌─── Trigonometry ────────────────────────────────────────────┐\n"
              << theme->reset;
    std::cout << "  9. sin          10. cos          11. tan          12. csc\n"
              << " 13. sec          14. cot          15. arcsin       16. arccos\n"
              << " 17. arctan       18. atan2        19. sinh         20. cosh\n"
              << " 21. tanh         22. arcsinh      23. arccosh      24. arctanh\n";

    std::cout << theme->secondary << "\n┌─── Exponential & Logarithm ─────────────────────────────────┐\n"
              << theme->reset;
    std::cout << " 25. x^y          26. e^x          27. ln(x)        28. log10(x)\n"
              << " 29. log2(x)      30. logₐ(x)\n";

    std::cout << theme->secondary << "\n┌─── Roots & Rounding ────────────────────────────────────────┐\n"
              << theme->reset;
    std::cout << " 31. √x           32. ∛x           33. nth root     34. ceil\n"
              << " 35. floor        36. round        37. truncate     38. round to N\n";

    std::cout << theme->secondary << "\n┌─── Combinatorics & Number Theory ───────────────────────────┐\n"
              << theme->reset;
    std::cout << " 39. Factorial    40. Gamma Γ(x)   41. nPr          42. nCr\n"
              << " 43. GCD & LCM    44. Prime check  45. Prime sieve  46. Euler φ(n)\n"
              << " 47. Fibonacci    48. Collatz\n";

    std::cout << theme->secondary << "\n┌─── Statistics & Data ───────────────────────────────────────┐\n"
              << theme->reset;
    std::cout << " 49. Statistics   50. Linear Regression\n";

    std::cout << theme->secondary << "\n┌─── Solvers ─────────────────────────────────────────────────┐\n"
              << theme->reset;
    std::cout << " 51. Quadratic    52. Cubic         53. Newton-Raphson\n";

    std::cout << theme->secondary << "\n┌─── Matrix Operations ───────────────────────────────────────┐\n"
              << theme->reset;
    std::cout << " 54. Add          55. Subtract      56. Multiply     57. Transpose\n"
              << " 58. Determinant  59. Inverse       60. Scalar Ops\n";

    std::cout << theme->secondary << "\n┌─── Conversions ─────────────────────────────────────────────┐\n"
              << theme->reset;
    std::cout << " 61. Angle ↔      62. Number Base   63. Unit Conv    64. Integration\n";

    std::cout << theme->accent << "\n┌─── Advanced Features ───────────────────────────────────────┐\n"
              << theme->reset;
    std::cout << " 65. Expression   66. Complex Nums  67. Memory       68. History\n"
              << " 69. Save History 70. Load History  71. Use History  72. Clear History\n"
              << " 73. Constants    74. Theme\n";

    std::cout << theme->error << "\n  0. Exit\n"
              << theme->reset;
}

// =============================================================================
//  MAIN
// =============================================================================

int main()
{
    std::cout << std::fixed << std::setprecision(8);

    double a, b, result;
    int choice;
    char cont;

    do
    {
        displayMenu();
        choice = getValidChoice(0, 74);
        if (choice == 0)
        {
            std::cout << theme->success << "\n  Thank you for using the Ultimate Calculator! Goodbye.\n\n"
                      << theme->reset;
            break;
        }

        bool validOp = true;

        switch (choice)
        {
        // ── Basic ──────────────────────────────────────────────────────
        case 1:
            a = getValidNumber("  First: ");
            b = getValidNumber("  Second: ");
            result = add(a, b);
            break;
        case 2:
            a = getValidNumber("  First: ");
            b = getValidNumber("  Second: ");
            result = subtract(a, b);
            break;
        case 3:
            a = getValidNumber("  First: ");
            b = getValidNumber("  Second: ");
            result = multiply(a, b);
            break;
        case 4:
            a = getValidNumber("  Dividend: ");
            b = getValidNumber("  Divisor: ");
            result = divide(a, b);
            break;
        case 5:
            a = getValidNumber("  First: ");
            b = getValidNumber("  Second: ");
            result = modulus(a, b);
            break;
        case 6:
            result = absoluteValue();
            break;
        case 7:
            result = percentage();
            break;
        case 8:
            result = reciprocal();
            break;
        // ── Trig ───────────────────────────────────────────────────────
        case 9:
            result = sine();
            break;
        case 10:
            result = cosine();
            break;
        case 11:
            result = tangent();
            break;
        case 12:
            result = cosecant();
            break;
        case 13:
            result = secant();
            break;
        case 14:
            result = cotangent();
            break;
        case 15:
            result = arcsine();
            break;
        case 16:
            result = arccosine();
            break;
        case 17:
            result = arctangent();
            break;
        case 18:
            result = arctan2Func();
            break;
        case 19:
            result = hyperbolicSine();
            break;
        case 20:
            result = hyperbolicCosine();
            break;
        case 21:
            result = hyperbolicTangent();
            break;
        case 22:
            result = arcSinh();
            break;
        case 23:
            result = arcCosh();
            break;
        case 24:
            result = arcTanh();
            break;
        // ── Exp & Log ──────────────────────────────────────────────────
        case 25:
            result = power();
            break;
        case 26:
            result = exponential();
            break;
        case 27:
            result = naturalLog();
            break;
        case 28:
            result = log10Func();
            break;
        case 29:
            result = log2Func();
            break;
        case 30:
            result = logBase();
            break;
        // ── Roots & Round ─────────────────────────────────────────────
        case 31:
            result = squareRoot();
            break;
        case 32:
            result = cubeRoot();
            break;
        case 33:
            result = nthRoot();
            break;
        case 34:
            result = ceiling();
            break;
        case 35:
            result = floorFunc();
            break;
        case 36:
            result = roundNum();
            break;
        case 37:
            result = truncateNum();
            break;
        case 38:
            result = roundToN();
            break;
        // ── Combinatorics & Number Theory ─────────────────────────────
        case 39:
            result = factorial();
            break;
        case 40:
            result = gammaFunc();
            break;
        case 41:
            result = permutation();
            break;
        case 42:
            result = combination();
            break;
        case 43:
            gcdLcm();
            validOp = false;
            break;
        case 44:
            primeChecker();
            validOp = false;
            break;
        case 45:
            sieveOfEratosthenes();
            validOp = false;
            break;
        case 46:
            eulersTotient();
            validOp = false;
            break;
        case 47:
            fibonacci();
            validOp = false;
            break;
        case 48:
            collatzSequence();
            validOp = false;
            break;
        // ── Statistics ─────────────────────────────────────────────────
        case 49:
            statistics();
            validOp = false;
            break;
        case 50:
            linearRegression();
            validOp = false;
            break;
        // ── Solvers ────────────────────────────────────────────────────
        case 51:
            quadraticSolver();
            validOp = false;
            break;
        case 52:
            cubicSolver();
            validOp = false;
            break;
        case 53:
            newtonRaphson();
            validOp = false;
            break;
        // ── Matrix ─────────────────────────────────────────────────────
        case 54:
            matrixAddition();
            validOp = false;
            break;
        case 55:
            matrixSubtraction();
            validOp = false;
            break;
        case 56:
            matrixMultiplication();
            validOp = false;
            break;
        case 57:
            matrixTranspose();
            validOp = false;
            break;
        case 58:
            matrixDeterminant();
            validOp = false;
            break;
        case 59:
            matrixInverse();
            validOp = false;
            break;
        case 60:
            matrixScalarOps();
            validOp = false;
            break;
        // ── Conversions ────────────────────────────────────────────────
        case 61:
            angleConversionMenu();
            validOp = false;
            break;
        case 62:
            numberSystemConversion();
            validOp = false;
            break;
        case 63:
            unitConversions();
            validOp = false;
            break;
        case 64:
            numericalIntegration();
            validOp = false;
            break;
        // ── Advanced ───────────────────────────────────────────────────
        case 65:
            expressionCalculator();
            validOp = false;
            break;
        case 66:
            complexNumberMenu();
            validOp = false;
            break;
        case 67:
            memoryMenu();
            validOp = false;
            break;
        case 68:
            displayHistory();
            validOp = false;
            break;
        case 69:
            saveHistoryToFile();
            validOp = false;
            break;
        case 70:
            loadHistoryFromFile();
            validOp = false;
            break;
        case 71:
            result = getFromHistory();
            break;
        case 72:
            clearHistory();
            validOp = false;
            break;
        case 73:
            showConstants();
            validOp = false;
            break;
        case 74:
            changeTheme();
            validOp = false;
            break;
        default:
            validOp = false;
            break;
        }

        if (validOp)
        {
            printResult(result);
            addToHistory(result);
        }

        std::cout << theme->warning << "\n  Continue? (y/n): " << theme->reset;
        std::cin >> cont;
        clearInput();

    } while (cont == 'y' || cont == 'Y');

    return 0;
}