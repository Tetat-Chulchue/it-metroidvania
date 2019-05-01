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
    
    int playerSpeed = 10;
    int currentMap = 1;
    char currentDialogue[256] = {'\0'};
    
    // ---------- Struct ----------
    
    struct Entity {
        int type;         // Entity Type
        int x;            // 1 : Player
        int y;            // 2 : NPC
        int width;
        int height;
        bool isHitWall;
        int dialogueCounter;
        char dialogue[5][MAX_DIALOGUE_CHAR];
    };

    struct Prop {
        int type;         // Prop Type 
        int x;            // 0 : No Collision
        int y;            // 1 : Collision
        int width;
        int height;
    };
    
    struct Entity Player     = {1, 800, 450, 50, 50, false, 0, {"", "", "", "", ""}}; // Declare a "Player" Entity

    struct Entity TestNPC    = {2, 450, 200, 50, 50, false, 0, {"FUCK", "OFF", "DONT", "MASS", "WITH ME"}};

    struct Rectangle PlayerHitbox   = {Player.x, Player.y, Player.width, Player.height};
    struct Rectangle TestNPCHitbox  = {TestNPC.x - 50, TestNPC.y - 50, 150, 150};
    
    struct Rectangle LeftBorder   = {0, 0, 0, 0};
    struct Rectangle RightBorder  = {0, 0, 0, 0};
    struct Rectangle TopBorder    = {0, 0, 0, 0};
    struct Rectangle BottomBorder = {0, 0, 0, 0};
   

    // ---------- Main game loop ----------

    while (!WindowShouldClose()) {
       
        // ---------- Controller ----------

        if (IsKeyDown(KEY_W)) Player.y -= playerSpeed; // Up
 
        if (IsKeyDown(KEY_S)) Player.y += playerSpeed; // Down

        if (IsKeyDown(KEY_A)) Player.x -= playerSpeed; // Left

        if (IsKeyDown(KEY_D)) Player.x += playerSpeed; // Right
        
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
               
               RED : Warp
               BLUE : Obstacle
               BLACK : Map Border
               PINK : Player
*/
        switch (currentMap) {
            
            case 0: // Home
                
                DrawRectangle(0, 0, 400, 700, BLACK);
                DrawRectangle(1200, 0, 400, 700, BLACK);
                DrawRectangle(0, 0, 1600, 200, BLACK);
                DrawRectangle(0, 600, 1600, 150, BLACK);
                
                
                LeftBorder.x = 0, LeftBorder.y = 0, LeftBorder.width = 400, LeftBorder.height = 700;
                RightBorder.x = 1200, RightBorder.y = 0, RightBorder.width = 400, RightBorder.height = 700;
                TopBorder.x = 0, TopBorder.y = 0, TopBorder.width = 1600, TopBorder.height = 200;
                BottomBorder.x = 0, BottomBorder.y = 600, BottomBorder.width = 1600, BottomBorder.height = 150;
                
                DrawRectangle(1180, 250, 20, 100, RED);
                struct Rectangle toMainF1 = {1180, 250, 20, 100};
                
                if (CheckCollisionRecs(PlayerHitbox, TopBorder))    Player.y += playerSpeed; // Top
                if (CheckCollisionRecs(PlayerHitbox, BottomBorder)) Player.y -= playerSpeed; // Bottom
                if (CheckCollisionRecs(PlayerHitbox, LeftBorder))   Player.x += playerSpeed; // Left
                if (CheckCollisionRecs(PlayerHitbox, RightBorder))  Player.x -= playerSpeed; // Right
                
                if (CheckCollisionRecs(PlayerHitbox, toMainF1)) {
                    Player.x = 800, Player.y = 450;
                    currentMap = 1;
                }
                
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
                
                struct Rectangle toMFloor = {50, 50, 1500, 20};       // |
                struct Rectangle toCommonAudi = {1530, 450, 20, 250}; // | Warp Hitbox
                struct Rectangle toHome = {400, 680, 200, 20};        // |
                
                DrawRectangle(TestNPC.x, TestNPC.y, TestNPC.width, TestNPC.height, MAGENTA);
                DrawRectangleLines(TestNPCHitbox.x, TestNPCHitbox.y, TestNPCHitbox.width, TestNPCHitbox.height, BLUE);
                
                if (CheckCollisionRecs(PlayerHitbox, toHome)) {
                    currentMap = 0;
                    Player.x = 800, Player.y = 450;
                }
                if (CheckCollisionRecs(PlayerHitbox, toCommonAudi)) currentMap = 2;
                if (CheckCollisionRecs(PlayerHitbox, toMFloor)) currentMap     = 3;
                
                if (CheckCollisionRecs(PlayerHitbox, TestNPCHitbox) && IsKeyPressed(KEY_SPACE)) { // |
                    strcpy(currentDialogue, TestNPC.dialogue[TestNPC.dialogueCounter]);           // | Example of dialogue
                    TestNPC.dialogueCounter++;                                                    // | system of 1 NPC
                    if (TestNPC.dialogueCounter > 4) TestNPC.dialogueCounter = 0;                 // |
                }
                
                DrawText("Main F1", 80, 80, 40, RED);
                break;
            
            case 2: ;
            
            case 3: ;
            
            default: ;
        }
            
/*                         ------- Draw Main Component -------
                         NOTE : Low layer component must be render first!
                         Layer : Low ----> High
                            1 : Map Border
                            2 : Dialogue Box
                            3 : Player
                            4 : NPC
                            5 : Dialogue Text                                                                          */
                         
            DrawRectangle(75, 775, 1450, 100, BLACK);                                     // Dialogue Box    
            DrawRectangle(Player.x, Player.y, Player.width, Player.height, PINK);         // Draw Player
            
                            // ------- Draw Dialogue -------          
            DrawText(currentDialogue, DIALOGUE_X, DIALOGUE_Y, 20, RED); // Draw dialogue
            

        EndDrawing();
    }

    
    
    
    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
