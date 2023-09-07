#pragma once
#include <vector>
#include <list>
#include <map>
#include <set>
#include <functional>
#include <string>
#include <filesystem>
#include <bitset>

#include "framework.h"
#include "exMath.h"

// Assert() ÇÔ¼ö
#include <cassert>

#define DIRECTINPUT_VERSION 0x0800
#pragma comment(lib, "Msimg32.lib")

// Sound 
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")



#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")


namespace ex::enums
{
	enum class eLayerType
	{
		Background,
		Floor,
		Wall,
		Rope,
		NPC,
		Monster,
		Potal,
		Buff,
		Player,
		BuffEffect,
		PlayerAttack,
		Effect,
		BuffUI,
		UI,
		End,
	};

	enum class eComponentType
	{
		Transform,
		SpriteRenderer,
		Animation,
		Animator,
		Collider,
		Rigidbody,
		End,
	};
	
	enum class eMoveDir
	{
		Right,
		Left,
		End,
	};

}

 

