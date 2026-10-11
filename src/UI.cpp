#include "UI.hpp"

#include <imgui.h>

UI::UI(){

}

namespace {
void toolButton(const char* label, Tool tool, ToolState& tools) {
    bool selected = tools.current == tool;

    if (selected) {
        ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonActive));
    }

    if (ImGui::Button(label)) {
        if (selected) {
            tools.current = Tool::None;
        } else {
            tools.current = tool;
        }
    }

    if (selected) {
        ImGui::PopStyleColor();
    }
}
}

UIActions UI::drawToolPanel(ToolState& tools, float& canvasZoom) {
    UIActions actions;
    ImGui::Begin("Tools");

    toolButton("Brush", Tool::Brush, tools);
    ImGui::SameLine();
    toolButton("Eraser", Tool::Eraser, tools);
    ImGui::SameLine();

    toolButton("Eyedropper", Tool::Eyedropper, tools);
    ImGui::SameLine();

    toolButton("Fill", Tool::FillBucket, tools);

    ImGui::SliderFloat("Brush Size", &tools.brushSize, 1.0f, 100.0f);
    float color[4] = {
        tools.brushColor.r / 255.0f,
        tools.brushColor.g / 255.0f,
        tools.brushColor.b / 255.0f,
        tools.brushColor.a / 255.0f
    };

    if (ImGui::ColorEdit4("Brush Color", color)) {
        tools.brushColor = sf::Color(
            static_cast<std::uint8_t>(color[0] * 255.0f),
            static_cast<std::uint8_t>(color[1] * 255.0f),
            static_cast<std::uint8_t>(color[2] * 255.0f),
            static_cast<std::uint8_t>(color[3] * 255.0f)
        );
    }

    ImGui::SliderFloat("Eraser Size", &tools.eraserSize, 1.0f, 100.0f);

    ImGui::SliderFloat("Zoom", &canvasZoom, 0.25f, 8.0f);

    if (ImGui::Button("100%")) {
        canvasZoom = 1.0f;
    }
    if (ImGui::Button("Export PNG")) {
        actions.exportPng = true;
    }

    ImGui::End();

    return actions;
}