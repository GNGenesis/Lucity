#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define SPACE_KEY SDLK_SPACE
#define F1_KEY SDLK_F1
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT

#define INCLUDE_SDL
#include "SDL_include.h"

#include "Vec2.h"

#include <vector>
#include <unordered_map>

class InputManager {
private:
	static std::unordered_map<int, bool> keyState;
	static std::unordered_map<int, int> keyUpdate;
	static bool mouseState [6];
	static int mouseUpdate [6];
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
	static int GetMouseX();
	static int GetMouseY();
	static Vec2 GetMousePos();
	static bool QuitRequested();

	//Joystick Related
	static void LoadJoysticks();
	static void CloseJoysticks();
	static void AddJoystick(SDL_Joystick* joystick);
	static SDL_Joystick* GetJoystick(int nJoy);
	static Vec2 GetJoyAxis(int nJoy);
	static int JoyAxisAngle(int nJoy);
	static bool JoyAxisEvent(int nJoy);
	static bool IsJButtonDown(int nJoy, int jbutton);
};

#endif /* INPUTMANAGER_H_ */
