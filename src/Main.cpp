
#include "MyMain.h"
#include <memory>
#include <thread>
// #include <boost/thread.hpp>


// void process_body() {
//     printf("Starting background process...\n");
//
//
//     printf("Done background process.\n");
// }


int main() {
    MyMain mainObject;

    mainObject.process_start();

    mainObject.video();

    mainObject.process_stop();

    // t.join();
    return 0;
}
