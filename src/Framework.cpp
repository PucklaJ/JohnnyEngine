#include "../include/Framework.h"
#include "../include/SDLFramework.h"
#include "../include/GLFWFramework.h"

namespace Johnny
{
    Framework* Framework::createFramework(Frameworks fw)
    {
        switch(fw)
        {
            case Frameworks::SDL:
                return new SDLFramework();
#ifdef USE_GLFW
			case Frameworks::GLFW:
				return new GLFWFramework();
#endif
            default:
                return nullptr;
        }
    }
}