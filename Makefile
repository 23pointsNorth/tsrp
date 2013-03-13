#build harware control only when embedded
HARDWARE_CONTROL = tsrp_hardware_control
MOTOR_CONTROL = tsrp_motor_control
VIDEO_STREAM = tsrp_video_stream

PACKAGES = $(MOTOR_CONTROL) $(HARDWARE_CONTROL) $(VIDEO_STREAM)

#ifeq ($(EMBEDDED_HARDWARE),TRUE)
#	PACKAGES += $(HARDWARE_CONTROL)
#endif

.PHONY: all $(PACKAGES)

all: $(PACKAGES)

$(PACKAGES):
	@$(MAKE) -j8 -o3 -C $@;

clean:
	for d in $(PACKAGES) ; do (cd $$d; $(MAKE) clean ) ; done
	
