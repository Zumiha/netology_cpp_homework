#define POT A0
#define FILTER_WIDTH 10

int buffer_array[FILTER_WIDTH]{};
int index = 0; 

int output_val;

double filtered_result;
int value;
String str;

void FirFilter() {
  buffer_array[index] = analogRead(POT);
  index = (index + 1)%FILTER_WIDTH;
  
  output_val = 0;
  for (int i = 0; i < FILTER_WIDTH; i++) {
    output_val += buffer_array[i];
  }

  filtered_result = (double)output_val/FILTER_WIDTH;
}

int AngleConvert(int _val) {
  double xyz = (270.0*(_val - 511.5))/1023.0;
  return xyz;
}

void setup()
{
  Serial.begin(9600); //последовательный порт для отладки
  while (!Serial)
  {
  // wait for serial port to connect.
  }
  pinMode(POT, INPUT); //контакт потенциометра - вход
}

void loop()
{
  FirFilter();
  // value = static_cast<int>((270.0*filtered_result)/1023.0);
  // str = static_cast<String>(value);

  // str = ToString(filtered_result);
  str = static_cast<String>(AngleConvert(filtered_result));  
  Serial.println("Angle: " + str + "°");
  delay(100); //задержка для наглядности
}