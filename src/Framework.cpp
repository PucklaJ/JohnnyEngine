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
			case Frameworks::GLFW:
				return new GLFWFramework();
            default:
                return nullptr;
        }
    }
}