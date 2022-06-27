// #pragma one

// #include "../../FLSystemConfig.h"
// #include "../../System/API/InterruptAPI/InterruptAPI.h"

// #include <map>
// #include <string>

// namespace FLSYSTEM
// {
//     class Interrupt
//     {
//     private:
//         Interrupt* interrupt;
//         std::map<std::string, InterruptAPI *> list;
//         unsigned long long InterruptTime;
//         Interrupt();
//         ~Interrupt();

//     public:
//         Interrupt* instance() { return interrupt; }
//         static esp_timer_cb_t InterruptRunFunc;
//         bool regInterrupt(InterruptAPI *regData);
//         static void _InterruptRunFunc_(void *data);
// #if defined(FLSYSTEM_ARDUINO_BOARD)

// #elif defined(FLSYSTEM_ESPRESSIF_BOARD)
//     private:
//         esp_timer_handle_t timerHandle;
//         esp_timer_create_args_t timerStruct;

// #elif defined(FLSYSTEM_STM32_BOARD)

// #elif defined(FLSYSTEM_UNKNOW_BOARD)
        
// #endif
//     };
// }