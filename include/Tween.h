#ifndef TWEEN_H
#define TWEEN_H
#include "mathematics.h"
#include <vector>
#include "Transform2D.h"
#include "Geometry.h"

namespace Johnny
{
    class Sprite2D;
    class Texture;
	class TweenableObject2D;
    
    class Tween2D
    {
        public:
			Tween2D(float);
            virtual ~Tween2D();

            virtual bool update(float)=0;
            virtual void init();
            void setParent(TweenableObject2D*);
            void setPaused(bool b) {m_paused = b;}
            
            void addTime(float);

            const bool isPaused() const {return m_paused;}
            const int getID() const {return m_id;}

        protected:
            void quit();

            float m_time = 0.0;
            float m_passedTime = 0.0;
            TweenableObject2D* m_parent = nullptr;
            bool m_paused = false;
            int m_id = 0;

        private:
            static std::vector<int> m_ids;

    };

    class PositionTween2D : public Tween2D
    {
    public:
        PositionTween2D(const Vector2f&,float);

        void init() override;
        bool update(float) override;

    private:
        Vector2f m_dstPos;
        Vector2f m_vel;
    };
    
    class AnimationTween2D : public Tween2D
    {
    public:
        AnimationTween2D(Texture* atlas,int x,int y,float time,bool loop = true,bool customTime = false);
        AnimationTween2D(const std::vector<Texture*>&,float time,bool loop = true,bool customTime = false);
        AnimationTween2D(const std::vector<TextureRegion>&,float time,bool loop = true,bool customTime = false);
        ~AnimationTween2D();
        
        void init() override;
        bool update(float) override;
    private:
        Sprite2D* m_sprParent;
        std::vector<Texture*>* m_textures = nullptr;
        std::vector<TextureRegion>* m_regions = nullptr;
        Texture* m_atlas = nullptr;
        int m_x = 0;
        int m_y = 0;
		TextureRegion m_srcRegion = {0,0,0,0};
        bool m_loop = true;
        bool m_customTime = false;
    };
    
    class PulsateTween2D : public Tween2D
    {
    public:
        PulsateTween2D(float,float speed = 6.0f,bool loop = true);
        
        void init() override;
        bool update(float) override;
    private:
        bool m_loop = true;
        float m_length = 0.0f;
        float m_speed = 6.0f;
		Vector2f m_startScale;
		Vector2f m_startPos;
    };

	class TweenableObject2D : public TransformableObject2D
	{
	public:
		TweenableObject2D();
		~TweenableObject2D();

		std::vector<Tween2D*>& getTweens() { return m_tweens; }
		Tween2D* getTween(int);

		void clearTweens();
		void pauseTween(int);
		void resumeTween(int);
		void stopTween(int);
	protected:
		void updateTweens(float);
	private:
		std::vector<Tween2D*> m_tweens;
	};
}


#endif // TWEEN_H
