/* 
 * from webrtc/base/ratelimiter.h
 */
namespace base {

class RateLimiter {
public:
    RateLimiter(size_t max, size_t period)
        : max_per_period_(max),
          period_length_(period),
          used_in_period_(0),
          period_start_(0.0),
          period_end_(period) {
    }

    virtual ~RateLimiter() {}

    // Returns true if the desired quantity is available in the
    // current period (< (max - used)). Once the given time passes the
    // end of the period, used is set to zero and more use in available.
    bool CanUse(size_t desired, size_t time) {
        return ((time > period_end_ && desired <= max_per_period_) ||
                (used_in_period_ + desired) <= max_per_period_);
    }
    // Increment the quantity used this period. If past the end of a
    // period, a new period is started.
    void Use(size_t used, size_t time) {
        if (time > period_end_) {
            period_start_ = time;
            period_end_ = time + period_length_;
            used_in_period_ = 0;
        }
        
        used_in_period_ += used;
    }

    size_t used_in_period() const {
        return used_in_period_;
    }

    size_t max_per_period() const {
        return max_per_period_;
    }
private:
    size_t max_per_period_;
    size_t period_length_;
    size_t used_in_period_;
    size_t period_start_;
    size_t period_end_;
};

}
