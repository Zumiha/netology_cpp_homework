#include <iostream>

enum monthNum
{
    jan = 1,
    feb,
    mar,
    apr,
    may,
    jun,
    jul,
    aug,
    sep,
    oct,
    nov,
    dec
};

void displMonth(const monthNum inp_month)
{
    std::string monthName;

    switch (inp_month)
    {
        case monthNum::jan:
            monthName = "Январь";
            break;
        case monthNum::feb:
            monthName = "Февраль";
            break;
        case monthNum::mar:
            monthName = "Март";
            break;
        case monthNum::apr:
            monthName = "Апрель";
            break;
        case monthNum::may:
            monthName = "Май";
            break;
        case monthNum::jun:
            monthName = "Июнь";
            break;
        case monthNum::jul:
            monthName = "Июль";
            break;
        case monthNum::aug:
            monthName = "Август";
            break;
        case monthNum::sep:
            monthName = "Сентябрь";
            break;
        case monthNum::oct:
            monthName = "Октябрь";
            break;
        case monthNum::nov:
            monthName = "Ноябрь";
            break;
        case monthNum::dec:
            monthName = "Декабрь";
            break;
        default:
            monthName = "Неправильный номер!";
            break;
    }

    std::cout << monthName << std::endl;
}

int main()
{
    int user_month = 0;

    do
    {
        std::cout << "Введите номер месяца: ";
        std::cin >> user_month;
        if (!(0 == user_month))
            {
                displMonth(static_cast<monthNum>(user_month));
            }
    } while (!(0 == user_month));

    std::cout << "До Свидания!";
    
    return 0;
}