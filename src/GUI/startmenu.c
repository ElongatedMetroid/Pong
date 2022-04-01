#include <GUI/startmenu.h>

void ShowTitleGui(GameScreen *gameScreen){
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GREEN);

    DrawText("Ultimate Pong", SCREEN_WIDTH/5, SCREEN_HEIGHT/6, 100, GRAY);

    Rectangle StartButtonRect = { };
    StartButtonRect.width = SCREEN_WIDTH/4;
    StartButtonRect.height = SCREEN_HEIGHT/6;
    StartButtonRect.x = SCREEN_WIDTH/2 - StartButtonRect.width/2;
    StartButtonRect.y = SCREEN_HEIGHT/2 - StartButtonRect.height;

    if(GuiButton(StartButtonRect, "START")){
        *gameScreen = GAMEPLAY;
    }

    Rectangle SettingsButtonRect = { StartButtonRect.x, StartButtonRect.y + StartButtonRect.width/2, StartButtonRect.width, StartButtonRect.height};

    if(GuiButton(SettingsButtonRect, "SETTINGS")){
        //ShowSettingsGui(gameScreen);
    }

    Rectangle QuitButtonRect = { SettingsButtonRect.x, SettingsButtonRect.y + SettingsButtonRect.width/2, SettingsButtonRect.width, SettingsButtonRect.height};

    if(GuiButton(QuitButtonRect, "QUIT")){
        CloseWindow();
        exit(EXIT_SUCCESS);
    }
}