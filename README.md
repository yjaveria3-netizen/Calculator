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

🚀 **52 Mathematical Operations** spanning basic arithmetic to advanced calculus  
🎨 **Customizable Themes** - Dark, Light, and Monochrome color schemes  
🧠 **Smart Expression Parser** - Evaluate complex expressions with proper operator precedence  
💾 **Memory & History** - Store and recall up to 50 previous calculations  
📊 **Statistical Analysis** - Mean, median, mode, variance, and standard deviation  
🔢 **Number System Converter** - Binary, Octal, Decimal, and Hexadecimal  
🎯 **Zero Error Tolerance** - Robust input validation and error handling  
🔺 **Advanced Trigonometry** - Includes cosec, sec, cot functions  
🧬 **Prime Number Checker** - Instant primality testing with factor analysis  

---

## 🎯 Features

<table>
<tr>
<td width="50%">

### 🧮 Core Operations
- ➕ **Basic Arithmetic**  
  Addition, subtraction, multiplication, division, modulus, percentage
  
- 📐 **Trigonometric Functions**  
  sin, cos, tan, cosec, sec, cot, arcsin, arccos, arctan
  
- 📈 **Hyperbolic Functions**  
  sinh, cosh, tanh
  
- 📊 **Logarithmic & Exponential**  
  ln(x), log10(x), log2(x), logₐ(x), e^x
  
- 🔢 **Roots & Powers**  
  x^y, √x, ∛x, ⁿ√x
  
- ⚡ **Rounding Functions**  
  ceiling, floor, round, truncate, absolute value
  
- 🎲 **Factorial Calculation**  
  n! for combinatorial problems

</td>
<td width="50%">

### 🔬 Advanced Mathematics
- 🧪 **Expression Parser**  
  Evaluate `(3 + 5) * 2^3 - 10` instantly
  
- 🌀 **Complex Numbers**  
  Full support with conjugate operations
  
- 📏 **Matrix Operations**  
  Addition, multiplication, and transpose
  
- 🎰 **Combinatorics**  
  Permutations (nPr) and Combinations (nCr)
  
- 🔐 **Number Theory**  
  GCD, LCM, and prime number checking
  
- 🎯 **Quadratic Solver**  
  Real and complex roots with discriminant analysis
  
- 📊 **Statistics Suite**  
  Complete statistical analysis with mode detection

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

- **Enhanced Memory Functions**: Store (MS), Recall (MR), Clear (MC), Add (M+), Subtract (M-)
- **Calculation History**: Automatically stores up to 50 calculations
- **History Export**: Save your calculation history to file
- **History Recall**: Reuse any previous result instantly
- **Smart Input Validation**: Never worry about invalid inputs
- **Matrix File Export**: Save matrix results to text files
- **Statistics Reports**: Export statistical analysis to files

### 🎨 Visual Customization

Choose from three beautiful color themes:

```
🌙 Dark Theme (Default)    - Cyan, blue, and green accents
☀️  Light Theme            - Bright colors for light backgrounds  
⬛ Monochrome Theme        - Classic black & white for any terminal
```

- Beautiful Unicode box-drawing characters
- Color-coded outputs for instant recognition and aesthetics
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

Upon launching, you'll be greeted with an elegant menu featuring **52 operations** organized into intuitive categories:

```
╔════════════════════════════════════════════════════════════════╗
║               ULTIMATE SCIENTIFIC CALCULATOR                   ║
║                 ULTIMATE SCIENTIFIC CALCULATOR                 ║
╚════════════════════════════════════════════════════════════════╝

┌─── Basic Operations ───┐
 1. Addition            2. Subtraction         3. Multiplication
 4. Division            5. Modulus             6. Absolute Value
 7. Percentage

┌─── Trigonometric ───┐
 8-19. Complete trig suite including cosec, sec, cot

┌─── Advanced Features ───┐
46. Expression Parser  47. Complex Numbers    48. Memory Ops
49. View History       50. Save History       51. Use History Value
52. Change Theme

 0. Exit Calculator
```

### Basic Operation Flow

1. **Select Operation** → Enter number (0-52)
2. **Input Values** → Provide required numbers
3. **View Result** → See formatted output
4. **Continue or Exit** → Choose to keep calculating

---

## 💡 Examples

### Example 1: Reciprocal Trigonometric Functions

```
Enter your choice: 11
Enter angle in radians: 0.5236

┌─────────────────────┐
│ Result: 2.000000    │  (cosec(π/6) = 2)
└─────────────────────┘
```

### Example 2: Prime Number Checking

```
Enter your choice: 41
Enter a positive integer: 97

=== Prime Check ===
Number: 97
97 is a PRIME number!
```

### Example 3: Logarithm with Custom Base

```
Enter your choice: 25
Enter positive number: 1024
Enter positive base (≠ 1): 2

┌─────────────────────┐
│ Result: 10.000000   │  (log₂(1024) = 10)
└─────────────────────┘
```

