# USAGE EXAMPLES AND TEST CASES

## How to Use FAST-SCOREBOOK Components

---

## 1. CREATING PLAYERS

### Example 1: Basic Player Creation
```cpp
// Create a batsman
Player* player1 = new Player("Babar Azam", 29, "Pakistan", "PAK001", 56);
player1->setBattingStyle("Right-handed");
player1->addRole(PlayerRole::BATSMAN);
player1->addRole(PlayerRole::CAPTAIN);

// Display player info
player1->displayInfo();
```

**Output:**
```
Player: Babar Azam (#56)
Age: 29 | Nationality: Pakistan
Batting Style: Right-handed
Roles: Batsman Captain
```

### Example 2: All-rounder with Bowling
```cpp
Player* allrounder = new Player("Hardik Pandya", 30, "India", "IND007", 33);
allrounder->setBattingStyle("Right-handed");
allrounder->setBowlingStyle("Right-arm Medium-fast");
allrounder->addRole(PlayerRole::ALLROUNDER);
allrounder->displayInfo();
```

---

## 2. CREATING AND MANAGING TEAMS

### Example: Complete Team Setup
```cpp
// Create team
Team* pakistan = new Team("Pakistan", "Pakistan");
pakistan->setWorldRanking(4);

// Add players to squad
Player* babar = new Player("Babar Azam", 29, "Pakistan", "PAK001", 56);
Player* rizwan = new Player("Mohammad Rizwan", 31, "Pakistan", "PAK002", 7);
Player* shaheen = new Player("Shaheen Afridi", 24, "Pakistan", "PAK003", 10);

pakistan->addPlayer(babar);
pakistan->addPlayer(rizwan);
pakistan->addPlayer(shaheen);

// Select playing XI
pakistan->addToPlayingXI(babar);
pakistan->addToPlayingXI(rizwan);
pakistan->addToPlayingXI(shaheen);

// Set captain
pakistan->setCaptain(babar);

// Add support staff
SupportStaff* coach = new SupportStaff("Misbah", 49, "Pakistan", "ST001", "Coach");
pakistan->addSupportStaff(coach);

// Display team
pakistan->displayTeam();
```

---

## 3. CREATING MATCH OFFICIALS

### Example: Setting up Officials
```cpp
// Create umpires
Umpire* umpire1 = new Umpire("Aleem Dar", 55, "Pakistan", "UMP001", "On-field");
Umpire* umpire2 = new Umpire("Richard Kettleborough", 51, "England", "UMP002", "On-field");
Umpire* thirdUmp = new Umpire("Joel Wilson", 47, "West Indies", "UMP003", "Third Umpire");

// Create commentators
Commentator* comm1 = new Commentator("Rameez Raja", 61, "Pakistan", 
                                     "COM001", "Urdu", "TV");
Commentator* comm2 = new Commentator("Harsha Bhogle", 62, "India", 
                                     "COM002", "English", "TV");

// Display
umpire1->displayInfo();
comm1->displayInfo();
```

---

## 4. CREATING VENUES

### Example: Venue Setup
```cpp
Venue* venue = new Venue("National Stadium", "Karachi", "Pakistan", 34228);
venue->setPitchType("Batting-friendly");
venue->setFloodlights(true);
venue->displayVenueInfo();
```

**Output:**
```
===== Venue Information =====
Stadium: National Stadium
Location: Karachi, Pakistan
Capacity: 34228
Pitch Type: Batting-friendly
Floodlights: Yes
```

---

## 5. CREATING DIFFERENT MATCH TYPES

### Example 1: ODI Match
```cpp
ODIMatch* odiMatch = new ODIMatch("PAK_IND_001", team1, team2, venue);
odiMatch->setToss("Pakistan", "bat");
odiMatch->addUmpire(umpire1);
odiMatch->addUmpire(umpire2);
odiMatch->displayMatchInfo();
```

### Example 2: T20 Match
```cpp
T20Match* t20Match = new T20Match("PAK_IND_T20_001", team1, team2, venue);
t20Match->setToss("India", "bowl");
t20Match->displayMatchInfo();
```

### Example 3: Test Match
```cpp
TestMatch* testMatch = new TestMatch("PAK_IND_TEST_001", team1, team2, venue);
testMatch->setToss("Pakistan", "bat");
testMatch->displayMatchInfo();
```

---

## 6. RECORDING BALLS

