# 🏏 FAST-SCOREBOOK: Cricket Match Management System

[![Language](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://isocpp.org/)
[![Standard](https://img.shields.io/badge/C%2B%2B-11-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B11)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20MacOS-lightgrey.svg)](https://github.com/abdullahjvd384/FAST-SCOREBOOK)

> A comprehensive cricket match management and scoring system demonstrating advanced Object-Oriented Programming principles.

## 📋 Project Overview

FAST-SCOREBOOK is a professional-grade cricket match management system built from scratch using advanced OOP concepts. The system provides complete ball-by-ball recording, multi-user network synchronization, and an innovative conflict resolution mechanism for managing cricket matches of all formats.

### 🎯 Key Highlights

- **Complete OOP Implementation** - All 4 pillars + advanced concepts
- **Ball-by-Ball Recording** - Comprehensive tracking system
- **Multi-User Sync** - Network simulation with conflict resolution
- **Multiple Match Types** - Test, ODI, T20, First-Class
- **Professional Architecture** - Industry-standard design patterns

---

## ✨ Key Features

### 1. **Comprehensive OOP Design**
- **Inheritance**: Person base class with specialized derived classes (Player, Umpire, Commentator, etc.)
- **Polymorphism**: Virtual functions for match types, display methods
- **Encapsulation**: Private data members with controlled access via getters/setters
- **Abstraction**: Abstract base classes (Person, Match) with pure virtual functions

### 2. **Complete Entity Management**
- **People**: Players, Umpires, Commentators, Ground Staff, Support Staff, Supervisors
- **Teams**: Full squad management, playing XI selection, role assignments
- **Matches**: Support for Test, ODI, T20, First-Class, and other formats
- **Venues**: Stadium information, pitch types, facilities
- **Officials**: Umpire assignments, commentary teams
- **Broadcasters**: Multi-region broadcasting coverage

### 3. **Ball-by-Ball Recording**
- Detailed ball tracking with outcomes (runs, wickets, extras)
- Over management with maiden over detection
- Innings management with complete statistics
- Multiple ball outcome types (Dot, Single, Four, Six, Wide, No-ball, Wicket, etc.)
- All wicket types supported (Bowled, Caught, LBW, Run-out, Stumped, etc.)

### 4. **Multi-User Network Sync**
- Multiple scorers can record simultaneously
- Automatic conflict detection when entries disagree
- Supervisor-based conflict resolution
- Voting mechanism for majority consensus
- Complete audit trail with timestamps

### 5. **Statistics and Reporting**
- Player statistics (batting, bowling, fielding)
- Match summaries and scorecards
- Over-by-over analysis
- Run rate calculations
- Comprehensive match reports

## 📁 Project Structure

```
FAST-SCOREBOOK/
├── include/              - Header files
│   ├── Person.h         - Base class for all people
│   ├── Player.h         - Player class with roles and statistics
│   ├── Officials.h      - Umpire, Commentator, Supervisor classes
│   ├── Team.h          - Team management and squad handling
│   ├── Venue.h         - Venue and Broadcaster classes
│   ├── Ball.h          - Ball class with outcomes
│   ├── Innings.h       - Over and Innings classes
│   ├── Match.h         - Match hierarchy and Series
│   └── Scorebook.h     - Multi-user scorebook
├── src/                 - Source files
│   └── main.cpp        - Main program
├── docs/                - Documentation
│   ├── OOP_PRINCIPLES.md
│   ├── CLASS_DIAGRAM.md
│   ├── USAGE_EXAMPLES.md
│   ├── COMPILATION_GUIDE.md
│   ├── REQUIREMENTS_CHECKLIST.md
│   └── PROJECT_SUMMARY.md
├── build.bat           - Windows build script
├── run.bat             - Windows run script
├── Makefile            - Unix/Linux build system
├── .gitignore          - Git ignore file
└── README.md           - This file
```

## 🚀 Quick Start

### Windows Users

**Option 1: Using Build Script (Easiest)**
```bash
# Build the project
build.bat

# Run the program
run.bat
```

**Option 2: Manual Compilation**
```bash
g++ -std=c++11 -Wall -Iinclude -o bin\fast-scorebook.exe src\main.cpp
bin\fast-scorebook.exe
```

### Linux/Mac Users

**Using Makefile**
```bash
# Build the project
make

# Run the program
make run

# Clean build artifacts
make clean
```

**Manual Compilation**
```bash
g++ -std=c++11 -Wall -Iinclude -o bin/fast-scorebook src/main.cpp
./bin/fast-scorebook
```

## Class Hierarchy

### Person Hierarchy
```
Person (Abstract)
├── Player
├── SupportStaff
├── Umpire
├── Commentator
├── GroundStaff
└── Supervisor
```

### Match Hierarchy
```
Match (Abstract)
├── ODIMatch
├── T20Match
├── TestMatch
└── FirstClassMatch
```

## OOP Principles Demonstrated

### 1. Inheritance
- Person is the base class for all human entities
- Match is the base class for all match types
- Proper use of protected and private access specifiers

### 2. Polymorphism
- Virtual functions: `displayInfo()`, `displayMatchInfo()`, `checkInningsComplete()`
- Pure virtual functions making classes abstract
- Runtime polymorphism through base class pointers

### 3. Encapsulation
- All data members are private/protected
- Public getter/setter methods for controlled access
- Data hiding and validation in setters

### 4. Abstraction
- Abstract base classes (Person, Match)
- Interface-like design for conflict resolution
- Hiding complex implementation details

### 5. Composition
- Team HAS-A collection of Players
- Match HAS-A Venue, Teams, Umpires
- Innings HAS-A collection of Overs
- Over HAS-A collection of Balls

### 6. Association
- Player associated with Team
- Umpire associated with Match
- Bowler and Batsman in Ball recording

## Key Classes

### Person (Abstract Base Class)
- Attributes: name, age, nationality, id
- Pure virtual function: `displayInfo()`
- Base for all human entities

### Player
- Inherits from Person
- Attributes: jerseyNumber, roles, battingStyle, bowlingStyle, statistics
- Methods: Role management, statistics updates, display

### Team
- Manages squad and playing XI
- Captain and vice-captain assignment
- Support staff management
- Display methods

### Ball
- Records individual ball information
- Ball outcomes and wicket types
- Timestamp for conflict resolution
- Commentary support

### Innings
- Manages overs and balls
- Tracks batsmen and bowlers
- Calculates scores and wickets
- Run rate calculation

### Match (Abstract)
- Base class for all match types
- Pure virtual functions for match-specific rules
- Innings management
- Complete match summary

### Scorebook
- Multi-user entry management
- Conflict detection algorithm
- Supervisor-based resolution
- Voting mechanism
- Comprehensive statistics

## Compilation and Execution

### Compile:
```bash
g++ -std=c++11 main.cpp -o fast-scorebook
```

### Run:
```bash
./fast-scorebook
```

## 📖 Documentation

Comprehensive documentation is available in the `docs/` directory:

- **[OOP_PRINCIPLES.md](docs/OOP_PRINCIPLES.md)** - Detailed explanation of all OOP concepts used
- **[CLASS_DIAGRAM.md](docs/CLASS_DIAGRAM.md)** - Visual architecture and class diagrams
- **[USAGE_EXAMPLES.md](docs/USAGE_EXAMPLES.md)** - Code examples and test cases
- **[COMPILATION_GUIDE.md](docs/COMPILATION_GUIDE.md)** - Detailed compilation instructions
- **[REQUIREMENTS_CHECKLIST.md](docs/REQUIREMENTS_CHECKLIST.md)** - Project requirements verification
- **[PROJECT_SUMMARY.md](docs/PROJECT_SUMMARY.md)** - Executive project summary

## ✨ Features Demonstration

The main program demonstrates:

1. **Team Creation**: Two complete teams with 11 players each
2. **Match Setup**: ODI match with venue, officials, broadcasters
3. **Ball-by-Ball Recording**: Simulated match with actual ball tracking
4. **Conflict Scenarios**: Multiple users recording same balls differently
5. **Conflict Resolution**: Supervisor resolving disagreements
6. **Interactive Menu**: User can explore all features
7. **Complete Reports**: Scorecards, statistics, summaries

## Conflict Resolution System

### Conflict Detection
- Automatic detection when multiple users enter different data
- Ball-by-ball comparison
- Timestamp tracking

### Resolution Methods
1. **Supervisor Decision**: Authorized person makes final call
2. **Voting System**: Majority consensus among scorers
3. **Audit Trail**: Complete history maintained

## Network Sync Simulation

The system simulates multiple scorers by:
- Creating multiple ScoreEntry objects for same ball
- Different userIds representing different people
- Automatic conflict flagging
- Supervisor intervention for resolution

## Advanced Features

### 1. Match Types
- **Test Match**: Unlimited overs, 4 innings, declaration support
- **ODI**: 50 overs, powerplay rules
- **T20**: 20 overs, strategic timeouts
- **First-Class**: Multi-day format

### 2. Ball Outcomes
- Dot Ball, Singles, Doubles, Triples
- Boundaries (Four, Six)
- Extras (Wide, No-ball, Bye, Leg-bye)
- Wickets with detailed types

### 3. Statistics
- Player batting average, strike rate
- Bowling average, economy rate
- Team totals and run rates
- Over-by-over breakdown

## Future Enhancements

1. Database integration for persistent storage
2. Actual network implementation (sockets/web services)
3. Real-time score updates
4. Mobile app integration
5. Video replay integration
6. AI-based conflict resolution
7. Historical data analytics
8. Player ranking systems

## Design Patterns Used

1. **Template Method**: Match base class with specific implementations
2. **Strategy Pattern**: Different conflict resolution strategies
3. **Observer Pattern**: Scorebook observing multiple score entries
4. **Factory Pattern**: Could be added for Match creation

## Error Handling

- Input validation in setter methods
- Boundary checks for array access
- Null pointer checks before operations
- Exception handling framework ready

## Memory Management

Current implementation uses raw pointers. For production:
- Use `std::unique_ptr` and `std::shared_ptr`
- Implement RAII principles
- Proper destructor chains

## Testing Recommendations

1. **Unit Tests**: Test each class individually
2. **Integration Tests**: Test class interactions
3. **Conflict Tests**: Test various conflict scenarios
4. **Performance Tests**: Test with large number of balls
5. **Edge Cases**: Unusual match situations

## Contributing

To extend this system:
1. Follow the existing class hierarchy
2. Maintain OOP principles
3. Add proper documentation
4. Test thoroughly

## 🤝 Contributing

Contributions are welcome! To extend this system:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Follow the existing class hierarchy and OOP principles
4. Add proper documentation
5. Test thoroughly
6. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
7. Push to the branch (`git push origin feature/AmazingFeature`)
8. Open a Pull Request

## 👨‍💻 Author

**Abdullah Javed**
- GitHub: [@abdullahjvd384](https://github.com/abdullahjvd384)
- Project: [FAST-SCOREBOOK](https://github.com/abdullahjvd384/FAST-SCOREBOOK)

## 🙏 Acknowledgments

- Developed for Object-Oriented Programming Course Project
- Inspired by professional cricket scoring systems (Cricinfo, Cricbuzz)
- Demonstrates comprehensive understanding of:
  - Object-Oriented Programming
  - Software Design Principles
  - Cricket Domain Knowledge
  - System Architecture

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

Educational Project - Free to use, modify, and distribute.

---

## 📞 Contact & Support

If you have questions or need help:
- Open an [Issue](https://github.com/abdullahjvd384/FAST-SCOREBOOK/issues)
- Check the [Documentation](docs/)
- Review [Usage Examples](docs/USAGE_EXAMPLES.md)

---

<div align="center">

**⭐ Star this repository if you find it helpful! ⭐**

**FAST-SCOREBOOK** - Where Cricket Meets Code! 🏏

Made with ❤️ by [Abdullah Javed](https://github.com/abdullahjvd384)

</div>
