/*============================================================
*	@file	 : debugger.cpp
*	@brief	 : ImGuiデバッガー
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/05/21
*	@updated : 2026/06/02
*============================================================*/
#ifndef NDEBUG
#include "Debugger.h"
#include "DeviceManager.h"

// ImGui
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"

// デバッグ対象のインクルード
#include "Scene.h"
#include "Particle.h"
#include "BezierCurve.h"

/*============================================================
	使い方

	ヘッダ側にデバッグウィンドウ関数の宣言を記述し、cpp側で定義
	Initialize, Finalize, Drawの内部とUpdateのImGui::NewFrame();より上の行の変更厳禁

	デバッグ関数は以下の書式で記述する
	必ずBeginとEndで挟むこと（飛びます）

	const void Debugger::[関数名]()
	{
		ImGui::Begin("Cursor");

		// 処理内容

		ImGui::End();
	}
============================================================*/
const void Debugger::Initialize(HWND hwnd) const
{
	// バージョンチェック
	IMGUI_CHECKVERSION();

	// コンテキスト作成
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	// win32用の初期化
	ImGui_ImplWin32_Initialize(hwnd);

	// DirectX11用の初期化
	ImGui_ImplDX11_Initialize(D3D11::DeviceManager::getInstance().GetDevice(),
		D3D11::DeviceManager::getInstance().GetContext());
}

const void Debugger::Finalize() const
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

const void Debugger::Update() const
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// ===== デバッグウィンドウの追加処理 =====
}

const void Debugger::Draw() const
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

const void Debugger::BezierControl()
{
	BezierCurve* b = Scene::GetGameObject<ParticleBezier>()->GetBezier();
	if (!b) return;

	// ウィンドウ位置固定
	ImGui::SetNextWindowPos(ImVec2(1000, 0), ImGuiCond_Always);
	// ウィンドウサイズ固定
	ImGui::SetNextWindowSize(ImVec2(280, 405), ImGuiCond_Always);

	// 移動不可・サイズ変更不可
	ImGui::Begin("Bezier", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

	ImGui::SeparatorText("ControlPoint[0]");
	ImGui::SliderFloat("[0].X", &b->mControlPoint[0].position.x, -50.0f, 50.0f, "%.2f");
	ImGui::SliderFloat("[0].Y", &b->mControlPoint[0].position.y, -50.0f, 50.0f, "%.2f");
	ImGui::SliderFloat("[0].Z", &b->mControlPoint[0].position.z, -50.0f, 50.0f, "%.2f");

	ImGui::SeparatorText("ControlPoint[1]");
	ImGui::SliderFloat("[1].X", &b->mControlPoint[1].position.x, -50.0f, 50.0f, "%.2f");
	ImGui::SliderFloat("[1].Y", &b->mControlPoint[1].position.y, -50.0f, 50.0f, "%.2f");
	ImGui::SliderFloat("[1].Z", &b->mControlPoint[1].position.z, -50.0f, 50.0f, "%.2f");

	ImGui::SeparatorText("ControlPoint[2]");
	ImGui::SliderFloat("[2].X", &b->mControlPoint[2].position.x, -50.0f, 50.0f, "%.2f");
	ImGui::SliderFloat("[2].Y", &b->mControlPoint[2].position.y, -50.0f, 50.0f, "%.2f");
	ImGui::SliderFloat("[2].Z", &b->mControlPoint[2].position.z, -50.0f, 50.0f, "%.2f");
	ImGui::Separator();

	ImGui::SeparatorText("ControlPoint[3]");
	ImGui::SliderFloat("[3].X", &b->mControlPoint[3].position.x, -50.0f, 50.0f, "%.2f");
	ImGui::SliderFloat("[3].Y", &b->mControlPoint[3].position.y, -50.0f, 50.0f, "%.2f");
	ImGui::SliderFloat("[3].Z", &b->mControlPoint[3].position.z, -50.0f, 50.0f, "%.2f");

	ImGui::End();
}

const void Debugger::ParticleControl()
{
	ParticleBezier* p = Scene::GetGameObject<ParticleBezier>();
	if (!p) return;

	BezierCurve* b = p->GetBezier();
	if (!b) return;

	double min = 0.005;
	double max = 0.1;

	// ウィンドウ位置固定
	ImGui::SetNextWindowPos(ImVec2(1000, 405), ImGuiCond_Always);
	// ウィンドウサイズ固定
	ImGui::SetNextWindowSize(ImVec2(280, 315), ImGuiCond_Always);

	ImGui::Begin("Particle", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	ImGui::SeparatorText("Value");
	ImGui::SliderInt("Frame", &p->Life, 30, b->DEFAULT_FRAMEMAX);
	ImGui::SliderInt("Count", &p->Count, 10, 500);
	ImGui::SliderScalar("Interval", ImGuiDataType_Double, &p->Interval, &min, &max, "%.3f");

	ImGui::SeparatorText("MainColor");
	ImGui::SliderFloat("MainColor.R", &p->mMainColor.x, 0.02f, 1.00f, "%.3f");
	ImGui::SliderFloat("MainColor.G", &p->mMainColor.y, 0.02f, 1.00f, "%.3f");
	ImGui::SliderFloat("MainColor.B", &p->mMainColor.z, 0.02f, 1.00f, "%.3f");

	ImGui::SeparatorText("SubColor");
	ImGui::SliderFloat("SubColor.R", &p->mSubColor.x, 0.02f, 1.00f, "%.3f");
	ImGui::SliderFloat("SubColor.G", &p->mSubColor.y, 0.02f, 1.00f, "%.3f");
	ImGui::SliderFloat("SubColor.B", &p->mSubColor.z, 0.02f, 1.00f, "%.3f");

	ImGui::End();
}


#endif