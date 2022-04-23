#ifndef JOYSTICKLISTENER_H
#define JOYSTICKLISTENER_H
#include "Events.h"
#include "JoystickListenerEnums.h"
#include <map>
#include <vector>

namespace Johnny {
class JoystickListener;

/*! \brief A Listener class which catches button input and axis movement of a
 * controller
 *
 */
class AxisButtonListener {
public:
  virtual ~AxisButtonListener() {}
  /*! \brief Gets called when a stick or a trigger gets moved
   * \param e A struct which holds information about the event
   */
  virtual void onAxisMotion(const ControllerAxisEvent &e) = 0;
  /*! \brief Gets called when a button is pressed
   * \param e A struct which holds information about the event
   */
  virtual void onButtonDown(const ControllerButtonEvent &e) = 0;
  /*! \brief Gets called when a button is released
   * \param e A struct which holds information about the event
   */
  virtual void onButtonUp(const ControllerButtonEvent &e) = 0;

  /*! \brief Sets the JoystickListener of the object
   * \param jl The JoystickListener to set
   */
  void setListener(JoystickListener *jl);

  /*! \brief Detaches the AxisButtonListener from the parent JoystickListener
   *
   */
  void detach();

protected:
  JoystickListener *m_listener =
      nullptr; //!< The JoystickListener of the object
};

/*! \brief A Listener class which listens to controllers connecting and
 * disconnecting
 *
 */
class ConnectionListener {
public:
  virtual ~ConnectionListener();

  /*! \brief Gets called when a controller connects
   * \param e A struct which holds infotmation about the event
   */
  virtual void onConnect(const ControllerDeviceEvent &e) = 0;
  /*! \brief Gets called when a controller disconnects
   * \param e A struct which holds information about the event
   */
  virtual void onDisconnect(const ControllerDeviceEvent &e) = 0;

  /*! \brief Sets the JoystickListener of the object
   * \param jl The JoystickListener to set
   */
  void setListener(JoystickListener *jl);

protected:
  JoystickListener *m_listener; //!< The JoystickListener of the object
};

class JoystickManager;

/*! \brief The main JoystickListener class which fetches all ControllerInputs
 *
 */
class JoystickListener {
public:
  JoystickListener();
  virtual ~JoystickListener();

  /*! \brief Sets the JoystickManager
   * \param jm The JoystickManager to set
   */
  void setManager(JoystickManager *jm);
  /*! \return The JoystickManager of the object
   *
   */
  JoystickManager *getManager() { return m_manager; }

  /*! \brief Gets called when a axsis or trigger of a controller is moved
   * \param e A struct which holds information about the event
   */
  void onAxisMotion(const ControllerAxisEvent &e);
  /*! \brief Gets called when a button of a controller is pressed
   * \param e A struct which holds information about the event
   */
  void onButtonDown(const ControllerButtonEvent &e);
  /*! \brief Gets called when a button of a controller is released
   * \param e A struct which holds information about the event
   */
  void onButtonUp(const ControllerButtonEvent &e);
  /*! \brief Gets called when a controller connects
   * \param e A struct which holds information about the event
   */
  void onConnect(const ControllerDeviceEvent &e);
  /*! \brief Gets called when a controller disconnects
   * \param e A struct which holds information about the event
   */
  void onDisconnect(const ControllerDeviceEvent &e);

  /*! \brief Attaches a AxisButtonListener to a specific controller id
   * \param abl The listener to attach
   * \param id The id to which the listener gets attached
   */
  void addListener(AxisButtonListener *abl, int id);
  /*! \brief Attaches a ConnectionListener
   * \param cl The listener to attach
   */
  void addListener(ConnectionListener *cl);
  /*! \brief Remove a AxisButtonListener from this listener
   * \param abl The listener to remove
   */
  void removeListener(AxisButtonListener *abl);
  /*! \brief Removes a ConnectionListener from this listener
   * \param cl The listener to remove
   */
  void removeListener(ConnectionListener *cl);

protected:
  JoystickManager *m_manager = nullptr; //!< The JoystickManager of the object
private:
  std::map<int, std::vector<AxisButtonListener *>>
      m_abLis; //!< The map which holds all AxisButtonListeners with the
               //!< specific ids
  std::vector<ConnectionListener *>
      m_conLis; //!< The vector which holds all ConnectionListeners
};

/*! \brief A Iterator which iterates over the m_abLis map
 *
 */
typedef std::map<int, std::vector<AxisButtonListener *>>::iterator AbIterator;
} // namespace Johnny

#endif // JOYSTICKLISTENER_H
