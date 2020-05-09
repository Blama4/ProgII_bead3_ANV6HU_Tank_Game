#ifndef SELECT_WIDGET_H_INCLUDED
#define SELECT_WIDGET_H_INCLUDED

#include "widget.h"
#include "graphics.hpp"
#include <sstream>
#include <vector>
struct Select_Widget : public Widget
{
protected:
    int margin = 3;
    int viewable;
    int open_counter = 0;
    int m_margin = 2;
    bool opened = false;
    bool newselected = false;
    double rate=0.2;
    std::vector<std::string>menu;
    std::string selected;
    void opener(int posx, int posy);
    void draw();
    void menu_draw();
    void on_click(int pos_x, int pos_y);
    void setmenu(bool tmp);
    void bowl_up();
    void bowl_do();
    void select(int tmp);
    void selector(int posx, int posy);
    std::string get_value();

public:
    Select_Widget(int _beg_x, int _beg_y, int _end_x, int _end_y, bool _focusable, std::vector<std::string>_menu, int _viewable);
    void event_handler(genv::event &e);
    bool getfocused();
    bool getopened();
    bool was_action();
    void new_selected(bool tmp);

};


#endif

