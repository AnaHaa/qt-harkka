#ifndef HOLIDAY_H
#define HOLIDAY_H

#include <QString>

// Holiday class
// Used by the main program to create custom variables
// in the main program interface
class Holiday {
public:
    Holiday(QString inputLocation, QString inputWeather, int inputRating, QString desc);
    QString location;
    QString weather;
    int rating;
    QString desc;
};

#endif // HOLIDAY_H
