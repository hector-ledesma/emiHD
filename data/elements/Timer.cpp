#include "Timer.h"
#include <iostream>
namespace {
}
namespace data {
    // Timer::TimerDuration
    Timer::TimerDuration::TimerDuration(clock::time_point startTime, TimerState_ state) : m_state(state), m_start(startTime) {

    }

    TimerState_ Timer::TimerDuration::getState() const {
        return m_state;
    }
    clock::time_point Timer::TimerDuration::getDuration() {
        return m_start;
    }
    clock::time_point Timer::TimerDuration::getRuntime() {
        switch (m_state) {
        case data::TimerState_::PAUSE:
            return m_elapsed;
            break;
        case data::TimerState_::PLAY:
            return clock::time_point{ clock::now() - m_start };
            break;
        default:
            break;
        }
    }

    TimerState_ Timer::TimerDuration::updateState(TimerState_ change_to) {
        switch (change_to)
        {
        case data::TimerState_::PAUSE:
            m_pausedAt = clock::now();
            m_elapsed = clock::time_point{ m_pausedAt - m_start };
            break;
        case data::TimerState_::PLAY:
            m_start = clock::time_point{ clock::now() - m_elapsed };
            break;
        case data::TimerState_::STOP:
            if (m_state == TimerState_::PAUSE) m_start = clock::time_point{ clock::now() - m_elapsed };
            m_start = clock::time_point{ clock::now() - m_start };
            break;
        default:
            break;
        }
        m_state = change_to;
        return getState();
    }


    // Timer
    Timer::Timer(int id, system_clock::time_point date, std::string title, std::string comments,
        system_clock::time_point startTime, TimerState_ state) :
        m_id(id), m_date(date), m_title(title), m_comments(comments), m_duration{startTime, state}
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
        return m_date;
    }
    system_clock::time_point Timer::getRuntime() {
        auto runtime = m_duration.getRuntime();

        return clock::time_point{ runtime };
    }
    system_clock::time_point Timer::getDuration() {
        auto duration = m_duration.getDuration();

        return clock::time_point{ duration };
    }
    
    bool Timer::isRunning() const {
        return m_duration.getState() != TimerState_::STOP;
    }

    void Timer::togglePause() {
        if (m_duration.getState() == TimerState_::PAUSE) {
            m_duration.updateState(TimerState_::PLAY);
        }
        else {
            m_duration.updateState(TimerState_::PAUSE);
        }
    }

    void Timer::stop() {
        m_duration.updateState(TimerState_::STOP);
    }
}