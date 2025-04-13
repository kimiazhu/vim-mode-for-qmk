# 说明

目前的可视化改键方式似乎总是无法很好直接在键盘上模拟 VIM 的快捷键。这个 repo 的方式准备基于 YDKB / VIAL / QMK 在代码上进行改键模拟。


# 如何构建

手上的固件是 ydkb，所以基于 ydkb 的 repo 进行调整

`make ydkb/hhkb_ble:vial`

# 刷入固件

- 拔掉 USB 线，按住 ESC 并重新插入 USB 线缆
- Windows 下直接拷贝进刷出来的盘符中，mac 执行以下指令,* 注意替换为自己的分区 *：
```
$ mount /Volumes/HHKB_BLE
sudo dd if=/Users/kc/Development/keyboard/vial-qmk-v5/ydkb_hhkb_ble_vial.bin of=/dev/disk8 seek=4
```

