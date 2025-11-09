/*
 * FAST-SCOREBOOK: Cricket Match Scoring and Management System
 * 
 * This system implements a comprehensive cricket scorebook with:
 * - Complete OOP design with inheritance, polymorphism, encapsulation
 * - Ball-by-ball recording for all match types
 * - Multi-user network sync with conflict resolution
 * - Support for all cricket formats (Test, ODI, T20, First-Class, etc.)
 * - Complete entity management (Players, Teams, Officials, Venues, etc.)
 */

#include <iostream>
#include <iomanip>
#include "../include/Person.h"
#include "../include/Player.h"
#include "../include/Officials.h"
#include "../include/Team.h"
#include "../include/Venue.h"
#include "../include/Ball.h"
#include "../include/Innings.h"
#include "../include/Match.h"
#include "../include/Scorebook.h"

using namespace std;

// Helper function to display menu
void displayMenu() {
    cout << "\n========================================" << endl;
    cout << "    FAST-SCOREBOOK MAIN MENU" << endl;
    cout << "========================================" << endl;
    cout << "1. Display Match Information" << endl;
    cout << "2. Display Teams" << endl;
    cout << "3. Display Venue Information" << endl;
    cout << "4. View Current Score" << endl;
    cout << "5. View Full Scorecard" << endl;
    cout << "6. View Scorebook Summary" << endl;
    cout << "7. View Conflicts" << endl;
    cout << "8. Display Match Officials" << endl;
    cout << "9. Display Broadcasters" << endl;
    cout << "0. Exit" << endl;
    cout << "========================================" << endl;
    cout << "Enter choice: ";
}

