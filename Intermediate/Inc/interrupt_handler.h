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
    InterruptObject() : _interruptFlag(false) {}
    InterruptObject(T& resource) : _interruptFlag(false), _resource(&resource) {}

    // "Default" irq behavior is simply to set the flag boolean to true.
    void irq() { setFlag(); }

    // IRQ flag boolean management
    inline bool isInterruptFired() { return this->_interruptFlag; }
    void resetFlag() { this->_interruptFlag = false; }

    // Resource management
    void setResouce(T& resource) { this->_resource = &resource; }
    T& getResource() { return (*(this->_resource)); }

    // Operator(s)
    //InterruptObject& operator=(const InterruptObject& other) { this->_resource = other._resource; }
protected:

    void setFlag() {  this->_interruptFlag = true;  }

    bool _interruptFlag;
    T* _resource;
};