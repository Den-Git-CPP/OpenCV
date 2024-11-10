#include "logger.hpp"

namespace logger
{
    /**
     * @brief Construct a new Logger:: Logger object
     * 
     * @param log_file   path of the log file
     * @param log_level  level logging
     * @param display    display or not on console
     */
    Logger::Logger(std::string log_file, int log_level, bool display) : m_log_file(log_file), m_log_level(log_level), m_display(display)
    {}

    
    /**
     * @brief Destroy the Logger:: Logger object
     * 
     */
    Logger::~Logger()
    {}


    /**
     * @brief Get the local time of the machine
     * 
     * @return date time string on the format [%Y-%m-%d %H:%M:%S]
     */
    std::string Logger::get_time() const
    {
        time_t rawtime;
        struct tm * timeinfo;
        char buffer [80];

        time ( &rawtime );
        timeinfo = localtime ( &rawtime );

        strftime (buffer,80,"[%Y-%m-%d %H:%M:%S]",timeinfo);
        return buffer;
    }

} // namespace logger
