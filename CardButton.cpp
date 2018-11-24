#include "CardButton.h"
#include "Card.h"
#include "HandFrame.h"

#include <gtkmm/frame.h>

const int PADDING = 2;

CardButton::CardButton(HandFrame *handFrame)
    : handFrame_(handFrame), card_(SEVEN_OF_SPADES), image_(Gtk::Image(NOTHING_IMG)) {
  image_.set_padding(PADDING, PADDING);
  set_image(image_);
}

void CardButton::setCard(Card card) {
  card_ = card;
  image_ = Gtk::Image(CARD_IMG_PREFIX + card.getString() + CARD_IMG_SUFFIX);
  image_.set_padding(PADDING, PADDING);
  set_image(image_);
}

void CardButton::setColor(Gdk::RGBA color) {
  image_.override_background_color(color);
}

void CardButton::reset() {
  card_ = SEVEN_OF_SPADES;
  image_ = Gtk::Image(NOTHING_IMG);
  image_.set_padding(PADDING, PADDING);
  set_image(image_);
}

void CardButton::on_clicked() {
  handFrame_->executeCommand(card_);
}
