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
    int startingMap = 1;
    char currentDialogue[256] = {'\0'};
    
    // ---------- Struct ----------
    
    struct Entity {
        int type;         // Entity Type
        int x;            // 1 : Player
        int y;            // 2 : NPC
        int width;
        int height;
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
    
    struct Entity Player     = {1, 800, 450, 50, 50, 0, {"", "", "", "", ""}}; // Declare a "Player" Entity

    struct Entity TestNPC    = {2, 450, 200, 50, 50, 0, {"FUCK", "OFF", "DONT", "MASS", "WITH ME"}};

    struct Rectangle LeftBorder   = {0, 0, 50, 900};           // |
    struct Rectangle RightBorder  = {1550, 0, 50, 900};        // | Declare border for colision detect
    struct Rectangle TopBorder    = {0, 0, 1600, 50};          // |
    struct Rectangle BottomBorder = {0, 700, 1600, 50};        // |

    struct Rectangle PlayerHitbox   = {Player.x, Player.y, Player.width, Player.height};
    struct Rectangle TestNPCHitbox  = {TestNPC.x - 50, TestNPC.y - 50, 150, 150};
   

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
        
        // ---------- Colision Detect ----------
        
        if (CheckCollisionRecs(PlayerHitbox, TopBorder))    Player.y += playerSpeed; // Top
        if (CheckCollisionRecs(PlayerHitbox, BottomBorder)) Player.y -= playerSpeed; // Bottom
        if (CheckCollisionRecs(PlayerHitbox, LeftBorder))   Player.x += playerSpeed; // Left
        if (CheckCollisionRecs(PlayerHitbox, RightBorder))  Player.x -= playerSpeed; // Right

        
        // ---------- Draw ----------

        BeginDrawing();
        
        // ---------- Border Of Map ----------

            ClearBackground(RAYWHITE);
            for (int y = 0; y <= 850; y += 50) {
                for (int x = 0; x <= 1550; x += 50) {
                    if (x == 0 || x == 1550 || y == 0 || y == 700) {
                        DrawRectangle(x, y, 50, 50, BLACK); 
                    }
                }
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

                            // ------- Draw NPC -------
            DrawRectangle(TestNPC.x, TestNPC.y, TestNPC.width, TestNPC.height, MAGENTA);
            
                            // ------- Draw Dialogue -------
            if (CheckCollisionRecs(PlayerHitbox, TestNPCHitbox) && IsKeyPressed(KEY_SPACE)) { // |
                strcpy(currentDialogue, TestNPC.dialogue[TestNPC.dialogueCounter]);           // | Example of dialogue
                TestNPC.dialogueCounter++;                                                    // | system of 1 NPC
                if (TestNPC.dialogueCounter > 4) TestNPC.dialogueCounter = 0;                 // |
            }
            
            DrawText(currentDialogue, DIALOGUE_X, DIALOGUE_Y, 20, RED); // Draw dialogue
                            // ------- *TEST* -------
            
            DrawRectangleLines(TestNPCHitbox.x, TestNPCHitbox.y, TestNPCHitbox.width, TestNPCHitbox.height, BLUE);

        EndDrawing();
    }

    
    
    
    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}