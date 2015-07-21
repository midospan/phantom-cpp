**P** reprocessed <br>
<b>H</b> igh-level <br>
<b>A</b> llocators <br>
<b>N</b> ested-state-machine and <br>
<b>T</b> emplate <br>
<b>O</b> riented <br>
<b>M</b> eta-programming<br>
<br>
<h1>Dependencies</h1>
Phantom needs some third part library to work. Inside the phantom projects, some environment variable are defined and must point to the path of some dependencies you need to install and/or build  :<br>
<br>
BOOST <a href='http://boostpro.com/download/boost_1_47_setup.exe'>http://boostpro.com/download/boost_1_47_setup.exe</a>

GOOGLE TEST (for unit test) : <a href='http://googletest.googlecode.com/files/gtest-1.6.0.zip'>http://googletest.googlecode.com/files/gtest-1.6.0.zip</a>

<hr />

<h1>Motivations</h1>
<i>Phantom</i> was born from the desire to make a solid base for a game engine that I develop in parallel (Yamato) and from the statement that C++ misses introspection reflection which is powerful to handle serialization, to create generic/modular UI and a lot of cool things. I also wanted as a software engineer to write secured and predictable code, that's why I've implemented a way to easily integrate allocators (boost ones for example) and a nested state-machine system. This last one is essential to gameplay programming (AI, motion synchronisation, ...). To sum, below are listed what i believe are the requirements needed to implement a good game engine core and gui, and what phantom provides to satisfy these requirements :<br>
<br>
<ul><li><b>Data allocation and object instanciation control</b> -> Extended C++ construction concepts to control over initialization and restoration of persistents objects + Per-type allocator customization<br>
</li><li><b>Introspection for easy property edition</b> -> Introspection reflection system<br>
</li><li><b>Recompilable prototyping script language</b> -> Structural reflection system<br>
</li><li><b>Inter-object dynamic connections and property bindings</b> -> Signal / Slot system + Properties<br>
</li><li><b>Persistent data storage</b> -> Serialization and modular data-base system<br>
</li><li><b>Determinist and robust gameplay behavior</b> -> Nested-State-Machine system</li></ul>

<hr />

<h1>Features</h1>
<h2>Prolog on macro name convention</h2>
Phantom uses it's own names for macros, not following the standard <b>PHANTOM_UPPER_CASE</b> model, but a <b>o_lower_case</b> one. Why ? To be discreet and not disturb the whole apparence of your code and so that the phantom macro look like keywords. The ALL_UPPER_CASE model tend to be very messy and unreadable once there is too much of them stick together.<br>
A sample, would you prefer...<br>
<br>
<pre><code>  PHANTOM_CLASS(...)<br>
  {<br>
    PHANTOM_MEMBER_FUNCTION(..., PHANTOM_PUBLIC|PHANTOM_PURE_VIRTUAL)<br>
    PHANTOM_DATA_MEMBER(..., PHANTOM_TRANSIENT)<br>
  }<br>
</code></pre>

or<br>
<br>
<pre><code>  o_class(...)<br>
  {<br>
    o_member_function(..., o_public|o_pure_virtual)<br>
    o_data_member(..., o_transient)<br>
  }<br>
</code></pre>

