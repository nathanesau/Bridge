#pragma once

#include "stdafx.h"

// a widget describing the "QuantLib::Schedule" class
// https://github.com/lballabio/QuantLib/blob/master/Examples/Bonds/Bonds.cpp
class QuantLibScheduleWidget : public QDialog
{
    QDateEdit* effectiveDate;
    QDateEdit* terminationDate;
    QComboBox* tenorFrequency;
    QComboBox* unitedStatesCalendarMarket;
    QComboBox* convention;
    QComboBox* terminationDateConvention;
    QComboBox* rule;
    QCheckBox* endOfMonth;
    QGridLayout* mainLayout;

public:
    QuantLibScheduleWidget(QString objectName, QWidget* parent = nullptr);

    QuantLib::Date getEffectiveDate() const;
    QuantLib::Date getTerminationDate() const;
    QuantLib::Period getTenor() const;
    QuantLib::Calendar getCalendar() const;
    QuantLib::BusinessDayConvention getConvention() const;
    QuantLib::BusinessDayConvention getTerminationDateConvention() const;
    QuantLib::DateGeneration::Rule getRule() const;
    bool getEndOfMonth() const;
};