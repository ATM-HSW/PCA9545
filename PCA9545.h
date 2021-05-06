#ifndef __PCA9545_H__
#define __PCA9545_H__


class PCA9545 {
  public:
    static const uint8_t PCA9545_ADDRESS8BIT = 0xE0;

    static const uint8_t PCA9545_BUS0        = 0x01;  // 1 = enable, 0 = disable
    static const uint8_t PCA9545_BUS1        = 0x02;  // 1 = enable, 0 = disable
    static const uint8_t PCA9545_BUS2        = 0x04;  // 1 = enable, 0 = disable
    static const uint8_t PCA9545_BUS3        = 0x08;  // 1 = enable, 0 = disable

  private:
    uint8_t m_devAddr = PCA9545_ADDRESS8BIT;
    I2C *m_i2c;
    uint8_t m_cmd[1];

  public:
    int init(I2C *i2c, uint8_t devAddr) {
      m_devAddr = devAddr;
      this->m_i2c = i2c;
      return 0;
    }

    int enableBus(int8_t busno) {
      int ret;

      switch(busno) {
        case 0: this->m_cmd[0] = PCA9545_BUS0; break;
        case 1: this->m_cmd[0] = PCA9545_BUS1; break;
        case 2: this->m_cmd[0] = PCA9545_BUS2; break;
        case 3: this->m_cmd[0] = PCA9545_BUS3; break;
        default: this->m_cmd[0] = 0; break;
      }

      ret = this->m_i2c->write(PCA9545_ADDRESS8BIT, (const char*)m_cmd, 1);
      this->m_cmd[0] = 0;
      ret = this->m_i2c->read(PCA9545_ADDRESS8BIT, (char*)m_cmd, 1);
      if(ret==0 && (this->m_cmd[0]&0x0f) == m_cmd[0]) return 0;
      else return 1;
    }

};

#endif
