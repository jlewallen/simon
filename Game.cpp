#include "Game.h"

Game::Game(Buttons *buttons, DemoMode *demoMode) :
    buttons(buttons), demoMode(demoMode), state(GameState::WELCOME), maximumRoundNumber(0), roundNumber(0) {
}

void Game::welcome() {
    maximumRoundNumber = 4;
    roundNumber = 0;
    state = GameState::WELCOME;
}

void Game::startOver() {
    randomSeed(8483); // TOOD: Remove this :)
    maximumRoundNumber = 0;
    lastButtonPressedAt = millis();
    for (int16_t i = 0; i < GAME_ROUNDS_MAXIMUM; ++i) {
        rounds[i] = 0;
    }
    increase();
}

void Game::increase() {
    rounds[maximumRoundNumber] = random(0, 4);
    maximumRoundNumber++;
    roundNumber = 0;
    state = GameState::PLAYBACK;
}

void Game::tick() {
    switch (state) {
    case GameState::WELCOME: {
        if (millis() - transitionAt > 500) {
            if (roundNumber < maximumRoundNumber) {
                buttons->play(roundNumber);
                roundNumber++;
            }
            else {
                startOver();
            }
            transitionAt = millis();
        }

        break;
    }
    case GameState::INACTIVE: {
        buttons->tick();

        int8_t pressed = buttons->dequeuePress();
        if (pressed >= 0) {
            startOver();
        }
        else {
            demoMode->tick();
        }
        break;
    }
    case GameState::WAITING: {
        buttons->tick();

        int8_t pressed = buttons->dequeuePress();
        if (pressed >= 0) {
            lastButtonPressedAt = millis();
            if (pressed == rounds[roundNumber]) {
                buttons->play(pressed);
                roundNumber++;
                if (roundNumber == maximumRoundNumber) {
                    state = GameState::SUCCESS;
                    transitionAt = millis();
                }
            }
            else {
                buttons->fail();
                state = GameState::FAIL;
                transitionAt = millis();
            }
        }

        if (lastButtonPressedAt > 0 && millis() - lastButtonPressedAt > 1000 * 30) {
            lastButtonPressedAt = 0;
            state = GameState::INACTIVE;
            demoMode->start();
            transitionAt = millis();
        }
        break;
    }
    case GameState::PLAYBACK: {
        if (millis() - transitionAt > 500) {
            if (roundNumber < maximumRoundNumber) {
                buttons->play(rounds[roundNumber]);
                roundNumber++;
            }
            else {
                roundNumber = 0;
                buttons->off();
                state = GameState::WAITING;
            }
            transitionAt = millis();
        }
        break;
    }
    case GameState::SUCCESS: {
        if (millis() - transitionAt > 1000) {
            increase();
        }
        break;
    }
    case GameState::FAIL: {
        if (millis() - transitionAt > 1500) {
            startOver();
        }
        break;
    }
    }
}