To me it was clear that the second one looks pretty lighter and more readable.<br>
<br>
Anyway I plan to make aliases for people prefering keeping their names standards.<br>
<br>
Let's start now !<br>
<br>
<h2>Extended C++ Concepts</h2>
C++ is based on two main concepts to handle objects : allocation/deallocation and construction/destruction. Phantom, as a C++ extension, reimplement these concepts – based on the C++ ones – and implement new ones, built thanks to template meta-programming :<br>
<ul><li><b>allocation/deallocation</b> : you can provide your own default allocator for the type you want. NO new/delete overloading.<br>
</li><li><b>construction/destruction (shouldn't be customized)</b> : using C++ placement new and destructor call<br>
</li><li><b>installation/uninstallation</b> : occurs just after construction/before destruction to allow extra-construction/destruction processing. As an example, the state-machine system (see below) uses installation to set the state-machine data pointer which stores the current/transit/history states on each instances (It uses a process similar to the installation of the virtual table pointer on C++ instances constructor call).<br>
</li><li><b>serialization/deserialization</b> : Serialization occurs outside of the construction process to serialize an object easily, either into human readable archives, either into binary ones (see Serialization section). Deserialization is correlated with the next initialization concept.<br>
</li><li><b>initialization/restoration/termination</b> : initialization occurs after installation to execute some code that cannot be executed in the object construction (for instance virtual calls) and notify about its construction via signals (see below the Signal/Slot system). If the object is deserialized, it will skip initialization and rather execute a restoration after the deserialization process. Termination makes sure that what has been initialized/restored is properly released. Member functions can be defined in your class to be called on these three different stages :<br>
<ul><li><b>o_initialize()/o_initialize_cpp(your_class)</b>
</li><li><b>o_restore(uint filter, uint pass)/o_restore_cpp(your_class, uint filter, uint pass)</b>
</li><li><b>o_terminate()/o_terminate_cpp(your_class)</b></li></ul></li></ul>

<ul><li><b>o_new(T) / o_delete(T) / o_dynamic delete / o_new_n(n,T) / o_delete_n(n,T)</b> : these helper macros mimics the corresponding C++ operators and integrate the previous extra concepts. Deleting via <b>o_delete(T)</b> requires to know the internal type of what you want to delete. It’s a strongly typed new/delete system. The main reason of this is first to have symetry (which new/delete does not provide sadly) and then to be able to use some pool allocators such as boost::pool ones which need static type information on deallocation.<br>
Dynamic deletion is still available with o<code>_</code>dynamic_delete, used like the classical detete, except that null pointer test is of your responsability.</li></ul>

These extensions have default implementations for all of the phantom handled types. They can then be customized by template specialization if you really need a different behavior(except construction/destruction).<br>
<br>
<hr />

<h2>Non-intrusive Reflection System</h2>

Every language element you want, at any inheritance level can acquire phantom reflection. No ‘Object’ class system which constrain you to derive from an Object root class. Phantom handles it’s own data information such as RTTI data so that you can reflect POD types (not possible with an Object class which generally contains virtual methods).<br>
<br>
<h3>Reflected Language Elements</h3>
C++ introspection is almost fully implemented. Most of the main C++ language elements are reflected<br>
<ul><li><b>Global variables</b>
</li><li><b>Global functions</b>
</li><li><b>Namespaces</b>
</li><li><b>Fundamental types</b> (int, float, void<code>*</code>, ...)<br>
</li><li><b>Class types</b> (POD and Aggregate)<br>
</li><li><b>Class</b> : Polymorphic class (which inherits from a base class or have virtual methods)<br>
</li><li><b>Pointer types</b>
</li><li><b>Reference types</b>
</li><li><b>Const types</b>
</li><li><b>Member functions</b>
</li><li><b>Data members</b>
</li><li><b>Multiple inheritance</b> (limited to 10 super classes… but not recommanded for good designs ;). Virtual inheritance monster is not supported by choice and because it's too complicated for nothing)<br>
</li><li><b>Templates</b> (you can reflect STL or BOOST libraries for example).<br>
</li><li><b>JIT structural and behavioral reflection</b> is in progress and almost complete thanks to libjit</li></ul>

<h3>Reflection in use</h3>

<font color='#BB6600'>DECLARATION SAMPLE</font>

<pre><code>/*<br>
 * MyNestingClass.h<br>
 */<br>
<br>
enum MyEnum<br>
{<br>
    MyEnumValue0,<br>
    MyEnumValue1,<br>
};<br>
<br>
typedef MyEnum MyEnumAlias;<br>
<br>
namespace my_namespace {<br>
namespace my_sub_namespace {<br>
<br>
class MyNestingClass<br>
{<br>
public:<br>
    template&lt;typename Ty&gt;<br>
    class MyClass: public MySuperClass0, public MySuperClass1<br>
    {<br>
    public:<br>
        void memberFunction(int parameter) {}<br>
        void setProperty(bool value) <br>
        {<br>
            mPropertyValue = value;<br>
            o_emit propertyChanged(value);<br>
        }<br>
        bool getProperty() const { return mPropertyValue; }<br>
<br>
    protected:<br>
        o_signal_data(signal, float);<br>
        o_signal_data(propertyChanged, bool);<br>
<br>
    protected:<br>
        double mDataMember;<br>
        bool mPropertyValue;<br>
    };<br>
<br>
};<br>
<br>
}<br>
}<br>
<br>
namespace my_namespace_alias = my_namespace::my_sub_namespace;<br>
<br>
/*<br>
 * Corresponding reflection declarations<br>
 */<br>
<br>
o_enum(MyEnum, (MyEnumValue0, MyEnumValue1));<br>
<br>
o_classN((my_namespace, my_sub_namespace), MyNestingClass)<br>
{<br>
<br>
};<br>
o_exposeN((my_namespace, my_sub_namespace), MyNestingClass)<br>
<br>
o_classNCTS((my_namespace, my_sub_namespace), (MyNestingClass), (typename), (Ty), MyClass, (MySuperClass0, MySuperClass1), o_protected|my_other_modifiers)<br>
{<br>
    o_member_function(void, memberFunction,(int));<br>
    o_signal(signal,(float));<br>
    o_data_member(double, mDataMember, o_protected);<br>
    o_property(bool, property, setProperty, getProperty, propertyChanged, o_transient|o_public, 0xffffffff);<br>
};<br>
o_exposeNCT((my_namespace, my_sub_namespace), (MyNestingClass), (typename), (Ty), MyClass);<br>
<br>
</code></pre>

<pre><code>/*<br>
 * MyNestingClass.cpp <br>
 */<br>
o_registerN((my_namespace, my_sub_namespace), MyNestingClass)); <br>
// NOTE : in o_register you don't need to give the super classes and modifiers again.<br>
<br>
o_register(MyEnum);<br>
<br>
o_register_typedef(MyEnumAlias); // A simple typedef alias registration (can be N or NC if the typedef is present in a namespace or a class)<br>
<br>
o_register_namespace_alias((ny_namespace::my_sub_namespace, my_namespace_alias); // A simple namespace alias registration<br>
<br>
o_register_template_instance(my_namespace::my_sub_namespace::MyNestingClass::MyClass&lt;int&gt;); // Template instance registration. .<br>
<br>
</code></pre>

<font color='#BB6600'>USE SAMPLE</font>

<pre><code>phantom::reflection::LanguageElement* pElement = phantom::elementByName("my_namespace::my_sub_namespace::MyNestingClass::MyClass&lt;int&gt;");<br>
<br>
phantom::reflection::Class* pClass = phantom::as&lt;phantom::reflection::Class*&gt;(element);<br>
 <br>
my_namespace::my_sub_namespace::MyNestingClass::MyClass&lt;int&gt;* instance = o_new(my_namespace::my_sub_namespace::MyNestingClass::MyClass&lt;int&gt;);<br>
<br>
SuperClass0* as_super_class0 = instance;<br>
SuperClass1* as_super_class1 = instance;<br>
<br>
o_assert(phantom::typeByName("SuperClass0") == phantom::typeOf&lt;SuperClass0&gt;());<br>
<br>
phantom::reflection::Property* pProperty = pClass-&gt;getProperty("property");<br>
phantom::reflection::InstanceMemberFunction* pMemberFunction = pClass-&gt;getInstanceMemberFunction("memberFunction(int)");<br>
void* pInstance = pClass-&gt;newInstance();<br>
int arg0 = 5;<br>
void* args[1] = {&amp;arg0};<br>
pMemberFunction-&gt;call(pInstance, args);<br>
pClass-&gt;deleteInstance(pInstance); <br>
<br>
</code></pre>


<h3>Declaration</h3>
To declare easily your phantom extension, a <b>non intrusive</b> module made of macro is provided. A short example is better than a long talk:<br>
<br>
List of declaration macro-keywords:<br>
<ul><li><b>Globals</b>:<br>
<ul><li><b>o_class</b><code>[</code>N<code>]</code><code>[</code>C<code>]</code><code>[</code>T<code>]</code><code>[</code>S<code>]</code>
</li><li><b>o_enum</b><code>[</code>N<code>]</code><code>[</code>C<code>]</code>
</li></ul></li><li><b>Members</b>:<br>
<ul><li><b>o_data_member</b>
</li><li><b>o_member_function</b>
</li><li><b>o_signal</b>
</li><li><b>o_property</b></li></ul></li></ul>

What means N C T and S ?<br>
Well, depending on the qualifications of your reflected element, you can combine these letters (keeping the given order) after the base keyword to tell phantom what arguments you are passing to the macro:<br>
<ul><li>N : namespaces : "(n0,n1,...)"<br>
</li><li>C : nesting classes : "(c0, c1, ...)"<br>
</li><li>T : template : "(arg-type0, arg-type1, ...), (arg-name0, arg-name1, ...)"<br>
</li><li>S : super classes : (s0, s1, ...)</li></ul>

You may wonder why the nested class is not declared in the <b>o_reflection</b> part of the nesting class ? I had two choices, first to consider nested types as 'members' which they don't really are, either as scoped types, which they most look like to. I've chosen the second one because it allows me to manipulate nested type the way top level types are. Indeed, reflection declaration of a class needs to be on the global scope to be able internally to specialize a lot of template helpers (which cannot be specialized in another namespace than theirs).<br>
<br>
<h3>Exposition</h3>

To be able to use the template traits and functions associated with the declared type, an extra step is needed : exposition<br>
<ul><li><b>o_expose</b><code>[</code>N<code>]</code><code>[</code>C<code>]</code><code>[</code>T<code>]</code></li></ul>

<h3>Registration</h3>

The declaration and expositions by themself are not enough if you want to be able to use reflection dynamically via string or else (without explicit template calls) and be sure members are added to their owner class. A registration using C++ dynamic initialization process is needed (in the .cpp part of your library). Here are the keywords to do that:<br>
<ul><li>o_register<code>[</code>N<code>]</code><code>[</code>C<code>]</code> : to register any non template type<br>
</li><li>o_register_template_instance(instanciated template type) : As template are only instanciated on demand, you need to instanciate the module for a given template instance to register. The syntax is not the final version, it needs to be improved to be able to accept any number of parameters and access protected nested template classes<br>
</li><li>o_register_typedef<code>[</code>N<code>]</code><code>[</code>C<code>]</code></li></ul>


<h3>To sum</h3>

Reflection use implies :<br>
<ul><li>o_classX : the declaration (generally in the .h file, but can be in the .cpp file if you want templates functions and o_new/o_delete concepts to be used privately in the .cpp file. Even if in .cpp, type reflection still can be accessed dynamically via strings if it is registered.<br>
</li><li>o_exposeX : the exposition (In .h or .cpp file, just after the o_classX)<br>
</li><li>o_registerX : the registration (.cpp file only to avoid multiple symbol collision)</li></ul>

If you miss one of these, you may have some problem accessing and using the reflection objects related to your type.<br>
<br>
<h3>RTTI system</h3>

Phantom has its own RTTI system based on the reflection system combined with the extended C++ construction process. Here is how to use it:<br>
<br>
<pre><code>    <br>
/*<br>
 *  We use as example arbitrary A, B and I classes supposed to be declared with phantom reflection system<br>
 */ <br>
<br>
    class A <br>
    {<br>
    };<br>
    class I<br>
    {<br>
    };<br>
    class B : public A, public I<br>
    {<br>
    };<br>
<br>
    int main()<br>
    {  <br>
        B* pB = o_new(B);<br>
        A* pA = pB;<br>
<br>
        // With classical C++ you would activate RTTI and use dynamic_cast to <br>
retrieve the layout address of I from an A* pointer which points to an instance of B<br>
<br>
        // In Phantom equivalent way to do so is:<br>
        I* pI = phantom::as&lt;I*&gt;(pA);<br>
<br>
        // You can retrieve the class of an object with classOf() <br>
        phantom::reflection::Class* pClassOf = phantom::classOf(pI); // Returns meta-class of B<br>
<br>
        // Or the class pointed by a memory address  <br>
        phantom::reflection::Class* pClassAt = phantom::classAt(pI);  // Returns meta-class of I <br>
<br>
        // For advanced use you can directly get the RTTI struct corresponding to a given address by <br>
        // calling rttiDataOf()<br>
        phantom::rtti_data const&amp; oi = phantom::rttiDataOf(pI);<br>
<br>
        // Get the class of the object the layout address belongs to (equivalent to classOf())<br>
        phantom::reflection::Class* pBaseClass = oi.base_class;<br>
<br>
        // Get the class of the layout pointed (equivalent to classAt()))<br>
        phantom::reflection::Class* pThisClass = oi.this_class;            <br>
<br>
        // Get the base address of the object<br>
        void* pBase = oi.base;<br>
<br>
        // Static deletion<br>
        o_delete(B) pB;<br>
<br>
        /* OR */<br>
<br>
        // Dynamic deletion (DON'T use o_delete(I) here !!! indeed the internal type is B not I)<br>
        o_dynamic_delete pI;<br>
    }<br>
</code></pre>

<hr />

<h2>Signal / Slot system</h2>
A classic signal/slot system, inspired from the Qt one (a great framework). The main difference with Qt is that there is no meta-compilation here but macro plus template meta-programming to create the system. To be clear about that, it’s not a meta-programming based connection system such as fastdelegate or boost::signals, but a dynamic system which uses template meta-programming to optimize the internal implementation. The reason of the choice of this technique compared to Qt or Boost ones is that on a first hand you can handle template class signals and on the other hand you can still connect them dynamically via Reflection.<br>
<br>
<br>
<pre><code>/*<br>
 *  We use MyClass from the previous example to illustrate this one <br>
 */ <br>
<br>
int main()<br>
{<br>
    MyClass* pMyClass1 = o_new(MyClass);<br>
    MyClass* pMyClass2 = o_new(MyClass);<br>
    <br>
    o_connect(pMyClass1, signal(int), pMyClass2, instanceMethod(int));<br>
    o_emit pMyClass1-&gt;signal(2);<br>
    o_disconnect(pMyClass1, signal(int), pMyClass2, instanceMethod(int));<br>
<br>
    o_delete(MyClass) pMyClass1;<br>
    o_delete(MyClass) pMyClass2;<br>
}<br>
<br>
</code></pre>

<hr />

<h2>High-Level Serialization system</h2>
As mentioned in the Extension system section, serialization is straightforward in phantom and is based on the Reflection system which provides introspection. A High-level serialization system has been implemented upon the Extension system to handle Data Bases with persistent Objects. This system uses a hierachical data base system which provides dependency tree nodes plugged together to create a loading dependency tree (any child node must have it’s parent node loaded to be loaded itself. This ensure dependency between them to be respected). An abstract implementation is provided with a first specialization : XmlFileTreeDataBase which stores your object’s serialized data into xml files organized into folders representing the dependency nodes. More are coming like a BinaryFileTreeDataBase.<br>
<br>
<hr />

<h2>Nested-State-Machine system</h2>
As Phantom was mostly designed to build a robust and flexible game engine, state-machines were mandatory to build determinist game play behaviors. They are implemented to mimic an extra language element so that you can manipulate/declare/add them (almost) the same way as you would manipulate/declare/add a method in a class. More, they are polymorphic, so that you can extend a base class state machine inside it’s derived classes and overload the enter/leave/update methods. Phantom tends to be as much as possible close to the UML State Machine standard, and provides a Track system to nest the state inside each other (orthogonal regions). Like the Signal/Slot system, the implementation uses meta-programming to optimize as much as we can the code at compilation time but is still based on a Visitor pattern to be dynamic and more flexible. Here are the main components available :<br>
<ul><li>Simple states<br>
</li><li>Nested states (nested inside <i>tracks</i>, themselves nested inside states, and so on ...)<br>
</li><li>Standard execution methods ( enter, update, leave ) defined in the class which declares the statechart<br>
</li><li>Event dispatching and solving<br>
</li><li>Transition reaction (self-transition possible)<br>
</li><li>Custom reactions<br>
</li><li>State inheritance/duplication, from a super-class to its derived-classes, enabled through template meta-programming (hidden to the user)</li></ul>

<font color='#BB6600'>DECLARATION SAMPLE</font>
<pre><code>/*  <br>
 *  Game entity class, used as root class of every gameplay element in almost every game engine<br>
 */<br>
<br>
class GameEntity <br>
{<br>
    <br>
};<br>
<br>
o_classN((sc2), GameEntity)<br>
{<br>
    o_statechart<br>
    {<br>
        o_state(Pooled, Root)<br>
        o_state(Spawned, Root)<br>
        o_event(Spawn)<br>
        o_transition(Pooled, Spawn, Spawned)<br>
    };<br>
};<br>
o_exposeN((sc2), GameEntity);<br>
<br>
</code></pre>

<pre><code>/*  <br>
 *  Starcraft 2 like unit design ; you can see that some Unit states are attached to the <br>
 *  GameEntity class tracks. Indeed Unit extends the statechart of GameEntity <br>
 */<br>
<br>
class Unit : public GameEntity<br>
{<br>
 <br>
    ...<br>
    /* some member declarations, ... */<br>
    ...<br>
<br>
    o_enter(Alive) { std::cout &lt;&lt; "i'm alive !!!" &lt;&lt; std::endl; }<br>
    o_update(Alive){ std::cout &lt;&lt; "i'm still alive !!!" &lt;&lt; std::endl; }<br>
    o_leave(Alive) { std::cout &lt;&lt; "Argghhh ..." &lt;&lt; std::endl; }<br>
    /* [repeated for each state] */<br>
<br>
    ...<br>
    /* some member declarations, ... */<br>
    ...<br>
};<br>
<br>
o_classNS((sc2), Unit, (GameEntity))<br>
{<br>
   o_statechart<br>
   {<br>
        o_track(Life, Spawned)<br>
            o_state(Alive, Life)<br>
                o_track(Motion, Alive)<br>
                    o_state(Idle, Motion)<br>
                    o_state(Move, Motion)<br>
                    o_state(Patrol, Motion)<br>
                o_track(Attack, Alive)<br>
                    o_state(Pacific, Attack)<br>
                    o_state(Hit, Attack)<br>
                    o_state(CoolDown, Attack)<br>
                o_track(Visibility, Alive)<br>
                    o_state(Visible, Visibility)<br>
                    o_state(Invisible, Visibility)<br>
                o_track(Control, Alive)<br>
                    o_state(ControlOff, Control)<br>
                    o_state(ControlOn, Control)<br>
            o_state(Dead, Life)<br>
<br>
        o_event(CoolDownFinished)<br>
        o_event(HitFinished)<br>
        o_event(Die)<br>
        o_transition(CoolDown, CoolDownFinished, Hit)<br>
        o_transition(Hit, HitFinished, CoolDown)<br>
        o_transition(Alive, Die, Dead)<br>
    };<br>
};<br>
o_exposeN((sc2), Unit);<br>
<br>
</code></pre>

<font color='#BB6600'>USE SAMPLE</font>
<pre><code><br>
int main()<br>
{<br>
    // Create a new Unit instance with phantom extension<br>
    sc2::Unit* pUnit = o_new(sc2::Unit);<br>
<br>
    // The state machine belongs to the class and uses a Visitor pattern <br>
    // to modify the class instances <br>
<br>
    phantom::state::StateMachine* pStateMachine = phantom::stateMachineOf&lt;sc2::Unit&gt;();<br>
    <br>
    // Initialize the state machine, which means entering the initial states (the first<br>
    // declared in the statechart for each track)<br>
<br>
    pStateMachine-&gt;initialize(pUnit);                      <br>
<br>
    // Post Spawn event which triggers the transition : Pooled -&gt; Spawned /// &gt; <br>
  <br>
    pStateMachine-&gt;postEvent&lt;sc2::Unit::StateChart::Spawn&gt;(pUnit);        /// &gt; I'm alive !!!<br>
<br>
    // Update the state machine (simulates a game tick) <br>
    <br>
    pStateMachine-&gt;update(pUnit);                                         /// &gt; I'm still alive !!!<br>
<br>
    // Post Die event which triggers the transition : Alive -&gt; Dead<br>
    <br>
    pStateMachine-&gt;postEvent&lt;sc2::Unit::StateChart::Die&gt;(pUnit);          /// &gt; Argghhh ...<br>
<br>
    // Terminate the state machine, which means leaving the current states of each track<br>
    pStateMachine-&gt;terminate(pUnit); <br>
<br>
    // Clean the instance<br>
    o_delete(sc2::Unit) pUnit;<br>
<br>
    return 0;<br>
}<br>
<br>
</code></pre>

<hr />

<h2>Type traits extension</h2>
Phantom uses std/boost type_traits to choose at compile time the correct needed implementation for the Extension system and the Reflection system (for instance to avoid compilation errors when implementating the construction method of an abstract class reflection). Phantom provides its own type traits which inform the developer about some Phantom extra traits such as the super/base class count, about if the type has a phantom reflection, if the type has a phantom extension, if the class has an user state chart defined, etc …<br>
<br>
<hr />

<h1>More about ...</h1>

Maybe some of you are not used to these "reflection" or "state-machine" things, and you miss something great, that's why I explain it to you right now.<br>
<br>
<h2><i>Reflection</i></h2>

To sum, the basic principle of reflection is to modelize with a language the structure or the semantic of the language itself and sometimes enable to modify it ; that's why reflection is a part of what we call <b>meta</b>-programming. In fact, it's a quite universal representation ; let's take for example an industry robot able to build another robot, slightly different, able to repare itself or even to rebuild it's original creator. In the case of a language featuring reflection like java, it enables you to manipulate the classes and their related members as objects themselves so that you can access dynamically to a method and invoke it for example.<br>
<i>Phantom</i> adds these features to C++ :<br>
<br>
<table><tr><td><b>Java</b> with the package <b>java.lang.reflect</b></td><td>
<pre><code>Ball.class.getMethod("bounce()").invoke(my_ball, null);<br>
</code></pre>
</td></tr>
<tr><td><b>C++</b> with <b>phantom::reflection</b></td><td>
<pre><code>Ball::Reflect()-&gt;getMethod("bounce()")-&gt;invoke(my_ball_ptr, NULL);<br>
</code></pre>
</td></tr></table>

To be more precise, this example introduce <i>introspection</i>, one of the two reflections implemented in <i>phantom</i>, which provide an interface to interact with the language structure and manipulate it without modifying it (method call, attribute access ...). <i>Phantom</i> also implements <i>partial</i> <i>structural</i> <i>reflection</i> which provides the tools to create and modify extra elements at runtime. To make it short, with structural reflection you can create class, attribute and even methods at runtime. Since C++ is a compiled language it is not really possible to create real C++ classes on runtime (classes are only abstract concept in C++, and that's why reflection is not native). However, combined with introspection, we can create objects which represent class and are able to create instances of that meta-class by allocating memory and manipulating C++ constructors/destructors. Combined with introspection, structural reflection enables to make a <i>runtime</i> <i>meta-class</i> inherit from a <i>native</i> <i>meta-class</i>, which is powerful to create a scalable and flexible script language without using extern wrappers.<br>
<br>
A third reflection type, the <i>behavioral reflection</i> which allow to alter the language semantic, is not featured in <i>phantom</i> ... for now :)<br>
<br>
<h2><i>Nested State-machine</i></h2>
State-machine ... you will probably think it's about a machine handling states and you'll be pretty right :)<br>
The main goal of a state machine is to modelize the different states that could have an object, an application section or even an entire application, and to manage strictly the transitions between them so that you can have a hard control on what happen at execution time. That's why the state-machines I talk about are generally called <i>finite state machine</i> (FSM). Why finite ? Because the number of states and transitions managed by the state-machine is finite and known by the user/developer so that it can control which state will be reachable from any other state at any time. In the industrial domain tey are generally called automaton and are massively used to handle robots motion and actions to avoid impredictable behavior. For the same reasons, they are mainly used in game programming to manipulate game entities such as characters, interruptors, triggers, and any element that could be modelized with at least two states.<br>
<br>
A quick example : a door... it can have two basic states : <b>opened</b> and <b>closed</b>. And as you know, we can only open the door when it's closed and close it when it's opened. That's what is called a <b>transition</b> ; we can define here two transitions : <b>opened</b>-><b>closed</b> and <b>closed</b>-><b>opened</b>. And the most sceptic and cynical will tell : yes, but I can do it with a boolean man. And, for that case I can say yes, you are right. But now since you are introduced to the basics, let's take a more complicated example. Let's comme back to our robot. Imagine an arm-robot supposed to take a piece of metal, move it and assemble it someway depending on the type of piece it handles. I swear that if you still want to use your booleans to handle these kind of situations, you'll have more problems ^^ Imagine that there are two different type of pieces to handle, the robot will have to make two different moves to take it and two others to assemble them. If you consider also that the hand moves are independant from the arm moves, prepare a lot of boolean and warm up your debugger wohoo... or simply use state-machines. How can we use state-machines to design such a complicated case ? We can simply divide first the robot actions into states :<br>
<br>
<ul><li>shutdown (the robot is turned off)<br>
</li><li>standby  (the robot is turned on)<br>
</li><li>take piece 1<br>
</li><li>take piece 2<br>
</li><li>assemble piece 1<br>
</li><li>assemble piece 2<br>
</li><li>go back to standby from assembling 1<br>
</li><li>go back to standby from assembling 2</li></ul>

So if the robot is given the piece 1, it will take these states : standby -> take piece 1 -> assemble piece 1 -> go back to standby from assembling 1 -> standby<br>
<br>
Easy no ? it really is :)<br>
<br>
<b>Bob</b> : "Eey Vivien, but how does the robot know that it has to transit from one state to another ??"<br>
<br>
<b>Vivien</b> : "With <b>events</b> Bob !! "<br>
<br>
Events are data propagated through the state-machine and handled by the active states to trigger (or not) some reactions. Among these reactions is the transition I told you previously. So the guy who take care of the robot will program something like this : "if you are in state <i>A</i> and you receive an event <i>E</i>, go in state <i>B</i>". In our design, "if you are in state <i>shutdown</i> and you receive an event <i>switchOn</i>, go in state <i>standby</i>".<br>
So, to sum, if the robot is shutdown and receive a switchOn event, it will transit to standby. BUT, and that's the power of state-machines, if the robot is already in standby or in a state we do not want the robot to go in standby, the robot won't do anything... nice roby !<br>
<br>
<p align='center'>"No reaction set, no reaction done".</p>

