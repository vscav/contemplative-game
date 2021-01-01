#include <engine/UI.hpp>

#include <GL/glew.h>

#include <iostream>

namespace engine
{


    UI::UI()
    {
    }

    void UI::initializeText(){

      m_textShader = Shader("application/res/shaders/text.vert", "application/res/shaders/text.frag");

      if (FT_Init_FreeType(&m_ft))
      {
          std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
      }

      if (FT_New_Face(m_ft, "application/res/fonts/Montserrat-Regular.ttf", 0, &m_face))
      {
          std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
      }

      else {
          FT_Set_Pixel_Sizes(m_face, 0, 48);
          glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

          for (unsigned char c = 0; c < 128; c++)
          {
              // load character glyph
              if (FT_Load_Char(m_face, c, FT_LOAD_RENDER))
              {
                  std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                  continue;
              }
              // generate texture
              unsigned int texture;
              glGenTextures(1, &texture);
              glBindTexture(GL_TEXTURE_2D, texture);
              glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, m_face->glyph->bitmap.buffer);

              // set texture options
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

              // now store character for later use
              Character character;
              character.TextureID = texture;
              character.Size = glm::ivec2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows);
              character.Bearing = glm::ivec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top);
              character.Advance = m_face->glyph->advance.x;
              Characters.insert(std::pair<char, Character>(c, character));
          }
      }

      // destroy FreeType once we're finished
      FT_Done_Face(m_face);
      FT_Done_FreeType(m_ft);
    }

    void UI::initialization()
    {
        glGenBuffers(1, &mVbo);
        glBindBuffer(GL_ARRAY_BUFFER, mVbo);
        glBufferData(GL_ARRAY_BUFFER, 6 * 4 * sizeof(float), NULL, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glGenVertexArrays(1, &mVao);
        glBindVertexArray(mVao);
        glBindBuffer(GL_ARRAY_BUFFER, mVbo);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void UI::update(){
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

      RenderText("This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
      RenderText("(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f));

      glDisable(GL_BLEND);
    }

    void UI::RenderText(std::string text, float x, float y, float scale, glm::vec3 color)
    {
      glEnable(GL_BLEND);
      glEnable(GL_DEPTH_TEST);
      m_textShader.bind();
      m_textShader.setMat4("uModelViewProjMatrix",mProj);

      // activate corresponding render state
      m_textShader.setVec3f("uTextColor",color);
      glActiveTexture(GL_TEXTURE0);
      glBindVertexArray(mVao);

      // iterate through all characters
      std::string::const_iterator c;
      for (c = text.begin(); c != text.end(); c++)
      {
          Character ch = Characters[*c];

          float xpos = x + ch.Bearing.x * scale;
          float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

          float w = ch.Size.x * scale;
          float h = ch.Size.y * scale;
          // update VBO for each character
          float vertices[6][4] = {
              { xpos,     ypos + h,   0.0f, 0.0f },
              { xpos,     ypos,       0.0f, 1.0f },
              { xpos + w, ypos,       1.0f, 1.0f },

              { xpos,     ypos + h,   0.0f, 0.0f },
              { xpos + w, ypos,       1.0f, 1.0f },
              { xpos + w, ypos + h,   1.0f, 0.0f }
          };
          // render glyph texture over quad
          glBindTexture(GL_TEXTURE_2D, ch.TextureID);
          // update content of VBO memory
          glBindBuffer(GL_ARRAY_BUFFER, mVbo);
          glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
          glBindBuffer(GL_ARRAY_BUFFER, 0);
          // render quad
          glDrawArrays(GL_TRIANGLES, 0, 6);
          // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
          x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
      }
      glBindVertexArray(0);
      glBindTexture(GL_TEXTURE_2D, 0);

      glDisable(GL_DEPTH_TEST);
      glDisable(GL_BLEND);
    }


} // namespace engine