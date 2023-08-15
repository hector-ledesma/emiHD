#include "Timer.h"

namespace data {

    Timer::Timer(int id, system_clock::time_point date, std::string title, std::string comments,
        system_clock::time_point startTime, system_clock::time_point endTime) :
        m_id(id), m_date(date), m_title(title), m_comments(comments), m_startTime(startTime), m_endTime(endTime)
    {
    }

    int Timer::getId() {
        return m_id;
    }
    system_clock::time_point Timer::getDate() {
        return m_date;
    }
    std::string Timer::getTitle() {
        return m_title;
    }
    std::string Timer::getComments() {
        return m_comments;
    }
    system_clock::time_point Timer::getStartTime() {
        return m_startTime;
    }
    system_clock::time_point Timer::getEndTime() {
        return m_endTime;
    }
    float Timer::getDuration() {
        std::chrono::duration<float, std::milli> elapsed = std::chrono::system_clock::now() - m_startTime;
        return elapsed.count();
    }
    bool Timer::isRunning() {
        return m_endTime == TIMER_RUNNING;
    }
    void Timer::updateTime(system_clock::time_point time) {
        m_startTime = time;
    }
}