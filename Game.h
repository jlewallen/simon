#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <Arduino.h>
#include "Speaker.h"
#include "Buttons.h"
#include "DemoMode.h"

#define GAME_ROUNDS_MAXIMUM                                   256

enum class GameState {
    WELCOME,
    WAITING,
    PLAYBACK,
    SUCCESS,
    FAIL,
    INACTIVE
};

class Game {
private:
    Buttons *buttons;
    DemoMode *demoMode;
    GameState state;
    uint8_t rounds[GAME_ROUNDS_MAXIMUM];
    int16_t maximumRoundNumber;
    int16_t roundNumber;
    uint32_t transitionAt;
    uint32_t lastButtonPressedAt;

public:
    Game(Buttons *buttons, DemoMode *demoMode);

public:
    void welcome();
    void startOver();
    void increase();
    void tick();

};

#endif
