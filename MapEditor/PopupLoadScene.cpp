#include "PopupLoadScene.h"

#include "UIMapView.h"
#include "imgui.h"
#include "imgui_stdlib.h"

bool PopupLoadScene::IsOpen = false;
std::string PopupLoadScene::SceneIdentifier = "";
SceneMgr::Type PopupLoadScene::SceneType = SceneMgr::Type::SkyIslands;
void (*PopupLoadScene::Func)(SceneMgr::Type, std::string) = nullptr;

void PopupLoadScene::Render()
{
    if (IsOpen) {
        UIMapView::RenderSettings.AllowSelectingActor = false;
        ImGui::SetNextWindowSize(ImVec2(520, 113));
        ImGui::OpenPopup("Load scene");
        if (ImGui::BeginPopupModal("Load scene")) {
            const char* TypeDropdownItems[] = { "SkyIslands", "MainField", "MinusField", "LargeDungeon", "SmallDungeon", "NormalStage", "Custom" };
            ImGui::PushItemWidth(250);
            ImGui::Combo("Type", reinterpret_cast<int*>(&SceneType), TypeDropdownItems, IM_ARRAYSIZE(TypeDropdownItems));
            ImGui::PopItemWidth();
            std::string Example = "";
            switch (SceneType) {
            case SceneMgr::Type::SkyIslands:
                Example = "StartIslandMerge2";
                break;
            case SceneMgr::Type::MainField:
                Example = "E-6";
                break;
            case SceneMgr::Type::MinusField:
                Example = "E-6";
                break;
            case SceneMgr::Type::SmallDungeon:
                Example = "001";
                break;
            case SceneMgr::Type::LargeDungeon:
                Example = "Thunder";
                break;
            case SceneMgr::Type::NormalStage:
                Example = "TitleScene";
                break;
            case SceneMgr::Type::Custom:
                Example = "MainField/Castle/\nSet_HyruleCastle_IslandGround_A";
                break;
            }
            ImGui::PushItemWidth(250);
            ImGui::InputText(("Identifier (e.g. " + Example + ")").c_str(), &SceneIdentifier);
            ImGui::PopItemWidth();
            if (ImGui::Button("Load")) {
                Func(SceneType, SceneIdentifier);
                IsOpen = false;
                Func = nullptr;
                SceneType = SceneMgr::Type::SkyIslands;
                SceneIdentifier = "";
            }
            ImGui::SameLine();
            if (ImGui::Button("Return")) {
                IsOpen = false;
                Func = nullptr;
                SceneType = SceneMgr::Type::SkyIslands;
                SceneIdentifier = "";
            }
        }
        ImGui::EndPopup();
    }
}

void PopupLoadScene::Open(void (*Callback)(SceneMgr::Type, std::string))
{
    Func = Callback;
    SceneType = SceneMgr::Type::SkyIslands;
    SceneIdentifier = "";
    IsOpen = true;
}