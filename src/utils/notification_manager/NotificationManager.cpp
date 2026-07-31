#include <chrono>

#include "NotificationManager.h"

#include "external/imgui/imgui.h"
#include "../../gui/fonts.h"


// structs
typedef struct {
    deque<string> notificationQueue;
} NotificationManager ;

NotificationManager notificationManager;


bool bShowNotification = false;
float fAlpha = 1.0f;
auto notificationStartTime = std::chrono::steady_clock::now();
auto currentTime = std::chrono::steady_clock::now();
float elapsedTimeInSeconds = 0.0f;

void notificationLoop(void)
{
    if (notificationManager.notificationQueue.size() > 0)
    {
        if (!bShowNotification)
        {
            bShowNotification = true;
            notificationStartTime = std::chrono::steady_clock::now();
        }

        currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = currentTime - notificationStartTime;
        elapsedTimeInSeconds = std::chrono::duration<float>(elapsedTime).count();

        if (elapsedTimeInSeconds > 3.0f){
            fAlpha -= 0.0009f;
        }

        if (elapsedTimeInSeconds > 4.5f)
        {
            bShowNotification = false;
            fAlpha = 1.0f;
            notificationManager.notificationQueue.pop_front();
            elapsedTimeInSeconds = 0.0f;
        }
    }
    else
    {
        return;
    }
}

void createNotification(string msg)
{
    notificationManager.notificationQueue.push_back(msg);
}

void showNotification(void)
{
    if (notificationManager.notificationQueue.size() > 0)
    {
        string msg = notificationManager.notificationQueue.front();

        ImGui::SetNextWindowPos(ImVec2(1250, 60));
        ImGui::SetNextWindowBgAlpha(0.35f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::Begin("Toast",
                     nullptr,
                     ImGuiWindowFlags_NoDecoration |
                         ImGuiWindowFlags_NoMove |
                         ImGuiWindowFlags_AlwaysAutoResize |
                         ImGuiWindowFlags_NoBackground);

        ImGui::PushStyleColor( ImGuiCol_Text, ImVec4(0.5, 1, 0.5, fAlpha));

        ImGui::PushFont(boldFont);

        ImGui::Text(msg.c_str());

        ImGui::PopFont();

        ImGui::PopStyleColor();
        ImGui::End();
        ImGui::PopStyleVar();
    }
    else
    {
        return;
    }
}

