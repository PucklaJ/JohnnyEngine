#ifndef ACTOR_H
#define ACTOR_H
#include <vector>

#define NORM_W 1280.0
#define NORM_H 720.0
#define NATIVE_W (m_mainClass->getNativeRes().x)
#define NATIVE_H (m_mainClass->getNativeRes().y)

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif


/*! \brief The main namespace
 *         Here is every element of the engine
 *
 */
namespace Johnny
{
    class MainClass;
    class Shader;
    class RenderManager;

    /*! \brief This is the base class for everything
     *         Every object is derived from this class
     *  
     */
    class Actor
    {
    public:
        friend class MainClass;
        friend class RenderManager;
    
		static const std::vector<Actor*> getAllActors() { return m_allActors; }

            Actor(const char* name = "Actor");
            virtual ~Actor();

            /*! \brief Gets called right after being added to its parent
             * 
             *
             * If the function returns false the application closes 
             */
            virtual bool init();
            /*! \brief Gets called every frame before rendering
             *
             *
             * If the function returns false the application closes 
             */
            virtual bool update()=0;
            /*! \brief Is the same as update, but for internal use
             *
             *
             * If the function returns false the application closes 
             */
            virtual bool m_update();
            /*! \brief Gets called after every update method and normally renders the object
             *
             *
             * If the function returns false the application closes 
             */
            virtual bool render();
            /*! \brief Gets called when the object is removed from its parent
             *
             */ 
            virtual void quit();
            /*! \brief Is the same as quit, but for internal use
             *
             */ 
            virtual void m_quit(); 

            /*! \brief Adds an actor as a child
             *  \param a The Actor which should be added
             *  \param instantAdd if true The child will instantly within this function call added, otherwhise it will be added after the frame
             *  \return true if the iniitialisation worked and false if not
             */
            bool addChild(Actor* a,bool instantAdd = true);
            /*! \brief Removes an actor from the children
             *  \param a The Actor which should be removed
             *  \param del Defines wether the Actor should be deleted when removing from its parent
             *  \param instant if true The child will instantly within this function call removed, otherwhise it will be added after the frame
             */ 
            void removeChild(Actor* a,bool del = true,bool instant = false);

            /*! \brief Sets the parent (for internal use only)
             *  \param a The Actor to set as parent
             */
            void setParent(Actor* a);
            /*! \brief Sets the MainClass (for internal use only)
             *  \param m The MainClass to set
             */
            void setMainClass(MainClass* m);
            /*! \brief Defines wether the position and orientation should change by moving the camera
             *  \param b The corresponding bol value
             */ 
            void setAffectedByCamera(const bool);
            /*! \brief Defines wether the ocject is visible
             *  \param b The orresponding bool value
             */ 
            void setVisible(const bool b);
            /*! \brief Defines wether the object casts shadows from a 3D Light
             *  \param b The corresponding bool value
             */ 
			void setCastsShadows(bool b) { m_castsShadows3D = b; }
            /*! \brief Sets the name (Is only used for debugging)
             *  \param name The name to set
             */
            void setName(const char* name){m_name = name;}
            /*! \brief Sets the shader with which the object is getting rendered
             *  \param s The Shader to set
             *  \param changeInRenderManager if true The Actor will be moved the other Shader inside the RenderManager
             */ 
			void setShader(Shader* s,bool changeInRenderManager = true); 


            MainClass* getMainClass();
            Actor* getParent(){return m_parent;}
            std::vector<Actor*>& getChildren() {return m_children;}
            bool isAffectedByCamera() const {return m_isAffectedByCamera;}
            const char* getName() const {return m_name;}
            const bool isVisible() const {return m_visible;}
			bool castsShadows() const { return m_castsShadows3D; }
            const int getID() const {return m_id;}
			Shader* getShader() { return m_shader; }

            /*! \brief Detect if a Actor is a child of the object
             * \param Actor* The Actor to query
             * \return true if the Actor is a child and false if not
             */
            bool isChild(Actor*);

            /*! \brief Does all quitting actions (For internal use only)
             *
             */
            void m_all_quit();
            /*! \brief Does all updatting actions (For internal use only)
             *
             */
            bool m_all_update();
            /*! \brief Does all rendering actions (For internal use only)
             *
             */
			bool m_render_render();
            
            /*! \brief Detect wether the object is on Screen
             * \return true if the object is on screen and false if not
             *
             * This method is not used and always returns true
             */
            virtual bool isOnScreen();

            /*! \brief Gets all children and children of them which cast shadows
             * \return a vector of Actor* with all children which match this
             */
			std::vector<Actor*> getChildrenWithCastsShadow();
    protected:
            

            MainClass* m_mainClass = nullptr; //!< The MainClass to which the object or its parent is attached to
            bool m_isAffectedByCamera = true; //!< Defines if the object should be transformed depinding on the camera
            bool m_visible = true;            //!< Defines wether the object is visible
			bool m_castsShadows3D = true;     //!< Defines wether the object casts shadows from a 3D light
			Shader* m_shader = nullptr;       //!< The shader whith which the object is rendered

            const char* m_name = "";          //!< The name of the object

    private:
            static std::vector<Actor*> m_allActors; //!< All actors which are currently not deleted
            
            /*! \brief Loops through all children (and the children of them) and
             *        sets the shader to RenderManager::DEFAULT_SHADER if the shader is nullptr
             *
             */
            void setAllChildrenWithNullShaderToDefaultShader();

            /*! \brief Removes all children which are currently in the ToRemove vectors
             *
             */
            void removeChildrenAfterLoops();
            /*! \brief Adds all Actors which are currently in the ToAdd vectors
             *
             */
            bool addChildrenBeforeLoops();

            std::vector<int> m_idsToRemove;       //!< Stores all ids of the actors which are removed with instant = false
            std::vector<bool> m_ifDeleteToRemove; //!< Stores all values of del of the actors which are removed with instant = false
            std::vector<Actor*> m_childrenToAdd;  //!< Stores all Actors which are added with instantAdd = false
            static std::vector<int> m_ids;        //!< Stores all ids of every Actor which isn't deleted
            int m_id;                             //!< The ID of the object (unique to every actor which isn't deleted)

            Actor* m_parent;                      //!< The parent of the object
            std::vector<Actor*> m_children;       //!< The children of the object

            bool m_initialised = false;           //!< Stores wether the init method is called
    };
}


#endif // ACTOR_H
