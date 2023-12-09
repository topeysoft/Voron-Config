## Create CAN interface

```bash
sudo nano /etc/network/interfaces.d/can0
```

Paste the following:

```bash
allow-hotplug can0
iface can0 can static
  bitrate 1000000
  up ip link set can0 txqueuelen 1024
```

## Check CAN interface

```bash
ifconfig can0
```

## Check klipper CAN device

```bash
~/klippy-env/bin/python ~/klipper/scripts/canbus_query.py can0
```
