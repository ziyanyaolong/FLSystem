//#ifndef UPDATETIME
//#define UPDATETIME
//
//#include "../../System/SafeSTL/FLVector/FLVector.h"
//
//namespace FLSYSTEM
//{
//    class UpdateTime
//    {
//    private:
//        FLVector<uint16_t> timeList;
//        short vectorSize = -1;
//        void timeListSet(std::size_t max, std::size_t indexe, std::size_t reset = 0, bool gain = false);
//        void dayFix();
//
//    public:
//        void update();
//        
//        const uint16_t &second() { return timeList[0]; }
//        const uint16_t &minute() { return timeList[1]; }
//        const uint16_t &hour() { return timeList[2]; }
//        const uint16_t &day() { return timeList[3]; }
//        const uint16_t &month() { return timeList[4]; }
//        const uint16_t &year() { return timeList[5]; }
//
//        UpdateTime();
//        ~UpdateTime();
//    };
//}
//
//#endif