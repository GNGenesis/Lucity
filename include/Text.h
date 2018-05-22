#ifndef TEXT_H_
#define TEXT_H_

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_TTF
#include "SDL_include.h"

#include "Component.h"

#include <string>
#include <memory>

class Text : public Component {
public:
	enum TextStyle {SOLID, SHADED, BLENDED};

	Text(GameObject& associated);
	Text(GameObject& associated, std::string fontFile, int fontSize, std::string text, SDL_Color color, TextStyle style);
	~Text();
	void Open();
	void SetFontFile(std::string fontFile);
	void SetFontSize(int fontSize);
	void SetText(std::string text);
	void SetColor(SDL_Color color);
	void SetStyle(TextStyle style);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	bool IsOpen();

private:
	std::shared_ptr<TTF_Font> font;
	SDL_Texture* texture;
	std::string fontFile;
	int fontSize;
	std::string text;
	SDL_Color color;
	TextStyle style;

	void RemakeTexture();
};

#endif /* TEXT_H_ */
