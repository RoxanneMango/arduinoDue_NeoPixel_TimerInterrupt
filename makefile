include *.include

OBJECTS = main.o
EXEC = doit

OUTPUT = build

.PHONY: src flash all clean

src: $(OBJECTS)
	@echo ("Linking everything together . . .")
	$(CXX) -mcpu=cortex-m3 -mthumb -Os -Wl,--gc-sections -T..\arduino\hardware\sam\1.6.12\variants\arduino_due_x\linker_scripts\gcc\flash.ld "-Wl,-Map,$(OUTPUT)\mapping.map" -o $(OUTPUT)\$(EXEC).elf -L$(OUTPUT) -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--entry=Reset_Handler -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align -Wl,--start-group -u _sbrk -u link -u _close -u _fstat -u _isatty -u _lseek -u _read -u _write -u _exit -u kill -u _getpid $(ARDUINO_DUE_AR) $(ADAFRUIT_NEOPIXEL_AR) $(RTC_AR) $(OUTPUT)\$(EXEC).a -Wl,--end-group -lm -lgcc
	$(OBJC) -O binary $(OUTPUT)\$(EXEC).elf $(OUTPUT)\$(EXEC).bin
	$(SIZE) -A $(OUTPUT)\$(EXEC).elf

%.o : %.cpp $(OUTPUT)
	@echo ("Compiling source files . . .);
	$(CXX) $(CXXFLAGS) $(ADAFRUIT_NEOPIXEL_I) $(RTC_I) $< -o $(OUTPUT)\$@
	$(AR) rcs $(OUTPUT)\$(EXEC).a $(OUTPUT)\$@

%.o : %.c $(OUTPUT)
	@echo ("Compiling source files . . .);
	$(CC) $(CFLAGS) $(ADAFRUIT_NEOPIXEL_I) $(RTC_I) $< -o $(OUTPUT)\$@
	$(AR) rcs $(OUTPUT)\$(EXEC).a $(OUTPUT)\$@

$(OUTPUT):
	mkdir build

flash:
	@echo ("Forcing reset with port-bump of 1200 bps . . .");
	$(PYTHON3) $(PORT_BUMP)
	@echo ("Writing binary to the arduino due . . .");
	$(BOSSAC) $(BOSSAC_FLAGS) $(OUTPUT)\$(EXEC).bin -R 

clean: 
	@echo ("Initiating lemon pledge . . .");
	cd $(OUTPUT) && del *.o *.bin *.elf *.map *.d *.a
	@echo ("I clean . . .");
	
all: lib src flash