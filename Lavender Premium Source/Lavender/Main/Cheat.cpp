#include "Cheat.hpp"
#include "FivemSDK/Fivem.hpp"
#include "Main/images.h"
#include "Main/fonts.h"
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include <thread>
#include <Utils/FrameWork.hpp>
#include "Options.hpp"
#include <Utils/Dependencies/ImGui/imgui_settings.h>
 
#include "base64.h"
#include "AES.h"
 
#include <Utils/Render/kaanlar.h>
bool qs = false;

std::string g_key = xorstr_("yaladediyalama");
std::string g_iv = xorstr_("aaaaaaaaaaaaaaaa");
std::string DecryptionAES(const std::string& strSrc)
{
	std::string strData = base64_decode(strSrc);
	size_t length = strData.length();
	char* szDataIn = new char[length + 1];
	memcpy(szDataIn, strData.c_str(), length + 1);
	char* szDataOut = new char[length + 1];
	memcpy(szDataOut, strData.c_str(), length + 1);

	AES aes;
	aes.MakeKey(g_key.c_str(), g_iv.c_str(), 16, 16);
	aes.Decrypt(szDataIn, szDataOut, length, AES::CBC);

	if (0x00 < szDataOut[length - 1] <= 0x16)
	{
		int tmp = szDataOut[length - 1];
		for (int i = length - 1; i >= length - tmp; i--)
		{
			if (szDataOut[i] != tmp)
			{
				memset(szDataOut, 0, length);
				std::cout << "q" << std::endl;
				break;
			}
			else
				szDataOut[i] = 0;
		}
	}
	std::string strDest(szDataOut);
	delete[] szDataIn;
	delete[] szDataOut;
	return strDest;
}
std::string DecryptionAESV2(std::string g_key, const std::string& strSrc)
{
	std::string strData = base64_decode(strSrc);
	size_t length = strData.length();
	char* szDataIn = new char[length + 1];
	memcpy(szDataIn, strData.c_str(), length + 1);
	char* szDataOut = new char[length + 1];
	memcpy(szDataOut, strData.c_str(), length + 1);

	AES aes;
	aes.MakeKey(g_key.c_str(), g_iv.c_str(), 16, 16);
	aes.Decrypt(szDataIn, szDataOut, length, AES::CBC);

	if (0x00 < szDataOut[length - 1] <= 0x16)
	{
		int tmp = szDataOut[length - 1];
		for (int i = length - 1; i >= length - tmp; i--)
		{
			if (szDataOut[i] != tmp)
			{
				memset(szDataOut, 0, length);
				std::cout << "q" << std::endl;
				break;
			}
			else
				szDataOut[i] = 0;
		}
	}
	std::string strDest(szDataOut);
	delete[] szDataIn;
	delete[] szDataOut;
	return strDest;
}
std::string EncryptionAES(const string& strSrc)
{
	size_t length = strSrc.length();
	int block_num = length / BLOCK_SIZE + 1;
	char* szDataIn = new char[block_num * BLOCK_SIZE + 1];
	memset(szDataIn, 0x00, block_num * BLOCK_SIZE + 1);
	strcpy(szDataIn, strSrc.c_str());

	int k = length % BLOCK_SIZE;
	int j = length / BLOCK_SIZE;
	int padding = BLOCK_SIZE - k;
	for (int i = 0; i < padding; i++)
	{
		szDataIn[j * BLOCK_SIZE + k + i] = padding;
	}
	szDataIn[block_num * BLOCK_SIZE] = '\0';

	char* szDataOut = new char[block_num * BLOCK_SIZE + 1];
	memset(szDataOut, 0, block_num * BLOCK_SIZE + 1);

	AES aes;
	aes.MakeKey(g_key.c_str(), g_iv.c_str(), 16, 16);
	aes.Encrypt(szDataIn, szDataOut, block_num * BLOCK_SIZE, AES::CBC);
	string str = base64_encode((unsigned char*)szDataOut,
		block_num * BLOCK_SIZE);
	delete[] szDataIn;
	delete[] szDataOut;
	return str;
}
 
 
using namespace nlohmann;
 