<b>Bob</b> : "ok I get it ! But what is the real interest of using states instead of booleans/flags ?"<br>
<br>
<b>Vivien</b> : "ok, let's explain"<br>
<br>
The main problem with booleans it that you have to maintain them all the time to keep your model working, and if you forget an affectation or a reset somewhere, it could be a maze to find what is the reason of the crash or misbehavior you get. Another issue is when you design your flags to fit a 32-bit integer and save memory, thinking you'll only need 32 state. The day you want to put more states, you are in a big problem... I've seen in some gameplay code that kind of design with nearly hundred flags set and unset everywhere... a hell to debug, really.<br>
That's what state-machine are made for. The data associated with each state is automatically initialized and terminated by the underlying design on each transition so that you keep a clean, maintainable and scalable code. Each time an object enter a state or exit a state, code is executed so that you can handle the initialization and termination of the designed state. The goal of the state-machine is to manage correctly the enter and exit of each state. To take again our example, if the piece 1 is given to the arm-robot when it's on standby the following will be executed successively :<br>
<br>
<ol><li><font color='#FF0000'>exit</font>  <i>standby</i> (some code written by the user is executed to clean the standby state data)<br>
</li><li><font color='#00BB55'>enter</font> <i>take piece 1</i> (some code is executed to init the <i>take piece 1</i> state)<br>
</li><li><font color='#FF0000'>exit</font>  <i>take piece 1</i> (and so on ...)<br>
</li><li><font color='#00BB55'>enter</font> <i>assemble piece 1</i>
</li><li><font color='#FF0000'>exit</font>  <i>assemble piece 1</i>
</li><li><font color='#00BB55'>enter</font> <i>go back to standby from assembling 1</i>
</li><li><font color='#FF0000'>exit</font>  <i>go back to standby from assembling 1</i>
</li><li><font color='#00BB55'>enter</font> <i>standby</i></li></ol>

