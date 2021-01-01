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
  struct Character {
      unsigned int TextureID;  // ID handle of the glyph texture
      glm::ivec2   Size;       // Size of glyph
      glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
      unsigned int Advance;    // Offset to advance to next glyph
  };
    /// \brief
    class UI
    {
    private :
      FT_Library m_ft;
      FT_Face m_face;
      std::map<char, Character> Characters;
      Shader *m_textShader;

      GLuint mVbo,mVao;
	    glm::mat4 mProj;

    public:
        /// \brief
        UI();
        /// \brief
        ~UI() = default;

        void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);
        void render();
        void initialization();
        void initializeText();

    };

} // namespace engine

#endif /* _Obstacle_HPP_ */
