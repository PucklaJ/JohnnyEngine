#ifndef JOYSTCKMANAGER_H
#define JOYSTCKMANAGER_H
#include "Events.h"
#include <vector>

namespace Johnny {
class JoystickListener;

/*! \brief The class which manages all controller specific things
 *
 */
class JoystickManager {
public:
  JoystickManager();
  virtual ~JoystickManager();

  /*! \brief Polls the controller events
   * \param e The event from which to poll
   */
  void pollEvents(const Event &e);
  /*! \brief Updates the JoystickManager
   *
   */
  void update();

  /*! \brief Sets the JoystickListener
   *  \param jl The JoystickListener to set
   */
  void setListener(JoystickListener *jl);
  /*! \brief Adds a controller to the vector
   * \param gc The controller to add
   */
  void addController(void *gc);
  /*! \brief Removes a controller from the vector
   * \param gc The controller to remove
   */
  void removeController(void *gc);
  /*! \brief Removes a controller with an index from the vector
   * \param index The index of te controller
   */
  void removeController(int index);

  /*! \return A vector with all SDL_GameController handles of the connected
   * controllers
   *
   */
  std::vector<void *> &getControllers() { return m_controllers; }

  /*! \return The currently attached JoystickListener
   *
   */
  JoystickListener *getListener() { return m_listener; }

private:
  JoystickListener *m_listener =
      nullptr;                       //!< The JoystickListener of the object
  std::vector<void *> m_controllers; //!< The vector which holds the controllers
};
} // namespace Johnny

#endif // JOYSTCKMANAGER_H
