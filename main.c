#include <stdio.h>
#include <raylib.h>
#include <string.h>

#define MAX_DIALOGUE_CHAR 256
#define DIALOGUE_X 100
#define DIALOGUE_Y 810

/*    ___________________________________
     ♥    Hand-Crafted With Love ♥       ♥
     |       ---- Shib@ ----             |
     |      ---- TWongpoo ----           | 
     |       ---- James ----             |  
     ♥___________________________________♥

*/

int main() {
    
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1600;
    int screenHeight = 900;
    // 1 tile = 50 px ----> 32 tile * 18 tile

    InitWindow(screenWidth, screenHeight, "it-metroidvenia"); 
    SetTargetFPS(33);
    
    // ---------- Load All Resouce ----------
    
    Texture2D playerSpriteX = LoadTexture("./asset/main-char-x");
    Texture2D playerSpriteY = LoadTexture("./asset/main-char-y"); 
    
    // ---------- Variable ----------
    
    int playerSpeed = 30;
    int currentMap = 0;
    int day = 1;
    int score = 0;
    int counter_score_day = 0;
    char currentDialogue[256] = {'\0'};
    char xPos[8], yPos[8], DAYPos[8], ScorePos[5];
    
    // ---------- Struct ----------
    
    struct Entity {
        int x;            
        int y;            
        int width;
        int height;
        int dialogueCounter;
        char dialogue[5][MAX_DIALOGUE_CHAR];
    };

    struct Entity Player     = {800, 450, 50, 50, 0, {"", "", "", "", ""}}; // Declare a "Player" Entity

    //struct Entity TestNPC    = {450, 200, 50, 50, 0, {"FUCK", "OFF", "DONT", "MASS", "WITH ME"}};
    struct Entity NPCday1_f1_1    = {450, 200, 50, 50, 0, {"Howdy...","Have a nice day hahaha","","","..."}};
    struct Entity NPCday1_f1_2    = {980, 230, 50, 50, 0, {"T. Sho ?","Teacher is on the 1st floor","He is teaching","","..."}};
    struct Entity NPCday1_f2    = {80, 330, 50, 50, 0, {"Hi...","I'm Jon Snow","Winter's coming","","..."}};
    struct Entity NPCday1_f3    = {1220, 99, 50, 50, 0, {"Player!!!!","Did you go to study?","Subjects of T.Sho","","..."}};
    struct Entity NPCday1_f5    = {350, 150, 50, 50, 0, {".","..","...","....","....."}};
    struct Entity NPCday1_T   = {750, 60, 50, 50, 0, {"Project PSIT, ","Project sent after the final","see you","","..."}}; //in audi
    
    struct Rectangle NPCday1_f1_1_h  = {NPCday1_f1_1.x - 50, NPCday1_f1_1.y - 50, 150, 150};
    struct Rectangle NPCday1_f1_2_h   = {NPCday1_f1_2.x - 50, NPCday1_f1_2.y - 50, 150, 150};
    struct Rectangle NPCday1_f2_h   = {NPCday1_f2.x - 50, NPCday1_f2.y - 50, 150, 150};
    struct Rectangle NPCday1_f3_h   = {NPCday1_f3.x - 50, NPCday1_f3.y - 50, 150, 150};
    struct Rectangle NPCday1_f5_h   = {NPCday1_f5.x - 50, NPCday1_f5.y - 50, 150, 150};
    struct Rectangle NPCday1_T_h   = {NPCday1_T.x - 50, NPCday1_T.y - 50, 150, 150};

    struct Entity NPCday2_f1_1     = {450, 200, 50, 50, 0, {"ICS ?","It is very difficult","","","..."}};
    struct Entity NPCday2_f1_2    = {980, 230, 50, 50, 0, {"T. Sho ?","Teacher is on the 5 floor.","...","...","..."}};
    struct Entity NPCday2_f2     = {80, 330, 50, 50, 0, {"Hi...","ICS subjects are about to begin.","Teacher is on the 2 floor.","","..."}};
    struct Entity NPCday2_f3     = {1220, 99, 50, 50, 0, {"Player!!!!","Did you go to study?","","","..."}};
    struct Entity NPCday2_f5     = {350, 150, 50, 50, 0, {".","..","...","....","....."}};
    struct Entity NPCday2_T    = {140, 120, 50, 50, 0, {"ICS is Ez","Do not worry","Cut F at 50 points","","..."}}; //in room f2
    
    struct Rectangle NPCday2_f1_1_h   = {NPCday2_f1_1.x - 50, NPCday2_f1_1.y - 50, 150, 150};
    struct Rectangle NPCday2_f1_2_h   = {NPCday2_f1_2.x - 50, NPCday2_f1_2.y - 50, 150, 150};
    struct Rectangle NPCday2_f2_h   = {NPCday2_f2.x - 50, NPCday2_f2.y - 50, 150, 150};
    struct Rectangle NPCday2_f3_h   = {NPCday2_f3.x - 50, NPCday2_f3.y - 50, 150, 150};
    struct Rectangle NPCday2_f5_h   = {NPCday2_f5.x - 50, NPCday2_f5.y - 50, 150, 150};
    struct Rectangle NPCday2_T_h   = {NPCday2_T.x - 50, NPCday2_T.y - 50, 150, 150};

    struct Entity NPCday3_f1_1     = {450, 200, 50, 50, 0, {"I hate this subject","...","It is very difficult","...",""}};
    struct Entity NPCday3_f1_2     = {980, 230, 50, 50, 0, {"Study IT","Did not study management","","","..."}};
    struct Entity NPCday3_f2     = {80, 330, 50, 50, 0, {"Hi...","Can you bring a calculator?","","","..."}};
    struct Entity NPCday3_f3       = {1220, 99, 50, 50, 0, {"On the 2nd floor","Very difficult to learn","","","..."}};
    struct Entity NPCday3_f5     = {350, 150, 50, 50, 0, {".","..","...","....","....."}};
    struct Entity NPCday3_T    = {1190, 180, 50, 50, 0, {"Gen Bit ","is not F","...","Right?","..."}}; //in room f2
    
    struct Rectangle NPCday3_f1_1_h   = {NPCday3_f1_1.x - 50, NPCday3_f1_1.y - 50, 150, 150};
    struct Rectangle NPCday3_f1_2_h   = {NPCday3_f1_2.x - 50, NPCday3_f1_2.y - 50, 150, 150};
    struct Rectangle NPCday3_f2_h   = {NPCday3_f2.x - 50, NPCday3_f2.y - 50, 150, 150};
    struct Rectangle NPCday3_f3_h   = {NPCday3_f3.x - 50, NPCday3_f3.y - 50, 150, 150};
    struct Rectangle NPCday3_f5_h   = {NPCday3_f5.x - 50, NPCday3_f5.y - 50, 150, 150};
    struct Rectangle NPCday3_T_h   = {NPCday3_T.x - 50, NPCday3_T.y - 50, 150, 150};

    struct Entity NPCday4_f1_1     = {450, 200, 50, 50, 0, {"I am heartbroken","...","Because you don't like me","...","..."}};
    struct Entity NPCday4_f1_2     = {980, 230, 50, 50, 0, {"Where is ITF studying?","...","","",""}};
    struct Entity NPCday4_f2     = {80, 330, 50, 50, 0, {"Hi...","The 3rd floor has a lab.","Don't forget","...",""}};
    struct Entity NPCday4_f3     = {1220, 99, 50, 50, 0, {"Want to go home","Now!!!","...","",""}};
    struct Entity NPCday4_f5     = {350, 150, 50, 50, 0, {".","..","...","....","....."}};
    struct Entity NPCday4_T    = {950, 300, 50, 50, 0, {"ITF ","F for IT","...","Right?","..."}}; //in room f3
    
    struct Rectangle NPCday4_f1_1_h   = {NPCday4_f1_1.x - 50, NPCday4_f1_1.y - 50, 150, 150};
    struct Rectangle NPCday4_f1_2_h   = {NPCday4_f1_2.x - 50, NPCday4_f1_2.y - 50, 150, 150};
    struct Rectangle NPCday4_f2_h   = {NPCday4_f2.x - 50, NPCday4_f2.y - 50, 150, 150};
    struct Rectangle NPCday4_f3_h   = {NPCday4_f3.x - 50, NPCday4_f3.y - 50, 150, 150};
    struct Rectangle NPCday4_f5_h   = {NPCday4_f5.x - 50, NPCday4_f5.y - 50, 150, 150};
    struct Rectangle NPCday4_T_h   = {NPCday4_T.x - 50, NPCday4_T.y - 50, 150, 150};

    struct Entity NPCday5_f1_1     = {450, 200, 50, 50, 0, {"The 3rd floor has a lab.","...","","",""}};
    struct Entity NPCday5_f1_2     = {980, 230, 50, 50, 0, {"On the 2nd floor","...","","",""}};
    struct Entity NPCday5_f2     = {80, 330, 50, 50, 0, {"ICS subjects are about to begin.","","","",""}};
    struct Entity NPCday5_f3     = {1220, 99, 50, 50, 0, {"Teacher is on the 1st floor.","","","",""}};
    struct Entity NPCday5_f5     = {350, 150, 50, 50, 0, {"Today no classes",".","..","...","...."}};
    struct Entity NPCday5_T    = {420, 210, 50, 50, 0, {"","","","",""}}; // No T pass day give 10p.
    
    struct Rectangle NPCday5_f1_1_h   = {NPCday5_f1_1.x - 50, NPCday5_f1_1.y - 50, 150, 150};
    struct Rectangle NPCday5_f1_2_h   = {NPCday5_f1_2.x - 50, NPCday5_f1_2.y - 50, 150, 150};
    struct Rectangle NPCday5_f2_h   = {NPCday5_f2.x - 50, NPCday5_f2.y - 50, 150, 150};
    struct Rectangle NPCday5_f3_h   = {NPCday5_f3.x - 50, NPCday5_f3.y - 50, 150, 150};
    struct Rectangle NPCday5_f5_h   = {NPCday5_f5.x - 50, NPCday5_f5.y - 50, 150, 150};
    struct Rectangle NPCday5_T_h   = {NPCday5_T.x - 50, NPCday5_T.y - 50, 150, 150};

    struct Entity NPCday6_f1_1     = {450, 200, 50, 50, 0, {"Memorization.","about computers","","","..."}};
    struct Entity NPCday6_f1_2      = {980, 230, 50, 50, 0, {"On the 2nd floor","","","","..."}};
    struct Entity NPCday6_f2     = {80, 330, 50, 50, 0, {"Very sleepy","","","",""}};
    struct Entity NPCday6_f3     = {1220, 99, 50, 50, 0, {    "Teacher is on the 2st floor.","","","",""}};
    struct Entity NPCday6_f5     = {350, 150, 50, 50, 0, {".","..","...","....","....."}};
    struct Entity NPCday6_T    = {80, 630, 50, 50, 0, {"This course focuses on remembering.","about computers","","","..."}}; //in room f2
    
    struct Rectangle NPCday6_f1_1_h  = {NPCday6_f1_1.x - 50, NPCday6_f1_1.y - 50, 150, 150};;
    struct Rectangle NPCday6_f1_2_h  = {NPCday6_f1_2.x - 50, NPCday6_f1_2.y - 50, 150, 150};
    struct Rectangle NPCday6_f2_h  = {NPCday6_f2.x - 50, NPCday6_f2.y - 50, 150, 150};
    struct Rectangle NPCday6_f3_h  = {NPCday6_f3.x - 50, NPCday6_f3.y - 50, 150, 150};
    struct Rectangle NPCday6_f5_h  = {NPCday6_f5.x - 50, NPCday6_f5.y - 50, 150, 150};
    struct Rectangle NPCday6_T_h  = {NPCday6_T.x - 50, NPCday6_T.y - 50, 150, 150};

    struct Entity NPCday7_f1_1    = {450, 200, 50, 50, 0, {"This course focuses","on creative thinking.","","",""}};
    struct Entity NPCday7_f1_2    = {980, 230, 50, 50, 0, {"On the 1st floor",".","..","","..."}};
    struct Entity NPCday7_f2    = {80, 330, 50, 50, 0, {"Hi...","I'm Jon Snow","Winter's coming","","..."}};
    struct Entity NPCday7_f3    = {1220, 99, 50, 50, 0, {"Must take the computer to do the project too. 2 projects","","","","..."}};
    struct Entity NPCday7_f5    = {350, 150, 50, 50, 0, {".","..","...","....","....."}};
    struct Entity NPCday7_T   = {750, 60, 50, 50, 0, {"This course focuses creative thinking","Art and creative","","","..."}}; // in audi
    
    struct Rectangle NPCday7_f1_1_h  = {NPCday7_f1_1.x - 50, NPCday7_f1_1.y - 50, 150, 150};
    struct Rectangle NPCday7_f1_2_h  = {NPCday7_f1_2.x - 50, NPCday7_f1_2.y - 50, 150, 150};
    struct Rectangle NPCday7_f2_h  = {NPCday7_f2.x - 50, NPCday7_f2.y - 50, 150, 150};
    struct Rectangle NPCday7_f3_h  = {NPCday7_f3.x - 50, NPCday7_f3.y - 50, 150, 150};
    struct Rectangle NPCday7_f5_h  = {NPCday7_f5.x - 50, NPCday7_f5.y - 50, 150, 150};
    struct Rectangle NPCday7_T_h  = {NPCday7_T.x - 50, NPCday7_T.y - 50, 150, 150};

    struct Entity NPCday8_f1_1    = {450, 200, 50, 50, 0, {"DISCRETE MATHEMATICS ","Not easy","","",""}};
    struct Entity NPCday8_f1_2    = {980, 230, 50, 50, 0, {"Discrete","Previous group,studying 1st floor","","",""}};
    struct Entity NPCday8_f2    = {80, 330, 50, 50, 0, {"i want to go home!!","","","",""}};
    struct Entity NPCday8_f3    = {1220, 99, 50, 50, 0, {"Not...","understand....","","",""}};
    struct Entity NPCday8_f5    = {350, 150, 50, 50, 0, {".","..","...","....","....."}};
    struct Entity NPCday8_T   = {149, 60, 50, 50, 0, {"This course focuses creative logic","Prove","and Truth value","",""}};// in room f2
    
    struct Rectangle NPCday8_f1_1_h  = {NPCday8_f1_1.x - 50, NPCday8_f1_1.y - 50, 150, 150};
    struct Rectangle NPCday8_f1_2_h  = {NPCday8_f1_2.x - 50, NPCday8_f1_2.y - 50, 150, 150};
    struct Rectangle NPCday8_f2_h  = {NPCday8_f2.x - 50, NPCday8_f2.y - 50, 150, 150};
    struct Rectangle NPCday8_f3_h  = {NPCday8_f3.x - 50, NPCday8_f3.y - 50, 150, 150};
    struct Rectangle NPCday8_f5_h  = {NPCday8_f5.x - 50, NPCday8_f5.y - 50, 150, 150};
    struct Rectangle NPCday8_T_h  = {NPCday8_T.x - 50, NPCday8_T.y - 50, 150, 150};

    struct Entity NPCday9_f1_1    = {450, 200, 50, 50, 0, {"Don't like foreign languages at all","Not easy","","",""}};
    struct Entity NPCday9_f1_2    = {980, 230, 50, 50, 0, {"Hi...","...","and","...","See you"}};
    struct Entity NPCday9_f2    = {80, 330, 50, 50, 0, {"i want to go home!!","","","",""}};
    struct Entity NPCday9_f3    = {1220, 99, 50, 50, 0, {"Eng","Ez","","",""}};
    struct Entity NPCday9_f5    = {350, 150, 50, 50, 0, {".","..","...","....","....."}};
    struct Entity NPCday9_T   = {1400, 510, 50, 50, 0, {"English is a...","common language in communication.","","",""}};// in room f2
    
    struct Rectangle NPCday9_f1_1_h  = {NPCday9_f1_1.x - 50, NPCday9_f1_1.y - 50, 150, 150};
    struct Rectangle NPCday9_f1_2_h  = {NPCday9_f1_2.x - 50, NPCday9_f1_2.y - 50, 150, 150};
    struct Rectangle NPCday9_f2_h  = {NPCday9_f2.x - 50, NPCday9_f2.y - 50, 150, 150};
    struct Rectangle NPCday9_f3_h  = {NPCday9_f3.x - 50, NPCday9_f3.y - 50, 150, 150};
    struct Rectangle NPCday9_f5_h  = {NPCday9_T.x - 50, NPCday9_T.y - 50, 150, 150};
    struct Rectangle NPCday9_T_h = {NPCday9_T.x - 50, NPCday9_T.y - 50, 150, 150};

    struct Entity NPCday10_f1_1    = {450, 200, 50, 50, 0, {"Don't like foreign languages at all","Not easy","","",""}};
    struct Entity NPCday10_f1_2    = {980, 230, 50, 50, 0, {"This course focuses creative logic","...","and","...","See you"}};
    struct Entity NPCday10_f2    = {80, 330, 50, 50, 0, {"This course focuses creative thinking","","","",""}};
    struct Entity NPCday10_f3    = {1220, 99, 50, 50, 0, {"This course focuses on remembering.","Ez","","",""}};
    struct Entity NPCday10_f5    = {350, 150, 50, 50, 0, {"Today","Send the project last day","Hurry to the computer.","And send","Now !!!"}};
    struct Entity NPCday10_T   = {420, 210, 50, 50, 0, {"","","","",""}}; // computer your home
    
    struct Rectangle NPCday10_f1_1_h  = {NPCday10_f1_1.x - 50, NPCday10_f1_1.y - 50, 150, 150};
    struct Rectangle NPCday10_f1_2_h  = {NPCday10_f1_2.x - 50, NPCday10_f1_2.y - 50, 150, 150};
    struct Rectangle NPCday10_f2_h  = {NPCday10_f2.x - 50, NPCday10_f2.y - 50, 150, 150};
    struct Rectangle NPCday10_f3_h  = {NPCday10_f3.x - 50, NPCday10_f3.y - 50, 150, 150};
    struct Rectangle NPCday10_f5_h  = {NPCday10_f5.x - 50, NPCday10_f5.y - 50, 150, 150};
    struct Rectangle NPCday10_T_h  = {NPCday10_T.x - 50, NPCday10_T.y - 50, 150, 150};;

    struct Rectangle PlayerHitbox   = {Player.x, Player.y, Player.width, Player.height};
    
    struct Rectangle LeftBorder   = {0, 0, 0, 0};
    struct Rectangle RightBorder  = {0, 0, 0, 0};
    struct Rectangle TopBorder    = {0, 0, 0, 0};
    struct Rectangle BottomBorder = {0, 0, 0, 0};
   

    // ---------- Main game loop ----------

    while (!WindowShouldClose()) {
        if(day < 11){
        // ---------- Controller ----------

        if (IsKeyDown(KEY_W)) Player.y -= playerSpeed; // Up
 
        if (IsKeyDown(KEY_S)) Player.y += playerSpeed; // Down

        if (IsKeyDown(KEY_A)) Player.x -= playerSpeed; // Left

        if (IsKeyDown(KEY_D)) Player.x += playerSpeed; // Right
        
        if (IsKeyPressed(KEY_Q)) currentMap = 1, day += 1, counter_score_day = 0;
        
        // ---------- Update Variable ----------
        
        PlayerHitbox.x = Player.x;
        PlayerHitbox.y = Player.y;
        
        // ---------- Draw ----------

        BeginDrawing();
        
            ClearBackground(RAYWHITE);
         
        // ---------- Map ----------
        
/*         Map
               0 : Home
               1 : Main F1
               2 : Sub F1
               3 : M
               4 : Common
               5 : Audi
               6 : F2
               7 : F3
               8 : -
               7 : F5
               21 : F2Room
               31 : F3Room
               51 : F5Room
               
               RED : Warp
               BLUE : Obstacle
               BLACK : Map Border
               PINK : Player
*/
        switch (currentMap) {
            
            case 0: // Home
                
                DrawRectangle(0, 0, 1600, 200, BLACK);
                DrawRectangle(0, 600, 1600, 150, BLACK);
                DrawRectangle(0, 0, 400, 700, BLACK);
                DrawRectangle(1200, 0, 400, 700, BLACK);
                
                
                LeftBorder.x = 0, LeftBorder.y = 0, LeftBorder.width = 400, LeftBorder.height = 700;
                RightBorder.x = 1200, RightBorder.y = 0, RightBorder.width = 400, RightBorder.height = 700;
                TopBorder.x = 0, TopBorder.y = 0, TopBorder.width = 1600, TopBorder.height = 200;
                BottomBorder.x = 0, BottomBorder.y = 600, BottomBorder.width = 1600, BottomBorder.height = 150;
                
                DrawRectangle(1180, 250, 20, 100, RED);
                struct Rectangle home_mainF1 = {1180, 250, 20, 100};
                
                if (CheckCollisionRecs(PlayerHitbox, TopBorder))    Player.y += playerSpeed; // Top
                if (CheckCollisionRecs(PlayerHitbox, BottomBorder)) Player.y -= playerSpeed; // Bottom
                if (CheckCollisionRecs(PlayerHitbox, LeftBorder))   Player.x += playerSpeed; // Left
                if (CheckCollisionRecs(PlayerHitbox, RightBorder))  Player.x -= playerSpeed; // Right
                
                if (CheckCollisionRecs(PlayerHitbox, home_mainF1)) {
                    Player.x = 480, Player.y = 610;
                    currentMap = 1;
                }
                
                if (day == 5){
                    DrawRectangle(NPCday5_T.x, NPCday5_T.y, 50, 50, MAGENTA);
                    if (CheckCollisionRecs(PlayerHitbox, NPCday5_T_h) && IsKeyPressed(KEY_SPACE) && day == 5) {
                        strcpy(currentDialogue, NPCday5_T.dialogue[NPCday5_T.dialogueCounter]);           
                        NPCday5_T.dialogueCounter++;
                        counter_score_day++;                                                    
                        if (NPCday5_T.dialogueCounter > 4) NPCday2_T.dialogueCounter = 0;
                        if (counter_score_day == 1) score += 10;
                }
                }
                
                if (day == 10){
                    DrawRectangle(NPCday10_T.x, NPCday10_T.y, 50, 50, MAGENTA);
                    if (CheckCollisionRecs(PlayerHitbox, NPCday10_T_h) && IsKeyPressed(KEY_SPACE) && day == 10) {
                        strcpy(currentDialogue, NPCday10_T.dialogue[NPCday10_T.dialogueCounter]);           
                        NPCday10_T.dialogueCounter++;
                        counter_score_day++;                                                    
                        if (NPCday10_T.dialogueCounter > 4) NPCday2_T.dialogueCounter = 0;
                        if (counter_score_day == 1) score += 10;
                }
                }
                DrawRectangle(410, 540, 100, 50, RED);
                struct Rectangle bad   = {410, 540, 100, 50};
                if (CheckCollisionRecs(PlayerHitbox, bad) && IsKeyPressed(KEY_SPACE)) {
                    day += 1;
                    counter_score_day = 0;
                }
                
                DrawText("Home", 80, 80, 40, RED);
                break;
            
            case 1: // Main F1
            
                for (int y = 0; y <= 850; y += 50) {
                    for (int x = 0; x <= 1550; x += 50) {
                        if (x == 0 || x == 1550 || y == 0 || y == 700) {
                            DrawRectangle(x, y, 50, 50, BLACK); 
                        }
                    }
                }
            
                LeftBorder.x = 0, LeftBorder.y = 0, LeftBorder.width = 50, LeftBorder.height = 900;
                RightBorder.x = 1550, RightBorder.y = 0, RightBorder.width = 50, RightBorder.height = 900;
                TopBorder.x = 0, TopBorder.y = 0, TopBorder.width = 1600, TopBorder.height = 50;
                BottomBorder.x = 0, BottomBorder.y = 700, BottomBorder.width = 1600, BottomBorder.height = 50;
   
                if (CheckCollisionRecs(PlayerHitbox, TopBorder))    Player.y += playerSpeed; // Top
                if (CheckCollisionRecs(PlayerHitbox, BottomBorder)) Player.y -= playerSpeed; // Bottom
                if (CheckCollisionRecs(PlayerHitbox, LeftBorder))   Player.x += playerSpeed; // Left
                if (CheckCollisionRecs(PlayerHitbox, RightBorder))  Player.x -= playerSpeed; // Right   
                
                DrawRectangle(1300, 200, 150, 200, BLUE);
            
                DrawRectangle(50, 50, 1500, 20, RED);    // |
                DrawRectangle(1530, 450, 20, 250, RED);  // | Draw Warp
                DrawRectangle(400, 680, 200, 20, RED);   // |
                
                struct Rectangle mainF1_mFloor = {50, 50, 1500, 20};       // |
                struct Rectangle mainF1_subF1 = {1530, 450, 20, 250};      // | Warp Hitbox
                struct Rectangle mainF1_home = {400, 680, 200, 20};        // |
                
                //DrawRectangle(TestNPC.x, TestNPC.y, TestNPC.width, TestNPC.height, MAGENTA);
                //DrawRectangleLines(TestNPCHitbox.x, TestNPCHitbox.y, TestNPCHitbox.width, TestNPCHitbox.height, BLUE);
                
                if (CheckCollisionRecs(PlayerHitbox, mainF1_home)) {
                    currentMap = 0;
                    Player.x = 1110, Player.y = 270;
                }
                if (CheckCollisionRecs(PlayerHitbox, mainF1_subF1)) {
                    currentMap = 2;
                    Player.x = 80, Player.y = 350;
                }
                if (CheckCollisionRecs(PlayerHitbox, mainF1_mFloor)) {
                    currentMap = 3;
                    Player.y = 630;
                }
/*                if (CheckCollisionRecs(PlayerHitbox, TestNPCHitbox) && IsKeyPressed(KEY_SPACE)) { // |
                    strcpy(currentDialogue, TestNPC.dialogue[TestNPC.dialogueCounter]);           // | Example of dialogue
                    TestNPC.dialogueCounter++;                                                    // | system of 1 NPC
                    if (TestNPC.dialogueCounter > 4) TestNPC.dialogueCounter = 0;                 // |
                } */
                
                DrawRectangle(NPCday1_f1_1.x, NPCday1_f1_1.y, 50, 50, MAGENTA);

                if (CheckCollisionRecs(PlayerHitbox, NPCday1_f1_1_h) && IsKeyPressed(KEY_SPACE) && day == 1) {
                    strcpy(currentDialogue, NPCday1_f1_1.dialogue[NPCday1_f1_1.dialogueCounter]);           
                    NPCday1_f1_1.dialogueCounter++;                                                    
                    if (NPCday1_f1_1.dialogueCounter > 4) NPCday1_f1_1.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday2_f1_1_h) && IsKeyPressed(KEY_SPACE) && day == 2) {
                    strcpy(currentDialogue, NPCday2_f1_1.dialogue[NPCday2_f1_1.dialogueCounter]);           
                    NPCday2_f1_1.dialogueCounter++;                                                    
                    if (NPCday2_f1_1.dialogueCounter > 4) NPCday2_f1_1.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday3_f1_1_h) && IsKeyPressed(KEY_SPACE) && day == 3) {
                    strcpy(currentDialogue, NPCday3_f1_1.dialogue[NPCday3_f1_1.dialogueCounter]);           
                    NPCday3_f1_1.dialogueCounter++;                                                    
                    if (NPCday3_f1_1.dialogueCounter > 4) NPCday3_f1_1.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday4_f1_1_h) && IsKeyPressed(KEY_SPACE) && day == 4) {
                    strcpy(currentDialogue, NPCday4_f1_1.dialogue[NPCday4_f1_1.dialogueCounter]);           
                    NPCday4_f1_1.dialogueCounter++;                                                    
                    if (NPCday4_f1_1.dialogueCounter > 4) NPCday4_f1_1.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday5_f1_1_h) && IsKeyPressed(KEY_SPACE) && day == 5) {
                    strcpy(currentDialogue, NPCday5_f1_1.dialogue[NPCday5_f1_1.dialogueCounter]);           
                    NPCday5_f1_1.dialogueCounter++;                                                    
                    if (NPCday5_f1_1.dialogueCounter > 4) NPCday5_f1_1.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday6_f1_1_h) && IsKeyPressed(KEY_SPACE) && day == 6) {
                    strcpy(currentDialogue, NPCday6_f1_1.dialogue[NPCday6_f1_1.dialogueCounter]);           
                    NPCday6_f1_1.dialogueCounter++;                                                    
                    if (NPCday6_f1_1.dialogueCounter > 4) NPCday6_f1_1.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday7_f1_1_h) && IsKeyPressed(KEY_SPACE) && day == 7) {
                    strcpy(currentDialogue, NPCday7_f1_1.dialogue[NPCday7_f1_1.dialogueCounter]);           
                    NPCday7_f1_1.dialogueCounter++;                                                    
                    if (NPCday7_f1_1.dialogueCounter > 4) NPCday7_f1_1.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday8_f1_1_h) && IsKeyPressed(KEY_SPACE) && day == 8) {
                    strcpy(currentDialogue, NPCday8_f1_1.dialogue[NPCday8_f1_1.dialogueCounter]);           
                    NPCday8_f1_1.dialogueCounter++;                                                    
                    if (NPCday8_f1_1.dialogueCounter > 4) NPCday8_f1_1.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday9_f1_1_h) && IsKeyPressed(KEY_SPACE) && day == 9) {
                    strcpy(currentDialogue, NPCday9_f1_1.dialogue[NPCday9_f1_1.dialogueCounter]);           
                    NPCday9_f1_1.dialogueCounter++;                                                    
                    if (NPCday9_f1_1.dialogueCounter > 4) NPCday9_f1_1.dialogueCounter = 0;
                }
                
             
                if (CheckCollisionRecs(PlayerHitbox, NPCday10_f1_1_h) && IsKeyPressed(KEY_SPACE) && day == 10) {
                    strcpy(currentDialogue, NPCday10_f1_1.dialogue[NPCday10_f1_1.dialogueCounter]);           
                    NPCday10_f1_1.dialogueCounter++;                                                    
                    if (NPCday10_f1_1.dialogueCounter > 4) NPCday10_f1_1.dialogueCounter = 0;
                }
                        
                
                
                DrawText("Main F1", 80, 80, 40, RED);
                break;
            
            case 2: // Common & Audi

                DrawRectangle(0, 0, 1600, 200, BLACK);
                DrawRectangle(0, 600, 1600, 150, BLACK);
                DrawRectangle(0, 0, 50, 700, BLACK);
                DrawRectangle(1550, 0, 50, 700, BLACK);
                
                TopBorder.x = 0, TopBorder.y = 0, TopBorder.width = 1600, TopBorder.height = 200;
                BottomBorder.x = 0, BottomBorder.y = 600, BottomBorder.width = 1600, BottomBorder.height = 150;
                LeftBorder.x = 0, LeftBorder.y = 0, LeftBorder.width = 50, LeftBorder.height = 700;
                RightBorder.x = 1550, RightBorder.y = 0, RightBorder.width = 50, RightBorder.height = 700;
                
                if (CheckCollisionRecs(PlayerHitbox, TopBorder))    Player.y += playerSpeed; // Top
                if (CheckCollisionRecs(PlayerHitbox, BottomBorder)) Player.y -= playerSpeed; // Bottom
                if (CheckCollisionRecs(PlayerHitbox, LeftBorder))   Player.x += playerSpeed; // Left
                if (CheckCollisionRecs(PlayerHitbox, RightBorder))  Player.x -= playerSpeed; // Right
                
                DrawRectangle(50, 330, 20, 100, RED);
                DrawRectangle(270, 580, 100, 20, RED);
                DrawRectangle(1150, 200, 200, 20, RED);
                
                struct Rectangle subF1_mainF1 = {50, 330, 20, 100};        // |
                struct Rectangle subF1_common = {270, 580, 100, 20};       // | Warp Hitbox
                struct Rectangle subF1_audi = {1150, 200, 200, 20};        // |
                
                if (CheckCollisionRecs(PlayerHitbox, subF1_mainF1)) {
                    currentMap = 1;
                    Player.x = 1470, Player.y = 550;
                }
                if (CheckCollisionRecs(PlayerHitbox, subF1_common)) {
                    strcpy(currentDialogue, "It's Lock");
                    Player.x = 290, Player.y = 510;
                }
                if (CheckCollisionRecs(PlayerHitbox, subF1_audi)) {
                    currentMap = 5;
                    Player.x = 750, Player.y = 600;
                }
                
                DrawRectangle(NPCday1_f1_2.x, NPCday1_f1_2.y, 50, 50, MAGENTA);

                if (CheckCollisionRecs(PlayerHitbox, NPCday1_f1_2_h) && IsKeyPressed(KEY_SPACE) && day == 1) {
                    strcpy(currentDialogue, NPCday1_f1_2.dialogue[NPCday1_f1_2.dialogueCounter]);           
                    NPCday1_f1_2.dialogueCounter++;                                                    
                    if (NPCday1_f1_2.dialogueCounter > 4) NPCday1_f1_2.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday2_f1_2_h) && IsKeyPressed(KEY_SPACE) && day == 2) {
                    strcpy(currentDialogue, NPCday2_f1_2.dialogue[NPCday2_f1_2.dialogueCounter]);           
                    NPCday2_f1_2.dialogueCounter++;                                                    
                    if (NPCday2_f1_2.dialogueCounter > 4) NPCday2_f1_2.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday3_f1_2_h) && IsKeyPressed(KEY_SPACE) && day == 3) {
                    strcpy(currentDialogue, NPCday3_f1_2.dialogue[NPCday3_f1_2.dialogueCounter]);           
                    NPCday3_f1_2.dialogueCounter++;                                                    
                    if (NPCday3_f1_2.dialogueCounter > 4) NPCday3_f1_2.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday4_f1_2_h) && IsKeyPressed(KEY_SPACE) && day == 4) {
                    strcpy(currentDialogue, NPCday4_f1_2.dialogue[NPCday4_f1_2.dialogueCounter]);           
                    NPCday4_f1_2.dialogueCounter++;                                                    
                    if (NPCday4_f1_2.dialogueCounter > 4) NPCday4_f1_2.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday5_f1_2_h) && IsKeyPressed(KEY_SPACE) && day == 5) {
                    strcpy(currentDialogue, NPCday5_f1_2.dialogue[NPCday5_f1_2.dialogueCounter]);           
                    NPCday5_f1_2.dialogueCounter++;                                                    
                    if (NPCday5_f1_2.dialogueCounter > 4) NPCday5_f1_2.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday6_f1_2_h) && IsKeyPressed(KEY_SPACE) && day == 6) {
                    strcpy(currentDialogue, NPCday6_f1_2.dialogue[NPCday6_f1_2.dialogueCounter]);           
                    NPCday6_f1_2.dialogueCounter++;                                                    
                    if (NPCday6_f1_2.dialogueCounter > 4) NPCday6_f1_2.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday7_f1_2_h) && IsKeyPressed(KEY_SPACE) && day == 7) {
                    strcpy(currentDialogue, NPCday7_f1_2.dialogue[NPCday7_f1_2.dialogueCounter]);           
                    NPCday7_f1_2.dialogueCounter++;                                                    
                    if (NPCday7_f1_2.dialogueCounter > 4) NPCday7_f1_2.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday8_f1_2_h) && IsKeyPressed(KEY_SPACE) && day == 8) {
                    strcpy(currentDialogue, NPCday8_f1_2.dialogue[NPCday8_f1_2.dialogueCounter]);           
                    NPCday8_f1_2.dialogueCounter++;                                                    
                    if (NPCday8_f1_2.dialogueCounter > 4) NPCday8_f1_2.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday9_f1_2_h) && IsKeyPressed(KEY_SPACE) && day == 9) {
                    strcpy(currentDialogue, NPCday9_f1_2.dialogue[NPCday9_f1_2.dialogueCounter]);           
                    NPCday9_f1_2.dialogueCounter++;                                                    
                    if (NPCday9_f1_2.dialogueCounter > 4) NPCday9_f1_2.dialogueCounter = 0;
                }
                
             
                if (CheckCollisionRecs(PlayerHitbox, NPCday10_f1_2_h) && IsKeyPressed(KEY_SPACE) && day == 10) {
                    strcpy(currentDialogue, NPCday10_f1_2.dialogue[NPCday10_f1_2.dialogueCounter]);           
                    NPCday10_f1_2.dialogueCounter++;                                                    
                    if (NPCday10_f1_2.dialogueCounter > 4) NPCday10_f1_2.dialogueCounter = 0;
                }
                        
                DrawText("SubF1", 80, 80, 40, RED);
                break;
            
            case 3: // M
                DrawRectangle(0, 0, 1600, 50, BLACK);
                DrawRectangle(0, 700, 1600, 50, BLACK);
                DrawRectangle(0, 0, 50, 900, BLACK);
                DrawRectangle(1550, 0, 50, 900, BLACK);
                
                LeftBorder.x = 0, LeftBorder.y = 0, LeftBorder.width = 50, LeftBorder.height = 900;
                RightBorder.x = 1550, RightBorder.y = 0, RightBorder.width = 50, RightBorder.height = 900;
                TopBorder.x = 0, TopBorder.y = 0, TopBorder.width = 1600, TopBorder.height = 50;
                BottomBorder.x = 0, BottomBorder.y = 700, BottomBorder.width = 1600, BottomBorder.height = 50;
   
                if (CheckCollisionRecs(PlayerHitbox, TopBorder))    Player.y += playerSpeed; // Top
                if (CheckCollisionRecs(PlayerHitbox, BottomBorder)) Player.y -= playerSpeed; // Bottom
                if (CheckCollisionRecs(PlayerHitbox, LeftBorder))   Player.x += playerSpeed; // Left
                if (CheckCollisionRecs(PlayerHitbox, RightBorder))  Player.x -= playerSpeed; // Right
                
                DrawRectangle(1110, 320, 170, 20, RED);
                DrawRectangle(50, 680, 1500, 20, RED);
                
                struct Rectangle m_F2 = {1110, 320, 170, 20};
                struct Rectangle m_mainF1 = {50, 680, 1500, 20};
                
                if (CheckCollisionRecs(PlayerHitbox, m_F2)) {
                    currentMap = 6;
                    Player.x = 800, Player.y = 450;
                }
                if (CheckCollisionRecs(PlayerHitbox, m_mainF1)) {
                    currentMap = 1;
                    Player.y = 75;
                }
                
                DrawText("M", 80, 80, 40, RED);
                break;
            
            
            case 4: break;
            
            case 5:
                DrawRectangle(0, 0, 1600, 50, BLACK);
                DrawRectangle(0, 700, 1600, 50, BLACK);
                DrawRectangle(0, 0, 50, 900, BLACK);
                DrawRectangle(1550, 0, 50, 900, BLACK);
                
                TopBorder.x = 0, TopBorder.y = 0, TopBorder.width = 1600, TopBorder.height = 50;
                BottomBorder.x = 0, BottomBorder.y = 700, BottomBorder.width = 1600, BottomBorder.height = 50;
                LeftBorder.x = 0, LeftBorder.y = 0, LeftBorder.width = 50, LeftBorder.height = 900;
                RightBorder.x = 1550, RightBorder.y = 0, RightBorder.width = 50, RightBorder.height = 900;
                
                if (CheckCollisionRecs(PlayerHitbox, TopBorder))    Player.y += playerSpeed; // Top
                if (CheckCollisionRecs(PlayerHitbox, BottomBorder)) Player.y -= playerSpeed; // Bottom
                if (CheckCollisionRecs(PlayerHitbox, LeftBorder))   Player.x += playerSpeed; // Left
                if (CheckCollisionRecs(PlayerHitbox, RightBorder))  Player.x -= playerSpeed; // Right
                
                DrawRectangle(550, 680, 450, 20, RED);
                struct Rectangle audi_subF1 = {550, 680, 450, 20};
                
                if (CheckCollisionRecs(PlayerHitbox, audi_subF1)) {
                    currentMap = 2;
                    Player.x = 1220, Player.y = 230;
                }
                
                if (day == 1){
                    DrawRectangle(NPCday1_T.x, NPCday1_T.y, 50, 50, MAGENTA);
                    if (CheckCollisionRecs(PlayerHitbox, NPCday1_T_h) && IsKeyPressed(KEY_SPACE) && day == 1) {
                        strcpy(currentDialogue, NPCday1_T.dialogue[NPCday1_T.dialogueCounter]);           
                        NPCday1_T.dialogueCounter++;
                        counter_score_day++;                                                    
                        if (NPCday1_T.dialogueCounter > 4) NPCday1_T.dialogueCounter = 0;
                        if (counter_score_day == 1) score += 10;
                }
                }
                
                if (day == 7){
                    DrawRectangle(NPCday7_T.x, NPCday7_T.y, 50, 50, MAGENTA);
                    if (CheckCollisionRecs(PlayerHitbox, NPCday7_T_h) && IsKeyPressed(KEY_SPACE) && day == 7) {
                        strcpy(currentDialogue, NPCday7_T.dialogue[NPCday7_T.dialogueCounter]);           
                        NPCday7_T.dialogueCounter++;
                        counter_score_day++;                                                       
                        if (NPCday7_T.dialogueCounter > 4) NPCday2_T.dialogueCounter = 0;
                        if (counter_score_day == 1) score += 10;
                }
                }
                
                
                DrawText("Audi", 80, 80, 40, RED);
                break;
                
            case 6:
                DrawRectangle(0, 0, 1600, 50, BLACK);
                DrawRectangle(0, 700, 1600, 50, BLACK);
                DrawRectangle(0, 0, 50, 900, BLACK);
                DrawRectangle(1550, 0, 50, 900, BLACK);
                DrawRectangle(400, 0, 800, 300, BLACK);
                
                TopBorder.x = 0, TopBorder.y = 0, TopBorder.width = 1600, TopBorder.height = 50;
                BottomBorder.x = 0, BottomBorder.y = 700, BottomBorder.width = 1600, BottomBorder.height = 50;
                LeftBorder.x = 0, LeftBorder.y = 0, LeftBorder.width = 50, LeftBorder.height = 900;
                RightBorder.x = 1560, RightBorder.y = 0, RightBorder.width = 50, RightBorder.height = 900;
                
                struct Rectangle left = {410, 0, 20, 300};
                struct Rectangle right = {1180, 0, 20, 300};
                struct Rectangle bottom = {400, 260, 800, 20};
                
                if (CheckCollisionRecs(PlayerHitbox, TopBorder) || CheckCollisionRecs(PlayerHitbox, bottom))    Player.y += playerSpeed; // Top
                if (CheckCollisionRecs(PlayerHitbox, BottomBorder)) Player.y -= playerSpeed; // Bottom
                if (CheckCollisionRecs(PlayerHitbox, LeftBorder) || CheckCollisionRecs(PlayerHitbox, right))   Player.x += playerSpeed; // Left                    
                if (CheckCollisionRecs(PlayerHitbox, RightBorder) || CheckCollisionRecs(PlayerHitbox, left))  Player.x -= playerSpeed; // Right
            
                DrawRectangle(700, 300, 200, 20, RED); // UP
                DrawRectangle(1000, 300, 200, 20, RED); // DOWN
                
                DrawRectangle(50, 100, 20, 200, RED); // LEFT
                DrawRectangle(50, 400, 20, 200, RED);
                
                DrawRectangle(1530, 100, 20, 200, RED); // RIGHT
                DrawRectangle(1530, 400, 20, 200, RED);
                
                struct Rectangle f2_m = {1000, 300, 200, 20};
                struct Rectangle f2_f3 = {700, 300, 200, 20};
                
                struct Rectangle f2_21 = {50, 100, 20, 200};
                struct Rectangle f2_22 = {50, 400, 20, 200};
                
                struct Rectangle f2_23 = {1530, 100, 20, 200};
                struct Rectangle f2_24 = {1530, 400, 20, 200};
                
                if (CheckCollisionRecs(PlayerHitbox, f2_m)) {
                    currentMap = 3;
                    Player.x = 800, Player.y = 450;
                }
                
                if (CheckCollisionRecs(PlayerHitbox, f2_f3)) {
                    currentMap = 7;
                    Player.x = 800, Player.y = 450;
                }
                
                if (CheckCollisionRecs(PlayerHitbox, f2_21)) {
                    currentMap = 21;
                }
                
                if (CheckCollisionRecs(PlayerHitbox, f2_22) || CheckCollisionRecs(PlayerHitbox, f2_23) || CheckCollisionRecs(PlayerHitbox, f2_24)) {
                    strcpy(currentDialogue, "It's Lock");
                }
                DrawRectangle(NPCday1_f2.x, NPCday1_f2.y, 50, 50, MAGENTA);

                if (CheckCollisionRecs(PlayerHitbox, NPCday1_f2_h) && IsKeyPressed(KEY_SPACE) && day == 1) {
                    strcpy(currentDialogue, NPCday1_f2.dialogue[NPCday1_f2.dialogueCounter]);           
                    NPCday1_f2.dialogueCounter++;                                                    
                    if (NPCday1_f2.dialogueCounter > 4) NPCday1_f2.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday2_f2_h) && IsKeyPressed(KEY_SPACE) && day == 2) {
                    strcpy(currentDialogue, NPCday2_f2.dialogue[NPCday2_f2.dialogueCounter]);           
                    NPCday2_f2.dialogueCounter++;                                                    
                    if (NPCday2_f2.dialogueCounter > 4) NPCday2_f2.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday3_f2_h) && IsKeyPressed(KEY_SPACE) && day == 3) {
                    strcpy(currentDialogue, NPCday3_f2.dialogue[NPCday3_f2.dialogueCounter]);           
                    NPCday3_f2.dialogueCounter++;                                                    
                    if (NPCday3_f2.dialogueCounter > 4) NPCday3_f2.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday4_f2_h) && IsKeyPressed(KEY_SPACE) && day == 4) {
                    strcpy(currentDialogue, NPCday4_f2.dialogue[NPCday4_f2.dialogueCounter]);           
                    NPCday4_f2.dialogueCounter++;                                                    
                    if (NPCday4_f2.dialogueCounter > 4) NPCday4_f2.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday5_f2_h) && IsKeyPressed(KEY_SPACE) && day == 5) {
                    strcpy(currentDialogue, NPCday5_f2.dialogue[NPCday5_f2.dialogueCounter]);           
                    NPCday5_f2.dialogueCounter++;                                                    
                    if (NPCday5_f2.dialogueCounter > 4) NPCday5_f2.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday6_f2_h) && IsKeyPressed(KEY_SPACE) && day == 6) {
                    strcpy(currentDialogue, NPCday6_f2.dialogue[NPCday6_f2.dialogueCounter]);           
                    NPCday6_f2.dialogueCounter++;                                                    
                    if (NPCday6_f2.dialogueCounter > 4) NPCday6_f2.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday7_f2_h) && IsKeyPressed(KEY_SPACE) && day == 7) {
                    strcpy(currentDialogue, NPCday7_f2.dialogue[NPCday7_f2.dialogueCounter]);           
                    NPCday7_f2.dialogueCounter++;                                                    
                    if (NPCday7_f2.dialogueCounter > 4) NPCday7_f2.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday8_f2_h) && IsKeyPressed(KEY_SPACE) && day == 8) {
                    strcpy(currentDialogue, NPCday8_f2.dialogue[NPCday8_f2.dialogueCounter]);           
                    NPCday8_f2.dialogueCounter++;                                                    
                    if (NPCday8_f2.dialogueCounter > 4) NPCday8_f2.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday9_f2_h) && IsKeyPressed(KEY_SPACE) && day == 9) {
                    strcpy(currentDialogue, NPCday9_f2.dialogue[NPCday9_f2.dialogueCounter]);           
                    NPCday9_f2.dialogueCounter++;                                                    
                    if (NPCday9_f2.dialogueCounter > 4) NPCday9_f2.dialogueCounter = 0;
                }
                
             
                if (CheckCollisionRecs(PlayerHitbox, NPCday10_f2_h) && IsKeyPressed(KEY_SPACE) && day == 10) {
                    strcpy(currentDialogue, NPCday10_f2.dialogue[NPCday10_f2.dialogueCounter]);           
                    NPCday10_f2.dialogueCounter++;                                                    
                    if (NPCday10_f2.dialogueCounter > 4) NPCday10_f2.dialogueCounter = 0;
                }
                        
                
                DrawText("F2", 80, 80, 40, RED);
                break;
                    
            case 7:
                DrawRectangle(0, 0, 1600, 50, BLACK);
                DrawRectangle(0, 700, 1600, 50, BLACK);
                DrawRectangle(0, 0, 50, 900, BLACK);
                DrawRectangle(1550, 0, 50, 900, BLACK);
                DrawRectangle(400, 0, 800, 300, BLACK);
                
                TopBorder.x = 0, TopBorder.y = 0, TopBorder.width = 1600, TopBorder.height = 50;
                BottomBorder.x = 0, BottomBorder.y = 700, BottomBorder.width = 1600, BottomBorder.height = 50;
                LeftBorder.x = 0, LeftBorder.y = 0, LeftBorder.width = 50, LeftBorder.height = 900;
                RightBorder.x = 1560, RightBorder.y = 0, RightBorder.width = 50, RightBorder.height = 900;
                
                struct Rectangle leftF3 = {410, 0, 20, 300};
                struct Rectangle rightF3 = {1180, 0, 20, 300};
                struct Rectangle bottomF3 = {400, 260, 800, 20};
                
                if (CheckCollisionRecs(PlayerHitbox, TopBorder) || CheckCollisionRecs(PlayerHitbox, bottomF3))    Player.y += playerSpeed; // Top
                if (CheckCollisionRecs(PlayerHitbox, BottomBorder)) Player.y -= playerSpeed; // Bottom
                if (CheckCollisionRecs(PlayerHitbox, LeftBorder) || CheckCollisionRecs(PlayerHitbox, rightF3))   Player.x += playerSpeed; // Left                    
                if (CheckCollisionRecs(PlayerHitbox, RightBorder) || CheckCollisionRecs(PlayerHitbox, leftF3))  Player.x -= playerSpeed; // Right
            
                DrawRectangle(700, 300, 200, 20, RED); // UP
                DrawRectangle(1000, 300, 200, 20, RED); // DOWN
                
                DrawRectangle(50, 100, 20, 200, RED); // LEFT
                DrawRectangle(50, 400, 20, 200, RED);
                
                DrawRectangle(1530, 100, 20, 200, RED); // RIGHT
                DrawRectangle(1530, 400, 20, 200, RED);
                
                struct Rectangle f3_f2 = {1000, 300, 200, 20};
                struct Rectangle f3_f5 = {700, 300, 200, 20};
                
                struct Rectangle f3_f31 = {50, 100, 20, 200};
                struct Rectangle f3_f32 = {50, 400, 20, 200};
                
                struct Rectangle f3_f33 = {1530, 100, 20, 200};
                struct Rectangle f3_f34 = {1530, 400, 20, 200};
                
                if (CheckCollisionRecs(PlayerHitbox, f3_f2)) {
                    currentMap = 6;
                    Player.x = 800, Player.y = 450;
                }
                
                if (CheckCollisionRecs(PlayerHitbox, f3_f5)) {
                    currentMap = 9;
                    Player.x = 800, Player.y = 450;
                }
                
                if (CheckCollisionRecs(PlayerHitbox, f3_f33)) {
                    currentMap = 31;
                }
                
                if (CheckCollisionRecs(PlayerHitbox, f3_f31) || CheckCollisionRecs(PlayerHitbox, f3_f32) || CheckCollisionRecs(PlayerHitbox, f3_f34)) {
                    strcpy(currentDialogue, "It's Lock");
                }
                
                DrawRectangle(NPCday1_f3.x, NPCday1_f3.y, 50, 50, MAGENTA);

                if (CheckCollisionRecs(PlayerHitbox, NPCday1_f3_h) && IsKeyPressed(KEY_SPACE) && day == 1) {
                    strcpy(currentDialogue, NPCday1_f3.dialogue[NPCday1_f3.dialogueCounter]);           
                    NPCday1_f3.dialogueCounter++;                                                    
                    if (NPCday1_f3.dialogueCounter > 4) NPCday1_f3.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday2_f3_h) && IsKeyPressed(KEY_SPACE) && day == 2) {
                    strcpy(currentDialogue, NPCday2_f3.dialogue[NPCday2_f3.dialogueCounter]);           
                    NPCday2_f3.dialogueCounter++;                                                    
                    if (NPCday2_f3.dialogueCounter > 4) NPCday2_f3.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday3_f3_h) && IsKeyPressed(KEY_SPACE) && day == 3) {
                    strcpy(currentDialogue, NPCday3_f3.dialogue[NPCday3_f3.dialogueCounter]);           
                    NPCday3_f3.dialogueCounter++;                                                    
                    if (NPCday3_f3.dialogueCounter > 4) NPCday3_f3.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday4_f3_h) && IsKeyPressed(KEY_SPACE) && day == 4) {
                    strcpy(currentDialogue, NPCday4_f3.dialogue[NPCday4_f3.dialogueCounter]);           
                    NPCday4_f3.dialogueCounter++;                                                    
                    if (NPCday4_f3.dialogueCounter > 4) NPCday4_f3.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday5_f3_h) && IsKeyPressed(KEY_SPACE) && day == 5) {
                    strcpy(currentDialogue, NPCday5_f3.dialogue[NPCday5_f3.dialogueCounter]);           
                    NPCday5_f3.dialogueCounter++;                                                    
                    if (NPCday5_f3.dialogueCounter > 4) NPCday5_f3.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday6_f3_h) && IsKeyPressed(KEY_SPACE) && day == 6) {
                    strcpy(currentDialogue, NPCday6_f3.dialogue[NPCday6_f3.dialogueCounter]);           
                    NPCday6_f3.dialogueCounter++;                                                    
                    if (NPCday6_f3.dialogueCounter > 4) NPCday6_f3.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday7_f3_h) && IsKeyPressed(KEY_SPACE) && day == 7) {
                    strcpy(currentDialogue, NPCday7_f3.dialogue[NPCday7_f3.dialogueCounter]);           
                    NPCday7_f3.dialogueCounter++;                                                    
                    if (NPCday7_f3.dialogueCounter > 4) NPCday7_f3.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday8_f3_h) && IsKeyPressed(KEY_SPACE) && day == 8) {
                    strcpy(currentDialogue, NPCday8_f3.dialogue[NPCday8_f3.dialogueCounter]);           
                    NPCday8_f3.dialogueCounter++;                                                    
                    if (NPCday8_f3.dialogueCounter > 4) NPCday8_f3.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday9_f3_h) && IsKeyPressed(KEY_SPACE) && day == 9) {
                    strcpy(currentDialogue, NPCday9_f3.dialogue[NPCday9_f3.dialogueCounter]);           
                    NPCday9_f3.dialogueCounter++;                                                    
                    if (NPCday9_f3.dialogueCounter > 4) NPCday9_f3.dialogueCounter = 0;
                }
                
             
                if (CheckCollisionRecs(PlayerHitbox, NPCday10_f3_h) && IsKeyPressed(KEY_SPACE) && day == 10) {
                    strcpy(currentDialogue, NPCday10_f3.dialogue[NPCday10_f3.dialogueCounter]);           
                    NPCday10_f3.dialogueCounter++;                                                    
                    if (NPCday10_f3.dialogueCounter > 4) NPCday10_f3.dialogueCounter = 0;
                }
                        
                
                DrawText("F3", 80, 80, 40, RED);
                break;
            
            case 9:
                DrawRectangle(0, 0, 1600, 50, BLACK);
                DrawRectangle(0, 700, 1600, 50, BLACK);
                DrawRectangle(0, 0, 50, 900, BLACK);
                DrawRectangle(1550, 0, 50, 900, BLACK);
                DrawRectangle(400, 0, 800, 300, BLACK);
                
                TopBorder.x = 0, TopBorder.y = 0, TopBorder.width = 1600, TopBorder.height = 50;
                BottomBorder.x = 0, BottomBorder.y = 700, BottomBorder.width = 1600, BottomBorder.height = 50;
                LeftBorder.x = 0, LeftBorder.y = 0, LeftBorder.width = 50, LeftBorder.height = 900;
                RightBorder.x = 1560, RightBorder.y = 0, RightBorder.width = 50, RightBorder.height = 900;
                
                struct Rectangle leftF5 = {410, 0, 20, 300};
                struct Rectangle rightF5 = {1180, 0, 20, 300};
                struct Rectangle bottomF5 = {400, 260, 800, 20};
                
                if (CheckCollisionRecs(PlayerHitbox, TopBorder) || CheckCollisionRecs(PlayerHitbox, bottomF5))    Player.y += playerSpeed; // Top
                if (CheckCollisionRecs(PlayerHitbox, BottomBorder)) Player.y -= playerSpeed; // Bottom
                if (CheckCollisionRecs(PlayerHitbox, LeftBorder) || CheckCollisionRecs(PlayerHitbox, rightF5))   Player.x += playerSpeed; // Left                    
                if (CheckCollisionRecs(PlayerHitbox, RightBorder) || CheckCollisionRecs(PlayerHitbox, leftF5))  Player.x -= playerSpeed; // Right
            
                DrawRectangle(1000, 300, 200, 20, RED); // DOWN
                
                DrawRectangle(50, 100, 20, 200, RED); // LEFT
                DrawRectangle(50, 400, 20, 200, RED);
                
                DrawRectangle(1530, 100, 20, 200, RED); // RIGHT
                DrawRectangle(1530, 400, 20, 200, RED);
                
                struct Rectangle f5_f3 = {1000, 300, 200, 20};
                
                struct Rectangle f5_51 = {50, 100, 20, 200};
                struct Rectangle f5_52 = {50, 400, 20, 200};
                
                struct Rectangle f5_53 = {1530, 100, 20, 200};
                struct Rectangle f5_54 = {1530, 400, 20, 200};
                
                if (CheckCollisionRecs(PlayerHitbox, f5_f3)) {
                    currentMap = 7;
                    Player.x = 800, Player.y = 450;
                } 
                if (CheckCollisionRecs(PlayerHitbox, f5_54)) {
                    currentMap = 51;
                }
                if (CheckCollisionRecs(PlayerHitbox, f5_51) || CheckCollisionRecs(PlayerHitbox, f5_52) || CheckCollisionRecs(PlayerHitbox, f5_53)) {
                    strcpy(currentDialogue, "It's Lock");
                }
                
                DrawRectangle(NPCday1_f5.x, NPCday1_f5.y, 50, 50, MAGENTA);

                if (CheckCollisionRecs(PlayerHitbox, NPCday1_f5_h) && IsKeyPressed(KEY_SPACE) && day == 1) {
                    strcpy(currentDialogue, NPCday1_f5.dialogue[NPCday1_f5.dialogueCounter]);           
                    NPCday1_f5.dialogueCounter++;                                                    
                    if (NPCday1_f5.dialogueCounter > 4) NPCday1_f5.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday2_f5_h) && IsKeyPressed(KEY_SPACE) && day == 2) {
                    strcpy(currentDialogue, NPCday2_f5.dialogue[NPCday2_f5.dialogueCounter]);           
                    NPCday2_f5.dialogueCounter++;                                                    
                    if (NPCday2_f5.dialogueCounter > 4) NPCday2_f5.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday3_f5_h) && IsKeyPressed(KEY_SPACE) && day == 3) {
                    strcpy(currentDialogue, NPCday3_f5.dialogue[NPCday3_f5.dialogueCounter]);           
                    NPCday3_f5.dialogueCounter++;                                                    
                    if (NPCday3_f5.dialogueCounter > 4) NPCday3_f5.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday4_f5_h) && IsKeyPressed(KEY_SPACE) && day == 4) {
                    strcpy(currentDialogue, NPCday4_f5.dialogue[NPCday4_f5.dialogueCounter]);           
                    NPCday4_f5.dialogueCounter++;                                                    
                    if (NPCday4_f5.dialogueCounter > 4) NPCday4_f5.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday5_f5_h) && IsKeyPressed(KEY_SPACE) && day == 5) {
                    strcpy(currentDialogue, NPCday5_f5.dialogue[NPCday5_f5.dialogueCounter]);           
                    NPCday5_f5.dialogueCounter++;                                                    
                    if (NPCday5_f5.dialogueCounter > 4) NPCday5_f5.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday6_f5_h) && IsKeyPressed(KEY_SPACE) && day == 6) {
                    strcpy(currentDialogue, NPCday6_f5.dialogue[NPCday6_f5.dialogueCounter]);           
                    NPCday6_f5.dialogueCounter++;                                                    
                    if (NPCday6_f5.dialogueCounter > 4) NPCday6_f5.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday7_f5_h) && IsKeyPressed(KEY_SPACE) && day == 7) {
                    strcpy(currentDialogue, NPCday7_f5.dialogue[NPCday7_f5.dialogueCounter]);           
                    NPCday7_f5.dialogueCounter++;                                                    
                    if (NPCday7_f5.dialogueCounter > 4) NPCday7_f5.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday8_f5_h) && IsKeyPressed(KEY_SPACE) && day == 8) {
                    strcpy(currentDialogue, NPCday8_f5.dialogue[NPCday8_f5.dialogueCounter]);           
                    NPCday8_f5.dialogueCounter++;                                                    
                    if (NPCday8_f5.dialogueCounter > 4) NPCday8_f5.dialogueCounter = 0;
                }
                
            
                if (CheckCollisionRecs(PlayerHitbox, NPCday9_f5_h) && IsKeyPressed(KEY_SPACE) && day == 9) {
                    strcpy(currentDialogue, NPCday9_f5.dialogue[NPCday9_f5.dialogueCounter]);           
                    NPCday9_f5.dialogueCounter++;                                                    
                    if (NPCday9_f5.dialogueCounter > 4) NPCday9_f5.dialogueCounter = 0;
                }
                
             
                if (CheckCollisionRecs(PlayerHitbox, NPCday10_f5_h) && IsKeyPressed(KEY_SPACE) && day == 10) {
                    strcpy(currentDialogue, NPCday10_f5.dialogue[NPCday10_f5.dialogueCounter]);           
                    NPCday10_f5.dialogueCounter++;                                                    
                    if (NPCday10_f5.dialogueCounter > 4) NPCday10_f5.dialogueCounter = 0;
                }
                        
                
                
                DrawText("F5", 80, 80, 40, RED);
                break;
                
            case 21:
            
                DrawRectangle(0, 0, 1600, 50, BLACK);
                DrawRectangle(0, 700, 1600, 50, BLACK);
                DrawRectangle(0, 0, 50, 900, BLACK);
                DrawRectangle(1550, 0, 50, 900, BLACK);
                
                LeftBorder.x = 0, LeftBorder.y = 0, LeftBorder.width = 50, LeftBorder.height = 900;
                RightBorder.x = 1550, RightBorder.y = 0, RightBorder.width = 50, RightBorder.height = 900;
                TopBorder.x = 0, TopBorder.y = 0, TopBorder.width = 1600, TopBorder.height = 50;
                BottomBorder.x = 0, BottomBorder.y = 700, BottomBorder.width = 1600, BottomBorder.height = 50;
   
                if (CheckCollisionRecs(PlayerHitbox, TopBorder))    Player.y += playerSpeed; // Top
                if (CheckCollisionRecs(PlayerHitbox, BottomBorder)) Player.y -= playerSpeed; // Bottom
                if (CheckCollisionRecs(PlayerHitbox, LeftBorder))   Player.x += playerSpeed; // Left
                if (CheckCollisionRecs(PlayerHitbox, RightBorder))  Player.x -= playerSpeed; // Right
                
                DrawRectangle(1530, 550, 20, 100, RED);
                
                struct Rectangle r21_f2 = {1530, 550, 20, 100};
                
                if (CheckCollisionRecs(PlayerHitbox, r21_f2)) {
                    currentMap = 6;
                    Player.x = 800, Player.y = 450;
                }
                
                if (day == 2){
                    DrawRectangle(NPCday2_T.x, NPCday2_T.y, 50, 50, MAGENTA);
                    if (CheckCollisionRecs(PlayerHitbox, NPCday2_T_h) && IsKeyPressed(KEY_SPACE) && day == 2) {
                        strcpy(currentDialogue, NPCday2_T.dialogue[NPCday2_T.dialogueCounter]);           
                        NPCday2_T.dialogueCounter++;
                        counter_score_day++;                                                       
                        if (NPCday2_T.dialogueCounter > 4) NPCday2_T.dialogueCounter = 0;
                        if (counter_score_day == 1) score += 10;
                }
                }
                
                if (day == 3){
                    DrawRectangle(NPCday3_T.x, NPCday3_T.y, 50, 50, MAGENTA);
                    if (CheckCollisionRecs(PlayerHitbox, NPCday3_T_h) && IsKeyPressed(KEY_SPACE) && day == 3) {
                        strcpy(currentDialogue, NPCday3_T.dialogue[NPCday3_T.dialogueCounter]);           
                        NPCday3_T.dialogueCounter++;
                        counter_score_day++;                                                       
                        if (NPCday3_T.dialogueCounter > 4) NPCday2_T.dialogueCounter = 0;
                        if (counter_score_day == 1) score += 10;
                }
                }
                
                if (day == 6){
                    DrawRectangle(NPCday6_T.x, NPCday6_T.y, 50, 50, MAGENTA);
                    if (CheckCollisionRecs(PlayerHitbox, NPCday6_T_h) && IsKeyPressed(KEY_SPACE) && day == 6) {
                        strcpy(currentDialogue, NPCday6_T.dialogue[NPCday6_T.dialogueCounter]);           
                        NPCday6_T.dialogueCounter++;
                        counter_score_day++;                                                       
                        if (NPCday6_T.dialogueCounter > 4) NPCday2_T.dialogueCounter = 0;
                        if (counter_score_day == 1) score += 10;
                }
                }
                
                if (day == 8){
                    DrawRectangle(NPCday8_T.x, NPCday8_T.y, 50, 50, MAGENTA);
                    if (CheckCollisionRecs(PlayerHitbox, NPCday8_T_h) && IsKeyPressed(KEY_SPACE) && day == 8) {
                        strcpy(currentDialogue, NPCday8_T.dialogue[NPCday8_T.dialogueCounter]);           
                        NPCday8_T.dialogueCounter++;
                        counter_score_day++;                                                  
                        if (NPCday8_T.dialogueCounter > 4) NPCday2_T.dialogueCounter = 0;
                        if (counter_score_day == 1) score += 10;
                }
                }
                
                if (day == 9){
                    DrawRectangle(NPCday9_T.x, NPCday9_T.y, 50, 50, MAGENTA);
                    if (CheckCollisionRecs(PlayerHitbox, NPCday9_T_h) && IsKeyPressed(KEY_SPACE) && day == 9) {
                        strcpy(currentDialogue, NPCday9_T.dialogue[NPCday9_T.dialogueCounter]);           
                        NPCday9_T.dialogueCounter++;
                        counter_score_day++;                                                       
                        if (NPCday9_T.dialogueCounter > 4) NPCday2_T.dialogueCounter = 0;
                        if (counter_score_day == 1) score += 10;
                }
                }
                
                DrawText("21", 80, 80, 40, RED);
                break;
                
                
            case 31:
            
                DrawRectangle(0, 0, 1600, 50, BLACK);
                DrawRectangle(0, 700, 1600, 50, BLACK);
                DrawRectangle(0, 0, 50, 900, BLACK);
                DrawRectangle(1550, 0, 50, 900, BLACK);
                
                LeftBorder.x = 0, LeftBorder.y = 0, LeftBorder.width = 50, LeftBorder.height = 900;
                RightBorder.x = 1550, RightBorder.y = 0, RightBorder.width = 50, RightBorder.height = 900;
                TopBorder.x = 0, TopBorder.y = 0, TopBorder.width = 1600, TopBorder.height = 50;
                BottomBorder.x = 0, BottomBorder.y = 700, BottomBorder.width = 1600, BottomBorder.height = 50;
   
                if (CheckCollisionRecs(PlayerHitbox, TopBorder))    Player.y += playerSpeed; // Top
                if (CheckCollisionRecs(PlayerHitbox, BottomBorder)) Player.y -= playerSpeed; // Bottom
                if (CheckCollisionRecs(PlayerHitbox, LeftBorder))   Player.x += playerSpeed; // Left
                if (CheckCollisionRecs(PlayerHitbox, RightBorder))  Player.x -= playerSpeed; // Right
                
                DrawRectangle(50, 550, 20, 100, RED);
                
                struct Rectangle r31_f3 = {50, 550, 20, 100};
                
                if (CheckCollisionRecs(PlayerHitbox, r31_f3)) {
                    currentMap = 7;
                    Player.x = 800, Player.y = 450;
                }
                
                if (day == 4){
                    DrawRectangle(NPCday4_T.x, NPCday4_T.y, 50, 50, MAGENTA);
                    if (CheckCollisionRecs(PlayerHitbox, NPCday4_T_h) && IsKeyPressed(KEY_SPACE) && day == 4) {
                        strcpy(currentDialogue, NPCday4_T.dialogue[NPCday4_T.dialogueCounter]);           
                        NPCday4_T.dialogueCounter++;
                        counter_score_day++;                                                       
                        if (NPCday4_T.dialogueCounter > 4) NPCday2_T.dialogueCounter = 0;
                        if (counter_score_day == 1) score += 10;
                }
                }
                
                DrawText("31", 80, 80, 40, RED);
                break;
            
            case 51:
                DrawRectangle(0, 0, 1600, 50, BLACK);
                DrawRectangle(0, 700, 1600, 50, BLACK);
                DrawRectangle(0, 0, 50, 900, BLACK);
                DrawRectangle(1550, 0, 50, 900, BLACK);
                
                LeftBorder.x = 0, LeftBorder.y = 0, LeftBorder.width = 50, LeftBorder.height = 900;
                RightBorder.x = 1550, RightBorder.y = 0, RightBorder.width = 50, RightBorder.height = 900;
                TopBorder.x = 0, TopBorder.y = 0, TopBorder.width = 1600, TopBorder.height = 50;
                BottomBorder.x = 0, BottomBorder.y = 700, BottomBorder.width = 1600, BottomBorder.height = 50;
   
                if (CheckCollisionRecs(PlayerHitbox, TopBorder))    Player.y += playerSpeed; // Top
                if (CheckCollisionRecs(PlayerHitbox, BottomBorder)) Player.y -= playerSpeed; // Bottom
                if (CheckCollisionRecs(PlayerHitbox, LeftBorder))   Player.x += playerSpeed; // Left
                if (CheckCollisionRecs(PlayerHitbox, RightBorder))  Player.x -= playerSpeed; // Right
                
                DrawRectangle(50, 550, 20, 100, RED);
                
                struct Rectangle r51_f5 = {50, 550, 20, 100};
                
                if (CheckCollisionRecs(PlayerHitbox, r51_f5)) {
                    currentMap = 9;
                    Player.x = 800, Player.y = 450;
                }
                
                DrawText("51", 80, 80, 40, RED);
                break;

            default: ;
        }
