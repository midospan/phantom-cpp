/* TODO LICENCE HERE */

/* ******************* Includes ****************** */
#include "phantom/phantom.h"
/* ** The Class Header must be the last #include * */
#include "RootClass.h"
#if o__int__reflection_template_use_level != 3
#include "RootClass.hxx"
#endif
#include "phantom/vector.hxx"
#include "phantom/map.hxx"
/* *********************************************** */
o_registerN((unitest), RootClass);
o_registerNTI((phantom), vector, (unitest::RootClass*));
o_registerNTI((phantom), map, (int, unitest::RootClass*));

o_namespace_begin(unitest)

RootClass* RootClass::m_pStaticDataMember = NULL;

RootClass::RootClass( void )
: m_fMultAcc(1.f)
{ 
    o_dynamic_delete (phantom::constant<int>(2));
}

o_namespace_end(unitest)

#if 0


class Character
{
public:
    Character() : mLifePoints(10), mX(0), mY(0) {}

    void setX(float x) { mX = x; }
    void setY(float y) { mY = y; }
    float getX() const { return mX; }
    float getY() const { return mY; }

protected:
    int mLifePoints;
    float mX;
    float mY;
};

enum EPlayer
{
    player1,
    player2,
};

class Hero : public Character 
{
public:
    Hero(EPlayer player) : mPlayer(player) {} 

    void setPlayer(EPlayer player) { mPlayer = player; }
    EPlayer getPlayer() const { return mPlayer; }

protected:
    EPlayer mPlayer;
};

class Enemy : public Character
{
public:
    enum EType { tiny, small, big, boss };
    Enemy() : mType(tiny) {}

    void setType(EType type) { mType = type; }
    EType getType() const { return mType; }

protected:
    EType mType;
};

o_class(Character)
(
o_public:
    o_property(float, x, setX, getX);
    o_property(float, y, setY, getY);

o_protected:
    o_data_member(int, mLifePoints);
    o_data_member(float,  mX);
    o_data_member(float, mY);
);

o_enum(EPlayer)
(
    player1,
    player2
);

o_classB(Hero, (Character))
(
o_public: 
    o_property(EPlayer, player, setPlayer, getPlayer);

o_protected:
    o_data_member(EPlayer, mPlayer);
);

o_declareC((Enemy), EType);

o_classB(Enemy, (Character))
(
o_public:
    o_property(EType, Type, setType, getType);

o_protected:
    o_data_member(EType, mType);
);

o_enumC((Enemy), EType) ( tiny, small, big, boss );



o_register(Character);
o_register(EPlayer);
o_register(Hero);
o_register(Enemy);
o_registerC((Enemy), EType);


class CharacterWidget : public QWidget
{
    Q_OBJECT
 
public:
    CharacterWidget()
        : m_pCharacter(nullptr)
    {
        QFormLayout* pLayout = new QFormLayout;
        setLayout(pLayout);
        pLayout->addRow("mX", m_pEditor_mX = new QSpinBox);
        pLayout->addRow("mY", m_pEditor_mY = new QSpinBox);
        connect(m_pEditor_mX, SIGNAL(valueChanged(float)), this, SLOT(mXChanged(float)));
        connect(m_pEditor_mY, SIGNAL(valueChanged(float)), this, SLOT(mYChanged(float)));
    }

    void setCharacter(Character* a_pCharacter) 
    {
        if(m_pCharacter == a_pCharacter) return;
        m_pCharacter = a_pCharacter; 
        if(m_pCharacter)
        {
            m_pEditor_mX->setValue(m_pCharacter->getX());
            m_pEditor_mY->setValue(m_pCharacter->getY());
        }
    }

protected slots:
    void mXChanged(float a_Value) { if(m_pCharacter) m_pCharacter->setX(a_Value); }
    void mYChanged(float a_Value) { if(m_pCharacter) m_pCharacter->setY(a_Value); }

protected:
    Character* m_pCharacter;
    QSpinBox* m_pEditor_mX;
    QSpinBox* m_pEditor_mY;
};

class PlayerComboBox : public QComboBox
{
    Q_OBJECT

public:
    PlayerComboBox() 
    {
        addItem("player1", player1);
        addItem("player2", player2);
        connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(indexChanged(int)));
    }

    void setValue(EPlayer player) 
    {
        setCurrentIndex(player);
    }

    EPlayer getValue() const { return (EPlayer)currentIndex(); }

protected slots:
    void indexChanged(int index) { emit playerSelected((EPlayer)index); }

signals:
    void playerSelected(EPlayer);
};


class EnemyTypeComboBox : public QComboBox
{
    Q_OBJECT

public:
    EnemyTypeComboBox() 
    {
        addItem("tiny", Enemy::tiny);
        addItem("small", Enemy::small);
        addItem("big", Enemy::big);
        addItem("boss", Enemy::boss);
        connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(indexChanged(int)));
    }

    void setEnemyType(Enemy::EType a_eType) 
    {
        setCurrentIndex(a_eType);
    }

    Enemy::EType getValue() const { return (Enemy::EType)currentIndex(); }

protected slots:
    void indexChanged(int index) { emit enemyTypeSelected((Enemy::EType)index); }

signals:
    void enemyTypeSelected(Enemy::EType);
};

