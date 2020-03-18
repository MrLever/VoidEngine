#pragma once
//STD Headers

//Library headers

//Void Engine Headers

namespace utils {
	template <class T>
    class Property {
    public:
        /**
         * Constructor
         */
        Property() = default;

        /**
         * Variadic Constructor
         */
        template <class... Args>
        Property(Args&&... args) : m_Value(std::forward<Args>(args)...) {};

        /**
         * Destructor
         */
        virtual ~Property() = default;

        /**
         * Setter
         */
        virtual T& operator= (const T& val) { return m_Value = val; }

        /**
         * Getter
         */
        virtual const T& operator() () const { return m_Value; }

        /**
         * Pointer Getter
         */
        virtual T* operator->() { return &m_Value; }
    protected:
        /** Underlying value of property */
        T m_Value;
    };
}

/** EXAMPLE PROPERTY WITH CUSTOM SETTER/GETTER */
//class : public utils::Property<math::Vector3> {
//public:
//    math::Vector3& operator= (const math::Vector3& val) override { return m_Value = val; }
//    virtual const math::Vector3& operator() () const override { return m_Value; }
//} Position;