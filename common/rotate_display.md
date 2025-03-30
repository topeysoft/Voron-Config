When using a 7" screen, you may want to rotate the display to use the screen in portrait mode. This can be done as follows:

Rotate text console at boot

```bash
sudo nano /boot/config.txt
```

Comment out the following line:

```bash
#dtoverlay=vc4-kms-v3d
```

# For 0 degree rotation:

# (no additional entries - default setting)

# For 90 degree rotation (top to right):

display_lcd_rotate=1

dtoverlay=rpi-ft5406,touchscreen-swapped-x-y=1,touchscreen-inverted-x=1

# For 180 degree rotation (upside down)

display_lcd_rotate=2

dtoverlay=rpi-ft5406,touchscreen-inverted-x=1,touchscreen-inverted-y=1

# For 270 degree rotation (top to left)

display_lcd_rotate=3

dtoverlay=rpi-ft5406,touchscreen-swapped-x-y=1,touchscreen-inverted-y=1

<!--
 The following did not work for me, but may work for you. If you want to try it, do the following:

comment out the following line:

```bash
#display_auto_detect=1
```

and add the following lines:

```bash
# Rotate text console at boot
lcd_rotate=2
# Rotate the touchscreen
dtoverlay=vc4-kms-dsi-7inch,invx,invy
```

Rotate the screen after boot (for example, if you are using a 7" screen)

```bash
sudo nano /boot/cmdline.txt`
```

add this to the end of the line (all in one line):

```bash
video=DSI-1:800x480@60,rotate=180
``` -->

<!-- # @lxpanel --profile LXDE-pi

@pcmanfm --desktop --profile LXDE-pi
@xscreensaver -no-splash
@unclutter -idle 0
@xrandr --output HDMI-1 --rotate inverted

sudo nano /usr/share/X11/xorg.conf.d/40-libinput.conf -->
