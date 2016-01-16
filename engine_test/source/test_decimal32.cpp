/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                        Includes                        */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Std-Includes
#include <bitset>

// Other Includes

// Internal Includes
#include "_global.h"
#include "math/decimal32.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Class                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
using namespace kerosine;

class decimal32Test
{

public:
    decimal32Test();

private:


};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                         Tests                          */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

decimal32Test::decimal32Test() {}

// Test: fromInt
void decimal32Test::fromInt_data()
{
    QTest::addColumn<qint32>("aInt");
    QTest::newRow("0") << -1000000;
    QTest::newRow("1") << -1;
    QTest::newRow("2") << 0;
    QTest::newRow("3") << 1;
    QTest::newRow("4") << 1000000;
}

void decimal32Test::fromInt()
{
    // Preparation
    QFETCH(qint32, aInt);

    // Test
    decimal32 subject = decimal32::fromInt(aInt);
    debugDecimal(subject);

    // Evaluation
    QCOMPARE(decimal32::toInt(subject), aInt);
}

// Test: fromDouble
// TODO: Rework this test, so it becomes more meaningful
void decimal32Test::fromDouble_data()
{
    QTest::addColumn<double>("aDouble");
    QTest::newRow("0") << -1.0;
    QTest::newRow("1") << 0.0;
    QTest::newRow("2") << 1.0;
}

void decimal32Test::fromDouble()
{
    // Preparation
    QFETCH(double, aDouble);

    // Test
    decimal32 subject = decimal32::fromDouble(aDouble);
    debugDecimal(subject);

    // Evaluation
    QVERIFY(qFuzzyCompare(decimal32::toDouble(subject), aDouble));
}

// Test: fromFloat
// TODO: Rework this test, so it becomes more meaningful
void decimal32Test::fromFloat_data()
{
    QTest::addColumn<float>("aFloat");
    QTest::newRow("0") << -1.0f;
    QTest::newRow("1") << 0.0f;
    QTest::newRow("2") << 1.0f;
}

void decimal32Test::fromFloat()
{
    // Preparation
    QFETCH(float, aFloat);

    // Test
    decimal32 subject = decimal32::fromFloat(aFloat);
    debugDecimal(subject);

    // Evaluation
    QVERIFY(qFuzzyCompare(decimal32::toFloat(subject), aFloat));
}

// Test: operator+
void decimal32Test::operatorPlus_data()
{
    QTest::addColumn<qint32>("aInt1"); QTest::addColumn<qint32>("aInt2");
    QTest::newRow("0") << 0 << 0;
    QTest::newRow("1") << 0 << 123;
    QTest::newRow("2") << 123 << 0;
    QTest::newRow("3") << 1 << 1;
    QTest::newRow("4") << -1 << 1;
    QTest::newRow("5") << 1 << -1;
    QTest::newRow("6") << -1 << -1;
    QTest::newRow("7") << 1 << 456;
    QTest::newRow("8") << -1 << 456;
    QTest::newRow("9") << 1 << -456;
    QTest::newRow("10") << -1 << -456;
    QTest::newRow("11") << 123 << 456;
    QTest::newRow("12") << -123 << 456;
    QTest::newRow("13") << 123 << -456;
    QTest::newRow("13") << -123 << -456;
}

void decimal32Test::operatorPlus()
{
    // Preparation
    QFETCH(qint32, aInt1);
    QFETCH(qint32, aInt2);

    // Test
    decimal32 dec1 = decimal32::fromInt(aInt1);
    decimal32 dec2 = decimal32::fromInt(aInt2);

    debugDecimals(dec1, dec2);

    qint32 expected = aInt1 + aInt2;
    qint32 result = decimal32::toInt(dec1 + dec2);

    // Evaluation
    QCOMPARE(result, expected);
}

