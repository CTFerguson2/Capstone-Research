#pragma once

#include "Tool.hpp"

struct UIActions {
    bool exportPng = false;
};

class UI {
    public:
    UI();
    UIActions drawToolPanel(ToolState& tools, float& canvasZoom);
};