#include "holiday.h"

Holiday::Holiday(QString inputLocation, QString inputWeather, int inputRating, QString inputDesc) {
    // Create the custom holiday class with input
    location = inputLocation;
    weather = inputWeather;
    rating = inputRating;
    desc = inputDesc;
}
