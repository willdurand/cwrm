Camera WiFi Remote Module
=========================

CWRM stands for _Camera WiFi Remote Module_. It is a ESP8266-based device that
allows to trigger the focus/shutter of a camera. It is in **early stage** but it
works.

## Schematic

Note: the schematic below assumes the presence of a 3.3V power supply for the
WiFi module. This will evolve soon to use a battery (along with a voltage
regulator) in order to make the module fully autonomous.

<p align="center">
    <img src="./design/cwrm_schem.png">
</p>

### Parts

- 1 x ESP8266-01 (_U1_)
- 2 x 2.2k ohms (_R1_ and _R2_)
- 2 x 2N2222 (_Q1_ and _Q2_)
- 2.5mm male stereo plug (connected to _J1_)
- 3.3V power supply

## Software

The module creates its own WiFi network, and then acts as a captive portal,
redirecting everything to `192.168.10.1`. A simplistic web page is served to
control the camera.

### Development

The source code can be found in the `cwrm/` folder (Arduino IDE requires the
same name for both the main sketch and directory names). You can compile the
firmware using `make` (recommended):

    $ make clean
    $ make

You will need [html-minifier](https://github.com/kangax/html-minifier) installed
to compile the HTML code and generate the `cwrm/cwrm_generated.h` file:

    $ npm install html-minifier -g
    $ make compile-html

## Similar projects

- https://guillermoamaral.com/read/canon-wifimote/

## License

CWRM is released under the MIT License. See the bundled LICENSE file for
details.
