BUILD_DIR=_build
BIN=facedetect

all: $(BUILD_DIR) cmake

$(BUILD_DIR):
	mkdir -p $@

cmake:
	cd $(BUILD_DIR) && cmake .. && make

clean:
	rm -rf $(BIN) $(BUILD_DIR) output.png classif
