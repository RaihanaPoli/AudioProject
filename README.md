# Separate filter and volume for each stream (network & line)
      $ MIX_001 ---Contains code for the audio mixer IP
      $ Audioip_lab4 -- Contains code for the volume and filter IP
	    $ Driver/Devmem	
		      udpclient-- Contains simple library for receiving an UDP broadcast stream
		      AudioFilter-- Contains code for the filte
		      VolumeFilter-- Contains code for the volume
		      Devmem—receiving data from network
	    $ repo -- Contains ready-made IPs(volume and filter) for Vivado
  
  # Use GPIO to control switch on Zedboard and reflect it on filter and control LED
	  InterfaceWork(folder)
		    $ driver/devmem
		        AudioFilter
		        VolumeFilter
		        ZedboardOLED-- print on OLED
		        Devmem
            Udpclient  
  # Final Designing for the user interface  procedure
  FinalAudioMixer(folder)
	    $ Driver/devmem
	    Volume-Filter-Devmem---it is only when we tried to merge all together before separate the both stream (network & line) and it is working properly
	    ZedboardOLED
	    Devmem
	    Udpclient
	    network -- control from network
	    line -- control from line


