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
  struct Character
  {
    unsigned int textureID; // ID handle of the glyph texture
    glm::ivec2 size;        // Size of glyph
    glm::ivec2 bearing;     // Offset from baseline to left/top of glyph
    unsigned int advance;   // Offset to advance to next glyph
  };
  /// \brief
  class UI
  {
  private:
    FT_Library m_ft;
    FT_Face m_face;
    std::map<char, Character> m_characters;
    Shader *m_textShader;

    GLuint m_vbo, m_vao;

    std::string m_scoreText = "0";

    float m_wWidth;
    float m_wHeight;

  public:
    /// \brief
    UI() = default;
    /// \brief
    ~UI();

    void updateMatrix(float width, float height);

    void initialize();
    void initializeText();

    void reset();

    void updateScore(unsigned int score);

    void renderText(std::string text, float x, float y, float scale, glm::vec3 color);
    void render();
  };

} // namespace engine

#endif /* _Obstacle_HPP_ */
