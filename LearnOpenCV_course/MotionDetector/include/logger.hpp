#pragma once

#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>


static const char *enum_str_message[] = { "FATAL", "ERROR", "WARNING", "INFO", "DEBUG", "TRACE" };
static const char *enum_color_message[] = { "31", "31", "33", "90", "35", "39" };
namespace logger
{
    /**
     * @brief Logger class
     * 
     */
    class Logger
    {
    private:
        /**
         * @brief Get the local time of the machine
         * 
         * @return date time string on the format [%Y-%m-%d %H:%M:%S]
         */
        std::string get_time() const;

        /* Attributes */
        std::string m_log_file; // Path of the log file
        int m_log_level;        // Log level
        bool m_display;         // Display on fd 
    public:
        enum MessageType { FATAL, ERROR, WARN, INFO, DEBUG, TRACE };

        /**
         * @brief Construct a new Logger object
         * 
         * @param log_file   path of the log file
         * @param log_level  level logging
         * @param display    display or not on console
         */
        Logger(std::string log_file, int log_level, bool display);
        
        /* Destructor */
        ~Logger();


        /**
         * @brief Add message log to console and in log file
         * 
         * @tparam T Level type of the log
         * @tparam U Represents the message to log
         */
        template <typename T, typename U>
        void add_log(T logType, U message)
        {
            if (m_log_level > logType)
            {
                time_t now = time(0);
                tm *ltm = localtime(&now);
                std::ostream &fd = (logType >= FATAL && logType <= ERROR) ? std::cerr : std::cout;
                std::string type = "\033[" + std::string(enum_color_message[logType])+ 'm';
                auto log = get_time() + '[' + std::string(enum_str_message[logType])[0] + "] " + message;

                if (m_display)
                {
                    // Write on console
                    fd << type << log << "\033[0m" << '\n';
                }

                // Write on file
                std::ofstream logfile(m_log_file, std::ios_base::app);
                if (logfile.is_open())
                {
                    logfile << log + '\n';
                    logfile.close();
                }
            }
        }
    };
} // namespace logger
