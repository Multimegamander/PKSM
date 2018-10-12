/*
*   This file is part of PKSM
*   Copyright (C) 2016-2018 Bernardo Giordano, Admiral Fish, piepie62
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
*       * Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*       * Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/

#include "BallSelectionScreen.hpp"
#include "gui.hpp"
#include "loader.hpp"
#include "Configuration.hpp"

namespace {
    int maxBalls()
    {
        switch (TitleLoader::save->version())
        {
            case 10:
            case 11:
            case 12:
                return 16;
            case 7:
            case 8:
                return 24;
            case 20:
            case 21:
            case 22:
            case 23:
            case 24:
            case 25:
            case 26:
            case 27:
                return 25;
            case 30:
            case 31:
            case 32:
            case 33:
                return 26;
            default:
                return 0;
        }
    }
}

void BallSelectionScreen::draw() const
{
    C2D_SceneBegin(g_renderTargetTop);
    Gui::sprite(ui_sheet_part_mtx_5x6_idx, 0, 0);

    int x = (hid.index() % 6) * 67;
    int y = (hid.index() / 6) * 48;
    // Selector
    C2D_DrawRectSolid(x, y, 0.5f, 66, 47, COLOR_MASKBLACK);
    C2D_DrawRectSolid(x, y, 0.5f, 66, 1, COLOR_YELLOW);
    C2D_DrawRectSolid(x, y, 0.5f, 1, 47, COLOR_YELLOW);
    C2D_DrawRectSolid(x + 65, y, 0.5f, 1, 47, COLOR_YELLOW);
    C2D_DrawRectSolid(x, y + 46, 0.5f, 66, 1, COLOR_YELLOW);

    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 6; x++)
        {
            if (x + y * 6 >= maxBalls())
            {
                break;
            }
            Gui::ball(x + y * 6 + 1, x * 67 + 24, y * 48 + 8);
            Gui::dynamicText(x * 67, y * 48 + 30, 67, i18n::ball(Configuration::getInstance().language(), x + y * 6), FONT_SIZE_9, FONT_SIZE_9, COLOR_WHITE);
        }
    }
}

void BallSelectionScreen::update(touchPosition* touch)
{
    hid.update(maxBalls());
    u32 downKeys = hidKeysDown();
    if (downKeys & KEY_A)
    {
        pkm->ball((u8) hid.fullIndex() + 1);
        done = true;
        return;
    }
    else if (downKeys & KEY_B)
    {
        done = true;
        return;
    }
}