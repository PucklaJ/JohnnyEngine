#ifndef LOGMANAGER_H
#define LOGMANAGER_H
#include <ctime>
#include <string>

extern void shutdownProgram();

namespace Johnny

{
    /*! \brief A class which handles logging
     *
     */
    class LogManager
    {
        public:
            LogManager();
            virtual ~LogManager();

            /*! \brief Sets the file where the logs should go to
             *  \param file The file to set
             */
            static void setFile(const char* file){m_file=file;}
            /*! \brief Logs some text to the console and a file
             *  \param text The text which will be logged
             *  \param withTime Defines wether the date and time should be included in the log
             *  \param newLine Defines wether there should be a new line placed after the log
             */
            static void log(const std::string& text,bool withTime = true,bool newLine = true);
            /*! \brief Logs a number to the console and a file
             *  \param i The number which will be logged
             *  \param withTime Defines wether the date and time should be included in the log
             *  \param newLine Defines wether there should be a new line placed after the log
             */
			static void log(int i, bool withTime = true, bool newLine = true);
            /*! \brief Logs the text as an error
             *  \param text The text which will be logged
             *  \param withTime Defines wether the date and time should be included in the log
             *  \param newLine Defines wether there should be a new line placed after the log
             *  \param messageBox Defines wether there should be a MessageBox opened with the error contents
             */
			static void error(const std::string& text, bool withTime = true, bool newLine = true, bool messageBox = true);

        private:
            /*! \return The current time in format HH:MM:SS
             *
             */
            static const std::string getTime();
            /*! \return The current Date in format DD:MM:YYYY
             *
             */
            static const std::string getDay();
            /*! \brief Creates a MessageBox which will be used for error logging
             *  \param msg The message which will be written
             *  \return The id of the button pressed (0=Continue, 1=Shutdown)
             */
			static int createMessageBox(const std::string& msg);

            static const char* m_file; //!< The relative or absolute path of the file where the logs go to
            static time_t m_timer;     //!< Is used to determine the time and the date
            static struct tm* m_tm;    //!< Is used to determine the time and the date
    };
}



#endif // LOGMANAGER_H