// Function to create sample teams
void createTeamsWithPlayers(Team*& pakistan, Team*& india) {
    // Create Pakistan Team
    pakistan = new Team("Pakistan", "Pakistan");
    pakistan->setWorldRanking(4);
    pakistan->setTeamColor("Green");
    
    // Create Pakistan Players
    Player* babar = new Player("Babar Azam", 29, "Pakistan", "PAK001", 56);
    babar->setBattingStyle("Right-handed");
    babar->addRole(PlayerRole::BATSMAN);
    babar->addRole(PlayerRole::CAPTAIN);
    pakistan->addPlayer(babar);
    pakistan->addToPlayingXI(babar);
    pakistan->setCaptain(babar);
    
    Player* rizwan = new Player("Mohammad Rizwan", 31, "Pakistan", "PAK002", 7);
    rizwan->setBattingStyle("Right-handed");
    rizwan->addRole(PlayerRole::WICKETKEEPER_BATSMAN);
    pakistan->addPlayer(rizwan);
    pakistan->addToPlayingXI(rizwan);
    
    Player* shaheen = new Player("Shaheen Afridi", 24, "Pakistan", "PAK003", 10);
    shaheen->setBattingStyle("Left-handed");
    shaheen->setBowlingStyle("Left-arm Fast");
    shaheen->addRole(PlayerRole::BOWLER);
    pakistan->addPlayer(shaheen);
    pakistan->addToPlayingXI(shaheen);
    
    Player* fakhar = new Player("Fakhar Zaman", 33, "Pakistan", "PAK004", 9);
    fakhar->setBattingStyle("Left-handed");
    fakhar->addRole(PlayerRole::BATSMAN);
    pakistan->addPlayer(fakhar);
    pakistan->addToPlayingXI(fakhar);
    
    Player* shadab = new Player("Shadab Khan", 25, "Pakistan", "PAK005", 4);
    shadab->setBattingStyle("Right-handed");
    shadab->setBowlingStyle("Leg-spin");
    shadab->addRole(PlayerRole::ALLROUNDER);
    pakistan->addPlayer(shadab);
    pakistan->addToPlayingXI(shadab);
    
    Player* haris = new Player("Haris Rauf", 30, "Pakistan", "PAK006", 14);
    haris->setBowlingStyle("Right-arm Fast");
    haris->addRole(PlayerRole::BOWLER);
    pakistan->addPlayer(haris);
    pakistan->addToPlayingXI(haris);
    
    Player* iftikhar = new Player("Iftikhar Ahmed", 33, "Pakistan", "PAK007", 27);
    iftikhar->setBattingStyle("Right-handed");
    iftikhar->setBowlingStyle("Off-spin");
    iftikhar->addRole(PlayerRole::ALLROUNDER);
    pakistan->addPlayer(iftikhar);
    pakistan->addToPlayingXI(iftikhar);
    
    Player* nawaz = new Player("Mohammad Nawaz", 29, "Pakistan", "PAK008", 18);
    nawaz->setBattingStyle("Left-handed");
    nawaz->setBowlingStyle("Left-arm Orthodox");
    nawaz->addRole(PlayerRole::ALLROUNDER);
    pakistan->addPlayer(nawaz);
    pakistan->addToPlayingXI(nawaz);
    
    Player* imam = new Player("Imam-ul-Haq", 28, "Pakistan", "PAK009", 12);
    imam->setBattingStyle("Left-handed");
    imam->addRole(PlayerRole::BATSMAN);
    pakistan->addPlayer(imam);
    pakistan->addToPlayingXI(imam);
    
    Player* naseem = new Player("Naseem Shah", 21, "Pakistan", "PAK010", 3);
    naseem->setBowlingStyle("Right-arm Fast");
    naseem->addRole(PlayerRole::BOWLER);
    pakistan->addPlayer(naseem);
    pakistan->addToPlayingXI(naseem);
    
    Player* usama = new Player("Usama Mir", 28, "Pakistan", "PAK011", 21);
    usama->setBowlingStyle("Leg-spin");
    usama->addRole(PlayerRole::BOWLER);
    pakistan->addPlayer(usama);
    pakistan->addToPlayingXI(usama);
    
    // Add support staff
    SupportStaff* coach1 = new SupportStaff("Misbah-ul-Haq", 49, "Pakistan", "STAFF001", "Head Coach");
    pakistan->addSupportStaff(coach1);
    
    // Create India Team
    india = new Team("India", "India");
    india->setWorldRanking(1);
    india->setTeamColor("Blue");
    
    // Create India Players
    Player* rohit = new Player("Rohit Sharma", 36, "India", "IND001", 45);
    rohit->setBattingStyle("Right-handed");
    rohit->addRole(PlayerRole::BATSMAN);
    rohit->addRole(PlayerRole::CAPTAIN);
    india->addPlayer(rohit);
    india->addToPlayingXI(rohit);
    india->setCaptain(rohit);
    
    Player* virat = new Player("Virat Kohli", 35, "India", "IND002", 18);
    virat->setBattingStyle("Right-handed");
    virat->addRole(PlayerRole::BATSMAN);
    india->addPlayer(virat);
    india->addToPlayingXI(virat);
    
    Player* bumrah = new Player("Jasprit Bumrah", 30, "India", "IND003", 93);
    bumrah->setBattingStyle("Right-handed");
    bumrah->setBowlingStyle("Right-arm Fast");
    bumrah->addRole(PlayerRole::BOWLER);
    india->addPlayer(bumrah);
    india->addToPlayingXI(bumrah);
    
    Player* gill = new Player("Shubman Gill", 24, "India", "IND004", 77);
    gill->setBattingStyle("Right-handed");
    gill->addRole(PlayerRole::BATSMAN);
    india->addPlayer(gill);
    india->addToPlayingXI(gill);
    
    Player* pant = new Player("Rishabh Pant", 26, "India", "IND005", 17);
    pant->setBattingStyle("Left-handed");
    pant->addRole(PlayerRole::WICKETKEEPER_BATSMAN);
    india->addPlayer(pant);
    india->addToPlayingXI(pant);
    
    Player* jadeja = new Player("Ravindra Jadeja", 35, "India", "IND006", 8);
    jadeja->setBattingStyle("Left-handed");
    jadeja->setBowlingStyle("Left-arm Orthodox");
    jadeja->addRole(PlayerRole::ALLROUNDER);
    india->addPlayer(jadeja);
    india->addToPlayingXI(jadeja);
    
    Player* hardik = new Player("Hardik Pandya", 30, "India", "IND007", 33);
    hardik->setBattingStyle("Right-handed");
    hardik->setBowlingStyle("Right-arm Medium-fast");
    hardik->addRole(PlayerRole::ALLROUNDER);
    india->addPlayer(hardik);
    india->addToPlayingXI(hardik);
    
    Player* kuldeep = new Player("Kuldeep Yadav", 29, "India", "IND008", 23);
    kuldeep->setBattingStyle("Left-handed");
    kuldeep->setBowlingStyle("Left-arm Wrist-spin");
    kuldeep->addRole(PlayerRole::BOWLER);
    india->addPlayer(kuldeep);
    india->addToPlayingXI(kuldeep);
    
    Player* shami = new Player("Mohammed Shami", 33, "India", "IND009", 11);
    shami->setBowlingStyle("Right-arm Fast");
    shami->addRole(PlayerRole::BOWLER);
    india->addPlayer(shami);
    india->addToPlayingXI(shami);
    
    Player* siraj = new Player("Mohammed Siraj", 30, "India", "IND010", 13);
    siraj->setBowlingStyle("Right-arm Fast");
    siraj->addRole(PlayerRole::BOWLER);
    india->addPlayer(siraj);
    india->addToPlayingXI(siraj);
    
    Player* iyer = new Player("Shreyas Iyer", 29, "India", "IND011", 41);
    iyer->setBattingStyle("Right-handed");
    iyer->addRole(PlayerRole::BATSMAN);
    india->addPlayer(iyer);
    india->addToPlayingXI(iyer);
    
    // Add support staff
    SupportStaff* coach2 = new SupportStaff("Rahul Dravid", 51, "India", "STAFF002", "Head Coach");
    india->addSupportStaff(coach2);
}

