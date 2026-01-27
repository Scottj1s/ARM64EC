#pragma once

#include "Class.g.h"

namespace winrt::RuntimeComponent1::implementation
{
    struct Class : ClassT<Class>
    {
        Class() = default;

        int32_t m_myProperty{ 42 };

        int32_t MyProperty()
        {
            return m_myProperty;
        }

        void MyProperty(int32_t value)
        {
            m_myProperty = value;
        }
    };
}

namespace winrt::RuntimeComponent1::factory_implementation
{
    struct Class : ClassT<Class, implementation::Class>
    {
    };
}