### Example 1: Dot Ball
```cpp
Player* bowler = team2->getPlayingXI()[2];  // Get bowler
Player* batsman = team1->getPlayingXI()[0]; // Get batsman
Player* nonStriker = team1->getPlayingXI()[1];

Ball* ball1 = new Ball(1, 1, bowler, batsman, nonStriker);
ball1->recordBall(BallOutcome::DOT_BALL, 0);
ball1->setCommentary("Good length delivery, defended");
ball1->displayBall();
```

**Output:**
```
1.1 - Jasprit Bumrah to Babar Azam: Dot Ball - Good length delivery, defended
```

### Example 2: Boundary
```cpp
Ball* ball2 = new Ball(1, 2, bowler, batsman, nonStriker);
ball2->recordBall(BallOutcome::FOUR, 4);
ball2->setCommentary("Brilliant cover drive!");
ball2->displayBall();
```

**Output:**
```
1.2 - Jasprit Bumrah to Babar Azam: FOUR! (4 runs) - Brilliant cover drive!
```

### Example 3: Wicket
```cpp
Ball* ball3 = new Ball(1, 3, bowler, batsman, nonStriker);
ball3->recordBall(BallOutcome::WICKET, 0);
ball3->recordWicket(WicketType::BOWLED);
ball3->setCommentary("Cleaned him up!");
ball3->displayBall();
```

**Output:**
```
1.3 - Jasprit Bumrah to Babar Azam: WICKET! Babar Azam Bowled b Jasprit Bumrah
```

### Example 4: Wide Ball
```cpp
Ball* ball4 = new Ball(1, 4, bowler, batsman, nonStriker);
ball4->recordBall(BallOutcome::WIDE, 0, 1);
ball4->setCommentary("Down the leg side");
ball4->displayBall();
```

---

## 7. MANAGING INNINGS

### Example: Complete Over
```cpp
Innings* innings1 = match->startNewInnings(team1, team2);
innings1->setBatsmen(batsman1, batsman2);

// Start over
Player* bowler = team2->getPlayingXI()[2];
innings1->startOver(bowler);

// Record 6 balls
for(int i = 1; i <= 6; i++) {
    Ball* ball = new Ball(1, i, bowler, 
                         innings1->getStriker(), 
                         innings1->getNonStriker());
    
    // Simulate different outcomes
    if(i == 1) ball->recordBall(BallOutcome::DOT_BALL, 0);
    else if(i == 2) ball->recordBall(BallOutcome::SINGLE, 1);
    else if(i == 3) ball->recordBall(BallOutcome::FOUR, 4);
    else if(i == 4) ball->recordBall(BallOutcome::DOUBLE, 2);
    else if(i == 5) ball->recordBall(BallOutcome::SIX, 6);
    else ball->recordBall(BallOutcome::DOT_BALL, 0);
    
    innings1->recordBall(ball);
    ball->displayBall();
}

// Display innings score
innings1->displayInningsScore();
```

---

## 8. MULTI-USER SCORE ENTRY

### Example: Multiple Users Recording Same Ball
```cpp
// Three users recording ball 1.1
ScoreEntry entry1("user1", "Ali", 1, 1, BallOutcome::DOT_BALL, 0, 0, WicketType::NONE);
ScoreEntry entry2("user2", "Ahmed", 1, 1, BallOutcome::DOT_BALL, 0, 0, WicketType::NONE);
ScoreEntry entry3("user3", "Zain", 1, 1, BallOutcome::DOT_BALL, 0, 0, WicketType::NONE);

scorebook->addScoreEntry(entry1);
scorebook->addScoreEntry(entry2);
scorebook->addScoreEntry(entry3);

// No conflict - all agree!
```

---

## 9. CONFLICT DETECTION

### Example: Creating a Conflict
```cpp
// Ball 1.2 - Users disagree!
ScoreEntry entry1("user1", "Ali", 1, 2, BallOutcome::FOUR, 4, 0, WicketType::NONE);
ScoreEntry entry2("user2", "Ahmed", 1, 2, BallOutcome::SINGLE, 1, 0, WicketType::NONE);
ScoreEntry entry3("user3", "Zain", 1, 2, BallOutcome::FOUR, 4, 0, WicketType::NONE);

scorebook->addScoreEntry(entry1);
scorebook->addScoreEntry(entry2);  // This creates a conflict!
scorebook->addScoreEntry(entry3);
```

**Output:**
```
!!! CONFLICT DETECTED for ball 1.2 !!!
```

---

## 10. CONFLICT RESOLUTION

