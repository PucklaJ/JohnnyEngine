#include "../include/TiledMap.h"
#include "../include/FrameBuffer.h"
#include "../include/LogManager.h"
#include "../include/MainClass.h"
#include "../include/RenderTexture.h"
#include "../include/ResourceManager.h"
#include "../include/Settings.h"
#include "../include/Shader.h"
#include "../include/Texture.h"
#include "../include/Timer.h"
#include "../include/mathematics.h"
#include "../include/operators.h"
#include <GL/glew.h>
#include <box2d/box2d.h>
#include <iostream>
//#define DRAW_DEBUG

#define GETGID(obj)                                                            \
  (obj->GetGid() < 0 ? obj->GetGid() + INT_MAX : obj->GetGid())

namespace Johnny {
TiledMap::TiledMap(const std::string &file) : Sprite2D(nullptr), Tmx::Map() {
  m_affectedByCenter = true;
  setName("TiledMap");

  ParseFile(file);

  if (HasError()) {
    LogManager::error(std::string("TiledMap Error (") +
                      std::to_string(GetErrorCode()) + ") : " + GetErrorText());
    m_works = false;
  }
}

TiledMap::~TiledMap() {}

bool TiledMap::init() {
  Sprite2D::init();

  if (m_works) {
    LogManager::log("Loading Map...");

    if (GetOrientation() != Tmx::MapOrientation::TMX_MO_ORTHOGONAL) {
      LogManager::error(std::string("This Orientation is not supported (") +
                        std::to_string(GetOrientation()) + ")");
      return true;
    }

    loadTexture();

    loadTilesets();

    loadLayers();
  }

  if (m_texture) {
    m_srcRegion.x = 0;
    m_srcRegion.y = 0;
    m_srcRegion.width = m_texture->getWidth();
    m_srcRegion.height = m_texture->getHeight();

    setScale(1.0f, 1.0f);
    setDrawSize(Vector2f((GLfloat)m_srcRegion.w, (GLfloat)m_srcRegion.h));
    setSize((GLfloat)m_srcRegion.width, (GLfloat)m_srcRegion.height);
    setPosition(0.0f, 0.0f);
    // SDL_QueryTexture(m_texture->getTexture(),nullptr,nullptr,&m_srcRect.w,&m_srcRect.h);

    // m_size.set(m_texture->getWidth(),m_texture->getHeight());
  }

  m_clearTexture =
      Texture::BOX(Vector2i(GetTileWidth(), GetTileHeight()), m_background);
  m_clearTexture->setDrawMode(DrawModes::DIRECT);

  m_mainClass->getBackBuffer()->bind();
  glViewport(0, 0, (GLsizei)m_mainClass->getNativeRes().x,
             (GLsizei)m_mainClass->getNativeRes().y);
  TransformableObject2D::setViewportSize(m_mainClass->getNativeRes());

  LogManager::log("Finished Loading Map!");

  return true;
}

Uint8 hexCharToInt(char c) {
  switch (c) {
  case '0':
    return 0;
  case '1':
    return 1;
  case '2':
    return 2;
  case '3':
    return 3;
  case '4':
    return 4;
  case '5':
    return 5;
  case '6':
    return 6;
  case '7':
    return 7;
  case '8':
    return 8;
  case '9':
    return 9;
  case 'A':
  case 'a':
    return 10;
  case 'B':
  case 'b':
    return 11;
  case 'C':
  case 'c':
    return 12;
  case 'D':
  case 'd':
    return 13;
  case 'E':
  case 'e':
    return 14;
  case 'F':
  case 'f':
    return 15;
  default:
    return -1;
  }
}

Colorb TiledMap::colorStringToColor(const std::string &str) {
  Colorb col;

  if (str.length() == 0) {
    col.r = col.g = col.b = 128;
    col.a = 255;

    return col;
  }

  Uint8 num;

  for (unsigned int i = 1; i < 6; i += 2) {
    num = (hexCharToInt(str[i]) << 4) + hexCharToInt(str[i + 1]);

    switch (i) {
    case 1:
      col.r = num;
      break;
    case 3:
      col.g = num;
      break;
    case 5:
      col.b = num;
      break;
    default:
      break;
    }
  }

  return col;
}

void TiledMap::loadTexture() {
  m_background = colorStringToColor(GetBackgroundColor().ToString());
  // m_background.a = 255;

  m_mainTextureFrameBuffer = new FrameBuffer();

  m_texture = new Texture(
      nullptr, GetWidth() * GetTileWidth(), GetHeight() * GetTileHeight(),
      (GLenum)Settings::geti(SettingName::SPRITE2D_FILTERING));
  m_mainTextureFrameBuffer->addTexture(m_texture);
  if (!m_mainTextureFrameBuffer->checkStatus())
    LogManager::error("MainTextureFrameBuffer of TiledMap isn't completed!");

  m_mainTextureFrameBuffer->bind();
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  m_mainTextureFrameBuffer->unbind();
}

void TiledMap::loadTilesets() {
  LogManager::log("Loading Tilesets...");

  m_tilesX = new int[GetNumTilesets()];

  for (int i = 0; i < GetNumTilesets(); i++) {
    const Tmx::Tileset *tileSet = GetTileset(i);
    std::string imageFile = GetFilepath() + tileSet->GetImage()->GetSource();
    Texture *tex = m_mainClass->getResourceManager()->loadTexture(imageFile);
    if (!contains(m_tilesetTextures, tex))
      m_tilesetTextures.push_back(tex);

    FrameBuffer *fr = new FrameBuffer();
    fr->addTexture(tex);
    if (!fr->checkStatus())
      LogManager::error("FrameBuffer of Tileset \"" + imageFile +
                        "\" is not completed!");

    m_frameBuffersOfTileSets.insert(
        std::pair<Texture *, FrameBuffer *>(tex, fr));

    m_tilesX[i] = (tileSet->GetImage()->GetWidth() - tileSet->GetMargin() * 2 +
                   tileSet->GetSpacing()) /
                  (tileSet->GetTileWidth() + tileSet->GetSpacing());
  }
}

void TiledMap::addTexture() {
  RenderTexture *texture = new RenderTexture(
      GetWidth() * GetTileWidth(), GetHeight() * GetTileHeight(),
      (GLenum)Settings::geti(SettingName::SPRITE2D_FILTERING), GL_TEXTURE_2D);
  texture->target();
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  texture->untarget();
  m_renderTextures.push_back(texture);
}

void TiledMap::loadLayers() {
  LogManager::log("Loading Layers..");

  for (int i = 0; i < GetNumLayers(); i++) {
    addTexture();

    switch (GetLayer(i)->GetLayerType()) {
    case Tmx::LayerType::TMX_LAYERTYPE_TILE:
      loadTileLayer(static_cast<const Tmx::TileLayer *>(GetLayer(i)), i);
      break;
    case Tmx::LayerType::TMX_LAYERTYPE_OBJECTGROUP:
      loadObjectGroup(static_cast<const Tmx::ObjectGroup *>(GetLayer(i)));
      break;
    case Tmx::LayerType::TMX_LAYERTYPE_IMAGE_LAYER:
      loadImageLayer(static_cast<const Tmx::ImageLayer *>(GetLayer(i)));
      break;
    }
  }
}

void TiledMap::loadTileLayer(const Tmx::TileLayer *tileLayer, int Lindex) {
  if (!tileLayer->IsVisible())
    return;

  int index, tileID;
  std::string imageFile;
  Texture *texture;
  TextureRegion dst, src;

  /*std::cout << "-- TileLayer --" << std::endl;
  std::cout << "+ ZOrder: " << tileLayer->GetZOrder() << std::endl;
  std::cout << "+ Opacity: " << tileLayer->GetOpacity() << std::endl;
  std::cout << "+ X: " << tileLayer->GetX() << std::endl;
  std::cout << "+ Y: " << tileLayer->GetY() << std::endl;
  std::cout << "+ ParseOrder: " << tileLayer->GetParseOrder() << std::endl;*/

  m_renderTextures.back()->target();

  for (int y = 0; y < tileLayer->GetHeight(); y++) {
    for (int x = 0; x < tileLayer->GetWidth(); x++) {
      if (tileLayer->GetTileTilesetIndex(x, y) == -1)
        continue;

      index = tileLayer->GetTileTilesetIndex(x, y);
      tileID = tileLayer->GetTileId(x, y);

      const Tmx::Tileset *tileSet = GetTileset(index);
      imageFile = GetFilepath() + tileSet->GetImage()->GetSource();
      const Tmx::MapTile &tile = tileLayer->GetTile(x, y);

      texture = m_mainClass->getResourceManager()->loadTexture(imageFile);

      getSrcRegionForTileID(&src, m_tilesX[index], index, tileID);

      dst.x = x * GetTileWidth();
      dst.y = y * GetTileHeight();
      dst.w = tileSet->GetTileWidth();
      dst.h = tileSet->GetTileHeight();

      texture->setModColor(Colorf(1.0f, 1.0f, 1.0f, tileLayer->GetOpacity()));

      if (tile.flippedHorizontally || tile.flippedVertically ||
          tile.flippedDiagonally) {
        if (tile.flippedHorizontally) {
          texture->setFlip(Flip::HORIZONTALLY);
        } else if (tile.flippedVertically) {
          texture->setFlip(Flip::VERTICALLY);
        } else {
          texture->setFlip(Flip::DIAGONALLY);
        }
      }

      Texture::renderTexture2D(texture, &dst, &src);
      texture->setFlip(Flip::NONE);

      const Tmx::Tile *ttile = tileSet->GetTile(tileID);
      if (ttile && (ttile->GetNumObjects() > 0))
        loadCollisionObjects(ttile, x * GetTileWidth(), y * GetTileHeight());
    }
  }

  loadAnimations(tileLayer, Lindex);
}

void TiledMap::loadObjectGroup(const Tmx::ObjectGroup *objectGroup) {
  if (!objectGroup->IsVisible())
    return;

  TextureRegion dst, src;
  Texture *texture;

  /*std::cout << "-- ObjectGroup --" << std::endl;
  std::cout << "+ ParseOrder: " << objectGroup->GetParseOrder() << std::endl;
  std::cout << "+ Color: " << objectGroup->GetColor() << std::endl;
  std::cout << "+ X: " << objectGroup->GetX() << std::endl;
  std::cout << "+ Y: " << objectGroup->GetY() << std::endl;
  std::cout << "+ Opacity:" << objectGroup->GetOpacity() << std::endl;
  std::cout << "+ ZOrder: " << objectGroup->GetZOrder() << std::endl;*/

  m_renderTextures.back()->target();

  for (int j = 0; j < objectGroup->GetNumObjects(); j++) {
    const Tmx::Object *obj = objectGroup->GetObject(j);
    if (!obj->IsVisible())
      continue;

    /*std::cout << "-- Object --" << std::endl;
    std::cout << "+ Position: " << obj->GetX() << "; " << obj->GetY() <<
    std::endl; std::cout << "+ Rotation: " << obj->GetRot() << std::endl;
    std::cout << "+ Height: " << obj->GetHeight() << std::endl;
    std::cout << "+ Width: " << obj->GetWidth() << std::endl;
    std::cout << "+ Name: " << obj->GetName() << std::endl;
    std::cout << "+ Typ: " << obj->GetType() << std::endl;
    std::cout << "+ GID: " << obj->GetGid() << std::endl;*/
    if (obj->GetEllipse() && m_renderObjects) {
      // std::cout << "+ Ellipse" << std::endl;
      // const Tmx::Ellipse* ellipse = obj->GetEllipse();
      // Colorb color = colorStringToColor(objectGroup->GetColor().ToString());
      /*std::cout << "++ Center: " << ellipse->GetCenterX() << "; " <<
      ellipse->GetCenterY() << std::endl; std::cout << "++ Radius: " <<
      ellipse->GetRadiusX() << "; " << ellipse->GetRadiusY() << std::endl;*/

      // aaellipseRGBA(m_mainClass->getRenderer(),ellipse->GetCenterX(),ellipse->GetCenterY(),ellipse->GetRadiusX(),ellipse->GetRadiusY(),color.r,color.g,color.b,(Uint8)(objectGroup->GetOpacity()*255.0f));
      // filledEllipseRGBA(m_mainClass->getRenderer(),ellipse->GetCenterX(),ellipse->GetCenterY(),ellipse->GetRadiusX(),ellipse->GetRadiusY(),color.r,color.g,color.b,(Uint8)(objectGroup->GetOpacity()*255.0f/4.0f));

      continue;
    } else if (obj->GetPolygon() && m_renderObjects) {
      // std::cout << "+ Polygon" << std::endl;
      const Tmx::Polygon *polygon = obj->GetPolygon();
      // Colorb color = colorStringToColor(objectGroup->GetColor().ToString());
      // std::cout << "++ Points" << std::endl;

      Sint16 *vx = new Sint16[polygon->GetNumPoints()];
      Sint16 *vy = new Sint16[polygon->GetNumPoints()];

      for (int k = 0; k < polygon->GetNumPoints(); k++) {
        const Tmx::Point &point = polygon->GetPoint(k);
        // std::cout << "+++ " << k+1 << ". " << point.x << "; " << point.y <<
        // std::endl;
        vx[k] = (Sint16)((float)obj->GetX() + point.x);
        vy[k] = (Sint16)((float)obj->GetY() + point.y);

        // std::cout << "+++ vx: " << vx[k] << "; vy: " << vy[k] << std::endl;
      }

      delete[] vx;
      delete[] vy;

      for (int k = 0; k < polygon->GetNumPoints(); k++) {
        if (k != 0) {
          // aalineRGBA(m_mainClass->getRenderer(),vx[k-1],vy[k-1],vx[k],vy[k],color.r,color.g,color.b,(Uint8)(objectGroup->GetOpacity()*255.0f));
          if (k == polygon->GetNumPoints() - 1) {
            // aalineRGBA(m_mainClass->getRenderer(),vx[k],vy[k],vx[0],vy[0],color.r,color.g,color.b,(Uint8)(objectGroup->GetOpacity()*255.0f));
          }
        }
      }

      // aapolygonRGBA(m_mainClass->getRenderer(),vx,vy,polygon->GetNumPoints(),color.r,color.g,color.b,(Uint8)(objectGroup->GetOpacity()*255.0f));
      // filledPolygonRGBA(m_mainClass->getRenderer(),vx,vy,polygon->GetNumPoints(),color.r,color.g,color.b,(Uint8)(objectGroup->GetOpacity()*255.0f/4.0f));

      continue;
    } else if (obj->GetPolyline() && m_renderObjects) {
      // std::cout << "+ Polyline" << std::endl;
      // const Tmx::Polyline* polyline = obj->GetPolyline();
      // Colorb color = colorStringToColor(objectGroup->GetColor().ToString());
      // std::cout << "++ Points" << std::endl;
      // for(int k = 0;k<polyline->GetNumPoints();k++)
      //{
      //     if(k!=0)
      //     {
      // const Tmx::Point& point1 = polyline->GetPoint(k-1);
      // const Tmx::Point& point2 = polyline->GetPoint(k);
      // std::cout << "+++ " << k << ". " << point1.x << "; " << point1.y <<
      // std::endl;

      // aalineRGBA(m_mainClass->getRenderer(),point1.x+obj->GetX(),point1.y+obj->GetY(),point2.x+obj->GetX(),point2.y+obj->GetY(),color.r,color.g,color.b,(Uint8)(objectGroup->GetOpacity()*255.0f));
      //    }
      //}

      continue;
    }

    int GID = obj->GetGid() < 0 ? 282 : obj->GetGid();

    const Tmx::Tileset *gidTileSet = getTileset(GID);
    if (gidTileSet) {
      // std::cout << "+ Tile" << std::endl;

      getSrcRegionForTileGID(&src, GID);
      dst.x = obj->GetX();
      dst.y = obj->GetY() - obj->GetHeight();
      dst.w = obj->GetWidth();
      dst.h = obj->GetHeight();

      texture = m_mainClass->getResourceManager()->loadTexture(
          GetFilepath() + gidTileSet->GetImage()->GetSource());
      // texture->setAlphaMod((Uint8)(objectGroup->GetOpacity()*255.0f)); TODO
      // texture->renderCopy(m_mainClass->getRenderer(),&dst,&src);
      Texture::renderTexture2D(texture, &dst, &src);
      // texture->setAlphaMod(255);

      int tileID = getTileIDForTileGID(GID);
      const Tmx::Tile *ttile = gidTileSet->GetTile(tileID);
      if (ttile && ttile->GetNumObjects() > 0)
        loadCollisionObjects(ttile, obj->GetX(),
                             obj->GetY() - obj->GetHeight());

      continue;
    }

    if (!m_renderObjects)
      continue;

    // Render Rectangle

    // Colorb color = colorStringToColor(objectGroup->GetColor().ToString());

    // rectangleRGBA(m_mainClass->getRenderer(),obj->GetX(),obj->GetY(),obj->GetX()+obj->GetWidth(),obj->GetY()+obj->GetHeight(),color.r,color.g,color.b,(Uint8)(objectGroup->GetOpacity()*255.0f));
    // boxRGBA(m_mainClass->getRenderer(),obj->GetX(),obj->GetY(),obj->GetX()+obj->GetWidth(),obj->GetY()+obj->GetHeight(),color.r,color.g,color.b,(Uint8)(objectGroup->GetOpacity()*255.0f/4.0f));
  }

  glClearColor(m_background.r, m_background.g, m_background.b, m_background.a);
}

void TiledMap::loadImageLayer(const Tmx::ImageLayer *imageLayer) {
  m_renderTextures.back()->target();
  m_renderTextures.back()->untarget();
}

void TiledMap::loadCollisionObjects(const Tmx::Tile *tile, int x, int y) {
  // std::cout << "+++++++++++++ Collision Objects: " << tile->GetNumObjects()
  // << std::endl;

  if (!m_mainClass->getPhysics2D())
    LogManager::error("The Physics2D aren't activated! You need to add "
                      "PHYSICS2D to the InitFlags!");

  for (int i = 0; i < tile->GetNumObjects(); i++) {
    const Tmx::Object *obj = tile->GetObject(i);

    /*std::cout << "--------------- Object ---" << std::endl;
    std::cout << "+++++++++++++++ Position: " << obj->GetX() << "; " <<
    obj->GetY() << std::endl; std::cout << "+++++++++++++++ Rotation: " <<
    obj->GetRot() << std::endl; std::cout << "+++++++++++++++ Height: " <<
    obj->GetHeight() << std::endl; std::cout << "+++++++++++++++ Width: " <<
    obj->GetWidth() << std::endl; std::cout << "+++++++++++++++ Name: " <<
    obj->GetName() << std::endl; std::cout << "+++++++++++++++ Typ: " <<
    obj->GetType() << std::endl; std::cout << "+++++++++++++++ GID: " <<
    obj->GetGid() << std::endl; std::cout << "+++++++++++++++ Visible: " <<
    obj->IsVisible() << std::endl;*/

    if (obj->GetEllipse()) {
#ifdef DRAW_DEBUG
      // std::cout << "+++++++++++++++ Ellipse" << std::endl;
      const Tmx::Ellipse *ellipse = obj->GetEllipse();
      Colorb color = Colors::WHITE;
      /*std::cout << "++++++++++++++++ Center: " << ellipse->GetCenterX() << ";
      " << ellipse->GetCenterY() << std::endl; std::cout << "++++++++++++++++
      Radius: " << ellipse->GetRadiusX() << "; " << ellipse->GetRadiusY() <<
      std::endl;*/

      if (obj->IsVisible()) {
        /*aaellipseRGBA(m_mainClass->getRenderer(),
                      ellipse->GetCenterX()+x,
                      ellipse->GetCenterY()+y,
                      ellipse->GetRadiusX(),
                      ellipse->GetRadiusY(),
                      color.r,color.g,color.b,255);
        filledEllipseRGBA(m_mainClass->getRenderer(),
                          ellipse->GetCenterX()+x,
                          ellipse->GetCenterY()+y,
                          ellipse->GetRadiusX(),
                          ellipse->GetRadiusY(),
                          color.r,color.g,color.b,64);*/
      }
#endif

      loadCollisionEllipse(obj, x, y);

    } else if (obj->GetPolygon()) {
      // std::cout << "+++++++++++++++ Polygon" << std::endl;
#ifdef DRAW_DEBUG
      const Tmx::Polygon *polygon = obj->GetPolygon();
      Colorb color = Colors::WHITE;
      // std::cout << "++++++++++++++++ Points" << std::endl;

      Sint16 vx[polygon->GetNumPoints()];
      Sint16 vy[polygon->GetNumPoints()];
      for (int k = 0; k < polygon->GetNumPoints(); k++) {
        const Tmx::Point &point = polygon->GetPoint(k);
        // std::cout << "+++++++++++++++++ " << k+1 << ". " << point.x << "; "
        // << point.y << std::endl;
        vx[k] = obj->GetX() + point.x + x;
        vy[k] = obj->GetY() + point.y + y;

        // std::cout << "+++++++++++++++++ vx: " << vx[k] << "; vy: " << vy[k]
        // << std::endl;
      }
      if (obj->IsVisible()) {
        for (int k = 0; k < polygon->GetNumPoints(); k++) {
          if (k != 0) {
            // aalineRGBA(m_mainClass->getRenderer(),vx[k-1],vy[k-1],vx[k],vy[k],color.r,color.g,color.b,255);
            if (k == polygon->GetNumPoints() - 1) {
              // aalineRGBA(m_mainClass->getRenderer(),vx[k],vy[k],vx[0],vy[0],color.r,color.g,color.b,255);
            }
          }
        }

        // aapolygonRGBA(m_mainClass->getRenderer(),vx,vy,polygon->GetNumPoints(),color.r,color.g,color.b,(Uint8)(objectGroup->GetOpacity()*255.0f));
        /*filledPolygonRGBA(m_mainClass->getRenderer(),
                          vx,
                          vy,
                          polygon->GetNumPoints(),
                          color.r,color.g,color.b,64);*/
      }
#endif

      loadCollisionPolygon(obj, x, y);
    } else if (obj->GetPolyline()) {
#ifdef DRAW_DEBUG // std::cout << "+++++++++++++++ Polyline" << std::endl;
      const Tmx::Polyline *polyline = obj->GetPolyline();
      Colorb color = Colors::WHITE;
      // std::cout << "++++++++++++++++ Points" << std::endl;
      for (int k = 0; k < polyline->GetNumPoints(); k++) {
        if (k != 0) {
          const Tmx::Point &point1 = polyline->GetPoint(k - 1);
          const Tmx::Point &point2 = polyline->GetPoint(k);
          // std::cout << "+++++++++++++++++ " << k << ". " << point1.x << "; "
          // << point1.y << std::endl;

          /*if(obj->IsVisible())
              aalineRGBA(m_mainClass->getRenderer(),
                         point1.x+obj->GetX()+x,
                         point1.y+obj->GetY()+y,
                         point2.x+obj->GetX()+x,
                         point2.y+obj->GetY()+y,
                         color.r,color.g,color.b,255);*/
        }
      }
#endif
      loadCollisionPolyline(obj, x, y);
    } else {
#ifdef DRAW_DEBUG
      Colorb color = Colors::WHITE;

      // std::cout << "+++++++++++++++ Rectangle" << std::endl;

      if (obj->IsVisible()) {
        /*rectangleRGBA(m_mainClass->getRenderer(),
                      obj->GetX()+x,
                      obj->GetY()+y,
                      obj->GetX()+obj->GetWidth()+x,
                      obj->GetY()+obj->GetHeight()+y,
                      color.r,color.g,color.b,255);
        boxRGBA(m_mainClass->getRenderer(),
                obj->GetX()+x,
                obj->GetY()+y,
                obj->GetX()+obj->GetWidth()+x,
                obj->GetY()+obj->GetHeight()+y,
                color.r,color.g,color.b,64);*/
      }
#endif

      loadCollisionRectangle(obj, x, y);
    }
  }
}

void TiledMap::loadCollisionEllipse(const Tmx::Object *obj, int x, int y) {
  const Tmx::Ellipse *ellipse;
  b2Body *body;
  b2BodyDef bdef;
  b2FixtureDef fdef[3];
  b2CircleShape cshape[2];
  // b2PolygonShape pshape; TODO

  ellipse = obj->GetEllipse();

  const Tmx::PropertySet &props = obj->GetProperties();

  bdef.position = m_mainClass->getPhysics2D()->coordsPixelToWorld(
      Vector2f((GLfloat)(x + ellipse->GetCenterX() + obj->GetX()),
               (GLfloat)(y + ellipse->GetCenterY() + obj->GetY())));
  std::string type = props.GetStringProperty("Type", "static");
  bdef.type = (type == "static"
                   ? b2_staticBody
                   : (type == "dynamic" ? b2_dynamicBody : b2_kinematicBody));

  fdef[0].density = props.GetFloatProperty("Density", DEF_DENSITY);
  fdef[0].friction = props.GetFloatProperty("Friction", DEF_FRICTION);
  fdef[0].restitution = props.GetFloatProperty("Restitution", DEF_RESTITUTION);
  fdef[0].filter.categoryBits = props.GetIntProperty("CategoryBits", 1);
  fdef[0].filter.maskBits = props.GetIntProperty("MaskBits", ~0);
  fdef[0].isSensor = props.GetBoolProperty("isSensor", false);

  body = m_mainClass->getPhysics2D()->getWorld()->CreateBody(&bdef);

  if (ellipse->GetRadiusX() == ellipse->GetRadiusY()) {
    cshape[0].m_radius = m_mainClass->getPhysics2D()->scalarPixelToWorld(
        (float)ellipse->GetRadiusX());
    fdef[0].shape = &cshape[0];

    body->CreateFixture(&fdef[0]);

    m_bodies.push_back(body);
  }
}

void TiledMap::loadCollisionPolygon(const Tmx::Object *obj, int x, int y) {
  const Tmx::Polygon *polygon = obj->GetPolygon();

  if (polygon->GetNumPoints() < 3 ||
      polygon->GetNumPoints() > b2_maxPolygonVertices) {
    LogManager::error(std::string("Polygon (") + std::to_string(x) + "; " +
                      std::to_string(y) + ") has too much or too few vertices");
    return;
  }

  const Tmx::PropertySet &props = obj->GetProperties();

  b2Body *body;
  b2BodyDef bdef;
  b2FixtureDef fdef;
  b2PolygonShape shape;
  b2Vec2 *v;

  v = new b2Vec2[polygon->GetNumPoints()];

  Vector2f pixelPos((GLfloat)x + (GLfloat)GetTileWidth() / 2.0f,
                    (GLfloat)y + (GLfloat)GetTileHeight() / 2.0f);

  bdef.position = m_mainClass->getPhysics2D()->coordsPixelToWorld(pixelPos);
  std::string type = props.GetStringProperty("Type", "static");
  bdef.type = (type == "static"
                   ? b2_staticBody
                   : (type == "dynamic" ? b2_dynamicBody : b2_kinematicBody));

  fdef.density = props.GetFloatProperty("Density", DEF_DENSITY);
  fdef.friction = props.GetFloatProperty("Friction", DEF_FRICTION);
  fdef.restitution = props.GetFloatProperty("Restitution", DEF_RESTITUTION);
  fdef.filter.categoryBits = props.GetIntProperty("CategoryBits", 1);
  fdef.filter.maskBits = props.GetIntProperty("MaskBits", ~0);
  fdef.isSensor = props.GetBoolProperty("isSensor", false);

  for (int i = polygon->GetNumPoints() - 1; i >= 0; i--) {
    const Tmx::Point &point = polygon->GetPoint(i);
    float xb =
        (float)obj->GetX() + (float)point.x - (float)GetTileWidth() / 2.0f;
    float yb =
        (float)obj->GetY() + (float)point.y - (float)GetTileHeight() / 2.0f;

    v[polygon->GetNumPoints() - 1 - i] =
        m_mainClass->getPhysics2D()->vectorPixelToWorld(Vector2f(xb, yb));
  }

  shape.Set(v, polygon->GetNumPoints());

  delete[] v;

  fdef.shape = &shape;

  body = m_mainClass->getPhysics2D()->getWorld()->CreateBody(&bdef);
  body->CreateFixture(&fdef);

  m_bodies.push_back(body);
}

void TiledMap::loadCollisionPolyline(const Tmx::Object *obj, int x, int y) {
  const Tmx::Polyline *polyline = obj->GetPolyline();

  if (polyline->GetNumPoints() < 2 ||
      polyline->GetNumPoints() > b2_maxPolygonVertices) {
    LogManager::log(std::string("Polyline (") + std::to_string(x) + "; " +
                    std::to_string(y) + ") has too much or too few vertices");
    return;
  }

  b2Body *body;
  b2BodyDef bdef;
  b2FixtureDef fdef;
  b2ChainShape shape;
  b2Vec2 *v;

  v = new b2Vec2[polyline->GetNumPoints()];

  const Tmx::PropertySet &props = obj->GetProperties();

  std::string type = props.GetStringProperty("Type", "static");
  bdef.type = (type == "static"
                   ? b2_staticBody
                   : (type == "dynamic" ? b2_dynamicBody : b2_kinematicBody));

  fdef.density = props.GetFloatProperty("Density", DEF_DENSITY);
  fdef.friction = props.GetFloatProperty("Friction", DEF_FRICTION);
  fdef.restitution = props.GetFloatProperty("Restitution", DEF_RESTITUTION);
  fdef.filter.categoryBits = props.GetIntProperty("CategoryBits", 1);
  fdef.filter.maskBits = props.GetIntProperty("MaskBits", ~0);
  fdef.isSensor = props.GetBoolProperty("isSensor", false);

  for (int i = polyline->GetNumPoints() - 1; i >= 0; i--) {
    const Tmx::Point &point = polyline->GetPoint(i);
    float xb = x + point.x + obj->GetX();
    float yb = y + point.y + obj->GetY();

    v[polyline->GetNumPoints() - 1 - i] =
        m_mainClass->getPhysics2D()->coordsPixelToWorld(Vector2f(xb, yb));
  }

  shape.CreateChain(v, polyline->GetNumPoints(), v[0],
                    v[polyline->GetNumPoints() - 1]);
  delete[] v;

  fdef.shape = &shape;

  body = m_mainClass->getPhysics2D()->getWorld()->CreateBody(&bdef);
  body->CreateFixture(&fdef);

  m_bodies.push_back(body);
}

void TiledMap::loadCollisionRectangle(const Tmx::Object *obj, int x, int y) {
  b2Body *body;
  b2BodyDef bdef;
  b2FixtureDef fdef;
  b2PolygonShape shape;

  const Tmx::PropertySet &props = obj->GetProperties();

  bdef.position = m_mainClass->getPhysics2D()->coordsPixelToWorld(Vector2f(
      (GLfloat)x + (GLfloat)obj->GetX() + (GLfloat)obj->GetWidth() / 2.0f,
      (GLfloat)y + (GLfloat)obj->GetY() + (GLfloat)obj->GetHeight() / 2.0f));
  std::string type = props.GetStringProperty("Type", "static");
  bdef.type = (type == "static"
                   ? b2_staticBody
                   : (type == "dynamic" ? b2_dynamicBody : b2_kinematicBody));

  fdef.density = props.GetFloatProperty("Density", DEF_DENSITY);
  fdef.friction = props.GetFloatProperty("Friction", DEF_FRICTION);
  fdef.restitution = props.GetFloatProperty("Restitution", DEF_RESTITUTION);
  fdef.filter.categoryBits = props.GetIntProperty("CategoryBits", 1);
  fdef.filter.maskBits = props.GetIntProperty("MaskBits", ~0);
  fdef.isSensor = props.GetBoolProperty("isSensor", false);

  shape.SetAsBox(m_mainClass->getPhysics2D()->scalarPixelToWorld(
                     (GLfloat)obj->GetWidth() / 2.0f),
                 m_mainClass->getPhysics2D()->scalarPixelToWorld(
                     (GLfloat)obj->GetHeight() / 2.0f));
  fdef.shape = &shape;

  body = m_mainClass->getPhysics2D()->getWorld()->CreateBody(&bdef);
  body->CreateFixture(&fdef);

  m_bodies.push_back(body);
}

const Tmx::Tileset *TiledMap::getTileset(int gid) {
  if (gid == 0)
    return nullptr;

  int curGID = 0;

  for (int i = 0; i < GetNumTilesets(); i++) {
    curGID = GetTileset(i)->GetFirstGid();

    if (curGID == gid) {
      return GetTileset(i);
    } else if (i != 0 && curGID > gid) {
      return GetTileset(i - 1);
    } else if (i + 1 == GetNumTilesets()) {
      return GetTileset(i);
    }
  }

  return nullptr;
}

void TiledMap::getSrcRegionForTileGID(TextureRegion *src, int gid) {
  const Tmx::Tileset *tileSet = getTileset(gid);
  int id = gid - tileSet->GetFirstGid();
  int numTilesX = (tileSet->GetImage()->GetWidth() - tileSet->GetMargin() * 2 +
                   tileSet->GetSpacing()) /
                  (tileSet->GetTileWidth() + tileSet->GetSpacing());

  src->x = id % numTilesX;
  src->y = (id - src->x) / numTilesX;

  src->x = src->x * (tileSet->GetTileWidth() + tileSet->GetSpacing()) +
           tileSet->GetMargin();
  src->y = src->y * (tileSet->GetTileHeight() + tileSet->GetSpacing()) +
           tileSet->GetMargin();
  src->w = tileSet->GetTileWidth();
  src->h = tileSet->GetTileHeight();
}

void TiledMap::getSrcRegionForTileID(TextureRegion *src, int numTilesX,
                                     int index, int id) {
  src->x = id % numTilesX;
  src->y = (id - src->x) / numTilesX;

  const Tmx::Tileset *tileSet = GetTileset(index);

  src->x = src->x * (tileSet->GetTileWidth() + tileSet->GetSpacing()) +
           tileSet->GetMargin();
  src->y = src->y * (tileSet->GetTileHeight() + tileSet->GetSpacing()) +
           tileSet->GetMargin();
  src->w = tileSet->GetTileWidth();
  src->h = tileSet->GetTileHeight();
}

int TiledMap::getTileIDForTileGID(int gid) {
  const Tmx::Tileset *tileSet = getTileset(gid);
  if (!tileSet)
    return -1;
  else {
    return gid - tileSet->GetFirstGid();
  }
}

void TiledMap::loadAnimations(const Tmx::TileLayer *layer, int Lindex) {
  LogManager::log("Loading Animations...");

  for (int x = 0; x < layer->GetWidth(); x++) {
    for (int y = 0; y < layer->GetHeight(); y++) {
      int index = layer->GetTileTilesetIndex(x, y);

      if (index == -1)
        continue;

      const Tmx::MapTile &mapTile = layer->GetTile(x, y);
      const Tmx::Tileset *tileset = GetTileset(index);
      const Tmx::Tile *tile = tileset->GetTile(mapTile.id);

      if (!tile || tile->GetFrameCount() == 0)
        continue;

      if (m_animations.count(tile->GetId()) == 0) {
        const std::vector<Tmx::AnimationFrame> &anims = tile->GetFrames();
        Texture *texture = m_mainClass->getResourceManager()->loadTexture(
            GetFilepath() + tileset->GetImage()->GetSource());
        TileAnimation tileAnim;
        tileAnim.texture = texture;
        tileAnim.curRegion = 0;
        tileAnim.curTime = 0;

        for (size_t i = 0; i < anims.size(); i++) {
          TextureRegion region;
          getSrcRegionForTileID(&region, m_tilesX[index], index,
                                anims[i].GetTileID());
          tileAnim.regions.push_back(region);
          tileAnim.times.push_back(anims[i].GetDuration());
        }

        m_animations.insert(
            std::pair<int, TileAnimation>(tile->GetId(), tileAnim));
      }

      AnimationTile animTile;
      animTile.x = x * GetTileWidth();
      animTile.y = y * GetTileHeight();
      animTile.layer = Lindex;
      animTile.animID = tile->GetId();

      m_animTiles.push_back(animTile);
    }
  }
}

void TiledMap::updateAnimations() {
  int dMil = (int)(m_mainClass->getTimer()->getDeltaTimeInSeconds() * 1000.0f);

  for (std::map<int, TileAnimation>::iterator it = m_animations.begin();
       it != m_animations.end(); it++) {
    it->second.curTime += dMil;
    if (it->second.times[it->second.curRegion] <= it->second.curTime) {
      it->second.curTime = 0;
      it->second.curRegion++;
      if (it->second.curRegion == (int)it->second.regions.size())
        it->second.curRegion = 0;
    }
  }
}

void TiledMap::renderAnimations() {
  TileAnimation anim;
  TextureRegion dstRegion(0, 0, GetTileWidth(), GetTileHeight());

  // SDL_SetRenderDrawColor(m_mainClass->getRenderer(),m_background.r,m_background.g,m_background.b,m_background.a);
  for (size_t i = 0; i < m_animTiles.size(); i++) {
    m_renderTextures[m_animTiles[i].layer]->target();
    anim = m_animations[m_animTiles[i].animID];
    dstRegion.x = m_animTiles[i].x;
    dstRegion.y = m_animTiles[i].y;
    // SDL_RenderFillRect(m_mainClass->getRenderer(),&dstRect);
    Texture::renderTexture2D(m_clearTexture, &dstRegion);
    // anim.texture->renderCopy(m_mainClass->getRenderer(),&dstRect,&anim.rects[anim.curRect]);
    Texture::renderTexture2D(anim.texture, &dstRegion,
                             &anim.regions[anim.curRegion]);
  }

  m_mainClass->getBackBuffer()->bind();
  glViewport(0, 0, (GLsizei)m_mainClass->getNativeRes().x,
             (GLsizei)m_mainClass->getNativeRes().y);
  TransformableObject2D::setViewportSize(m_mainClass->getNativeRes());
}

bool TiledMap::update() {
  updateAnimations();

  return true;
}

void TiledMap::renderLayers() {
  // m_texture->setRenderTarget(m_mainClass->getRenderer());
  m_mainTextureFrameBuffer->bind();
  TransformableObject2D::setViewportSize(Vector2f(
      (GLfloat)m_texture->getWidth(), (GLfloat)m_texture->getHeight()));
  glViewport(0, 0, m_texture->getWidth(), m_texture->getHeight());

  // SDL_SetRenderDrawColor(m_mainClass->getRenderer(),m_background.r,m_background.g,m_background.b,m_background.a);
  Colorf back(m_background);
  glClearColor(back.r, back.g, back.b, back.a);

  glClear(GL_COLOR_BUFFER_BIT);

  //		void blit(FrameBuffer*, GLint, GLint, GLint, GLint, GLint, GLint,
  //GLint, GLint, GLbitfield mask = GL_COLOR_BUFFER_BIT, GLenum filter =
  //GL_NEAREST);

  for (size_t i = 0; i < m_renderTextures.size(); i++) {
    m_renderTextures[i]->render(Vector2f(0.0f, 0.0f), Vector2f(1.0f, 1.0f),
                                0.0f, nullptr, nullptr, true, GL_TEXTURE_2D);
  }

  m_mainClass->getBackBuffer()->bind();
  glViewport(0, 0, (GLsizei)m_mainClass->getNativeRes().x,
             (GLsizei)m_mainClass->getNativeRes().y);
  TransformableObject2D::setViewportSize(m_mainClass->getNativeRes());
}

bool TiledMap::render() {
  renderAnimations();

  renderLayers();

  m_shader->getShaderUpdater()->update();

  setScale(getScale() * m_drawScale);

  m_shader->getShaderUpdater()->setUniforms(
      &m_transform, m_isAffectedByCamera
                        ? Texture2DShaderUpdater::TRANSFORM_CAMERA
                        : Texture2DShaderUpdater::TRANSFORM_NORMAL);
  m_shader->getShaderUpdater()->setUniforms(m_texture, 1);
  m_shader->getShaderUpdater()->setUniforms(&m_srcRegion);
  m_shader->getShaderUpdater()->setUniforms(this);

  setScale(getScale() / m_drawScale);

  return true;
}

void TiledMap::quit() {
  for (size_t i = 0; i < m_bodies.size(); i++) {
    m_mainClass->getPhysics2D()->getWorld()->DestroyBody(m_bodies[i]);
  }
  m_bodies.clear();

  delete[] m_tilesX;
  m_tilesX = nullptr;

  for (size_t i = 0; i < m_renderTextures.size(); i++) {
    delete m_renderTextures[i];
  }
  m_renderTextures.clear();

  delete m_mainTextureFrameBuffer;

  for (std::map<Texture *, FrameBuffer *>::iterator it =
           m_frameBuffersOfTileSets.begin();
       it != m_frameBuffersOfTileSets.end(); it++) {
    delete it->second;
  }
  m_frameBuffersOfTileSets.clear();

  m_tilesetTextures.clear();
}

b2Body *TiledMap::toCollisionBody(const Tmx::Object *obj) {
  if (obj->GetEllipse()) {
    loadCollisionEllipse(obj, 0, 0);
  } else if (obj->GetPolygon()) {
    loadCollisionPolygon(obj, 0, 0);
  } else if (obj->GetPolyline()) {
    loadCollisionPolyline(obj, 0, 0);
  } else {
    loadCollisionRectangle(obj, 0, 0);
  }

  if (m_bodies.empty())
    return nullptr;
  else
    return m_bodies.back();
}

void TiledMap::destroyTile(int x, int y, int layer) {
  RenderTexture *rTex = m_renderTextures[layer];

  // SDL_SetRenderDrawColor(m_mainClass->getRenderer(),0,0,0,0);
  // SDL_SetRenderDrawBlendMode(m_mainClass->getRenderer(),SDL_BLENDMODE_NONE);
  rTex->target();

  // TextureRegion region =
  // {x*GetTileWidth(),y*GetTileHeight(),GetTileWidth(),GetTileHeight()};

  // SDL_RenderFillRect(m_mainClass->getRenderer(),&rect);
  // SDL_SetRenderDrawBlendMode(m_mainClass->getRenderer(),SDL_BLENDMODE_BLEND);
  // SDL_SetRenderTarget(m_mainClass->getRenderer(),m_mainClass->getBackBuffer());

  Texture::renderTexture2D(
      m_clearTexture,
      Vector2f((GLfloat)(x * GetTileWidth()), (GLfloat)(y * GetTileHeight())));

  rTex->untarget();

  for (size_t i = 0; i < m_animTiles.size(); i++) {
    if (m_animTiles[i].x == x * GetTileWidth() &&
        m_animTiles[i].y == y * GetTileHeight() &&
        m_animTiles[i].layer == layer) {
      m_animTiles[i] = m_animTiles.back();
      m_animTiles.pop_back();
      return;
    }
  }
}

void TiledMap::setTile(int x, int y, int layer, int tileset, int id) {
  destroyTile(x, y, layer);

  TextureRegion srcRegion;
  TextureRegion dstRegion;

  getSrcRegionForTileID(&srcRegion, m_tilesX[tileset], tileset, id);
  RenderTexture *rTex = m_renderTextures[layer];

  rTex->target();

  dstRegion.x = x * GetTileWidth();
  dstRegion.y = y * GetTileHeight();
  dstRegion.w = GetTileWidth();
  dstRegion.h = GetTileHeight();
  const Tmx::Tile *tile = GetTileset(tileset)->GetTile(id);

  /*if(!tile)
  {
          LogManager::error(std::string("Couldn't set Tile: ") +
  std::to_string(id)); return;
  }*/

  Texture *tileSetTex = m_tilesetTextures
      [tileset]; // m_mainClass->getResourceManager()->loadTexture(GetFilepath()
                 // + GetTileset(tileset)->GetImage()->GetSource());
  // tileSetTex->renderCopy(m_mainClass->getRenderer(),&dstRect,&srcRect);
  Texture::renderTexture2D(tileSetTex, &dstRegion, &srcRegion);

  bool isAnim = false;
  bool animLoaded = false;

  for (std::map<int, TileAnimation>::iterator it = m_animations.begin();
       it != m_animations.end(); it++) {
    if (it->first == id) {
      animLoaded = true;
      break;
    }
  }

  if (tile && tile->GetFrameCount() > 0 && !animLoaded) {
    TileAnimation anim;
    anim.curRegion = 0;
    anim.curTime = 0;
    anim.texture = tileSetTex;
    std::vector<TextureRegion> regions;
    std::vector<int> times;
    for (size_t i = 0; i < tile->GetFrames().size(); i++) {
      Tmx::AnimationFrame frame = tile->GetFrames()[i];
      times.push_back(frame.GetDuration());
      getSrcRegionForTileID(&srcRegion, m_tilesX[tileset], tileset,
                            frame.GetTileID());
      regions.push_back(srcRegion);
    }
    anim.regions = regions;
    anim.times = times;
    isAnim = true;
  }

  for (std::map<int, TileAnimation>::iterator it = m_animations.begin();
       it != m_animations.end(); it++) {
    if (it->first == id) {
      animLoaded = true;
      break;
    }
  }

  if (isAnim || animLoaded) {
    AnimationTile anim;
    anim.animID = id;
    anim.layer = layer;
    anim.x = x * GetTileWidth();
    anim.y = y * GetTileHeight();

    m_animTiles.push_back(anim);
  }
}
} // namespace Johnny
