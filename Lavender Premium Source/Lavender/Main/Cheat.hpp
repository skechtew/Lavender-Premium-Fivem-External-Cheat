#pragma once

// ImGui

#include <Utils/Dependencies/ImGui/imgui.h>
#include <Utils/Dependencies/ImGui/imgui_impl_dx11.h>
#include <Utils/Dependencies/ImGui/imgui_impl_win32.h>
#include <Utils/Dependencies/ImGui/imgui_internal.h>

#include "Options.hpp"

namespace Cheat
{
	void Initialize();
	void ShutDown();
}