t## Flash firmware

```bash
git clone https://github.com/Arksine/katapult.git ~/katapult
```

```bash
cd ~/katapult
sudo dfu-util -R -a 0 -s 0x08000000:force:mass-erase:leave -D ~/katapult/out/katapult.bin -d 0483:df11
```

```bash
cd ~/klipper
make flash FLASH_DEVICE=0483:df11

# or

cd ~/katapult/scripts
python3 flash_can.py -i can0 -q
```

then

```bash
python3 ~/katapult/scripts/flash_can.py -i can0 -f ~/klipper/out/klipper.bin -u abcdef123556
```

The above command can also be used for updating the firmware on the CAN device when a new firmware is available.

## Create CAN interface

### 1. Using ip command

```bash
sudo nano /etc/network/interfaces.d/can0
```

sudo ip link set can0 up type can bitrate 1000000
sudo ifconfig can0 txqueuelen 1024

Paste the following:

```bash
allow-hotplug can0
iface can0 can static
  bitrate 1000000
  up ip link set can0 txqueuelen 1024
```

### 2. Using systemd.networkd

```bash
sudo nano /etc/systemd/network/80-can0.network
```

Copy and paste the following:

```bash
# This replaces the historic /etc/network/interfaces configuration

[Match]
Name=can0

[CAN]
BitRate=1000000
RestartSec=100ms
FDMode=no
BusErrorReporting=yes


# May no longer be required.
# See https://github.com/linux-can/can-utils/issues/68#issuecomment-1894136824
[Link]
RequiredForOnline=no
```

Then run:

```bash
sudo nano /etc/systemd/network/80-can-txqueue.link
```

And paste the following:

```bash
[Match]
OriginalName=can*

[Link]
TransmitQueueLength=1024
```

And then:

```bash
udevadm control --reload # or systemctl reload systemd-udevd.service
udevadm trigger --action=add /sys/class/net/can0
```

```bash
sudo systemctl restart systemd-networkd
```

## Check CAN interface

```bash
ifconfig can0
```

## Check klipper CAN device

```bash
~/klippy-env/bin/python ~/klipper/scripts/canbus_query.py can0
```
