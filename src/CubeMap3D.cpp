#include "../include/CubeMap3D.h"
#include "../include/ResourceManager.h"
#include <iostream>

namespace Johnny {
CubeMap3D::CubeMap3D(const std::string &top, const std::string &bottom,
                     const std::string &left, const std::string &right,
                     const std::string &front, const std::string &back,
                     ResourceManager *res)
    : Texture() {
  /*
  #define GL_TEXTURE_CUBE_MAP_POSITIVE_X 0x8515 RIGHT
  #define GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x8516 LEFT
  #define GL_TEXTURE_CUBE_MAP_POSITIVE_Y 0x8517 TOP
  #define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x8518 BOTTOM
  #define GL_TEXTURE_CUBE_MAP_POSITIVE_Z 0x8519 BACK
  #define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x851A FRONT

  */

  if (m_texture != 0) {
    TextureData *datas[6];

    datas[0] = res->loadTextureData(right);
    datas[1] = res->loadTextureData(left);
    datas[2] = res->loadTextureData(top);
    datas[3] = res->loadTextureData(bottom);
    datas[4] = res->loadTextureData(back);
    datas[5] = res->loadTextureData(front);

    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);

    for (unsigned int i = 0; i < 6; i++) {
      if (datas[i]) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA,
                     datas[i]->width, datas[i]->height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, datas[i]->data);
      } else {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, 0, 0, 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
      }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    for (unsigned int i = 0; i < 6; i++) {
      res->deleteTextureData(datas[i]);
    }
  }
}

CubeMap3D::CubeMap3D(TextureData *top, TextureData *bottom, TextureData *left,
                     TextureData *right, TextureData *front,
                     TextureData *back) {
  /*
  #define GL_TEXTURE_CUBE_MAP_POSITIVE_X 0x8515 RIGHT
  #define GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x8516 LEFT
  #define GL_TEXTURE_CUBE_MAP_POSITIVE_Y 0x8517 TOP
  #define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x8518 BOTTOM
  #define GL_TEXTURE_CUBE_MAP_POSITIVE_Z 0x8519 BACK
  #define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x851A FRONT

  */

  if (m_texture != 0) {
    TextureData *datas[6];

    datas[0] = right;
    datas[1] = left;
    datas[2] = top;
    datas[3] = bottom;
    datas[4] = back;
    datas[5] = front;

    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);

    for (unsigned int i = 0; i < 6; i++) {
      if (datas[i]) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA,
                     datas[i]->width, datas[i]->height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, datas[i]->data);
      } else {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, 0, 0, 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
      }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
  }
}

} // namespace Johnny