### Example 1: Supervisor Resolution
```cpp
// Display unresolved conflicts
scorebook->displayUnresolvedConflicts();

// Supervisor resolves
Supervisor* supervisor = new Supervisor("Nadeem", 45, "Pakistan", "SUP001", "nadeem");
ScoreEntry correctEntry("supervisor", "Nadeem", 1, 2, 
                       BallOutcome::FOUR, 4, 0, WicketType::NONE);

bool resolved = scorebook->resolveConflict(1, 2, correctEntry);

if(resolved) {
    cout << "✓ Conflict resolved successfully!" << endl;
}
```

### Example 2: Voting Resolution
```cpp
// Let majority decide
ScoreEntry votedEntry = scorebook->resolveByVoting(1, 2);
scorebook->resolveConflict(1, 2, votedEntry);
```

---

## 11. DISPLAYING STATISTICS

### Example: Player Statistics
```cpp
Player* player = team->findPlayerByName("Babar Azam");

// Update batting stats
player->updateBattingStats(45, 52, 4, 1);  // 45 runs, 52 balls, 4 fours, 1 six

// Display stats
const PlayerStats& stats = player->getStats();
cout << "Runs: " << stats.runsScored << endl;
cout << "Strike Rate: " << stats.strikeRate << endl;
```

### Example: Match Summary
```cpp
match->displayMatchSummary();
```

**Output:**
```
========================================
       MATCH SUMMARY
========================================
Match ID: PAK_IND_ODI_001
Type: One Day International
Venue: National Stadium, Karachi
Status: In Progress

Toss: Pakistan won and chose to bat

--- SCORECARD ---
===== Innings 1 =====
Pakistan: 145/3 (25 overs)
Extras: 8 (wd 3, nb 2, b 2, lb 1)
========================================
```

---

## 12. CREATING A SERIES

### Example: Bilateral Series
```cpp
Series* series = new Series("Pakistan vs India 2025", "Bilateral");
series->addTeam(pakistan);
series->addTeam(india);

// Add multiple matches
series->addMatch(odiMatch1);
series->addMatch(odiMatch2);
series->addMatch(odiMatch3);

series->displaySeriesInfo();
```

---

## 13. TEST CASES

### Test Case 1: Player Creation and Roles
```cpp
void testPlayerCreation() {
    Player* player = new Player("Test Player", 25, "Country", "ID001", 10);
    
    // Test role addition
    player->addRole(PlayerRole::BATSMAN);
    player->addRole(PlayerRole::CAPTAIN);
    
    // Verify
    assert(player->hasRole(PlayerRole::BATSMAN) == true);
    assert(player->hasRole(PlayerRole::CAPTAIN) == true);
    assert(player->isCaptain() == true);
    assert(player->hasRole(PlayerRole::BOWLER) == false);
    
    cout << "✓ Player Creation Test Passed" << endl;
    delete player;
}
```

### Test Case 2: Ball Recording
```cpp
void testBallRecording() {
    Player* bowler = new Player("Bowler", 25, "Country", "ID001", 1);
    Player* batsman = new Player("Batsman", 26, "Country", "ID002", 2);
    Player* nonStriker = new Player("NonStriker", 27, "Country", "ID003", 3);
    
    Ball* ball = new Ball(1, 1, bowler, batsman, nonStriker);
    ball->recordBall(BallOutcome::FOUR, 4);
    
    // Verify
    assert(ball->getOverNumber() == 1);
    assert(ball->getBallNumber() == 1);
    assert(ball->getRuns() == 4);
    assert(ball->getOutcome() == BallOutcome::FOUR);
    assert(ball->getIsValid() == true);
    
    cout << "✓ Ball Recording Test Passed" << endl;
    
    delete ball;
    delete bowler;
    delete batsman;
    delete nonStriker;
}
```

### Test Case 3: Innings Score Calculation
```cpp
void testInningsScoring() {
    Team* team1 = new Team("Team1", "Country1");
    Team* team2 = new Team("Team2", "Country2");
    Innings* innings = new Innings(1, team1, team2);
    
    // Add players
    Player* bat1 = new Player("Bat1", 25, "C1", "ID1", 1);
    Player* bat2 = new Player("Bat2", 26, "C1", "ID2", 2);
    Player* bowl = new Player("Bowl", 27, "C2", "ID3", 3);
    
    team1->addPlayer(bat1);
    team1->addPlayer(bat2);
    team2->addPlayer(bowl);
    
    innings->setBatsmen(bat1, bat2);
    innings->startOver(bowl);
    
    // Record balls
    Ball* ball1 = new Ball(1, 1, bowl, bat1, bat2);
    ball1->recordBall(BallOutcome::FOUR, 4);
    innings->recordBall(ball1);
    
    Ball* ball2 = new Ball(1, 2, bowl, bat1, bat2);
    ball2->recordBall(BallOutcome::SIX, 6);
    innings->recordBall(ball2);
    
    // Verify
    assert(innings->getTotalRuns() == 10);
    assert(innings->getTotalWickets() == 0);
    
    cout << "✓ Innings Scoring Test Passed" << endl;
    
    delete innings;
    delete team1;
    delete team2;
}
```

