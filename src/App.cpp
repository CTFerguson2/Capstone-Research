#include "App.hpp"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include "UI.hpp"

App::App()
    : window(sf::VideoMode(Constants::WINDOW_DIM), "Capstone Research"),
    deltaClock(), canvas(500, 500), tools(), ui() {
        window.setFramerateLimit(60);
        if(!ImGui::SFML::Init(window)){
            std::cerr << "Failed to initialize ImGui";
        };
    }

App::~App(){
    ImGui::SFML::Shutdown();
}

void App::run(){
    while(window.isOpen()){
        processEvents();
        update();
        render();
    }
}


void App::processEvents(){
    while(const std::optional event = window.pollEvent())
    {
        ImGui::SFML::ProcessEvent(window, *event);
        
        if(event -> is<sf::Event::Closed>())
            window.close();
    }
}

void App::update(){
    ImGui::SFML::Update(window, deltaClock.restart());
}

void App::render(){
    window.clear(Constants::BG_COLOR);

     UIActions actions = ui.drawToolPanel(tools, canvasZoom);

    if (actions.exportPng) {
        if( canvas.exportPng("drawing.png"))
            std::cout << "Drawing saved!" << std::endl;
        else
            std::cout << "Epic fail :(" << std::endl;
        
    }
    drawCanvasPanel();
    ImGui::SFML::Render(window);
    window.display();
}

void App::drawCanvasPanel() {
    ImGui::Begin("Canvas");

    ImGui::BeginChild(
        "CanvasView",
        ImVec2(0, 0),
        true,
        ImGuiWindowFlags_HorizontalScrollbar
    );

    sf::Vector2u canvasSize = canvas.getSize();

    sf::Vector2f displaySize(
        static_cast<float>(canvasSize.x) * canvasZoom,
        static_cast<float>(canvasSize.y) * canvasZoom
    );
    ImVec2 displaySizeImGui(displaySize.x, displaySize.y);

    ImVec2 available = ImGui::GetContentRegionAvail();

    float offsetX = std::max((available.x - displaySize.x) * 0.5f, 0.0f);
    float offsetY = std::max((available.y - displaySize.y) * 0.5f, 0.0f);

    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offsetX);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + offsetY);

    ImVec2 imageTopLeft = ImGui::GetCursorScreenPos();

    ImGui::Image(canvas.getRenderTexture(), displaySize);

    ImVec2 imageBottomRight = ImGui::GetItemRectMax();

    ImGui::SetCursorScreenPos(imageTopLeft);

    ImGui::InvisibleButton(
        "canvas_input",
        displaySizeImGui,
        ImGuiButtonFlags_MouseButtonLeft
    );

    bool canvasHovered = ImGui::IsItemHovered();
    bool canvasActive = ImGui::IsItemActive();

    ImGui::SetCursorScreenPos(imageBottomRight);

    ImGuiIO& io = ImGui::GetIO();
    ImVec2 mouse = io.MousePos;

    float canvasX = (mouse.x - imageTopLeft.x) / canvasZoom;
    float canvasY = (mouse.y - imageTopLeft.y) / canvasZoom;


    bool mouseOverCanvas =
        canvasX >= 0.0f &&
        canvasY >= 0.0f &&
        canvasX < static_cast<float>(canvasSize.x) &&
        canvasY < static_cast<float>(canvasSize.y);

     sf::Vector2u canvasPoint(
        static_cast<unsigned int>(canvasX),
        static_cast<unsigned int>(canvasY)
    );
    // Use tools
    // Eyedropper
    if (
        canvasActive &&
        mouseOverCanvas &&
        ImGui::IsMouseClicked(ImGuiMouseButton_Left) &&
        tools.current == Tool::Eyedropper
    ) {
        tools.brushColor = canvas.pickColor(canvasPoint);
    } 
    //Fill
    if (
        canvasActive &&
        mouseOverCanvas &&
        ImGui::IsMouseClicked(ImGuiMouseButton_Left) &&
        tools.current == Tool::FillBucket
    ) {
        canvas.fill(canvasPoint, tools.brushColor);
    }
    // Draw/Erase
    if ((tools.current == Tool::Brush || tools.current == Tool::Eraser) && canvasActive && mouseOverCanvas && ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
        sf::Vector2f currentCanvasPoint(canvasX, canvasY);

        if (!isDrawing) {
            isDrawing = true;
            lastCanvasPoint = currentCanvasPoint;
        }

        canvas.drawBrush(
            lastCanvasPoint,
            currentCanvasPoint,
            tools.current == Tool::Brush ? tools.brushSize : tools.eraserSize,
            tools.current == Tool::Brush ? tools.brushColor : sf::Color::White
        );

        lastCanvasPoint = currentCanvasPoint;
    } else {
        isDrawing = false;
       
    }
    ImGui::EndChild();

    ImGui::End();
}


