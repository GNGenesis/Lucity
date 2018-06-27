#include "InputManager.h"
#include "Camera.h"

std::unordered_map<int, bool> InputManager::keyState;
std::unordered_map<int, int> InputManager::keyUpdate;
bool InputManager::mouseState [6];
int InputManager::mouseUpdate [6];
int InputManager::mouseWheel;
int InputManager::mouseX;
int InputManager::mouseY;
int InputManager::updateCounter;
bool InputManager::quitRequested = false;

//Joystick Related
std::vector<SDL_Joystick*> InputManager::joysticks;

void InputManager::Update() {
	SDL_Event event;
	SDL_GetMouseState(&mouseX, &mouseY);
	mouseWheel = 0;
	mouseX += Camera::pos.x;
	mouseY += Camera::pos.y;
	updateCounter++;

	while(SDL_PollEvent(&event)) {
		if(event.key.repeat != 1) {
			if(event.type == SDL_QUIT)
				quitRequested = true;
			if(event.type == SDL_MOUSEBUTTONDOWN) {
				mouseState[event.button.button] = true;
				mouseUpdate[event.button.button] = updateCounter;
			}
			if(event.type == SDL_MOUSEBUTTONUP) {
				mouseState[event.button.button] = false;
				mouseUpdate[event.button.button] = updateCounter;
			}
			if(event.type == SDL_MOUSEWHEEL) {
				mouseWheel = event.wheel.y;
				if(event.wheel.y > 0) {

				}
				else if(event.wheel.y < 0) {

				}
			}
			if(event.type == SDL_KEYDOWN) {
				keyState[event.key.keysym.sym] = true;
				keyUpdate[event.key.keysym.sym] = updateCounter;
			}
			if(event.type == SDL_KEYUP) {
				keyState[event.key.keysym.sym] = false;
				keyUpdate[event.key.keysym.sym] = updateCounter;
			}
		}
	}
}

bool InputManager::KeyPress(int key) {
	return (keyUpdate[key] == updateCounter) ? (keyState[key]) : false;
}

bool InputManager::KeyRelease(int key) {
	return (keyUpdate[key] == updateCounter) ? (!keyState[key]) : false;
}

bool InputManager::IsKeyDown(int key) {
	return keyState[key];
}

bool InputManager::MousePress(int button) {
	return (mouseUpdate[button] == updateCounter) ? (mouseState[button]) : false;
}

bool InputManager::MouseRelease(int button) {
	return (mouseUpdate[button] == updateCounter) ? (!mouseState[button]) : false;
}

bool InputManager::IsMouseDown(int button) {
	return mouseState[button];
}

int InputManager::GetMouseWheel() {
	return mouseWheel;
}

int InputManager::GetMouseX() {
	return mouseX;
}

int InputManager::GetMouseY() {
	return mouseY;
}

Vec2 InputManager::GetMousePos() {
	return Vec2(mouseX, mouseY);
}

bool InputManager::QuitRequested() {
	return quitRequested;
}

//Joystick Related
void InputManager::LoadJoysticks() {
	for(unsigned int i = 0; i < SDL_NumJoysticks(); i++) {
		AddJoystick(SDL_JoystickOpen(i));
		if(!GetJoystick(i))
			printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
	}
}

void InputManager::CloseJoysticks() {
	for(unsigned int i = 0; i < joysticks.size(); i++)
		SDL_JoystickClose(joysticks[i]);
	joysticks.clear();
}

void InputManager::AddJoystick(SDL_Joystick* joystick) {
	joysticks.emplace_back(joystick);
}

SDL_Joystick* InputManager::GetJoystick(int nJoy) {
	if(nJoy < joysticks.size())
		return joysticks[nJoy];
	else
		return nullptr;
}

Vec2 InputManager::GetJoyAxis(int nJoy) {
	if(nJoy < joysticks.size())
		return Vec2(SDL_JoystickGetAxis(joysticks[nJoy], 0), SDL_JoystickGetAxis(joysticks[nJoy], 1));
	else
		return Vec2();
}

int InputManager::JoyAxisAngle(int nJoy) {
	if(nJoy < joysticks.size())
		return Vec2().GetAngle(GetJoyAxis(nJoy)/32768);
	else
		return 0;
}

bool InputManager::JoyAxisEvent(int nJoy) {
	if(nJoy < joysticks.size())
		return (GetJoyAxis(nJoy).x != 0 || GetJoyAxis(nJoy).y != 0);
	else
		return false;
}

bool InputManager::IsJButtonDown(int nJoy, int jbutton) {
	return SDL_JoystickGetButton(joysticks[nJoy], jbutton);
}
