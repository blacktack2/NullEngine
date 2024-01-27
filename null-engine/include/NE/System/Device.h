/**
 * GraphicsDevice.h
 */
#ifndef NULLENGINE_DEVICE_H
#define NULLENGINE_DEVICE_H

#include "NE/Core/Core.h"

#include <memory>
#include <string>

namespace null
{
    namespace system
    {
        /**
         * Wrapper class for managing the graphics device and all relevant API/functionality.
         */
        class Device
        {
        public:
            Device(core::Engine& engine);
            ~Device();

            /**
             * @return true on success, otherwise false. If false is returned use Device::GetDebugMessage to get an
             * error message
             */
            bool Init();

            std::string_view GetDebugMessage() const
            {
                return m_debugMessage;
            }
        private:
            void Destroy();

            bool WindowInit();
        private:
            core::Engine& m_engine;

            std::unique_ptr<DeviceData> m_deviceData;

            std::string m_debugMessage;
        };
    } // namespace system
} // namespace null

#endif //NULLENGINE_DEVICE_H
