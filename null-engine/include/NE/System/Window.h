/**
 * Window.h
 */
#ifndef NULLENGINE_WINDOW_H
#define NULLENGINE_WINDOW_H

#include "NE/Core/Core.h"

#include <memory>
#include <string>

namespace null
{
    namespace system
    {
        /**
         * Wrapper class for managing the application window and all relevant API/functionality.
         */
        class Window
        {
        public:
            Window(core::Engine& engine);
            ~Window();

            void SetBounds(math::uint32 width, math::uint32 height)
            {
                m_width  = width;
                m_height = height;
            }
            math::uint32 GetWidth() const
            {
                return m_width;
            }
            math::uint32 GetHeight() const
            {
                return m_height;
            }

            void SetTitle(std::string_view title)
            {
                m_title = title;
            }

            /**
             * @return true on success, otherwise false. If false is returned use Window::GetDebugMessage to get an
             * error message
             */
            bool Init();

            std::string_view GetDebugMessage() const
            {
                return m_debugMessage;
            }

            WindowData& GetWindowData()
            {
                return *m_windowData;
            }
            const WindowData& GetWindowData() const
            {
                return *m_windowData;
            }
            WindowDeviceData& GetWindowDeviceData()
            {
                return *m_windowDeviceData;
            }
            const WindowDeviceData& GetWindowDeviceData() const
            {
                return *m_windowDeviceData;
            }
        private:
            void Destroy();

            // Device-specific extension methods
            bool DeviceInit();
            void DeviceDestroy();
        private:
            core::Engine& m_engine;

            std::unique_ptr<WindowData> m_windowData;
            std::unique_ptr<WindowDeviceData> m_windowDeviceData;

            math::uint32 m_width  = 100;
            math::uint32 m_height = 100;
            math::sint32 m_minWidth  = 10;
            math::sint32 m_minHeight = 10;
            math::sint32 m_maxWidth  = 10000;
            math::sint32 m_maxHeight = 10000;

            std::string m_title = "Null-Engine Application";

            std::string m_debugMessage;
        };
    } // namespace system
} // namespace null

#endif //NULLENGINE_WINDOW_H
