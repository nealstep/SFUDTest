#include <Arduino.h>
#include <sfud.h>

const sfud_flash* flash;
static const uint32_t addr=0x0;
static const size_t data_size = 192;
uint8_t data1[data_size];
uint8_t data2[data_size];

void data_init(void) {
  for (size_t i=0;i<data_size;i++) {
    data1[i] = (uint8_t)i;
    data2[i] = 0;
  }
}

void print_hex(uint8_t val) {
    if (val < 16) {
      Serial.print("0");
    }
    Serial.print(val, HEX);
}

void data_dump(uint8_t data[]) {
  Serial.print("  ");
  for (size_t i = 0; i < data_size; i++) {
    print_hex(data[i]);
    if ((i % 32) == 31) {
      Serial.print("\n  ");
    }
  }
  Serial.println("");
}

void data_compare(void) {
  size_t i;

  Serial.print("Mismatches: ");
  for (i = 0; i < data_size; i++) {
    if (data1[i] != data2[i]) {
      Serial.print(i, DEC);
      Serial.print(":(");
      print_hex(data1[i]);
      Serial.print(",");
      print_hex(data2[i]);
      Serial.print(") ");
    }
  }
  Serial.println("");
}  

void flash_read(void) {
  if (sfud_read(flash, addr, data_size, data2) != SFUD_SUCCESS) {
    Serial.println("*** Flash read failed");
  } else {
    Serial.println("Read worked");
  }
}

void flash_write(void) {
  if (sfud_erase_write(flash, addr, data_size, data1) != SFUD_SUCCESS) {
    Serial.println("*** Flash write failed ***");
  } else {
    Serial.println("Write succeeded");
  }
}

void setup(void) {
  Serial.begin(115200);
  while (!Serial) {
    delay(50);
  }
  delay(2000);
  Serial.println("Starting");
  while (!(sfud_init() == SFUD_SUCCESS))
    ;
  sfud_qspi_fast_read_enable(sfud_get_device(SFUD_W25Q32_DEVICE_INDEX), 2);
  flash = sfud_get_device_table();
  Serial.println("Started");

  data_init();

  Serial.println("Data 1");
  data_dump(data1);
  Serial.println("Data 2");
  data_dump(data2);

  Serial.println("Write");
  flash_write();

  Serial.println("Data 1");
  data_dump(data1);

  Serial.println("Read");
  flash_read();

  Serial.println("Data 1");
  data_dump(data1);
  Serial.println("Data 2");
  data_dump(data2);
  data_compare();
}

void loop() {
  delay(100);
}

// logger print function
void send(const char* msg) {
  Serial.println(msg);
}