// Function to simulate a match with ball-by-ball recording
void simulateMatch(Match* match, Scorebook* scorebook) {
    cout << "\n========================================" << endl;
    cout << "  STARTING MATCH SIMULATION" << endl;
    cout << "========================================" << endl;
    
    Team* team1 = match->getTeam1();
    Team* team2 = match->getTeam2();
    
    // Set toss
    match->setToss(team1->getTeamName(), "bat");
    cout << "\nToss: " << team1->getTeamName() << " won and elected to bat first." << endl;
    
    // Start First Innings
    cout << "\n--- FIRST INNINGS BEGINS ---" << endl;
    Innings* innings1 = match->startNewInnings(team1, team2);
    
    // Get opening batsmen
    Player* batsman1 = team1->getPlayingXI()[0]; // Babar Azam
    Player* batsman2 = team1->getPlayingXI()[3]; // Fakhar Zaman
    innings1->setBatsmen(batsman1, batsman2);
    
    // Get opening bowler
    Player* bowler1 = team2->getPlayingXI()[2]; // Bumrah
    
    cout << "\nOpening: " << batsman1->getName() << " and " << batsman2->getName() << endl;
    cout << "Opening Bowler: " << bowler1->getName() << endl;
    
    // Start first over
    innings1->startOver(bowler1);
    
    // Simulate balls with multiple users recording (showing conflict resolution)
    
    // Ball 1.1
    Ball* ball1 = new Ball(1, 1, bowler1, innings1->getStriker(), innings1->getNonStriker());
    ball1->recordBall(BallOutcome::DOT_BALL, 0);
    ball1->setCommentary("Good length delivery, defended back to the bowler");
    innings1->recordBall(ball1);
    
    // Simulate multiple users recording this ball
    ScoreEntry entry1a("user1", "Scorer Ali", 1, 1, BallOutcome::DOT_BALL, 0, 0, WicketType::NONE);
    ScoreEntry entry1b("user2", "Scorer Ahmed", 1, 1, BallOutcome::DOT_BALL, 0, 0, WicketType::NONE);
    ScoreEntry entry1c("user3", "Scorer Zain", 1, 1, BallOutcome::DOT_BALL, 0, 0, WicketType::NONE);
    scorebook->addScoreEntry(entry1a);
    scorebook->addScoreEntry(entry1b);
    scorebook->addScoreEntry(entry1c);
    
    ball1->displayBall();
    
    // Ball 1.2 - CONFLICT SCENARIO
    Ball* ball2 = new Ball(1, 2, bowler1, innings1->getStriker(), innings1->getNonStriker());
    ball2->recordBall(BallOutcome::FOUR, 4);
    ball2->setCommentary("Brilliant cover drive! Races away to the boundary");
    innings1->recordBall(ball2);
    
    // Users disagree on this ball!
    ScoreEntry entry2a("user1", "Scorer Ali", 1, 2, BallOutcome::FOUR, 4, 0, WicketType::NONE);
    ScoreEntry entry2b("user2", "Scorer Ahmed", 1, 2, BallOutcome::SINGLE, 1, 0, WicketType::NONE); // Wrong!
    ScoreEntry entry2c("user3", "Scorer Zain", 1, 2, BallOutcome::FOUR, 4, 0, WicketType::NONE);
    scorebook->addScoreEntry(entry2a);
    scorebook->addScoreEntry(entry2b); // This creates a conflict!
    scorebook->addScoreEntry(entry2c);
    
    ball2->displayBall();
    
    // Ball 1.3
    Ball* ball3 = new Ball(1, 3, bowler1, innings1->getStriker(), innings1->getNonStriker());
    ball3->recordBall(BallOutcome::SINGLE, 1);
    ball3->setCommentary("Pushed to mid-off for a quick single");
    innings1->recordBall(ball3);
    
    ScoreEntry entry3("user1", "Scorer Ali", 1, 3, BallOutcome::SINGLE, 1, 0, WicketType::NONE);
    scorebook->addScoreEntry(entry3);
    ball3->displayBall();
    
    // Ball 1.4 - ANOTHER CONFLICT
    Ball* ball4 = new Ball(1, 4, bowler1, innings1->getStriker(), innings1->getNonStriker());
    ball4->recordBall(BallOutcome::DOUBLE, 2);
    ball4->setCommentary("Nicely placed through the gap");
    innings1->recordBall(ball4);
    
    // Another disagreement
    ScoreEntry entry4a("user1", "Scorer Ali", 1, 4, BallOutcome::DOUBLE, 2, 0, WicketType::NONE);
    ScoreEntry entry4b("user2", "Scorer Ahmed", 1, 4, BallOutcome::TRIPLE, 3, 0, WicketType::NONE); // Wrong!
    ScoreEntry entry4c("user3", "Scorer Zain", 1, 4, BallOutcome::SINGLE, 1, 0, WicketType::NONE); // Also wrong!
    scorebook->addScoreEntry(entry4a);
    scorebook->addScoreEntry(entry4b);
    scorebook->addScoreEntry(entry4c);
    
    ball4->displayBall();
    
    // Ball 1.5 - Wicket!
    Ball* ball5 = new Ball(1, 5, bowler1, innings1->getStriker(), innings1->getNonStriker());
    ball5->recordBall(BallOutcome::WICKET, 0);
    ball5->recordWicket(WicketType::BOWLED);
    ball5->setCommentary("Cleaned him up! What a delivery from Bumrah!");
    innings1->recordBall(ball5);
    
    ScoreEntry entry5("user1", "Scorer Ali", 1, 5, BallOutcome::WICKET, 0, 0, WicketType::BOWLED);
    scorebook->addScoreEntry(entry5);
    ball5->displayBall();
    
    // Ball 1.6
    Player* newBatsman = team1->getPlayingXI()[1]; // Rizwan
    innings1->setBatsmen(batsman1, newBatsman);
    
    Ball* ball6 = new Ball(1, 6, bowler1, innings1->getStriker(), innings1->getNonStriker());
    ball6->recordBall(BallOutcome::DOT_BALL, 0);
    ball6->setCommentary("Solid defense from the new batsman");
    innings1->recordBall(ball6);
    
    ScoreEntry entry6("user1", "Scorer Ali", 1, 6, BallOutcome::DOT_BALL, 0, 0, WicketType::NONE);
    scorebook->addScoreEntry(entry6);
    ball6->displayBall();
    
    cout << "\n--- END OF OVER 1 ---" << endl;
    
    // Start second over with different bowler
    Player* bowler2 = team2->getPlayingXI()[8]; // Shami
    innings1->startOver(bowler2);
    
    // Ball 2.1
    Ball* ball7 = new Ball(2, 1, bowler2, innings1->getStriker(), innings1->getNonStriker());
    ball7->recordBall(BallOutcome::SINGLE, 1);
    ball7->setCommentary("Tucked away for a single");
    innings1->recordBall(ball7);
    ball7->displayBall();
    
    // Ball 2.2 - Wide
    Ball* ball8 = new Ball(2, 2, bowler2, innings1->getStriker(), innings1->getNonStriker());
    ball8->recordBall(BallOutcome::WIDE, 0, 1);
    ball8->setCommentary("Wide down the leg side");
    innings1->recordBall(ball8);
    ball8->displayBall();
    
    // Ball 2.2 (re-bowled)
    Ball* ball9 = new Ball(2, 2, bowler2, innings1->getStriker(), innings1->getNonStriker());
    ball9->recordBall(BallOutcome::SIX, 6);
    ball9->setCommentary("MASSIVE SIX! That's out of the ground!");
    innings1->recordBall(ball9);
    ball9->displayBall();
    
    // Continue with a few more balls...
    Ball* ball10 = new Ball(2, 3, bowler2, innings1->getStriker(), innings1->getNonStriker());
    ball10->recordBall(BallOutcome::FOUR, 4);
    ball10->setCommentary("Beautiful shot through covers!");
    innings1->recordBall(ball10);
    ball10->displayBall();
    
    Ball* ball11 = new Ball(2, 4, bowler2, innings1->getStriker(), innings1->getNonStriker());
    ball11->recordBall(BallOutcome::SINGLE, 1);
    ball11->setCommentary("Works it to square leg");
    innings1->recordBall(ball11);
    ball11->displayBall();
    
    Ball* ball12 = new Ball(2, 5, bowler2, innings1->getStriker(), innings1->getNonStriker());
    ball12->recordBall(BallOutcome::DOUBLE, 2);
    ball12->setCommentary("Good running between the wickets");
    innings1->recordBall(ball12);
    ball12->displayBall();
    
    Ball* ball13 = new Ball(2, 6, bowler2, innings1->getStriker(), innings1->getNonStriker());
    ball13->recordBall(BallOutcome::DOT_BALL, 0);
    ball13->setCommentary("Dot ball to end the over");
    innings1->recordBall(ball13);
    ball13->displayBall();
    
    cout << "\n--- END OF OVER 2 ---" << endl;
}

