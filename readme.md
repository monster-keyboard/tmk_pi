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
