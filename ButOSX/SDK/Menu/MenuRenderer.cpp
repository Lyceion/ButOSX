//
//  MenuRenderer.cpp
//  ButOSX
//
//  Created by Can on 29.10.2020.
//  Copyright © 2020 VersteckteKrone. All rights reserved.
//

#include "MenuRenderer.hpp"
#include "xorstr.h"
#include "CheatSettings.h"
#include "MainHooker.hpp"
#include "CustomWidgets.hpp"

char *Pages::PageList[]{
    "VISUALS",
    "ASSISTS",
    "CHANGERS",
    "MISCS",
    "SETTINGS"
};

float clip(float n, float lower, float upper)
{
    n = (n > lower) * n + !(n > lower) * lower;
    return (n < upper) * n + !(n < upper) * upper;
}

ImFont* g_Büyük;
ImFont* g_GirisFontBüyük;
ImFont* g_Font;
static ImVec2 WindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
void MenuRenderer::RenderMenu(bool _visible){
    static float flAlpha = 0;
    if(_visible){
        const char* CheatName = xorstr("ButOSX - Godly Cheat of MACOSX");
        static ImGuiStyle& style = ImGui::GetStyle();
        flAlpha = clip(flAlpha + (1 / 0.55f) * ImGui::GetIO().DeltaTime, 0.f, 1.f);
        style.Alpha = flAlpha;
        style.WindowRounding = WINDOW_PADDING;
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.12, 0.12, 0.12, style.Alpha);
        style.Colors[ImGuiCol_Button] = ImVec4(0.11f, 0.11f, 0.11f, style.Alpha);
        ImGui::SetNextWindowSize(WindowSize);
        ImGui::SetNextWindowBgAlpha(style.Alpha);
        static int selected_Tab = 0;
        static bool isFullscreen = false;
        static ImGuiWindowFlags UI_FLAGS = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar;
        ImGui::Begin(CheatName, NULL, UI_FLAGS); {
            static ImGuiWindow* window = ImGui::GetCurrentWindow();
            static ImDrawList* UI = window->DrawList;
            //Fullscreen Mode
            if(!isFullscreen){
                //Make Menu Movable
                WindowSize = ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT);
                UI_FLAGS = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar;
            }
            else{
                ImGui::SetWindowPos(ImVec2(0,0));
                WindowSize = ImGui::GetIO().DisplaySize;
                UI_FLAGS |= ImGuiWindowFlags_NoMove;
            }
            
            //UI TITLE
            ImGui::PushFont(g_Büyük);
            UI->AddText(ImVec2((ImGui::GetWindowPos().x + WindowSize.x) - (ImGui::CalcTextSize(CheatName).x + WINDOW_PADDING), ImGui::GetWindowPos().y + (WINDOW_PADDING * 3) - ImGui::CalcTextSize(CheatName).y), ImColor(1.0f, 1.0f, 1.0f, style.Alpha), CheatName);
            ImGui::PopFont();
            UI->AddRectFilled(ImVec2(ImGui::GetWindowPos().x + WINDOW_PADDING, ImGui::GetWindowPos().y + (WINDOW_PADDING * 3) + 1), ImVec2(ImGui::GetWindowPos().x + WindowSize.x - WINDOW_PADDING, ImGui::GetWindowPos().y + (WINDOW_PADDING * 3) + 2), ImColor(1.0f, 1.0f, 1.0f, style.Alpha));
            
            //CONTROLBOX
            style.FrameRounding = WINDOW_PADDING;
            //Close Button
            style.Colors[ImGuiCol_Button] = ImVec4(1.00f, 0.36f, 0.33f, style.Alpha);
            style.Colors[ImGuiCol_ButtonHovered] = ImVec4(1.00f, 0.56f, 0.53f, style.Alpha);
            style.Colors[ImGuiCol_ButtonActive] = ImVec4(1.00f, 0.26f, 0.23f, style.Alpha);
            style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 0.00f);
            ImGui::SetCursorPos(ImVec2(10, 9));
            if (ImGui::Button(xorstr("X"), ImVec2(10, 10))){
                Hooker::Destroy();
            }
            
            //Minimize Button
            style.Colors[ImGuiCol_Button] = ImVec4(1.00f, 0.76f, 0.20f, style.Alpha);
            style.Colors[ImGuiCol_ButtonHovered] = ImVec4(1.00f, 0.96f, 0.40f, style.Alpha);
            style.Colors[ImGuiCol_ButtonActive] = ImVec4(1.00f, 0.66f, 0.10f, style.Alpha);
            style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 0.00f);
            ImGui::SetCursorPos(ImVec2(25, 9));
            if (ImGui::Button(xorstr("_"), ImVec2(10, 10))){
                SDLHook::_visible = false;
            }
            
            //Fullscreen Button
            style.Colors[ImGuiCol_Button] = ImVec4(0.14f, 0.49f, 0.20f, style.Alpha);
            style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.14f, 0.69f, 0.40f, style.Alpha);
            style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.14f, 0.39f, 0.10f, style.Alpha);
            style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 0.00f);
            ImGui::SetCursorPos(ImVec2(40, 9));
            if (ImGui::Button(xorstr("<>"), ImVec2(10, 10)))
            {
                isFullscreen = !isFullscreen;
            }
            style.FrameRounding = 0;
            
            //TABs Renderer
            ImGui::PushFont(g_GirisFontBüyük);
            static int PageCount = 5 /*sizeof(Pages::PageList[0]) / sizeof(Pages::PageList)*/;
            ImVec2 TabSize = ImVec2((WindowSize.x - (WINDOW_PADDING * 2)) / PageCount, WINDOW_PADDING * 2);
            UI->AddRectFilled(ImVec2(ImGui::GetWindowPos().x + WINDOW_PADDING, ImGui::GetWindowPos().y + (WINDOW_PADDING * 3.5f)), ImVec2(ImGui::GetWindowPos().x + WindowSize.x - WINDOW_PADDING + 2, ImGui::GetWindowPos().y + (WINDOW_PADDING * 3.5f) + TabSize.y), ImColor(0.20f, 0.20f, 0.20f, style.Alpha));
            for(int i = 0; i <= PageCount - 1; i++){
                style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, flAlpha);
                const char* PageName = Pages::PageList[i];
                ImVec2 PageNameSize = ImGui::CalcTextSize(PageName);
                ImGui::SetCursorPos(ImVec2(WINDOW_PADDING + 2 + (TabSize.x * i), WINDOW_PADDING * 3.5f));
                if (CustomWidgets::SubTab(PageName, TabSize, selected_Tab == i ? true : false))
                    selected_Tab = i;
                ImGui::SetCursorPos(ImVec2(WINDOW_PADDING + 2 + (((TabSize.x * (i + 1)) - PageNameSize.x) / 2) + ((TabSize.x * i) / 2), (WINDOW_PADDING * 3.5f) + ((TabSize.y - PageNameSize.y - 4) / 2)));
                ImGui::Text(PageName); 
            }
            switch (selected_Tab){
                case 0:
                    Pages::VisualsPage();
                    break;
                case 1:
                    Pages::AssistsPage();
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
            }
            UI->AddRectFilled(ImVec2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y + WindowSize.y - 4), ImVec2(ImGui::GetWindowPos().x + WindowSize.x, ImGui::GetWindowPos().y + WindowSize.y + 2), ImColor(0.99f, 0.43f, 0.f, style.Alpha), 3, ImDrawCornerFlags_Bot);
        }
        ImGui::PopFont();
        ImGui::End();
    }
    else {
        flAlpha = 0;
    }
    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void Pages::VisualsPage(){ //Page for visuals.
    ImGui::PushFont(g_Font);
    static int ChildCount = 3;
    ImVec2 ChildSize = ImVec2((WindowSize.x - (WINDOW_PADDING * 2)) / ChildCount, WindowSize.y - ((WINDOW_PADDING * 7.5f ) + 5) );
    ImGui::SetCursorPos(ImVec2(WINDOW_PADDING + (ChildSize.x * 0), WINDOW_PADDING * 6.5f));
    ImGui::BeginChild(xorstr("##1"), ChildSize, true, ImGuiWindowFlags_NoScrollbar);{
        CustomWidgets::Switch(xorstr("Watermark"), &CheatSettings::WaterMark);
        CustomWidgets::Switch(xorstr("ESP"), &CheatSettings::ESP);
    }
    ImGui::EndChild();
    ImGui::SetCursorPos(ImVec2(WINDOW_PADDING + (ChildSize.x * 1), WINDOW_PADDING * 6.5f));
    ImGui::BeginChild(xorstr("##2"), ChildSize, true, ImGuiWindowFlags_NoScrollbar);{
    }
    ImGui::EndChild();
    ImGui::SetCursorPos(ImVec2(WINDOW_PADDING + (ChildSize.x * 2), WINDOW_PADDING * 6.5f));
    ImGui::BeginChild(xorstr("##3"), ChildSize, true, ImGuiWindowFlags_NoScrollbar);
    {
    }
    ImGui::EndChild();
    ImGui::PopFont();
}

void Pages::AssistsPage(){ //Page for assists.
    ImGui::PushFont(g_Font);
    static int ChildCount = 1;
    ImVec2 ChildSize = ImVec2((WindowSize.x - (WINDOW_PADDING * 2)) / ChildCount, WindowSize.y - ((WINDOW_PADDING * 7.5f ) + 5) );
    ImGui::SetCursorPos(ImVec2(WINDOW_PADDING + (ChildSize.x * 0), WINDOW_PADDING * 6.5f));
    ImGui::BeginChild(xorstr("##2"), ChildSize, true, ImGuiWindowFlags_NoScrollbar);{
        CustomWidgets::Switch(xorstr("TEST"), &CheatSettings::WaterMark);
    }
    ImGui::EndChild();
    ImGui::PopFont();
}