// Function to demonstrate conflict resolution
void demonstrateConflictResolution(Scorebook* scorebook, Supervisor* supervisor) {
    cout << "\n========================================" << endl;
    cout << "  CONFLICT RESOLUTION DEMONSTRATION" << endl;
    cout << "========================================" << endl;
    
    // Display unresolved conflicts
    scorebook->displayUnresolvedConflicts();
    
    // Supervisor resolves conflicts
    cout << "\n--- Supervisor Intervention ---" << endl;
    cout << supervisor->getName() << " is reviewing the conflicts..." << endl;
    
    // Resolve first conflict (ball 1.2)
    ScoreEntry correctEntry1("supervisor", supervisor->getName(), 1, 2, 
                            BallOutcome::FOUR, 4, 0, WicketType::NONE);
    bool resolved1 = scorebook->resolveConflict(1, 2, correctEntry1);
    
    if(resolved1) {
        cout << "✓ Conflict 1 resolved successfully!" << endl;
    }
    
    // Resolve second conflict (ball 1.4)
    ScoreEntry correctEntry2("supervisor", supervisor->getName(), 1, 4,
                            BallOutcome::DOUBLE, 2, 0, WicketType::NONE);
    bool resolved2 = scorebook->resolveConflict(1, 4, correctEntry2);
    
    if(resolved2) {
        cout << "✓ Conflict 2 resolved successfully!" << endl;
    }
    
    cout << "\nAll conflicts have been resolved!" << endl;
    
    // Display all conflicts with resolution
    scorebook->displayAllConflicts();
}

