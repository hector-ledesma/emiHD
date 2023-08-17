#ifndef ELEMENT_INTERFACE_INCLUDED
#define ELEMENT_INTERFACE_INCLUDED

#pragma once
#include "imgui.h"
#include <string>
#include <functional>

namespace UI {
    class Element {
    public:
        virtual void setFlags(int flags) { m_flags = flags; };
        virtual void render(const std::function<void()>& lambda = []{}) {
            begin();
            style();
            lambda();
            end();
            
        };
    protected:
        int m_flags = 0;

        virtual bool begin() = 0;
        virtual void style() = 0;
        virtual void end() = 0;
    };
}
#endif
