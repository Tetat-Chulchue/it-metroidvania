#include <stdio.h>
#include <raylib.h>

   ////////////////////////////////////
  //    Hand-Crafted With Love ♥    //
 //         ---- Shib@ ----        //
////////////////////////////////////

int main() {
    
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1600;
    int screenHeight = 900;
    // 1 tile = 50 px ----> 32 tile * 18 tile

    InitWindow(screenWidth, screenHeight, "it-metroidvenia"); 
    SetTargetFPS(33);
    
    // ---------- Setting ----------
    
    int playerSpeed = 10;
    int startingMap = 1;
    
    // ---------- Struct ----------

    struct Entity {
        int type;         // Entity Type
        int x;            // 1 : Player
        int y;            // 2 : NPC
        int width;
        int height;
    };

    struct Prop {
        int type;         // Prop Type 
        int x;            // 0 : No Collision
        int y;            // 1 : Collision
        int width;
        int height;
    };
    
    struct Entity Player     = {1, 800, 450, 50, 50}; // Declare a "Player" Entity

    struct Entity TestNPC   = {2, 450, 200, 50, 50};

    struct Rectangle LeftBorder   = {0, 0, 50, 900};           // |
    struct Rectangle RightBorder  = {1550, 0, 50, 900};        // | Declare border for colision detect
    struct Rectangle TopBorder    = {0, 0, 1600, 50};          // |
    struct Rectangle BottomBorder = {0, 850, 1600, 50};        // |

    struct Rectangle PlayerHitbox = {Player.x, Player.y, Player.width, Player.height};
    struct Rectangle TestNPCHitbox      = {TestNPC.x - 50, TestNPC.y - 50, 150, 150};
   

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
        
        if (CheckCollisionRecs(PlayerHitbox, TestNPCHitbox)) {
            Player.x = 800;
            Player.y = 450;
        }

        
        // ---------- Draw ----------

        BeginDrawing();
        
        // ---------- Border Of Map ----------

            ClearBackground(RAYWHITE);
            for (int y = 0; y <= 850; y += 50) {
                for (int x = 0; x <= 1550; x += 50) {
                    if (x == 0 || x == 1550 || y == 0 || y == 850) {
                        DrawRectangle(x, y, 50, 50, BLACK); 
                    }
                }
            }
            
                
            DrawRectangle(Player.x, Player.y, Player.width, Player.height, PINK);
            DrawRectangle(TestNPC.x, TestNPC.y, TestNPC.width, TestNPC.height, MAGENTA);
            DrawRectangleLines(TestNPCHitbox.x, TestNPCHitbox.y, TestNPCHitbox.width, TestNPCHitbox.height, BLUE);

        EndDrawing();
    }

    
    
    
    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}