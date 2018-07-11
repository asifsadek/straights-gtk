#ifndef MENU_FRAME_H
#define MENU_FRAME_H

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/frame.h>

class MenuFrame : public Gtk::Frame {
  public:
    MenuFrame();

  private:
    Gtk::Box contents_;
    Gtk::Button newGameButton_, quitButton_, rageButton_;
    Gtk::Entry seedEntry_;
};

#endif
