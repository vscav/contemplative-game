#include <engine/InputManager.hpp>
#include <engine/GLApplication.hpp>

namespace engine
{

	void InputManager::keyPressed(InputCodes code)
	{
		if (GLApplication::getInstance().getCamera() == nullptr)
			return;

		switch (code)
		{
		case Up:
			GLApplication::getInstance().getScene()->player()->moveForward(-1);
			break;
		case Down:
			GLApplication::getInstance().getScene()->player()->moveForward(1);
			break;
		case Left:
			GLApplication::getInstance().getScene()->player()->moveLeft(-1);
			break;
		case Right:
			GLApplication::getInstance().getScene()->player()->moveLeft(1);
			break;
		case Jump:
			GLApplication::getInstance().getScene()->player()->moveUp(1);
			break;
		case Pause:
			GLApplication::getInstance().pause();
			GLApplication::getInstance().getAudioManager()->pause();
				break;
		default:
			break;
		}
	}

	void InputManager::mouseMoved(float mouseX, float mouseY)
	{
		// Return if we don't have a valid camera assigned
		if (GLApplication::getInstance().getCamera() == nullptr)
			return;

		GLApplication::getInstance().getCamera()->rotateLeft(mouseX);
		GLApplication::getInstance().getCamera()->rotateUp(mouseY);
	}

	void InputManager::wheelMoved(double offsetY)
	{
		// Return if we don't have a valid camera assigned
		if (GLApplication::getInstance().getCamera() == nullptr)
			return;

		GLApplication::getInstance().getCamera()->moveFront(offsetY * GLApplication::getInstance().getCamera()->getSpeed());
	}

} // namespace engine
