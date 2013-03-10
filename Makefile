#build harware control only when embedded
HARDWARE_CONTROL = tsrp_hardware_control
MOTOR_CONTROL = tsrp_motor_control

PACKAGES = $(MOTOR_CONTROL) 

ifeq ($(EMBEDDED_HARDWARE),TRUE)
	PACKAGES += $(HARDWARE_CONTROL)
endif

.PHONY: all $(PACKAGES)

all: $(PACKAGES)

$(PACKAGES):
	@$(MAKE) -j8 -C $@;

clean:
	for d in $(PACKAGES) ; do (cd $$d; $(MAKE) clean ) ; done
	