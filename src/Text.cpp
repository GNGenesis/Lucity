#include "Text.h"
#include "Game.h"
#include "Resources.h"
#include "Camera.h"

Text::Text(GameObject& associated) : Component(associated) {
	texture = nullptr;
	font = nullptr;
	fontFile = "";
	fontSize = 0;
	text = "";
	color = SDL_Color {};
	style = SOLID;
}

Text::Text(GameObject& associated, std::string fontFile, int fontSize,
		   std::string text, SDL_Color color, TextStyle style) : Text(associated) {
	Text::fontFile = fontFile;
	Text::fontSize = fontSize;
	Text::text = text;
	Text::color = color;
	Text::style = style;
	Open();
}

Text::~Text() {
	if(texture)
		SDL_DestroyTexture(texture);
	texture = nullptr;
	font = nullptr;
}

void Text::RemakeTexture() {
	if(IsOpen())
		SDL_DestroyTexture(texture);
	
	SDL_Surface* surface = nullptr;
	if(style == SOLID)
		surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
	if(style == SHADED)
		surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color, SDL_Color {});
	if(style == BLENDED)
		surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
	SDL_FreeSurface(surface);
	
	if(!IsOpen()) {
		printf("IMG_LoadTexture failed: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	int w, h;
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	associated.box.SetSize(Vec2(w, h));
}

void Text::Open() {
	font = Resources::GetFont(fontFile, fontSize);
	RemakeTexture();
}

void Text::SetFontFile(std::string fontFile) {
	Text::fontFile = fontFile;
	Open();
}

void Text::SetFontSize(int fontSize) {
	Text::fontSize = fontSize;
	Open();
}

void Text::SetText(std::string text) {
	Text::text = text;
	RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
	Text::color = color;
	RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
	Text::style = style;
	RemakeTexture();
}

void Text::Update(float dt) {

}

void Text::Render() {
#ifdef DEBUG
	Rect box(associated.box);
	Vec2 center(box.GetCenter());
	float rotation = associated.rotation;
	SDL_Point points[5];

	Vec2 point;
	point = (Vec2(box.x, box.y)-center).Rotate(rotation)+center-Camera::pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x+box.w, box.y)-center).Rotate(rotation)+center-Camera::pos;
	points[1] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x+box.w, box.y+box.h)-center).Rotate(rotation)+center-Camera::pos;
	points[2] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x, box.y+box.h)-center).Rotate(rotation)+center-Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 0, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
	SDL_Rect clipRect = SDL_Rect {0, 0, (int)associated.box.w, (int)associated.box.h};
	SDL_Rect dstRect = clipRect;
	dstRect.x = (int)associated.box.x-Camera::pos.x;
	dstRect.y = (int)associated.box.y-Camera::pos.y;
	SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect,
					 associated.rotation, nullptr, SDL_FLIP_NONE);
}

bool Text::Is(std::string type) {
	return (type == "Text");
}

bool Text::IsOpen() {
	return (!texture) ? false : true;
}
