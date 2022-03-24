//#include "UpdateTime.h"
//
//FLSYSTEM::UpdateTime::UpdateTime()
//{
//}
//
//FLSYSTEM::UpdateTime::~UpdateTime()
//{
//}
//
//void FLSYSTEM::UpdateTime::dayFix()
//{
//    unsigned short &nowMonth = timeList[4];
//    if (nowMonth == 2)
//    {
//        if (nowMonth % 4 == 0)
//        {
//            timeListSet(29, 3, 1, true);
//        }
//        else
//        {
//            timeListSet(28, 3, 1, true);
//        }
//    }
//    else if ((nowMonth == 1) || (nowMonth == 3) || (nowMonth == 5) || (nowMonth == 7) || (nowMonth == 8) || (nowMonth == 10) || (nowMonth == 11))
//    {
//        timeListSet(31, 3, 1, true);
//    }
//    else
//    {
//        timeListSet(30, 3, 1, true);
//    }
//}
//
//void FLSYSTEM::UpdateTime::timeListSet(std::size_t max, std::size_t indexe, std::size_t reset, bool gain)
//{
//    if (gain && (timeList[indexe] > max))
//    {
//        timeList[indexe] = reset;
//        if (indexe != timeList.size())
//            timeList[indexe + 1] += 1;
//    }
//    else if (!gain && timeList[indexe] >= max)
//    {
//        timeList[indexe] = reset;
//        if (indexe != timeList.size())
//            timeList[indexe + 1] += 1;
//    }
//}
//
//void FLSYSTEM::UpdateTime::update()
//{
//    std::size_t vectorSize = timeList.size();
//    if (vectorSize < 6)
//    {
//        timeList.clear();
//        for (std::size_t i = 0; i < 3; i++)
//        {
//            timeList.push_back(0);
//        }
//        for (std::size_t i = 0; i < 3; i++)
//        {
//            timeList.push_back(1);
//        }
//    }
//    vectorSize = timeList.size();
//    for (std::size_t i = 0; i < vectorSize; i++)
//    {
//        switch (i)
//        {
//        case 0:
//            timeList[i] += 1;
//            timeListSet(60, i);
//            break;
//        case 1:
//            timeListSet(60, i);
//            break;
//        case 2:
//            timeListSet(24, i);
//            break;
//        case 3:
//            dayFix();
//            break;
//        case 4:
//            timeListSet(12, i);
//            break;
//        case 5:
//            break;
//        default:
//            break;
//        }
//    }
//}