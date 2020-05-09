#ifndef BUTTON_WIDGET_H_INCLUDED
#define BUTTON_WIDGET_H_INCLUDED

#include "widget.h"
#include "graphics.hpp"
#include <sstream>
struct Button_Widget : public Widget
{
protected:
    int margin = 3;
    int r,g,b;

    std::string textin;
    void textsetter(std::string newtext);
    void draw();
    std::string get_value();

public:
    Button_Widget(int _beg_x, int _beg_y, int _end_x, int _end_y, bool _focusable, std::string _textin, int _r, int _g, int _b);
    void event_handler(genv::event &e);
    bool getfocused();
};

#endif // WIDGET_H_INCLUDED

