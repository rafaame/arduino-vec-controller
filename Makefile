upload:
	platformio run -t upload

compile:
	platformio run

monitor:
	 while true; do if ! [[ -n "`lsof /dev/cu.usbmodem1451`" ]] ; then platformio device monitor; sleep 1; fi done