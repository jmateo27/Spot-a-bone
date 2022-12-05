OUTDIR = $(HOME)/cmpt433/public/myApps/spotabone
FACERECOG_DIR = facerecog
CAMERA = $(FACERECOG_DIR)/camera.c

all: nested-cmodule camera-copy nested-spotify remarks

nested-cmodule:
	make --directory=cmodule

nested-spotify:
	make --directory=spotify

camera-copy:
	cp -r $(CAMERA) $(OUTDIR)
	mkdir -p $(OUTDIR)/photos
	cp -r $(FACERECOG_DIR)/* $(OUTDIR)
	@echo "Copied camera"

remarks:
	@echo ""
	@echo "You must do the following to run everything:"
	@echo "(bbg)$$ cd /mnt/remote/myApps/spotabone/"
	@echo "(bbg)$$ make"
	@echo "(bbg)$$ ./main"
	@echo "(bbg)$$ ./camera"
	@echo "(bbg)$$ python3 facerecog.py"