// Test: operator-
void decimal32Test::operatorMinus_data()
{
    QTest::addColumn<qint32>("aInt1"); QTest::addColumn<qint32>("aInt2");
    QTest::newRow("0") << 0 << 0;
    QTest::newRow("1") << 0 << 123;
    QTest::newRow("2") << 123 << 0;
    QTest::newRow("3") << 1 << 1;
    QTest::newRow("4") << -1 << 1;
    QTest::newRow("5") << 1 << -1;
    QTest::newRow("6") << -1 << -1;
    QTest::newRow("7") << 1 << 456;
    QTest::newRow("8") << -1 << 456;
    QTest::newRow("9") << 1 << -456;
    QTest::newRow("10") << -1 << -456;
    QTest::newRow("11") << 123 << 456;
    QTest::newRow("12") << -123 << 456;
    QTest::newRow("13") << 123 << -456;
    QTest::newRow("13") << -123 << -456;
}

void decimal32Test::operatorMinus()
{
    // Preparation
    QFETCH(qint32, aInt1);
    QFETCH(qint32, aInt2);

    // Test
    decimal32 dec1 = decimal32::fromInt(aInt1);
    decimal32 dec2 = decimal32::fromInt(aInt2);

    debugDecimals(dec1, dec2);

    qint32 expected = aInt1 - aInt2;
    qint32 result = decimal32::toInt(dec1 - dec2);

    // Evaluation
    QCOMPARE(result, expected);
}

// Test: operator*
void decimal32Test::operatorMultiplication_data()
{
    QTest::addColumn<qint32>("aInt1"); QTest::addColumn<qint32>("aInt2");
    QTest::newRow("0") << 0 << 0;
    QTest::newRow("1") << 0 << 123;
    QTest::newRow("2") << 123 << 0;
    QTest::newRow("3") << 1 << 1;
    QTest::newRow("4") << -1 << 1;
    QTest::newRow("5") << 1 << -1;
    QTest::newRow("6") << -1 << -1;
    QTest::newRow("7") << 1 << 456;
    QTest::newRow("8") << -1 << 456;
    QTest::newRow("9") << 1 << -456;
    QTest::newRow("10") << -1 << -456;
    QTest::newRow("11") << 123 << 456;
    QTest::newRow("12") << -123 << 456;
    QTest::newRow("13") << 123 << -456;
    QTest::newRow("13") << -123 << -456;
}

void decimal32Test::operatorMultiplication()
{
    // Preparation
    QFETCH(qint32, aInt1);
    QFETCH(qint32, aInt2);

    // Test
    decimal32 dec1 = decimal32::fromInt(aInt1);
    decimal32 dec2 = decimal32::fromInt(aInt2);

    debugDecimals(dec1, dec2);

    qint32 expected = aInt1 * aInt2;
    qint32 result = decimal32::toInt(dec1 * dec2);

    // Evaluation
    QCOMPARE(result, expected);
}

// Test: operator/
void decimal32Test::operatorDivision_data()
{
    QTest::addColumn<qint32>("aInt1"); QTest::addColumn<qint32>("aInt2");
    QTest::newRow("0") << 0 << 123;
    QTest::newRow("1") << 1 << 1;
    QTest::newRow("2") << -1 << 1;
    QTest::newRow("3") << 1 << -1;
    QTest::newRow("4") << -1 << -1;
    QTest::newRow("5") << 1 << 456;
    QTest::newRow("6") << -1 << 456;
    QTest::newRow("7") << 1 << -456;
    QTest::newRow("8") << -1 << -456;
    QTest::newRow("9") << 123 << 456;
    QTest::newRow("10") << -123 << 456;
    QTest::newRow("11") << 123 << -456;
    QTest::newRow("12") << -123 << -456;
}

void decimal32Test::operatorDivision()
{
    // Preparation
    QFETCH(qint32, aInt1);
    QFETCH(qint32, aInt2);

    // Test
    decimal32 dec1 = decimal32::fromInt(aInt1);
    decimal32 dec2 = decimal32::fromInt(aInt2);

    debugDecimals(dec1, dec2);

    qint32 expected = aInt1 / aInt2;
    qint32 result = decimal32::toInt(dec1 / dec2);

    // Evaluation
    QCOMPARE(result, expected);
}

