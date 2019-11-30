#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include "window.h"
class Board;

class GraphicsDisplay {
    Xwindow *xw = nullptr; // owns an Xwindow object
    std::vector<*Board> boards;
 public:
     GraphicsDisplay(size_t n);
     ~GraphicsDisplay();
};

#endif

