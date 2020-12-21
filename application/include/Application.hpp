#pragma once
#ifndef _Application_HPP_
#define _Application_HPP_

#include <engine/GLApplication.hpp>

/// \class Application
/// \brief Class which inherites from the global GLApplication class.
class Application : public engine::GLApplication
{
protected:
  /// \brief The application loop (run until the user asks to quit).
  virtual void loop();

public:
  /// \brief Constructor.
  Application();
  /// \brief Parameterized Constructor.
  /// \param title : The application title (string).
  /// \param width : The application width value.
  /// \param height : The application height value.
  /// \param fullScreen : A boolean to determine if the application window is in full screen mode.
  explicit Application(std::string title, int width, int height, bool fullScreen);
  /// \brief Destructor.
  virtual ~Application() = default;

  void initialize();
};

#endif /* _Application_HPP_ */