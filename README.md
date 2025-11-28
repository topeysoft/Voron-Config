# Voron-Config

## KlipperScreen Development on macOS

### Prerequisites

1. **Install XQuartz** (required for GTK display):

   ```bash
   brew install --cask xquartz
   ```

   Then **log out and back in** (or reboot).

2. **Install GTK dependencies**:

   ```bash
   brew install gtk+3 gobject-introspection cairo pygobject3
   ```

3. **Install Python requirements**:

   ```bash
   cd KlipperScreen
   # Use macOS-specific requirements (excludes Linux-only sdbus packages)
   pip3 install -r scripts/KlipperScreen-requirements-macos.txt
   ```

### Running KlipperScreen

```bash
cd KlipperScreen

# Run with default config (will try to connect to Klipper)
python3 screen.py

# Or specify a config file
python3 screen.py -c /path/to/your/KlipperScreen.conf
```

### Notes

- The `sdbus` and `sdbus_networkmanager` dependencies won't work on macOS (Linux-specific D-Bus libraries). You may need to comment those out or handle import errors for macOS development.
- Check the `KlipperScreen/config/` directory for sample configurations.
