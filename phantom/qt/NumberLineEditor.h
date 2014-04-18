#ifndef phantom_qt_NumberLineEditor_h__
#define phantom_qt_NumberLineEditor_h__


/* ****************** Includes ******************* */
#include <phantom/qt/VariableWidgetEditor.h>
#include <QLongLongValidator.h>
#include <QLineEdit.h>
/* **************** Declarations ***************** */
class QWidget;
o_declareN(class, (phantom, qt), NumberLineEditor);
o_declareNT(class, (phantom, qt), (typename), (Ty), TNumberLineEditor);
/* *********************************************** */

namespace phantom { namespace qt {

class o_qt_export NumberLineEditor : public VariableWidgetEditor
{
public:
    NumberLineEditor(reflection::Type* a_pType);
};

template<typename t_Ty>
struct TNumberLineEditorStringHelper;

template<>
struct TNumberLineEditorStringHelper<char>
{
    static char number(const QString& str) { return *(str.toAscii().constData()); }
};

template<>
struct TNumberLineEditorStringHelper<unsigned char>
{
    static unsigned char number(const QString& str) { return (unsigned char)*(str.toAscii().constData()); }
};

template<>
struct TNumberLineEditorStringHelper<short>
{
    static short number(const QString& str) { return str.toShort(); }
};

template<>
struct TNumberLineEditorStringHelper<unsigned short>
{
    static unsigned short number(const QString& str) { return str.toUShort(); }
};

template<>
struct TNumberLineEditorStringHelper<int>
{
    static int number(const QString& str) { return str.toInt(); }
};

template<>
struct TNumberLineEditorStringHelper<unsigned int>
{
    static unsigned int number(const QString& str) { return str.toUInt(); }
};

template<>
struct TNumberLineEditorStringHelper<long>
{
    static long number(const QString& str) { return str.toLong(); }
};

template<>
struct TNumberLineEditorStringHelper<unsigned long>
{
    static unsigned long number(const QString& str) { return str.toULong(); }
};

template<>
struct TNumberLineEditorStringHelper<long long>
{
    static long long number(const QString& str) { return str.toLongLong(); }
};

template<>
struct TNumberLineEditorStringHelper<unsigned long long>
{
    static unsigned long long number(const QString& str) { return str.toULongLong(); }
};

template<>
struct TNumberLineEditorStringHelper<float>
{
    static float number(const QString& str) { return str.toFloat(); }
};

template<>
struct TNumberLineEditorStringHelper<double>
{
    static double number(const QString& str) { return str.toDouble(); }
};

template<typename t_Ty, bool unsigned_integral>
struct TNumberLineEditorValidorCreatorHelper
{
    static QValidator* create(QObject* a_pParent, reflection::Range* a_pRange = nullptr)
    {
        t_Ty min = std::numeric_limits<t_Ty>::min();
        t_Ty max = std::numeric_limits<t_Ty>::max();
        if(a_pRange)
        {
            a_pRange->getMin(&min);
            a_pRange->getMax(&max);
        }
        return new QULongLongValidator(min, max, a_pParent);
    }
};

template<typename t_Ty>
struct TNumberLineEditorValidorCreatorHelper<t_Ty, false>
{
    static QValidator* create(QObject* a_pParent, reflection::Range* a_pRange = nullptr)
    {
        t_Ty min = std::numeric_limits<t_Ty>::min();
        t_Ty max = std::numeric_limits<t_Ty>::max();
        if(a_pRange)
        {
            a_pRange->getMin(&min);
            a_pRange->getMax(&max);
        }
        return new QLongLongValidator(min, max, a_pParent);
    }
};

template<typename t_Ty>
struct TNumberLineEditorValidorCreator : TNumberLineEditorValidorCreatorHelper<t_Ty, boost::is_unsigned<t_Ty>::value>
{
    
};

template<>
struct TNumberLineEditorValidorCreator<float>
{
    static QValidator* create(QObject* a_pParent, reflection::Range* a_pRange = nullptr)
    {
        float min = std::numeric_limits<float>::lowest();
        float max = std::numeric_limits<float>::max();
        if(a_pRange)
        {
            a_pRange->getMin(&min);
            a_pRange->getMax(&max);
        }
        return new QDoubleValidator();
    }
};

template<>
struct TNumberLineEditorValidorCreator<double>
{
    static QValidator* create(QObject* a_pParent, reflection::Range* a_pRange = nullptr)
    {
        double min = std::numeric_limits<double>::lowest();
        double max = std::numeric_limits<double>::max();
        if(a_pRange)
        {
            a_pRange->getMin(&min);
            a_pRange->getMax(&max);
        }
        return new QDoubleValidator(min, max, 3, a_pParent);
    }
};

template<>
struct TNumberLineEditorValidorCreator<int>
{
    static QValidator* create(QObject* a_pParent, reflection::Range* a_pRange = nullptr)
    {
        double min = std::numeric_limits<int>::min();
        double max = std::numeric_limits<double>::max();
        if(a_pRange)
        {
            a_pRange->getMin(&min);
            a_pRange->getMax(&max);
        }
        return new QDoubleValidator(min, max, 3, a_pParent);
    }
};

template<>
struct TNumberLineEditorValidorCreator<long long>
{
    static QValidator* create(QObject* a_pParent, reflection::Range* a_pRange = nullptr)
    {
        long long min = std::numeric_limits<long long>::min();
        long long max = std::numeric_limits<long long>::max();
        if(a_pRange)
        {
            a_pRange->getMin(&min);
            a_pRange->getMax(&max);
        }
        return new QLongLongValidator(min, max, a_pParent);
    }
};

template<>
struct TNumberLineEditorValidorCreator<unsigned long long>
{
    static QValidator* create(QObject* a_pParent, reflection::Range* a_pRange = nullptr)
    {
        unsigned long long min = std::numeric_limits<unsigned long long>::min();
        unsigned long long max = std::numeric_limits<unsigned long long>::max();
        if(a_pRange)
        {
            a_pRange->getMin(&min);
            a_pRange->getMax(&max);
        }
        return new QULongLongValidator(min, max, a_pParent);
    }
};

template<typename t_Ty>
class TNumberLineEditor : public NumberLineEditor
{
public:
    TNumberLineEditor()
        : NumberLineEditor(typeOf<t_Ty>())
    {
        ((QLineEdit*)m_pWidget)->setValidator(TNumberLineEditorValidorCreator<t_Ty>::create(m_pWidget, nullptr));
    }
    virtual void setValue(const void* a_pSrc) const
    {
        t_Ty value = *((t_Ty*)a_pSrc);
        ((QLineEdit*)m_pWidget)->setText(QString::number(value, boost::is_floating_point<t_Ty>::value ? 'f' : 'g', 3));
    }
    virtual void getValue(void* a_pDest) const
    {
        *((t_Ty*)a_pDest) = TNumberLineEditorStringHelper<t_Ty>::number(((QLineEdit*)m_pWidget)->text());
    }

    void variableChanged(reflection::Variable* a_pVariable)
    {
        VariableWidgetEditor::variableChanged(a_pVariable);
        if(a_pVariable->getRange())
        {
            ((QLineEdit*)m_pWidget)->setValidator(TNumberLineEditorValidorCreator<t_Ty>::create(m_pWidget, a_pVariable->getRange()));
        }
    }
};

}}

#endif // phantom_qt_NumberLineEditor_h__