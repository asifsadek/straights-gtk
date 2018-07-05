#include "Card.h"
#include "Command.h"
#include "Game.h"
#include "Observer.h"
#include "Player.h"
#include "Straight.h"

#include <algorithm>
#include <cassert>
#include <random>
#include <vector>

const Card SEVEN_OF_SPADES = Card(SPADE, SEVEN);

Game::Game(int seed, std::vector<PlayerType> playerTypes, Observer *userInterface):
  seed_(seed), userInterface_(userInterface), gameState_(GameState::ROUND_START),
  lastCard_(Card(SPADE, ACE))
{
  assert(playerTypes.size() == PLAYER_COUNT);

  // treating vectors like static arrays by reserving space
  // we opted to use vectors since objects do not have default constructors
  players_.reserve(PLAYER_COUNT);
  straights_.reserve(STRAIGHT_COUNT);
  deck_.reserve(CARD_COUNT);

  for (int i = 0; i < PLAYER_COUNT; i++)
    players_.push_back(Player(playerTypes[i]));

  for (int i = 0; i < STRAIGHT_COUNT; i++)
    straights_.push_back(Straight((Suit)i));

  for (int i = 0; i < SUIT_COUNT; i++)
    for (int j = 0; j < RANK_COUNT; j++)
      deck_.push_back(Card((Suit)i, (Rank)j));
}

std::vector<Card> Game::getCurrentPlayerCards() const {
  return players_[currentPlayer_].getCards();
}

std::vector<Card> Game::getCurrentPlayerValidCards() const {
  std::vector<Card> validCards = players_[currentPlayer_].getCards();
  if (std::find(validCards.begin(), validCards.end(), SEVEN_OF_SPADES) != validCards.end()) {
    return { SEVEN_OF_SPADES };
  } else {
    validCards.erase(
      std::remove_if(
        validCards.begin(),
        validCards.end(),
        [this](const Card &card) {
          Suit suit = card.getSuit();
          return !straights_[suit].canPlayCard(card);
        }
      ),
      validCards.end()
    );
  }
  return validCards;
}

void Game::notify() {
  userInterface_->update();
}

void Game::setGameState(Game::GameState gameState) {
  gameState_ = gameState;
  notify();
}

void Game::playCard(Card card) {
  Suit suit = card.getSuit();
  std::vector<Card> validCards = getCurrentPlayerValidCards();
  bool isValidMove = std::find(validCards.begin(), validCards.end(), card) != validCards.end();

  if (isValidMove) {
    straights_[suit].playCard(card);
    players_[currentPlayer_].playCard(card);
    lastCard_ = card;
    setGameState(GameState::PLAYED_CARD);
    currentPlayer_ = (currentPlayer_ + 1) % 4;
    runRound();
  } else {
    setGameState(GameState::INVALID_PLAY_INPUT);
  }
}

void Game::discardCard(Card card) {
  std::vector<Card> cards = getCurrentPlayerCards();
  if (getCurrentPlayerValidCards().empty() && std::find(cards.begin(), cards.end(), card) != cards.end()) {
    players_[currentPlayer_].discardCard(card);
    lastCard_ = card;
    setGameState(GameState::DISCARDED_CARD);
    currentPlayer_ = (currentPlayer_ + 1) % 4;
    runRound();
  } else {
    setGameState(GameState::INVALID_DISCARD_INPUT);
  }
}

void Game::ragequit() {
  players_[currentPlayer_].setPlayerType(PlayerType::COMPUTER);
  runRound();
}

void Game::startRound() {
  // update scores
  for (int i = 0; i < PLAYER_COUNT; i++) {
    players_[i].updateScore();
  }

  // check if game is over
  for (int i = 0; i < PLAYER_COUNT; i++) {
    if (players_[i].getScore() >= MAX_SCORE) {
      setGameState(GameState::GAME_END);
      return;
    }
  }

  // shuffle the deck
  static std::mt19937 rng(seed_);
  int n = CARD_COUNT;
  while (n > 1) {
    int k = (int)(rng() % n--);
    std::swap(deck_[k], deck_[n]);
  }

  // reset straights
  for (int i = 0; i < SUIT_COUNT; i++) {
    straights_[i] = Straight((Suit)i);
  }

  // assign cards
  std::vector<Card> currentHand;
  for (int i = 0; i < PLAYER_COUNT; i++) {
    for (int j = 0; j < CARD_COUNT / PLAYER_COUNT; j++) {
      currentHand.push_back(deck_[13 * i + j]);
    }
    players_[i].setCards(currentHand);
    currentHand.clear();
  }

  // find the player with 7 of spades
  for (int i = 0; i < PLAYER_COUNT; i++) {
    std::vector<Card> playerCards = players_[i].getCards();
    if (std::find(playerCards.begin(), playerCards.end(), SEVEN_OF_SPADES) != playerCards.end()) {
      currentPlayer_ = i;
      break;
    }
  }

  setGameState(GameState::ROUND_START);
  runRound();
}

void Game::runRound() {
  if (getCurrentPlayerCards().empty()) {
    setGameState(GameState::ROUND_END);
    startRound();
  } else if (players_[currentPlayer_].getPlayerType() == PlayerType::HUMAN) {
    setGameState(GameState::HUMAN_INPUT);
  } else {
    std::vector<Card> validCards = getCurrentPlayerValidCards();

    // if no valid cards, discard first valid card
    if (validCards.empty()) {
      discardCard(getCurrentPlayerCards()[0]);
    }

    // play first valid card
    else {
      playCard(validCards[0]);
    }
  }
}