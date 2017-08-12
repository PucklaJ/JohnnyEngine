#ifndef PHYSICS_H
#define PHYSICS_H
#include <Box2D/Box2D.h>
#include "mathematics.h"
#include "Actor.h"

#define DEF_FRICTION 1.0f
#define DEF_RESTITUTION 0.0f
#define DEF_DENSITY 0.01f

namespace Johnny
{
    class MainClass;
    
    class Physics2D
    {
        public:
            Physics2D(MainClass*,const Vector2f& gravity = Vector2f(0.0,-10.0),const Vector2f& worldSize = Vector2f(NORM_W,NORM_H));
            virtual ~Physics2D();

            void update();
            void quit();
            
            void setPixelPerMetre(float d) {m_pixelsPerMetre = d;}
            b2World* getWorld() {return m_world;}
            const Vector2f& getWorldSize() const {return m_worldSize;}
            
            b2Vec2 coordsPixelToWorld(const Vector2f&);
            Vector2f coordsWorldToPixel(const b2Vec2&);
            
            b2Vec2 vectorPixelToWorld(const Vector2f&);
            Vector2f vectorWorldToPixel(const b2Vec2&);

            float scalarPixelToWorld(float);
            float scalarWorldToPixel(float);
            
            static Vector2f toVector2f(const b2Vec2&);
            
            void setDebug(bool b){m_debug = b;}
            bool getDebug() {return m_debug;}
            
            // Creator methods
            
            b2Body* createBOX(const Vector2f&,float, float,float32 friction = DEF_FRICTION,float32 restitution = DEF_RESTITUTION,float32 density = DEF_DENSITY,b2BodyType type = b2_dynamicBody);
            b2Body* createBOX(const Vector2f&, float, float,b2BodyDef&,b2FixtureDef&);
            b2Body* createCIRCLE(const Vector2f&, float,float32 friction = DEF_FRICTION,float32 restitution = DEF_RESTITUTION,float32 density = DEF_DENSITY,b2BodyType type = b2_dynamicBody);
            b2Body* createCIRCLE(const Vector2f&, float,b2BodyDef&,b2FixtureDef&);
            b2Body* createCAPSULE(const Vector2f&, float, float,float32 friction = DEF_FRICTION,float32 restitution = DEF_RESTITUTION,float32 density = DEF_DENSITY,b2BodyType type = b2_dynamicBody);
            b2Body* createCAPSULE(const Vector2f&, float, float,b2BodyDef&,b2FixtureDef&);
            
        protected:

        private:
            b2World* m_world;
            MainClass* m_mainClass;
            Vector2f m_worldSize;
            float m_pixelsPerMetre = 10.0;
            bool m_debug = false;
    };
}


#endif // PHYSICS_H
