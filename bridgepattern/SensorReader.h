class SensorReader {
  private:
    ISensor *sensor;
    String name;

  public:
    // Constructor now accepts a name parameter
    SensorReader(ISensor *sensor, String name) : sensor(sensor), name(name) {}

    void readSensor() {
      sensor->read_sensor();
    }

    float getData(int index) {
      return sensor->get_data(index);
    }

    // Method to get the name of the sensor
    String getName() {
      return name;
    }
};
