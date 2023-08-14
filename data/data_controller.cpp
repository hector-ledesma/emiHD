#include "data_controller.h"

#include <ctime>
#include <chrono>

namespace data {
    static std::chrono::time_point g_appStart = std::chrono::high_resolution_clock().now();
    static auto clock_now = std::chrono::high_resolution_clock::now();
    static auto system_now = std::chrono::system_clock::now();

    DataController::DataController() {
    }
    DataController::~DataController() {
    }
    std::vector<Timer> DataController::getActiveTimers() {
        std::vector<Timer> timers;
        for (int i = 0; i < 3; i++) {
            
            auto today = std::chrono::system_clock::to_time_t(system_now);
            auto new_timer = data::Timer(i, today, "Studying", "Quota completed and other business idk.", g_appStart, g_appStart);
            timers.push_back(new_timer);
        }
        return timers;
    }
}