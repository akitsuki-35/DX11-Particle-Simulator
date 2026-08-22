/*============================================================
*	@file	 : ParticleGUI.cpp
*	@brief	 : パーティクル制御用GUI
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/22
*	@updated : 2026/08/22
*============================================================*/
#include "ParticleGUI.h"
#include "Scene.h"
#include "ParticleEmitter.h"
#include "ParticleRenderer.h"
#include "ParticleTypes.h"
#include "BezierCurve.h"
#include "Texture.h"
#include <filesystem>

#include "ImGui/imgui.h"

const void ParticleGUI::Display()
{
	auto emitter = Scene::GetGameObject<ParticleEmitter>();
	if (!emitter) {
		return;
	}

	parameterControl(emitter);
	particleControl(emitter);
	fileControl(emitter);
}

const void ParticleGUI::parameterControl(ParticleEmitter* emitter)
{
	ParticleType::Type* type = emitter->GetType();
	if (!type) {
		return;
	}

	auto renderer = emitter->GetComponent<ParticleRenderer>();

	double min = 0.005;
	double max = 0.1;

	// ウィンドウ位置固定
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	// ウィンドウサイズ固定
	ImGui::SetNextWindowSize(ImVec2(300, 660), ImGuiCond_Always);

	ImGui::Begin("Parameter", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	ImGui::SeparatorText("Value");
	ImGui::SliderInt("Frame", &emitter->mLife, 30, 60);
	ImGui::SliderInt("Count", &emitter->mCount, 10, 100);
	ImGui::SliderScalar("Interval", ImGuiDataType_Double, &emitter->mMaxInterval, &min, &max, "%.3f");

	ImGui::SeparatorText("MainColor");
	ImGui::ColorPicker3("MainPicker", &renderer->mColor.x,
		ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_Float);

	ImGui::SeparatorText("SubColor");
	ImGui::ColorPicker3("SubPicker", &renderer->mSubColor.x,
		ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_Float);

	ImGui::End();
}

const void ParticleGUI::fileControl(ParticleEmitter* emitter)
{
	// ウィンドウ位置固定
	ImGui::SetNextWindowPos(ImVec2(0, 660), ImGuiCond_Always);
	// ウィンドウサイズ固定
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_Always);

	ImGui::Begin("File", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

	auto renderer = emitter->GetComponent<ParticleRenderer>();
	auto texture = renderer->GetTexture()->GetSRV();

	if (!texture) {
		return;
	}

	ImGui::SeparatorText("CSV File");
	ImGui::Text("Load CSV File");
	loadCSV(emitter);

	ImGui::SeparatorText("Texture File");
	ImGui::Image(reinterpret_cast<ImTextureID>(texture), ImVec2(100, 100));
	ImGui::Text("Load Texture File");
	loadTexture(emitter);

	ImGui::End();
}

const void ParticleGUI::loadCSV(ParticleEmitter* emitter)
{
	if (mCSVFiles.empty()) {
		CSVListInitialize();
	}

	if (!mCSVFiles.empty()) {
		if (ImGui::BeginCombo("##CSVList", mCSVFiles[mCSVIndex].c_str())) {
			for (int i = 0; i < static_cast<int>(mCSVFiles.size()); ++i) {
				const bool isSelected = (mCSVIndex == i);

				if (ImGui::Selectable(mCSVFiles[i].c_str(), isSelected)) {
					mCSVIndex = i;

					std::string fullPath = "assets\\csv\\" + mCSVFiles[mCSVIndex];
					emitter->LoadCSV(fullPath.c_str());
				}

				if (isSelected) {
					ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}
	}
}

const void ParticleGUI::CSVListInitialize()
{
	mCSVFiles.clear();
	std::string path = "assets\\csv\\";

	if (std::filesystem::exists(path)) {
		for (const auto& e : std::filesystem::directory_iterator(path)) {
			mCSVFiles.push_back(e.path().filename().string());
		}
	}
}

const void ParticleGUI::loadTexture(ParticleEmitter* emitter)
{
	if (mTextureFiles.empty()) {
		textureListInitialize();
	}

	if (!mTextureFiles.empty()) {
		if (ImGui::BeginCombo("##TextureList", mTextureFiles[mTextureIndex].c_str())) {
			for (int i = 0; i < static_cast<int>(mTextureFiles.size()); ++i) {
				const bool isSelected = (mTextureIndex == i);

				if (ImGui::Selectable(mTextureFiles[i].c_str(), isSelected)) {
					mTextureIndex = i;

					std::string fullPath = "assets\\textures\\" + mTextureFiles[mTextureIndex];
					auto renderer = emitter->GetComponent<ParticleRenderer>();
					renderer->LoadTexture(fullPath.c_str());
				}

				if (isSelected) {
					ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}
	}
}

const void ParticleGUI::textureListInitialize()
{
	mTextureFiles.clear();
	std::string path = "assets\\textures\\";

	if (std::filesystem::exists(path)) {
		for (const auto& e : std::filesystem::directory_iterator(path)) {
			if (!e.is_regular_file()) {
				continue;
			}

			std::string ext = e.path().extension().string();
			for (auto& c : ext) c = static_cast<char>(std::tolower(c));

			if (ext == ".png" || ext == ".jpg" || ext == ".tga") {
				mTextureFiles.push_back(e.path().filename().string());
			}
		}
	}
}

const void ParticleGUI::particleControl(ParticleEmitter* emitter)
{
	// ウィンドウ位置固定
	ImGui::SetNextWindowPos(ImVec2(1620, 0), ImGuiCond_Always);
	// ウィンドウサイズ固定
	ImGui::SetNextWindowSize(ImVec2(300, 500), ImGuiCond_Always);

	// 移動不可・サイズ変更不可
	ImGui::Begin("Type Parameter", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

	// ボタンによるタイプ変更
	typeControl(emitter);

	ParticleType::Type* type = Scene::GetGameObject<ParticleEmitter>()->GetType();
	std::string name = type->GetTypeName().data();

	// タイプ別のパラメータ制御
	if (name == "Box") {

	}
	else if (name == "Bezier") {
		bezierControl(emitter);
	}

	ImGui::End();
}

const void ParticleGUI::typeControl(ParticleEmitter* emitter)
{
	// 同じタイプの場合は処理しない
	std::string name = emitter->GetType()->GetTypeName().data();

	// ボタン押下でパーティクルタイプを変更・初期化

	// ボックス
	if (ImGui::Button("Box", ImVec2(50, 20))) {
		if (name != "Box") {
			emitter->SetType(std::make_unique<ParticleType::Box>(emitter));
			emitter->SetPosition({ 0.0f, 0.0f, 0.0f });
		}
	}

	ImGui::SameLine();

	// ベジエ曲線
	if (ImGui::Button("Bezier", ImVec2(50, 20))) {
		if (name != "Bezier") {
			emitter->SetType(std::make_unique<ParticleType::Bezier>(emitter));
			emitter->SetPosition({ 0.0f, 0.0f, 0.0f });
		}
	}
}

const void ParticleGUI::bezierControl(ParticleEmitter* emitter)
{
	ParticleType::Type* type = emitter->GetType();
	if (!type) {
		return;
	}

	auto* b = dynamic_cast<ParticleType::Bezier*>(type);

	if (!b) {
		return;
	}

	BezierCurve& bezier = b->GetBezier();

	ImGui::SeparatorText("ControlPoint[0]");
	ImGui::SliderFloat("[0].X", &bezier.mControlPoint[0].position.x, -50.0f, 50.0f, "%.2f");
	ImGui::SliderFloat("[0].Y", &bezier.mControlPoint[0].position.y, -50.0f, 50.0f, "%.2f");
	ImGui::SliderFloat("[0].Z", &bezier.mControlPoint[0].position.z, -50.0f, 50.0f, "%.2f");

	ImGui::SeparatorText("ControlPoint[1]");
	ImGui::SliderFloat("[1].X", &bezier.mControlPoint[1].position.x, -50.0f, 50.0f, "%.2f");
	ImGui::SliderFloat("[1].Y", &bezier.mControlPoint[1].position.y, -50.0f, 50.0f, "%.2f");
	ImGui::SliderFloat("[1].Z", &bezier.mControlPoint[1].position.z, -50.0f, 50.0f, "%.2f");

	ImGui::SeparatorText("ControlPoint[2]");
	ImGui::SliderFloat("[2].X", &bezier.mControlPoint[2].position.x, -50.0f, 50.0f, "%.2f");
	ImGui::SliderFloat("[2].Y", &bezier.mControlPoint[2].position.y, -50.0f, 50.0f, "%.2f");
	ImGui::SliderFloat("[2].Z", &bezier.mControlPoint[2].position.z, -50.0f, 50.0f, "%.2f");

	ImGui::SeparatorText("ControlPoint[3]");
	ImGui::SliderFloat("[3].X", &bezier.mControlPoint[3].position.x, -50.0f, 50.0f, "%.2f");
	ImGui::SliderFloat("[3].Y", &bezier.mControlPoint[3].position.y, -50.0f, 50.0f, "%.2f");
	ImGui::SliderFloat("[3].Z", &bezier.mControlPoint[3].position.z, -50.0f, 50.0f, "%.2f");
}
