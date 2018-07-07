#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT
#define ESCAPE_KEY  SDLK_ESCAPE
#define CONFIRM  SDLK_RETURN

#define INCLUDE_SDL
#include "SDL_include.h"

#include "Vec2.h"

#include <vector>
#include <unordered_map>

class InputManager {
private:
	static std::unordered_map<int, bool> keyState;
	static std::unordered_map<int, int> keyUpdate;
	static bool toggleMouse;
	static bool mouseState [6];
	static int mouseUpdate [6];
	static int lastKey;
	static int mouseWheel;
	static int mouseX;
	static int mouseY;
	static int updateCounter;
	static bool quitRequested;

	//Joystick Related
	static std::vector<SDL_Joystick*> joysticks;
	static bool joyState [10];
	static int joyUpdate [10];
	static Vec2 joyAxis;

public:
	static void Update();
	static bool KeyPress(int key);
	static bool KeyRelease(int key);
	static bool IsKeyDown(int key);
	static bool MousePress(int button);
	static bool MouseRelease(int button);
	static bool IsMouseDown(int button);
	static int GetMouseWheel();
	static int GetMouseX();
	static int GetMouseY();
	static int GetLastKey();
	static Vec2 GetMousePos();
	static Vec2 GetMouseTruePos();
	static bool GetToggle();
	static bool QuitRequested();

	//Joystick Related
	static void LoadJoysticks();
	static void CloseJoysticks();
	static void AddJoystick(SDL_Joystick* joystick);
	static SDL_Joystick* GetJoystick(unsigned int nJoy);
	static Vec2 GetJoyAxis(unsigned int nJoy);
	static int JoyAxisAngle(unsigned int nJoy);
	static bool JoyAxisEvent(unsigned int nJoy);
	static bool IsJButtonDown(unsigned int nJoy, int jbutton);
};

#endif /* INPUTMANAGER_H_ */
