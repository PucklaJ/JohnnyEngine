#include "../include/Physics2D.h"
#include "../include/MainClass.h"

namespace Johnny
{
	Physics2D::Physics2D(MainClass* mainClass,const Vector2f& gravity,const Vector2f& worldSize)
    {
        m_world = new b2World(b2Vec2(gravity.x,gravity.y));
        m_mainClass = mainClass;
        m_worldSize = worldSize;
    }

	Physics2D::~Physics2D()
    {

    }

    void Physics2D::update()
    {
        m_world->Step(m_mainClass->getTimer()->getDeltaTimeInSeconds(),6,2);
    }

    void Physics2D::quit()
    {
        delete m_world;
    }
    
    b2Vec2 Physics2D::coordsPixelToWorld(const Vector2f& pos)
    {
        b2Vec2 worldPos(pos.x,pos.y);
        
        worldPos.x -= m_worldSize.x/2.0f;
        worldPos.y -= m_worldSize.y/2.0f;
        
        worldPos.y *= -1.0f;
        
        worldPos.x /= m_pixelsPerMetre;
        worldPos.y /= m_pixelsPerMetre;
        
        return worldPos;
    }
    
    Vector2f Physics2D::coordsWorldToPixel(const b2Vec2& pos)
    {
        Vector2f pixelPos(pos.x,pos.y);
        
        pixelPos *= m_pixelsPerMetre;
        
        pixelPos.y = (pixelPos.y*-1.0f);
        
        pixelPos += m_worldSize / 2.0f;
        
        return pixelPos;
    }
    
    Vector2f Physics2D::toVector2f(const b2Vec2& vec)
    {
        return Vector2f(vec.x,vec.y);
    }
    
    float Physics2D::scalarPixelToWorld(float d)
    {
        return d / m_pixelsPerMetre;
    }
    
    float Physics2D::scalarWorldToPixel(float d)
    {
        return d * m_pixelsPerMetre;
    }
    
    b2Body* Physics2D::createBOX(const Vector2f& pos,float w,float h,float32 friction,float32 restitution,float32 density,b2BodyType type)
    {
        b2BodyDef bdef;
        b2FixtureDef fdef;
        b2PolygonShape shape;
        b2Body* body;
        
        bdef.type = type;
        bdef.position = coordsPixelToWorld(pos);
        
        fdef.density = density;
        fdef.friction = friction;
        fdef.restitution = restitution;
        
        shape.SetAsBox(scalarPixelToWorld(w/2.0f),scalarPixelToWorld(h/2.0f));
        
        fdef.shape = &shape;
        
        body = m_world->CreateBody(&bdef);
        body->CreateFixture(&fdef);
        
        return body;
    }
    
    b2Body* Physics2D::createBOX(const Vector2f& pos,float w,float h,b2BodyDef& bdef,b2FixtureDef& fdef)
    {
        b2PolygonShape shape;
        b2Body* body;
        
        bdef.position = coordsPixelToWorld(pos);
        
        shape.SetAsBox(scalarPixelToWorld(w/2.0f),scalarPixelToWorld(h/2.0f));
        
        fdef.shape = &shape;
        
        body = m_world->CreateBody(&bdef);
        body->CreateFixture(&fdef);
        
        return body;
    }
    
    b2Body* Physics2D::createCIRCLE(const Vector2f& pos,float radius,float32 friction,float32 restitution,float32 density,b2BodyType type)
    {
        b2BodyDef bdef;
        b2FixtureDef fdef;
        b2CircleShape shape;
        b2Body* body;
        
        bdef.type = type;
        bdef.position = coordsPixelToWorld(pos);
        
        fdef.density = density;
        fdef.friction = friction;
        fdef.restitution = restitution;
        
        shape.m_radius = scalarPixelToWorld(radius);
        
        fdef.shape = &shape;
        
        body = m_world->CreateBody(&bdef);
        body->CreateFixture(&fdef);
        
        return body;
    }
    
    b2Body* Physics2D::createCIRCLE(const Vector2f& pos,float radius,b2BodyDef& bdef,b2FixtureDef& fdef)
    {
        b2CircleShape shape;
        b2Body* body;
        
        bdef.position = coordsPixelToWorld(pos);
        
        shape.m_radius = scalarPixelToWorld(radius);
        fdef.shape = &shape;
        
        body = m_world->CreateBody(&bdef);
        body->CreateFixture(&fdef);
        
        return body;
    }

    b2Body* Physics2D::createCAPSULE(const Vector2f& pos,float w,float h,float32 friction,float32 restitution,float32 density,b2BodyType type)
    {
    	b2BodyDef bdef;
    	b2FixtureDef fdef;
    	b2PolygonShape boxShape;
    	b2CircleShape cShape1,cShape2;
    	b2Body* body;

    	bdef.type = type;
    	bdef.position = coordsPixelToWorld(pos);

    	fdef.friction = friction;
    	fdef.restitution = restitution;
    	fdef.density = density;


    	boxShape.SetAsBox(w/2.0f,h/2.0f/2.0f);
    	cShape1.m_p = vectorPixelToWorld(Vector2f(0.0f,-h/2.0f));
    	cShape1.m_radius = scalarPixelToWorld(w/2.0f);
    	cShape2.m_p = vectorPixelToWorld(Vector2f(0.0f,h/2.0f));
    	cShape2.m_radius = scalarPixelToWorld(w/2.0f);


    	fdef.shape = &boxShape;
    	body = m_world->CreateBody(&bdef);
    	body->CreateFixture(&fdef);

    	fdef.shape = &cShape1;
    	body->CreateFixture(&fdef);

    	fdef.shape = &cShape2;
    	body->CreateFixture(&fdef);

    	return body;

    }
    b2Body* Physics2D::createCAPSULE(const Vector2f& pos,float w,float h,b2BodyDef& bdef,b2FixtureDef& fdef)
    {
    	b2PolygonShape boxShape;
    	b2CircleShape cShape1,cShape2;
    	b2Body* body;

    	bdef.position = coordsPixelToWorld(pos);

    	boxShape.SetAsBox(w/2.0f,h/2.0f/2.0f);
		cShape1.m_p = vectorPixelToWorld(Vector2f(0.0f,-h/4.0f));
		cShape1.m_radius = scalarPixelToWorld(w/2.0f);
		cShape2.m_p = vectorPixelToWorld(Vector2f(0.0f,h/4.0f));
		cShape2.m_radius = scalarPixelToWorld(w/2.0f);

		fdef.shape = &boxShape;
		body = m_world->CreateBody(&bdef);
		body->CreateFixture(&fdef);

		fdef.shape = &cShape1;
		body->CreateFixture(&fdef);

		fdef.shape = &cShape2;
		body->CreateFixture(&fdef);

		return body;
    }

    b2Vec2 Physics2D::vectorPixelToWorld(const Vector2f& v)
    {
    	return b2Vec2(v.x/m_pixelsPerMetre,-v.y/m_pixelsPerMetre);
    }

    Vector2f Physics2D::vectorWorldToPixel(const b2Vec2& v)
    {
    	return Vector2f(v.x*m_pixelsPerMetre,-v.y*m_pixelsPerMetre);
    }
}
