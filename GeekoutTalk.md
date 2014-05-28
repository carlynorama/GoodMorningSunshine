
Geekout Talk Outline
=============
Overview: Anatomy of a networked projects
-----
The system triangle:
- Local Inputs
- Internet compatible format for data (local data processing)
- Web connection - outbound protocol
- Remote Server for data storage 
  - For some projects, done here (dataloggers)
  - Others start here (twitter displays, etc.)
- Web connection - inbound protocol
- Ability to parse internet data
- Local Outputs

Demo
-----

- What it is
  - Two devices to ambiently connect loved ones
 
- Why it's interesting
  - Minimal interfaces, Retina LCD screens not needed
  - Arduino Yun as first Internet-primary Arduino
  - Network infrastructure for connected (IoT) devices

- Related work: 
  - Goodnight Lamp - http://www.goodnightlamp.com/
  - Availabot - http://berglondon.com/projects/availabot/

Building It
-----------

- Making enclosure

- Wiring up LEDs & switches

- Powering Arduino Yun


Behavior & Design
---------------

- General description of behavior

- Thoughts on color choices

- Fading algorithm

- Box design


Internet Connectivity
-----------------

- Network messaging needed
  - Send message to cloud
  - Receive message 

- ThingSpeak
  - pros
  - cons

- FTP
  - pros
  - cons

Hardware Discussion
-----------------

- Arduino Yun
  - Linux!
  - curl!
  - Python!

- BlinkM
  - high-level I2C commanding
  - built-in fading
 
Wrap Up
--------



