// (c) 2013 Maarten ter Huurne <maarten@treewalker.org>
// License: GPL version 2 or later.

#ifndef LAYER_H
#define LAYER_H

#include "inputmanager.h"

class Surface;
class Touchscreen;


/**
 * Abstract base class for UI layers.
 * A layer handles both painting and input events.
 */
class Layer {
public:
	enum class Status { PASSIVE, ANIMATING, DISMISSED };

	virtual ~Layer() {}

	/**
	 * Paints this layer on the given surface.
	 */
	virtual void paint(Surface &s) = 0;

	/**
	 * Handles the pressing of the give button.
	 * Returns true iff the button press event was fully handled by this layer.
	 */
	virtual bool handleButtonPress(InputManager::Button button) = 0;

	/**
	 * Handles the touch screen.
	 * Only called if there is a touch screen available.
	 * Returns true iff the touch screen was fully handled by this layer.
	 */
	virtual bool handleTouchscreen(Touchscreen &ts) = 0;

	Status getStatus() { return status; }

protected:
	/**
	 * Request the Layer to be removed from the stack.
	 * There could be a few more calls to the Layer before it is actually
	 * removed, so be prepared to handle those.
	 */
	void dismiss() {
		status = Status::DISMISSED;
	}

	/**
	 * Request that this layer be repainted every frame.
	 */
	void startAnimating() {
		if (status == Status::PASSIVE) status = Status::ANIMATING;
	}

	/**
	 * Request that this layer be repainted only after an event.
	 */
	void stopAnimating() {
		if (status == Status::ANIMATING) status = Status::PASSIVE;
	}

private:
	Status status = Status::PASSIVE;
};

#endif // LAYER_H
