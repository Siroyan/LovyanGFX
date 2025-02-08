/*----------------------------------------------------------------------------/
 *  Lovyan GFX - Graphics library for embedded devices.
 *
 * Original Source:
 * https://github.com/lovyan03/LovyanGFX/
 *
 * Licence:
 * [FreeBSD](https://github.com/lovyan03/LovyanGFX/blob/master/license.txt)
 *
 * Author:
 * [lovyan03](https://twitter.com/lovyan03)
 *
 * Contributors:
 * [ciniml](https://github.com/ciniml)
 * [mongonta0716](https://github.com/mongonta0716)
 * [tobozo](https://github.com/tobozo)
 * /----------------------------------------------------------------------------*/

#if defined (ESP_PLATFORM)

#include "Panel_AXS15231B.hpp"
#include "../Bus.hpp"
#include "../platforms/common.hpp"
#include "../misc/pixelcopy.hpp"
#include "../misc/colortype.hpp"
#include "driver/spi_master.h"
#include "esp_log.h"

namespace lgfx
{
    inline namespace v1
    {
        bool Panel_AXS15231B::init(bool use_reset)
        {
            if (!Panel_Device::init(use_reset)) {
                return false;
            }

            return true;
        }

        void Panel_AXS15231B::write_cmd(uint8_t cmd)
        {
            uint8_t cmd_buffer[4] = {0x02, 0x00, 0x00, 0x00};
            cmd_buffer[2] = cmd;
            // _bus->writeBytes(cmd_buffer, 4, 0, false);
            for (int i = 0; i < 4; i++) {
                _bus->writeCommand(cmd_buffer[i], 8);
            }
        }


        void Panel_AXS15231B::start_qspi()
        {
            /* Begin QSPI */
            cs_control(false);
            _bus->writeCommand(0x32, 8);
            _bus->writeCommand(0x00, 8);
            _bus->writeCommand(0x2C, 8);
            _bus->writeCommand(0x00, 8);
            _bus->wait();
        }

        void Panel_AXS15231B::end_qspi()
        {
            /* Stop QSPI */
            _bus->writeCommand(0x32, 8);
            _bus->writeCommand(0x00, 8);
            _bus->writeCommand(0x00, 8);
            _bus->writeCommand(0x00, 8);
            _bus->wait();
            cs_control(true);
        }
    }
}

#endif