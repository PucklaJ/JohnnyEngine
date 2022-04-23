#pragma once
#include <GL/glew.h>

namespace Johnny {
class MainClass;

/*! \brief A enum which stores all names of the settings which can be adjusted
 *
 */
enum SettingName {
  VSYNC, //!< The name of the setting that specifys if vsync should be activated
  MSAA,  //!< The name of the setting that specifys if multisampling should be
         //!< applied
  MSAA_SAMPLES,       //!< The name of the setting that sepcifys the number of
                      //!< multisampling samples
  SPRITE2D_FILTERING, //!< The name of the setting that specifys which method to
                      //!< use for filtering for Sprite2Ds
  BACK_BUFFER_FILTERING //!< The name of the settings that specifys which method
                        //!< to use for filtering for the back buffer
};

/*! \brief A class which handles all settings
 *
 */
class Settings {
public:
  friend class MainClass;
  /*! \brief Sets a setting with type of integer
   *  \param s The name of the setting to adjust
   *  \param i The new value
   *  \return true if it worked and false otherwhise
   */
  static bool seti(SettingName s, int i);
  /*! \brief Sets a setting with type of bool
   *  \param s The name of the setting to adjust
   *  \param b The new value
   *  \return true if it worked and false otherwhise
   */
  static bool setb(SettingName s, bool b);

  /*! \brief Gets a setting with type of bool
   *  \param s The name of the setting to get the value from
   *  \return the value of the setting or false if the setting doesn't is a bool
   * or doesn't exist
   */
  static bool getb(SettingName s);
  /*! \brief Gets a setting width type of integer
   *  \param s The name of the setting to get the value from
   *  \return The value of the setting or 0 if the setting isn't a integer or
   * the setting doesn't exist
   */
  static int geti(SettingName s);

private:
  static bool m_vsync;                   //!< The value of VSYNC
  static bool m_msaa;                    //!< The value of MSAA
  static int m_msaa_samples;             //!< The value of MSAA_SAMPLES
  static GLenum m_sprite2D_filtering;    //!< The value of SPRITE2D_FILTERING
  static GLenum m_back_buffer_filtering; //!< The value of BACK_BUFFER_FILTERING

  static bool m_initialized; //!< true if the MainClass has been initialize
};
} // namespace Johnny