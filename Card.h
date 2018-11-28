#ifndef CARD_H
#define CARD_H

#include <istream>
#include <ostream>

const std::string CARD_IMG_PREFIX = "./img/";
const std::string CARD_IMG_SUFFIX = ".png";
const std::string NOTHING_IMG = CARD_IMG_PREFIX + "nothing" + CARD_IMG_SUFFIX;

enum Suit { CLUB, DIAMOND, HEART, SPADE, SUIT_COUNT };
// enum representing the suit of the card

enum Rank {
  ACE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  TEN,
  JACK,
  QUEEN,
  KING,
  RANK_COUNT
};
// enum representing the rank of the card

class Card {
  // Represents a Poker card with a rank and a suit
  // Specification Fields:
  //   rank = rank of the card
  //   suit = suit of the card
  friend std::istream &operator>>(std::istream &in, Card &c);
  // modifies: in, num
  // ensures: in@pre = cardString + in, c stores the Card represented by cardString
  // returns: in

 public:
  Card(Suit s, Rank r);
  // ensures: initializes this to a Card with suit s and rank r

  Suit getSuit() const;
  // returns: suit

  Rank getRank() const;
  // returns: rank

  std::string getString() const;
  // returns: string representation of Card (rankString + suitString)

 private:
  Suit suit_;
  Rank rank_;
};

const Card SEVEN_OF_SPADES = Card(SPADE, SEVEN);

bool operator==(const Card &a, const Card &b);
// returns: true if cards a and b have the same rank and suit
//          false if cards a and b have different ranks or different suits

// output/input Card in the format <rank><suit>
std::ostream &operator<<(std::ostream &out, const Card &c);
// modifies: out
// ensures: out = out@pre + rankString + suitString
// returns: out

#endif
