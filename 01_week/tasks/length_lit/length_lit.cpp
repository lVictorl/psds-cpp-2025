#include <cmath>

// Константы преобразования
constexpr double FEET_TO_METERS = 0.3048;
constexpr double INCHES_TO_METERS = 0.0254;
constexpr double METERS_TO_FEET = 1.0 / FEET_TO_METERS;
constexpr double METERS_TO_INCHES = 1.0 / INCHES_TO_METERS;
constexpr double FEET_TO_INCHES = 12.0;
constexpr double INCHES_TO_FEET = 1.0 / FEET_TO_INCHES;
constexpr double METERS_TO_CM = 100.0;
constexpr double CM_TO_METERS = 0.01;

// Футы в другие единицы
constexpr double operator"" _ft_to_m(long double feet)
{
    return feet * FEET_TO_METERS;
}

constexpr double operator"" _ft_to_cm(long double feet)
{
    return feet * FEET_TO_METERS * METERS_TO_CM;
}

constexpr double operator"" _ft_to_in(long double feet)
{
    return feet * FEET_TO_INCHES;
}

// Дюймы в другие единицы
constexpr double operator"" _in_to_m(long double inches)
{
    return inches * INCHES_TO_METERS;
}

constexpr double operator"" _in_to_cm(long double inches)
{
    return inches * INCHES_TO_METERS * METERS_TO_CM;
}

constexpr double operator"" _in_to_ft(long double inches)
{
    return inches * INCHES_TO_FEET;
}

// Метры в другие единицы
constexpr double operator"" _m_to_ft(long double meters)
{
    return meters * METERS_TO_FEET;
}

constexpr double operator"" _m_to_in(long double meters)
{
    return meters * METERS_TO_INCHES;
}

constexpr double operator"" _m_to_cm(long double meters)
{
    return meters * METERS_TO_CM;
}

// Сантиметры в другие единицы
constexpr double operator"" _cm_to_m(long double centimeters)
{
    return centimeters * CM_TO_METERS;
}

constexpr double operator"" _cm_to_ft(long double centimeters)
{
    return centimeters * CM_TO_METERS * METERS_TO_FEET;
}

constexpr double operator"" _cm_to_in(long double centimeters)
{
    return centimeters * CM_TO_METERS * METERS_TO_INCHES;
}

// Перегрузки для целочисленных литералов
constexpr double operator"" _ft_to_m(unsigned long long feet)
{
    return static_cast<double>(feet) * FEET_TO_METERS;
}

constexpr double operator"" _ft_to_cm(unsigned long long feet)
{
    return static_cast<double>(feet) * FEET_TO_METERS * METERS_TO_CM;
}

constexpr double operator"" _ft_to_in(unsigned long long feet)
{
    return static_cast<double>(feet) * FEET_TO_INCHES;
}

constexpr double operator"" _in_to_m(unsigned long long inches)
{
    return static_cast<double>(inches) * INCHES_TO_METERS;
}

constexpr double operator"" _in_to_cm(unsigned long long inches)
{
    return static_cast<double>(inches) * INCHES_TO_METERS * METERS_TO_CM;
}

constexpr double operator"" _in_to_ft(unsigned long long inches)
{
    return static_cast<double>(inches) * INCHES_TO_FEET;
}

constexpr double operator"" _m_to_ft(unsigned long long meters)
{
    return static_cast<double>(meters) * METERS_TO_FEET;
}

constexpr double operator"" _m_to_in(unsigned long long meters)
{
    return static_cast<double>(meters) * METERS_TO_INCHES;
}

constexpr double operator"" _m_to_cm(unsigned long long meters)
{
    return static_cast<double>(meters) * METERS_TO_CM;
}

constexpr double operator"" _cm_to_m(unsigned long long centimeters)
{
    return static_cast<double>(centimeters) * CM_TO_METERS;
}

constexpr double operator"" _cm_to_ft(unsigned long long centimeters)
{
    return static_cast<double>(centimeters) * CM_TO_METERS * METERS_TO_FEET;
}

constexpr double operator"" _cm_to_in(unsigned long long centimeters)
{
    return static_cast<double>(centimeters) * CM_TO_METERS * METERS_TO_INCHES;
}