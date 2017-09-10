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
    
    /*! \brief A class which is used to animate 2D objects
     *
     */
    class Tween2D
    {
    public:
            friend class TweenableObject2D;
            /*! \brief Creates a new Tween2D
             *  \param time The time in which the action should be completed
             */
			Tween2D(float time);
            virtual ~Tween2D();

            /*! \brief Gets called every frame from the parent 2D object
             *  \param dt The time between the last and the current frame
             *  \return true if the Tween finished and should be deleted and false otherwhise
             */
            virtual bool update(float dt)=0;
            /*! \brief Gets called when a Tween2D gets attached to a 2D object
             * 
             */
            virtual void init();
            /*! \brief Sets the parent of the Tween2D which will be animated
             *  \param p The TweenableObject2D which should be animated
             */
            void setParent(TweenableObject2D* p);
            /*! \brief Sets if the Tween2D should pause
             *  \param b Wether it should pause or resume
             */
            void setPaused(bool b) {m_paused = b;}
            
            /*! \brief Adds time to the Tween2D if customTime is activated
             *  \param time The time to add
             */
            void addTime(float time);

            /*! \return Wether the Tween2D is currently paused
             *
             */
            const bool isPaused() const {return m_paused;}
            /*! \return The id of the Tween2D which is unique to every Tween2D
             *
             */
            const int getID() const {return m_id;}
            
            /*! \return The time which was passed through the constructor
             * 
             */
            float getTime() const {return m_time;}

        protected:
            /*! \brief The quit method which gets called when the Tween2D is done
             *
             */
            virtual void quit();

            float m_time = 0.0;                    //!< The time how much the Tween2D has advanced
            float m_passedTime = 0.0;              //!< The time which has passed
            TweenableObject2D* m_parent = nullptr; //!< The parent TweenableObject2D which will be animated
            bool m_paused = false;                 //!< Wether the Tween2D is currently paused
            int m_id = 0;                          //!< The id of the Tween2D which is unique to every Tween2D

        private:
            static std::vector<int> m_ids;         //!< An array which stores all ids of every Tween

    };

    /*! \brief A Tween which is used to animate the position
     *
     */
    class PositionTween2D : public Tween2D
    {
    public:
        /*! \brief Creates a new PositionTween2D
         *  \param dest The position to which it should animate
         *  \param time The time in which it should be 
         */
        PositionTween2D(const Vector2f& dest,float time);

        /*! \brief The intit method
         *
         *
         * It is overiding the method from Tween2D
         */
        void init() override;
        /*! \brief The update method
         *  \param dt The time that has passed from the last frame to this in sec
         *
         * It is overriding the mthod from Tween2D
         */
        bool update(float dt) override;

    private:
        Vector2f m_dstPos; //!< The position where the object should go
        Vector2f m_vel;    //!< The velocity in with wihch it travels
    };
    
    /*! \brief A Tween2D which is used for sprite animations
     *
     */
    class AnimationTween2D : public Tween2D
    {
    public:
    	/*! \brief Creates a new AnimationTween2D
    	 *  \param atlas The texture from it should get the animation frames
    	 *  \param x The amount of frames in the x-Axis
    	 *  \param y The amount of frames in the y-Axis
    	 *  \param time The time of one animation frame in sec
    	 *  \param loop Wether the animation should loop
    	 *  \param customTime Wether the time should manually get added
    	 */
        AnimationTween2D(Texture* atlas,int x,int y,float time,bool loop = true,bool customTime = false);
        /*! \brief Creates a new AnimationTween2D
         *  \param textures The animation frames which will be used for the animation
         *  \param time The time of one animation frame in sec
         *  \param loop Wether the animation should loop
         *  \param customTime Wether the time should will be manually added
         */
        AnimationTween2D(const std::vector<Texture*>& textures,float time,bool loop = true,bool customTime = false);
        /*! \brief Creates a new AnimationTween2D
         *  \param regions The TextureRegions which represent the region of each animation frame on the texture
         *  \param time The time of one animation frame in sec
         *  \param loop Wether the animation should loop
         *  \param customTime Wether the time should be added manually
         */
        AnimationTween2D(const std::vector<TextureRegion>& regions,float time,bool loop = true,bool customTime = false);
        ~AnimationTween2D();
        
        /*! \brief The init method
         *
         * 
         * It is overriding the method from Tween2D
         */
        void init() override;
        /*! \brief The update method
         *  \param dt The time that has passed from the last frame to this frame
         *
         * It is overriding the method from Tween2D
         */
        bool update(float dt) override;
    private:
        Sprite2D* m_sprParent;							 //!< The parent object as a Sprite2D
        std::vector<Texture*>* m_textures = nullptr;     //!< The vector which stores all animation frames if the corresponding constructor was used
        std::vector<TextureRegion>* m_regions = nullptr; //!< The vector which stores all TextureRegions of all animation frames if the corresponding construct was used
        Texture* m_atlas = nullptr;						 //!< The texture atlas from it should take the animation frames if the corresponding constructor was used
        int m_x = 0;									 //!< The amount of animation frames on the x-Axis
        int m_y = 0;									 //!< The amount of animation frames on the y-Axis
		TextureRegion m_srcRegion = {0,0,0,0};			 //!< The region which defines what to take from the atlas
        bool m_loop = true;								 //!< Wether the animation should loop
        bool m_customTime = false;						 //!< Wether the time should be added manually
    };
    
    /*! \brief A Tween2D which pulsates the object NOT WORKING
     *
     */
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
    
    /*! \brief A Tween2D which lets the object blink
     *
     */
    class BlinkTween2D : public Tween2D
    {
    public:
    	/*! \brief Creates a new BlinkTween2D
    	 *  \param time The time which it should stay visible/invisible
    	 */
        BlinkTween2D(float time);
        ~BlinkTween2D();
        
        /*! \brief The init method
         *
         *
         * It is overriding the method from Tween2D 
         */
        void init() override;
        /*! \brief The update method
         *  \param dt The time that has passed from the last frame to this
         *
         * It is overriding the mthod from Tween2D
         */
        bool update(float dt) override;
    protected:
    	/*! \brief The quit method
    	 *
    	 *
    	 * It is overriding the method from Tween2D
    	 */
        void quit() override;
    private:
        Sprite2D* m_sprParent = nullptr; //!< The parent as a Sprite2D
    };
    
    /*! \brief A Tween2D which rotates the object
     *
     */
    class RotationTween2D : public Tween2D
    {
    public:
    	/*! \brief Creates a new RotationTween2D
    	 *  \param speed The amount of degrees it should rotate per second
    	 */
        RotationTween2D(float speed);
        ~RotationTween2D();
        
        /*! \brief The init method
         *
         *
         * It is overriding the method from Tween2D
         */
        void init() override;
        /*! \brief The update method
         *  \param dt The time that has passed between the last frame and this
         *
         * It is overriding the method from Tween2D
         */
        bool update(float dt) override;
    private:
        float m_speed = 0.0f; //!< The speed at which it rotates per second
    };

    /*! \brief A class which adds tweenability to a object
     *
     */
	class TweenableObject2D : public TransformableObject2D
	{
	public:
		TweenableObject2D();
		~TweenableObject2D();

		/*! \return All Tween2Ds which are currently running
		 *
		 */
		std::vector<Tween2D*>& getTweens() { return m_tweens; }
		/*! \brief Gets a Tween2D with a id 
		 *  \param id The id of the Tween2D to get
		 *  \return The Tween2D with the given id or nullptr if no Tween2D with te id was found
		 */
		Tween2D* getTween(int id);

		/*! \brief Adds a Tween2D to animate the object
		 *  \param t The Tween2D which will be added
		 *  \return The id of the newly added Tween2D
		 */
		int addTween(Tween2D* t);

		/*! \brief Stops all Tween2Ds and deletes them
		 *
		 */
		void clearTweens();
		/*! \brief Pauses a Tween2D with the given id
		 *  \param id The id of the Tween2D to pause
		 */
		void pauseTween(int id);
		/*! \brief Resumes a Tween2D with the given id
		 *  \param id The id of the Tween2D to resume
		 */
		void resumeTween(int id);
		/*! \brief Stops a Tween2D with the given id
		 *  \param id The id of the Tween2D to stop
		 */
		void stopTween(int id);
		/*! \brief Checks wether a Tween2D with the given id is running
		 *  \param id The id of the Tween2D to check
		 *  \return true if a Tween2D with the id was found nad false otherwhise
		 */
        bool isRunning(int id);
	protected:
		/*! \brief Updates all currently added Tween2Ds
		 *  \param dt The time that has passed between the last frame and this
		 */
		void updateTweens(float dt);
	private:
		std::vector<Tween2D*> m_tweens; //!< The vector which stores all Tween2Dsof the object
	};
}


#endif // TWEEN_H
