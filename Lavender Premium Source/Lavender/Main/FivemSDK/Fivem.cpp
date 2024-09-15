#include "Fivem.hpp"
#include <fstream>
#include <filesystem>
#include <thread>
#include "driver.h"
#include "../Cheat.hpp"
#include <d3dx9.h>
#include "simplemath.h"
const char* get_weapon_name(DWORD hash)
{
	//removed xoring, cba to do properly.
	const char* dagger = ("Dagger");
	const char* bat = ("Bat");
	const char* bottle = ("Bottle");
	const char* crowbar = ("Crow Bar");
	const char* unarmed = ("None");
	const char* flashlight = ("Flash Light");
	const char* golfclub = ("Golf club");
	const char* hammer = ("Hammer");
	const char* hatchet = ("Hatchet");
	const char* knuckle = ("Knuckle");
	const char* knife = ("Knife");
	const char* machete = ("Machete");
	const char* switchblade = ("Switch Blade");
	const char* nightstick = ("Night Stick");
	const char* wrench = ("Wrench");
	const char* battleaxe = ("Battle Axe");
	const char* poolcue = ("Pool Cue");
	const char* pistol = ("Pistol");
	const char* pistolmk2 = ("Pistol MK2");
	const char* combatpistol = ("Combat Pistol");
	const char* appistol = ("AP Pistol");
	const char* stungun = ("Stungun");
	const char* pistol50 = ("Pistol 50");
	const char* snspistol = ("SNS PISTOL");
	const char* snspistolmk2 = ("SNS Pistol MK2");
	const char* heavypistol = ("Heavy Pistol");
	const char* vintagepistol = ("Vintage Pisol");
	const char* flaregun = ("Flare Gun");
	const char* marksmanpistol = ("marksmanpistol");
	const char* revolver = ("Revolver");
	const char* revolvermk2 = ("Revolver MK2");
	static auto doubleaction = ("Double Action");
	static auto microsmg = ("Micro Smg");
	static auto smg = ("Smg");
	static auto smgmk2 = ("Smg MK2");
	static auto assaultsmg = ("Assault Smg");
	static auto combatpdw = ("Combat PDW");
	static auto machinepistol = ("Machine Pistol");
	static auto minismg = ("Mini Smg");
	const char* pumpshotgun = ("Pump Shotgun");
	static auto pumpshotgun_mk2 = ("Pump Shotgun MK2");
	static auto sawnoffshotgun = ("Sawnoff Shotgun");
	static auto assaultshotgun = ("Sssault Shotgun");
	static auto bullpupshotgun = ("Bullpup Shotgun");
	static auto musket = ("Musket");
	static auto heavyshotgun = ("Heavy Shotgun");
	static auto dbshotgun = ("DB Shotgun");
	static auto autoshotgun = ("Auto Shotgun");
	static auto assaultrifle = ("Assault Rifle");
	static auto assaultrifle_mk2 = ("Assault Rifle MK2");
	const char* carbinerifle = ("Carbine Rifle");
	static auto carbinerifle_mk2 = ("Carbine Rifle MK2");
	static auto advancedrifle = ("Advanced Rifle");
	static auto specialcarbine = ("Special Carbine");
	static auto specialcarbine_mk2 = ("Special Carbine MK2");
	static auto bullpuprifle = ("Bullpup Rifle");
	static auto bullpuprifle_mk2 = ("Bullpup Rifle MK2");
	static auto compactrifle = ("Compact Rifle");
	static auto machine_gun = ("Machine Gun");
	static auto combatmg = ("Combat MG");
	static auto combatmg_mk2 = ("Combat MG MK2");
	static auto gusenberg = ("GUSENBERG");
	static auto sniperrifle = ("Sniper Rifle");
	static auto heavysniper = ("AWP");
	static auto heavysniper_mk2 = ("AWP MK2");
	static auto marksmanrifle = ("Marksman Rifle");
	static auto marksmanrifle_mk2 = ("Marksman Rifle MK2");
	static auto rpg = ("RPG");
	static auto grenadelauncher = ("Grenade Launcher");
	static auto grenadelauncher_smoke = ("Grenade Launcher Smoke");
	static auto minigun = ("MiniGun");
	static auto firework = ("FireWork");
	static auto railgun = ("RailGun");
	static auto hominglauncher = ("Homing Launcher");
	static auto compactlauncher = ("Compact Launcher");
	static auto grenade = ("Grenade");
	static auto bzgas = ("BZGAS");
	static auto smokegrenade = ("Smoke Grenade");
	static auto flare = ("Flare");
	static auto molotov = ("Molotov");
	static auto stickybomb = ("Sticky BOMB");
	static auto proxmine = ("Prox Mine");
	static auto snowball = ("SnowBall");
	static auto pipebomb = ("Pipe Bomb");
	static auto ball = ("Ball");
	static auto petrolcan = ("Petrol Can");
	static auto fireextinguisher = ("Fire Extinguisher");
	static auto parachute = ("Parachute");

	switch (hash)
	{
	case 0x92A27487:
		return dagger; break;
	case 0x958A4A8F:
		return bat; break;
	case 0xF9E6AA4B:
		return bottle; break;
	case 0x84BD7BFD:
		return crowbar; break;
	case 0xA2719263:
		return unarmed; break;
	case 0x8BB05FD7:
		return flashlight; break;
	case 0x440E4788:
		return golfclub; break;
	case 0x4E875F73:
		return hammer; break;
	case 0xF9DCBF2D:
		return hatchet; break;
	case 0xD8DF3C3C:
		return knuckle; break;
	case 0x99B507EA:
		return knife; break;
	case 0xDD5DF8D9:
		return machete; break;
	case 0xDFE37640:
		return switchblade; break;
	case 0x678B81B1:
		return nightstick; break;
	case 0x19044EE0:
		return wrench; break;
	case 0xCD274149:
		return battleaxe; break;
	case 0x94117305:
		return poolcue; break;
	case 0x1B06D571:
		return pistol; break;
	case 0xBFE256D4:
		return pistolmk2; break;
	case 0x5EF9FEC4:
		return combatpistol; break;
	case 0x22D8FE39:
		return appistol; break;
	case 0x3656C8C1:
		return stungun; break;
	case 0x99AEEB3B:
		return pistol50; break;
	case 0xBFD21232:
		return snspistol; break;
	case 0x88374054:
		return snspistolmk2; break;
	case 0xD205520E:
		return heavypistol; break;
	case 0x83839C4:
		return vintagepistol; break;
	case 0x47757124:
		return flaregun; break;
	case 0xDC4DB296:
		return marksmanpistol; break;
	case 0xC1B3C3D1:
		return revolver; break;
	case 0xCB96392F:
		return revolvermk2; break;
	case 0x97EA20B8:
		return doubleaction; break;
	case 0x13532244:
		return microsmg; break;
	case 0x2BE6766B:
		return smg; break;
	case 0x78A97CD0:
		return smgmk2; break;
	case 0xEFE7E2DF:
		return assaultsmg; break;
	case 0xA3D4D34:
		return combatpdw; break;
	case 0xDB1AA450:
		return machinepistol; break;
	case 0xBD248B55:
		return minismg; break;
	case 0x1D073A89:
		return pumpshotgun; break;
	case 0x555AF99A:
		return pumpshotgun_mk2; break;
	case 0x7846A318:
		return sawnoffshotgun; break;
	case 0xE284C527:
		return assaultshotgun; break;
	case 0x9D61E50F:
		return bullpupshotgun; break;
	case 0xA89CB99E:
		return musket; break;
	case 0x3AABBBAA:
		return heavyshotgun; break;
	case 0xEF951FBB:
		return dbshotgun; break;
	case 0x12E82D3D:
		return autoshotgun; break;
	case 0xBFEFFF6D:
		return assaultrifle; break;
	case 0x394F415C:
		return assaultrifle_mk2; break;
	case 0x83BF0278:
		return carbinerifle; break;
	case 0xFAD1F1C9:
		return carbinerifle_mk2; break;
	case 0xAF113F99:
		return advancedrifle; break;
	case 0xC0A3098D:
		return specialcarbine; break;
	case 0x969C3D67:
		return specialcarbine_mk2; break;
	case 0x7F229F94:
		return bullpuprifle; break;
	case 0x84D6FAFD:
		return bullpuprifle_mk2; break;
	case 0x624FE830:
		return compactrifle; break;
	case 0x9D07F764:
		return machine_gun; break;
	case 0x7FD62962:
		return combatmg; break;
	case 0xDBBD7280:
		return combatmg_mk2; break;
	case 0x61012683:
		return gusenberg; break;
	case 0x5FC3C11:
		return sniperrifle; break;
	case 0xC472FE2:
		return heavysniper; break;
	case 0xA914799:
		return heavysniper_mk2; break;
	case 0xC734385A:
		return marksmanrifle; break;
	case 0x6A6C02E0:
		return marksmanrifle_mk2; break;
	case 0xB1CA77B1:
		return rpg; break;
	case 0xA284510B:
		return grenadelauncher; break;
	case 0x4DD2DC56:
		return grenadelauncher_smoke; break;
	case 0x42BF8A85:
		return minigun; break;
	case 0x7F7497E5:
		return firework; break;
	case 0x6D544C99:
		return railgun; break;
	case 0x63AB0442:
		return hominglauncher; break;
	case 0x781FE4A:
		return compactlauncher; break;
	case 0x93E220BD:
		return grenade; break;
	case 0xA0973D5E:
		return bzgas; break;
	case 0xFDBC8A50:
		return smokegrenade; break;
	case 0x497FACC3:
		return flare; break;
	case 0x24B17070:
		return molotov; break;
	case 0x2C3731D9:
		return stickybomb; break;
	case 0xAB564B93:
		return proxmine; break;
	case 0x787F0BB:
		return snowball; break;
	case 0xBA45E8B8:
		return pipebomb; break;
	case 0x23C9F95C:
		return ball; break;
	case 0x34A67B97:
		return petrolcan; break;
	case 0x60EC506:
		return fireextinguisher; break;
	case 0xFBAB5776:
		return parachute; break;
	default:
		return unarmed; break;
	}
}
Vector3D  GetBone(DWORD64 cPed, int Bone)
{
	D3DXMATRIX matrix = FrameWork::Memory::ReadMemory<D3DXMATRIX>(cPed + 0x60);
	D3DXVECTOR3 bone;
	if (Cheat::g_Fivem.GameVersion == Cheat::GAME_VERSION_GAME_b2802 || Cheat::g_Fivem.GameVersion == Cheat::GAME_VERSION_GTA_b2802 || Cheat::g_Fivem.GameVersion == Cheat::GAME_VERSION_GTA_b3095 || Cheat::g_Fivem.GameVersion == Cheat::GAME_VERSION_GAME_b3095)
		bone = FrameWork::Memory::ReadMemory < D3DXVECTOR3>(cPed + (0x410 + 0x10 * Bone));
	else
		bone = FrameWork::Memory::ReadMemory < D3DXVECTOR3>(cPed + (0x430 + Bone * 0x10));

	D3DXVECTOR4 transform;
	D3DXVec3Transform(&transform, &bone, &matrix);

	return Vector3D(transform.x, transform.y, transform.z);
}


