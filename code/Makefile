OUTDIR = $(HOME)/cmpt433/public/myApps/spotabone
FACERECOG_DIR = facerecog
TOCOPY = $(FACERECOG_DIR)/photodump/ $(FACERECOG_DIR)/stock/ $(FACERECOG_DIR)/camera.c $(FACERECOG_DIR)/Makefile

all: nested-cmodule camera-copy nested-spotify remarks

nested-cmodule:
	make --directory=cmodule

nested-spotify:
	make --directory=spotify

camera-copy:
	mkdir -p $(OUTDIR)/photos
	rm -rf $(OUTDIR)/photos/*
	cp -r $(TOCOPY) $(OUTDIR)
	@echo "Copied camera and its dependencies"

remarks:
	@echo ""
	@echo "You must do the following to run everything:"
	@echo "(bbg)$$ cd /mnt/remote/myApps/spotabone/"
	@echo "(bbg)$$ make"
	@echo "(bbg)$$ ./main"
	@echo "(bbg)$$ ./camera"
