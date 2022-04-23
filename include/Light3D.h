#ifndef LIGHT_H
#define LIGHT_H

#include "Colors.h"
#include "Vector3.h"
#include "Vector4.h"
#include <GL/glew.h>
#include <map>
#include <string>
#include <vector>

namespace Johnny {
class Shader;
class ShadowMap3D;
class MainClass;

/*! \brief This class represents a light
 *        with just a position
 *
 */
class PointLight3D {
public:
  /*! \brief Loads a number of point lights to a shader
   *  \param s The Shader to which to load
   *  \param p An array of point lights to load
   *  \param size The number of elements in the array
   *  \param name The name of the uniform of the array in the shader
   *  \param shadowMapStartIndex The index at which the shadow maps start to
   * bind
   */
  static void load(Shader *s, PointLight3D *p, unsigned int size,
                   const std::string &name = "pointLights",
                   GLuint shadowMapStartIndex = 0);

  /*! \brief Creates a new PointLight3D
   *
   *
   * With arguments position=Vector3f(0.0f,0.0f,0.0f),
   * diffuse=Colorb(255,255,255), specular=Colorb(255,255,255), quadratic =
   * 0.001f, linear = 0.1f, constant = 0.5f
   */
  PointLight3D() : PointLight3D(Vector3f(0.0f, 0.0f, 0.0f)) {}
  /*! \brief Creates a new PointLight3D
   *  \param position The position of the new PointLight3D
   *  \param diffuse The diffuse color of the new PointLight3D
   *  \param specular The specular color of the new PointLight3D
   *  \param quadratic The quadratic value of the new PointLight3D which is used
   * for attentuation \param linear The linear value of the new PointLight3D
   * which is used for attentuation \param constant The constant value of the
   * new PointLight3D which is used for attentuation
   */
  PointLight3D(const Vector3f &position,
               const Colorb &diffuse = Colorb(255, 255, 255),
               const Colorb &specular = Colorb(255, 255, 255),
               GLfloat quadratic = 0.001f, GLfloat linear = 0.1f,
               GLfloat constant = 0.5f);
  ~PointLight3D();

  /*! \brief Loads this point light to shader as a uniform
   *  \param s The Shader to load to
   *  \param index The index of the array to load to (ignored when
   * isArray=false) \param isArray Defines if the uniform to load to is an array
   *  \param name The name of the uniform
   *  \param shadowMapIndex The index to which the shadow map should be bound
   */
  void load(Shader *s, GLuint index = 0, bool isArray = true,
            const std::string &name = "pointLights", GLuint shadowMapIndex = 0);
  /*! \brief Activates the ShadowMap3D of the point light
   *  \param width The width of the ShadowMap3D texture in pixels
   *  \param height The height of the ShadowMap3D texture in pixels
   */
  void setShadowMap(GLsizei width, GLsizei height);

  Vector3f position; //!< The position of the point light
  Colorb diffuse;    //!< The diffuse color of the point light
  Colorb specular;   //!< The specular color of the point light
  GLfloat quadratic; //!< The quadratic value of the point light which is used
                     //!< for attentuation
  GLfloat linear;    //!< The linear value of the point light which is used for
                     //!< attentuation
  GLfloat constant; //!< The constant value of the point light which is used for
                    //!< attentuation
  ShadowMap3D *shadowMap = nullptr; //!< The shadow map of the texture where all
                                    //!< shadow map rendering gets stored
  bool castsShadow =
      false; //!< Defines wether the point light should cast shadows (gets set
             //!< to true when calling setShadowMap)
};

/*! \brief A class which represents a light with just a direction
 *
 */
class DirectionalLight3D {
public:
  /*! \brief Loads a number of direction lights to the Shader as uniforms
   *  \param s The Shader to load to
   *  \param d An array of direction lights which should be loaded to the Shader
   *  \param size The size of the array
   *  \param name The name of the uniform in the Shader
   *  \param shadowMapStartIndex The index at which the ShadowMap3Ds should
   * start to get bound
   */
  static void load(Shader *s, DirectionalLight3D *d, unsigned int size,
                   const std::string &name = "directionalLights",
                   GLuint shadowMapStartIndex = 0);

