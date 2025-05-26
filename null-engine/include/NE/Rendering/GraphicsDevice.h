/**
 * GraphicsDevice.h
 */
#pragma once

#include "NE/Core/Core.h"

#include <memory>
#include <string>

namespace null
{
    namespace render
    {
        /**
         * Wrapper class for managing the graphics device and all relevant API/functionality.
         */
        class GraphicsDevice
        {
        public:
            GraphicsDevice(core::Engine& engine);
            ~GraphicsDevice();

            /**
             * @return true on success, otherwise false. If false is returned use Device::GetDebugMessage to get an
             * error message
             */
            bool Init();

            std::string_view GetDebugMessage() const
            {
                return m_debugMessage;
            }

            GraphicsDeviceData& GetGraphicsDeviceData()
            {
                return *m_graphicsDeviceData;
            }
            const GraphicsDeviceData& GetGraphicsDeviceData() const
            {
                return *m_graphicsDeviceData;
            }
        private:
            void Destroy();

            bool WindowInit();
        private:
            core::Engine& m_engine;

            std::unique_ptr<GraphicsDeviceData> m_graphicsDeviceData;

            std::string m_debugMessage;
        };
    } // namespace render
} // namespace null
