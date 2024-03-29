#include "../include/LogManager.h"
#include <cstdio>
#include <iostream>
#include <sstream>
#ifdef _WIN32
#include <Windows.h>
#endif
#include "../include/MainClass.h"
#include "../include/Window.h"
#include "../include/operators.h"
#include <SDL2/SDL.h>

namespace Johnny {
const char *LogManager::m_file = "log.txt";
time_t LogManager::m_timer;
struct tm *LogManager::m_tm = new struct tm;

LogManager::LogManager() {
  // ctor
}

LogManager::~LogManager() {
  // dtor
}

const std::string setTime(int i) {
  std::string text = "";
  std::stringstream str;

  str << i;
  str >> text;

  if (text.length() == 1) {
    text = "0" + text;
  }

  return text;
}

const std::string LogManager::getTime() {
  std::string text = "";

  time(&m_timer);
#ifdef _WIN32
  localtime_s(m_tm, &m_timer);
#else
  m_tm = localtime(&m_timer);
#endif

  std::stringstream str;

  str << "[" << setTime(m_tm->tm_hour) << ":" << setTime(m_tm->tm_min) << ":"
      << setTime(m_tm->tm_sec) << "]";

  str >> text;
  str.clear();

  return text;
}

const std::string LogManager::getDay() {
  std::string text = ""; // Hallo

  time(&m_timer);
#ifdef _WIN32
  localtime_s(m_tm, &m_timer);
#else
  m_tm = localtime(&m_timer);
#endif
  std::stringstream str;

  str << "[" << setTime(m_tm->tm_mday) << ":" << setTime(m_tm->tm_mon + 1)
      << ":" << m_tm->tm_year + 1900 << "]";

  str >> text;
  str.clear();

  return text;
}

int LogManager::createMessageBox(const std::string &text) {
  const SDL_MessageBoxButtonData buttons[] = {
      {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Continue"},
      {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "Shutdown"}};

  const SDL_MessageBoxColorScheme colorScheme = {{{255, 0, 0},
                                                  {255, 255, 255},
                                                  {90, 90, 90},
                                                  {128, 128, 128},
                                                  {200, 200, 200}}};

  const SDL_MessageBoxData messageBoxData = {
      SDL_MESSAGEBOX_ERROR,
      MainClass::getInstance()->getWindow()
          ? (SDL_Window *)MainClass::getInstance()->getWindow()->getHandle()
          : nullptr,
      "An error accoured",
      text.c_str(),
      SDL_arraysize(buttons),
      buttons,
      &colorScheme};

  int buttonId = 0;

  SDL_ShowMessageBox(&messageBoxData, &buttonId);

  return buttonId;
}

void LogManager::log(const std::string &text, bool withTime, bool newLine) {
  std::string msg = (withTime ? (getDay() + " " + getTime()) : "");

  msg += (withTime ? " " : "") + text + (newLine ? "\n" : "");

  std::cout << msg;

  FILE *file;
#ifdef _WIN32
  fopen_s(&file, m_file, "a");
#else
  file = fopen(m_file, "a");
#endif
  fprintf(file, msg.c_str(), "");
  fclose(file);
}
void LogManager::log(int i, bool withTime, bool newLine) {
  log(std::to_string(i), withTime, newLine);
}
void LogManager::error(const std::string &text, bool withTime, bool newLine,
                       bool messageBox) {
  std::string msg = (withTime ? (getDay() + " " + getTime()) : "");

  msg += (withTime ? " " : "") + std::string("ERROR: ") + text +
         (newLine ? "\n" : "");

  std::cerr << msg;

  FILE *file;
#ifdef _WIN32
  fopen_s(&file, m_file, "a");
#else
  file = fopen(m_file, "a");
#endif
  fprintf(file, msg.c_str(), "");
  fclose(file);

  if (messageBox) {
    int button = createMessageBox(text);
    if (button == 1)
      shutdownProgram();
  }
}
} // namespace Johnny

void shutdownProgram() {
  Johnny::MainClass::getInstance()->m_all_quit();
  Johnny::LogManager::log("Program was shutdown by an error");
  exit(-1);
}
