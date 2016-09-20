#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <Arduino.h>
#include "Speaker.h"
#include "Buttons.h"

#define GAME_ROUNDS_MAXIMUM                                   256

enum class GameState {
    WELCOME,
    WAITING,
    PLAYBACK,
    SUCCESS,
    FAIL
};

class Game {
private:
    Buttons *buttons;
    GameState state;
    uint8_t rounds[GAME_ROUNDS_MAXIMUM];
    int16_t maximumRoundNumber;
    int16_t roundNumber;
    uint32_t transitionAt;

public:
    Game(Buttons *buttons);

public:
    void welcome();
    void startOver();
    void increase();
    void tick();

};

#endif