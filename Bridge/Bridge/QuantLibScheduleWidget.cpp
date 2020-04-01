#include "stdafx.h"
#include "QuantLibScheduleWidget.h"

QuantLibScheduleWidget::QuantLibScheduleWidget(QString objectName, QWidget *parent) :
    QDialog(parent)
{
    effectiveDate = new QDateEdit();

    terminationDate = new QDateEdit();

    tenorFrequency = new QComboBox();
    tenorFrequency->addItem("Annual");
    tenorFrequency->addItem("Semiannual");
    tenorFrequency->addItem("Quarterly");
    tenorFrequency->addItem("Monthly");

    unitedStatesCalendarMarket = new QComboBox();
    unitedStatesCalendarMarket->addItem("NYSE");
    unitedStatesCalendarMarket->addItem("GovernmentBond");

    convention = new QComboBox();
    convention->addItem("Following");
    convention->addItem("ModifiedFollowing");
    convention->addItem("Preceding");

    terminationDateConvention = new QComboBox();
    terminationDateConvention->addItem("Following");
    terminationDateConvention->addItem("ModifiedFollowing");
    terminationDateConvention->addItem("Preceding");

    rule = new QComboBox();
    rule->addItem("Backward");
    rule->addItem("Forward");

    endOfMonth = new QCheckBox();

    mainLayout = new QGridLayout();
    mainLayout->addWidget(new QLabel("Effective Date:"), 0, 0);
    mainLayout->addWidget(effectiveDate, 0, 1);
    mainLayout->addWidget(new QLabel("Termination Date:"), 1, 0);
    mainLayout->addWidget(terminationDate, 1, 1);
    mainLayout->addWidget(new QLabel("Tenor:"), 2, 0);
    mainLayout->addWidget(tenorFrequency, 2, 1);
    mainLayout->addWidget(new QLabel("US Calendar Market:"), 3, 0);
    mainLayout->addWidget(unitedStatesCalendarMarket, 3, 1);
    mainLayout->addWidget(new QLabel("Convention:"), 4, 0);
    mainLayout->addWidget(convention, 4, 1);
    mainLayout->addWidget(new QLabel("Termination Date Convention:"), 5, 0);
    mainLayout->addWidget(terminationDateConvention, 5, 1);
    mainLayout->addWidget(new QLabel("Rule:"), 6, 0);
    mainLayout->addWidget(rule, 6, 1);
    mainLayout->addWidget(new QLabel("End Of Month:"), 7, 0);
    mainLayout->addWidget(endOfMonth, 7, 1);

    setLayout(mainLayout);
    setWindowTitle(QString("Schedule (%1)").arg(objectName));
    resize(300, 500);
}

QuantLib::Date QuantLibScheduleWidget::getEffectiveDate() const
{
    auto date = effectiveDate->date();
    return QuantLib::Date(QuantLib::Day(date.day()),
        QuantLib::Month(date.month()),
        QuantLib::Year(date.year()));
}

QuantLib::Date QuantLibScheduleWidget::getTerminationDate() const
{
    auto date = terminationDate->date();
    return QuantLib::Date(QuantLib::Day(date.day()),
        QuantLib::Month(date.month()),
        QuantLib::Year(date.year()));
}

QuantLib::Period QuantLibScheduleWidget::getTenor() const
{
    std::map<std::string, QuantLib::Frequency> frequencyMap = {
        {"Annual", QuantLib::Frequency::Annual},
        {"Semiannual", QuantLib::Frequency::Semiannual},
        {"Quarterly", QuantLib::Frequency::Quarterly},
        {"Monthly", QuantLib::Frequency::Monthly}
    };

    auto frequency = frequencyMap[tenorFrequency->currentText().toStdString()];
    return QuantLib::Period(frequency);
}

QuantLib::Calendar QuantLibScheduleWidget::getCalendar() const
{
    std::map<std::string, QuantLib::UnitedStates::Market> marketMap = {
        {"NYSE", QuantLib::UnitedStates::Market::NYSE},
        {"GovernmentBond", QuantLib::UnitedStates::Market::GovernmentBond}
    };

    auto market = marketMap[unitedStatesCalendarMarket->currentText().toStdString()];

    return QuantLib::UnitedStates(market);
}

QuantLib::BusinessDayConvention QuantLibScheduleWidget::getConvention() const
{
    std::map<std::string, QuantLib::BusinessDayConvention> conventionMap = {
        {"Following", QuantLib::BusinessDayConvention::Following},
        {"ModifiedFollowing", QuantLib::BusinessDayConvention::ModifiedFollowing},
        {"Preceding", QuantLib::BusinessDayConvention::Preceding}
    };

    return conventionMap[convention->currentText().toStdString()];
}

QuantLib::BusinessDayConvention QuantLibScheduleWidget::getTerminationDateConvention() const
{
    std::map<std::string, QuantLib::BusinessDayConvention> conventionMap = {
        {"Following", QuantLib::BusinessDayConvention::Following},
        {"ModifiedFollowing", QuantLib::BusinessDayConvention::ModifiedFollowing},
        {"Preceding", QuantLib::BusinessDayConvention::Preceding}
    };

    return conventionMap[terminationDateConvention->currentText().toStdString()];
}

QuantLib::DateGeneration::Rule QuantLibScheduleWidget::getRule() const
{
    std::map<std::string, QuantLib::DateGeneration::Rule> ruleMap = {
        {"Backward", QuantLib::DateGeneration::Backward},
        {"Forward", QuantLib::DateGeneration::Forward}
    };

    return ruleMap[terminationDateConvention->currentText().toStdString()];
}

bool QuantLibScheduleWidget::getEndOfMonth() const
{
    return endOfMonth->isChecked();
}
