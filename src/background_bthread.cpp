
#include <bthread.h>
#include <memory>

class Task {
public:
    Task() : _stop{false} {
    }

    virtual ~Task() {
        _stop = true;
        bthread_stop(_tid);
        bthread_join(_tid, nullptr);
    }

    /**
     * @retrun {0|OK}, {Other|Failed}
     */
    int start() {
        std::call_once(_start_once_flag, start_once);
        return 0;
    }

    void* start_once() {
        thread_start_background(&_tid, NULL, start_static, this);
        return nullptr;
    }

    static void* start_static(void* param) {
        Task* self = static_cast<Task*>(param);
        self->start_impl_udf();
    }

    void* start_impl_udf() {
        for (; !_stop;) {
            start_udf();
            bthread_usleep(1000/*us*/);
        }
        return nullptr;
    }

    virtual void start_udf(void) {
        return;
    }

private:
    DISALLOW_COPY_AND_ASSIGN(Task);

private:
    std::atomic<bool>   _stop;
    bthread_t           _tid;
    std::once_flag      _start_once_flag;
};
