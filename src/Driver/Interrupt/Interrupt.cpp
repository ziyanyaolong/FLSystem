// #include "Interrupt.h"

// esp_timer_cb_t FLSYSTEM::Interrupt::InterruptRunFunc;

// FLSYSTEM::Interrupt::Interrupt()
// {
//     if (list.size() > 0)
//         list.clear();

//     #ifdef FLSYSTEM_ARDUINO_BOARD

// #elif defined(FLSYSTEM_ESPRESSIF_BOARD)
//     if (InterruptRunFunc == nullptr)
//         InterruptRunFunc = &FLSYSTEM::Interrupt::_InterruptRunFunc_;
//     timerStruct.arg = NULL;
//     timerStruct.callback = InterruptRunFunc;
//     timerStruct.name = "Interrupt";
//     esp_err_t err = ESP_OK;
//     err = esp_timer_start_periodic(FLSYSTEM::Interrupt::timerHandle, InterruptTime);
//     if (err != ESP_OK)
//     {
//         esp_timer_stop(timerHandle);
//         esp_timer_delete(timerHandle);
//         throw 0x1;
//     }
//     err = esp_timer_create(&timerStruct, &(FLSYSTEM::Interrupt::timerHandle));
//     if (err != ESP_OK)
//     {
//         esp_timer_stop(timerHandle);
//         esp_timer_delete(timerHandle);
//         throw 0x2;
//     }

// #elif defined(FLSYSTEM_STM32_BOARD)

// #endif
// }

// FLSYSTEM::Interrupt::~Interrupt()
// {
//     if (list.size() > 0)
//         list.clear();
// }

// #if !defined(FLSYSTEM_UNKNOW_BOARD)
// void FLSYSTEM::Interrupt::_InterruptRunFunc_(void *data)
// {
//     FLSYSTEM::Interrupt* interrupt = static_cast<FLSYSTEM::Interrupt*>(data);

//     for (auto &&i : interrupt->list)
//     {
//         i.second->run(i.second->readData());
//     }
// }
// #endif

// bool FLSYSTEM::Interrupt::regInterrupt(InterruptAPI *regData)
// {
//     if (std::find(list.begin(), list.end(), regData) != list.end())
//     {
//         list[regData->readName()] = regData;
//         return true;
//     }
//     return false;
// }