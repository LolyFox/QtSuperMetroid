/**
 * @file Object.h
 *
 * @brief The main variables qualifying an Object through their sprites
 *
 * @date 15 october 2019
 *
 * @author LolyFox
 *
 */

#pragma once

/*!
 * \struct spriteFrame
 * \brief The spriteFrame struct is made to take the wanted shape form QPaint function
 */
struct spriteFrame
{
    unsigned short shift;
    unsigned short level;
    unsigned short width;
    unsigned short height;
};
