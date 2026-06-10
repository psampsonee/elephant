#pragma once
// Minimal virtual interrupt handler
class InterruptHandler {
    public:
    virtual void irq() = 0;
};

// Interrupt handler object with added bells and whistles that make it usable
template <typename T>
class InterruptObject : public InterruptHandler {
public:

    // Constructors
    InterruptObject() : _interruptFlag(false), _myErrorHandler(&defaultErrorHandler) {}
    InterruptObject(T& resource) : 
        _interruptFlag(false), _resource(&resource),
        _myErrorHandler(&(defaultErrorHandler)) {}
    InterruptObject(T& resource, void (*errorHandler)) : 
        _interruptFlag(false), _resource(&resource), _myErrorHandler(&errorHandler)  {}

    // "Default" irq behavior is simply to set the flag boolean to true.
    void irq() { setFlag(); }

    // IRQ flag boolean management
    inline bool isInterruptFired() { return this->_interruptFlag; }
    void resetFlag() { this->_interruptFlag = false; }

    // Resource management
    void setResouce(T& resource) { this->_resource = &resource; }
    T& getResource() { return (*(this->_resource)); }

    // Allow the ability to set the error handler after initialization
    void setErrorHandler(void (*errorHandler)) { this->_myErrorHandler = errorHandler; }

protected:
    // Protected Constructors (For derived objects)
    // Allow inherited objects to set the _resource pointer directly
    InterruptObject(T* resource) : 
        _interruptFlag(false), _resource(resource),
        _myErrorHandler(&(defaultErrorHandler)) {}
    InterruptObject(T* resource, void (*errorHandler)) : 
        _interruptFlag(false), _resource(resource), _myErrorHandler(&errorHandler)  {}

    void setFlag() {  this->_interruptFlag = true;  }
    static void defaultErrorHandler() { while(true) {} };

    bool _interruptFlag;
    void (*_myErrorHandler)();
    T* _resource;
};