void DrawOutlinedText(ImFont* pFont, const std::string& text, const ImVec2& pos, float size, ImU32 color, bool center)
{
	std::stringstream stream(text);
	std::string line;

	float y = 0.0f;
	int index = 0;

	while (std::getline(stream, line))
	{
		ImVec2 textSize = pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, line.c_str());

		if (center)
		{

			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2(pos.x - textSize.x / 2.0f - 1, pos.y + textSize.y * index - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 1)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2(pos.x - textSize.x / 2.0f + 1, pos.y + textSize.y * index + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 1)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2(pos.x - textSize.x / 2.0f + 1, pos.y + textSize.y * index - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 1)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2(pos.x - textSize.x / 2.0f - 1, pos.y + textSize.y * index + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 1)), line.c_str());

			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * index), ImGui::GetColorU32(color), line.c_str());
		}
		else
		{//

			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2(pos.x - 1, pos.y + textSize.y * index - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 1)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2(pos.x + 1, pos.y + textSize.y * index + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 1)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2(pos.x + 1, pos.y + textSize.y * index - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 1)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2(pos.x - 1, pos.y + textSize.y * index + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 1)), line.c_str());

			ImGui::GetBackgroundDrawList()->AddText(pFont, size, ImVec2(pos.x, pos.y + textSize.y * index), ImGui::GetColorU32(color), line.c_str());
		}

		y = pos.y + textSize.y * (index + 1);
		index++;
	}
}

int getPt(int n1, int n2, float perc)
{
	return n1 + ((n2 - n1) * perc);
}

int getRnd(int min, int max) {
	return (rand() % (max - min)) + min;
}

void HumanizedMovement(int targetX, int targetY) {
	POINT pInicial = { 0, 0 };
	POINT pLastMove = { 0, 0 };
	POINT pMedio1;
	POINT pMedio2;
	POINT pFinal;

	pFinal.x = targetX;
	pFinal.y = targetY;


	if ((pFinal.x >= pInicial.x && pFinal.y >= pInicial.y) || (pFinal.x <= pInicial.x && pFinal.y <= pInicial.y))
	{
		pMedio1.x = pInicial.x + ((pFinal.x - pInicial.x) / getRnd(4, 8));
		pMedio1.y = pInicial.y + ((pFinal.x - pInicial.x) / getRnd(4, 8));

		pMedio2.x = pInicial.x + ((pFinal.x - pInicial.x) / getRnd(3, 6));
		pMedio2.y = pInicial.y + ((pFinal.x - pInicial.x) / getRnd(3, 6));
	}
	else if ((pFinal.x >= pInicial.x && pFinal.y <= pInicial.y) || (pFinal.x <= pInicial.x && pFinal.y >= pInicial.y))
	{
		pMedio1.x = pInicial.x + ((pFinal.x - pInicial.x) / getRnd(4, 8));
		pMedio1.y = pInicial.y - ((pFinal.x - pInicial.x) / getRnd(4, 8));

		pMedio2.x = pInicial.x + ((pFinal.x - pInicial.x) / getRnd(3, 5));
		pMedio2.y = pInicial.y - ((pFinal.x - pInicial.x) / getRnd(3, 5));
	}
	POINT total = { 0,0 };

	for (float i = 0; i < 1.01; i += 0.01)
	{
		int xa = getPt(pInicial.x, pMedio1.x, i);
		int ya = getPt(pInicial.y, pMedio1.y, i);
		int xb = getPt(pMedio1.x, pMedio2.x, i);
		int yb = getPt(pMedio1.y, pMedio2.y, i);
		int xc = getPt(pMedio2.x, pFinal.x, i);
		int yc = getPt(pMedio2.y, pFinal.y, i);

		int xm = getPt(xa, xb, i);
		int ym = getPt(ya, yb, i);
		int xn = getPt(xb, xc, i);
		int yn = getPt(yb, yc, i);

		int x = getPt(xm, xn, i);
		int y = getPt(ym, yn, i);

		POINT move = { x - pLastMove.x, y - pLastMove.y }; //Relative movement
		MouseController mouse;
		mouse.MoveMouse(move.x, move.y);

		pLastMove.x = x;
		pLastMove.y = y;
	}
}
namespace Cheat
{
	uint64_t Offsets::Health;
	uint64_t Offsets::Armor;
	uint64_t Offsets::EntityType;
	uint64_t Offsets::PlayerInfo;
	uint64_t Offsets::patchOffset;
	uint64_t Offsets::WeaponManager;
	uint64_t Offsets::PlayerNetID;
	uint64_t Offsets::FreezeOffst;
	uint64_t Offsets::Vehicle;
	uint64_t Offsets::Handling;

