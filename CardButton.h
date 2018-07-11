#ifndef CARD_BUTTON_H
#define CARD_BUTTON_H

#include "Card.h"

#include <gtkmm/image.h>
#include <gtkmm/button.h>

class HandFrame;

class CardButton : public Gtk::Button {
  public:
    explicit CardButton(HandFrame *);
    void setCard(Card card);
    void reset();
    void on_clicked() override;

  private:
    HandFrame *handFrame_;
    Card card_;
    Gtk::Image image_;
};

#endif
