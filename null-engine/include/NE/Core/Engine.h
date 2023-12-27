#ifndef NULLENGINE_ENGINE_H
#define NULLENGINE_ENGINE_H

#include "NE/Core/Core.h"

#include "NE/Rendering/PipelineManager.h"

#include "NE/System/Device.h"
#include "NE/System/Window.h"

#include <functional>
#include <string>
#include <vector>

namespace null
{
    namespace core
    {
        class Engine
        {
        public:
            typedef std::function<void(float dt)> on_update_callback_t;
        public:
            Engine();
            ~Engine();

            void RegisterOnPreUpdate(const on_update_callback_t& onPreUpdate)
            {
                m_onPreUpdateEvents.push_back(onPreUpdate);
            }
            void RegisterOnUpdate(const on_update_callback_t& onUpdate)
            {
                m_onUpdateEvents.push_back(onUpdate);
            }
            void RegisterOnPostUpdate(const on_update_callback_t& onPostUpdate)
            {
                m_onPostUpdateEvents.push_back(onPostUpdate);
            }
            void RegisterOnFixedUpdate(const on_update_callback_t& onFixedUpdate)
            {
                m_onFixedUpdateEvents.push_back(onFixedUpdate);
            }

            /**
             * @return true on success, otherwise false. If false is returned use Engine::GetDebugMessage to get an
             * error message
             */
            bool Init();

            void Run();

            std::string_view GetDebugMessage() const
            {
                return m_debugMessage;
            }
        private:
            void Mainloop();
        private:
            system::Window m_window;
            system::Device m_device;

            render::PipelineManager m_pipelineManager;

            bool m_isRunning = false;

            std::vector<on_update_callback_t> m_onPreUpdateEvents;
            std::vector<on_update_callback_t> m_onUpdateEvents;
            std::vector<on_update_callback_t> m_onPostUpdateEvents;
            std::vector<on_update_callback_t> m_onFixedUpdateEvents;

            std::string m_debugMessage;
        };
    } // namespace core
} // namespace null

#endif //NULLENGINE_ENGINE_H
