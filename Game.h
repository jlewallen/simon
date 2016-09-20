#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <Arduino.h>
#include "Speaker.h"
#include "Buttons.h"

#define GAME_ROUNDS_MAXIMUM                                   256

enum class GameState {
    WAITING,
    PLAYBACK,
    SUCCESS,
    FAIL
};

class Game {
private:
    Buttons *buttons;
    Speaker *speaker;
    GameState state;
    uint8_t rounds[GAME_ROUNDS_MAXIMUM];
    int16_t maximumRoundNumber;
    int16_t roundNumber;
    uint32_t transitionAt;

public:
    Game(Speaker *speaker, Buttons *buttons);

public:
    void startOver();
    void increase();
    void tick();

};

#endif
