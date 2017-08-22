#ifndef PHYSICS_SPRITE_H
#define PHYSICS_SPRITE_H
#include "../include/Sprite2D.h"
#include <Box2D/Box2D.h>

namespace Johnny
{
    class Texture;
    
    class PhysicsSprite2D : public Sprite2D
    {
    public:
		PhysicsSprite2D(b2Body* body = nullptr);
		PhysicsSprite2D(const std::string&,b2Body* body = nullptr);
		PhysicsSprite2D(Texture*,b2Body* body = nullptr);
        virtual ~PhysicsSprite2D();
        
        virtual bool init();
        virtual bool m_update();
        virtual void m_quit();
        
        b2Body* getBody() {return m_body;}
        bool getAutomaticDestroy() {return m_automaticDestroy;}
        const Vector2f& getOffset() const {return m_offset;}
        
        void setBody(b2Body* body) {m_body = body; body->SetUserData(this);}
        void setAutomaticDestroy(bool b) {m_automaticDestroy = b;}
        void setOffset(const Vector2f& v) {m_offset = v;}

        virtual void BeginContact(b2Contact*,b2Fixture*,b2Fixture*);
        virtual void EndContact(b2Contact*,b2Fixture*,b2Fixture*);
        virtual void PreSolve(b2Contact*,b2Fixture*,b2Fixture*,const b2Manifold*);
        virtual void PostSolve(b2Contact*,b2Fixture*,b2Fixture*,const b2ContactImpulse*);

    protected:
        bool m_automaticDestroy = true;
        Vector2f m_offset;
        
    private:
		virtual void attachBodyToSprite();

        b2Body* m_body = nullptr;
    };
}


#endif
