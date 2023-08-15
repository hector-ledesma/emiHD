#include "data_controller.h"

#include <ctime>
#include <chrono>
#include "elements/Timer.h"

namespace data {
    static std::chrono::time_point g_appStart = std::chrono::system_clock().now();
    static auto clock_now = std::chrono::system_clock::now();
    static auto system_now = std::chrono::system_clock::now();

    DataController::DataController() {
        using namespace std::chrono_literals;
        // active timers
        for (int i = 0; i < 3; i++) {
            auto new_timer = data::Timer(i, g_appStart, "Studying", "Quota completed and other business idk.", g_appStart);
            m_timers.push_back(new_timer);
        }
        // completed timers
        for (int i = 0; i < 15; i++) {
            auto new_timer = data::Timer(i+3, g_appStart, "Studying", "Quota completed and other business idk.", g_appStart, g_appStart + 2111h + 155s);
            m_timers.push_back(new_timer);
        }
    }
    DataController::~DataController() {
    }
    std::vector<Timer> DataController::getActiveTimers() {
        std::vector<Timer> timers;
        for (auto& timer : m_timers) {
            if (timer.getEndTime() <= timer.getStartTime()) {
                timers.push_back(timer);
            }
        }
        return timers;
    }
    std::vector<Timer> DataController::getAllTimers() {
        return m_timers;
    }
}