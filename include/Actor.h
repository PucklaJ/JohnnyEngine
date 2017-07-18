#ifndef ACTOR_H
#define ACTOR_H
#include <vector>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include "../include/Transform3D.h"

#define NORM_W 1280.0
#define NORM_H 720.0
#define NATIVE_W (m_mainClass->getNativeRes().getX())
#define NATIVE_H (m_mainClass->getNativeRes().getY())

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif



namespace Johnny
{
    class MainClass;
	class Shader;

    class Actor
    {
    public:
		static const std::vector<Actor*> getAllActors() { return m_allActors; }

            Actor(const char* name = "Actor");
            virtual ~Actor();

            virtual bool init();
            virtual bool update()=0;
            virtual bool m_update();
            virtual bool render();
            virtual void quit();
            virtual void m_quit();

            bool addChild(Actor*,bool instantAdd = true);
            void removeChild(Actor*,bool del = true,bool instant = false);

            void setParent(Actor*);
            void setMainClass(MainClass*);
            void setAffectedByCamera(const bool);
            void setVisible(const bool);
			void setCastsShadows(bool b) { m_castsShadows = b; }
            void setName(const char* name){m_name = name;}
			void setShader(Shader* s,bool changeInRenderManager = true);


            MainClass* getMainClass();
            Actor* getParent(){return m_parent;}
            std::vector<Actor*>& getChildren() {return m_children;}
            bool isAffectedByCamera() const {return m_isAffectedByCamera;}
            const char* getName() const {return m_name;}
            const bool isVisible() const {return m_visible;}
			bool castsShadows() const { return m_castsShadows; }
            const int getID() const {return m_id;}
			Shader* getShader() { return m_shader; }

            bool isChild(Actor*);

            void m_all_quit();
            bool m_all_update();
			bool m_render_render();
            
            virtual bool isOnScreen();

			std::vector<Actor*> getChildrenWithCastsShadow();
    protected:

            MainClass* m_mainClass = nullptr;
            bool m_isAffectedByCamera = true;
            bool m_visible = true;
			bool m_castsShadows = true;
			Shader* m_shader = nullptr;

            const char* m_name = "";

    private:
		static std::vector<Actor*> m_allActors;

            void removeChildrenAfterLoops();
            bool addChildrenBeforeLoops();

            std::vector<int> m_idsToRemove;
            std::vector<bool> m_ifDeleteToRemove;
            std::vector<Actor*> m_childrenToAdd;
            static std::vector<int> m_ids;
            int m_id;

            Actor* m_parent;
            std::vector<Actor*> m_children;

            bool m_initialised = false;
    };
}


#endif // ACTOR_H