int main() {
    cout << "========================================" << endl;
    cout << "  WELCOME TO FAST-SCOREBOOK" << endl;
    cout << "  Cricket Match Management System" << endl;
    cout << "========================================" << endl;
    
    // Create Venue
    Venue* venue = new Venue("National Stadium", "Karachi", "Pakistan", 34228);
    venue->setPitchType("Batting-friendly");
    venue->setFloodlights(true);
    
    // Create Teams
    Team* pakistan = nullptr;
    Team* india = nullptr;
    createTeamsWithPlayers(pakistan, india);
    
    // Create Match Officials
    Umpire* umpire1 = new Umpire("Aleem Dar", 55, "Pakistan", "UMP001", "On-field");
    Umpire* umpire2 = new Umpire("Richard Kettleborough", 51, "England", "UMP002", "On-field");
    Umpire* umpire3 = new Umpire("Joel Wilson", 47, "West Indies", "UMP003", "Third Umpire");
    
    Commentator* comm1 = new Commentator("Rameez Raja", 61, "Pakistan", "COM001", "Urdu", "TV");
    Commentator* comm2 = new Commentator("Harsha Bhogle", 62, "India", "COM002", "English", "TV");
    
    // Create Broadcasters
    BroadcastAgency* ptvSports = new BroadcastAgency("PTV Sports", "Pakistan", "Urdu");
    BroadcastAgency* starSports = new BroadcastAgency("Star Sports", "India", "Hindi/English");
    BroadcastAgency* skySports = new BroadcastAgency("Sky Sports", "UK", "English");
    
    // Create Supervisor for conflict resolution
    Supervisor* supervisor = new Supervisor("Nadeem Khan", 45, "Pakistan", "SUP001", "nadeem_admin");
    
    // Create ODI Match
    ODIMatch* match = new ODIMatch("PAK_IND_ODI_001", pakistan, india, venue);
    match->addUmpire(umpire1);
    match->addUmpire(umpire2);
    match->addUmpire(umpire3);
    match->addCommentator(comm1);
    match->addCommentator(comm2);
    match->addBroadcaster(ptvSports);
    match->addBroadcaster(starSports);
    match->addBroadcaster(skySports);
    
    // Create Scorebook
    Scorebook* scorebook = new Scorebook(match, supervisor);
    
    // Display initial information
    cout << "\n";
    match->displayMatchInfo();
    venue->displayVenueInfo();
    
    cout << "\n--- Match Officials ---" << endl;
    umpire1->displayInfo();
    umpire2->displayInfo();
    umpire3->displayInfo();
    
    cout << "\n--- Commentators ---" << endl;
    comm1->displayInfo();
    comm2->displayInfo();
    
    cout << "\n--- Broadcasters ---" << endl;
    ptvSports->displayInfo();
    starSports->displayInfo();
    skySports->displayInfo();
    
    // Display teams
    pakistan->displayTeam();
    india->displayTeam();
    
    // Simulate match
    simulateMatch(match, scorebook);
    
    // Display current state
    cout << "\n";
    match->displayMatchSummary();
    
    // Demonstrate conflict resolution
    demonstrateConflictResolution(scorebook, supervisor);
    
    // Display scorebook summary
    scorebook->displayScorebookSummary();
    
    // Interactive menu
    int choice;
    do {
        displayMenu();
        cin >> choice;
        
        switch(choice) {
            case 1:
                match->displayMatchInfo();
                break;
            case 2:
                pakistan->displayTeam();
                india->displayTeam();
                break;
            case 3:
                venue->displayVenueInfo();
                break;
            case 4:
                match->displayMatchSummary();
                break;
            case 5:
                match->displayFullMatch();
                break;
            case 6:
                scorebook->displayScorebookSummary();
                break;
            case 7:
                scorebook->displayAllConflicts();
                break;
            case 8:
                cout << "\n--- Match Officials ---" << endl;
                umpire1->displayInfo();
                umpire2->displayInfo();
                umpire3->displayInfo();
                break;
            case 9:
                cout << "\n--- Broadcasters ---" << endl;
                ptvSports->displayInfo();
                starSports->displayInfo();
                skySports->displayInfo();
                break;
            case 0:
                cout << "\nThank you for using FAST-SCOREBOOK!" << endl;
                break;
            default:
                cout << "\nInvalid choice! Please try again." << endl;
        }
    } while(choice != 0);
    
    // Cleanup (in a real system, use smart pointers)
    delete scorebook;
    delete supervisor;
    delete match; // This will also delete innings
    delete pakistan;
    delete india;
    delete venue;
    delete umpire1;
    delete umpire2;
    delete umpire3;
    delete comm1;
    delete comm2;
    delete ptvSports;
    delete starSports;
    delete skySports;
    
    return 0;
}
