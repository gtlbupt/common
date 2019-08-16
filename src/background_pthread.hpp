
#include <thread>
#include <atomic>
#include <memory>
#include <iostream>

#include "macros.hpp"

namespace gtl {

class BackGroundTask {
public:
    BackGroundTask() : _stop{false} {}

    virtual ~BackGroundTask () {
        stop();
    }

    int start(void) {
        std::call_once(_start_once_flag, &BackGroundTask::start_once, this);
        return 0;
    }

    int stop(void) {
        std::call_once(_stop_once_flag, &BackGroundTask::stop_once, this);
        return 0;
    }

    virtual void routine(void) {
        for (; !_stop;) {
            std::cout << "Run Routine ..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        return;
    }
private:
    DISALLOW_COPY_AND_ASSIGN(BackGroundTask);

private:
    int start_once(void) {
        std::cout << "func:" << __func__ << " called";
        std::thread t(&BackGroundTask::routine, this);
        _tid.swap(t);
        return 0;
    }

    int stop_once(void) {
        std::cout << "func:" << __func__ << " called";
        if (_stop) {
            return 0;
        }
        _stop = true;
        _tid.join();
        return 0;
    }
private:
    std::atomic<bool> _stop;
    std::thread _tid;
    std::once_flag      _start_once_flag;
    std::once_flag      _stop_once_flag;
};

}
