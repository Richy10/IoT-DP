/*class state
{
public:

    //virtual void read_data();
    virtual void connect(sensorMachine*);
    virtual void check_connection(sensorMachine*);

protected:
    void ChangeState(sensorMachine*, state*);

};

class sensorMachine
{

public:
    sensorMachine();

    void connect();
    void check_connection();
    
    state not_connected;
    state connected;

    state state = not_connected;
    
    private:
        friend class state;
        void ChangeState(state*);

    private:
        state* _state;
};



sensorMachine::sensorMachine(){
    _state = sensorOffline::Instance();
}

void sensorMachine::ChangeState (state* s) {
_state = s;
}

void sensorMachine::connect(){
    _state -> connect(this);
}

void sensorMachine::check_connection(){
    _state -> check_connection(this);
}

void state::connect(sensorMachine*){}

void state::check_connection(sensorMachine*){}

void state::ChangeState(sensorMachine* t, state* s){
    t->ChangeState(s);
}

class sensorOffline : public state{

public:
    static state* Instance();

    virtual void connect(sensorMachine*);

};

class sensorOnline : public state{

public:
    static state* Instance();

    virtual void check_connection(sensorMachine*);

};

void sensorOffline::connect(sensorMachine* t){
    //connect

    ChangeState(t, sensorOnline::Instance());
}

//void sensorOffline: func()

void sensorOnline::check_connection(sensorMachine* t){
    //if WiFi == off
    //ChangeState(t, sensorOffline::Instance());

}

state* sensorOffline::Instance(){
    static sensorOffline instance;
    return &instance;
}

state* sensorOnline::Instance(){
    static sensorOnline instance;
    return &instance;
}

int main()
{
    sensorMachine* t = new sensorMachine();
    t->connect();
    t->check_connection();
    return 0;
}
*/