void styledarklgg()
{

	ImGuiStyle* style = &ImGui::GetStyle();
	ImVec4* colors = style->Colors;
	style->WindowRounding = 9.f;
	style->AntiAliasedFill = true;
	style->AntiAliasedLines = true;

	style->WindowPadding = ImVec2(0, 0);
	style->ItemSpacing = ImVec2(10, 10);
	style->WindowBorderSize = 0;
	style->ScrollbarSize = 8.f;

	colors[ImGuiCol_Text] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_Border] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_Button] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_Header] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_Tab] = ImLerp(colors[ImGuiCol_Header], colors[ImGuiCol_TitleBgActive], 0.0f);
	colors[ImGuiCol_TabHovered] = colors[ImGuiCol_HeaderHovered];
	colors[ImGuiCol_TabActive] = ImLerp(colors[ImGuiCol_HeaderActive], colors[ImGuiCol_TitleBgActive], 0.0f);
	colors[ImGuiCol_TabUnfocused] = ImLerp(colors[ImGuiCol_Tab], colors[ImGuiCol_TitleBg], 0.0f);
	colors[ImGuiCol_TabUnfocusedActive] = ImLerp(colors[ImGuiCol_TabActive], colors[ImGuiCol_TitleBg], 0.0f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_TableRowBg] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.f, 0.f, 0.f, 0.f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.f, 0.f, 0.f, 0.f);

}


