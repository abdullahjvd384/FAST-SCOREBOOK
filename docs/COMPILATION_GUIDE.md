# COMPILATION GUIDE - FAST-SCOREBOOK

## Prerequisites

You need a C++ compiler to compile this project. Here are the options:

### Option 1: MinGW (Recommended for Windows)

1. **Download MinGW**:
   - Go to: https://sourceforge.net/projects/mingw/
   - Or use MinGW-w64: https://www.mingw-w64.org/

2. **Install MinGW**:
   - Run the installer
   - Select "g++" during installation
   - Add MinGW bin folder to PATH (e.g., C:\MinGW\bin)

3. **Verify Installation**:
   ```bash
   g++ --version
   ```

### Option 2: Visual Studio (Microsoft)

1. **Download Visual Studio**:
   - Go to: https://visualstudio.microsoft.com/
   - Download Community Edition (Free)

2. **Install C++ Development Tools**:
   - During installation, select "Desktop development with C++"
   - This includes MSVC compiler

3. **Use Developer Command Prompt**:
   - Open "Developer Command Prompt for VS"
   - Navigate to project folder
   - Use `cl` instead of `g++`

### Option 3: Online Compiler (Quick Test)

Use online C++ compilers:
- https://www.onlinegdb.com/
- https://www.programiz.com/cpp-programming/online-compiler/
- https://replit.com/

## Compilation Instructions

### Using g++ (MinGW/Linux/Mac):

```bash
# Navigate to project directory
cd "c:\Users\Asadullah Javed\OneDrive\Desktop\OOP-proj"

# Compile with C++11 standard
g++ -std=c++11 main.cpp -o fast-scorebook.exe

# Run the program
./fast-scorebook.exe
```

### Using MSVC (Visual Studio):

```bash
# Open Developer Command Prompt for VS
cd "c:\Users\Asadullah Javed\OneDrive\Desktop\OOP-proj"

# Compile
cl /EHsc main.cpp /Fe:fast-scorebook.exe

# Run
fast-scorebook.exe
```

### Using Code::Blocks IDE:

1. Open Code::Blocks
2. Create new project (Console Application)
3. Add all .h files and main.cpp to project
4. Build and Run (F9)

### Using Visual Studio Code:

1. Install C/C++ extension
2. Install a compiler (MinGW or MSVC)
3. Configure tasks.json:
```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Build FAST-SCOREBOOK",
            "type": "shell",
            "command": "g++",
            "args": [
                "-std=c++11",
                "main.cpp",
                "-o",
                "fast-scorebook.exe"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
```
4. Press Ctrl+Shift+B to build

## Compilation Flags Explained

- `-std=c++11`: Use C++11 standard (required for some features)
- `-o fast-scorebook.exe`: Output file name
- `-Wall`: Show all warnings (optional, recommended)
- `-O2`: Optimization level 2 (optional)

## Full Command with All Options:

```bash
g++ -std=c++11 -Wall -O2 main.cpp -o fast-scorebook.exe
```

## Troubleshooting

### Error: "g++ is not recognized"
- Solution: Install MinGW and add to PATH
- Or use Visual Studio's cl compiler

### Error: "No such file or directory"
- Solution: Make sure you're in the correct directory
- Use `dir` (Windows) or `ls` (Linux/Mac) to list files

### Error: Header file not found
- Solution: All .h files must be in the same directory as main.cpp

### Linker Errors
- Solution: Make sure all header files are included correctly
- Check for circular dependencies

## Running the Program

After successful compilation:

### Windows:
```bash
fast-scorebook.exe
```

### Linux/Mac:
```bash
./fast-scorebook
```

## Alternative: Single Header File Compilation

If you face issues with multiple header files, you can create a single-file version:

1. Copy all class definitions into main.cpp (before main function)
2. Remove `#include` directives for custom headers
3. Compile: `g++ -std=c++11 main.cpp -o fast-scorebook.exe`

## IDE Recommendations

1. **Visual Studio Code** (Lightweight, cross-platform)
2. **Code::Blocks** (Easy for beginners)
3. **Visual Studio** (Full-featured, Windows)
4. **CLion** (Professional, paid)
5. **Dev-C++** (Simple, Windows)

## Quick Test Without Compilation

Copy the code to an online compiler:
1. Go to https://www.onlinegdb.com/
2. Select C++ language
3. Paste the code (combine all headers in main.cpp)
4. Click "Run"

## File Structure Check

Make sure your directory has these files:
```
OOP-proj/
├── Person.h
├── Player.h
├── Officials.h
├── Team.h
├── Venue.h
├── Ball.h
├── Innings.h
├── Match.h
├── Scorebook.h
├── main.cpp
├── README.md
└── COMPILATION_GUIDE.md
```

Verify using:
```bash
dir  # Windows
ls   # Linux/Mac
```

## Expected Output

When you run the program successfully, you should see:
- Welcome message
- Match information
- Team details with all players
- Venue information
- Officials and broadcasters
- Ball-by-ball commentary
- Conflict detection messages
- Conflict resolution demonstration
- Interactive menu

## Performance Notes

- The program should compile in < 5 seconds
- Run time is nearly instant
- Memory usage is minimal (<10MB)

## Need Help?

If you continue to face issues:
1. Check if C++ compiler is installed: `g++ --version`
2. Verify file permissions
3. Try online compiler for quick test
4. Check for syntax errors in code

---

**Happy Coding! 🏏**
