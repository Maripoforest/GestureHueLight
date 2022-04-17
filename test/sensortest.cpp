#define BOOST_TEST_MODULE MAXtests
#include <boost/test/unit_test.hpp>
#include "mlx90640/mlx90640_driver.h"

BOOST_AUTO_TEST_CASE(SENT){
    
    int error = 1;
    MLX90640 mlx90640;
    mlx90640.start();

    for (int i=0;i<768;i++) {
        if (mlx90640.mlx90640To[i] < -100 || mlx90640.mlx90640To[i] > 300) {
            error = 0;
        }
    }
    
    std::cout << error << std::endl;
    mlx90640.stop();
    BOOST_CHECK_EQUAL(error, 1);

}