ID3D11ShaderResourceView* Image = nullptr;
std::string infoBegin;
bool inst = false;
std::string acKontrol;
void bioscntrl()
{

}
void lgNTab()
{
	inst = true;



	styledarklgg();
	ImDrawList* draw;
	static char yrkey[65] = { "" };
	ImGuiStyle* style = &ImGui::GetStyle();
	ImVec2 totalsize = { 800,450 };
	ImGui::SetNextWindowSize(totalsize, ImGuiCond_Always);
	const float width = (float)(GetSystemMetrics)(SM_CXSCREEN);
	const float height = (float)(GetSystemMetrics)(SM_CYSCREEN);
	ImGui::SetNextWindowPos(ImVec2((width / 2) - (totalsize.x / 2), (height / 2) - (totalsize.y / 2)), ImGuiCond_FirstUseEver);
	HW_PROFILE_INFO hwProfileInfo;
	ImGui::Begin(xorstr_("ESPRENDERTAB"), NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBringToFrontOnFocus);
	{
		const ImVec2& pos = ImGui::GetWindowPos();
		ImGui::GetWindowDrawList()->AddRectFilled(pos, ImVec2(pos.x + totalsize.x, pos.y + totalsize.y), ImGui::GetColorU32(ImVec4{ 30.f / 255.f,33.f / 255.f,39.f / 255.f,1.f }), 0);
		ImGui::GetWindowDrawList()->AddRect(pos, ImVec2(pos.x + totalsize.x, pos.y + totalsize.y), ImGui::GetColorU32(c::background::stroke), 0);
		ImGui::PushClipRect(pos, ImVec2(pos.x + totalsize.x, pos.y + totalsize.y), false);
		ImGui::GetWindowDrawList()->AddCircleFilled(ImVec2(pos.x + 125, pos.y + 70), 300, ImGui::GetColorU32(ImVec4{ 22.f / 255.f,25.f / 255.f,29.f / 255.f,1.f }), 10000);
		ImGui::PopClipRect();

		ImGui::GetWindowDrawList()->AddImage(Image, ImVec2(pos.x + (totalsize.x / 2), pos.y), ImVec2(pos.x + totalsize.x, pos.y + totalsize.y), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255));
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(pos.x + (totalsize.x / 2), pos.y), ImVec2(pos.x + totalsize.x, pos.y + totalsize.y), ImGui::GetColorU32(ImVec4{ 0,0,0,0.4f }));

		ImGui::BeginChild(xorstr_("SolTaraf"), ImVec2(400, totalsize.y), false);
		{
			std::string lavender = xorstr_("LAVENDER");
			std::string premium = xorstr_("PREMIUM");
			std::string finalText = lavender + premium;
			ImGui::PushFont(font::lexend_general_ultrabold);
			const ImVec2 label_size = ImGui::CalcTextSize(finalText.c_str(), NULL, true);
			const ImVec2 lavender_size = ImGui::CalcTextSize(lavender.c_str(), NULL, true);
			ImGui::GetWindowDrawList()->AddText(ImVec2(pos.x + (totalsize.x / 4) - (label_size.x / 2), pos.y + 15), ImGui::GetColorU32(ImVec4{ 1,1,1,1 }), lavender.c_str());
			ImGui::GetWindowDrawList()->AddText(ImVec2(pos.x + (totalsize.x / 4) - (label_size.x / 2) + lavender_size.x + 2, pos.y + 15), ImGui::GetColorU32(c::accent), premium.c_str());
			ImGui::PopFont();

			std::string slogan = xorstr_("YOU CAN'T EVEN DREAM THIS!");
			ImGui::PushFont(font::slogan);
			const ImVec2 slogan_size = ImGui::CalcTextSize(slogan.c_str(), NULL, true);
			ImGui::GetWindowDrawList()->AddText(ImVec2(pos.x + (totalsize.x / 4) - (slogan_size.x / 2), pos.y + 18 + lavender_size.y), ImGui::GetColorU32(ImVec4{ 150.f / 255.f,150.f / 255.f,150.f / 255.f,1 }), slogan.c_str());
			ImGui::PopFont();
			ImGui::PushFont(font::main);
			{
				 
				 
				{


					std::string showesponlyenemy = xorstr_("Inject");
					const ImVec2 showesponlyenemy_size = ImGui::CalcTextSize(showesponlyenemy.c_str(), NULL, true);
					ImGui::GetWindowDrawList()->AddText(ImVec2(pos.x + (totalsize.x / 4) - (showesponlyenemy_size.x / 2), pos.y + 105 + lavender_size.y), ImGui::GetColorU32(ImVec4{ 1,1,1,1 }), showesponlyenemy.c_str());

					ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 40, ImGui::GetCursorPosY() + 175));
					ImGui::BeginGroup();
				//	ImGui::InputTextEx(xorstr_("v"), xorstr_("Just click login button "), yrkey, 65, ImVec2(ImGui::GetContentRegionMax().x - style->WindowPadding.x - 80, 40), NULL);
					if (ImGui::Button(xorstr_("Inject"), ImVec2(ImGui::GetContentRegionMax().x - style->WindowPadding.x - 80, 50)))
					{ 
						qs = true;
						ImGui::EndGroup();
					}
					ImGui::PushFont(font::copyright);
					std::string vehiclename = xorstr_("LavenderPremium copyrighted since 2024");
					const ImVec2 vehiclename_size = ImGui::CalcTextSize(vehiclename.c_str(), NULL, true);

					ImGui::PushFont(font::main);
					const ImVec2 infoBegin_size = ImGui::CalcTextSize(infoBegin.c_str(), NULL, true);
					ImGui::GetWindowDrawList()->AddText(ImVec2(pos.x + (totalsize.x / 4) - (infoBegin_size.x / 2), pos.y + 300), ImGui::GetColorU32(ImVec4{ 1,1,1,1 }), infoBegin.c_str());
					ImGui::PopFont();

					ImGui::GetWindowDrawList()->AddText(ImVec2(pos.x + (totalsize.x / 4) - (vehiclename_size.x / 2), pos.y + totalsize.y - (vehiclename_size.y * 1.6f)), ImGui::GetColorU32(ImVec4{ 1,1,1,1 }), vehiclename.c_str());
					ImGui::PopFont();
				}
				ImGui::PopFont();
			}
		}
		ImGui::EndChild();
		ImGui::SameLine(0, 0);
		ImGui::BeginChild(xorstr_("SagTaraf"), ImVec2(400, totalsize.y), false);
		{
			ImGui::PushFont(font::lexend_general_ultrabold);
			std::string fivem = xorstr_("FiveM");
			const ImVec2 fivem_size = ImGui::CalcTextSize(fivem.c_str(), NULL, true);
			ImGui::GetWindowDrawList()->AddText(ImVec2(pos.x + 400 + (totalsize.x / 4) - (fivem_size.x / 2), pos.y + 133), ImGui::GetColorU32(ImVec4{ 1,1,1,1 }), fivem.c_str());
			ImGui::PopFont();
			ImGui::PushFont(font::main);
			{
				std::string infotext = xorstr_("FiveM is a multiplayer modification framework \n                for GTA V, allowing you to \n       play on customized dedicated servers.");
				const ImVec2 infotext_size = ImGui::CalcTextSize(infotext.c_str(), NULL, true);
				ImGui::GetWindowDrawList()->AddText(ImVec2(pos.x + 400 + (totalsize.x / 4) - (infotext_size.x / 2), pos.y + 138 + fivem_size.y), ImGui::GetColorU32(ImVec4{ 220.f / 255.f,220.f / 255.f,220.f / 255.f,1 }), infotext.c_str());
				ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + (totalsize.x / 4) - (infotext_size.x / 2), ImGui::GetCursorPosY() + 143.f + fivem_size.y + infotext_size.y));
				if (ImGui::Button(xorstr_("Exit"), ImVec2(infotext_size.x, 50)))
					(exit)(0);
			}
			ImGui::PopFont();
		}
		ImGui::EndChild();
	}
	ImGui::End();


}