  /*! \brief Creates a new DirectionLight3D
   *
   *
   * With arguments direction=Vector3f(0.0f,0.0f,-1.0f),
   * diffuse=Colorb(255,255,255), specular=Colorb(255,255,255)
   */
  DirectionalLight3D() : DirectionalLight3D(Vector3f(0.0f, 0.0f, -1.0f)) {}
  /*! \brief Creates a new DirectionLight3D
   *  \param direction The direction of the new DirectionLight3D
   *  \param diffuse The diffuse color of the new DirectionLight3D
   *  \param specular The specular color of the new DirectionalLight3D
   */
  DirectionalLight3D(const Vector3f &direction,
                     const Colorb &diffuse = Colorb(255, 255, 255),
                     const Colorb &specular = Colorb(255, 255, 255));
  ~DirectionalLight3D();

  /*! \brief Loads a this directional light to a Shader as a uniform
   *  \param s The Shader to load to
   *  \param index The index of the array element in the Shader (ingored when
   * isArray=false) \param name The name of the uniform \param shadowMapIndex
   * The index to which the ShadowMap3D should be bound
   */
  void load(Shader *s, GLuint index = 0, bool isArray = true,
            const std::string &name = "directionalLights",
            GLuint shadowMapIndex = 0);
  /*! \brief Activates the ShadowMap3D of the directional light
   *  \param width The width of the ShadowMap3D texture in pixels
   *  \param height The height of the ShadowMap3D texture in pixels
   */
  void setShadowMap(GLsizei width, GLsizei height);

  Vector3f direction; //!< The direction of the directional light
  Colorb diffuse;     //!< The diffuse color of the directional light
  Colorb specular;    //!< The specular color of the directional light
  ShadowMap3D *shadowMap =
      nullptr; //!< The shadow map of the directional light where all shadow map
               //!< rendering gets stored
  bool castsShadow =
      false; //!< Defines wether the directional light should cast shadows (gets
             //!< set to true when setShadowMap is called)
};

/*! \brief A class which represents a light with a position and a direction
 *
 */
class SpotLight3D {
public:
  /*! \brief Loads a number of spot lights to a Shader
   *  \param s The Shader to load to
   *  \param sl An array of spot lights which are loaded to the Shader
   *  \param size The number of elements of the array
   *  \param name The name of the uniform
   *  \param shadowMapStartIndex The index at which the ShadowMap3Ds should
   * start to get bound
   */
  static void load(Shader *s, SpotLight3D *sl, unsigned int size,
                   const std::string &name = "spotLights",
                   GLuint shadowMapStartIndex = 0);

  /*! \brief Creates a new SpotLight3D
   *
   *
   * With arguments position=Vector3f(0.0f,0.0f,0.0f),
   * direction=Vector3f(0.0f,0.0f,-1.0f), innerCutOff=30.0f, outerCutOff=50.0f,
   * diffuse=Colorb(255,255,255), specular=Colorb(255,255,255),
   * quadratic=0.001f, linear=0.1f, constant=0.5f
   */
  SpotLight3D()
      : SpotLight3D(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, -1.0f),
                    30.0f, 50.0f) {}
  /*! \brief Creates a newe SpotLight3D
   *  \param position The position of the new SpotLight3D
   *  \param direction The direction of the new SpotLight3D
   *  \param innerCutOff The innerCutOff of the new SpotLight3D which sets the
   * point where to start to lower the light strength (in degrees) \param
   * outerCutOff The outerCutOff of the new SpotLight3D which sets the point
   * where to completly turn off the light (in degrees) \param diffuse The
   * diffuse color of the new SpotLight3D \param specular The specular color of
   * the new SpotLight3D \param quadratic The quadratic value of the new
   * SpotLight3D which is used for attentuation \param linear The linear value
   * of the enew SpotLight3D which is used for attenttuation \param constant The
   * constant value of the new SpotLight3D which is use for attentuation
   */
  SpotLight3D(const Vector3f &position, const Vector3f &direction,
              GLfloat innerCutOff, GLfloat outerCutOff,
              const Colorb &diffuse = Colorb(255, 255, 255),
              const Colorb &specular = Colorb(255, 255, 255),
              GLfloat quadratic = 0.001f, GLfloat linear = 0.1f,
              GLfloat constant = 0.5f);
  ~SpotLight3D();

  /*! \brief Loads a spot light to the Shader as a uniform
   *  \param s The Shader to load to
   *  \param index The index of the array element (ignored when isArray=false)
   *  \param isArray Defines wether the uniform is an array
   *  \param name The name of the uniform
   *  \param shadowMapIndex The index to which the ShadowMap3D should be bound
   */
  void load(Shader *s, GLuint index = 0, bool isArray = true,
            const std::string &name = "spotLights", GLuint shadowMapIndex = 0);
  /*! \brief Activates the ShadowMap3D
   *  \param width The width of the ShadowMap3D texture in pixels
   *  \param height The height of the ShadowMap3D texture in pixels
   */
  void setShadowMap(GLsizei width, GLsizei height);

