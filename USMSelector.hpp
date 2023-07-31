#ifndef USM_SELECTOR_HPP_
#define USM_SELECTOR_HPP_

#include <sycl/sycl.hpp>

class usm_selector
{
  public:
    int operator()(const sycl::device &dev) const
    {
        if (dev.has(sycl::aspect::usm_device_allocations))
        {
            if (dev.has(sycl::aspect::gpu))
                return 2;
            return 1;
        }
        return -1;
    }
};

#endif //USM_SELECTOR_HPP_