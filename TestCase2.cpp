#include <doctest/doctest.h>
#include <iostream>
#include <sycl/sycl.hpp>

#include "USMSelector.hpp"

TEST_CASE("Test2")
{
    constexpr size_t num_elements = 1024;

    try
    {
        sycl::queue usm_queue{usm_selector{}};

        auto shared_ptr_a = sycl::malloc_shared<int>(num_elements, usm_queue);
        auto shared_ptr_b = sycl::malloc_shared<int>(num_elements, usm_queue);
        auto shared_ptr_c = sycl::malloc_shared<int>(num_elements, usm_queue);

        for (size_t i = 0; i < num_elements; ++i)
        {
            shared_ptr_a[i] = i;
            shared_ptr_b[i] = i;
        }

        usm_queue
            .parallel_for(sycl::range<1>{num_elements},
                          [=](sycl::id<1> idx)
                          {
                              auto i = idx[0];
                              shared_ptr_c[i] =
                                  shared_ptr_a[i] + 2 * shared_ptr_b[i];
                          })
            .wait_and_throw();

        for (size_t i = 0; i < num_elements; ++i)
        {
            REQUIRE(shared_ptr_c[i] == 3 * i);
        }
    }
    catch (const sycl::exception &e)
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
}