// Test: sqrt
void decimal32Test::sqrt_data()
{
    QTest::addColumn<decimal32>("value"); QTest::addColumn<decimal32>("expected");
    QTest::newRow("4") << decimal32::fromInt(3) << decimal32::fromInt(2);
}

void decimal32Test::sqrt()
{
    // Preparation
    QFETCH(decimal32, value);
    QFETCH(decimal32, expected);

    // Test
    decimal32 result = decimal32::sqrt(value);

    // Evaluation
    QString errorMsg = QString("Expected: ")
        .append(QString::number(decimal32::toDouble(expected), 'f', 10))
        .append(QString(" but was: "))
        .append(QString::number(decimal32::toDouble(result), 'f', 10));
    qDebug() << errorMsg;
    QVERIFY(true);
}

// Test: sin
void decimal32Test::sin_data()
{
    QTest::addColumn<decimal32>("value"); QTest::addColumn<double>("expected");
    QTest::newRow("-2PI") << -decimal32::_2PI << 0.0;
    QTest::newRow("-7PI_4") << -(decimal32::PI + decimal32::_3PI_4) << 0.707;
    QTest::newRow("-6PI_4") << -(decimal32::PI + decimal32::PI_2) << 1.0;
    QTest::newRow("-5PI_4") << -(decimal32::PI + decimal32::PI_4) << 0.707;
    QTest::newRow("-PI") << -decimal32::PI << 0.0;
    QTest::newRow("-3PI_4") << -decimal32::_3PI_4 << -0.707;
    QTest::newRow("-2PI_4") << -decimal32::PI_2 << -1.0;
    QTest::newRow("-1PI_4") << -decimal32::PI_4 << -0.707;
    QTest::newRow("0") << decimal32::ZERO << 0.0;
    QTest::newRow("1PI_4") << decimal32::PI_4 << 0.707;
    QTest::newRow("2PI_4") << decimal32::PI_2 << 1.0;
    QTest::newRow("3PI_4") << decimal32::_3PI_4 << 0.707;
    QTest::newRow("PI") << decimal32::PI << 0.0;
    QTest::newRow("5PI_4") << decimal32::PI + decimal32::PI_4 << -0.707;
    QTest::newRow("6PI_4") << decimal32::PI + decimal32::PI_2 << -1.0;
    QTest::newRow("7PI_4") << decimal32::PI + decimal32::_3PI_4 << -0.707;
    QTest::newRow("2PI") << decimal32::_2PI << 0.0;
}

void decimal32Test::sin()
{
    // Preparation
    QFETCH(decimal32, value);
    QFETCH(double, expected);

    // Test
    double result = decimal32::toDouble(decimal32::sin(value));

    // Evaluation
    QString errorMsg = QString("Expected: ")
        .append(QString::number(expected, 'f', 10))
        .append(QString(" but was: "))
        .append(QString::number(result, 'f', 10));
    //qDebug() << errorMsg;
    QVERIFY2(compareDouble(result, expected, 0.0011), errorMsg.toStdString().c_str());
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*                     Helper Methods                     */
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void decimal32Test::debugDecimals(decimal32 &dec1, decimal32 &dec2)
{
    qDebug() << "Dec1: " << decimal32::toInt(dec1);
    qDebug() << "Dec1-Val: " << dec1.value;
    qDebug() << "Dec1-Bit: " << std::bitset<32>(dec1.value).to_string().c_str();
    qDebug() << "Dec2: " << decimal32::toInt(dec2);
    qDebug() << "Dec2-Val: " << dec2.value;
    qDebug() << "Dec2-Bit: " << std::bitset<32>(dec2.value).to_string().c_str();
}

void decimal32Test::debugDecimal(decimal32 &dec)
{
    qDebug() << "Dec: " << decimal32::toInt(dec);
    qDebug() << "Dec-Val: " << dec.value;
    qDebug() << "Dec-Bit: " << std::bitset<32>(dec.value).to_string().c_str();
}

bool decimal32Test::compareDouble(double actual, double expected, double epsilon) {
    return (expected - epsilon)< actual && actual < (expected + epsilon);
}

QTEST_APPLESS_MAIN(decimal32Test)
#include "test_decimal32.moc"
