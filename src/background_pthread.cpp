
#include "background_pthread.hpp"

int main() {
    gtl::BackGroundTask  bgt;
    bgt.start();
    for (int i = 1;;i++) {
        if ((i%1000) == 0) {
            bgt.stop();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}
