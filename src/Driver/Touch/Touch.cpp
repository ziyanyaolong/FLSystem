#include "Touch.h"

FLSYSTEM::Touch::Touch()
{
}

FLSYSTEM::Touch::~Touch()
{
}

// bool FLSYSTEM::Touch::installTouch()
// {
//     if (touch == nullptr)
//         touch = new TouchUpdate(27, 4, 15, 14, 300);
//     lv_indev_drv_init(&touchIndevDrv);
//     touchIndevDrv.type = LV_INDEV_TYPE_POINTER;
//     touchIndevDrv.read_cb = FLSYSTEM::Touch::TouchInputRead;
//     touchIndev = lv_indev_drv_register(&touchIndevDrv);
// }

// void FLSYSTEM::Touch::TouchInputRead(lv_indev_drv_t *drv, lv_indev_data_t *data)
// {
//     MPoint tempXYZ = FLSYSTEM::Touch::touch->getComTouch();
//     // if(tempXYZ.z != 0)
//     // {
//     // Serial.print("X=");
//     // Serial.println(tempXYZ.x);
//     // Serial.print("Y=");
//     // Serial.println(tempXYZ.y);
//     // Serial.print("Z=");
//     // Serial.println(tempXYZ.z);
//     // }
//     // Serial.printf("x:%d,y:%d,z:%d\n", tempXYZ.x, tempXYZ.y, tempXYZ.z);
//     if (tempXYZ.x < 0)
//         tempXYZ.x = 0;
//     else if (tempXYZ.x > 480)
//         tempXYZ.x = 480;
//     if (tempXYZ.y < 0)
//         tempXYZ.y = 0;
//     else if (tempXYZ.y > 320)
//         tempXYZ.y = 320;
//     data->point.x = tempXYZ.x;
//     data->point.y = tempXYZ.y;
//     if (tempXYZ.z >= 200)
//     {
//         // data->state = LV_INDEV_STATE_REL;
//         data->state = LV_INDEV_STATE_PRESSED;
//     }
//     else
//     {
//         data->state = LV_INDEV_STATE_RELEASED;
//         // data->state = LV_INDEV_STATE_PR;
//     }
//     // data->state = LV_INDEV_STATE_PR or LV_INDEV_STATE_REL;
// }