### Example 4: Advanced Expression Parsing

```
Enter your choice: 46
Enter mathematical expression: (15 + 25) * 2^4 - 100 / 5

Evaluating: (15 + 25) * 2^4 - 100 / 5
Step-by-step:
  (40) * 16 - 20
  640 - 20
  
┌─────────────────────┐
│ Result: 620.000000  │
└─────────────────────┘
```

### Example 5: Complex Number Operations

```
Enter your choice: 47

Complex Number Operations:
1. Addition     2. Multiplication
3. Magnitude    4. Phase
5. Conjugate

Enter choice: 5

Enter real part: 3
Imaginary part: 4

Conjugate: 3 - 4i
```

### Example 6: Matrix Transpose

```
Enter your choice: 45

Enter number of rows: 2
Enter number of columns: 3

Enter elements of Matrix:
[0][0]: 1    [0][1]: 2    [0][2]: 3
[1][0]: 4    [1][1]: 5    [1][2]: 6

=== Original Matrix ===
         1          2          3 
         4          5          6 

=== Transposed Matrix ===
         1          4 
         2          5 
         3          6 
```

### Example 7: Statistical Analysis with Mode

```
Enter your choice: 34

How many numbers? 7
Enter number 1: 5
Enter number 2: 3
Enter number 3: 5
Enter number 4: 7
Enter number 5: 3
Enter number 6: 5
Enter number 7: 9

=== Statistics ===
Count: 7
Sum: 37.000000
Mean: 5.285714
Median: 5.000000
Mode: 5.000000
Minimum: 3.000000
Maximum: 9.000000
Range: 6.000000
Variance: 4.204082
Standard Deviation: 2.050385
```

### Example 8: Percentage Calculation

```
Enter your choice: 7
Enter number: 250
Enter percentage: 15

┌─────────────────────┐
│ Result: 37.500000   │  (15% of 250)
└─────────────────────┘
```

---

## 🔧 Technical Details

### Architecture Overview

```
┌─────────────────────────────────────────┐
│         User Interface Layer            │
│  (Colored menus, input validation)      │
└─────────────────────────────────────────┘
                    ↓
┌─────────────────────────────────────────┐
│       Calculator Engine Layer           │
│  (Math operations, algorithms)          │
└─────────────────────────────────────────┘
                    ↓
┌─────────────────────────────────────────┐
│      Data Management Layer              │
│  (History, memory, file I/O)            │
└─────────────────────────────────────────┘
```

### Code Structure

| Component | Purpose | Lines of Code |
|-----------|---------|---------------|
| **Color Themes** | Visual customization | ~70 |
| **Input Handling** | Validation & safety | ~100 |
| **Memory System** | Storage & recall | ~80 |
| **Expression Parser** | Evaluate expressions | ~150 |
| **Trig Functions** | Sin, cos, tan, cosec, sec, cot | ~120 |
| **Matrix Operations** | Linear algebra | ~200 |
| **Statistics** | Data analysis | ~100 |
| **File I/O** | Export functionality | ~120 |
| **Main Menu** | User interface | ~150 |

### Dependencies

| Library | Purpose | Usage |
|---------|---------|-------|
| `<iostream>` | I/O Operations | User input/output |
| `<cmath>` | Math Functions | Trig, log, exponential |
| `<vector>` | Dynamic Arrays | Matrix, data storage |
| `<complex>` | Complex Numbers | Imaginary arithmetic |
| `<stack>` | Expression Parsing | Shunting yard algorithm |
| `<map>` | Associative Arrays | Frequency analysis |
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

#### 3. **Sieve Optimization** (Prime Checking)
```
Purpose: Efficient primality testing
Complexity: O(√n)
Method: Trial division with 6k±1 optimization
```

#### 4. **Statistical Computations**
```
Mean: Σx / n
Variance: Σ(x - μ)² / n
Std Dev: √variance
Median: Sort-based with even/odd handling
Mode: Frequency analysis with hash map
```

#### 5. **Quadratic Formula with Discriminant Analysis**
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

## 🆕 New Features

### Reciprocal Trigonometric Functions
- **cosec(x)**: Cosecant function (1/sin(x))
- **sec(x)**: Secant function (1/cos(x))
- **cot(x)**: Cotangent function (1/tan(x))

All three functions include automatic domain checking and error handling for undefined values.

### Enhanced Memory Operations
- **M-**: New memory subtraction feature
- More intuitive 5-option menu for memory management

### Advanced Mathematical Tools
- **logₐ(x)**: Logarithm with custom base
- **Truncate**: Integer part extraction
- **Prime Checker**: Instant primality testing with factor display
- **Matrix Transpose**: Transform matrix dimensions

### Improved Statistics
- **Mode Detection**: Automatically identifies most frequent values
- Enhanced reporting with all statistical measures
- Better handling of multimodal datasets

### Complex Number Enhancements
- **Conjugate**: Calculate complex conjugate
- Improved display formatting