class EnemyWidget : public QWidget
{
    Q_OBJECT

public:
    EnemyWidget() 
        : m_pEnemy(nullptr)
    {
        QVBoxLayout* pLayout = new QVBoxLayout;
        setLayout(pLayout);
        QFormLayout* pFormLayout = new QFormLayout;
        pLayout->addLayout(pFormLayout);
        pFormLayout->addRow("mType", m_pEditor_mType = new EnemyTypeComboBox);
        pLayout->addWidget(m_pCharacterWidget = new CharacterWidget);
        connect(m_pEditor_mType, SIGNAL(enumValueChanged(Enemy::EType)), this, SLOT(mTypeChanged(Enemy::EType)));
    }

    void setEnemy(Enemy* a_pEnemy) 
    {
        if(m_pEnemy == a_pEnemy) return;
        m_pEnemy = a_pEnemy;
        m_pCharacterWidget->setCharacter(a_pEnemy);
        if(m_pEnemy)
        {
            m_pEditor_mType->setValue(m_pEnemy->getType());
        }
    }

protected slots:
    void mTypeChanged(Enemy::EType a_eType) { if(m_pEnemy) m_pEnemy->setType(a_eType); }

protected:
    Enemy* m_pEnemy;
    EnemyTypeComboBox* m_pEditor_mType;
    CharacterWidget* m_pCharacterWidget;
};

class FloatEditor : public QSpinBox
{
    Q_OBJECT

public:
    FloatEditor(void* a_pObject, phantom::reflection::Property* a_pProperty)
        : m_pObject(a_pObject)
        , m_pProperty(a_pProperty)
    {
        float fValue = 0.f;
        m_pProperty->getValue(a_pObject, &fValue);
        setValue(fValue);
        connect(this, SIGNAL(valueChanged(float)), this, SLOT(floatValueChanged(float)));
    }

protected slots:
    void floatValueChanged(float a_fValue) 
    {
        m_pProperty->setValue(m_pObject, &a_fValue); 
    }

protected:
    void* m_pObject;
    phantom::reflection::Property* m_pProperty;
};

class EnumEditor : public QComboBox
{
    Q_OBJECT

public:
    EnumEditor(void* a_pObject, phantom::reflection::Property* a_pProperty)
        : m_pObject(a_pObject)
        , m_pProperty(a_pProperty)
    {
        phantom::reflection::Enum* pEnum = a_pProperty->getValueType()->asEnum();
        unsigned long long ullTempValue; // use greatest unsigned integer type as buffer to prevent any enum overflow
        for(auto it = pEnum->beginConstants(); it != pEnum->endConstants(); ++it)
        {
            phantom::reflection::Constant* pConstant = *it;
            pConstant->getValue(&ullTempValue);
            addItem(pConstant->getName().c_str(), ullTempValue); 
        }
        a_pProperty->getValue(a_pObject, &ullTempValue);
        setCurrentValue(ullTempValue);
        connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(enumValueSelected(int)));
    }

    void setCurrentValue(unsigned long long a_ullValue)
    {
        setCurrentIndex(findData(a_ullValue));
    }

protected slots:
    void enumValueSelected(int a_uiIndex)
    {
        unsigned long long ullValue = itemData(a_uiIndex).toULongLong();
        a_pProperty->setValue(a_pObject, &ullValue);
    }

protected:
    void* m_pObject;
    phantom::reflection::Property* m_pProperty;
};

class GenericClassEditor : public QWidget
{
    Q_OBJECT

public:
    GenericClassEditor()
        : m_pObject(nullptr)
        , m_pClass(nullptr)
        , m_pLayout(nullptr)
    {
        
    }

    void setObject(void* a_pObject)
    {
        if(m_pObject == a_pObject) return;
        m_pObject = a_pObject;
        if(m_pObject)
        {
            m_pClass = phantom::classOf(a_pObject);
            setLayout(m_pLayout = new QVBoxLayout);
            createContent(m_pObject, m_pClass);
        }
        else 
        {
            setLayout(nullptr);
            m_pClass = nullptr;
            m_pLayout = nullptr;
        }
    }

    QWidget* createPropertyEditor(void* a_pObject, phantom::reflection::Property* a_pProperty)
    {
        switch(a_pProperty->getValueType()->getTypeId())
        {
        case phantom::reflection::e_float:
            return new FloatEditor(a_pObject, a_pProperty);
        case phantom::reflection::e_enum:
            return new EnumEditor(a_pObject, a_pProperty);
        case ... // We only show the editors required for our example
        }
        return nullptr;
    }

    void createContent( void* a_pObject, phantom::reflection::Class* a_pClass)
    {
        QGroupBox* pGroupBox = new QGroupBox(a_pClass->getName());
        m_pLayout->addWidget(pGroupBox);
        QFormLayout* pMembersLayout = new QFormLayout;
        pGroupBox->setLayout(pMembersLayout);

        // For each property in the class, create a specific editor based on property type
        for(auto it = a_pClass->beginProperties(); it != a_pClass->endProperties(); ++it)
        {
            phantom::reflection::Property* pProperty = *it;
            QWidget* pEditor = createPropertyEditor(a_pObject, pProperty);
            if(pEditor)
            {
                pMembersLayout->addRow(pProperty->getName().c_str(), pEditor);
            }
        }

        // Repeat the process recursively for all base classes
        for(size_t i = 0; i<a_pClass->getBaseClassCount(); ++i)
        {
            createContent(a_pClass->baseClassCast(a_pObject, i), a_pClass->getBaseClass(i));
        }
    }

protected:
    QVBoxLayout* m_pLayout;
    void* m_pObject;
    phantom::reflection::Class* m_pClass;
};


#endif