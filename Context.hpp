#pragma once
#include <memory>
#include <iostream>
#include <thread>
#include <chrono>
#include "IState.hpp"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

class Context
{
    public:
        void set_state(std::unique_ptr<IState> state)
        {
            current_state_ = std::move(state);
        }

        void run(void)
        {
            while (current_state_)
            {
                current_state_->handle(*this);
                // std::this_thread::sleep_for(std::chrono::seconds(4));
            }
        }

        // Configurable parameters
        bool is_conf_ok = false;
        int ping_count = 0;
        int max_ping_startup = 5;
        int delay_timer = 1;

        // Simulated trigger
        enum class TriggerStatus { SUBMERGED, SURFACED };
        // Helper function to convert TriggerStatus to string
        std::string triggerStatusToString(Context::TriggerStatus status)
        {
            switch (status)
            {
                case Context::TriggerStatus::SUBMERGED: return "SUBMERGED";
                case Context::TriggerStatus::SURFACED:  return "SURFACED";
                default: return "INVALID";
            }
        }
        // TriggerStatus trigger() {
        //     return simulated_trigger;
        // }
        TriggerStatus trigger(void)
        {
            char key = read_key();
            if (key == 's' || key == 'S')
            {
                simulated_trigger = (simulated_trigger == TriggerStatus::SUBMERGED)
                    ? TriggerStatus::SURFACED
                    : TriggerStatus::SUBMERGED;
                std::cout << "[Input] State change forced by key S : "
                        << (simulated_trigger == TriggerStatus::SURFACED ? "SURFACED" : "SUBMERGED") << "\n";
            }
            return simulated_trigger;
        }

        void set_trigger(TriggerStatus status) {
            simulated_trigger = status;
        }


        void ping() {
            std::cout << "Ping sent #" << ping_count << "\n";
        }

        void delay(int seconds) {
            std::cout << "Delay of " << seconds << " seconds\n";
            std::this_thread::sleep_for(std::chrono::seconds(seconds));
        }

    private:
        std::unique_ptr<IState> current_state_;
        TriggerStatus simulated_trigger = TriggerStatus::SUBMERGED;

        char read_key(void)
        {
            struct termios oldt, newt;
            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;
            newt.c_lflag &= ~(ICANON | ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);

            fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

            char ch = 0;
            ssize_t nread = read(STDIN_FILENO, &ch, 1);

            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            fcntl(STDIN_FILENO, F_SETFL, 0);

            if (nread > 0)
                return ch;
            return 0;
        }
};
