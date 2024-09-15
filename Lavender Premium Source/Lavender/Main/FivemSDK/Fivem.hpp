#pragma once
#include <cstdint>

#include "Classes.hpp"

#include <Utils/FrameWork.hpp>
#include <mutex>

namespace Cheat
{
	enum eGAME_VERSION
	{
		GAME_VERSION_GAME_b2060,
		GAME_VERSION_GTA_b2060,
		GAME_VERSION_GAME_b2189,
		GAME_VERSION_GTA_b2189,
		GAME_VERSION_GAME_b2372,
		GAME_VERSION_GTA_b2372,
		GAME_VERSION_GAME_b2545,
		GAME_VERSION_GTA_b2545,
		GAME_VERSION_GAME_b2612,
		GAME_VERSION_GTA_b2612,
		GAME_VERSION_GAME_b2699,
		GAME_VERSION_GTA_b2699,
		GAME_VERSION_GAME_b2802,
		GAME_VERSION_GTA_b2802,
		GAME_VERSION_GAME_b2944,
		GAME_VERSION_GTA_b2944,
		GAME_VERSION_GAME_b3095,
		GAME_VERSION_GTA_b3095,
	};

	struct PedStaticInfo
	{
		CPed* Ped;
		int iIndex;
		int NetId;
		bool bIsLocalPlayer;
		bool bIsNPC;
		std::string Name;

		std::unordered_map<unsigned int, unsigned int> MaskToBoneId;
	};

	struct Entity
	{
		PedStaticInfo StaticInfo;

		Vector3D Cordinates;
	};

	struct LocalPEDInfo
	{
		CPed* Ped;
		int iIndex;
		ImVec2 ScreenPos;
		Vector3D WorldPos;
	};

	class FivemSDK
	{
	public:
		void Intialize();
		void UpdateEntities();
		void visual();
		void vehicle();
		void player();
		void aimbot();
		void initDriver();
		void magicAimbot();
		uintptr_t findBestTarget(int boneidfnl);
		DWORD GetPid() { return Pid; }
		uint64_t GetModuleBase() { return ModuleBase; };
		std::string GetModuleName() { return ModuleName; };
		bool HasAdehsive() { return ((int)GameVersion % 2) != 0; }

		ImVec2 WorldToScreen(Vector3D Pos);
		bool IsOnScreen(ImVec2 Pos);

		void UpdateNamesThread();
		nlohmann::json GetServerInfo();
		std::uintptr_t worldOffet_b2545 = NULL;
		std::uintptr_t viewmatrixOffset_b2545 = NULL;

		std::uintptr_t worldOffet_b2699 = NULL;
		std::uintptr_t viewmatrixOffset_b2699 = NULL;

		std::uintptr_t worldOffet_GTAProcess = NULL;
		std::uintptr_t viewmatrixOffset_GTAProcess = NULL;

		std::uintptr_t worldOffet_b2060 = NULL;
		std::uintptr_t viewmatrixOffset_b2060 = NULL;

		std::uintptr_t worldOffet_b2372 = NULL;
		std::uintptr_t viewmatrixOffset_b2372 = NULL;

		std::uintptr_t worldOffet_b2612 = NULL;
		std::uintptr_t viewmatrixOffset_b2612 = NULL;

		std::uintptr_t worldOffet_b2189 = NULL;
		std::uintptr_t viewmatrixOffset_b2189 = NULL;

		std::uintptr_t worldOffet_b2802 = NULL;
		std::uintptr_t viewmatrixOffset_b2802 = NULL;

		std::uintptr_t worldOffet_b2944 = NULL;
		std::uintptr_t viewmatrixOffset_b2944 = NULL;

		std::uintptr_t worldOffet_b3095 = NULL;
		std::uintptr_t viewmatrixOffset_b3095 = NULL;
		uint64_t World; // 48 8B 05 ? ? ? ? 33 D2 48 8B 40 08 8A CA 48 85 C0 74 16 48 8B
		uint64_t ReplayInterface; // 48 8D 0D ?? ?? ?? ?? 48 ?? ?? E8 ?? ?? ?? ?? 48 8D 0D ?? ?? ?? ?? 8A D8 E8 ?? ?? ?? ?? 84 DB 75 13 48 8D 0D ?? ?? ?? ?? 48 8B D7 E8 ?? ?? ?? ?? 84 C0 74 BC 8B 8F
		uint64_t ViewPort; // 48 8B 15 ? ? ? ? 48 8D 2D ? ? ? ? 48 8B CD
		uint64_t Camera; // 48 8B 05 ? ? ? ? 38 98 ? ? ? ? 8A C3
		uint64_t Vehicle; // 48 8B 05 ? ? ? ? 38 98 ? ? ? ? 8A C3
		uint64_t Handling; // 48 8B 05 ? ? ? ? 38 98 ? ? ? ? 8A C3
		uint64_t FreezeOffst; // 48 8B 05 ? ? ? ? 38 98 ? ? ? ? 8A C3

		DWORD Pid;
		uint64_t ModuleBase;
		std::string ModuleName;
		bool IsInitialized() { return bIsIntialized; }
		bool isb2802;
		uint64_t PubWorld; // 48 8B 05 ? ? ? ? 33 D2 48 8B 40 08 8A CA 48 85 C0 74 16 48 8B
		uint64_t PubReplayInterface; // 48 8D 0D ?? ?? ?? ?? 48 ?? ?? E8 ?? ?? ?? ?? 48 8D 0D ?? ?? ?? ?? 8A D8 E8 ?? ?? ?? ?? 84 DB 75 13 48 8D 0D ?? ?? ?? ?? 48 8B D7 E8 ?? ?? ?? ?? 84 C0 74 BC 8B 8F
		uint64_t PubViewPort; // 48 8B 15 ? ? ? ? 48 8D 2D ? ? ? ? 48 8B CD
		uint64_t PubCamera; // 48 8B 05 ? ? ? ? 38 98 ? ? ? ? 8A C3
		eGAME_VERSION GameVersion;
		bool bIsIntialized = false;
	private:
	

		
		std::string FivemFolder;
		std::string CrashoMetryLocation;
		std::string ServerIp;
		std::string ServerPort;
		nlohmann::json PlayersInfo;
		std::unordered_map<int, std::string> PlayerIdToName;
		bool LanGame;
		

	private:
		CWorld* pWorld;
		CPed* pLocalPlayer;
		CReplayInterface* pReplayInterface;
		CPedInterface* pPedInterface;
		CCamGameplayDirector* pCamGameplayDirector;

		uint64_t pViewPort;

	private:
		std::mutex LockList;
		std::vector<Entity> EntityList;
		std::unordered_map<CPed*, PedStaticInfo> CachedStaticInfoList;
		LocalPEDInfo LocalPlayerInfo;

	};

	inline FivemSDK g_Fivem;
}