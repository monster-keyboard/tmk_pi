# 安装hid module

下载 linux-header


使用pl2303的linux下用minicom登录pi
https://blog.csdn.net/qq_38880380/article/details/77662637


## 安装wiringpi

## 开启i2c

```sh
sudo apt-get install -y i2c-tools
sudo raspi-config
```

```plaintext
5.Interfacing Options ----> p5 I2C
```

- [ ] 外置usb 接口
    - type-c 6p
    - mini usb 母座
- [ ] TFT(spi) 屏幕
- [ ] g_mass_storage 模拟U盘

### 键位文件格式

使用`json`格式

读取顺序

- `monster_keymap.json`
- `keymap.json`

```json
{
    "author":"rainboy",
    "keymap":"",
    "layout":"",
    "col_row_mapping":"|",
    "time":""
}
```
