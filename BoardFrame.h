#ifndef DECK_FRAME_H
#define DECK_FRAME_H

#include "Card.h"
#include "Observer.h"

#include <array>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/frame.h>

class GameController;

class BoardFrame : public Gtk::Frame, public Observer {
  // Frame that shows the straights on the table (reflects game state)
  // Specification Fields:
  //   board = UI displaying the cards played in a game of straights
  //   game = the game of straights the board is monitoring
  public:
    explicit BoardFrame(GameController *);
    // ensures: initializes this to an empty board of straights,
    //          board monitors the game managed by the specified GameController

    virtual ~BoardFrame() = default;
    // modifies: this
    // ensures: this is no longer exists, owned memory is freed

    void update() override;
    // modifies: this
    // ensures: board visualizes the current state of the game of straights

  private:
    GameController *gameController_;
    Gtk::VBox contents_;
    std::array<Gtk::Box, SUIT_COUNT> straightBoxes_;
    std::array<Gtk::Image, SUIT_COUNT * RANK_COUNT> cardImages_;

    void reset();
};

#endif
