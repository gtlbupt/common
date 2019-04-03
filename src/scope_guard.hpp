#pragma once

#include <functional>

#define SCOPEGUARD_LINENAME_CAT(name, line) name##line
#define SCOPEGUARD_LINENAME(name, line) SCOPEGUARD_LINENAME_CAT(name, line)
#define ON_SCOPE_EXIT(callback) base::ScopeGuard SCOPEGUARD_LINENAME(EXIT, __LINE__)(callback)

namespace base {

/*
 * @see http://mindhacks.cn/2012/08/27/modern-cpp-practices/
 */
class ScopeGuard {
public:
    explicit ScopeGuard(std::function<void()> on_exit_scope) 
        : _on_exit_scope(on_exit_scope), _dismissed(false)
    { }

    ~ScopeGuard()
    {
        if(!_dismissed)
        {
            _on_exit_scope();
        }
    }

    void dismiss()
    {
        _dismissed = true;
    }

private:
    std::function<void()> _on_exit_scope;
    bool _dismissed;

private: // noncopyable
    ScopeGuard(ScopeGuard const&);
    ScopeGuard& operator=(ScopeGuard const&);
};

}
