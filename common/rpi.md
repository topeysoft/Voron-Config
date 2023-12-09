## Make RPI boot faster

### Decrease time to boot by eliminating "switch to on demand CPU governor"

```
sudo systemctl disable triggerhappy.service
sudo systemctl disable triggerhappy.socket
    #Eliminate thd.socket errors from udev
[ -f /lib/udev/rules.d/60-triggerhappy.rules ] && sudo mv /lib/udev/rules.d/60-triggerhappy.rules /lib/udev/rules.d/.60-triggerhappy-sdm.rules
[ -f /usr/sbin/thd ] && sudo mv /usr/sbin/thd /usr/sbin/thd.sdm
```

### Disable Bluetooth

```
sudo systemctl disable hciuart.service
```

### Run the following commands to see what is taking the most time to boot

```
systemd-analyze blame
systemd-analyze critical-chain
```
