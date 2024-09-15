#pragma once

#include <Windows.h>
#include <string>

namespace Cheat
{
	class Options
	{
	public:
		struct General
		{
			std::string sysName;
			std::string sysPath;
			std::string mapperName;
			std::string mapperPath;
			std::string folderName;
			std::string folderPath;
			bool ShutDown = false;
			int MenuKey = VK_F4;
			int ThreadDelay = 0;
		}General;
		struct Player {
			bool enablePlayerSection;
			bool godmode;
			bool noclip;
			int noclipspeed;
			bool customspeed;
			float customspeedvalue;
			bool customfov;
			float customfovvalue;
			bool boostvehicle;
			bool rangebypass;
			bool nospread;
			bool norecoil;
			bool damageboos;
			float damageamount;
		}Player;
		struct Vehicle {
			bool enablevehicleesp;
			bool drawlocalvehicle;
			bool drawenemyvehicle;
			bool vehiclemarker;
			bool vehiclehealth;
			bool vehiclesnapline;
			bool vehicledistance;
		}Vehicle;
		struct Other {
			bool watermark;
			float boxcolor[4] = { 1.f, 0.f, 0.f, 1.f };
			float fillboxcolor[4] = { 1.f, 0.f, 0.f, 0.15f };
			float namecolor[4] = { 1.f, 1.f, 1.f, 1.f };
			float distancecolor[4] = { 1.f, 1.f, 1.f, 1.f };
			float linecolor[4] = { 1.f, 1.f, 1.f, 1.f };
			float weaponcolor[4] = { 1.f, 1.f, 1.f, 1.f };
			float skeletoncolor[4] = { 1.f, 1.f, 1.f, 1.f };
			float headdotcolor[4] = { 1.f, 1.f, 1.f, 1.f };
		}Other;
		struct Aimbot {
			bool enableAimbot;
			bool ignorePed;
			bool humanizedAim;
			int fov=70;
			float smooth=4;
			int distance=90;
			bool drawFov;
			int bone=0;
			int mousekey=0;
			bool autoadjustsmooth;
		}Aimbot;
		struct Visual
		{
			bool enableEsp = false;
			bool ignorePed = false;
			bool ignoreDead = false;
			bool espbox = false;
			bool fillbox = false;
			bool nameesp = false;
			bool weaponesp = false;
			bool snaplineesp = false;
			bool skeletonesp = false;
			bool headdotesp = false;
			bool killSet = false;
			int killpid = 0;
			bool distanceesp = false;
			bool armorbaresp = false;
			bool armortextesp = false;
			bool healthbaresp = false;
			bool healthtextesp = false;
			bool espRadar = false;
			bool espRadarNPC = false;
			bool espRadarPlayer = false;
			int radarzoom = 2;
			int renderdistance = 90;
		}Visual;
	};
}

inline Cheat::Options g_Options;