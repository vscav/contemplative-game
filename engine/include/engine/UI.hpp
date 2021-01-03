#pragma once
#ifndef _UI_HPP_
#define _UI_HPP_

#include <ft2build.h>
#include FT_FREETYPE_H
#include <engine/dependencies/glm.hpp>
#include <engine/Shader.hpp>

#include <iostream>
#include <map>
#include <memory>

namespace engine
{
  /// \struct
  /// \brief A structure that represents an text character.
  struct Character
  {
    unsigned int textureID; /*!< ID handle of the glyph texture. */
    glm::ivec2 size;        /*!< Size of glyph. */
    glm::ivec2 bearing;     /*!<  Offset from baseline to left/top of glyph. */
    unsigned int advance;   /*!<  Offset to advance to the next glyph. */
  };
  /// \brief
  class UI
  {
  private:
    FT_Library m_ft;                        /*!<  A handle to a FreeType library instance.. */
    FT_Face m_face;                         /*!<  The font used to display the text. */
    std::map<char, Character> m_characters; /*!< A map of the characters. */
    Shader *m_textShader;                   /*!< The shader used to display the text. */

    GLuint m_vbo, m_vao; /*!< Offset to advance to the next glyph. */

    std::string m_scoreText = "0"; /*!< The current score to display. */

    float m_wWidth;  /*!< The width of the window. */
    float m_wHeight; /*!< The height of the window. */

  public:
    /// \brief Default constructor.
    UI() = default;
    /// \brief Destructor.
    ~UI();

    /// \brief Initializes the opengl objects.
    void initialize();
    /// \brief Initializes the library used to render the text.
    void initializeText();

    /// \brief Resets the score to display.
    void reset();

    /// \brief Updates the matrix based on the window manager of the application.
    void updateMatrix(float width, float height);
    /// \brief Updates the score to display.
    void updateScore(unsigned int score);

    /// \brief Creates the quads containing the characters.
    void renderText(std::string text, float x, float y, float scale, glm::vec3 color);
    /// \brief Renders the UI.
    void render();
  };

} // namespace engine

#endif /* _Obstacle_HPP_ */
