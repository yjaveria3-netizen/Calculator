<div align="center">

# 🧮 Ultimate Scientific Calculator

### *A Powerful Command-Line Mathematical Powerhouse*

[![C++](https://img.shields.io/badge/C++-11%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS%20%7C%20Windows-lightgrey?style=for-the-badge)](https://github.com/)
[![License](https://img.shields.io/badge/License-Educational-green?style=for-the-badge)](https://github.com/)

*An interactive, feature-rich scientific calculator with expression parsing, complex numbers, matrix operations, and customizable themes.*

[Features](#-features) • [Installation](#-installation) • [Usage](#-usage) • [Examples](#-examples) • [Contributing](#-contributing)

</div>

---

## ✨ Highlights

🚀 **44 Mathematical Operations** spanning basic arithmetic to advanced calculus  
🎨 **Customizable Themes** - Dark, Light, and Monochrome color schemes  
🧠 **Smart Expression Parser** - Evaluate complex expressions with proper operator precedence  
💾 **Memory & History** - Store and recall up to 50 previous calculations  
📊 **Statistical Analysis** - Mean, median, mode, variance, and standard deviation  
🔢 **Number System Converter** - Binary, Octal, Decimal, and Hexadecimal  
🎯 **Zero Error Tolerance** - Robust input validation and error handling  

---

## 🎯 Features

<table>
<tr>
<td width="50%">

### 🧮 Core Operations
- ➕ **Basic Arithmetic**  
  Addition, subtraction, multiplication, division, modulus
  
- 📐 **Trigonometric Functions**  
  sin, cos, tan, arcsin, arccos, arctan
  
- 📈 **Hyperbolic Functions**  
  sinh, cosh, tanh
  
- 📊 **Logarithmic & Exponential**  
  ln(x), log10(x), log2(x), e^x
  
- 🔢 **Roots & Powers**  
  x^y, √x, ∛x, ⁿ√x
  
- ⚡ **Rounding Functions**  
  ceiling, floor, round, absolute value
  
- 🎲 **Factorial Calculation**  
  n! for combinatorial problems

</td>
<td width="50%">

### 🔬 Advanced Mathematics
- 🧪 **Expression Parser**  
  Evaluate `(3 + 5) * 2^3 - 10` instantly
  
- 🌀 **Complex Numbers**  
  Full support for operations with imaginary numbers
  
- 📏 **Matrix Operations**  
  Addition and multiplication up to 10×10 matrices
  
- 🎰 **Combinatorics**  
  Permutations (nPr) and Combinations (nCr)
  
- 🔐 **Number Theory**  
  GCD and LCM calculations
  
- 🎯 **Quadratic Solver**  
  Real and complex roots with discriminant analysis
  
- 📊 **Statistics Suite**  
  Complete statistical analysis toolkit

</td>
</tr>
</table>

### 🔄 Conversion Tools

| Category | Conversions Available |
|----------|----------------------|
| 📐 **Angles** | Degrees ↔ Radians |
| 🔢 **Number Systems** | Binary • Octal • Decimal • Hexadecimal |
| 📏 **Length** | Meters • Feet • Kilometers • Miles |
| 🌡️ **Temperature** | Celsius • Fahrenheit • Kelvin |
| ⚖️ **Weight** | Kilograms • Pounds |

### 💾 Smart Features

- **Memory Functions**: Store (MS), Recall (MR), Clear (MC), Add (M+)
- **Calculation History**: Automatically stores up to 50 calculations
- **History Export**: Save your calculation history to file
- **History Recall**: Reuse any previous result instantly
- **Smart Input Validation**: Never worry about invalid inputs

### 🎨 Visual Customization

Choose from three beautiful color themes:

```
🌙 Dark Theme (Default)    - Cyan, blue, and green accents
☀️  Light Theme            - Bright colors for light backgrounds  
⬛ Monochrome Theme        - Classic black & white for any terminal
```

- Beautiful Unicode box-drawing characters
- Color-coded outputs for instant recognition
- Professional formatting with elegant borders

---

## 🚀 Installation

### Prerequisites

<table>
<tr>
<td>

**Required**
- C++ Compiler with C++11+ support
  - GCC 4.8+
  - Clang 3.3+
  - MSVC 2015+
- Standard C++ Library

</td>
<td>

**Recommended**
- Terminal with Unicode support
- 256-color terminal for best theme experience
- Modern terminal emulator (iTerm2, Windows Terminal, etc.)

</td>
</tr>
</table>

### Quick Start

#### 🐧 Linux / 🍎 macOS

```bash
# Clone or download the source
# Navigate to the directory containing Calculator.cpp

# Compile with g++
g++ -std=c++11 Calculator.cpp -o calculator

# Or with optimizations for better performance
g++ -std=c++11 -O3 Calculator.cpp -o calculator

# Run the calculator
./calculator
```

#### 🪟 Windows

**Using MinGW/g++:**
```cmd
g++ -std=c++11 Calculator.cpp -o calculator.exe
calculator.exe
```

**Using MSVC (Visual Studio):**
```cmd
cl /EHsc /std:c++11 Calculator.cpp
Calculator.exe
```

#### 🎯 Alternative Compilation Options

```bash
# With debugging symbols
g++ -std=c++11 -g Calculator.cpp -o calculator

# With all warnings enabled
g++ -std=c++11 -Wall -Wextra Calculator.cpp -o calculator

# Using clang++ instead
clang++ -std=c++11 -O2 Calculator.cpp -o calculator
```

### Verification

After compilation, test with a simple calculation:

```bash
./calculator
# Choose option 1 (Addition)
# Enter: 42 and 8
# Expected result: 50.000000
```

---

## 📖 Usage

### Main Menu Navigation

Upon launching, you'll be greeted with an elegant menu featuring **44 operations** organized into intuitive categories:

```
╔════════════════════════════════════════════════════════════════╗
║         ULTIMATE SCIENTIFIC CALCULATOR v3.0                    ║
╚════════════════════════════════════════════════════════════════╝

┌─── Basic Operations ───┐
 1. Addition            2. Subtraction         3. Multiplication
 4. Division            5. Modulus             6. Absolute Value

┌─── Trigonometric ───┐
 7-15. Full suite of trig and inverse trig functions

┌─── Advanced Features ───┐
38. Expression Parser  39. Complex Numbers    40. Memory Ops
41. View History       42. Save History       43. Use History Value
44. Change Theme

 0. Exit Calculator
```

### Basic Operation Flow

1. **Select Operation** → Enter number (0-44)
2. **Input Values** → Provide required numbers
3. **View Result** → See formatted output
4. **Continue or Exit** → Choose to keep calculating

---

## 💡 Examples

### Example 1: Basic Arithmetic

```
Enter your choice: 3
Enter first number: 25.5
Enter second number: 4
┌─────────────────────┐
│ Result: 102.000000  │
└─────────────────────┘
```

### Example 2: Advanced Expression Parsing

```
Enter your choice: 38
Enter mathematical expression: (15 + 25) * 2^4 - 100 / 5

Evaluating: (15 + 25) * 2^4 - 100 / 5
Step-by-step:
  (40) * 16 - 20
  640 - 20
  
┌─────────────────────┐
│ Result: 620.000000  │
└─────────────────────┘
```

### Example 3: Complex Number Operations

```
Enter your choice: 39

Complex Number Operations:
1. Addition     2. Subtraction
3. Multiply     4. Division
5. Magnitude    6. Phase

Enter choice: 1

Enter first complex number:
Real part: 3
Imaginary part: 4

Enter second complex number:
Real part: 2
Imaginary part: -1

Result: (5 + 3i)
Magnitude: 5.831
Phase: 0.540 radians
```

### Example 4: Matrix Operations

```
Enter your choice: 37  # Matrix Multiplication

Matrix A dimensions:
Rows: 2
Columns: 3

Enter elements for Matrix A:
[1][1]: 1    [1][2]: 2    [1][3]: 3
[2][1]: 4    [2][2]: 5    [2][3]: 6

Matrix B dimensions:
Rows: 3
Columns: 2

Enter elements for Matrix B:
[1][1]: 7    [1][2]: 8
[2][1]: 9    [2][2]: 10
[3][1]: 11   [3][2]: 12

Result Matrix (2x2):
╔              ╗
║  58    64    ║
║ 139   154    ║
╚              ╝
```

### Example 5: Statistical Analysis

```
Enter your choice: 28

Enter number of values: 5
Enter value 1: 10
Enter value 2: 20
Enter value 3: 30
Enter value 4: 40
Enter value 5: 50

Statistical Analysis:
━━━━━━━━━━━━━━━━━━━━
Mean:               30.000000
Median:             30.000000
Mode:               No unique mode
Variance:          250.000000
Standard Deviation: 15.811388
Sum:               150.000000
Range:              40.000000
```

### Example 6: Using Memory & History

```
# First calculation
Enter your choice: 16  # Power
Base: 2
Exponent: 10
Result: 1024.000000

Enter your choice: 40  # Memory Operations
1. Store (MS)
Choice: 1
Value 1024.000000 stored in memory.

# Later calculation
Enter your choice: 4  # Division
Enter dividend: 5120
Enter divisor: [Press option to recall memory]

# Using history
Enter your choice: 43  # Use History Value
[0] Power(2, 10) = 1024.000000
[1] Division = 5.000000
Enter history index: 0
Using value: 1024.000000
```

### Example 7: Number System Conversion

```
Enter your choice: 30

Number System Conversion:
1. Decimal to Binary
2. Decimal to Octal
3. Decimal to Hexadecimal
4. Binary to Decimal
5. Octal to Decimal
6. Hexadecimal to Decimal

Choice: 3
Enter decimal number: 255

Results:
━━━━━━━━━━━━━━━━━━━━
Decimal:      255
Hexadecimal:  FF
Binary:       11111111
Octal:        377
```

### Example 8: Quadratic Equation Solver

```
Enter your choice: 35

Quadratic Equation Solver (ax² + bx + c = 0)
Enter coefficient a: 1
Enter coefficient b: -5
Enter coefficient c: 6

Analysis:
━━━━━━━━━━━━━━━━━━━━
Discriminant: 1.000000
Nature: Two distinct real roots

Solutions:
Root 1 (x₁): 3.000000
Root 2 (x₂): 2.000000

Verification:
1(3)² - 5(3) + 6 = 0 ✓
1(2)² - 5(2) + 6 = 0 ✓
```

---

## 🔧 Technical Deep Dive

### Architecture & Design

The calculator is built with a modular architecture that separates concerns:

```
┌─────────────────────────────────────┐
│         User Interface Layer        │
│  (Menu, Input Validation, Themes)   │
├─────────────────────────────────────┤
│       Calculation Engine Layer      │
│  (Core Math, Advanced Operations)   │
├─────────────────────────────────────┤
│      Expression Parser Layer        │
│   (Tokenization, Shunting Yard)     │
├─────────────────────────────────────┤
│     Memory & History Layer          │
│  (State Management, Persistence)    │
└─────────────────────────────────────┘
```

### Core Libraries & Dependencies

| Library | Purpose | Key Functions Used |
|---------|---------|-------------------|
| `<iostream>` | I/O Operations | `cin`, `cout`, stream manipulation |
| `<cmath>` | Mathematical Functions | `sin`, `cos`, `pow`, `sqrt`, `log` |
| `<iomanip>` | Output Formatting | `setprecision`, `fixed` |
| `<vector>` | Dynamic Arrays | History storage, datasets |
| `<string>` | String Processing | Expression parsing |
| `<complex>` | Complex Numbers | `complex<double>` operations |
| `<stack>` | Data Structures | Expression evaluation |
| `<map>` | Associative Arrays | Operator mapping |
| `<fstream>` | File I/O | History export |

### Key Algorithms Implemented

#### 1. **Shunting Yard Algorithm** (Expression Parser)
```
Purpose: Convert infix notation to postfix for evaluation
Complexity: O(n) where n is expression length
Handles: Operator precedence, parentheses, unary operators
```

#### 2. **Euclidean Algorithm** (GCD Calculation)
```
Purpose: Find greatest common divisor efficiently
Complexity: O(log min(a,b))
Extension: LCM calculated as (a * b) / GCD(a, b)
```

#### 3. **Statistical Computations**
```
Mean: Σx / n
Variance: Σ(x - μ)² / n
Std Dev: √variance
Median: Sort-based with even/odd handling
Mode: Frequency analysis with hash map
```

#### 4. **Quadratic Formula with Discriminant Analysis**
```
For ax² + bx + c = 0:
Δ = b² - 4ac

If Δ > 0:  Two distinct real roots
If Δ = 0:  One repeated real root
If Δ < 0:  Two complex conjugate roots
```

### Input Validation System

The calculator implements multi-layer validation:

```cpp
Layer 1: Type Checking
  ↓ Ensures numeric input
Layer 2: Range Validation  
  ↓ Checks menu choices, constraints
Layer 3: Domain Checking
  ↓ Validates mathematical domains (e.g., sqrt(x) requires x ≥ 0)
Layer 4: Error Recovery
  ↓ Clears bad input, prompts retry
```

### Expression Parser Features

**Supported Operators:**
- `+` Addition (Precedence: 1)
- `-` Subtraction (Precedence: 1)
- `*` Multiplication (Precedence: 2)
- `/` Division (Precedence: 2)
- `^` Exponentiation (Precedence: 3, right-associative)

**Special Handling:**
- ✅ Parentheses for grouping: `(2 + 3) * 4`
- ✅ Negative numbers: `-5 + 10`
- ✅ Decimal numbers: `3.14159 * 2`
- ✅ Operator precedence: `2 + 3 * 4 = 14`
- ✅ Nested expressions: `((2 + 3) * (4 - 1))^2`

**Example Parsing:**
```
Input:  (3 + 5) * 2^3 - 10
Tokens: [ '(', 3, '+', 5, ')', '*', 2, '^', 3, '-', 10 ]
Infix:  ( 3 + 5 ) * 2 ^ 3 - 10
Postfix: 3 5 + 2 3 ^ * 10 -
Result: 54
```

---

## ⚠️ Known Limitations & Constraints

| Feature | Limitation | Reason |
|---------|-----------|--------|
| **Factorial** | n ≤ 170 | Prevents integer overflow on 64-bit systems |
| **Matrix Operations** | Max 10×10 matrices | Memory and performance optimization |
| **History** | 50 most recent calculations | Prevents excessive memory usage |
| **Expression Functions** | No function calls in expressions | Parser limitation (e.g., can't use `sin(45)` in expression) |
| **Trigonometry** | Input in radians by default | Use conversion feature for degrees |
| **File Export** | History only (no settings) | Current implementation scope |

### Important Notes

⚠️ **Division by Zero**: Automatically caught and reported with error message  
⚠️ **Domain Errors**: Functions like `sqrt(-1)` handled with proper error messages  
⚠️ **Overflow**: Very large calculations may exceed numeric limits  
⚠️ **Precision**: Results displayed to 6 decimal places by default

---

## 🐛 Troubleshooting

<details>
<summary><b>🎨 Colors not displaying correctly</b></summary>

**Symptoms:** Strange characters or incorrect colors in terminal

**Solutions:**
1. Switch to Monochrome theme (Menu Option 44)
2. Ensure terminal supports ANSI color codes
3. Try a modern terminal emulator:
   - Windows: Windows Terminal, ConEmu
   - macOS: iTerm2, built-in Terminal.app
   - Linux: GNOME Terminal, Konsole, Alacritty

</details>

<details>
<summary><b>⚙️ Compilation errors</b></summary>

**Symptoms:** Build fails with C++ standard errors

**Solutions:**
```bash
# Ensure C++11 flag is set
g++ -std=c++11 Calculator.cpp -o calculator

# Check compiler version
g++ --version  # Should be 4.8 or higher

# Try with more verbose output
g++ -std=c++11 -Wall -Wextra Calculator.cpp -o calculator
```

</details>

<details>
<summary><b>🔢 Division by zero errors</b></summary>

**Symptoms:** Error message when dividing

**Solution:** The calculator automatically detects division by zero. Ensure divisor is non-zero.

</details>

<details>
<summary><b>⌨️ Input stuck in loop</b></summary>

**Symptoms:** Calculator keeps asking for input

**Solution:** 
- Enter valid numeric values when prompted
- Press Ctrl+C to force exit if needed
- Restart the calculator

</details>

<details>
<summary><b>📊 Matrix multiplication fails</b></summary>

**Symptoms:** Error when multiplying matrices

**Cause:** Matrix dimensions incompatible (A columns ≠ B rows)

**Solution:** For A(m×n) × B(p×q), ensure n = p

</details>

<details>
<summary><b>🔢 Unexpected results in expression parser</b></summary>

**Symptoms:** Expression gives wrong answer

**Checklist:**
- ✅ Check operator precedence (PEMDAS)
- ✅ Verify parentheses are balanced
- ✅ Ensure proper spacing isn't critical
- ✅ Test with simpler subexpressions

**Example:**
```
Wrong: 2+3*4    (User expects 20, gets 14)
Right: (2+3)*4  (Correctly gives 20)
```

</details>

---

## 🚀 Future Enhancements

### 📋 Planned Features

<table>
<tr>
<td width="50%">

**🎯 High Priority**
- [ ] Function calls in expressions (`sin(45)`, `sqrt(16)`)
- [ ] Variable support (`x = 5`, `y = x * 2`)
- [ ] Equation solver system (multiple equations)
- [ ] Configuration file for persistent settings
- [ ] Command-line argument support
- [ ] Copy result to clipboard

</td>
<td width="50%">

**💡 Medium Priority**
- [ ] ASCII graph plotting
- [ ] Derivative calculator (symbolic)
- [ ] Integration (numerical methods)
- [ ] More unit conversions (time, data size, etc.)
- [ ] Export to CSV/JSON formats
- [ ] Programmable functions/macros

</td>
</tr>
</table>

**🔮 Advanced Ideas**
- [ ] GUI version (Qt/GTK)
- [ ] Web-based interface
- [ ] Plugin system for custom functions
- [ ] Multi-line expression support
- [ ] LaTeX output for mathematical notation
- [ ] Interactive tutorial mode
- [ ] Voice command input (experimental)

### 💭 Community Wishlist

Have an idea? Check if it's already suggested:
- Calculus operations (derivatives, integrals)
- 3D matrix operations
- Probability distributions
- Financial calculations (NPV, IRR, etc.)
- Physics formulas library
- Chemistry molecular calculations

---

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

### 🐛 Bug Reports
Found a bug? Please include:
- Operating system and compiler version
- Steps to reproduce
- Expected vs actual behavior
- Screenshots if applicable

### 💻 Code Contributions

**Priority Areas:**
1. **Performance Optimization** - Speed up matrix operations, expression parsing
2. **New Mathematical Functions** - Expand the function library
3. **UI/UX Improvements** - Better formatting, clearer prompts
4. **Documentation** - Examples, tutorials, inline comments
5. **Testing** - Unit tests, edge case validation

**Coding Standards:**
- Follow existing code style and structure
- Add comments for complex algorithms
- Test thoroughly before submitting
- Update README for new features

### 📝 Documentation
- Fix typos or unclear explanations
- Add more usage examples
- Translate README to other languages
- Create video tutorials

### 🎨 Design
- Propose new color themes
- Improve ASCII art and borders
- Suggest UI layout improvements

---

## 📜 License

This project is available for **educational and personal use**. Feel free to:
- ✅ Use for learning and personal projects
- ✅ Modify and experiment
- ✅ Share with attribution

Please:
- ❌ Don't claim as your own work
- ❌ Don't sell commercially without permission

---

## 👏 Acknowledgments

Built with:
- ❤️ Passion for mathematics
- 🧠 Problem-solving enthusiasm
- ⌨️ Lots of coffee and debugging

**Special Thanks:**
- C++ Standard Library maintainers
- Open source community
- Mathematical pioneers whose algorithms power this tool

---

## 🌟 Star This Project!

If you found this calculator useful, please consider giving it a star ⭐

**Made with 🧮 for the love of mathematics**

[Report Bug](https://github.com) • [Request Feature](https://github.com) • [Ask Question](https://github.com)

---

*"Mathematics is the language with which God has written the universe."* - Galileo Galilei

</div>