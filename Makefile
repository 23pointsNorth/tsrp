HARDWARE_CONTROL = tsrp_hardware_control
MOTOR_CONTROL = tsrp_motor_control

PACKAGES = $(HARDWARE_CONTROL) $(MOTOR_CONTROL) 
	
.PHONY: all $(PACKAGES)

all: $(PACKAGES)

$(PACKAGES):
	@$(MAKE) -j8 -C $@;

clean:
	for d in $(PACKAGES) ; do (cd $$d; $(MAKE) clean ) ; done
	