  Vector3f position;   //!< The position of the spot light
  Vector3f direction;  //!< The direction of the spot light
  Colorb diffuse;      //!< The diffuse color of the spot light
  Colorb specular;     //!< The specular color of the spot light
  GLfloat innerCutOff; //!< The innerCutOff of the spot light which sets the
                       //!< point where to lower the light strength (in degrees)
  GLfloat
      outerCutOff;   //!< The outerCutOff of the spot light which sets the point
                     //!< where completely turn off the light (in degrees)
  GLfloat quadratic; //!< The quadratic value of the spot light which is used
                     //!< for attentuation
  GLfloat linear;    //!< The linear value of the spot light which is used for
                     //!< attentuation
  GLfloat constant;  //!< The contants value of the spot light which is used for
                     //!< attentuation
  ShadowMap3D *shadowMap = nullptr; //!< The shadow map of the spot light where
                                    //!< all shadow map rendering gets stored
  bool castsShadow =
      false; //!< Defines wether the spot light should cast shadows (gets set to
             //!< true when setShadowMap is called)
};

/*! \brief The class for handling all 3D lighting specific things
 *
 */
class Lighting3D {
public:
  static Colorb ambientLight; //!< The ambient light of the scene

  Lighting3D();
  ~Lighting3D();

  /*! \brief Loads all lights attached to this object to a Shader as uniforms
   *  \param s The Shader to load to
   *  \param shadowMapStartIndex The index where to ShadowMap3Ds start to get
   * bound \param spotLightsName The name of the uniform where to store the
   * SpotLight3Ds \param directionalLightsName The name of the uniform where to
   * store the DirectionalLight3Ds \param pointLightsName The name pf the
   * uniform where to store the PointLight3Ds
   */
  void load(Shader *s, GLuint shadowMapStartIndex = 0,
            const std::string &spotLightsName = "spotLights",
            const std::string &directionalLightsName = "directionalLights",
            const std::string &pointLightsName = "pointLights");
  /*! \brief Renders all ShadowMap3Ds of all lights with castsShadow=true
   *  \param m The MainClass from which to pick the objects
   *  \param s The Shader with which the ShadowMap3Ds get generated
   */
  void renderShadowMaps(MainClass *m, Shader *s);

  /*! \brief Adds a SpotLight3D to the object
   *  \param s The SpotLight3D to add
   */
  void addLight(SpotLight3D *s);
  /*! \brief Adds a DirectionalLight3D to the object
   *  \param d The DirectionalLight3D to add
   */
  void addLight(DirectionalLight3D *d);
  /*! \brief Adds a PointLight3D to the object
   *  \param p The PointLight3D to add
   */
  void addLight(PointLight3D *p);

  /*! \brief Converts the amounts of lights to a map which is used to change the
   * defines in the Shader \param numSpotLights The name of the makro to set the
   * number of SpotLight3Ds \param numDirectionalLights The name of the makro to
   * set the number of DirectionalLight3Ds \param numPointLights The name of the
   * makro to set the number of PointLight3Ds
   */
  std::map<std::string, std::string> getDefineChanges(
      const std::string &numSpotLights = "NUM_SPOT_LIGHTS",
      const std::string &numDirectionalLights = "NUM_DIRECTIONAL_LIGHTS",
      const std::string &numPointLights = "NUM_POINT_LIGHTS") const;

  /*! \return All SpotLight3Ds of the object
   *
   */
  const std::vector<SpotLight3D *> &getSpotLights() const {
    return m_spotLights;
  }
  /*! \return All DirectionalLight3Ds of the object
   *
   */
  const std::vector<DirectionalLight3D *> &getDirectionalLights() const {
    return m_directionalLights;
  }
  /*! \return All PointLight3Ds of the object
   *
   */
  const std::vector<PointLight3D *> &getPointLights() const {
    return m_pointLights;
  }

private:
  std::vector<SpotLight3D *>
      m_spotLights; //!< The vector where all SpotLight3Ds of the object are
                    //!< stored
  std::vector<DirectionalLight3D *>
      m_directionalLights; //!< The vector where all DirectionalLight3Ds of the
                           //!< object are stored
  std::vector<PointLight3D *>
      m_pointLights; //!< The vector where all PointLight3Ds of the object are
                     //!< stored
};
} // namespace Johnny

#endif