In some state-machine design, especially when the data is constantly evoluting (in game-programming, among others ...), an extra <i>update</i> code is executed on each application or machine cycle (on each game loop cycle for game-programming). It enable to update the data associated with the active state. In our example, the code of <font color='#BB6600'><i>update</i></font> <i>take piece 1</i> would handle the arm motion to make it go from an idle position to the position taking the piece 1.<br>
<br>
<h3>FSM limitations, UML extra-features</h3>

As FSM are sometimes limited, UML adds some new feature to improve the state-machines design. Let's talk of the first one, the <b>nested</b> thing. Imagine that you want the robot go in state <i>shutdown</i> when the <i>switchOff</i> event is dispatched, no matter the current state. With our current FSM features, we would need to set a transition from every state to the state shutdown, triggered by the <i>switchOff</i> event. Now imagine that your robot has 200 states instead of the 7 we have in our design, you'll need to set 200 transitions which point to the <i>shutdown</i> state... quite annoying, isn't it ?<br>
That's where nested states are useful. The principle is to embed some states into a parent state, so that when you exit this one, all it's associated child state will also be exited. You can see it as state-machine executed inside another one.<br>
In our design, we could add an extra <i>turnedOn</i> state which would contain all the states excepted the shutdown one. In that configuration, when the <i>turnedOn</i> is exited, any state inside will be also, avoiding to plug a transition for each state we want to be exited. You can obviously use this pattern recursively to improve your design robustness.<br>
<br>
Another feature, called <b>orthogonal-region</b> is available in UML. The name isn't really explicit concerning its use. The goal of orthogonal region is to make independant state to be run in parallel. The orthogonal comes from the fact that all parallel line are orthognonal to same line. In the case of state-machine it's like every independant group of state are run in parallel, orthogonal to the embedding state.<br>
<br>
<b>Bob</b> : what ??<br>
<br>
<b>Vivien</b> : hum...<br>
<br>
Let's assimilate an <b>orthogonal-regions</b> to a music <b>track</b> in digital music : each of them is independant and contains notes that are played at the same time to make the music richer. Imagine now that a note in a track represents the current state of an <b>orthogonal-region</b> and you will get a pretty good picture of how it works.<br>
By the way, in Phantom I've renamed them <b>track</b> to simplify.<br>
<br>
In our example, imagine our robot having its arm and hand moving independantly. To design this, we could have two <b>tracks</b> in our <i>turnedOn</i> state. The first one would handle all the states which update the arm motion and the second would handle the hand ones. Of course, independance doesn't mean we don't need synchronization between the arm and the hand ; this could be done by using <b>events</b> to communicate between the <b>tracks</b>.<br>
<br>
To conclude, a state-machine contains a root track which contains a set of states. Each state contains itself tracks, themselves containing states ... and so on ...<br>
<br>
<hr />

<h1>Why <i>Phantom</i> ?</h1>
<ul>
<li>First because the main goal of this C++ extension is to be mutable and to generate meta-data which can be completely transformed into an optimized and stable code or even be completely removed on a master release - as a phantom could appear, disappear and reappear ;)</li>
<li>Then, the extension can have its "shape" changing, according to the developer(team)'s requirements. It can be customized through an easy to use macro definition interface</li>
<li>Finally because <i>phantom</i> is almost the same word in french - my native language : <i>fantôme</i> ; same with spanish / italian : <i>fantasma</i>, and other latin-derived languages ...</li>

</ul>

<hr />