#include "button.h"

using namespace std;
using namespace fastdelegate;

Button::Button(GMenu2X * gmenu2x) {
	this->gmenu2x = gmenu2x;
	action = MakeDelegate(this, &Button::voidAction);
	setPosition(0,0);
	setSize(0,0);
}

void Button::paint() {
	if (gmenu2x->ts.inRect(rect))
		if (!paintHover()) return;
}

bool Button::paintHover() {
	return false;
}

bool Button::handleTS() {
	if (gmenu2x->ts.inRect(rect)) {
		exec();
		return true;
	} else {
		return false;
	}
}

void Button::exec() {
	action();
}

void Button::setSize(int w, int h) {
	rect.w = w;
	rect.h = h;
}

void Button::setPosition(int x, int y) {
	rect.x = x;
	rect.y = y;
}

void Button::setAction(ButtonAction action) {
	this->action = action;
}
