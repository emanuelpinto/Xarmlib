// ----------------------------------------------------------------------------
// @file    lpc84x_pins.hpp
// @brief   NXP LPC84x pin and port classes.
// @date    21 March 2018
// ----------------------------------------------------------------------------
//
// Xarmlib 0.1.0 - https://github.com/hparracho/Xarmlib
// Copyright (c) 2018 Helder Parracho (hparracho@gmail.com)
//
// See README.md file for additional credits and acknowledgments.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
// ----------------------------------------------------------------------------

#ifndef __XARMLIB_TARGETS_LPC84X_PINS_HPP
#define __XARMLIB_TARGETS_LPC84X_PINS_HPP

#ifdef __LPC84X__

#include <array>

#include "targets/LPC84x/lpc84x_cmsis.h"

namespace xarmlib
{
namespace lpc84x
{




class Pin
{
    public:

        // --------------------------------------------------------------------
        // PUBLIC DEFINITIONS
        // --------------------------------------------------------------------

        // Pin names according to the target package
        enum class Name
        {
            // LPC84x Pin Names
            P0_0 = 0,
            P0_1,
            P0_2,
            P0_3,
            P0_4,
            P0_5,
            P0_6,
            P0_7,
            P0_8,
            P0_9,
            P0_10,
            P0_11,
            P0_12,
            P0_13,
            P0_14,
            P0_15,
            P0_16,
            P0_17,
            P0_18,
            P0_19,
            P0_20,
            P0_21,
            P0_22,
            P0_23,
            P0_24,
            P0_25,
            P0_26,
            P0_27,
            P0_28,

            // The following pins are not present
            // in HVQFN33 packages
#if (__LPC84X_PINS__ >= 48)
            P0_29,
            P0_30,
            P0_31,
            P1_0,
            P1_1,
            P1_2,
            P1_3,
            P1_4,
            P1_5,
            P1_6,
            P1_7,
            P1_8,
            P1_9,

            // The following pins are not present
            // in HVQFN33, HVQFN48 or LQFP48 packages
#if (__LPC84X_PINS__ == 64)
            P1_10,
            P1_11,
            P1_12,
            P1_13,
            P1_14,
            P1_15,
            P1_16,
            P1_17,
            P1_18,
            P1_19,
            P1_20,
            P1_21,
#endif // (__LPC84X_PINS__ == 64)
#endif // (__LPC84X_PINS__ >= 48)

            // Not connected
            NC
        };

        // Pin direction options
        enum class Direction
        {
            INPUT = 0,
            OUTPUT
        };

        // Pin mode options
        enum class Mode
        {
            PULL_NONE  = 0,
            PULL_DOWN,
            PULL_UP,
            REPEATER,
            OPEN_DRAIN
        };

        // --------------------------------------------------------------------
        // PUBLIC MEMBER FUNCTIONS
        // --------------------------------------------------------------------

        static void mode(const Name pin, const Mode mode)
        {
            if(pin == Pin::Name::NC)
            {
                return;
            }

            #if (__LPC84X_PINS__ == 64)
            if(pin == Name::P0_10 || pin == Name::P0_11)
            {
                // True open-drain pins
                return;
            }
            #endif

            const int32_t pin_index = m_pin_number_to_iocon[static_cast<int32_t>(pin)];

            __IO uint32_t* reg = &LPC_IOCON->PIO[pin_index];

            if(mode == Mode::OPEN_DRAIN)
            {
                *reg |= (1 << 10);
            }
            else
            {
                *reg = (*reg & ~(0x03 << 3)) | ((static_cast<uint32_t>(mode) & 0x03) << 3);
            }
        }

    private:

        // --------------------------------------------------------------------
        // PRIVATE MEMBER FUNCTIONS
        // --------------------------------------------------------------------

        // --------------------------------------------------------------------
        // PRIVATE DEFINITIONS
        // --------------------------------------------------------------------

        // IOCON pin values
#if (__LPC84X_PINS__ == 33)
        static constexpr std::array<uint8_t, 29> m_pin_number_to_iocon
#elif (__LPC84X_PINS__ == 48)
        static constexpr std::array<uint8_t, 42> m_pin_number_to_iocon
#elif (__LPC84X_PINS__ == 64)
        static constexpr std::array<uint8_t, 54> m_pin_number_to_iocon
#else
#error "Target package invalid or not defined!"
#endif
        {
            // PORT0
            0x11,   // P0.0
            0x0B,   // P0.1
            0x06,   // P0.2
            0x05,   // P0.3
            0x04,   // P0.4
            0x03,   // P0.5
            0x10,   // P0.6
            0x0F,   // P0.7
            0x0E,   // P0.8
            0x0D,   // P0.9
            0x08,   // P0.10
            0x07,   // P0.11
            0x02,   // P0.12
            0x01,   // P0.13
            0x12,   // P0.14
            0x0A,   // P0.15
            0x09,   // P0.16
            0x00,   // P0.17
            0x1E,   // P0.18
            0x1D,   // P0.19
            0x1C,   // P0.20
            0x1B,   // P0.21
            0x1A,   // P0.22
            0x19,   // P0.23
            0x18,   // P0.24
            0x17,   // P0.25
            0x16,   // P0.26
            0x15,   // P0.27
            0x14,   // P0.28

            // The following pins are not present
            // in HVQFN33 packages
#if (__LPC84X_PINS__ >= 48)
            0x32,   // P0.29
            0x33,   // P0.30
            0x23,   // P0.31

            // PORT1
            0x24,   // P1.0
            0x25,   // P1.1
            0x26,   // P1.2
            0x29,   // P1.3
            0x2A,   // P1.4
            0x2B,   // P1.5
            0x2E,   // P1.6
            0x31,   // P1.7
            0x1F,   // P1.8
            0x20,   // P1.9

            // The following pins are not present
            // in HVQFN33, HVQFN48 or LQFP48 packages
#if (__LPC84X_PINS__ == 64)
            0x37,   // P1.10
            0x36,   // P1.11
            0x21,   // P1.12
            0x22,   // P1.13
            0x27,   // P1.14
            0x28,   // P1.15
            0x2C,   // P1.16
            0x2D,   // P1.17
            0x2F,   // P1.18
            0x30,   // P1.19
            0x34,   // P1.20
            0x35,   // P1.21
#endif // (__LPC84X_PINS__ == 64)
#endif // (__LPC84X_PINS__ >= 48)
        };
};




class Port
{
    public:

        // --------------------------------------------------------------------
        // PUBLIC DEFINITIONS
        // --------------------------------------------------------------------

        // Port names according to the target package
        enum class Name
        {
            PORT0 = 0,
#if (__LPC84X_PINS__ >= 48)
            PORT1
#endif
        };

        // --------------------------------------------------------------------
        // PUBLIC MEMBER FUNCTIONS
        // --------------------------------------------------------------------

    private:

        // --------------------------------------------------------------------
        // PRIVATE MEMBER FUNCTIONS
        // --------------------------------------------------------------------

        // --------------------------------------------------------------------
        // PRIVATE DEFINITIONS
        // --------------------------------------------------------------------
};




} // namespace lpc84x
} // namespace xarmlib

#endif // __LPC84X__

#endif // __XARMLIB_TARGETS_LPC84X_PIN_HPP
