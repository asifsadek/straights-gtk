#ifndef GAME_H
#define GAME_H

#include "Card.h"
#include "Player.h"
#include "Straight.h"
#include "Deck.h"

#include <vector>

struct Command;
class Observer;

class Game {
  public:
    enum class GameState {
      ROUND_START,
      HUMAN_INPUT,
      INVALID_PLAY_INPUT,
      INVALID_DISCARD_INPUT,
      DISCARDED_CARD,
      PLAYED_CARD,
      ROUND_END,
      GAME_END,
    };
    Game(int, std::vector<PlayerType>, Observer*);

    std::vector<Card> getCurrentPlayerCards() const;
    std::vector<Card> getCurrentPlayerValidCards() const;

    void startRound();
    void playCard(Card);
    void discardCard(Card);
    void ragequit();

    std::vector<Straight> getStraights() const;
    std::vector<Player> getPlayers() const;
    int getCurrentPlayer() const;
    Card getLastCard() const;
    std::vector<Card> getDeckCards() const;
    GameState getGameState() const;

  private:
    int seed_;
    std::vector<Straight> straights_;
    std::vector<Player> players_;
    int currentPlayer_;
    Deck deck_;
    Observer *userInterface_;
    GameState gameState_;
    Card lastCard_;

    void notify();
    void runRound();
    void setGameState(GameState);
};

#endif
