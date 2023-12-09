When using a 7" screen, you may want to rotate the display to use the screen in portrait mode. This can be done as follows:

Rotate text console at boot

```bash
sudo nano /boot/config.txt
```

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
```
