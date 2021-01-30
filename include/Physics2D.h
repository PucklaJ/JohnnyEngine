#ifndef PHYSICS_H
#define PHYSICS_H
#include <box2d/box2d.h>
#include "mathematics.h"
#include "Actor.h"

#define DEF_FRICTION 1.0f
#define DEF_RESTITUTION 0.0f
#define DEF_DENSITY 0.01f

namespace Johnny
{
    class MainClass;
    class ContactListener;
    
    /*! \brief A class which handles 2D physics
     *
     */
    class Physics2D
    {
        public:
            /*! \brief Creates a new instance of Physics2D
             *  \param m The MainClass to which the object belongs
             *  \param gravity The gravity of the physics world
             *  \param worldSize The size of the physics world
             */
            Physics2D(MainClass* m,const Vector2f& gravity = Vector2f(0.0,-10.0),const Vector2f& worldSize = Vector2f(NORM_W,NORM_H));
            virtual ~Physics2D();

            /*! \brief Updates the physics world
             *
             */
            void update();
            /*! \brief Removes all bodies from the world
             *
             */
            void quit();
            
            /*! \brief Set the pixel per metre value which defines how big object in the world is per metre
             *
             */
            void setPixelPerMetre(float d) {m_pixelsPerMetre = d;}
            /*! \return The b2World which includes all physics objects
             *
             */
            b2World* getWorld() {return m_world;}
            /*! \return The size of the physics world
             *
             */
            const Vector2f& getWorldSize() const {return m_worldSize;}
            
            /*! \brief Converts a coordinate from pixel coordinates to Box2D coordinates 
             *  \param v The coordinate to convert
             *  \return A b2Vec2 which represents the coresponding Box2D world position
             */
            b2Vec2 coordsPixelToWorld(const Vector2f& v);
            /*! \brief Converts Box2D coordinates to pixel coordinates
             *  \param v The coordinate to convert
             *  \return The coresponding pixel coordinate
             */
            Vector2f coordsWorldToPixel(const b2Vec2& v);
            
            /*! \brief Converts a vector of the pixel coordinates to a vector of the Box2D coordinates
             *  \param v The vector to convert
             *  \return The coresponding Box2D vector
             */
            b2Vec2 vectorPixelToWorld(const Vector2f& v);
            /*! \brief Converts a vector of the Box2D coordinates to a vector of the pixel coordinates
             *  \param v The vector to convert
             *  \return The coresponding pixel coordinate vector
             */
            Vector2f vectorWorldToPixel(const b2Vec2& v);

            /*! \brief Converts a scalar of the pixel coordinates to a scalar of the Box2D coordinates
             *  \param s The scalar to convert
             *  \return The coresponding scalar of the Box2D coordinates
             */
            float scalarPixelToWorld(float s);
            /*! \brief Converts a scalar of the Box2D coordinates the a scalar of the pixel coordinates
             *  \param s The scalar to convert
             *  \return The coresponding scalar of the pixel coordinates
             */
            float scalarWorldToPixel(float s);
            
            /*! \brief Directly converts a Box2D vector to a Vector2f
             *  \param v The vector to convert
             *  \return The Vector2f with the same x and y values
             */
            static Vector2f toVector2f(const b2Vec2& v);
            
            /*! \brief Set if it should draw debug graphics
             *  \param b Defines wether to draw debug graphics
             */
            void setDebug(bool b){m_debug = b;}
            /*! \return true if it draws debug graphics and false if not
             *
             */
            bool getDebug() {return m_debug;}
            
            // Creator methods
            /*! \brief Creates a body as a box
             *  \param positon The positon of the box in pixel coordinates
             *  \param width The width of the box
             *  \param height The height of the box
             *  \param friction The friction of the body
             *  \param restitution The restitution of the body
             *  \param density The density of the body
             *  \param type The type of the body
             *  \return The newly created body 
             */
            b2Body* createBOX(const Vector2f& position,float width, float height,float friction = DEF_FRICTION,float restitution = DEF_RESTITUTION,float density = DEF_DENSITY,b2BodyType type = b2_dynamicBody);
            /*! \brief Creates a body as a box
             *  \param positon The positon of the box in pixel coordinates
             *  \param width The width of the box
             *  \param height The height of the box
             *  \param bdef The b2BodyDef of the body
             *  \param fdef The b2FixtureDef of the body
             *  \return The newly created body 
             */
            b2Body* createBOX(const Vector2f& position, float width, float height,b2BodyDef& bdef,b2FixtureDef& fdef);
            /*! \brief Creates a body as a circle
             *  \param positon The positon of the circle in pixel coordinates
             *  \param radius The radius of the circle
             *  \param friction The friction of the body
             *  \param restitution The restitution of the body
             *  \param density The density of the body
             *  \param type The type of the body
             *  \return The newly created body 
             */
            b2Body* createCIRCLE(const Vector2f& position, float radius,float friction = DEF_FRICTION,float restitution = DEF_RESTITUTION,float density = DEF_DENSITY,b2BodyType type = b2_dynamicBody);
            /*! \brief Creates a body as a circle
             *  \param positon The positon of the circle in pixel coordinates
             *  \param radius The radius of the circle
             *  \param bdef The b2BodyDef of the body
             *  \param fdef The b2FixtureDef of the body
             *  \return The newly created body 
             */
            b2Body* createCIRCLE(const Vector2f& position, float radius,b2BodyDef& bdef,b2FixtureDef& fdef);
            /*! \brief Creates a body as a capsule
             *  \param positon The positon of the capsule in pixel coordinates
             *  \param width The width of the capsule
             *  \param height The height of the capsule
             *  \param fixture The fixture of the body
             *  \param restitution The restitution of the body
             *  \param density The density of the body
             *  \return The newly created body 
             */
            b2Body* createCAPSULE(const Vector2f& position, float width, float height,float friction = DEF_FRICTION,float restitution = DEF_RESTITUTION,float density = DEF_DENSITY,b2BodyType type = b2_dynamicBody);
            /*! \brief Creates a body as a capsule
             *  \param positon The positon of the capsule in pixel coordinates
             *  \param width The width of the capsule
             *  \param height The height of the capsule
             *  \param bdef The b2BodyDef of the body
             *  \param fdef The b2FixtureDef of the body
             *  \return The newly created body 
             */
            b2Body* createCAPSULE(const Vector2f& position, float width, float height,b2BodyDef&,b2FixtureDef&);

        private:
            b2World* m_world;                             //!< The b2World which includes all bodies
            MainClass* m_mainClass;                       //!< The MainClass to which the object belongs
            Vector2f m_worldSize;                         //!< The size of the physics world
            float m_pixelsPerMetre = 10.0;                //!< The value which defines the size of a body in the physics world
            bool m_debug = false;                         //!< Defines if it should draw debug graphics
            ContactListener* m_contactListener = nullptr; //!< The contact listener which listens to all collisions
    };
}


#endif // PHYSICS_H
