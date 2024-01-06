#include "NE/Core/Core.h"

#include "NE/Core/Engine.h"

int main()
{
    null::core::Engine engine;
    engine.Init();

    engine.RegisterOnUpdate([&engine]()
    {
        engine.GetInput().GetKeyboard().DebugPrint();
        engine.GetInput().GetMouse().DebugPrint();
        usleep(500000);
    });

    engine.Run();

    return 0;
}
