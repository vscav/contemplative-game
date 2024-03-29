#pragma once
#ifndef _InputManager_HPP_
#define _InputManager_HPP_

#include <engine/TimeManager.hpp>
#include <engine/dependencies/glm.hpp>

#include <functional>
#include <map>
#include <vector>

namespace engine
{

	/// \enum InputCodes
	/// \brief An enum for keyboard action inputs.
	enum InputCodes
	{
		Backward,
		Clear,
		Down,
		Forward,
		Left,
		Pause,
		Right,
		Up
	};

	/// \class InputManager
	/// \brief Class used to represent the input manager of the application. It allows us to abstract the input away from the WindowManager.
	class InputManager
	{
	public:
		/// \brief Constructor.
		InputManager() = default;
		/// \brief Destructor.
		~InputManager() = default;

		/// \brief Fires an action depending on the key code received.
		/// \param code : The key code captured.
		static void keyPressed(InputCodes code);
		/// \brief Sends in an updated mouse x and y position that should be a delta from (0, 0).
		/// \param mouseX : The X position of the mouse relative to the screen.
		/// \param mouseY : The Y position of the mouse relative to the screen.
		static void mouseMoved(float mouseX, float mouseY);
		/// \brief Sends in an updated wheel direction.
		/// \param offsetY : The Y direction of the scroll wheel.
		static void wheelMoved(double offsetY);
	};

} // namespace engine

#endif /* _InputManager_HPP_ */
