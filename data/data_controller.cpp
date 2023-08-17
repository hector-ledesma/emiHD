#include "data_controller.h"

#include <ctime>
#include <chrono>
#include <memory>
#include "elements/Timer.h"

namespace data {
    static std::chrono::time_point g_appStart = std::chrono::system_clock().now();
    static auto clock_now = std::chrono::system_clock::now();
    static auto system_now = std::chrono::system_clock::now();

    DataController::DataController() {
        using namespace std::chrono_literals;
        // active timers
        for (int i = 0; i < 3; i++) {
            auto new_timer = std::make_shared<Timer>( data::Timer(id_count++, g_appStart, "Studying", "Quota completed and other business idk.", g_appStart) );
            m_timers.push_back(new_timer);
        }
        // completed timers
        for (int i = 0; i < 15; i++) {
            std::chrono::system_clock::time_point end{ g_appStart + 2111h + 15s };
            auto new_timer = std::make_shared<Timer>( data::Timer(id_count++, g_appStart, "Studying", "Quota completed and other business idk.", g_appStart));
            new_timer->stop();
            m_timers.push_back(new_timer);
        }
    }
    DataController::~DataController() {
    }

    void DataController::createTimer(std::string title) {
        auto now = std::chrono:: system_clock::now();
        m_timers.push_back(std::make_shared<Timer>(data::Timer(id_count++, now, title, "", now)));
    }
}