### Additional Utilities
- **Percentage Calculator**: Direct percentage calculations
- Enhanced file export options
- Better error messages and user guidance

---

## ⚠️ Known Limitations & Constraints

| Feature | Limitation | Reason |
|---------|-----------|--------|
| **Factorial** | n ≤ 20 | Prevents integer overflow |
| **Matrix Operations** | Max 10×10 matrices | Memory and performance optimization |
| **History** | 50 most recent calculations | Prevents excessive memory usage |
| **Expression Functions** | No function calls in expressions | Parser limitation |
| **Trigonometry** | Input in radians by default | Use conversion feature for degrees |
| **File Export** | History, matrix, statistics only | Current implementation scope |
| **Reciprocal Trig** | Domain errors handled | Returns infinity for undefined cases |

### Important Notes

⚠️ **Division by Zero**: Automatically caught and reported with error message  
⚠️ **Domain Errors**: Functions like `sqrt(-1)` handled with proper error messages  
⚠️ **Overflow**: Very large calculations may exceed numeric limits  
⚠️ **Precision**: Results displayed to 6 decimal places by default  
⚠️ **Undefined Values**: cosec(0), sec(π/2), cot(0) return infinity with warning

---

## 🐛 Troubleshooting

<details>
<summary><b>🎨 Colors not displaying correctly</b></summary>

**Symptoms:** Strange characters or incorrect colors in terminal

**Solutions:**
1. Switch to Monochrome theme (Menu Option 52)
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
<summary><b>📐 Undefined trigonometric values</b></summary>

**Symptoms:** Infinity or error for cosec, sec, cot

**Cause:** These functions are undefined at certain angles where their base functions equal zero

**Solution:** This is mathematically correct. The calculator warns you and returns infinity.

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
- [ ] Determinant calculation for matrices
- [ ] Inverse trigonometric reciprocal functions

</td>
<td width="50%">

**💡 Medium Priority**
- [ ] ASCII graph plotting
- [ ] Derivative calculator (symbolic)
- [ ] Integration (numerical methods)
- [ ] More unit conversions (time, data size, area)
- [ ] Export to CSV/JSON formats
- [ ] Scientific notation support
- [ ] Probability distributions

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
- [ ] Matrix eigenvalues and eigenvectors

### 💭 Community Wishlist

Have an idea? Suggested features:
- Calculus operations (derivatives, integrals)
- 3D matrix operations and transformations
- Financial calculations (NPV, IRR, compound interest)
- Physics formulas library
- Chemistry molecular calculations
- Linear programming solver
- Differential equation solver

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
- Maintain backward compatibility

**Recent Additions:**
- ✅ Reciprocal trigonometric functions (cosec, sec, cot)
- ✅ Prime number checker with factor analysis
- ✅ Matrix transpose operation
- ✅ Enhanced memory operations (M-)
- ✅ Logarithm with custom base
- ✅ Improved mode detection in statistics
- ✅ Complex number conjugate

### 📝 Documentation
- Fix typos or unclear explanations
- Add more usage examples
- Translate README to other languages
- Create video tutorials
- Write blog posts about features

### 🎨 Design
- Propose new color themes
- Improve ASCII art and borders
- Suggest UI layout improvements
- Create application icons

---

## 📜 License

This project is available for **educational and personal use**. Feel free to:
- ✅ Use for learning and personal projects
- ✅ Modify and experiment
- ✅ Share with attribution
- ✅ Fork and extend

Please:
- ❌ Don't claim as your own work
- ❌ Don't sell commercially without permission
- ✅ Credit the original author when sharing

---

## 👏 Acknowledgments

Built with:
- ❤️ Passion for mathematics
- 🧠 Problem-solving enthusiasm
- ⌨️ Lots of coffee and debugging
- 🎓 Computer science principles

**Special Thanks:**
- C++ Standard Library maintainers
- Open source community
- Mathematical pioneers whose algorithms power this tool
- Beta testers and users who provided feedback

**Inspiration:**
- Classic scientific calculators (TI, Casio)
- GNU Octave and MATLAB
- Wolfram Alpha
- Stack Overflow community

---

## 🌟 Star This Project!

If you found this calculator useful, please consider giving it a star ⭐

**Made with 🧮 for the love of mathematics**

[Report Bug](https://github.com) • [Request Feature](https://github.com) • [Ask Question](https://github.com)

---

## 📊 Project Statistics

- **Total Functions**: 52+ mathematical operations
- **Lines of Code**: ~1,900
- **Supported Operations**: Arithmetic, Trigonometry, Logarithms, Statistics, Matrices, Complex Numbers
- **Memory Features**: 5 operations (MS, MR, MC, M+, M-)
- **Conversion Types**: 15+ unit and number system conversions
- **Theme Options**: 3 color schemes

---

*"Mathematics is the language with which God has written the universe."* - Galileo Galilei

*"Pure mathematics is, in its way, the poetry of logical ideas."* - Albert Einstein

</div>