### Test Case 4: Conflict Detection
```cpp
void testConflictDetection() {
    Team* t1 = new Team("T1", "C1");
    Team* t2 = new Team("T2", "C2");
    Venue* v = new Venue("Stadium", "City", "Country", 50000);
    ODIMatch* match = new ODIMatch("M001", t1, t2, v);
    Supervisor* sup = new Supervisor("Sup", 40, "C", "S1", "sup");
    
    Scorebook* scorebook = new Scorebook(match, sup);
    
    // Same ball, different entries
    ScoreEntry e1("u1", "User1", 1, 1, BallOutcome::FOUR, 4, 0, WicketType::NONE);
    ScoreEntry e2("u2", "User2", 1, 1, BallOutcome::SINGLE, 1, 0, WicketType::NONE);
    
    scorebook->addScoreEntry(e1);
    scorebook->addScoreEntry(e2);
    
    // Verify conflict detected
    assert(scorebook->getTotalConflicts() == 1);
    assert(scorebook->hasUnresolvedConflicts() == true);
    
    cout << "✓ Conflict Detection Test Passed" << endl;
    
    delete scorebook;
    delete match;
    delete t1;
    delete t2;
    delete v;
    delete sup;
}
```

### Test Case 5: Polymorphism Test
```cpp
void testPolymorphism() {
    Team* t1 = new Team("T1", "C1");
    Team* t2 = new Team("T2", "C2");
    Venue* v = new Venue("Stadium", "City", "Country", 50000);
    
    // Base class pointers
    Match* odiMatch = new ODIMatch("M001", t1, t2, v);
    Match* t20Match = new T20Match("M002", t1, t2, v);
    Match* testMatch = new TestMatch("M003", t1, t2, v);
    
    // Polymorphic calls
    odiMatch->displayMatchInfo();   // Calls ODI version
    t20Match->displayMatchInfo();   // Calls T20 version
    testMatch->displayMatchInfo();  // Calls Test version
    
    // Verify max overs
    assert(odiMatch->getMaxOversPerInnings() == 50);
    assert(t20Match->getMaxOversPerInnings() == 20);
    assert(testMatch->getMaxOversPerInnings() == 999);
    
    cout << "✓ Polymorphism Test Passed" << endl;
    
    delete odiMatch;
    delete t20Match;
    delete testMatch;
    delete t1;
    delete t2;
    delete v;
}
```

---

## 14. RUNNING ALL TESTS

```cpp
void runAllTests() {
    cout << "\n========== RUNNING TESTS ==========" << endl;
    
    testPlayerCreation();
    testBallRecording();
    testInningsScoring();
    testConflictDetection();
    testPolymorphism();
    
    cout << "\n✓ ALL TESTS PASSED!" << endl;
    cout << "===================================" << endl;
}

int main() {
    runAllTests();
    return 0;
}
```

---

## 15. COMMON USAGE PATTERNS

### Pattern 1: Creating a Complete Match
```cpp
// 1. Create venue
Venue* venue = new Venue(...);

// 2. Create teams
Team* team1 = new Team(...);
Team* team2 = new Team(...);

// 3. Add players to teams
// ... add players

// 4. Create match
ODIMatch* match = new ODIMatch(...);

// 5. Add officials
match->addUmpire(...);
match->addCommentator(...);

// 6. Create scorebook
Scorebook* scorebook = new Scorebook(match, supervisor);

// 7. Start match
Innings* innings = match->startNewInnings(team1, team2);

// 8. Record balls
// ... record each ball
```

### Pattern 2: Handling Score Updates
```cpp
// For each ball:
1. Create Ball object
2. Record outcome
3. Add to over/innings
4. Create ScoreEntry for each user
5. Check for conflicts
6. Resolve if needed
```

---

**These examples demonstrate all major features of the system!** 🎯
