#include "System.hpp"

void System::call(ComponentStorage &storage) const
{
    m_call_wrapper(storage);
}
