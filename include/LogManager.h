#ifndef LOGMANAGER_H
#define LOGMANAGER_H
#include <ctime>
#include <string>

extern void shutdownProgram();

namespace Johnny

{
    /** \brief
     *
     * Class for Logging
     *
     *
     *
     */
    class LogManager
    {
        public:
            LogManager();
            virtual ~LogManager();

            static void setFile(const char* file){m_file=file;}
            /** \brief
             *
             *  Logs some text to the console and a file
             *
             *
             *
             */

            static void log(const std::string& text,bool withTime = true,bool newLine = true);
			static void error(const std::string& text, bool withTime = true, bool newLine = true, bool messageBox = true);

        protected:

        private:
            static const std::string getTime();
            static const std::string getDay();
			static int createMessageBox(const std::string&);

            static const char* m_file;
            static time_t m_timer;
            static struct tm* m_tm;
    };
}



#endif // LOGMANAGER_H
