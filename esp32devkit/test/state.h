//class sensorMachine;
class sensorMachine;

class state
{
public:

    //virtual void read_data();
    virtual void connect(sensorMachine*);
    virtual void check_connection(sensorMachine*);

protected:
    void ChangeState(sensorMachine*, state*);

};
