#include "Timer.h"

namespace data {

    Timer::Timer(int id, system_clock::time_point date, std::string title, std::string comments,
        system_clock::time_point startTime, system_clock::duration duration) :
        m_id(id), m_date(date), m_title(title), m_comments(comments), m_startTime(startTime), m_duration(duration)
    {
    }

    int Timer::getId() const {
        return m_id;
    }
    system_clock::time_point Timer::getDate() const {
        return m_date;
    }
    std::string Timer::getTitle() const {
        return m_title;
    }
    std::string Timer::getComments() const {
        return m_comments;
    }
    system_clock::time_point Timer::getStartTime() const {
        return m_startTime;
    }
    system_clock::duration Timer::getDuration() const {
        return m_duration;
    }
    
    bool Timer::isRunning() const {
        return m_duration == TIMER_RUNNING;
    }
    void Timer::updateTime(system_clock::time_point time) const {
        m_startTime = time;
    }
    void Timer::setDuration(system_clock::duration duration) const {
        m_duration = duration;
    }
}