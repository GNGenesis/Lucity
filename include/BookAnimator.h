#ifndef BOOKANIMATOR_H_
#define BOOKANIMATOR_H_

#include "Component.h"
#include "Book.h"
#include "Sprite.h"

#include <string>
#include <unordered_map>
#include <memory>

class BookAnimator : public Component {
private:
	Book* book;
	Sprite* activeSprite;
	std::string action;
	std::unordered_map<std::string, Sprite*> sprites;

public:
	BookAnimator(GameObject& associated, Book* book);
	~BookAnimator();
	void Start();
	void BuildSprites();
	void Update(float dt);
	bool Is(std::string type);
};

#endif /* BOOKANIMATOR_H_ */