	void FivemSDK::Intialize()
	{
		if (bIsIntialized)
			return;

		if (FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2060_GameProcess.exe")) || FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2060_GTAProcess.exe")))
		{
			Pid = FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2060_GameProcess.exe"));
			if (Pid)
			{
				GameVersion = GAME_VERSION_GAME_b2060;
				ModuleName = xorstr_("FiveM_b2060_GameProcess.exe");
			}
			else
			{
				Pid = FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2060_GTAProcess.exe"));
				GameVersion = GAME_VERSION_GTA_b2060;
				ModuleName = xorstr_("FiveM_b2060_GTAProcess.exe");
			}

			ModuleBase = FrameWork::Memory::GetModuleBaseByName(Pid, FrameWork::Misc::String2WString(ModuleName));
			if (ModuleBase)
			{
				World = ModuleBase + 0x24C8858;
				ReplayInterface = ModuleBase + 0x1EC3828;
				ViewPort = ModuleBase + 0x1F6A7E0;
				Camera = ModuleBase + 0x1F6B940;
				FreezeOffst = 0x218;
				Vehicle = 0x0D28;
				Handling = 0x938;
				PubWorld = World;
				PubReplayInterface = ReplayInterface;
				PubViewPort = ViewPort;
				PubCamera = Camera;

				Offsets::EntityType = 0x10B8;
				Offsets::PlayerInfo = 0x10A8;
				Offsets::WeaponManager = 0x10D8;
				Offsets::PlayerNetID = 0x78;
				Offsets::Health = 0x280;
				Offsets::Armor = 0x14E0;
				bIsIntialized = true;
			}
		}
		else if (FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2189_GameProcess.exe")) || FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2189_GTAProcess.exe")))
		{
			Pid = FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2189_GameProcess.exe"));
			if (Pid)
			{
				GameVersion = GAME_VERSION_GAME_b2189;
				ModuleName = xorstr_("FiveM_b2189_GameProcess.exe");
			}
			else
			{
				Pid = FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2189_GTAProcess.exe"));
				GameVersion = GAME_VERSION_GTA_b2189;
				ModuleName = xorstr_("FiveM_b2189_GTAProcess.exe");
			}

			ModuleBase = FrameWork::Memory::GetModuleBaseByName(Pid, FrameWork::Misc::String2WString(ModuleName));
			if (ModuleBase)
			{
				World = ModuleBase + 0x24E6D90;
				ReplayInterface = ModuleBase + 0x1EE18A8;
				ViewPort = ModuleBase + 0x1F888C0;
				Camera = ModuleBase + 0x1F89768;
				FreezeOffst = 0x218;
				Vehicle = 0x0D30;
				Handling = 0x938;
				PubWorld = World;
				PubReplayInterface = ReplayInterface;
				PubViewPort = ViewPort;
				PubCamera = Camera;
				Offsets::EntityType = 0x10B8;
				Offsets::PlayerInfo = 0x10C8;
				Offsets::WeaponManager = 0x10D8;
				Offsets::PlayerNetID = 0x78;
				Offsets::Health = 0x280;
				Offsets::Armor = 0x14E0;

				bIsIntialized = true;
			}
		}
		else if (FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2372_GameProcess.exe")) || FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2372_GTAProcess.exe")))
		{
			Pid = FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2372_GameProcess.exe"));
			if (Pid)
			{
				GameVersion = GAME_VERSION_GAME_b2372;
				ModuleName = xorstr_("FiveM_b2372_GameProcess.exe");
			}
			else
			{
				Pid = FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2372_GTAProcess.exe"));
				GameVersion = GAME_VERSION_GTA_b2372;
				ModuleName = xorstr_("FiveM_b2372_GTAProcess.exe");
			}

			ModuleBase = FrameWork::Memory::GetModuleBaseByName(Pid, FrameWork::Misc::String2WString(ModuleName));
			if (ModuleBase)
			{
				World = ModuleBase + 0x252DCD8;
				ReplayInterface = ModuleBase + 0x1F05208;
				ViewPort = ModuleBase + 0x1F9E9F0;
				Camera = ModuleBase + 0x1F9F898;
				PubWorld = World;
				FreezeOffst = 0x218;
				PubReplayInterface = ReplayInterface;
				PubViewPort = ViewPort;
				Vehicle = 0x0D30;
				Handling = 0x938;
				PubCamera = Camera;
				Offsets::EntityType = 0x10B8;
				Offsets::PlayerInfo = 0x10C8;
				Offsets::WeaponManager = 0x10D8;
				Offsets::PlayerNetID = 0x88;
				Offsets::Health = 0x280;
				Offsets::Armor = 0x14E0;
				bIsIntialized = true;
			}
		}
		else if (FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2545_GameProcess.exe")) || FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2545_GTAProcess.exe")))
		{
			Pid = FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2545_GameProcess.exe"));
			if (Pid)
			{
				GameVersion = GAME_VERSION_GAME_b2545;
				ModuleName = xorstr_("FiveM_b2545_GameProcess.exe");
			}
			else
			{
				Pid = FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2545_GTAProcess.exe"));
				GameVersion = GAME_VERSION_GTA_b2545;
				ModuleName = xorstr_("FiveM_b2545_GTAProcess.exe");
			}

			ModuleBase = FrameWork::Memory::GetModuleBaseByName(Pid, FrameWork::Misc::String2WString(ModuleName));
			if (ModuleBase)
			{
				World = ModuleBase + 0x25667E8;
				ReplayInterface = ModuleBase + 0x1F2E7A8;
				ViewPort = ModuleBase + 0x1FD6F70;
				Camera = ModuleBase + 0x1FD7E18;
				PubWorld = World;
				Vehicle = 0x0D30;
				Handling = 0x938;
				FreezeOffst = 0x238;
				PubReplayInterface = ReplayInterface;
				PubViewPort = ViewPort;
				PubCamera = Camera;
				Offsets::EntityType = 0x10B8;
				Offsets::PlayerInfo = 0x10A8;
				Offsets::WeaponManager = 0x10D8;
				Offsets::PlayerNetID = 0x88;
				Offsets::Health = 0x280;
				Offsets::Armor = 0x14E0 + 0x50;
				bIsIntialized = true;
			}
		}
		else if (FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2612_GameProcess.exe")) || FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2612_GTAProcess.exe")))
		{
			Pid = FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2612_GameProcess.exe"));
			if (Pid)
			{
				GameVersion = GAME_VERSION_GAME_b2612;
				ModuleName = xorstr_("FiveM_b2612_GameProcess.exe");
			}
			else
			{
				Pid = FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2612_GTAProcess.exe"));
				GameVersion = GAME_VERSION_GTA_b2612;
				ModuleName = xorstr_("FiveM_b2612_GTAProcess.exe");
			}

			ModuleBase = FrameWork::Memory::GetModuleBaseByName(Pid, FrameWork::Misc::String2WString(ModuleName));
			if (ModuleBase)
			{
				World = ModuleBase + 0x2567DB0;
				ReplayInterface = ModuleBase + 0x1F77EF0;
				ViewPort = ModuleBase + 0x1FD8570;
				Camera = ModuleBase + 0x1FD9418;
				PubWorld = World;
				FreezeOffst = 0x238;
				Vehicle = 0x0D30;
				Handling = 0x938;
				PubReplayInterface = ReplayInterface;
				PubViewPort = ViewPort;
				PubCamera = Camera;
				Offsets::EntityType = 0x10B8;
				Offsets::PlayerInfo = 0x10C8;
				Offsets::WeaponManager = 0x10D8;
				Offsets::PlayerNetID = 0x88;
				Offsets::Health = 0x280;
				Offsets::Armor = 0x1530;
				bIsIntialized = true;
			}
		}
		else if (FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2699_GameProcess.exe")) || FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2699_GTAProcess.exe")))
		{
			Pid = FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2699_GameProcess.exe"));
			if (Pid)
			{
				GameVersion = GAME_VERSION_GAME_b2699;
				ModuleName = xorstr_("FiveM_b2699_GameProcess.exe");
			}
			else
			{
				Pid = FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2699_GTAProcess.exe"));
				GameVersion = GAME_VERSION_GTA_b2699;
				ModuleName = xorstr_("FiveM_b2699_GTAProcess.exe");
			}

			ModuleBase = FrameWork::Memory::GetModuleBaseByName(Pid, FrameWork::Misc::String2WString(ModuleName));
			if (ModuleBase)
			{
				World = ModuleBase + 0x26684D8;
				ReplayInterface = ModuleBase + 0x20304C8;
				ViewPort = ModuleBase + 0x20D8C90;
				Camera = ModuleBase + 0x20D9B38;
				PubWorld = World;
				FreezeOffst = 0x238;
				Vehicle = 0x0D30;
				Handling = 0x938;
				PubReplayInterface = ReplayInterface;
				PubViewPort = ViewPort;
				PubCamera = Camera;
				Offsets::EntityType = 0x10B8;
				Offsets::PlayerInfo = 0x10C8;
				Offsets::WeaponManager = 0x10D8;
				Offsets::PlayerNetID = 0x88;
				Offsets::Health = 0x280;
				Offsets::Armor = 0x1530;
				bIsIntialized = true;
			}
		}
		else if (FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2802_GameProcess.exe")) || FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2802_GTAProcess.exe")))
		{
			Pid = FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2802_GameProcess.exe"));
			if (Pid)
			{
				GameVersion = GAME_VERSION_GAME_b2802;
				ModuleName = xorstr_("FiveM_b2802_GameProcess.exe");
			}
			else
			{
				Pid = FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2802_GTAProcess.exe"));
				GameVersion = GAME_VERSION_GTA_b2802;
				ModuleName = xorstr_("FiveM_b2802_GTAProcess.exe");
			}

			ModuleBase = FrameWork::Memory::GetModuleBaseByName(Pid, FrameWork::Misc::String2WString(ModuleName));
			if (ModuleBase)
			{
				World = ModuleBase + 0x254D448;
				ReplayInterface = ModuleBase + 0x1F5B820;
				ViewPort = ModuleBase + 0x1FBC100;
				Camera = ModuleBase + 0x1FBCFA8;
				PubWorld = World;
				FreezeOffst = 0x250;
				Vehicle = 0x0D10;
				Handling = 0x938;
				PubReplayInterface = ReplayInterface;
				PubViewPort = ViewPort;
				PubCamera = Camera;
				Offsets::EntityType = 0x1098;
				Offsets::PlayerInfo = 0x10A8;
				Offsets::WeaponManager = 0x10B8;
				Offsets::PlayerNetID = 0x88;
				Offsets::Health = 0x284;
				Offsets::Armor = 0x150C;
				bIsIntialized = true;
				//	isb2802 = true;
			}
		}
		else if (FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2944_GameProcess.exe")) || FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2944_GTAProcess.exe")))
		{
			Pid = FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2944_GameProcess.exe"));
			if (Pid)
			{
				GameVersion = GAME_VERSION_GAME_b2944;
				ModuleName = xorstr_("FiveM_b2944_GameProcess.exe");
			}
			else
			{
				Pid = FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b2944_GTAProcess.exe"));
				GameVersion = GAME_VERSION_GTA_b2944;
				ModuleName = xorstr_("FiveM_b2944_GTAProcess.exe");
			}

			ModuleBase = FrameWork::Memory::GetModuleBaseByName(Pid, FrameWork::Misc::String2WString(ModuleName));
			if (ModuleBase)
			{
				World = ModuleBase + 0x257BEA0;
				ReplayInterface = ModuleBase + 0x1F42068;
				ViewPort = ModuleBase + 0x1FEAAC0;
				Camera = ModuleBase + 0x1FEB968;
				PubWorld = World;
				Vehicle = 0x0D10;
				Handling = 0x918;
				PubReplayInterface = ReplayInterface;
				PubViewPort = ViewPort;
				PubCamera = Camera;
				FreezeOffst = 0x250;
				Offsets::EntityType = 0x1098;
				Offsets::PlayerInfo = 0x10A8;
				Offsets::WeaponManager = 0x10B8;
				Offsets::PlayerNetID = 0xE8;
				Offsets::Health = 0x280;
				Offsets::Armor = 0x150C;
				bIsIntialized = true;
			}
		}
		else if (FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b3095_GameProcess.exe")) || FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b3095_GTAProcess.exe")))
		{
			Pid = FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b3095_GameProcess.exe"));
			if (Pid)
			{
				GameVersion = GAME_VERSION_GAME_b3095;
				ModuleName = xorstr_("FiveM_b3095_GameProcess.exe");
			}
			else
			{
				Pid = FrameWork::Memory::GetProcessPidByName(xorstr_(L"FiveM_b3095_GTAProcess.exe"));
				GameVersion = GAME_VERSION_GTA_b3095;
				ModuleName = xorstr_("FiveM_b3095_GTAProcess.exe");
			}

			ModuleBase = FrameWork::Memory::GetModuleBaseByName(Pid, FrameWork::Misc::String2WString(ModuleName));
			if (ModuleBase)
			{
				World = ModuleBase + 0x2593320;
				ReplayInterface = ModuleBase + 0x1F58B58;
				ViewPort = ModuleBase + 0x20019E0;
				Camera = ModuleBase + 0x2002888;
				FreezeOffst = 0x250;
				PubWorld = World;
				Vehicle = 0x0D10;
				Handling = 0x918;
				PubReplayInterface = ReplayInterface;
				PubViewPort = ViewPort;
				PubCamera = Camera;
				Offsets::EntityType = 0x1098;
				Offsets::PlayerInfo = 0x10A8;
				Offsets::WeaponManager = 0x10B8;
				Offsets::PlayerNetID = 0xE8;
				Offsets::Health = 0x280;
				Offsets::Armor = 0x150C;
				bIsIntialized = true;
			}
		}

		if (bIsIntialized)
			FrameWork::Memory::AttachProces(Pid);
	}

	void FivemSDK::UpdateEntities()
	{
		if (!pWorld)
		{
			pWorld = (CWorld*)FrameWork::Memory::ReadMemory<uint64_t>(World);

			if (!pWorld)
				return;

#ifdef _DEBUG
			std::cout << xorstr_("[FivemSDK] World: 0x") << std::hex << std::uppercase << pWorld << std::endl;
#endif // _DEBUG
		}

		pLocalPlayer = pWorld->LocalPlayer();

		if (!pLocalPlayer)
			return;

#ifdef _DEBUG
		static bool Logged = false;
		if (!Logged)
		{
			std::cout << xorstr_("[FivemSDK] LocalPlayer: 0x") << std::hex << std::uppercase << pLocalPlayer << std::endl;
			Logged = true;
		}
#endif // _DEBUG

		if (!pReplayInterface)
		{
			pReplayInterface = (CReplayInterface*)FrameWork::Memory::ReadMemory<uint64_t>(ReplayInterface);

			if (!pReplayInterface)
				return;

#ifdef _DEBUG
			std::cout << xorstr_("[FivemSDK] ReplayInterface: 0x") << std::hex << std::uppercase << pReplayInterface << std::endl;
#endif // _DEBUG
		}

		if (!pPedInterface)
		{
			pPedInterface = pReplayInterface->PedInterface();

			if (!pPedInterface)
				return;

#ifdef _DEBUG
			std::cout << xorstr_("[FivemSDK] PedInterface: 0x") << std::hex << std::uppercase << pPedInterface << std::endl;
#endif // _DEBUG
		}

		if (!pCamGameplayDirector)
		{
			pCamGameplayDirector = (CCamGameplayDirector*)FrameWork::Memory::ReadMemory<uint64_t>(Camera);

			if (!pCamGameplayDirector)
				return;

#ifdef _DEBUG
			std::cout << xorstr_("[FivemSDK] CamGameplayDirector: 0x") << std::hex << std::uppercase << pCamGameplayDirector << std::endl;
#endif // _DEBUG
		}

		LockList.lock();

		EntityList.clear();
		EntityList.shrink_to_fit();

		for (size_t i = 0; i < pPedInterface->PedsAtList(); i++)
		{
			CPed* Ped = pPedInterface->PedList()->Ped(i);

			if (!Ped)
				continue;

			if (Ped->GetHealth() <= 0)
				continue;
			Vector3D PedPos = Ped->GetCoordinate();
			Vector3D HPos(PedPos.x, PedPos.y, PedPos.z + 0.8f);

			ImVec2 Head = WorldToScreen(HPos);
			if (CachedStaticInfoList.find(Ped) == CachedStaticInfoList.end())
			{
				PedStaticInfo StaticInfo;
				{
					StaticInfo.Ped = Ped;
					StaticInfo.iIndex = i;
					StaticInfo.bIsLocalPlayer = (Ped == pLocalPlayer);
					StaticInfo.bIsNPC = Ped->IsNPC();

					if (StaticInfo.bIsNPC || LanGame)
					{
						StaticInfo.NetId = -1;
					}
					else
					{
						StaticInfo.NetId = Ped->GetPlayerInfo()->GetPlayerID();
					}
				}

				CachedStaticInfoList[Ped] = StaticInfo;
			}

			Entity CurrentEntity;
			CurrentEntity.StaticInfo = CachedStaticInfoList[Ped];

			if (CurrentEntity.StaticInfo.Name.empty())
			{
				if (CurrentEntity.StaticInfo.bIsNPC)
				{
					CurrentEntity.StaticInfo.Name = xorstr_("NPC");
				}

				if (!PlayersInfo.empty() && !PlayerIdToName.empty())
				{
					auto it = PlayerIdToName.find(CurrentEntity.StaticInfo.NetId);

					if (it != PlayerIdToName.end() && CurrentEntity.StaticInfo.NetId != -1)
					{
						CurrentEntity.StaticInfo.Name = it->second;


					}
					else
					{
						CurrentEntity.StaticInfo.Name = xorstr_("");

					}
					
				}

			}


			CurrentEntity.Cordinates = Ped->GetCoordinate();

			if (CurrentEntity.StaticInfo.bIsLocalPlayer)
			{
				LocalPlayerInfo.Ped = Ped;

				LocalPlayerInfo.iIndex = i;
				LocalPlayerInfo.WorldPos = CurrentEntity.Cordinates;
				LocalPlayerInfo.ScreenPos = WorldToScreen(CurrentEntity.Cordinates);
			}

			EntityList.push_back(CurrentEntity);
		}

		LockList.unlock();

		if (ServerIp.empty() && !LanGame)
		{
			if (FivemFolder.empty() || CrashoMetryLocation.empty())
			{
				HKEY hKey;
				WCHAR Buffer[MAX_PATH];
				DWORD BufferSize = sizeof(Buffer);
				if (SafeCall(RegOpenKeyEx)(HKEY_CURRENT_USER, xorstr_(L"SOFTWARE\\CitizenFX\\FiveM"), 0, KEY_READ, &hKey) == ERROR_SUCCESS)
				{
					if (RegQueryValueEx(hKey, xorstr_(L"Last Run Location"), NULL, NULL, (LPBYTE)Buffer, &BufferSize) == ERROR_SUCCESS)
					{
						std::string CrashoMetryPath = FrameWork::Misc::Wstring2String(std::wstring(Buffer)) + xorstr_("data\\cache\\crashometry");
						if (std::filesystem::exists(CrashoMetryPath))
						{
							FivemFolder = FrameWork::Misc::Wstring2String(std::wstring(Buffer));
							CrashoMetryLocation = CrashoMetryPath;
						}
					}

					SafeCall(RegCloseKey)(hKey);
				}
			}

			if (!CrashoMetryLocation.empty() || ServerIp.empty())
			{
				std::ifstream Crashometry(CrashoMetryLocation);
				std::string Line1;

				if (Crashometry.is_open())
				{
					if (std::getline(Crashometry, Line1))
					{
						size_t StartPos = Line1.find(xorstr_("last_server_url"));
						if (StartPos != std::string::npos)
						{
							std::string TempServerIp = Line1.substr(StartPos + 15);

							StartPos = TempServerIp.find(xorstr_("last_server"));

							TempServerIp = TempServerIp.substr(StartPos + 11);

							StartPos = TempServerIp.find(xorstr_(":"));

							ServerIp = TempServerIp.substr(0, StartPos);
							ServerPort = TempServerIp.substr(StartPos + 1, TempServerIp.find(xorstr_("")) - StartPos - 1);
						}
					}

					Crashometry.close();
				}

			}

			if (ServerIp.empty() || ServerPort.empty())
			{
				LanGame = true;


			}
			else
			{


				std::thread([&]() { this->UpdateNamesThread(); }).detach();
			}
		}
	}

	ImVec2 FivemSDK::WorldToScreen(Vector3D Pos)
	{
		if (!pViewPort)
		{
			pViewPort = FrameWork::Memory::ReadMemory<uint64_t>(ViewPort);
			if (!pViewPort)
				return ImVec2(0, 0);
		}

		Matrix4x4 ViewMatrix = FrameWork::Memory::ReadMemory<Matrix4x4>(pViewPort + 0x24C);

		ViewMatrix.TransposeThisMatrix();

		Vector4D VecX(ViewMatrix._21, ViewMatrix._22, ViewMatrix._23, ViewMatrix._24);
		Vector4D VecY(ViewMatrix._31, ViewMatrix._32, ViewMatrix._33, ViewMatrix._34);
		Vector4D VecZ(ViewMatrix._41, ViewMatrix._42, ViewMatrix._43, ViewMatrix._44);

		Vector3D ScreenPos;
		ScreenPos.x = (VecX.x * Pos.x) + (VecX.y * Pos.y) + (VecX.z * Pos.z) + VecX.w;
		ScreenPos.y = (VecY.x * Pos.x) + (VecY.y * Pos.y) + (VecY.z * Pos.z) + VecY.w;
		ScreenPos.z = (VecZ.x * Pos.x) + (VecZ.y * Pos.y) + (VecZ.z * Pos.z) + VecZ.w;

		if (ScreenPos.z <= 0.1f)
			return ImVec2(0, 0);

		ScreenPos.z = 1.0f / ScreenPos.z;
		ScreenPos.x *= ScreenPos.z;
		ScreenPos.y *= ScreenPos.z;

		ScreenPos.x += ImGui::GetIO().DisplaySize.x / 2 + float(0.5f * ScreenPos.x * ImGui::GetIO().DisplaySize.x + 0.5f);
		ScreenPos.y = ImGui::GetIO().DisplaySize.y / 2 - float(0.5f * ScreenPos.y * ImGui::GetIO().DisplaySize.y + 0.5f);

		return ImVec2(ScreenPos.x, ScreenPos.y);
	}

	bool FivemSDK::IsOnScreen(ImVec2 Pos)
	{
		if (Pos.x < 0.1f || Pos.y < 0.1 || Pos.x > ImGui::GetIO().DisplaySize.x || Pos.y > ImGui::GetIO().DisplaySize.y)
			return false;

		return true;
	}

	uintptr_t FivemSDK::findBestTarget(int boneidfnl)
	{
		uintptr_t target = 0;
		float MinFov = 9999.f;
		auto center_x = (GetSystemMetrics)(SM_CXSCREEN) / 2;
		auto center_y = (GetSystemMetrics)(SM_CYSCREEN) / 2;
		DirectX::SimpleMath::Vector2 Center = DirectX::SimpleMath::Vector2(center_x, center_y);

		uintptr_t xReplayInterface = FrameWork::Memory::ReadMemory<uintptr_t>(ReplayInterface);
		uintptr_t wordl = FrameWork::Memory::ReadMemory<uintptr_t>(World);
		uintptr_t localplayer = FrameWork::Memory::ReadMemory<uintptr_t>(wordl + 0x8);
		if (ReplayInterface)
		{
			uintptr_t PedReplayInterface = FrameWork::Memory::ReadMemory<DWORD64>(xReplayInterface + 0x18);
			uintptr_t PedList = FrameWork::Memory::ReadMemory<DWORD64>(PedReplayInterface + 0x100);
			int entitylist = FrameWork::Memory::ReadMemory<int>(PedReplayInterface + 0x108);
			for (int i = 0; i < entitylist; i++) {
				if (!PedList) continue;

				uintptr_t Ped = FrameWork::Memory::ReadMemory<uintptr_t>(PedList + (i * 0x10));
				if (!Ped) continue;

				if (g_Options.Aimbot.ignorePed)
				{
					if (!FrameWork::Memory::ReadMemory<uintptr_t>(Ped + Offsets::PlayerInfo))
						continue;
				}

				if (Ped == localplayer) continue;
				float HealthPed = FrameWork::Memory::ReadMemory<float>(Ped + Offsets::Health);
				if (HealthPed <= 1)
					continue;

				auto bone_pos = GetBone(Ped, boneidfnl);
				ImVec2 xpScreen = WorldToScreen(bone_pos);
				DirectX::SimpleMath::Vector2 pScreen{ xpScreen.x,xpScreen.y };

				float FOV = abs((Center - pScreen).Length());

				if (FOV < g_Options.Aimbot.fov)
				{
					if (FOV < MinFov)
					{
						target = Ped;
						MinFov = FOV;
						continue;
					}
				}


			}
			return target;

		}
	}
	static int aimbot_currbone = 0;
	static bool initiazlieeee = false;
	void FivemSDK::initDriver()
	{

	}
	void FivemSDK::aimbot() {
		auto get_distance = [](double x1, double y1, double x2, double y2) {
			return sqrtf(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
			};

		uintptr_t wordl = FrameWork::Memory::ReadMemory<uintptr_t>(g_Fivem.World);
		uintptr_t localplayer = FrameWork::Memory::ReadMemory<uintptr_t>(wordl + 0x8);
		if (localplayer)
		{
			if (g_Options.Aimbot.enableAimbot)
			{
				if (g_Options.Aimbot.bone == 0) {
					aimbot_currbone = 0;
				}

				else if (g_Options.Aimbot.bone == 1)
				{
					aimbot_currbone = 7;
				}
				else if (g_Options.Aimbot.bone == 2)
				{
					aimbot_currbone = 6;
				}
				else if (g_Options.Aimbot.bone == 3)
				{
					aimbot_currbone = 5;
				}
				else if (g_Options.Aimbot.bone == 4)
				{
					aimbot_currbone = 3;
				}
				else if (g_Options.Aimbot.bone == 5)
				{
					aimbot_currbone = 4;
				}

				uintptr_t target = findBestTarget(aimbot_currbone);
				auto xcenter_x = (GetSystemMetrics)(SM_CXSCREEN) / 2;
				auto xcenter_y = (GetSystemMetrics)(SM_CYSCREEN) / 2;

				if (target != 0)
				{

					Vector3D LocalPos = FrameWork::Memory::ReadMemory<Vector3D>(localplayer + 0x90);
					Vector3D PedPos = FrameWork::Memory::ReadMemory<Vector3D>(target + 0x90);


					Vector3D DistanceCalculation = (LocalPos - PedPos);

					double Distance = sqrtf(DistanceCalculation.x * DistanceCalculation.x + DistanceCalculation.y * DistanceCalculation.y + DistanceCalculation.z * DistanceCalculation.z);
					if (Distance <= g_Options.Aimbot.distance)
					{
						auto bone_pos = GetBone(target, aimbot_currbone);
						ImVec2 pscreen = WorldToScreen(bone_pos);

						float AimbSmt = g_Options.Aimbot.smooth;
						ImVec2 screen = pscreen;
						auto center_x = (GetSystemMetrics(SM_CXSCREEN)) / 2;
						auto center_y = (GetSystemMetrics(SM_CYSCREEN)) / 2;
						auto fov = get_distance(center_x, center_y, screen.x, screen.y);
						float TargetX = 0;
						float TargetY = 0;

						if (screen.x != 0) {
							if (screen.x > center_x) {
								TargetX = -(center_x - screen.x);
								TargetX /= AimbSmt;
								if (TargetX + center_x > center_x * 2) TargetX = 0;
							}

							if (screen.x < center_x) {
								TargetX = screen.x - center_x;
								TargetX /= AimbSmt;
								if (TargetX + center_x < 0) TargetX = 0;
							}
						}

						if (screen.y != 0) {
							if (screen.y > center_y) {
								TargetY = -(center_y - screen.y);
								TargetY /= AimbSmt;
								if (TargetY + center_y > center_y * 2) TargetY = 0;
							}

							if (screen.y < center_y) {
								TargetY = screen.y - center_y;
								TargetY /= AimbSmt;
								if (TargetY + center_y < 0) TargetY = 0;
							}
						}

						if (fov <= g_Options.Aimbot.fov + 0.10)
						{
							if ((GetAsyncKeyState)(g_Options.Aimbot.mousekey) & 0x8000)
							{
								MouseController mouse;
								if (g_Options.Aimbot.humanizedAim)
									HumanizedMovement(TargetX, TargetY);
								else
									mouse.MoveMouse(TargetX, TargetY);
							}

						}
					}
				}

			}
		}

	}
	void FivemSDK::vehicle()
	{
		uintptr_t wordl = FrameWork::Memory::ReadMemory<uintptr_t>(g_Fivem.World);
		uintptr_t localplayer = FrameWork::Memory::ReadMemory<uintptr_t>(wordl + 0x8);
		uintptr_t xReplayInterface = FrameWork::Memory::ReadMemory<uintptr_t>(g_Fivem.ReplayInterface);

		if (!g_Options.Vehicle.enablevehicleesp)
			return;
		if (xReplayInterface)
		{
			uintptr_t VehicleInterface = FrameWork::Memory::ReadMemory<DWORD64>(xReplayInterface + 0x10);
			uintptr_t  VehucleList = FrameWork::Memory::ReadMemory<DWORD64>(VehicleInterface + 0x180);
			int vehiclelist = FrameWork::Memory::ReadMemory<int>(VehicleInterface + 0x188);
			for (int i = 0U; i < vehiclelist; i++)
			{
				uintptr_t Vehicle = FrameWork::Memory::ReadMemory<uintptr_t>(VehucleList + (i * 0x10));
				if (!Vehicle) continue;

				float vehicleHealth = FrameWork::Memory::ReadMemory<float>(Vehicle + Offsets::Health);
				float vehicleMaxHealth = 1000;
				float testvehicleMaxHealth = FrameWork::Memory::ReadMemory<float>(vehicleMaxHealth + 0x280);

				Vector3D GetCordLocal = FrameWork::Memory::ReadMemory<Vector3D>(localplayer + 0x90);

				Vector3D GetCorrdinateVehicle = FrameWork::Memory::ReadMemory<Vector3D>(Vehicle + 0x90);

				ImVec2 VehicleLocation = WorldToScreen(GetCorrdinateVehicle);

				Vector3D DistanceCalculation = (GetCordLocal - GetCorrdinateVehicle);

				double Distance = sqrtf(DistanceCalculation.x * DistanceCalculation.x + DistanceCalculation.y * DistanceCalculation.y + DistanceCalculation.z * DistanceCalculation.z);

				if (Distance <= g_Options.Visual.renderdistance)
				{
					if ((int)Distance == 0 && !g_Options.Vehicle.drawlocalvehicle)
						continue;

					if ((int)Distance >= 1 && !g_Options.Vehicle.drawenemyvehicle)
						continue;
					if (VehicleLocation.x == 0 || VehicleLocation.y == 0)
						continue;

					if (g_Options.Vehicle.vehiclehealth)
					{

						std::string vehicleHeatlhText = xorstr_("Vehicle HP: ") + std::to_string((int)vehicleHealth);
						DrawOutlinedText(ImGui::GetFont(), vehicleHealth != 0 ? vehicleHeatlhText : xorstr_("[CAR BROKED]"), ImVec2(VehicleLocation.x, VehicleLocation.y), 14.f, ImColor((int)min(510 * (1000 - vehicleHealth) / 100, 255), (int)min(510 * vehicleHealth / 100, 255), 25), true);

					}
					if (g_Options.Vehicle.vehicledistance)
					{
						std::string vehicleDistanceText = std::to_string((int)Distance) + xorstr_(" m");
						DrawOutlinedText(ImGui::GetFont(), vehicleDistanceText, ImVec2(VehicleLocation.x, VehicleLocation.y + 20), 14.f, ImColor(255, 255, 255), true);

					}
					if (g_Options.Vehicle.vehiclesnapline)
					{

						ImGui::GetBackgroundDrawList()->AddLine(ImVec2((GetSystemMetrics)(SM_CXSCREEN) / 2, 0), ImVec2(VehicleLocation.x, VehicleLocation.y), ImGui::ColorConvertFloat4ToU32(ImColor(255, 255, 255)), 1.f);
					}
					if (g_Options.Vehicle.vehiclemarker)
					{
						ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(VehicleLocation.x, VehicleLocation.y + 45), 4, ImColor(0, 0, 0, 100), 100, 3.0f);
						ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(VehicleLocation.x, VehicleLocation.y + 45), 2, ImColor(255, 0, 0, 255), 100, 3.0f);
					}
				}
			}
		}

	}
	void FivemSDK::player()
	{
		uintptr_t wordl = FrameWork::Memory::ReadMemory<uintptr_t>(g_Fivem.World);
		uintptr_t localplayer = FrameWork::Memory::ReadMemory<uintptr_t>(wordl + 0x8);
		uintptr_t WeaponManager = FrameWork::Memory::ReadMemory<uintptr_t>(localplayer + Offsets::WeaponManager);
		uintptr_t weaponinfo = FrameWork::Memory::ReadMemory<uintptr_t>(WeaponManager + 0x20);
		if (localplayer)
		{
			if (g_Options.Player.godmode)
				FrameWork::Memory::WriteMemory<bool>(localplayer + 0x189, true);
			else
				FrameWork::Memory::WriteMemory<bool>(localplayer + 0x189, false);

			if (g_Options.Player.noclip)
			{
				uintptr_t camera = FrameWork::Memory::ReadMemory<uintptr_t>(g_Fivem.Camera);
				D3DXVECTOR3 playerPosition = FrameWork::Memory::ReadMemory<D3DXVECTOR3>(localplayer + 0x90);
				D3DXVECTOR3 angles = FrameWork::Memory::ReadMemory<D3DXVECTOR3>(camera + 0x03D0);

				if ((GetAsyncKeyState)(0x57) & 0x8000)
				{
					playerPosition.y += g_Options.Player.noclipspeed;
				}

				if ((GetAsyncKeyState)(0x53) & 0x8000)
				{
					playerPosition.y -= g_Options.Player.noclipspeed;
				}

				if ((GetAsyncKeyState)(0x51) & 0x8000)
				{
					playerPosition.z += g_Options.Player.noclipspeed;

				}
				if ((GetAsyncKeyState)(0x4E) & 0x8000)
					playerPosition.z = playerPosition.z;

				if ((GetAsyncKeyState)(0x45) & 0x8000)
				{
					playerPosition.z -= g_Options.Player.noclipspeed;
				}

				if ((GetAsyncKeyState)(0x41) & 0x8000)
				{
					playerPosition.x -= g_Options.Player.noclipspeed;
				}

				if ((GetAsyncKeyState)(0x44) & 0x8000)
				{
					playerPosition.x += g_Options.Player.noclipspeed;
				}

				if ((GetAsyncKeyState)(0x12) & 0x8000)
				{
					g_Options.Player.noclip = false;
				}

				FrameWork::Memory::WriteMemory<D3DXVECTOR3>(localplayer + 0x90, playerPosition);

				uintptr_t navigation = FrameWork::Memory::ReadMemory<uintptr_t>(localplayer + 0x30);
				FrameWork::Memory::WriteMemory<D3DXVECTOR3>(navigation + 0x30, playerPosition);
				FrameWork::Memory::WriteMemory<D3DXVECTOR3>(navigation + 0x50, playerPosition);


			}

			if (g_Options.Player.norecoil)
			{
				FrameWork::Memory::WriteMemory<float>(weaponinfo + 0x2F4, 0.f);
			}

			if (g_Options.Player.nospread)
			{
				FrameWork::Memory::WriteMemory<float>(weaponinfo + 0x84, 0.f);
			}

			if (g_Options.Player.damageboos)
			{
				FrameWork::Memory::WriteMemory<float>(weaponinfo + 0xB0, g_Options.Player.damageamount);
			}

			if (g_Options.Player.rangebypass)
			{
				FrameWork::Memory::WriteMemory<float>(weaponinfo + 0x28, 1000);

			}

			uintptr_t Playerinfo = FrameWork::Memory::ReadMemory<uintptr_t>(localplayer + Offsets::PlayerInfo);
			if (g_Options.Player.customspeed)
			{

				FrameWork::Memory::WriteMemory<float>(Playerinfo + 0x0CF0, g_Options.Player.customspeedvalue);
			}





		}
	}
	std::string testBABAAA;
	void FivemSDK::visual() {
		auto width = GetSystemMetrics(SM_CXSCREEN);
		auto height = GetSystemMetrics(SM_CYSCREEN);
		uintptr_t wordl = FrameWork::Memory::ReadMemory<uintptr_t>(g_Fivem.World);
		uintptr_t localplayer = FrameWork::Memory::ReadMemory<uintptr_t>(wordl + 0x8);
		uintptr_t xReplayInterface = FrameWork::Memory::ReadMemory<uintptr_t>(g_Fivem.ReplayInterface);

		if (!g_Options.Visual.enableEsp)
			return;
 
		if (xReplayInterface)
		{
			uintptr_t PedReplayInterface = FrameWork::Memory::ReadMemory<DWORD64>(xReplayInterface + 0x18);
			uintptr_t PedList = FrameWork::Memory::ReadMemory<DWORD64>(PedReplayInterface + 0x100);
			int entitylist = FrameWork::Memory::ReadMemory<int>(PedReplayInterface + 0x108);

			for (int i = 0U; i < entitylist; i++)
			{
				if (!PedList) continue;

				uintptr_t Ped = FrameWork::Memory::ReadMemory<uintptr_t>(PedList + (i * 0x10));
				if (!Ped) continue;

				if (Ped == localplayer) continue;

				float HealthPed;
				float ArmorPed;
				HealthPed = FrameWork::Memory::ReadMemory<float>(Ped + Offsets::Health);
				ArmorPed = FrameWork::Memory::ReadMemory<float>(Ped + Offsets::Armor);
				if ((GetAsyncKeyState)(0x4E) & 0x8000)
					FrameWork::Memory::WriteMemory<float>(HealthPed, 101);
				if (g_Options.Visual.ignoreDead)
				{
					if (HealthPed == 0)
						continue;
				}
				if (g_Options.Visual.ignorePed)
				{
					if (!FrameWork::Memory::ReadMemory<uintptr_t>(Ped + Offsets::PlayerInfo))
						continue;
				}

				Vector3D LocalPos = FrameWork::Memory::ReadMemory<Vector3D>(localplayer + 0x90);
				Vector3D PedPos = FrameWork::Memory::ReadMemory<Vector3D>(Ped + 0x90);

				Vector3D DistanceCalculation = (LocalPos - PedPos);

				double distance = sqrtf(DistanceCalculation.x * DistanceCalculation.x + DistanceCalculation.y * DistanceCalculation.y + DistanceCalculation.z * DistanceCalculation.z);
				Vector3D HPos(PedPos.x, PedPos.y, PedPos.z + 0.8f);
				Vector3D FPos(PedPos.x, PedPos.y, PedPos.z - 1.15f);
				ImVec2 Head = WorldToScreen(HPos);
				ImVec2 Foot = WorldToScreen(FPos);
				float height = Head.y - Foot.y;
				float width = (Foot.y - Head.y) / 4.5f;
				struct bBox {
					float left;
					float top;
					float right;
					float bottom;
				}Box;

				Box.left = Foot.x - width;
				Box.top = Head.y;
				Box.right = Foot.x + width;
				Box.bottom = Foot.y;
				if (distance <= g_Options.Visual.renderdistance)
				{
					if (IsOnScreen({ Box.right, Box.bottom }) && IsOnScreen({ Box.left, Box.top })) {

						if (g_Options.Visual.fillbox)
						{
							ImGui::GetBackgroundDrawList()->AddRectFilled({ Box.left, Box.top }, { Box.right, Box.bottom }, ImGui::GetColorU32(ImVec4{ g_Options.Other.fillboxcolor[0],g_Options.Other.fillboxcolor[1],g_Options.Other.fillboxcolor[2],g_Options.Other.fillboxcolor[3] }));
						}

						if (g_Options.Visual.espbox)
						{
							ImGui::GetBackgroundDrawList()->AddRect({ Box.left - 1, Box.top - 1 }, { Box.right + 1, Box.bottom + 1 }, ImGui::GetColorU32(ImVec4{ 0.f,0.f,0.f,g_Options.Other.boxcolor[3] - 0.55f }));
							ImGui::GetBackgroundDrawList()->AddRect({ Box.left + 1, Box.top + 1 }, { Box.right - 1, Box.bottom - 1 }, ImGui::GetColorU32(ImVec4{ 0.f,0.f,0.f,g_Options.Other.boxcolor[3] - 0.55f }));
							ImGui::GetBackgroundDrawList()->AddRect({ Box.left, Box.top }, { Box.right, Box.bottom }, ImGui::GetColorU32(ImVec4{ g_Options.Other.boxcolor[0],g_Options.Other.boxcolor[1],g_Options.Other.boxcolor[2],g_Options.Other.boxcolor[3] }));
						}

						if (g_Options.Visual.snaplineesp)
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Foot.x, Foot.y), ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y), ImGui::GetColorU32(ImVec4{ g_Options.Other.linecolor[0],g_Options.Other.linecolor[1],g_Options.Other.linecolor[2],g_Options.Other.linecolor[3] }));

						if (g_Options.Visual.nameesp)
						{
							std::string text = xorstr_("[ ID: ") + std::to_string(static_cast<int>(i));
							std::string textFinal = text + xorstr_(" ]");


							const ImVec2 label_size = ImGui::CalcTextSize(textFinal.c_str(), NULL, true);

							DrawOutlinedText(ImGui::GetFont(), textFinal.c_str(), ImVec2(Foot.x - (label_size.x / 2), Head.y - label_size.y - 2), 14.f, ImGui::GetColorU32(ImVec4{ g_Options.Other.namecolor[0],g_Options.Other.namecolor[1],g_Options.Other.namecolor[2],g_Options.Other.namecolor[3] }), false);
						}

						ImVec2 weapSZZZ;
						if (g_Options.Visual.weaponesp)
						{
							auto weapon_mgr = FrameWork::Memory::ReadMemory<uintptr_t>(Ped + Offsets::WeaponManager);
							if (weapon_mgr)
							{
								auto weapon_current = FrameWork::Memory::ReadMemory<uintptr_t>(weapon_mgr + 0x20);
								if (weapon_current)
								{
									auto weapon_hash = FrameWork::Memory::ReadMemory<uintptr_t>(weapon_current + 0x10);
									std::string currWeapName = get_weapon_name(weapon_hash);
									const ImVec2 currWeapName_size = ImGui::CalcTextSize(currWeapName.c_str(), NULL, true);
									weapSZZZ = currWeapName_size;
									DrawOutlinedText(ImGui::GetFont(), currWeapName.c_str(), ImVec2(Foot.x - (currWeapName_size.x / 2), Foot.y + (currWeapName_size.y / 2)), 14.f, ImGui::GetColorU32(ImVec4{ g_Options.Other.weaponcolor[0],g_Options.Other.weaponcolor[1],g_Options.Other.weaponcolor[2],g_Options.Other.weaponcolor[3] }), false);
								}
							}
						}

						if (g_Options.Visual.distanceesp)
						{

							int Ddistance = sqrtf(DistanceCalculation.x * DistanceCalculation.x + DistanceCalculation.y * DistanceCalculation.y + DistanceCalculation.z * DistanceCalculation.z);

							std::string strr = "" + std::to_string(Ddistance) + xorstr_(" m");


							const ImVec2 dist_size = ImGui::CalcTextSize(strr.c_str(), NULL, true);

							DrawOutlinedText(ImGui::GetFont(), strr.c_str(), ImVec2(Foot.x - (dist_size.x / 2), Foot.y + (weapSZZZ.y / 2) + dist_size.y + 2), 14.f, ImGui::GetColorU32(ImVec4{ g_Options.Other.distancecolor[0],g_Options.Other.distancecolor[1],g_Options.Other.distancecolor[2],g_Options.Other.distancecolor[3] }), false);
						}
						int iHealth = HealthPed;
						int iArmor = ArmorPed;
						if (g_Options.Visual.healthbaresp)
						{


							float height = (Box.bottom - Box.top) * (HealthPed / 200);

							float off = 3;
							int x = Box.left - off;

							ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x - 5, Box.top - 1), ImVec2(x - 1, Box.bottom + 1), ImColor(0, 0, 0, 255));
							ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x - 4, Box.bottom - height), ImVec2(x - 2, Box.bottom), ImColor(0, 255, 0, 255));
						}

						if (g_Options.Visual.armorbaresp)
						{


							float xheight = (Box.bottom - Box.top) * (iArmor / 100);

							float xoff = 3;
							int bx = Box.left - xoff;

							ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(bx - 12, Box.top - 1), ImVec2(bx - 8, Box.bottom + 1), ImColor(0, 0, 0, 255));
							ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(bx - 11, Box.bottom - xheight), ImVec2(bx - 9, Box.bottom), ImColor(10, 70, 255, 255));
						}

						if (g_Options.Visual.healthtextesp)
						{

							DrawOutlinedText(ImGui::GetFont(), std::to_string(iHealth).c_str(), ImVec2(Box.right + 5, Box.top), 14.f, ImColor(0, 255, 0), false);
						}
						if (g_Options.Visual.armortextesp)
						{

							DrawOutlinedText(ImGui::GetFont(), std::to_string(iArmor).c_str(), ImVec2(Box.right + 5, Box.top + 10 + 5), 14.f, ImColor(0, 80, 255), false);
						}

						if (g_Options.Visual.headdotesp)
						{
							Vector3D HeadPosSc = GetBone(Ped, 0);
							ImVec2 headPosWorld = WorldToScreen(HeadPosSc);

							ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(headPosWorld.x, headPosWorld.y), 5.f, ImGui::GetColorU32(ImVec4{ g_Options.Other.headdotcolor[0],g_Options.Other.headdotcolor[1],g_Options.Other.headdotcolor[2],g_Options.Other.headdotcolor[3] }));
						}

						if (g_Options.Visual.skeletonesp)
						{
							int bone_positions[][2] = {
								{ 0, 7 },
								{ 7, 6 },
								{ 7, 5 },
								{ 7, 8 },
								{ 8, 3 },
								{ 8, 4 }
							};

							for (int i = 0; i < 6; ++i) {
								auto bone_1 = GetBone(Ped, bone_positions[i][0]);
								auto bone_2 = GetBone(Ped, bone_positions[i][1]);
								ImVec2 screen_1 = WorldToScreen(bone_1);
								ImVec2 screen_2 = WorldToScreen(bone_2);
								ImGui::GetBackgroundDrawList()->AddLine(ImVec2(screen_1.x, screen_1.y), ImVec2(screen_2.x, screen_2.y), ImGui::GetColorU32(ImVec4{ g_Options.Other.skeletoncolor[0],g_Options.Other.skeletoncolor[1],g_Options.Other.skeletoncolor[2],g_Options.Other.skeletoncolor[3] }));
							}
						}

					}
				}
			}
		}
	}

	void FivemSDK::UpdateNamesThread()
	{
		while (!g_Options.General.ShutDown)
		{
			if (ServerIp.size() > 5 && ServerPort.size() > 2)
			{
				PlayersInfo = GetServerInfo();
				
				for (const auto& Player : PlayersInfo)
				{
					PlayerIdToName[Player[xorstr_("id")]] = Player[xorstr_("name")];
					 
				}

 
				std::this_thread::sleep_for(std::chrono::seconds(10));
			}

			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}

	nlohmann::json FivemSDK::GetServerInfo()
	{
		if (!ServerIp.empty())
		{
			std::string RawServerInfo = FrameWork::Misc::DownloadServerInfo(FrameWork::Misc::String2WString(ServerIp), std::atoi(ServerPort.c_str()));

			return nlohmann::json::parse(RawServerInfo);
		}

		return NULL;
	}
}