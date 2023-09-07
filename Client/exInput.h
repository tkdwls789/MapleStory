#pragma once
#include "exCommonInclude.h"

namespace ex
{
	enum class eKeyCode
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		Up, Down, Left, Right, Jump, Ctrl,
		LButton,
		End,
	};

	enum class eAutoCode
	{
		UP,
		LEFT,
		DOWN,
		RIGHT,
		NONE,
	};


	// 키의 상태
	enum class eKeyState
	{
		Down,
		Up,
		Pressed,
		None,
	};



	class Input
	{
	public:
		struct Key
		{
			eKeyCode keyCode;
			eKeyState keyState;
			eAutoCode autoCode;
			bool bPressed;

		};

		static void Initialize();
		static void Update();


		// __forceinline 강제로 inline 사용

		__forceinline static bool GetKeyDown(eKeyCode _keycode)
		{
			return mKeys[(int)_keycode].keyState == eKeyState::Down;
		}

		__forceinline static bool GetKeyUp(eKeyCode _keycode)
		{
			return mKeys[(int)_keycode].keyState == eKeyState::Up;
		}

		__forceinline static bool GetKeyPressed(eKeyCode _keycode)
		{
			return mKeys[(int)_keycode].keyState == eKeyState::Pressed;
		}





		__forceinline static bool GetAutoKeyUp(eAutoCode _keycode)
		{
			return mKeys[(int)_keycode].autoCode == eAutoCode::UP;
		}

		__forceinline static bool GetAutoKeyLeft(eAutoCode _keycode)
		{
			return mKeys[(int)_keycode].autoCode == eAutoCode::LEFT;
		}

		__forceinline static bool GetAutoKeyDown(eAutoCode _keycode)
		{
			return mKeys[(int)_keycode].autoCode == eAutoCode::DOWN;
		}

		__forceinline static bool GetAutoKeyRIGHT(eAutoCode _keycode)
		{
			return mKeys[(int)_keycode].autoCode == eAutoCode::RIGHT;
		}

		static math::Vector2 GetMousePos() { return mMousePos; }


	private:
		//static (전역으로 초기화)
		static std::vector<Key> mKeys;
		static math::Vector2 mMousePos;
	};

}
