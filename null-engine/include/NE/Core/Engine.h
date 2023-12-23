#ifndef NULLENGINE_ENGINE_H
#define NULLENGINE_ENGINE_H

#include "NE/Core/Core.h"

#include "NE/System/Device.h"
#include "NE/System/Window.h"

#include <memory>
#include <string>

namespace null
{
    namespace core
    {
        class Engine
        {
        public:
            Engine();
            ~Engine();

            bool Init();

            std::string_view GetDebugMessage() const
            {
                return m_debugMessage;
            }
        private:
            system::Window m_window;
            system::Device m_device;

            std::string m_debugMessage;
        };
    } // namespace core
} // namespace null

#endif //NULLENGINE_ENGINE_H
