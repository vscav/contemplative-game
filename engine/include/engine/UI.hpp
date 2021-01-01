#pragma once
#ifndef _UI_HPP_
#define _UI_HPP_

#include <ft2build.h>
#include FT_FREETYPE_H

namespace engine
{

    class UI
    {
    protected:
      FT_Library ft;
      FT_Face face;


    public:
        /// \brief
        UI();
        /// \brief
        ~UI() = default;

    };

} // namespace engine

#endif /* _Player_HPP_ */
