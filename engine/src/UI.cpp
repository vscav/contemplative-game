#include <engine/GLApplication.hpp>
#include <engine/UI.hpp>
#include <engine/GLWindowUtils.hpp>

#include <GL/glew.h>

#include <iostream>

namespace engine
{

  UI::~UI()
  {
    delete m_textShader;
  }

  void UI::initializeText()
  {

    m_textShader = new Shader("application/res/shaders/text.vert", "application/res/shaders/text.frag");

    if (FT_Init_FreeType(&m_ft))
    {
      std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }

    if (FT_New_Face(m_ft, "application/res/fonts/CarterOne-Regular.ttf", 0, &m_face))
    {
      std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }

    else
    {
      FT_Set_Pixel_Sizes(m_face, 0, 50);
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

      for (unsigned char c = 0; c < 128; c++)
      {

        if (FT_Load_Char(m_face, c, FT_LOAD_RENDER))
        {
          std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
          continue;
        }

        unsigned int texture;

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, m_face->glyph->bitmap.buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character;

        character.textureID = texture;
        character.size = glm::ivec2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows);
        character.bearing = glm::ivec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top);
        character.advance = m_face->glyph->advance.x;

        m_characters.insert(std::pair<char, Character>(c, character));
      }
    }

    FT_Done_Face(m_face);
    FT_Done_FreeType(m_ft);
  }

  void UI::initialize()
  {
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, 6 * 4 * sizeof(float), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }

  void UI::updateMatrix(float width, float height)
  {
    m_wWidth = width;
    m_wHeight = height;
  }

  void UI::updateScore(unsigned int score)
  {
    m_scoreText = std::to_string(score);
  }

  void UI::reset()
  {
    m_scoreText = "0";
  }

  void UI::render()
  {
    renderText("Collect the gems", m_wWidth / 2 - 200, m_wHeight - 75.0, 1.0, glm::vec3(1.0, 1.0, 1.0));

    if (GLApplication::getInstance().getState() == stateWin)
    {
      renderText("You have collected all the resources", m_wWidth / 2 - 435, m_wHeight / 2, 1.0, glm::vec3(1.0, 1.0, 1.0));
    }

    renderText(m_scoreText + "/10", m_wWidth / 2 - 50, 50.0, 1.0, glm::vec3(1.0, 1.0, 1.0));
  }

  void UI::renderText(std::string text, float x, float y, float scale, glm::vec3 color)
  {
    m_textShader->bind();

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_textShader->setMat4("uProjection", glm::ortho(0.0f, m_wWidth, 0.0f, m_wHeight));
    m_textShader->setVec3f("uTextColor", color);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_vao);

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
      Character ch = m_characters[*c];

      float xpos = x + ch.bearing.x * scale;
      float ypos = y - (ch.size.y - ch.bearing.y) * scale;

      float w = ch.size.x * scale;
      float h = ch.size.y * scale;

      float vertices[6][4] = {
          {xpos, ypos + h, 0.0f, 0.0f},
          {xpos, ypos, 0.0f, 1.0f},
          {xpos + w, ypos, 1.0f, 1.0f},

          {xpos, ypos + h, 0.0f, 0.0f},
          {xpos + w, ypos, 1.0f, 1.0f},
          {xpos + w, ypos + h, 1.0f, 0.0f}};

      glBindTexture(GL_TEXTURE_2D, ch.textureID);

      glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
      glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
      glBindBuffer(GL_ARRAY_BUFFER, 0);

      glDrawArrays(GL_TRIANGLES, 0, 6);

      x += (ch.advance >> 6) * scale;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    m_textShader->unbind();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
  }

} // namespace engine
