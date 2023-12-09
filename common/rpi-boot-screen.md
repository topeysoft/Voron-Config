## Setup Boot Screen

Visit [Voron Raspberry Pi Boot Screens](https://docs.vorondesign.com/community/howto/samwiseg0/voron_rpi_bootscreen.html)

Voron Raspberry Pi Boot Screens

Source PSD and images can be found in my GitHub repo! Feel free to reach out to me on Discord (Samwiseg0#4034). I will be happy to customize the serial number on any of the splash screens.

NOTE:
This guide will only work on Raspberry Pi OS LITE images. If you are using FluiddPi or MainsailOS those images will work. The following procedure has been verified on buster and bullseye.

Start by removing all the default screens and also the Raspberry images. Also, disable all the bootup lines.

Edit /boot/config.txt to remove the color test/rainbow screen.

```bash
sudo nano /boot/config.txt
```

Add:

```bash
disable_splash=1
```

Press Ctrl+X, Y for save and Enter to return to the command line.

Edit /boot/cmdline.txt

```bash
sudo nano /boot/cmdline.txt
```

Add the following to the end of the first line

```bash
consoleblank=1 logo.nologo quiet loglevel=0 vt.global_cursor_default=0 splash fastboot noatime nodiratime noram
```

<!-- ```bash
logo.nologo consoleblank=0 loglevel=1 quiet vt.global_cursor_default=0
``` -->

logo.nologo - Remove the Raspberry logo.
consoleblank=0 loglevel=1 quiet - Disable the commands and various bits of the kernel
vt.global_cursor_default=0- Removes the blinking cursor before the image loads.
Press Ctrl+X, Y for save and Enter to return to the command line.

Remove the login prompt by running

```bash
sudo systemctl disable getty@tty3
```

Add the new splash screen
To make the image readable install fbi. fbi is a frame-buffer image viewer.

Install fbi

```bash
sudo apt install fbi
```

It will take a few seconds to install. After this we have to create a file by

```bash
sudo nano /etc/systemd/system/splashscreen.service
```

Add the following:

```bash
[Unit]
Description=Splash screen
DefaultDependencies=no
After=local-fs.target

[Service]
#ExecStartPre is to workaround a race condition with bullseye. It can be removed in most cases. If an error apears on the screen that says it "cannot open /dev/fb0" then make sure ExecStartPre is used.
ExecStartPre=/usr/bin/sleep 2
ExecStart=/usr/bin/fbi -d /dev/fb0 --noverbose -a /home/pi/boot-image.png
StandardInput=tty
StandardOutput=tty

[Install]
WantedBy=sysinit.target
```

-d/dev/fb0 - Tells fbi which framebuffer to use for displaying

--noverbose - Suppresses fbi ‘status bar’ at the bottom.

-a - If the selected image is in the proper measurements then no editing is required; if not, then “-a” will act as editor.

StandardInput/StandardOutput - Allows fbi get access to tty.

DefaultDependencies - will override the systemd’s default behavior.

fbi will be loaded in the boot process when WantedBy is accessed, not before the file system (and hence image) are ready, through the After option.

Place the image on the Pi and name it boot-image.png. The image should live in the main home directory for the pi user. The full path for the image is /home/pi/boot-image.png You may use another name but you must change it in the systemd file above.

### Copy the image to the Pi

```bash
scp ./boot-image.png  pi@[pi-ip-or]-hostname.local:~/boot-image.png
```

Enable the service by running

```bash
sudo systemctl enable splashscreen
```

Now reboot the Raspberry Pi and verify your image by

```bash
sudo reboot
```
