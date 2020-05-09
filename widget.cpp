
#include "widget.h"

bool Widget::get_focusable()
{
    return focusable;
}
bool Widget::infocus(int pos_x, int pos_y)
{
    if(beg_x<=pos_x&&end_x>=pos_x && beg_y<=pos_y &&end_y>=pos_y)
        {
            return true;
        }
        else
        {
            return false;
        }
}
void Widget::setfocused(bool sb)
{
    if(focusable)
    {
        focused = sb;
    }
}

Widget::Widget(int _beg_x, int _beg_y, int _end_x, int _end_y, bool _focusable)
{
    beg_x = _beg_x;
        beg_y = _beg_y;
        end_x = _end_x;
        end_y = _end_y;
        focusable = _focusable;
        if(focusable)
        {
            focused = false;
        }
}
std::string Widget:: get_type()
{
        return type;
}

