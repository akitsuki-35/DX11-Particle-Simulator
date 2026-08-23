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
#include "CSVHandler.h"
#include "BezierCurve.h"
#include "Texture.h"
#include <filesystem>

#include "ImGui/imgui.h"

const void ParticleGUI::Display()
{
	// エミッタ取得
	auto emitter = Scene::GetGameObject<ParticleEmitter>();
	if (!emitter) {
		return;
	}

	// 各種GUI表示
	parameterControl(emitter);
	particleControl(emitter);
	fileControl(emitter);

	// ウィンドウのフォーカス解除
	if (!mInitialized) {
		ImGui::SetWindowFocus(nullptr);
		mInitialized = true;
	}
}

const void ParticleGUI::parameterControl(ParticleEmitter* emitter)
{
	auto renderer = emitter->GetComponent<ParticleRenderer>();

	if (!renderer) {
		return;
	}

	// インターバル最大値と最小値を設定
	double min = 0.005;
	double max = 0.1;

	// ウィンドウ位置固定
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	// ウィンドウサイズ固定
	ImGui::SetNextWindowSize(ImVec2(300, 660), ImGuiCond_Always);

	// 共通パラメータ操作
	ImGui::Begin("Parameter", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	ImGui::SeparatorText("Value");
	ImGui::SliderInt("Frame", &emitter->mLife, 30, 60);
	ImGui::SliderInt("Count", &emitter->mCount, 10, 100);
	ImGui::SliderScalar("Interval", ImGuiDataType_Double, &emitter->mMaxInterval, &min, &max, "%.3f");

	// メインカラー操作
	ImGui::SeparatorText("MainColor");
	ImGui::ColorPicker3("MainPicker", &renderer->mColor.x,
		ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_Float);

	// サブカラー操作
	ImGui::SeparatorText("SubColor");
	ImGui::ColorPicker3("SubPicker", &renderer->mSubColor.x,
		ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_Float);

	ImGui::End();
}

const void ParticleGUI::fileControl(ParticleEmitter* emitter)
{
	auto renderer = emitter->GetComponent<ParticleRenderer>();

	// テクスチャ取得
	auto texture = renderer->GetTexture()->GetSRV();
	if (!texture) {
		return;
	}

	// ウィンドウ位置固定
	ImGui::SetNextWindowPos(ImVec2(0, 660), ImGuiCond_Always);
	// ウィンドウサイズ固定
	ImGui::SetNextWindowSize(ImVec2(300, 420), ImGuiCond_Always);

	ImGui::Begin("File", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

	// CSVファイル読み込み
	ImGui::SeparatorText("Load CSV File");
	loadCSV(emitter);

	// CSVファイル出力
	ImGui::SeparatorText("Export CSV File");

	// ファイル名
	static char buf[128] = "";
	ImGui::InputText(".csv", buf, IM_ARRAYSIZE(buf));

	static ImVec4 logTextColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

	// ファイルエクスポート
	if (ImGui::Button("Export", ImVec2(50, 20))) {
		if (exportCSV(emitter, buf)) {
			// ファイル配列を再読み込み
			CSVListInitialize();
			logTextColor = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
		}
		else {
			logTextColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
		}
	}

	// ログ表示
	ImGui::SameLine();
	ImGui::TextColored(logTextColor, mLog.c_str());

	// テクスチャ読み込み
	ImGui::SeparatorText("Load Texture File");
	ImGui::Image(reinterpret_cast<ImTextureID>(texture), ImVec2(150, 150));
	loadTexture(emitter);

	ImGui::End();
}

const void ParticleGUI::loadCSV(ParticleEmitter* emitter)
{
	// ファイル配列が空の場合は初期化
	if (mCSVFiles.empty()) {
		CSVListInitialize();
	}

	// リストからのファイルのロード処理
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
	// ファイル配列初期化
	mCSVFiles.clear();

	// 探索ディレクトリ設定
	std::string path = "assets\\csv\\";

	// ディレクトリ内のファイルを取得
	if (std::filesystem::exists(path)) {
		for (const auto& e : std::filesystem::directory_iterator(path)) {
			mCSVFiles.push_back(e.path().filename().string());
		}
	}
}

const bool ParticleGUI::exportCSV(ParticleEmitter* emitter, std::string fileName)
{
	// ファイル名が空の場合はreturn
	if (fileName == "") {
		mLog = "error:FileName Empty!";
		return false;
	}

	auto renderer = emitter->GetComponent<ParticleRenderer>();

	CSVHandler::Data exportData{};

	// タイプ別のエクスポート処理のためタイプを格納
	auto type = emitter->GetType();

	// 共通パラメータ取得
	exportData.push_back({ "TYPE", type->GetTypeName().data() });
	exportData.push_back({ "LIFE", std::to_string(emitter->mLife) });
	exportData.push_back({ "INTERVAL", std::to_string(emitter->mMaxInterval) });
	exportData.push_back({ "COUNT", std::to_string(emitter->mCount) });

	// メインカラー取得
	DirectX::XMFLOAT4 mainColor = renderer->mColor;
	exportData.push_back({ "MAINCOLOR", std::to_string(mainColor.x), std::to_string(mainColor.y),
		std::to_string(mainColor.z), std::to_string(mainColor.w)});

	// サブカラー取得
	DirectX::XMFLOAT4 subColor = renderer->mSubColor;
	exportData.push_back({ "SUBCOLOR", std::to_string(subColor.x), std::to_string(subColor.y),
		std::to_string(subColor.z), std::to_string(subColor.w) });

	// タイプ特有のパラメータを取得
	if (type->GetTypeName() == "Box") {

	}
	if (type->GetTypeName() == "Bezier") {
		BezierCurve& bezier = dynamic_cast<ParticleType::Bezier*>(type)->GetBezier();
		exportData.push_back({ "CONTROLPOINT0", std::to_string(bezier.mControlPoint[0].position.x), 
			std::to_string(bezier.mControlPoint[0].position.y),
			std::to_string(bezier.mControlPoint[0].position.z) });

		exportData.push_back({ "CONTROLPOINT1", std::to_string(bezier.mControlPoint[1].position.x),
			std::to_string(bezier.mControlPoint[1].position.y),
			std::to_string(bezier.mControlPoint[1].position.z) });

		exportData.push_back({ "CONTROLPOINT2", std::to_string(bezier.mControlPoint[2].position.x),
			std::to_string(bezier.mControlPoint[2].position.y),
			std::to_string(bezier.mControlPoint[2].position.z) });

		exportData.push_back({ "CONTROLPOINT3", std::to_string(bezier.mControlPoint[3].position.x),
			std::to_string(bezier.mControlPoint[3].position.y),
			std::to_string(bezier.mControlPoint[3].position.z) });
	}

	// 出力先パス設定
	std::string fullPath = "assets\\csv\\" + fileName + ".csv";

	// フォルダが存在しない場合は生成
	std::filesystem::create_directories("assets\\csv\\");

	// エクスポート実行
	if (!CSVHandler::Export(fullPath.c_str(), exportData)) {
		mLog = "error:Export Failed!";
		return false;
	}

	mLog = "success:Export Success!";

	return true;
}

const void ParticleGUI::loadTexture(ParticleEmitter* emitter)
{
	// ファイル配列が空の場合は初期化
	if (mTextureFiles.empty()) {
		textureListInitialize();
	}

	// リストからのファイルのロード処理
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
	// ファイル配列初期化
	mTextureFiles.clear();

	// 探索ディレクトリ設定
	std::string path = "assets\\textures\\";

	if (std::filesystem::exists(path)) {
		for (const auto& e : std::filesystem::directory_iterator(path)) {
			if (!e.is_regular_file()) {
				continue;
			}

			// ディレクトリ内のファイルを取得
			std::string ext = e.path().extension().string();
			for (auto& c : ext) c = static_cast<char>(std::tolower(c));

			// テクスチャとして使える形式のファイルのみを取得
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

	// タイプ名取得
	ParticleType::Type* type = Scene::GetGameObject<ParticleEmitter>()->GetType();
	std::string name = type->GetTypeName().data();

	// 現在のタイプ名を表示
	std::string text = "Current Type : " + name;
	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), text.c_str());

	ImGui::SeparatorText("Set Particle Type");

	// ボタンによるタイプ変更
	typeControl(emitter);

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