namespace Cheat
{
	void Initialize()
	{
		while (!g_Fivem.IsInitialized())
		{
			g_Fivem.Intialize();

			if (!g_Fivem.IsInitialized())
				std::this_thread::sleep_for(std::chrono::seconds(5));
		}

		FrameWork::Overlay::Setup(g_Fivem.GetPid());
		FrameWork::Overlay::Initialize();

		if (FrameWork::Overlay::IsInitialized())
		{
			FrameWork::Interface Interface(FrameWork::Overlay::GetOverlayWindow(), FrameWork::Overlay::GetTargetWindow(), FrameWork::Overlay::dxGetDevice(), FrameWork::Overlay::dxGetDeviceContext());
			Interface.UpdateStyle();
			ImGuiIO& io = ImGui::GetIO();
			io.IniFilename = NULL;
			font::lexend_visuals = io.Fonts->AddFontFromMemoryTTF(lexend_bold, sizeof(lexend_bold), 14.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
			font::lexend_general_bold = io.Fonts->AddFontFromMemoryTTF(lexend_bold, sizeof(lexend_bold), 18.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
			font::lexend_bold = io.Fonts->AddFontFromMemoryTTF(lexend_regular, sizeof(lexend_regular), 17.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
			font::lexend_regular = io.Fonts->AddFontFromMemoryTTF(lexend_regular, sizeof(lexend_regular), 14.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
			font::lexend_general_ultrabold = io.Fonts->AddFontFromMemoryTTF(lexend_bold, sizeof(lexend_bold), 38.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
			font::slogan = io.Fonts->AddFontFromMemoryTTF(lexend_regular, sizeof(lexend_regular), 25.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
			font::copyright = io.Fonts->AddFontFromMemoryTTF(lexend_regular, sizeof(lexend_regular), 13.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
			font::icomoon = io.Fonts->AddFontFromMemoryTTF(icomoon, sizeof(icomoon), 20.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
			font::icomoon_widget = io.Fonts->AddFontFromMemoryTTF(icomoon_widget, sizeof(icomoon_widget), 15.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
			font::icomoon_widget2 = io.Fonts->AddFontFromMemoryTTF(icomoon, sizeof(icomoon), 16.f, NULL, io.Fonts->GetGlyphRangesCyrillic());
			font::menuFnt = io.Fonts->AddFontFromFileTTF(xorstr_("C:\\Windows\\Fonts\\Arial.ttf"), 18.f, NULL, io.Fonts->GetGlyphRangesDefault());
			font::menuBoldFont = io.Fonts->AddFontFromFileTTF(xorstr_("C:\\Windows\\Fonts\\Arial.ttf"), 25.f, NULL, io.Fonts->GetGlyphRangesDefault());
			D3DX11_IMAGE_LOAD_INFO info;
			ID3DX11ThreadPump* pump{ nullptr };

			D3DX11CreateShaderResourceViewFromMemory(FrameWork::Overlay::dxGetDevice(), backgroundLOGO, sizeof(backgroundLOGO), &info, pump, &Image, 0);

			FrameWork::Overlay::SetupWindowProcHook(std::bind(&FrameWork::Interface::WindowProc, &Interface, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

			MSG Message;
			ZeroMemory(&Message, sizeof(Message));
			while (Message.message != WM_QUIT)
			{
				if (PeekMessage(&Message, FrameWork::Overlay::GetOverlayWindow(), NULL, NULL, PM_REMOVE))
				{
					TranslateMessage(&Message);
					DispatchMessage(&Message);
				}

				ImGui::GetIO().MouseDrawCursor = Interface.GetMenuOpen();



				if (Interface.ResizeHeight != 0 || Interface.ResizeWidht != 0)
				{
					FrameWork::Overlay::dxCleanupRenderTarget();
					FrameWork::Overlay::dxGetSwapChain()->ResizeBuffers(0, Interface.ResizeWidht, Interface.ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
					Interface.ResizeHeight = Interface.ResizeWidht = 0;
					FrameWork::Overlay::dxCreateRenderTarget();
				}

				Interface.HandleMenuKey();
				FrameWork::Overlay::UpdateWindowPos();

				ImGui_ImplDX11_NewFrame();
				ImGui_ImplWin32_NewFrame();
				ImGui::NewFrame();
				g_Fivem.UpdateEntities();
				{

					if (!qs)
						lgNTab();
					else
					{
						 


							float oldfsize2 = ImGui::GetFont()->Scale;
							ImGui::PushFont(font::lexend_general_bold);
							auto draw_list = ImGui::GetBackgroundDrawList();
							std::string watermark = (xorstr_("LavenderPREMIUM | FiveM Best Legit Cheat | dc: bapseny | bapseny a.k.a skechtew"));
							auto watermark_size = ImGui::CalcTextSize(watermark.c_str(), NULL, true);

							draw_list->xAddRectFilledMultiColor(ImVec2(6, 6), ImVec2((4 * 2) + watermark_size.x + 6, 50), ImGui::GetColorU32(c::elements::background), ImGui::GetColorU32(c::background::filling), ImGui::GetColorU32(c::background::filling), ImGui::GetColorU32(c::elements::background), 4.f);
							draw_list->AddRect(ImVec2(6, 6), ImVec2((4 * 2) + watermark_size.x + 6, 50), ImGui::GetColorU32(c::accent), 4.f);

							draw_list->AddText(ImVec2(10, 25 - (watermark_size.y / 2)), ImColor(255, 255, 255, 255), watermark.c_str());
						 
						g_Fivem.visual();
						g_Fivem.player();
						g_Fivem.vehicle();  
				        g_Fivem.aimbot();
						if (g_Options.Aimbot.drawFov)
							ImGui::GetBackgroundDrawList()->AddCircle(ImVec2((GetSystemMetrics(SM_CXSCREEN)) / 2, (GetSystemMetrics(SM_CYSCREEN)) / 2), g_Options.Aimbot.fov, ImColor(255, 255, 255), 500, 2.f);
						Interface.RenderGui();
					}
				}
				ImGui::EndFrame();
				ImGui::Render();

				FrameWork::Overlay::dxRefresh();
				ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
				FrameWork::Overlay::dxGetSwapChain()->Present(0, 0);

				if (g_Options.General.ShutDown)
					return;

				std::this_thread::sleep_for(std::chrono::milliseconds(1 + g_Options.General.ThreadDelay));
			}
		}
	}

	void ShutDown()
	{
		if (!g_Options.General.ShutDown)
			return;

		FrameWork::Overlay::ShutDown();
		FrameWork::Overlay::dxShutDown();

		FrameWork::Memory::DetachProcess();
	}
}