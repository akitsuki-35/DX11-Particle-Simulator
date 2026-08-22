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
#include "ParticleGUI.h"

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
const void Debugger::Initialize(HWND hwnd)
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

const void Debugger::Finalize()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

const void Debugger::Update()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// ===== デバッグウィンドウの追加処理 =====
	ParticleGUI::getInstance().Display();
}

const void Debugger::Draw()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

#endif