/*
                        ------- Draw Main Component -------
                         NOTE : Low layer component must be render first!
                         Layer : Low ----> High
                            1 : Map Border
                            2 : Dialogue Box
                            3 : Player
                            4 : NPC
                            5 : Dialogue Text                                                                          */
                         
            DrawRectangle(75, 775, 1450, 100, BLACK);                                     // Dialogue Box    
            DrawRectangle(Player.x, Player.y, Player.width, Player.height, PINK);         // Draw Player
            
                sprintf(xPos, "%d", Player.x), sprintf(yPos, "%d", Player.y), sprintf(DAYPos, "%d", day), sprintf(ScorePos, "%d", score);;;
                DrawText(xPos, 80, 150, 20, RED);
                DrawText(yPos, 80, 170, 20, RED);
                DrawText("DAY", 80, 190, 20, RED);
                DrawText(DAYPos, 140, 190, 20, RED);
                DrawText("score", 80, 210, 20, RED);
                DrawText(ScorePos, 140, 210, 20, RED);
            }
            else{
                DrawRectangle(0, 0, 1600, 900, BLACK);
                currentMap = 1;
                strcpy(currentDialogue, " ");
                if(score >= 80){
                    DrawText("A", 700, 300, 300, RED);
                }
                if((score >= 70) && (score < 80)){
                    DrawText("B", 700, 300, 300, RED);
                }
                if((score >= 60) && (score < 70)){
                    DrawText("C", 700, 300, 300, RED);
                }
                if((score >= 50) && (score < 60)){
                    DrawText("D", 700, 300, 300, RED);
                }
                if((score >= 40) && (score < 50)){
                    DrawText("F", 700, 300, 300, RED);
                }
                if(score < 40){
                    DrawText("Retry", 350, 300, 300, RED);
                }
            }

                            // ------- Draw Dialogue -------          
            DrawText(currentDialogue, DIALOGUE_X, DIALOGUE_Y, 20, RED); // Draw dialogue
            

        EndDrawing();
    }
    
/*              
                TopBorder.x = 0, TopBorder.y = 0, TopBorder.width = 1600, TopBorder.height = 50;
                BottomBorder.x = 0, BottomBorder.y = 700, BottomBorder.width = 1600, BottomBorder.height = 50;
                LeftBorder.x = 0, LeftBorder.y = 0, LeftBorder.width = 50, LeftBorder.height = 900;
                RightBorder.x = 1550, RightBorder.y = 0, RightBorder.width = 50, RightBorder.height = 900;
*/

    
    
    
    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
